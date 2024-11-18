#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QSettings>
#include <QMessageBox>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    loadApiKey();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::loadApiKey()
{
    QSettings settings("YourCompany", "YourApp");
    QString apiKey = settings.value("apiKey", "").toString();
    ui->txtApiKey->setText(apiKey);
}

void SettingsDialog::saveApiKey(const QString &apiKey)
{
    QSettings settings("YourCompany", "YourApp");
    settings.setValue("apiKey", apiKey);
}

void SettingsDialog::on_saveButton_clicked()
{
    QString apiKey = ui->txtApiKey->text().trimmed();

    if (apiKey.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "API 密钥不能为空！");
        return;
    }

    saveApiKey(apiKey);
    QMessageBox::information(this, "保存成功", "API 密钥已保存。");
    accept(); // 关闭对话框
}
