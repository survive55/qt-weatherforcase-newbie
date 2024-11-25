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
void WeatherWidget::fetchForecast(const QString &cityName, const QString &apiKey)
{
    QString url = QString("http://api.openweathermap.org/data/2.5/forecast?q=%1&appid=%2&units=metric&lang=US")
    .arg(cityName)
        .arg(apiKey);
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray data = reply->readAll();
            QJsonDocument document = QJsonDocument::fromJson(data);
            QJsonObject json = document.object();
            QJsonArray list = json["list"].toArray();

            forecastData.clear();

            for (const QJsonValue &value : list)
            {
                QJsonObject obj = value.toObject();
                QVariantMap dataMap;
                dataMap["datetime"] = obj["dt_txt"].toString();
                dataMap["temp"] = QString::number(obj["main"].toObject()["temp"].toDouble(), 'f', 1) + "°C";
                dataMap["description"] = obj["weather"].toArray().first().toObject()["description"].toString();
                dataMap["icon"] = obj["weather"].toArray().first().toObject()["icon"].toString(); // Get the icon code
                forecastData.append(dataMap);
            }

            emit forecastDataUpdated();
        }

        else
        {
            QMessageBox::warning(this, "error", "Unable to get weather data:" + reply->errorString());
        }
        reply->deleteLater();
    });

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

        iconCode = json["weather"].toArray().first().toObject()["icon"].toString();

        emit weatherDataUpdated();
    }
    else
    {
        QMessageBox::warning(this, "error", "Unable to get weather data：" + reply->errorString());
    }
    reply->deleteLater();
}

void WeatherWidget::updateUI(Ui::MainWindow *ui)
{
    ui->lblTemperature->setText(temperature);
    ui->lblDescription->setText(description);
    ui->lblHumidity->setText(humidity);
    ui->lblWindSpeed->setText(windSpeed);
    ui->lblCityCountry->setText(cityName + ", " + countryCode);
    ui->lblFeelsLike->setText(feelsLikeTemperature);


    QString iconUrl = QString("http://openweathermap.org/img/wn/%1@2x.png").arg(iconCode);
    QNetworkRequest iconRequest(iconUrl);
    QNetworkReply *iconReply = manager->get(iconRequest);

    connect(iconReply, &QNetworkReply::finished, this, [this, iconReply, ui]() {
        if (iconReply->error() == QNetworkReply::NoError)
        {
            QByteArray iconData = iconReply->readAll();
            QPixmap pixmap;
            pixmap.loadFromData(iconData);
            ui->lblWeatherLogo->setPixmap(pixmap);
        }
        else
        {
            QMessageBox::warning(this, "error", "Unable to load weather icon:" + iconReply->errorString());
        }
        iconReply->deleteLater();
    });
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
