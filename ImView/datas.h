#ifndef DATAS_H
#define DATAS_H

#include <QWidget>
#include "QtSql"
#include "QSqlDatabase"
#include "ischodn_dannie.h"
#include <QButtonGroup>
#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class datas;
}

class datas : public QWidget
{
    Q_OBJECT

public:
    explicit datas(QWidget *parent = nullptr);
    ~datas();

public slots:
    void on_enterDannie_clicked();

    void on_deleteDannie_clicked();

private slots:
    void on_pushButton_5_clicked();

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_pushButton_clicked();

    void on_radioButton_5_toggled(bool checked);

    void on_saveDannie_clicked();

    void on_radioButton_4_toggled(bool checked);

public:
    Ui::datas *ui;
    void zapis();
    void table();
    MainWindow *wf;
private:
    QSqlDatabase sdb;
    QString dataSourceFilename;
    ischodn_dannie *isdn;

};

#endif // DATAS_H
