HEADERS += \
    mainwindow.h \
    settingsdialog.h \
    weatherwidget.h
    QT +=widgets
QT += network
QT += core gui network
QT += positioning
QT += location

QT += core gui network positioning location
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    weatherforcase.cpp

FORMS += \
    ../../Downloads/mainwindow.ui \
    settingsdialog.ui

DISTFILES +=
