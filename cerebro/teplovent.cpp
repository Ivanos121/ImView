#include "teplovent.h"
#include "ui_teplovent.h"

teplovent::teplovent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teplovent)
{
    ui->setupUi(this);
    ui->widget->t_max = 10.0;
    ui->widget->U_max = 3.0;
    ui->widget->margin_bottom = 40;
    ui->widget->margin_left = 100;
    ui->widget->reset();
    ui->widget_2->t_max = 0.1;
    ui->widget_2->U_max = 800.0;
    ui->widget_2->margin_bottom = 40;
    ui->widget_2->margin_left = 100;
    ui->widget_2->reset();

    //Заполнений таблицы настроек
//    ui->tableWidget->setRowCount(24);
//    ui->tableWidget->setColumnCount(2);
//    QStringList name;
//    name << "Свойство" << "Значение";
//    ui->tableWidget->setHorizontalHeaderLabels(name);
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
//    ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
//    ui->tableWidget->verticalHeader()->setVisible(false);
//    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Ток фазы А, А"));
//    ui->tableWidget->setItem(1, 0, new QTableWidgetItem("Напряжение фазы А, В"));
//    ui->tableWidget->setItem(2, 0, new QTableWidgetItem("Активная мошность фазы А, Вт"));
//    ui->tableWidget->setItem(3, 0, new QTableWidgetItem("Реактивная мошность фазы А, ВА"));

//    ui->tableWidget_2->setRowCount(24);
//    ui->tableWidget_2->setColumnCount(2);
//    QStringList name2;
//    name2 << "Свойство" << "Значение";
//    ui->tableWidget_2->setHorizontalHeaderLabels(name);
//    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView :: SelectRows);
//    ui->tableWidget_2->setSelectionMode(QAbstractItemView :: SingleSelection);
//    ui->tableWidget_2->verticalHeader()->setVisible(false);
//    ui->tableWidget_2->setItem(0, 0, new QTableWidgetItem("Ток фазы А, А"));
//    ui->tableWidget_2->setItem(1, 0, new QTableWidgetItem("Напряжение фазы А, В"));
//    ui->tableWidget_2->setItem(2, 0, new QTableWidgetItem("Активная мошность фазы А, Вт"));
//    ui->tableWidget_2->setItem(3, 0, new QTableWidgetItem("Реактивная мошность фазы А, ВА"));


}

teplovent::~teplovent()
{
    delete ui;
}
