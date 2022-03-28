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
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

private slots:
    void on_pushButton_5_clicked();

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_addRow_clicked();

    void on_remdRow_clicked();

    void onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight);

    void on_pushButton_clicked();

public:
    Ui::datas *ui;
    void zapis();
private:
    QSqlDatabase sdb;
    QString dataSourceFilename;
    ischodn_dannie *isdn;
    void table();
};

#endif // DATAS_H
