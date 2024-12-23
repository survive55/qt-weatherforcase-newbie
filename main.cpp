#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFont font("Segoe UI", 10);
    app.setFont(font);


    QString styleSheet = R"(
        QMessageBox {
            background-color: #2D2D30;
            color: white;
        }
        QMessageBox QLabel {
            color: white;
        }
        QMessageBox QPushButton {
            background-color: #007ACC;
            color: white;
            border: none;
            padding: 6px 12px;
            border-radius: 4px;
            min-width: 80px;
        }
        QMessageBox QPushButton:hover {
            background-color: #005F9E;
        }
        QMessageBox QPushButton:pressed {
            background-color: #003F6E;
        }
    )";

    app.setStyleSheet(styleSheet);

    MainWindow window;
    window.show();
    return app.exec();
}
