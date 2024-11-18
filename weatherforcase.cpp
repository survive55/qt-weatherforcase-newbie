#include "weatherwidget.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QTimer>
WeatherWidget::WeatherWidget(QWidget *parent) : QWidget(parent)
{
    manager = new QNetworkAccessManager(this);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() { fetchWeather(cityName, apiKey); });
    timer->start(600000);

    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &WeatherWidget::updateCountdown);
    countdownTimer->start(1000);
}

void WeatherWidget::fetchWeather(const QString &cityName, const QString &apiKey)
{
    this->cityName = cityName;
    this->apiKey = apiKey;

    QString url = QString("http://api.openweathermap.org/data/2.5/weather?q=%1&appid=%2&units=metric")
                      .arg(cityName)
                      .arg(apiKey);
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onWeatherDataReceived(reply);
    });

    countdown = 600;
}

void WeatherWidget::onWeatherDataReceived(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject json = document.object();


        temperature = QString::number(json["main"].toObject()["temp"].toDouble()) + "°C";


        description = json["weather"].toArray().first().toObject()["description"].toString();


        humidity = QString::number(json["main"].toObject()["humidity"].toInt()) + "%";


        windSpeed = QString::number(json["wind"].toObject()["speed"].toDouble()) + " m/s";


        cityName = json["name"].toString();


        countryCode = json["sys"].toObject()["country"].toString();

        cityName = json["name"].toString();

        feelsLikeTemperature = QString::number(json["main"].toObject()["feels_like"].toDouble(), 'f', 1) + "°C";

        emit weatherDataUpdated();
    }
    else
    {
        QMessageBox::warning(this, "错误", "无法获取天气数据：" + reply->errorString());
    }
    reply->deleteLater();
}

void WeatherWidget::updateUI(Ui::MainWindow *ui)
{
    ui->lblTemperature->setText(temperature);
    ui->lblDescription->setText(description);
    ui->lblHumidity->setText(humidity);
    ui->lblWindSpeed->setText( windSpeed);
    ui->lblCityCountry->setText(cityName + ", " + countryCode);
    ui->lblFeelsLike->setText( feelsLikeTemperature);

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
