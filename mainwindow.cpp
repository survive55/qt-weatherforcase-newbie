#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "settingsdialog.h"
#include <QSettings>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);

    weatherWidget = new WeatherWidget(this);
    connect(weatherWidget, &WeatherWidget::countdownUpdated, this, &MainWindow::updateCountdownLabel);
    connect(weatherWidget, &WeatherWidget::weatherDataUpdated, [this]() {
        weatherWidget->updateUI(ui);
    });

    positionSource = QGeoPositionInfoSource::createDefaultSource(this);
    if (positionSource) {
        connect(positionSource, &QGeoPositionInfoSource::positionUpdated,
                this, &MainWindow::positionUpdated);
        connect(positionSource, &QGeoPositionInfoSource::errorOccurred,
                this, [this](QGeoPositionInfoSource::Error error) {
                    QMessageBox::warning(this, "位置更新错误", "无法获取位置信息。");
                });
    } else {
        QMessageBox::warning(this, "错误", "无法创建位置源，请检查您的设备是否支持定位功能。");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnGo_clicked()
{
    QSettings settings("YourCompany", "YourApp");
    QString apiKey = settings.value("apiKey", "").toString();

    if (apiKey.isEmpty()) {
        QMessageBox::warning(this, "API 密钥未设置", "请在设置中输入您的 API 密钥。");
        return;
    }

    cityName = ui->txtCityName->text();

    if (cityName.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入城市名称。");
        return;
    }

    weatherWidget->fetchWeather(cityName, apiKey);

    updateCountdownLabel(weatherWidget->getCountdown());
}

void MainWindow::updateCountdownLabel(int countdown)
{
    ui->countdownLabel->setText("刷新倒计时: " + QString::number(countdown) + " 秒");
}

void MainWindow::on_btnLocate_clicked()
{
    if (positionSource) {
        positionSource->startUpdates();
    } else {
        QMessageBox::warning(this, "错误", "位置源不可用。");
    }
}

void MainWindow::positionUpdated(const QGeoPositionInfo &info)
{
    positionSource->stopUpdates();

    QGeoCoordinate coordinate = info.coordinate();
    if (coordinate.isValid()) {
        QString url = QString("https://nominatim.openstreetmap.org/reverse?format=json&lat=%1&lon=%2&zoom=18&addressdetails=1")
        .arg(coordinate.latitude(), 0, 'f', 8)
            .arg(coordinate.longitude(), 0, 'f', 8);

        QNetworkRequest request((QUrl(url)));

        request.setRawHeader("User-Agent", "weatherforcast/1.0 (timeset8000@gmail.com)");

        QNetworkReply *reply = networkManager->get(request);

        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            if (reply->error() == QNetworkReply::NoError) {
                QByteArray responseData = reply->readAll();
                QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
                QJsonObject jsonObj = jsonDoc.object();

                QJsonObject addressObj = jsonObj["address"].toObject();
                cityName = addressObj["city"].toString();

                if (cityName.isEmpty()) {
                    cityName = addressObj["town"].toString();
                }
                if (cityName.isEmpty()) {
                    cityName = addressObj["village"].toString();
                }

                if (cityName.isEmpty()) {
                    QMessageBox::warning(this, "错误", "无法获取城市名称。");
                } else {
                    ui->txtCityName->setText(cityName);
                    on_btnGo_clicked(); // 自动查询天气
                }
            } else {
                QMessageBox::warning(this, "错误", "逆地理编码失败：" + reply->errorString());
            }
            reply->deleteLater();
        });
    } else {
        QMessageBox::warning(this, "错误", "获取的坐标无效。");
    }
}

void MainWindow::on_actionApiKeySettings_clicked()
{
    SettingsDialog settingsDialog(this);
    settingsDialog.exec();
}
