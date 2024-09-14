#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QJsonArray>

class WeatherWidget : public QWidget
{
    Q_OBJECT

public:
    WeatherWidget(QWidget *parent = nullptr);

private slots:
    void fetchWeather();
  void onWeatherDataReceived(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QLineEdit *cityInput;
    QPushButton *searchButton;
    QLabel *temperatureLabel;
    QLabel *descriptionLabel;
    QLabel *humidityLabel;

    void updateUI(const QString &temperature, const QString &description, const QString &humidity);
};

#endif // WEATHERWIDGET_H
