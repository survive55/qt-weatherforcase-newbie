#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QSettings>
#include <QMessageBox>
#include <QMouseEvent>
#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")
#include <QDir>
#include <QStandardPaths>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);


    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground, false);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    enableBlurBehindWindow();


    QString styleSheet = R"(

    QDialog {
        background-color: #1E1E1E;
        border: 1px solid #444444;
        border-radius: 8px;
    }


    QLabel#labelTitle {
        color: #FFFFFF;
        font-size: 18px;
        font-weight: bold;
        qproperty-alignment: 'AlignHCenter | AlignVCenter';
    }


    QLabel#labelDescription {
        color: #CCCCCC;
        font-size: 12px;
    }


    QLineEdit {
        background-color: #2D2D30;
        color: #FFFFFF;
        border: 1px solid #3C3C3C;
        border-radius: 4px;
        padding: 6px;
    }
    QLineEdit:focus {
        border: 1px solid #007ACC;
    }

    QPushButton {
        background-color: #007ACC;
        color: #FFFFFF;
        border: none;
        border-radius: 4px;
        padding: 8px 16px;
        font-size: 14px;
    }
    QPushButton:hover {
        background-color: #005F9E;
    }
    QPushButton:pressed {
        background-color: #003F6E;
    }


    QPushButton#btnToggleVisibility {
        background-color: transparent;
        color: #CCCCCC;
        border: none;
        font-size: 14px;
    }
    QPushButton#btnToggleVisibility:hover {
        color: #FFFFFF;
    }
)";
    setStyleSheet(styleSheet);


    loadApiKey();



    connect(ui->btnToggleVisibility, &QPushButton::clicked, this, &SettingsDialog::toggleApiKeyVisibility);

}

void SettingsDialog::enableBlurBehindWindow()
{
    HWND hWnd = reinterpret_cast<HWND>(winId());
    DWM_BLURBEHIND bb = {0};
    bb.dwFlags = DWM_BB_ENABLE;
    bb.fEnable = TRUE;
    bb.hRgnBlur = NULL;
    DwmEnableBlurBehindWindow(hWnd, &bb);
}

void SettingsDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragging = true;
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void SettingsDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging && (event->buttons() & Qt::LeftButton))
    {
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}
void SettingsDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragging = false;
        event->accept();
    }
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::loadApiKey()
{
    QSettings settings("YourCompany", "YourApp");
    QString apiKey = settings.value("apiKey", "").toString();
    weatherApiKey = settings.value("weatherApiKey", "").toString();
    ui->txtApiKey->setText(apiKey);
    ui->txtWeatherApiKey->setText(weatherApiKey);

}

void SettingsDialog::saveApiKey(const QString &apiKey)
{
    QSettings settings("YourCompany", "YourApp");
    settings.setValue("apiKey", apiKey);
    settings.setValue("weatherApiKey", weatherApiKey);

}

void SettingsDialog::on_saveButton_clicked()
{
    QString apiKey = ui->txtApiKey->text().trimmed();
    weatherApiKey = ui->txtWeatherApiKey->text().trimmed();
    if (apiKey.isEmpty()) {
        QMessageBox::warning(this, "input error", "API key cannot be null");
        return;
    }

    saveApiKey(apiKey);
    QMessageBox::information(this, "Save Successful", "The API key is saved.");
    accept();
}

void SettingsDialog::toggleApiKeyVisibility()
{
    bool isPasswordMode = ui->txtApiKey->echoMode() == QLineEdit::Password;

    QLineEdit::EchoMode newEchoMode = isPasswordMode ? QLineEdit::Normal : QLineEdit::Password;
    ui->txtApiKey->setEchoMode(newEchoMode);
    ui->txtWeatherApiKey->setEchoMode(newEchoMode);

    ui->btnToggleVisibility->setText(isPasswordMode ? "🙈" : "👁");
}
