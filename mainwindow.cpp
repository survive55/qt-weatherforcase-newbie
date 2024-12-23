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
#include <QTextEdit>
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
    setupForecastContainer();
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icons/app.ico"));
    trayIcon->show();

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
    connect(weatherWidget, &WeatherWidget::weatherAlert,
            this, &MainWindow::handleWeatherAlert);

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
        QMessageBox::warning(this, "API key not set", "Please enter your API key in Settings");
        return;
    }

    cityName = ui->cmbCityName->currentText();

    if (cityName.isEmpty()) {
        QMessageBox::warning(this, "input error", "Please enter a city name");
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
    ui->countdownLabel->setText("Until the next refresh " + QString::number(countdown) + " sec");
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
                QMessageBox::warning(this, "error", "Unable to obtain public IP address");
            }
        } else {
            QMessageBox::warning(this, "error", "Failed to get public IP address：" + reply->errorString());
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
                QMessageBox::warning(this, "error", "Unable to get city information");
            }
        } else {
            QMessageBox::warning(this, "error", "Failure to locate ip：" + reply->errorString());
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
        QAction *removeAction = new QAction("Delete City", &menu);
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


void MainWindow::updateAlerts()
{
    ui->alertsListWidget->clear();
    QList<QVariantMap> alerts = weatherWidget->alertsData;


    QListWidgetItem *titleItem = new QListWidgetItem("Disaster Alert Information");
    titleItem->setTextAlignment(Qt::AlignCenter);
    titleItem->setBackground(QBrush(QColor(200, 0, 0, 180)));
    titleItem->setForeground(QBrush(Qt::white));
    QFont titleFont;
    titleFont.setBold(true);
    titleFont.setPointSize(12);
    titleItem->setFont(titleFont);
    ui->alertsListWidget->addItem(titleItem);

    if (alerts.isEmpty()) {
        QListWidgetItem *noAlertItem = new QListWidgetItem("✓ No disaster warning at this time");
        noAlertItem->setTextAlignment(Qt::AlignCenter);
        noAlertItem->setForeground(QBrush(Qt::green));
        ui->alertsListWidget->addItem(noAlertItem);
        return;
    }


    for (const QVariantMap &alertData : alerts) {
        QString severity = alertData["severity"].toString();
        QString event = alertData["event"].toString();
        QString effective = QDateTime::fromString(alertData["effective"].toString(), Qt::ISODate)
                                .toString("MM-dd HH:mm");


        QListWidgetItem *alertItem = new QListWidgetItem();


        QColor bgColor;
        QString icon;
        if (severity.toLower() == "severe") {
            bgColor = QColor(255, 0, 0, 180);
            icon = "⚠️";
        } else if (severity.toLower() == "moderate") {
            bgColor = QColor(255, 165, 0, 180);
            icon = "⚠";
        } else {
            bgColor = QColor(255, 255, 0, 180);
            icon = "ℹ";
        }

        QString previewText = QString("%1 %2\nRelease Time: %3")
                                  .arg(icon)
                                  .arg(event)
                                  .arg(effective);

        alertItem->setText(previewText);
        alertItem->setBackground(QBrush(bgColor));
        alertItem->setForeground(QBrush(Qt::white));
        alertItem->setData(Qt::UserRole, alertData);
        ui->alertsListWidget->addItem(alertItem);
    }


    if (!showMoreAlertsButton) {
        showMoreAlertsButton = new QPushButton("View more alerts", this);
        showMoreAlertsButton->setStyleSheet(R"(
            QPushButton {
                background-color: rgba(0, 122, 204, 0.8);
                color: white;
                border: none;
                padding: 5px;
                border-radius: 3px;
            }
            QPushButton:hover {
                background-color: rgba(0, 122, 204, 1.0);
            }
        )");
        ui->verticalLayout_3->addWidget(showMoreAlertsButton);
        connect(showMoreAlertsButton, &QPushButton::clicked,
                this, &MainWindow::on_showMoreAlertsButton_clicked);
    }


    connect(ui->alertsListWidget, &QListWidget::itemClicked,
            this, &MainWindow::showFullAlert);
}

void MainWindow::showFullAlert(QListWidgetItem* item)
{
    QVariant data = item->data(Qt::UserRole);
    if (data.isValid()) {
        showAlertDetails(data.toMap());
    }
}

void MainWindow::showAlertDetails(const QVariantMap &alertData)
{

    QDialog *detailDialog = new QDialog(this);
    detailDialog->setWindowTitle("Early Warning Details");
    detailDialog->setMinimumWidth(400);

    QVBoxLayout *layout = new QVBoxLayout(detailDialog);


    QString detailText = QString(
                             "Alert Type: %1\n\n"
                             "Severity: %2\n\n"
                             "Release Time: %3\n\n"
                             "End Time: %4\n\n"
                             "Details:\n%5")
                             .arg(alertData["event"].toString())
                             .arg(alertData["severity"].toString())
                             .arg(QDateTime::fromString(alertData["effective"].toString(), Qt::ISODate)
                                      .toString("yyyy-MM-dd HH:mm"))
                             .arg(QDateTime::fromString(alertData["expires"].toString(), Qt::ISODate)
                                      .toString("yyyy-MM-dd HH:mm"))
                             .arg(alertData["description"].toString());

    QTextEdit *textEdit = new QTextEdit(detailDialog);
    textEdit->setReadOnly(true);
    textEdit->setText(detailText);
    textEdit->setMinimumHeight(300);

    layout->addWidget(textEdit);


    QPushButton *closeButton = new QPushButton("Close", detailDialog);
    connect(closeButton, &QPushButton::clicked, detailDialog, &QDialog::accept);
    layout->addWidget(closeButton);

    detailDialog->setStyleSheet(R"(
        QDialog {
            background-color: #2D2D30;
            color: white;
        }
        QTextEdit {
            background-color: #1E1E1E;
            color: white;
            border: 1px solid #3C3C3C;
            border-radius: 4px;
        }
        QPushButton {
            background-color: #007ACC;
            color: white;
            border: none;
            padding: 5px 15px;
            border-radius: 3px;
        }
        QPushButton:hover {
            background-color: #005F9E;
        }
    )");

    detailDialog->exec();
}

void MainWindow::on_showMoreAlertsButton_clicked()
{

    QDialog *alertsDialog = new QDialog(this);
    alertsDialog->setWindowTitle("All Alerts");
    alertsDialog->setMinimumSize(500, 600);

    QVBoxLayout *layout = new QVBoxLayout(alertsDialog);
    QListWidget *alertsList = new QListWidget(alertsDialog);


    alertsList->setStyleSheet(ui->alertsListWidget->styleSheet());


    for (const QVariantMap &alertData : weatherWidget->alertsData) {
        QString severity = alertData["severity"].toString();
        QString event = alertData["event"].toString();
        QString effective = QDateTime::fromString(alertData["effective"].toString(), Qt::ISODate)
                                .toString("yyyy-MM-dd HH:mm");
        QString description = alertData["description"].toString();

        QListWidgetItem *item = new QListWidgetItem();
        QString text = QString("%1\nRelease Time: %2\n\n%3")
                           .arg(event)
                           .arg(effective)
                           .arg(description);

        item->setText(text);
        item->setData(Qt::UserRole, alertData);


        if (severity.toLower() == "severe") {
            item->setBackground(QBrush(QColor(255, 0, 0, 180)));
        } else if (severity.toLower() == "moderate") {
            item->setBackground(QBrush(QColor(255, 165, 0, 180)));
        } else {
            item->setBackground(QBrush(QColor(255, 255, 0, 180)));
        }

        item->setForeground(QBrush(Qt::white));
        alertsList->addItem(item);
    }

    layout->addWidget(alertsList);


    QPushButton *closeButton = new QPushButton("close", alertsDialog);
    connect(closeButton, &QPushButton::clicked, alertsDialog, &QDialog::accept);
    layout->addWidget(closeButton);

    alertsDialog->setStyleSheet(R"(
        QDialog {
            background-color: #2D2D30;
        }
        QPushButton {
            background-color: #007ACC;
            color: white;
            border: none;
            padding: 5px 15px;
            border-radius: 3px;
        }
        QPushButton:hover {
            background-color: #005F9E;
        }
    )");

    alertsDialog->exec();
}
void MainWindow::updateForecastList()
{

    QLayoutItem *item;
    while ((item = forecastLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    QDate currentDate = QDate::currentDate();
    int cardCount = 0;


    for (const QVariantMap &data : weatherWidget->dailyForecastData)
    {
        QDate forecastDate = data["date"].toDate();

        if (forecastDate >= currentDate && cardCount < 7)
        {
            ForecastCard *card = new ForecastCard(forecastContainer);


            QString dayName;
            if (forecastDate == currentDate) {
                dayName = "Today";
            } else {
                dayName = forecastDate.toString("dddd");
            }
            card->setDay(dayName);


            card->setIcon(data["icon"].toString());


            card->setDescription(data["description"].toString());


            double maxTemp = data["temp_max"].toDouble();
            double minTemp = data["temp_min"].toDouble();
            card->setTemperature(maxTemp, minTemp);


            double windSpeed = data["wind_speed"].toDouble();
            card->setWindSpeed(windSpeed);

            forecastLayout->addWidget(card);
            cardCount++;
        }
    }


    forecastLayout->addStretch();
}

void MainWindow::handleWeatherAlert(const QString &message, const QString &severity)
{

    QSystemTrayIcon::MessageIcon icon;
    if (severity.toLower() == "severe") {
        icon = QSystemTrayIcon::Critical;
    } else if (severity.toLower() == "moderate") {
        icon = QSystemTrayIcon::Warning;
    } else {
        icon = QSystemTrayIcon::Information;
    }


    trayIcon->showMessage("Weather Alert", message, icon, 15000);
}

void MainWindow::setupForecastContainer()
{

    forecastContainer = new QWidget(this);
    forecastLayout = new QHBoxLayout(forecastContainer);
    forecastLayout->setSpacing(10);
    forecastLayout->setContentsMargins(10, 10, 10, 10);


    ui->forecastListWidget->hide();


    ui->verticalLayout_3->addWidget(forecastContainer);
}
