#include "forecastcard.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>

ForecastCard::ForecastCard(QWidget *parent) : QWidget(parent) {
    setupUI();
}


void ForecastCard::setupUI()
{
    setFixedWidth(100);
    setFixedHeight(200);

    auto layout = new QVBoxLayout(this);
    layout->setSpacing(5);
    layout->setContentsMargins(5, 5, 5, 5);


    dayLabel = new QLabel(this);
    dayLabel->setAlignment(Qt::AlignCenter);
    dayLabel->setStyleSheet("QLabel { background-color: black; color: white; padding: 5px; }");

    iconLabel = new QLabel(this);
    iconLabel->setFixedSize(50, 50);
    iconLabel->setAlignment(Qt::AlignCenter);


    descLabel = new QLabel(this);
    descLabel->setAlignment(Qt::AlignCenter);
    descLabel->setWordWrap(true);


    tempHighLabel = new QLabel(this);
    tempLowLabel = new QLabel(this);
    tempHighLabel->setAlignment(Qt::AlignCenter);
    tempLowLabel->setAlignment(Qt::AlignCenter);


    windLabel = new QLabel(this);
    windLabel->setAlignment(Qt::AlignCenter);


    layout->addWidget(dayLabel);
    layout->addWidget(iconLabel);
    layout->addWidget(descLabel);
    layout->addWidget(tempHighLabel);
    layout->addWidget(tempLowLabel);
    layout->addWidget(windLabel);


    setStyleSheet(
        "ForecastCard {"
        "  background-color: rgba(200, 200, 200, 0.2);"
        "  border-radius: 5px;"
        "}"
        );
}

void ForecastCard::setDay(const QString &day) {
    dayLabel->setText(day);
}

void ForecastCard::setIcon(const QString &iconCode) {
    auto manager = new QNetworkAccessManager(this);
    QString url = QString("http://openweathermap.org/img/wn/%1@2x.png").arg(iconCode);

    QNetworkRequest request(url);
    auto reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QPixmap pixmap;
            pixmap.loadFromData(data);
            iconLabel->setPixmap(pixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        reply->deleteLater();
        manager->deleteLater();
    });
}

void ForecastCard::setDescription(const QString &desc) {
    descLabel->setText(desc);
}

void ForecastCard::setTemperature(double highTemp, double lowTemp)
{
    tempHighLabel->setText(QString("%1°").arg(qRound(highTemp)));
    tempLowLabel->setText(QString("%1°").arg(qRound(lowTemp)));
}
void ForecastCard::setWindSpeed(double speed) {
    windLabel->setText(QString("↑ %1km/h").arg(speed));
}
