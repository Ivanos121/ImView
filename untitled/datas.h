#ifndef DATAS_H
#define DATAS_H

#include <QWidget>
#include "QtSql"
#include "QSqlDatabase"
#include <QButtonGroup>

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

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private slots:
    void on_pushButton_5_clicked();

private:
    Ui::datas *ui;
    QSqlDatabase sdb;
    QButtonGroup buttonGroup;
    void table();
    void zapis();
};

#endif // DATAS_H
