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

    QPalette p3=ui->tableWidget->palette();
    p3.setColor(QPalette::Base, QColor(255, 255, 191));
    p3.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget->setPalette(p3);
    connect(ui->tableWidget, &QTableWidget::cellChanged, this, &Tepl_dannie::on_tableWidget_cellChanged);

    //Сохдание и заполнение таблицы проводимостей
    ui->tableWidget_2->setRowCount(76);
    ui->tableWidget_2->setColumnCount(2);
    QStringList name_2;
    name_2 << "Свойство" << "Значение";
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

    ui->tableWidget_2->item(0,0)->setText("Общая тепловая проводимость между сердечником статора и станиной");
    ui->tableWidget_2->item(1,0)->setText("Количеcтво пар полюсов");
    ui->tableWidget_2->item(2,0)->setText("Высота оси вращения, м");
    ui->tableWidget_2->item(3,0)->setText("Диаметр станины у основания ребер, м");
    ui->tableWidget_2->item(4,0)->setText("Длина свисающей части станины со стороны привода, м");
    ui->tableWidget_2->item(5,0)->setText("Длина свисающей части станины со стороны вентилятора, м");
    ui->tableWidget_2->item(6,0)->setText("Зазор между диффузором и механическим щитом в месте крепления, м");
    ui->tableWidget_2->item(7,0)->setText("Количество ребер станины");
    ui->tableWidget_2->item(8,0)->setText("Высота ребра станины, м");
    ui->tableWidget_2->item(9,0)->setText("Толщина ребра станины, м");
    ui->tableWidget_2->item(10,0)->setText("Внешний диаметр вентилятора, м");

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
    }

    QPalette p5=ui->tableWidget_2->palette();
    p5.setColor(QPalette::Base, QColor(255, 255, 191));
    p5.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_2->setPalette(p5);

    //Сохдание и заполнение таблицы проводимостей
    ui->tableWidget_3->setRowCount(76);
    ui->tableWidget_3->setColumnCount(2);
    QStringList name_3;
    name_3 << "Свойство" << "Значение";
    ui->tableWidget_3->setHorizontalHeaderLabels(name_2);
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
    }

    QPalette p4=ui->tableWidget_3->palette();
    p4.setColor(QPalette::Base, QColor(255, 255, 191));
    p4.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_3->setPalette(p4);


    //Сохдание и заполнение таблицы проводимостей
    ui->tableWidget_4->setRowCount(16);
    ui->tableWidget_4->setColumnCount(2);
    QStringList name_4;
    name_4 << "Свойство" << "Значение";
    ui->tableWidget_4->setHorizontalHeaderLabels(name_2);
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
    }

    QPalette p55=ui->tableWidget_4->palette();
    p55.setColor(QPalette::Base, QColor(255, 255, 191));
    p55.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_4->setPalette(p55);

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

void Tepl_dannie::on_tableWidget_cellChanged(int row, int column)
{
    if ((column == 1) || (column == 2))
    {
        double p=ui->tableWidget->item(row,1)->text().toDouble();
        if (ui->tableWidget->item(row,2) != 0)
        ui->tableWidget->item(row,2)->setText(QString("%1").arg(p));

        switch(row)
        {
            case 0:
                base_tepl.n0=p;
            break;

            case 1:
                base_tepl.pn=p;
            break;

            case 2:
                base_tepl.pn=p;
            break;

            case 3:
                base_tepl.h=p;
            break;

            case 4:
                base_tepl.D_c=p;
            break;

            case 5:
                base_tepl.l_sv_pr=p;
            break;

            case 6:
                base_tepl.l_cvv=p;
            break;

            case 7:
                base_tepl.sig_pr=p;
            break;

            case 8:
                base_tepl.z_c=p;
            break;

            case 9:
                base_tepl.h_c=p;
            break;

            case 10:
                base_tepl.sig_p=p;
            break;

            case 11:
                base_tepl.D_vent=p;
            break;

            case 12:
                base_tepl.D_a=p;
            break;

            case 13:
                base_tepl.D=p;
            break;

            case 14:
                base_tepl.l_p=p;
            break;

            case 15:
                base_tepl.Z_1=p;
            break;

            case 16:
                base_tepl.k_sh=p;
            break;

            case 17:
                base_tepl.b1=p;
            break;

            case 18:
                base_tepl.b2=p;
            break;

            case 19:
                base_tepl.h_p=p;
            break;

            case 20:
                base_tepl.k_z=p;
            break;

            case 21:
                base_tepl.h_sl1=p;
            break;

            case 22:
                base_tepl.b_sl1=p;
            break;

            case 23:
                base_tepl.h_z1=p;
            break;

            case 24:
                base_tepl.b_z=p;
            break;

            case 25:
                base_tepl.w_i=p;
            break;

            case 26:
                base_tepl.a=p;
            break;

            case 27:
                base_tepl.l_sr=p;
            break;

            case 28:
                base_tepl.l_lr=p;
            break;

            case 29:
                base_tepl.k_p=p;
            break;

            case 30:
                base_tepl.sig_okr=p;
            break;

            case 31:
                base_tepl.sig_ip=p;
            break;

            case 32:
                base_tepl.D_rot=p;
            break;

            case 33:
                base_tepl.Z_2=p;
            break;

            case 34:
                base_tepl.b_k=p;
            break;

            case 35:
                base_tepl.a_k=p;
            break;

            case 36:
                base_tepl.a_l=p;
            break;

            case 37:
                base_tepl.b_l=p;
            break;

            case 38:
                base_tepl.z_l=p;
            break;

            case 39:
                base_tepl.n_l=p;
            break;

            case 40:
                base_tepl.sig=p;
            break;

            case 41:
                base_tepl.nu=p;
            break;

            case 42:
                base_tepl.t_cp=p;
            break;

            case 43:
                base_tepl.lb_b=p;
            break;

            case 44:
                base_tepl.lb_m=p;
            break;

            case 45:
                base_tepl.lb_a=p;
            break;

            case 46:
                base_tepl.lb_c=p;
            break;

            case 47:
                base_tepl.d_b_iz=p;
            break;

            case 48:
                base_tepl.d_iz=p;
            break;

            case 49:
                base_tepl.k_pr=p;
            break;

            case 50:
                base_tepl.lb_p=p;
            break;

            case 51:
                base_tepl.lp_iz=p;
            break;

            case 52:
                base_tepl.D_vlch=p;
            break;

            case 53:
                base_tepl.lb_okr=p;
            break;

            case 54:
                base_tepl.lb_ip=p;
            break;

            case 55:
                base_tepl.sig_vp=p;
            break;

            case 56:
                base_tepl.h_z2=p;
            break;

            case 57:
                base_tepl.b_z2=p;
            break;

            case 58:
                base_tepl.D_dp=p;
            break;

            case 59:
                base_tepl.d=p;
            break;

            case 60:
                base_tepl.d1=p;
            break;

            case 61:
                base_tepl.h_z3=p;
            break;

            case 62:
                base_tepl.nu_l=p;
            break;

            case 63:
                base_tepl.t_p=p;
            break;

            case 64:
                base_tepl.m_i=p;
            break;

            case 65:
                base_tepl.n_el=p;
            break;

            case 66:
                base_tepl.gm_m=p;
            break;

            case 67:
                base_tepl.c_m=p;
            break;

            case 68:
                base_tepl.gm_c=p;
            break;

            case 69:
                base_tepl.c_ct=p;
            break;

            case 70:
                base_tepl.ro_m=p;
            break;

            case 71:
                base_tepl.P2=p;
            break;

            case 72:
                base_tepl.U1=p;
            break;

            case 73:
                base_tepl.n_u=p;
            break;

            case 74:
                base_tepl.cos_f=p;
            break;

            case 75:
                base_tepl.ro_al=p;
            break;

            case 76:
                base_tepl.D_kzk=p;
            break;

            case 77:
                base_tepl.k_obm=p;
            break;

            case 78:
                base_tepl.k_sk=p;
            break;
       }
    }
}
