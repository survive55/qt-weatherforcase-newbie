#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QStringList>
#include "weatherwidget.h"  // Include the header for your WeatherWidget

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnGo_clicked();
    void onWeatherDataReceived(QNetworkReply *reply);
    void on_btnMoreDetails_clicked();

        void updateCountdownLabel(int countdown);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QString API_KEY = "baa4a5e48bb2204d59ba0a956420b988";
    WeatherWidget *weatherWidget;
    QString temperature;
    QString description;
};

#endif // MAINWINDOW_H
