#include "tepl_dannie.h"
#include "customhelpdelegate.h"
#include "ui_tepl_dannie.h"

Tepl_dannie::Tepl_dannie(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tepl_dannie)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(76);
    ui->tableWidget->setColumnCount(6);
    QStringList name;
    name << "Свойство" << "Значение" << "Свойство" << "Значение"<< "Свойство" << "Значение";
    ui->tableWidget->setHorizontalHeaderLabels(name);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(true);
    ui->tableWidget->resizeColumnsToContents();
    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
        {
            ui->tableWidget->setItem(row, column, new QTableWidgetItem());
        }
    }
    ui->tableWidget->item(0,0)->setText("Синхронная частота вращения, об/мин");
    ui->tableWidget->item(1,0)->setText("Количеcтво пар полюсов");
    ui->tableWidget->item(2,0)->setText("Высота оси вращения, м");
    ui->tableWidget->item(3,0)->setText("Диаметр станины у основания ребер, м");
    ui->tableWidget->item(4,0)->setText("Длина свисающей части станины со стороны привода, м");
    ui->tableWidget->item(5,0)->setText("Длина свисающей части станины со стороны вентилятора, м");
    ui->tableWidget->item(6,0)->setText("Зазор между диффузором и механическим щитом в месте крепления, м");
    ui->tableWidget->item(7,0)->setText("Количество ребер станины");
    ui->tableWidget->item(8,0)->setText("Высота ребра станины, м");
    ui->tableWidget->item(9,0)->setText("Толщина ребра станины, м");
    ui->tableWidget->item(10,0)->setText("Внешний диаметр вентилятора, м");

    ui->tableWidget->item(11,0)->setText("Внешний диаметр сердечника статора, м");
    ui->tableWidget->item(12,0)->setText("Внутренний диаметр сердечника статора, м");
    ui->tableWidget->item(13,0)->setText("Длина паза, м");
    ui->tableWidget->item(14,0)->setText("Число пазов статора");
    ui->tableWidget->item(15,0)->setText("Коэффициент шихтовки");
    ui->tableWidget->item(16,0)->setText("Большая ширина паза, м");
    ui->tableWidget->item(17,0)->setText("Меньшая ширина паза, м");
    ui->tableWidget->item(18,0)->setText("Высота паза, м");
    ui->tableWidget->item(19,0)->setText("Ширина шлица, м");
    ui->tableWidget->item(20,0)->setText("Высота зубца, м");

    ui->tableWidget->item(21,0)->setText("Ширина зубца, м");
    ui->tableWidget->item(22,0)->setText("Количество витков в обмотке статора");
    ui->tableWidget->item(23,0)->setText("Число параллельных ветвей");
    ui->tableWidget->item(24,0)->setText("Средняя длина витка обмотки, м");
    ui->tableWidget->item(25,0)->setText("Длина вылета лобовой части обмотки, м");
    ui->tableWidget->item(26,0)->setText("Коэффициент пропитки обмотки");
    ui->tableWidget->item(27,0)->setText("Толщина окраски обмотки в лобовой части, м");
    ui->tableWidget->item(28,0)->setText("Толщина пазовой изоляции, м");
    ui->tableWidget->item(29,0)->setText("Внешний диаметр ротора, м");
    ui->tableWidget->item(30,0)->setText("Число пазов ротора");

    ui->tableWidget->item(31,0)->setText("Ширина короткозамыкающего кольца, м");
    ui->tableWidget->item(32,0)->setText("Высота короткозамыкающего кольца, м");
    ui->tableWidget->item(33,0)->setText("Ширина лопатки ротора, м");
    ui->tableWidget->item(34,0)->setText("Высота лопатки ротора, м");
    ui->tableWidget->item(35,0)->setText("Количество лопаток ротора");
    ui->tableWidget->item(36,0)->setText("Коэффициент качества лопатки");
    ui->tableWidget->item(37,0)->setText("Толщина воздушного зазора между статором и ротором, м");
    ui->tableWidget->item(38,0)->setText("Кинематическая вязкость ротора, м*м/с");
    ui->tableWidget->item(39,0)->setText("Средняя температуры обмотки, 0С");
    ui->tableWidget->item(40,0)->setText("Коэффициент теплопроводности воздуха");

    ui->tableWidget->item(41,0)->setText("Коэффициент теплопроводности меди");
    ui->tableWidget->item(42,0)->setText("Коэффициент теплопроводности алюминия");
    ui->tableWidget->item(43,0)->setText("Коэффициент теплопроводности стали пакета статора");
    ui->tableWidget->item(44,0)->setText("Диаметр провода без изоляции, м^2");
    ui->tableWidget->item(45,0)->setText("Диаметр изолированного провода, м^2");
    ui->tableWidget->item(46,0)->setText("Коэффициент пропитки обмотки");
    ui->tableWidget->item(47,0)->setText("Коэффициент теплопроводности пропиточного состава");
    ui->tableWidget->item(48,0)->setText("Коэффициент теплопроводности изоляции проводников");
    ui->tableWidget->item(49,0)->setText("Внешний диаметр лобовой части, м");
    ui->tableWidget->item(50,0)->setText("Коэффициент теплопроводности окраски обмотки в лобовой части");

    ui->tableWidget->item(51,0)->setText("Коэффициент теплопроводности изоляции проводников");
    ui->tableWidget->item(52,0)->setText("Толщина воздушных прослоек, м");
    ui->tableWidget->item(53,0)->setText("Высота зубца, м");
    ui->tableWidget->item(54,0)->setText("Средняя ширина зубца, м");
    ui->tableWidget->item(55,0)->setText("Диаметр окружности касательной ко дну пазов, м");
    ui->tableWidget->item(56,0)->setText("Большая ширина паза, м");
    ui->tableWidget->item(57,0)->setText("Меньшая ширина паза, м");
    ui->tableWidget->item(58,0)->setText("Высота паза, м");
    ui->tableWidget->item(59,0)->setText("Коэффициент качества лопатки ротора, рассматриваемой как ребро");
    ui->tableWidget->item(60,0)->setText("Шаг ребер станины, м");

    ui->tableWidget->item(61,0)->setText("Число фаз обмотки статора");
    ui->tableWidget->item(62,0)->setText("Количество элементарных проводников");
    ui->tableWidget->item(63,0)->setText("Плотность меди");
    ui->tableWidget->item(64,0)->setText("Удельная теплоемкость меди обмотки статора");
    ui->tableWidget->item(65,0)->setText("Плотность стали");
    ui->tableWidget->item(66,0)->setText("Удельная теплоемкость стали");
    ui->tableWidget->item(67,0)->setText("Удельное сопротивление меди");
    ui->tableWidget->item(68,0)->setText("Полезная мощность, Вт");
    ui->tableWidget->item(69,0)->setText("Напряжение питания, В");
    ui->tableWidget->item(70,0)->setText("Коэффициент полезного действия");

    ui->tableWidget->item(71,0)->setText("Коэффициент мощности");
    ui->tableWidget->item(72,0)->setText("Удельное сопротивление алюминия");
    ui->tableWidget->item(73,0)->setText("Средний диаметр короткозамыкающего кольца");
    ui->tableWidget->item(74,0)->setText("Обмоточный коэффициент обмотки статора");
    ui->tableWidget->item(75,0)->setText("Коэффициент скоса пазов");

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        if (ui->tableWidget->item(row,0) != 0)
        {
            ui->tableWidget->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget->item(row,1) != 0)
        {
            ui->tableWidget->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget->item(row,1)->setTextAlignment(Qt::AlignCenter);            
        }
        if (ui->tableWidget->item(row,2) != 0)
        {
            ui->tableWidget->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget->item(row,3) != 0)
        {
            ui->tableWidget->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget->item(row,3)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget->item(row,4) != 0)
        {
            ui->tableWidget->item(row,4)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget->item(row,5) != 0)
        {
            ui->tableWidget->item(row,5)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget->item(row,5)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QPalette p=ui->tableWidget->palette();
    p.setColor(QPalette::Base, QColor(255, 255, 191));
    p.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget->setPalette(p);

    CustomHelpDelegate* customHelpDelegate = new CustomHelpDelegate(this); //создание делегата для создания комбобоксов
    ui->tableWidget->setItemDelegateForColumn(0, customHelpDelegate);
}

Tepl_dannie::~Tepl_dannie()
{
    delete ui;
}

