#include "weatherwidget.h"
#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include<QTimer>
#include<QSettings>

WeatherWidget::WeatherWidget(QWidget *parent) : QWidget(parent)
{
    manager = new QNetworkAccessManager(this);
    resize(400,400);
    cityInput = new QLineEdit(this);
    cityInput->setPlaceholderText("輸入城市名稱");

    ApiInput = new QLineEdit(this);//api input
    ApiInput-> setPlaceholderText("輸入api");
    ApiInput-> setPlaceholderText("輸入api");

    searchButton = new QPushButton("搜索", this);//sec
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
    layout->addWidget(ApiInput);

    setLayout(layout);
    setWindowTitle("天氣");

    timer=new QTimer(this);

    connect(timer, &QTimer::timeout, this, &WeatherWidget::fetchWeather);
    timer->start(600000);
    countdownLabel = new QLabel(this);
    countdownLabel->setText("刷新倒計時: 600");
    layout->addWidget(countdownLabel);

    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &WeatherWidget::updateCountdown);
    countdownTimer->start(1000);


    connect(timer, &QTimer::timeout, this, &WeatherWidget::updateCountdown);
}



void WeatherWidget::fetchWeather()
{
    QString city = cityInput->text();
    QString API_KEY =ApiInput->text();//baa4a5e48bb2204d59ba0a956420b988
    QString url = QString("http://api.openweathermap.org/data/2.5/weather?q=%2&appid=%1&units=metric").arg(API_KEY).arg(city);

    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onWeatherDataReceived(reply);
    });
    countdown = 600;
    countdownLabel->setText("刷新倒計時: " + QString::number(countdown));
}
void WeatherWidget::updateCountdown()
{
    countdown--;
    countdownLabel->setText("刷新倒計時: " + QString::number(countdown));

    if (countdown == 0) {

        fetchWeather();
    }
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
//made and code by bob
//uwu
