#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QPoint>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void on_saveButton_clicked();
    void toggleApiKeyVisibility();

private:
    Ui::SettingsDialog *ui;
    void loadApiKey();
    void saveApiKey(const QString &apiKey);
    void enableBlurBehindWindow();
    QString apiKey;
QString weatherApiKey;
    bool m_dragging = false;
    QPoint m_dragPosition;
};

#endif // SETTINGSDIALOG_H
