#include "tepl_dannie.h"
#include "customhelpdelegate.h"
#include "ui_tepl_dannie.h"

Tepl_dannie::Tepl_dannie(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tepl_dannie)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(76);
    ui->tableWidget->setColumnCount(2);
    QStringList name;
    name << "Свойство" << "Значение" ;
    ui->tableWidget->setHorizontalHeaderLabels(name);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(true);
    ui->tableWidget->setColumnWidth(1, 100);
    ui->tableWidget->setColumnWidth(2, 100);
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
           // ui->tableWidget->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QPalette p=ui->tableWidget->palette();
    p.setColor(QPalette::Base, QColor(255, 255, 191));
    p.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget->setPalette(p);

    //Сохдание и заполнение таблицы проводимостей
    ui->tableWidget_2->setRowCount(76);
    ui->tableWidget_2->setColumnCount(3);
    QStringList name_2;
    name_2 << "Свойство" << "Обозначение" << "Значение";
    ui->tableWidget_2->setHorizontalHeaderLabels(name_2);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_2->verticalHeader()->setVisible(true);
    ui->tableWidget_2->setColumnWidth(1, 100);
    for(int row = 0; row<ui->tableWidget_2->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_2->columnCount(); column++)
        {
            ui->tableWidget_2->setItem(row, column, new QTableWidgetItem());
        }
    }

    ui->tableWidget_2->item(0,0)->setText("Тепловая проводимость между станиной и окружающей средой со стороны выступающей части вала");
    ui->tableWidget_2->item(1,0)->setText("Тепловая проводимость между подшипниковым щитом и воздушной зоной со стороны выступающей части вала");
    ui->tableWidget_2->item(2,0)->setText("Тепловая проводимость между обмоткой статора и воздушной зоной со стороны выступающей части вала");
    ui->tableWidget_2->item(3,0)->setText("Тепловая проводимость между обмоткой ротора и воздушной зоной со стороны выступающей части вала");
    ui->tableWidget_2->item(4,0)->setText("Тепловая проводимость между станиной и окружающей средой в зоне клеммной коробки");
    ui->tableWidget_2->item(5,0)->setText("Тепловая проводимость между обмоткой статора и станиной в зоне клеммной коробки");
    ui->tableWidget_2->item(6,0)->setText("Тепловая проводимость между обмоткой ротора и обмоткой статора в зоне клеммной коробки");
    ui->tableWidget_2->item(7,0)->setText("Тепловая проводимость между обмоткой статора и воздушной зоной со стороны вентиляторного узла");
    ui->tableWidget_2->item(8,0)->setText("Тепловая проводимость между обмоткой ротора и воздушной зоной со стороны вентиляторного узла");
    ui->tableWidget_2->item(9,0)->setText("Тепловая проводимость между обмоткой ротора и воздушной зоной со стороны вентиляторного узла");
    ui->tableWidget_2->item(10,0)->setText("Тепловая проводимость между обмоткой ротора и вспомогательным ротором");
    ui->tableWidget_2->item(11,0)->setText("Тепловая проводимость между клеммной коробкой и воздушной зоной со стороны вентиляторного узла");
    ui->tableWidget_2->item(12,0)->setText("Тепловая проводимость между вентиляторным узлом и воздушной зоной со стороны вентиляторного узла");
    ui->tableWidget_2->item(13,0)->setText("Тепловая проводимость между вентиляторным узлом и окружающей средой");
    ui->tableWidget_2->item(14,0)->setText("Тепловая проводимость между вспомогательным ротором и вентиляторным узлом");

    ui->tableWidget_2->item(0,1)->setText("λ₁₀");
    ui->tableWidget_2->item(1,1)->setText("λ₂₁");
    ui->tableWidget_2->item(2,1)->setText("λс₂");
    ui->tableWidget_2->item(3,1)->setText("λₚ₅");
    ui->tableWidget_2->item(4,1)->setText("λ₃₀");
    ui->tableWidget_2->item(5,1)->setText("λс₃");
    ui->tableWidget_2->item(6,1)->setText("λₚс");
    ui->tableWidget_2->item(7,1)->setText("λ₃ₖ");
    ui->tableWidget_2->item(8,1)->setText("λс₄");
    ui->tableWidget_2->item(9,1)->setText("λₚв");
    ui->tableWidget_2->item(10,1)->setText("λₚ₅");
    ui->tableWidget_2->item(11,1)->setText("λₖ₀");
    ui->tableWidget_2->item(12,1)->setText("λ₄₅");
    ui->tableWidget_2->item(13,1)->setText("λ₅₀");
    ui->tableWidget_2->item(14,1)->setText("λв₅");

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_2->rowCount(); row++)
    {
        if (ui->tableWidget_2->item(row,0) != 0)
        {
            ui->tableWidget_2->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_2->item(row,1) != 0)
        {
            ui->tableWidget_2->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->tableWidget_2->item(row,1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_2->item(row,2) != 0)
        {
            ui->tableWidget_2->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_2->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QPalette p2=ui->tableWidget_2->palette();
    p2.setColor(QPalette::Base, QColor(255, 255, 191));
    p2.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_2->setPalette(p2);

    //Сохдание и заполнение таблицы проводимостей
    ui->tableWidget_3->setRowCount(10);
    ui->tableWidget_3->setColumnCount(3);
    QStringList name_3;
    name_3 << "Свойство" << "Обозначение" << "Значение";
    ui->tableWidget_3->setHorizontalHeaderLabels(name_3);
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableWidget_3->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_3->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_3->verticalHeader()->setVisible(true);
    ui->tableWidget_3->setColumnWidth(1, 100);
    for(int row = 0; row<ui->tableWidget_3->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_3->columnCount(); column++)
        {
            ui->tableWidget_3->setItem(row, column, new QTableWidgetItem());
        }
    }

    ui->tableWidget_3->item(0,0)->setText("Температура окружающей среды");
    ui->tableWidget_3->item(1,0)->setText("Температура подшипникового щита со стороны выступающего конца вала");
    ui->tableWidget_3->item(2,0)->setText("Температура воздуха в закрытой зоне внутри двигателя со стороны выступающего конца вала");
    ui->tableWidget_3->item(3,0)->setText("Температура станины");
    ui->tableWidget_3->item(4,0)->setText("Температура воздуха в закрытой зоне внутри двигателя со стороны вентиляторного узла");
    ui->tableWidget_3->item(5,0)->setText("Температура воздуха в зоне вентиляторного узла");
    ui->tableWidget_3->item(6,0)->setText("Температура в клеммной коробке");
    ui->tableWidget_3->item(7,0)->setText("Температура в обмотке статора");
    ui->tableWidget_3->item(8,0)->setText("Температура в обмотке ротора");
    ui->tableWidget_3->item(9,0)->setText("Температура в обмотке вспомогательного ротора");

    ui->tableWidget_3->item(0,1)->setText("θ₀");
    ui->tableWidget_3->item(1,1)->setText("θ₁");
    ui->tableWidget_3->item(2,1)->setText("θ₂");
    ui->tableWidget_3->item(3,1)->setText("θ₃");
    ui->tableWidget_3->item(4,1)->setText("θ₄");
    ui->tableWidget_3->item(5,1)->setText("θ₅");
    ui->tableWidget_3->item(6,1)->setText("θₖ");
    ui->tableWidget_3->item(7,1)->setText("θс");
    ui->tableWidget_3->item(8,1)->setText("θₚ");
    ui->tableWidget_3->item(9,1)->setText("θв");


    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_3->rowCount(); row++)
    {
        if (ui->tableWidget_3->item(row,0) != 0)
        {
            ui->tableWidget_3->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_3->item(row,1) != 0)
        {
            ui->tableWidget_3->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->tableWidget_3->item(row,1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_3->item(row,2) != 0)
        {
            ui->tableWidget_3->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->tableWidget_3->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QPalette p3=ui->tableWidget_3->palette();
    p3.setColor(QPalette::Base, QColor(255, 255, 191));
    p3.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_3->setPalette(p3);


    //Сохдание и заполнение таблицы проводимостей
    ui->tableWidget_4->setRowCount(10);
    ui->tableWidget_4->setColumnCount(3);
    QStringList name_4;
    name_4 << "Свойство" << "Обозначение" << "Значение";
    ui->tableWidget_4->setHorizontalHeaderLabels(name_4);
    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableWidget_4->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_4->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_4->verticalHeader()->setVisible(true);
    ui->tableWidget_4->setColumnWidth(1, 100);

    for(int row = 0; row<ui->tableWidget_4->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_4->columnCount(); column++)
        {
            ui->tableWidget_4->setItem(row, column, new QTableWidgetItem());
        }
    }

    ui->tableWidget_4->item(0,0)->setText("Температура окружающей среды");
    ui->tableWidget_4->item(1,0)->setText("Температура подшипникового щита со стороны выступающего конца вала");
    ui->tableWidget_4->item(2,0)->setText("Температура воздуха в закрытой зоне внутри двигателя со стороны выступающего конца вала");
    ui->tableWidget_4->item(3,0)->setText("Температура станины");
    ui->tableWidget_4->item(4,0)->setText("Температура воздуха в закрытой зоне внутри двигателя со стороны вентиляторного узла");
    ui->tableWidget_4->item(5,0)->setText("Температура воздуха в зоне вентиляторного узла");
    ui->tableWidget_4->item(6,0)->setText("Температура в клеммной коробке");
    ui->tableWidget_4->item(7,0)->setText("Температура в обмотке статора");
    ui->tableWidget_4->item(8,0)->setText("Температура в обмотке ротора");
    ui->tableWidget_4->item(9,0)->setText("Температура в обмотке вспомогательного ротора");

    ui->tableWidget_4->item(0,1)->setText("C₀");
    ui->tableWidget_4->item(1,1)->setText("C₁");
    ui->tableWidget_4->item(2,1)->setText("C₂");
    ui->tableWidget_4->item(3,1)->setText("C₃");
    ui->tableWidget_4->item(4,1)->setText("C₄");
    ui->tableWidget_4->item(5,1)->setText("C₅");
    ui->tableWidget_4->item(6,1)->setText("Cₖ");
    ui->tableWidget_4->item(7,1)->setText("Cс");
    ui->tableWidget_4->item(8,1)->setText("Cₚ");
    ui->tableWidget_4->item(9,1)->setText("Cв");

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_4->rowCount(); row++)
    {
        if (ui->tableWidget_4->item(row,0) != 0)
        {
            ui->tableWidget_4->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_4->item(row,1) != 0)
        {
            ui->tableWidget_4->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->tableWidget_4->item(row,1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_4->item(row,2) != 0)
        {
            ui->tableWidget_4->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->tableWidget_4->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QPalette p4=ui->tableWidget_4->palette();
    p4.setColor(QPalette::Base, QColor(255, 255, 191));
    p4.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_4->setPalette(p4);

    CustomHelpDelegate* customHelpDelegate = new CustomHelpDelegate(this); //создание делегата для создания комбобоксов
    ui->tableWidget->setItemDelegateForColumn(0, customHelpDelegate);
    ui->tableWidget_2->setItemDelegateForColumn(0, customHelpDelegate);
    ui->tableWidget_3->setItemDelegateForColumn(0, customHelpDelegate);
    ui->tableWidget_4->setItemDelegateForColumn(0, customHelpDelegate);
}

Tepl_dannie::~Tepl_dannie()
{
    delete ui;
}

