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
#include <QJsonArray>
#include <QJsonDocument>



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
connect(weatherWidget, &WeatherWidget::forecastDataUpdated, this, &MainWindow::updateForecastTable);}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnGo_clicked()
{
    QSettings settings("YourCompany", "YourApp");
    QString apiKey = settings.value("apiKey", "").toString();

    if (apiKey.isEmpty()) {
        QMessageBox::warning(this, "API key not set", "Please enter your API key in the settings.");
        return;
    }

    cityName = ui->txtCityName->text();

    if (cityName.isEmpty()) {
        QMessageBox::warning(this, "input error", "Please enter a city name");
        return;
    }

    weatherWidget->fetchWeather(cityName, apiKey);
    weatherWidget->fetchForecast(cityName, apiKey);

    updateCountdownLabel(weatherWidget->getCountdown());
}

void MainWindow::updateCountdownLabel(int countdown)
{
    ui->countdownLabel->setText("Countdown to Refresh " + QString::number(countdown) + " 秒");
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
                QMessageBox::warning(this, "error", "Unable to obtain a public IP address");
            }
        } else {
            QMessageBox::warning(this, "error", "Failed to obtain a public IP address:" + reply->errorString());
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
                ui->txtCityName->setText(city);
                on_btnGo_clicked();
            } else {
                QMessageBox::warning(this, "error", "Unable to get city information");
            }
        } else {
            QMessageBox::warning(this, "error", "IP geolocation failure：" + reply->errorString());
        }
        reply->deleteLater();
    });
}
void MainWindow::updateForecastTable()
{
    ui->forecastTableWidget->clearContents();
    ui->forecastTableWidget->setRowCount(weatherWidget->forecastData.size());
    ui->forecastTableWidget->setColumnCount(4);

    QStringList headers;
    headers << "Date Time" << "temperature" << "description" << "icon";
    ui->forecastTableWidget->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < weatherWidget->forecastData.size(); ++i)
    {
        QVariantMap data = weatherWidget->forecastData[i];

        QTableWidgetItem *datetimeItem = new QTableWidgetItem(data["datetime"].toString());
        QTableWidgetItem *tempItem = new QTableWidgetItem(data["temperature"].toString());
        QTableWidgetItem *descItem = new QTableWidgetItem(data["description"].toString());

        ui->forecastTableWidget->setItem(i, 0, datetimeItem);
        ui->forecastTableWidget->setItem(i, 1, tempItem);
        ui->forecastTableWidget->setItem(i, 2, descItem);

          // Load and display icons
        QString iconCode = data["icon"].toString();
        QString iconUrl = QString("http://openweathermap.org/img/wn/%1.png").arg(iconCode);
        QNetworkRequest iconRequest(iconUrl);
        QNetworkReply *iconReply = networkManager->get(iconRequest);

        connect(iconReply, &QNetworkReply::finished, [this, iconReply, i]() {
            if (iconReply->error() == QNetworkReply::NoError)
            {
                QByteArray iconData = iconReply->readAll();
                QPixmap pixmap;
                pixmap.loadFromData(iconData);
                QTableWidgetItem *iconItem = new QTableWidgetItem;
                iconItem->setData(Qt::DecorationRole, pixmap.scaled(50, 50, Qt::KeepAspectRatio));
                ui->forecastTableWidget->setItem(i, 3, iconItem);
            }
            else
            {
                qDebug() << "Unable to load weather icon:" << iconReply->errorString();
            }
            iconReply->deleteLater();
        });
    }
}
void MainWindow::on_actionApiKeySettings_clicked()
{
    SettingsDialog settingsDialog(this);
    settingsDialog.exec();
}

