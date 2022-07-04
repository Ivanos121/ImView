#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "kalibr.h"
#include <QTimer>
#include <QElapsedTimer>
#include <QWebEngineView>
#include <QTreeWidgetItem>
#include <QStandardItem>
#include "itogs.h"

#include "ui_about_dialog.h"
#include "ui_settings.h"
#include "pushbuttondelegate.h"
#include "ui_graph_Settings.h"

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

//class Graph_Settings : public QDialog
//{
//    Q_OBJECT

//public:
//    explicit Graph_Settings(QWidget *parent = nullptr);

//    QVector<QColor> dataLineColors;

//private slots:
//    void on_pushButton_clicked();
//   // void setcolorincell(int row, int column);

//private:
//    Ui::graph_Settings *ui;
//};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent (QCloseEvent *event);
    void LoadProject(QString str);
    QVector<QColor> dataLineColors;

private slots:
    void on_actionabout_triggered();
    void on_actionExit_triggered();
    void on_actionhelp_triggered();
    void titleChanged(const QString &title);
    void on_action_16_triggered();
    void on_action_12_triggered();
    void on_action_17_triggered();
    void on_action_19_triggered();
    void on_action_5_triggered();
    void on_action_9_triggered();
    void on_action_20_triggered();
    void on_action_21_triggered();
    void on_tabWidget_currentChanged(int);
    void on_action_22_triggered();
    void on_action_23_triggered();
    void on_action_15_triggered();
    void setcolorincell(int row, int column);
    void onButtonClicked();
    void onButtonClicked2();
    void on_action_24_triggered();
    void on_action_25_triggered();

    void modelItemChangedSlot(QStandardItem *item);
    void modelItemChangedSlot_2(QStandardItem *item);
    void modelItemChangedSlot_3(QStandardItem *item);
    void modelItemChangedSlot_4(QStandardItem *item);
    void projectFileSelectedSlot(QString projectFile);
    void projectFileSelectedSlot_2(QString projectFile_2);
    void projectFileSelectedSlot_3(QString projectFile_3);
    void projectFileSelectedSlot_4(QString projectFile_4);
    void projectFileSelectedSlot_5(QString projectFile_5);
    void projectFileSelectedSlot_6(QString projectFile_6);
    void on_SaveProgectToFile_clicked();
    void on_item_itemSelectionChanged();
    void on_pushButton_5_clicked(bool checked);
    void on_LoadProgect_clicked();

public:
    Ui::MainWindow *ui;
    AboutDialog *rsc;
    Kalibr *kalibr;
    Settings *rsc2;
//    Graph_Settings *graph_Settings;
    QString dataSourceFilename;
QString dirName;


    QWebEngineView * view;

    QTreeWidgetItem *treeItem, *child3, *child, *child2;
    QTreeWidgetItem *currentItem;
    int currentColumn;

    QStandardItem *item1,  *item2,  *item3,  *item4,  *item5,  *item6,  *item7,  *item8;
    QStandardItem *item9,  *item10, *item11, *item12, *item13, *item14, *item15, *item16;
    QStandardItem *item17, *item18, *item19, *item20, *item21, *item22, *item23, *item24;
    QStandardItem *item25, *item26, *item27, *item28, *item29, *item30, *item31, *item32;
    QStandardItem *item33, *item34, *item35, *item36, *item37, *item38, *item39, *item40;
    QStandardItem *item41, *item42, *item43, *item44, *item45, *item46, *item47, *item48;
    QStandardItem *item49, *item50, *item51, *item52, *item53, *item54, *item55, *item56;
    QStandardItem *item57, *item58, *item59, *item60, *item61, *item62, *item63, *item64;
    QStandardItem *item65, *item66, *item67, *item68, *item69, *item70, *item71, *item72;
    QStandardItem *item73, *item74, *item75, *item76, *item77, *item78, *item79, *item80;
    QStandardItem *item81, *item82, *item83, *item84, *item85, *item86, *item87, *item88;
    QStandardItem *item89, *item90, *item91, *item92, *item93, *item94, *item95, *item96;
    QStandardItem *item97, *item98, *item99, *item100, *item101, *item102, *item103, *item104;
    QStandardItem *item105, *item106, *item107, *item108, *item109, *item110, *item111, *item112;
    QStandardItem *item113, *item114, *item115, *item116, *item117, *item118, *item119, *item120;
};

#endif // MAINWINDOW_H
