#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "ui_mainwindow.h"

class WeatherWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherWidget(QWidget *parent = nullptr);

    void fetchWeather(const QString &cityName, const QString &apiKey);
    void updateUI(Ui::MainWindow *ui);
    int getCountdown() const;
    void fetchForecast(const QString &cityName, const QString &apiKey);
    QList<QVariantMap> forecastData;



signals:
    void weatherDataUpdated();
    void countdownUpdated(int countdown);
    void forecastDataUpdated();





private slots:
    void onWeatherDataReceived(QNetworkReply *reply);
    void updateCountdown();



private:



    QNetworkAccessManager *manager;
    QTimer *timer;
    QTimer *countdownTimer;
    int countdown = 600;
    QString cityName;
    QString apiKey;
    QString temperature;
    QString description;
    QString humidity;
    QString windSpeed;
    QString countryCode;
    QString feelsLikeTemperature;
 QString iconCode;



};



#endif // WEATHERWIDGET_H
