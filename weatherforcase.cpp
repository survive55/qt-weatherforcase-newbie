#include "ui_mainwindow.h"
#include "weatherwidget.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include <QMessageBox>

WeatherWidget::WeatherWidget(QWidget *parent) : QWidget(parent)
{
    manager = new QNetworkAccessManager(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() { fetchWeather(city, apiKey); });
    timer->start(600000);

    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &WeatherWidget::updateCountdown);
    countdownTimer->start(1000);
}

void WeatherWidget::fetchWeather(const QString &city, const QString &apiKey)
{
    this->city = city;
    this->apiKey = apiKey;

    QString url = QString("http://api.openweathermap.org/data/2.5/weather?q=%2&appid=%1&units=metric").arg(apiKey).arg(city);
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onWeatherDataReceived(reply);
    });

    countdown = 600;
}

void WeatherWidget::updateCountdown()
{
    countdown--;
    emit countdownUpdated(countdown);
}

int WeatherWidget::getCountdown() const
{
    return countdown;
}

void WeatherWidget::onWeatherDataReceived(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject json = document.object();

        temperature = QString::number(json["main"].toObject()["temp"].toDouble()) + "°C";

        description = json["weather"].toArray()[0].toObject()["description"].toString();
        emit weatherDataUpdated();
        reply->deleteLater();
    }

}

void WeatherWidget::updateUI(Ui::MainWindow *ui)
{
    ui->lbltemprature->setText(temperature);

    ui->lblDescription->setText(description);
}


