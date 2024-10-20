#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "weatherwidget.h"

class QTreeWidget;
class QTabWidget;
class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void setupUi();
    void openWeatherWidget();

    QTreeWidget *tree;
    QTabWidget *tabs;
    QTextEdit *logArea;
    WeatherWidget *weatherWidget;
};

#endif // MAINWINDOW_H
