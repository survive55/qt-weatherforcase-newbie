#define NOMINMAX
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "settingsdialog.h"
#include <QSettings>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QContextMenuEvent>
#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")
#include <windows.h>
#include <QWidget>
#include <QMouseEvent>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground, false);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    enableBlurBehindWindow();

    QString styleSheet = R"(
    QMainWindow {
        background-color: #2D2D30;
    }

QLabel {
 color: #FFFFFF; font-size: 16px;
}

    QLineEdit, QComboBox {
        background-color: #3C3C3C;
        color: #FFFFFF;
        border: 1px solid #4D4D4D;
        padding: 4px;
        border-radius: 4px;
    }

    QPushButton {
        background-color: #007ACC;
        color: #FFFFFF;
        border: none;
        padding: 6px 12px;
        border-radius: 4px;
    }

    QPushButton:hover {
        background-color: #005F9E;
    }

    QPushButton:pressed {
        background-color: #003F6E;
    }
    )";
    setStyleSheet(styleSheet);

    manager = new QNetworkAccessManager(this);

    weatherWidget = new WeatherWidget(this);
    connect(weatherWidget, &WeatherWidget::countdownUpdated, this, &MainWindow::updateCountdownLabel);
    connect(weatherWidget, &WeatherWidget::weatherDataUpdated, [this]() {
        weatherWidget->updateUI(ui);
    });


    connect(weatherWidget, &WeatherWidget::forecastDataUpdated, this, &MainWindow::updateForecastList);
    connect(weatherWidget, &WeatherWidget::alertsDataUpdated, this, &MainWindow::updateAlerts);

    loadCityList();
    ui->cmbCityName->setEditable(true);
    ui->cmbCityName->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    saveCityList();
    delete ui;
}

void MainWindow::on_btnGo_clicked()
{
    QSettings settings("YourCompany", "YourApp");
    QString apiKey = settings.value("apiKey", "").toString();
QString weatherApiKey = settings.value("weatherApiKey", "").toString();
    if (apiKey.isEmpty()) {
        QMessageBox::warning(this, "API 密钥未设置", "请在设置中输入您的 API 密钥。");
        return;
    }

    cityName = ui->cmbCityName->currentText();

    if (cityName.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入城市名称");
        return;
    }

    if (ui->cmbCityName->findText(cityName) == -1) {
        ui->cmbCityName->addItem(cityName);
    }

    weatherWidget->fetchWeather(cityName, apiKey);
    weatherWidget->fetchForecast(cityName, apiKey);
weatherWidget->fetchAlertsFromWeatherAPI(cityName, weatherApiKey);
    updateCountdownLabel(weatherWidget->getCountdown());
}

void MainWindow::updateCountdownLabel(int countdown)
{
    ui->countdownLabel->setText("距离下次刷新还有 " + QString::number(countdown) + " 秒");
}

void MainWindow::on_btnLocate_clicked()
{
    getPublicIpAddress();
}

void MainWindow::getPublicIpAddress()
{
    QNetworkRequest request;
    request.setUrl(QUrl("https://api.ipify.org?format=json"));
    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            QJsonObject jsonObj = jsonDoc.object();
            QString publicIp = jsonObj["ip"].toString();

            if (!publicIp.isEmpty()) {
                getCityByIp(publicIp);
            } else {
                QMessageBox::warning(this, "错误", "无法获取公网 IP 地址");
            }
        } else {
            QMessageBox::warning(this, "错误", "获取公网 IP 地址失败：" + reply->errorString());
        }
        reply->deleteLater();
    });
}

void MainWindow::getCityByIp(const QString &ipAddress)
{
    QNetworkRequest request;
    request.setUrl(QUrl(QString("http://ip-api.com/json/%1?fields=city").arg(ipAddress)));
    QNetworkReply *reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
            QJsonObject jsonObj = jsonDoc.object();
            QString city = jsonObj["city"].toString();

            if (!city.isEmpty()) {
                ui->cmbCityName->setCurrentText(city);
                on_btnGo_clicked();
            } else {
                QMessageBox::warning(this, "错误", "无法获取城市信息");
            }
        } else {
            QMessageBox::warning(this, "错误", "IP 地理定位失败：" + reply->errorString());
        }
        reply->deleteLater();
    });
}

void MainWindow::loadCityList()
{
    QSettings settings("YourCompany", "YourApp");
    QStringList cityList = settings.value("cityList").toStringList();
    if (cityList.isEmpty()) {
        cityList << "Taipei" << "New York" << "London" << "Tokyo" << "Sydney";
    }
    ui->cmbCityName->clear();
    ui->cmbCityName->addItems(cityList);
}

void MainWindow::saveCityList()
{
    QSettings settings("YourCompany", "YourApp");
    QStringList cityList;
    for (int i = 0; i < ui->cmbCityName->count(); ++i) {
        cityList << ui->cmbCityName->itemText(i);
    }
    settings.setValue("cityList", cityList);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->cmbCityName && event->type() == QEvent::ContextMenu) {
        QContextMenuEvent *menuEvent = static_cast<QContextMenuEvent*>(event);
        QMenu menu;
        QAction *removeAction = new QAction("删除城市", &menu);
        connect(removeAction, &QAction::triggered, [this]() {
            int index = ui->cmbCityName->currentIndex();
            if (index != -1) {
                ui->cmbCityName->removeItem(index);
            }
        });
        menu.addAction(removeAction);
        menu.exec(menuEvent->globalPos());
        return true;
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::on_actionApiKeySettings_clicked()
{
    SettingsDialog settingsDialog(this);
    settingsDialog.exec();
}

void MainWindow::enableBlurBehindWindow()
{
    HWND hWnd = reinterpret_cast<HWND>(winId());

    DWM_BLURBEHIND bb = {0};
    bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
    bb.fEnable = TRUE;
    bb.hRgnBlur = NULL;

    HRESULT hr = DwmEnableBlurBehindWindow(hWnd, &bb);
    if (FAILED(hr))
    {
        qDebug() << "Failed to enable blur behind window:" << hr;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragging = true;
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging && (event->buttons() & Qt::LeftButton))
    {
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_dragging = false;
    event->accept();
}

void MainWindow::on_btnClose_clicked()
{
    close();
}

void MainWindow::on_btnMinimize_clicked()
{
    showMinimized();
}

void MainWindow::updateForecastList()
{
    ui->forecastListWidget->clear();
    QList<QVariantMap> dailyData = weatherWidget->dailyForecastData;

    // 示例：仅显示每天的预报
    QMap<QString, QVariantMap> dailyMap;
    for (const QVariantMap &data : dailyData) {
        QString dateStr = data["date"].toString();
        if (!dailyMap.contains(dateStr)) {
            dailyMap[dateStr] = data;
        }
    }

    for (const QString &dateStr : dailyMap.keys()) {
        QVariantMap data = dailyMap[dateStr];
        double temp = data["temp"].toDouble();
        QString description = data["description"].toString();
        QString listItemText = QString("%1: %2 (温度: %3°C)")
                                   .arg(dateStr)
                                   .arg(description)
                                   .arg(temp);
        ui->forecastListWidget->addItem(listItemText);
    }
}
void MainWindow::updateAlerts()
{
    ui->alertsListWidget->clear();
    QList<QVariantMap> alerts = weatherWidget->alertsData;

    if (alerts.isEmpty()) {
        ui->alertsListWidget->addItem("当前没有灾害预警。");
        return;
    }

    for (const QVariantMap &alertData : alerts)
    {
        QString headline = alertData["headline"].toString();
        QString event = alertData["event"].toString();
        QString severity = alertData["severity"].toString();
        QString effective = alertData["effective"].toString();
        QString expires = alertData["expires"].toString();
        QString description = alertData["description"].toString();

        QString alertText = QString("标题：%1\n事件：%2\n严重程度：%3\n生效时间：%4\n结束时间：%5\n详情：%6\n")
                                .arg(headline)
                                .arg(event)
                                .arg(severity)
                                .arg(effective)
                                .arg(expires)
                                .arg(description);

        ui->alertsListWidget->addItem(alertText);
    }
}
