#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class WeatherWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherWidget(QWidget *parent = nullptr);

private slots:
    void fetchWeather();
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
};

#endif // WEATHERWIDGET_H
