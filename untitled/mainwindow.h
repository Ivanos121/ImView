#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "kalibr.h"
#include <QTimer>
#include <QElapsedTimer>
#include <QWebEngineView>
#include "itogs.h"

#include "ui_about_dialog.h"
#include "ui_settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);

private slots:
    void on_pushButton_clicked();

private:
    Ui::aboutDialog *ui;
};

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_listWidget_itemSelectionChanged();

private:
    Ui::settings *ui;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionabout_triggered();

    void on_actionExit_triggered();

    void on_action_10_triggered();

    void on_actionhelp_triggered();

    void titleChanged(const QString &title);

    void on_action_16_triggered();

    void on_action_12_triggered();

    void on_action_17_triggered();

    void on_action_19_triggered();

    void on_action_18_triggered();

    void on_action_5_triggered();

    void on_action_9_triggered();

    void on_action_20_triggered();

    void on_action_21_triggered();

    void on_tabWidget_currentChanged(int);

    void on_action_22_triggered();
    void on_action_23_triggered();

    void on_action_15_triggered();

public:
    Ui::MainWindow *ui;
    AboutDialog *rsc;
    Kalibr *kalibr;
    Settings *rsc2;

    QWebEngineView * view;
};

#endif // MAINWINDOW_H
