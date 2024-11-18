#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

private slots:
    void on_saveButton_clicked();

private:
    Ui::SettingsDialog *ui;
    void loadApiKey();
    void saveApiKey(const QString &apiKey);
};

#endif // SETTINGSDIALOG_H
