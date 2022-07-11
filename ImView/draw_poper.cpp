#include "draw_poper.h"
#include "ui_draw_poper.h"

#include <QFileInfo>
#include <QIcon>

//double y_0,y_1,y_2,y_3,y_4,y_5,y_6,y_7,y_8,y_9,y_10,y_11;

draw_poper::draw_poper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::draw_poper)
{
    ui->setupUi(this);
    ui->webEngineView_2->hide();
    //ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/rad_var/rad_var_2.html").absoluteFilePath()));
    //ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));

//    ui->tableWidget->setRowCount(8);
//    ui->tableWidget->setColumnCount(3);
//    QStringList name;
//    name << " № " << "Сигнал" << "Величина";
//    ui->tableWidget->setHorizontalHeaderLabels(name);
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
//    ui->tableWidget->verticalHeader()->setVisible(false);
//    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
//    ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
//    ui->tableWidget->setColumnWidth(0, 100);
//    ui->tableWidget->setColumnWidth(1, 400);

//    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
//    {
//        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
//        {
//            ui->tableWidget->setItem(row, column, new QTableWidgetItem());

//        }
//    }

//    for (int i=0; i<8; i++)
//    {
//        if (ui->tableWidget->item(i, 0) != 0)
//        {
//            ui->tableWidget->item(i, 0)->setText(QString("%1").arg(i+1));
//            ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
//        }
//    }

//    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Ротор слева, °C"));
//    ui->tableWidget->setItem(1, 1, new QTableWidgetItem("Ротор справа, °C"));
//    ui->tableWidget->setItem(2, 1, new QTableWidgetItem("Станина слева, °C"));
//    ui->tableWidget->setItem(3, 1, new QTableWidgetItem("Станина справа, °C"));
//    ui->tableWidget->setItem(4, 1, new QTableWidgetItem("Вал, °C"));
//    ui->tableWidget->setItem(5, 1, new QTableWidgetItem("Клеммная коробка, °C"));
//    ui->tableWidget->setItem(6, 1, new QTableWidgetItem("Магнитопровод статора слева, °C"));
//    ui->tableWidget->setItem(7, 1, new QTableWidgetItem("Магнитопровод статора справа, °C"));

//    QPalette p99=ui->tableWidget->palette();
//    p99.setColor(QPalette::Base, QColor(225, 255, 255));
//    p99.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
//    ui->tableWidget->setPalette(p99);
}

draw_poper::~draw_poper()
{
    delete ui;
}
