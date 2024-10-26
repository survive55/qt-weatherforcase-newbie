#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);


    QStringList countryCodes;
    countryCodes << "US" << "CA" << "UK" << "JP"<<"TW";
    ui->cmbBox->addItems(countryCodes);

    weatherWidget = new WeatherWidget(this); // Initialize the WeatherWidget
    connect(weatherWidget, &WeatherWidget::countdownUpdated, this, &MainWindow::updateCountdownLabel);


    }


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnGo_clicked()
{
    QString countryCode = ui->cmbBox->currentText();
    QString zipCode = ui->txtZipCode->text();
     QString apiKey = "baa4a5e48bb2204d59ba0a956420b988";
      weatherWidget->fetchWeather("", apiKey);

    QString url = QString("http://api.openweathermap.org/data/2.5/weather?zip=%1,%2&appid=%3&units=metric")
                      .arg(zipCode)
                      .arg(countryCode)
                      .arg(API_KEY);

    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onWeatherDataReceived(reply);
    });
}


void MainWindow::onWeatherDataReceived(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(data);


        weatherWidget->updateUI(ui);

        QJsonObject json = document.object();
          temperature = QString::number(json["main"].toObject()["temp"].toDouble());


          ui->lbltemprature->setText(QString::number(json["main"].toObject()["temp"].toDouble()));
          ui->lblDescription->setText(json["weather"].toArray()[0].toObject()["description"].toString());
          ui->lblWind->setText(QString::number(json["wind"].toObject()["speed"].toDouble()) + " m/s");
          ui->lblHumidity->setText(QString::number(json["main"].toObject()["humidity"].toInt()) + "%");
          ui->lblRealFeel->setText(QString::number(json["main"].toObject()["feels_like"].toDouble()) + "°C");
          ui->lblCity->setText(json["name"].toString());
          ui->lblCountryName->setText(json["sys"].toObject()["country"].toString());



    }

    reply->deleteLater();
}

void MainWindow::on_btnMoreDetails_clicked()
{

    weatherWidget->show();
}

void MainWindow::updateCountdownLabel(int countdown)
{
    ui->countdownLabel->setText("刷新倒計時: " + QString::number(weatherWidget->getCountdown()));
}
