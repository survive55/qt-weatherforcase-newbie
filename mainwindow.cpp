#include "mainwindow.h"
#include <QTreeWidget>
#include <QTabWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi();
}

void MainWindow::setupUi()
{
    setWindowTitle("WeatherForecast");
    setGeometry(100, 100, 1000, 600);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, centralWidget);
    mainLayout->addWidget(splitter);


    tree = new QTreeWidget();
    tree->setHeaderLabel("天氣預報");
    QStringList items = {"台灣", "中國", "日本", "韓國"};
    for (const QString &item : items) {
        QTreeWidgetItem *treeItem = new QTreeWidgetItem(QStringList(item));
        tree->addTopLevelItem(treeItem);
    }
    splitter->addWidget(tree);

    // Right side
    QWidget *rightWidget = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
    splitter->addWidget(rightWidget);

    // Top buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *weatherButton = new QPushButton("天氣預報", rightWidget);
    buttonLayout->addWidget(weatherButton);
    connect(weatherButton, &QPushButton::clicked, this, &MainWindow::openWeatherWidget);
    rightLayout->addLayout(buttonLayout);


    tabs = new QTabWidget(rightWidget);
    rightLayout->addWidget(tabs);


    weatherWidget = new WeatherWidget(this);
    tabs->addTab(weatherWidget, "天氣預報");

    // Add an "Overview" tab
    QWidget *overviewTab = new QWidget();
    QVBoxLayout *overviewLayout = new QVBoxLayout(overviewTab);
    QLabel *overviewLabel = new QLabel("歡迎使用天氣預報應用！\n\n"
                                       "使用方法：\n"
                                       "1. 點擊左側樹狀圖中的地區\n"
                                       "2. 在右側的「天氣預報」標籤頁中輸入城市名稱\n"
                                       "3. 輸入您的 API 密鑰\n"
                                       "4. 點擊「搜索」按鈕獲取天氣信息");
    overviewLayout->addWidget(overviewLabel);
    tabs->addTab(overviewTab, "總覽");

    // Set the "Overview" tab as the default
    tabs->setCurrentIndex(1);

    // Log area
    logArea = new QTextEdit(rightWidget);
    logArea->setReadOnly(true);
    logArea->setMaximumHeight(100);
    rightLayout->addWidget(logArea);

    // Set the splitter's initial sizes
    splitter->setSizes(QList<int>() << 200 << 800);
}

void MainWindow::openWeatherWidget()
{
    tabs->setCurrentWidget(weatherWidget);
}
