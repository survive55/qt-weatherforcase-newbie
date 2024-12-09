#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFont font("Segoe UI", 10);
    app.setFont(font);

    // 设置全局样式表
    QString styleSheet = R"(
    QMessageBox QLabel {
        color: black;
    }
    )";
    app.setStyleSheet(styleSheet);

    MainWindow window;
    window.show();
    return app.exec();
}
