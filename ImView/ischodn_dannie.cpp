#include "ischodn_dannie.h"
#include "ui_ischodn_dannie.h"
#include "base.h"
#include "datas.h"
#include "ui_datas.h"
#include "ui_mainwindow.h"

#include <QSqlQuery>

ischodn_dannie::ischodn_dannie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ischodn_dannie)
{
    ui->setupUi(this);

    ui->tableWidget->setRowCount(8);
    ui->tableWidget->setColumnCount(2);
    QStringList name;
    name << "Величина" << "Значение";
    ui->tableWidget->setHorizontalHeaderLabels(name);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setVisible(true);
    //ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
    //ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("марка двигателя:"));
    ui->tableWidget->setItem(1, 0, new QTableWidgetItem("Номинальная мощность двигателя, кВт:"));
    ui->tableWidget->setItem(2, 0, new QTableWidgetItem("Номинальная частота вращения, об/мин:"));
    ui->tableWidget->setItem(3, 0, new QTableWidgetItem("Номинальное напряжение фазы, В"));
    ui->tableWidget->setItem(4, 0, new QTableWidgetItem("Номинальный коэффициент мощности"));
    ui->tableWidget->setItem(5, 0, new QTableWidgetItem("Номинальный коэффициент полезного действия"));
    ui->tableWidget->setItem(6, 0, new QTableWidgetItem("Кратность максимального момента"));
    ui->tableWidget->setItem(7, 0, new QTableWidgetItem("Синхронная частота вращения, об/мин"));

    ui->tableWidget->setItem(0, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(1, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(2, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(3, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(4, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(5, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(6, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(7, 1, new QTableWidgetItem());


//    QPalette p99=ui->tableWidget->palette();
//    p99.setColor(QPalette::Base, QColor(225, 255, 255));
//    p99.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
//    ui->tableWidget->setPalette(p99);
}

ischodn_dannie::~ischodn_dannie()
{
    delete ui;
}

void ischodn_dannie::on_pushButton_2_clicked()
{
    close();
}


void ischodn_dannie::on_pushButton_clicked()
{
    base.name = ui->tableWidget->item(0,2)->text().toDouble();
    base.P_nom = ui->tableWidget->item(1,2)->text().toDouble();
    base.n_nom = ui->tableWidget->item(2,2)->text().toDouble();
    base.U_fnom = ui->tableWidget->item(3,2)->text().toDouble();
    base.cosf_nom = ui->tableWidget->item(4,2)->text().toDouble();
    base.kpd_nom = ui->tableWidget->item(5,2)->text().toDouble();
    base.muk = ui->tableWidget->item(6,2)->text().toDouble();
    base.n_0 = ui->tableWidget->item(7,2)->text().toDouble();

    wf->zapis();
    close();
}

