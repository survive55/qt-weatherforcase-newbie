/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *groupBox;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLabel *lblCity;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_8;
    QLabel *lblCityCountry;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QLabel *lblHumidity;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_4;
    QLabel *lblWindSpeed;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_8;
    QLabel *lblDescription;
    QLabel *lblWeatherLogo;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblRealFeel_2;
    QLabel *lblFeelsLike;
    QWidget *layoutWidget7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lblTemperature;
    QLabel *countdownLabel;
    QPushButton *actionApiKeySettings;
    QPushButton *btnMoreDetails;
    QWidget *layoutWidget8;
    QHBoxLayout *horizontalLayout;
    QLabel *City;
    QLineEdit *txtCityName;
    QPushButton *btnLocate;
    QPushButton *btnGo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(650, 550);
        MainWindow->setMinimumSize(QSize(650, 550));
        MainWindow->setMaximumSize(QSize(650, 550));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 30, 619, 579));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_2);

        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName("groupBox");
        groupBox->setMinimumSize(QSize(0, 200));
        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(370, 70, 131, 18));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName("label_5");

        horizontalLayout_3->addWidget(label_5);

        lblCity = new QLabel(layoutWidget1);
        lblCity->setObjectName("lblCity");

        horizontalLayout_3->addWidget(lblCity);

        layoutWidget2 = new QWidget(groupBox);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(370, 100, 134, 18));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget2);
        label_8->setObjectName("label_8");

        horizontalLayout_4->addWidget(label_8);

        lblCityCountry = new QLabel(layoutWidget2);
        lblCityCountry->setObjectName("lblCityCountry");

        horizontalLayout_4->addWidget(lblCityCountry);

        layoutWidget3 = new QWidget(groupBox);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(190, 100, 161, 21));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget3);
        label_3->setObjectName("label_3");

        horizontalLayout_6->addWidget(label_3);

        lblHumidity = new QLabel(layoutWidget3);
        lblHumidity->setObjectName("lblHumidity");

        horizontalLayout_6->addWidget(lblHumidity);

        layoutWidget4 = new QWidget(groupBox);
        layoutWidget4->setObjectName("layoutWidget4");
        layoutWidget4->setGeometry(QRect(190, 70, 161, 18));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget4);
        label_4->setObjectName("label_4");

        horizontalLayout_7->addWidget(label_4);

        lblWindSpeed = new QLabel(layoutWidget4);
        lblWindSpeed->setObjectName("lblWindSpeed");

        horizontalLayout_7->addWidget(lblWindSpeed);

        layoutWidget5 = new QWidget(groupBox);
        layoutWidget5->setObjectName("layoutWidget5");
        layoutWidget5->setGeometry(QRect(12, 20, 281, 41));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        lblDescription = new QLabel(layoutWidget5);
        lblDescription->setObjectName("lblDescription");
        lblDescription->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_8->addWidget(lblDescription);

        lblWeatherLogo = new QLabel(layoutWidget5);
        lblWeatherLogo->setObjectName("lblWeatherLogo");

        horizontalLayout_8->addWidget(lblWeatherLogo);

        layoutWidget6 = new QWidget(groupBox);
        layoutWidget6->setObjectName("layoutWidget6");
        layoutWidget6->setGeometry(QRect(11, 150, 121, 17));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        lblRealFeel_2 = new QLabel(layoutWidget6);
        lblRealFeel_2->setObjectName("lblRealFeel_2");

        horizontalLayout_2->addWidget(lblRealFeel_2);

        lblFeelsLike = new QLabel(layoutWidget6);
        lblFeelsLike->setObjectName("lblFeelsLike");

        horizontalLayout_2->addWidget(lblFeelsLike);

        layoutWidget7 = new QWidget(groupBox);
        layoutWidget7->setObjectName("layoutWidget7");
        layoutWidget7->setGeometry(QRect(14, 70, 171, 72));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget7);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        lblTemperature = new QLabel(layoutWidget7);
        lblTemperature->setObjectName("lblTemperature");
        lblTemperature->setMinimumSize(QSize(50, 70));
        lblTemperature->setMaximumSize(QSize(300, 16777215));
        QFont font;
        font.setPointSize(40);
        lblTemperature->setFont(font);

        horizontalLayout_5->addWidget(lblTemperature);

        countdownLabel = new QLabel(groupBox);
        countdownLabel->setObjectName("countdownLabel");
        countdownLabel->setEnabled(true);
        countdownLabel->setGeometry(QRect(470, 180, 91, 16));
        actionApiKeySettings = new QPushButton(groupBox);
        actionApiKeySettings->setObjectName("actionApiKeySettings");
        actionApiKeySettings->setGeometry(QRect(10, 180, 111, 23));

        verticalLayout_3->addWidget(groupBox);

        btnMoreDetails = new QPushButton(layoutWidget);
        btnMoreDetails->setObjectName("btnMoreDetails");
        btnMoreDetails->setMinimumSize(QSize(100, 30));
        btnMoreDetails->setMaximumSize(QSize(100, 30));

        verticalLayout_3->addWidget(btnMoreDetails);

        layoutWidget8 = new QWidget(centralwidget);
        layoutWidget8->setObjectName("layoutWidget8");
        layoutWidget8->setGeometry(QRect(10, 0, 617, 32));
        horizontalLayout = new QHBoxLayout(layoutWidget8);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        City = new QLabel(layoutWidget8);
        City->setObjectName("City");

        horizontalLayout->addWidget(City);

        txtCityName = new QLineEdit(layoutWidget8);
        txtCityName->setObjectName("txtCityName");
        txtCityName->setEnabled(true);
        txtCityName->setFrame(false);

        horizontalLayout->addWidget(txtCityName);

        btnLocate = new QPushButton(layoutWidget8);
        btnLocate->setObjectName("btnLocate");

        horizontalLayout->addWidget(btnLocate);

        btnGo = new QPushButton(layoutWidget8);
        btnGo->setObjectName("btnGo");
        btnGo->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(btnGo);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 650, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "WeatherApp", nullptr));
        groupBox->setTitle(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "City", nullptr));
        lblCity->setText(QCoreApplication::translate("MainWindow", "City Name", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Country", nullptr));
        lblCityCountry->setText(QCoreApplication::translate("MainWindow", "Country Name", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Humidity", nullptr));
        lblHumidity->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "Wind", nullptr));
        lblWindSpeed->setText(QString());
        lblDescription->setText(QCoreApplication::translate("MainWindow", "Weather Description", nullptr));
        lblWeatherLogo->setText(QCoreApplication::translate("MainWindow", "Weather Logo", nullptr));
        lblRealFeel_2->setText(QCoreApplication::translate("MainWindow", "Real Feel", nullptr));
        lblFeelsLike->setText(QCoreApplication::translate("MainWindow", "RealFeel", nullptr));
        lblTemperature->setText(QString());
        countdownLabel->setText(QCoreApplication::translate("MainWindow", "countdown:", nullptr));
        actionApiKeySettings->setText(QCoreApplication::translate("MainWindow", "API KEY SETTING", nullptr));
        btnMoreDetails->setText(QCoreApplication::translate("MainWindow", "More Details..", nullptr));
        City->setText(QCoreApplication::translate("MainWindow", "CITYIMPUT", nullptr));
        btnLocate->setText(QCoreApplication::translate("MainWindow", "Locate", nullptr));
        btnGo->setText(QCoreApplication::translate("MainWindow", "Go", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
