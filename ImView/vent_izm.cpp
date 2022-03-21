#include "vent_izm.h"
#include "ui_vent_izm.h"

#include <QFileInfo>

vent_izm::vent_izm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vent_izm)
{
    ui->setupUi(this);

    ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_var/vent_var.html").absoluteFilePath()));
    ui->tableWidget->setRowCount(12);
    ui->tableWidget->setColumnCount(3);
    QStringList name;
    name << " № " << "Сигнал" << "Величина";
    ui->tableWidget->setHorizontalHeaderLabels(name);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget->setColumnWidth(0, 100);

    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
        {
            ui->tableWidget->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<12; i++)
    {
        if (ui->tableWidget->item(i, 0) != 0)
        {
            ui->tableWidget->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget->setItem(0,  1, new QTableWidgetItem("Станина"));
    ui->tableWidget->setItem(1,  1, new QTableWidgetItem("Подшипниковый узел справа сзади"));
    ui->tableWidget->setItem(2,  1, new QTableWidgetItem("Лобовая часть слева спереди"));
    ui->tableWidget->setItem(3,  1, new QTableWidgetItem("Подшипниковый узел слева спереди"));
    ui->tableWidget->setItem(4,  1, new QTableWidgetItem("Лобовая часть слева спереди"));
    ui->tableWidget->setItem(5,  1, new QTableWidgetItem("Лобовая часть слева сзади"));
    ui->tableWidget->setItem(6,  1, new QTableWidgetItem("Станина"));
    ui->tableWidget->setItem(7,  1, new QTableWidgetItem("Лобовая часть справа спереди"));
    ui->tableWidget->setItem(8,  1, new QTableWidgetItem("Лобовая часть справа сзади"));
    ui->tableWidget->setItem(9,  1, new QTableWidgetItem("Магнитопровод статора"));
    ui->tableWidget->setItem(10, 1, new QTableWidgetItem("Подшипниковый узел справа спереди"));
    ui->tableWidget->setItem(11, 1, new QTableWidgetItem("Подшипниковый узел слева сзади"));

    QPalette p99=ui->tableWidget->palette();
    p99.setColor(QPalette::Base, QColor(225, 255, 255));
    p99.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget->setPalette(p99);

}

vent_izm::~vent_izm()
{
    delete ui;
}
