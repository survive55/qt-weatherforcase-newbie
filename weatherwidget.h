#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "ui_mainwindow.h"

class WeatherWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherWidget(QWidget *parent = nullptr);

   void updateUI(Ui::MainWindow *ui);
    int getCountdown() const;

   public:
           void fetchWeather(const QString &city, const QString &apiKey);

signals:
    void weatherDataUpdated();
    void countdownUpdated(int countdown);
public:

    void setCity(const QString &city);
    void setApiKey(const QString &apiKey);
    QJsonObject getCurrentWeather();

private slots:


    void onWeatherDataReceived(QNetworkReply *reply);
    void updateCountdown();


private:
    void updateUI(const QString &temperature, const QString &description, const QString &humidity);

    QNetworkAccessManager *manager;
    QLineEdit *cityInput;
    QLineEdit *ApiInput;
    QPushButton *searchButton;
    QLabel *temperatureLabel;
    QLabel *descriptionLabel;
    QLabel *humidityLabel;
    QTimer *timer;
    QLabel *countdownLabel;
    int countdown=600;
    QTimer *countdownTimer;
    QString city;
    QString apiKey;
    QString temperature;
    QString description;
};

#endif // WEATHERWIDGET_H
