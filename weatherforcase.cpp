#include "weatherwidget.h"
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>

WeatherWidget::WeatherWidget(QWidget *parent) : QWidget(parent)
{
    manager = new QNetworkAccessManager(this);

    cityInput = new QLineEdit(this);
    cityInput->setPlaceholderText("輸入城市名稱");

    searchButton = new QPushButton("搜索", this);
    connect(searchButton, &QPushButton::clicked, this, &WeatherWidget::fetchWeather);

    temperatureLabel = new QLabel(this);
    descriptionLabel = new QLabel(this);
    humidityLabel = new QLabel(this);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(cityInput);
    layout->addWidget(searchButton);
    layout->addWidget(temperatureLabel);
    layout->addWidget(descriptionLabel);
    layout->addWidget(humidityLabel);

    setLayout(layout);
    setWindowTitle("天氣");
}

void WeatherWidget::fetchWeather()
{
    QString city = cityInput->text();
    QString API_KEY ="baa4a5e48bb2204d59ba0a956420b988";
    QString url = QString("http://api.openweathermap.org/data/2.5/weather?q=%2&appid=%1&units=metric").arg(API_KEY).arg(city);

    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onWeatherDataReceived(reply);
    });
}

void WeatherWidget::onWeatherDataReceived(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(data);
        QJsonObject json = document.object();

        QString temperature = QString::number(json["main"].toObject()["temp"].toDouble()) + "°C";
        QString description = json["weather"].toArray()[0].toObject()["description"].toString();
        QString humidity = "濕度: " + QString::number(json["main"].toObject()["humidity"].toInt()) + "%";

        updateUI(temperature, description, humidity);
    } else {
        updateUI("錯誤", "無法獲取天氣數據", "");
    }

    reply->deleteLater();
}

void WeatherWidget::updateUI(const QString &temperature, const QString &description, const QString &humidity)
{
    temperatureLabel->setText("溫度: " + temperature);
    descriptionLabel->setText("天氣: " + description);
    humidityLabel->setText(humidity);
}
