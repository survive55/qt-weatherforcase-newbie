/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
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
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *cmbBox;
    QLabel *label_2;
    QLineEdit *txtZipCode;
    QPushButton *btnGo;
    QSpacerItem *verticalSpacer_2;
    QPushButton *btnMoreDetails;
    QGroupBox *groupBox;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLabel *lblCity;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_8;
    QLabel *lblCountryName;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QLabel *lblHumidity;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_4;
    QLabel *lblWind;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_8;
    QLabel *lblDescription;
    QLabel *lblWeatherLogo;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lblRealFeel_2;
    QLabel *lblRealFeel;
    QWidget *layoutWidget7;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lbltemprature;
    QVBoxLayout *verticalLayout;
    QLabel *label_7;
    QLabel *lblCelcius;
    QLabel *countdownLabel;
    QSpacerItem *verticalSpacer;
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
        layoutWidget->setGeometry(QRect(11, 11, 619, 579));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        cmbBox = new QComboBox(layoutWidget);
        cmbBox->setObjectName("cmbBox");
        cmbBox->setMinimumSize(QSize(250, 30));

        horizontalLayout->addWidget(cmbBox);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        txtZipCode = new QLineEdit(layoutWidget);
        txtZipCode->setObjectName("txtZipCode");
        txtZipCode->setMinimumSize(QSize(70, 30));
        QFont font;
        font.setKerning(true);
        txtZipCode->setFont(font);

        horizontalLayout->addWidget(txtZipCode);

        btnGo = new QPushButton(layoutWidget);
        btnGo->setObjectName("btnGo");
        btnGo->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(btnGo);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_2);

        btnMoreDetails = new QPushButton(layoutWidget);
        btnMoreDetails->setObjectName("btnMoreDetails");
        btnMoreDetails->setMinimumSize(QSize(100, 30));
        btnMoreDetails->setMaximumSize(QSize(100, 30));

        verticalLayout_3->addWidget(btnMoreDetails);

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

        lblCountryName = new QLabel(layoutWidget2);
        lblCountryName->setObjectName("lblCountryName");

        horizontalLayout_4->addWidget(lblCountryName);

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

        lblWind = new QLabel(layoutWidget4);
        lblWind->setObjectName("lblWind");

        horizontalLayout_7->addWidget(lblWind);

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

        lblRealFeel = new QLabel(layoutWidget6);
        lblRealFeel->setObjectName("lblRealFeel");

        horizontalLayout_2->addWidget(lblRealFeel);

        layoutWidget7 = new QWidget(groupBox);
        layoutWidget7->setObjectName("layoutWidget7");
        layoutWidget7->setGeometry(QRect(14, 70, 171, 72));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget7);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        lbltemprature = new QLabel(layoutWidget7);
        lbltemprature->setObjectName("lbltemprature");
        lbltemprature->setMinimumSize(QSize(50, 70));
        lbltemprature->setMaximumSize(QSize(300, 16777215));
        QFont font1;
        font1.setPointSize(40);
        lbltemprature->setFont(font1);

        horizontalLayout_5->addWidget(lbltemprature);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_7 = new QLabel(layoutWidget7);
        label_7->setObjectName("label_7");

        verticalLayout->addWidget(label_7);

        lblCelcius = new QLabel(layoutWidget7);
        lblCelcius->setObjectName("lblCelcius");
        QFont font2;
        font2.setPointSize(20);
        lblCelcius->setFont(font2);

        verticalLayout->addWidget(lblCelcius);


        horizontalLayout_5->addLayout(verticalLayout);

        countdownLabel = new QLabel(groupBox);
        countdownLabel->setObjectName("countdownLabel");
        countdownLabel->setEnabled(true);
        countdownLabel->setGeometry(QRect(470, 180, 91, 16));

        verticalLayout_3->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

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
        label->setText(QCoreApplication::translate("MainWindow", "Country Code ", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Zip Code", nullptr));
        btnGo->setText(QCoreApplication::translate("MainWindow", "Go", nullptr));
        btnMoreDetails->setText(QCoreApplication::translate("MainWindow", "More Details..", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "CURRENT WEATHER", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "City", nullptr));
        lblCity->setText(QCoreApplication::translate("MainWindow", "City Name", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Country", nullptr));
        lblCountryName->setText(QCoreApplication::translate("MainWindow", "Country Name", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Humidity", nullptr));
        lblHumidity->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "Wind", nullptr));
        lblWind->setText(QString());
        lblDescription->setText(QCoreApplication::translate("MainWindow", "Weather Description", nullptr));
        lblWeatherLogo->setText(QCoreApplication::translate("MainWindow", "Weather Logo", nullptr));
        lblRealFeel_2->setText(QCoreApplication::translate("MainWindow", "Real Feel", nullptr));
        lblRealFeel->setText(QCoreApplication::translate("MainWindow", "RealFeel", nullptr));
        lbltemprature->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "o", nullptr));
        lblCelcius->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        countdownLabel->setText(QCoreApplication::translate("MainWindow", "countdown:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
