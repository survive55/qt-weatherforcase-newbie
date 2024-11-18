
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGeoPositionInfoSource>
#include <QGeoCoordinate>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include "weatherwidget.h"
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
    void updateCountdownLabel(int countdown);
    void on_btnLocate_clicked();
    void positionUpdated(const QGeoPositionInfo &info);
    void on_actionApiKeySettings_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    WeatherWidget *weatherWidget;
    QString cityName;
    QGeoPositionInfoSource *positionSource;
    QNetworkAccessManager *networkManager;



};

#endif // MAINWINDOW_H
