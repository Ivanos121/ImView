#ifndef SETTINGSCANALS_H
#define SETTINGSCANALS_H

#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class SettingsCanals;
}

class SettingsCanals : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsCanals(QWidget *parent = nullptr);
    ~SettingsCanals();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::SettingsCanals *ui;
};

#endif // SETTINGSCANALS_H
