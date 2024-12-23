#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "ui_mainwindow.h"
#include <QTimer>
#include <QVariantMap>

class WeatherWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherWidget(QWidget *parent = nullptr);
    void fetchWeather(const QString &cityName, const QString &apiKey);
    void updateUI(Ui::MainWindow *ui);
    int getCountdown() const;
    void fetchForecast(const QString &cityName, const QString &apiKey);
    void fetchAlertsFromWeatherAPI(const QString &cityName, const QString &weatherApiKey);
    QList<QVariantMap> dailyForecastData;

    QList<QVariantMap> alertsData;

signals:
    void weatherDataUpdated();
    void countdownUpdated(int countdown);
    void forecastDataUpdated();
    void alertsDataUpdated();
    void weatherAlert(const QString &message, const QString &severity);

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
    QString cwbApiKey;
    QTimer *cwbTimer;
    void initializeTaiwanCityMap();
    void fetchCWBAlerts(const QString &cityName);
    void processCWBAlerts(const QByteArray &data);
     QString currentCity;
    QMap<QString, QString> taiwanCityMap;
    bool isInTaiwan = false;

};


#endif // WEATHERWIDGET_H
