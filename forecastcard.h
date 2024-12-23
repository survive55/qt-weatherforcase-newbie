// forecastcard.h
#ifndef FORECASTCARD_H
#define FORECASTCARD_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class ForecastCard : public QWidget {
    Q_OBJECT
public:
    explicit ForecastCard(QWidget *parent = nullptr);

    void setDay(const QString &day);
    void setIcon(const QString &iconCode);
    void setDescription(const QString &desc);
    void setTemperature(double highTemp, double lowTemp);
    void setWindSpeed(double speed);

private:
    QLabel *dayLabel;
    QLabel *iconLabel;
    QLabel *descLabel;
    QLabel *tempHighLabel;
    QLabel *tempLowLabel;
    QLabel *windLabel;

    void setupUI();
};

#endif
