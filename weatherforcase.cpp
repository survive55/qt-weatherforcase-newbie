#include "weatherwidget.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QGraphicsOpacityEffect>
#include <QPainter>
#include <QPropertyAnimation>
#include <QSettings>

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
    QElapsedTimer timer;
    timer.start();
    QString url = QString("https://api.openweathermap.org/data/2.5/weather?q=%1&appid=%2&units=metric")
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
    QString coordUrl = QString("https://api.openweathermap.org/data/2.5/weather?q=%1&appid=%2")
    .arg(cityName)
        .arg(apiKey);
    QNetworkRequest coordRequest(coordUrl);
    QNetworkReply *coordReply = manager->get(coordRequest);

    connect(coordReply, &QNetworkReply::finished, this, [this, coordReply, apiKey]() {
        if (coordReply->error() == QNetworkReply::NoError)
        {
            QByteArray data = coordReply->readAll();
            QJsonDocument document = QJsonDocument::fromJson(data);
            QJsonObject json = document.object();

            double lat = json["coord"].toObject()["lat"].toDouble();
            double lon = json["coord"].toObject()["lon"].toDouble();


            QString url = QString("https://api.openweathermap.org/data/2.5/forecast?lat=%1&lon=%2&appid=%3&units=metric")
                              .arg(lat)
                              .arg(lon)
                              .arg(apiKey);
            QNetworkRequest request(url);
            QNetworkReply *reply = manager->get(request);

            connect(reply, &QNetworkReply::finished, this, [this, reply]() {
                if (reply->error() == QNetworkReply::NoError)
                {
                    QByteArray data = reply->readAll();
                    QJsonDocument document = QJsonDocument::fromJson(data);
                    QJsonObject json = document.object();
                    QJsonArray forecastList = json["list"].toArray();

                    dailyForecastData.clear();
                    QMap<QString, QVariantMap> dailyTempMap;


                    QDate currentDate = QDate::currentDate();


                    for (const QJsonValue &value : forecastList)
                    {
                        QJsonObject obj = value.toObject();
                        QString dateTimeStr = obj["dt_txt"].toString();
                        QDateTime dateTime = QDateTime::fromString(dateTimeStr, "yyyy-MM-dd HH:mm:ss");
                        QDate forecastDate = dateTime.date();


                        if (forecastDate >= currentDate)
                        {
                            QString dateStr = forecastDate.toString("yyyy-MM-dd");
                            double temp = obj["main"].toObject()["temp"].toDouble();
                            QString description = obj["weather"].toArray().first().toObject()["description"].toString();
                            QString icon = obj["weather"].toArray().first().toObject()["icon"].toString();
                            double windSpeed = obj["wind"].toObject()["speed"].toDouble();

                            if (!dailyTempMap.contains(dateStr))
                            {
                                QVariantMap dayData;
                                dayData["date"] = forecastDate;
                                dayData["temp_max"] = temp;
                                dayData["temp_min"] = temp;
                                dayData["description"] = description;
                                dayData["icon"] = icon;
                                dayData["wind_speed"] = windSpeed;
                                dailyTempMap[dateStr] = dayData;
                            }
                            else
                            {
                                QVariantMap &dayData = dailyTempMap[dateStr];
                                dayData["temp_max"] = qMax(dayData["temp_max"].toDouble(), temp);
                                dayData["temp_min"] = qMin(dayData["temp_min"].toDouble(), temp);
                            }
                        }
                    }


                    QStringList dateKeys = dailyTempMap.keys();
                    std::sort(dateKeys.begin(), dateKeys.end());
                    for (const QString &dateStr : dateKeys)
                    {
                        dailyForecastData.append(dailyTempMap[dateStr]);
                    }

                    emit forecastDataUpdated();
                }
                reply->deleteLater();
            });
        }
        coordReply->deleteLater();
    });
}
void WeatherWidget::onWeatherDataReceived(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray data = reply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject json = document.object();

        temperature = QString::number(json["main"].toObject()["temp"].toDouble(), 'f', 1) + "°C";
        description = json["weather"].toArray().first().toObject()["description"].toString();
        humidity = QString::number(json["main"].toObject()["humidity"].toInt()) + "%";
        windSpeed = QString::number(json["wind"].toObject()["speed"].toDouble(), 'f', 1) + " m/s";
        cityName = json["name"].toString();
        countryCode = json["sys"].toObject()["country"].toString();
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

    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(ui->groupBox);
    ui->groupBox->setGraphicsEffect(effect);

    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(500);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start(QPropertyAnimation::DeleteWhenStopped);

    QString iconUrl = QString("http://openweathermap.org/img/wn/%1@2x.png").arg(iconCode);
    QNetworkRequest iconRequest(iconUrl);
    QNetworkReply *iconReply = manager->get(iconRequest);

    connect(iconReply, &QNetworkReply::finished, this, [this, iconReply, ui]() {
        if (iconReply->error() == QNetworkReply::NoError)
        {
            QByteArray iconData = iconReply->readAll();
            QPixmap pixmap;
            pixmap.loadFromData(iconData);
            ui->lblWeatherLogo->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        else
        {
            QMessageBox::warning(this, "error", "Unable to load weather icons：" + iconReply->errorString());
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
void WeatherWidget::fetchAlertsFromWeatherAPI(const QString &cityName, const QString &weatherApiKey)
{

    QString url = QString("https://api.weatherapi.com/v1/forecast.json?key=%1&q=%2&days=1&alerts=yes&lang=zh")
    .arg(weatherApiKey)
        .arg(cityName);
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray data = reply->readAll();
            QJsonDocument document = QJsonDocument::fromJson(data);
            QJsonObject json = document.object();


            if (json.contains("alerts") && json["alerts"].toObject().contains("alert"))
            {
                QJsonArray alertsArray = json["alerts"].toObject()["alert"].toArray();
                alertsData.clear();
                for (const QJsonValue &value : alertsArray)
                {
                    QJsonObject alertObj = value.toObject();
                    QVariantMap alertData;
                    alertData["headline"] = alertObj["headline"].toString();
                    alertData["event"] = alertObj["event"].toString();
                    alertData["severity"] = alertObj["severity"].toString();
                    alertData["effective"] = alertObj["effective"].toString();
                    alertData["expires"] = alertObj["expires"].toString();
                    alertData["description"] = alertObj["desc"].toString();
                    alertsData.append(alertData);
                }
                emit alertsDataUpdated();
            }
            else
            {

                alertsData.clear();
                emit alertsDataUpdated();
            }
        }
        else
        {
            QMessageBox::warning(this, "error", "Inability to access early warning data：" + reply->errorString());
        }
        reply->deleteLater();
    });
}


