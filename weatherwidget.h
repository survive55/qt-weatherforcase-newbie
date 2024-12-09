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
    QList<QVariantMap> dailyForecastData; // 存储每日天气数据

    // 添加成员变量
    QList<QVariantMap> alertsData; // 存储预警数据

signals:
    void weatherDataUpdated();
    void countdownUpdated(int countdown);
    void forecastDataUpdated(); // 发出天气预报数据已更新的信号
    void alertsDataUpdated();
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
