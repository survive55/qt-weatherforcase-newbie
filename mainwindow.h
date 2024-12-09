#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include "weatherwidget.h"
#include <QPoint>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnGo_clicked();
    void updateCountdownLabel(int countdown);
    void on_btnLocate_clicked();
    void on_btnClose_clicked();
    void on_btnMinimize_clicked();
    void on_actionApiKeySettings_clicked();
    void updateForecastList(); // 新增，用于更新天气预报列表


    void updateAlerts();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    WeatherWidget *weatherWidget;
    QString cityName;
    QNetworkAccessManager *networkManager;
    void getPublicIpAddress();
    void getCityByIp(const QString &ipAddress);
    void loadCityList();
    void saveCityList();
    void enableBlurBehindWindow();
    bool m_dragging = false;
    QPoint m_dragPosition;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // MAINWINDOW_H
