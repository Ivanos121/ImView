#include "vent_model.h"
#include "ui_vent_model.h"
#include "customhelpdelegate.h"
#include "plot.h"

vent_model::vent_model(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vent_model)
{
    ui->setupUi(this);

    ui->plot_2->t_max = 0.01;
    ui->plot_2->U_max = 400.0;
    ui->plot_2->margin_bottom = 40;
    ui->plot_2->margin_left = 100;
    ui->plot_2->reset();

//    ui->tableWidget->setRowCount(30);
//    ui->tableWidget->setColumnCount(4);
//    QStringList name;
//    name << "Величина" << "Обозначение" << "Значение" << "Размерность";
//    ui->tableWidget->setHorizontalHeaderLabels(name);
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
//    ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
//    ui->tableWidget->verticalHeader()->setVisible(true);
//    ui->tableWidget->resizeColumnsToContents();

//    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
//    {
//        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
//        {
//            ui->tableWidget->setItem(row, column, new QTableWidgetItem());

//        }
//    }

//    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Внутренний расчетный диаметр вентилятора"));
//    ui->tableWidget->setItem(1, 0, new QTableWidgetItem("Внешний расчетный диаметр вентилятора"));
//    ui->tableWidget->setItem(2, 0, new QTableWidgetItem("Ширина лопатки вентилятора"));
//    ui->tableWidget->setItem(3, 0, new QTableWidgetItem("Частота вращения вентилятора"));
//    ui->tableWidget->setItem(4, 0, new QTableWidgetItem("Плотность воздуха"));
//    ui->tableWidget->setItem(5, 0, new QTableWidgetItem("Суммарная площадь отверстий в сетке кожуха"));
//    ui->tableWidget->setItem(6, 0, new QTableWidgetItem("Общая площадь сетки кожуха"));
//    ui->tableWidget->setItem(7, 0, new QTableWidgetItem("Площадь сечения в месте поворота к рабочему колесу"));
//    ui->tableWidget->setItem(8, 0, new QTableWidgetItem("Угол поворота потока к входным кромкам лопаток рабочего колеса"));
//    ui->tableWidget->setItem(9, 0, new QTableWidgetItem("Площадь сечения в месте поворота перед входом в межреберные каналы"));
//    ui->tableWidget->setItem(10, 0, new QTableWidgetItem("Угол поворота потока перед входом в межреберные каналы"));
//    ui->tableWidget->setItem(11, 0, new QTableWidgetItem("Площадь сечения перед входом в межреберные каналы"));
//    ui->tableWidget->setItem(12, 0, new QTableWidgetItem("Площадь сечения межреберных каналов от станины до кожуха вентилятора"));
//    ui->tableWidget->setItem(13, 0, new QTableWidgetItem("Угол натекания потока на ребра станины"));
//    ui->tableWidget->setItem(14, 0, new QTableWidgetItem("Угол поворота потока в межреберных каналах"));

//    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("D1р"));
//    ui->tableWidget->setItem(1, 1, new QTableWidgetItem("D2р"));
//    ui->tableWidget->setItem(2, 1, new QTableWidgetItem("b"));
//    ui->tableWidget->setItem(3, 1, new QTableWidgetItem("n"));
//    ui->tableWidget->setItem(4, 1, new QTableWidgetItem("ro"));
//    ui->tableWidget->setItem(5, 1, new QTableWidgetItem("Sotv"));
//    ui->tableWidget->setItem(6, 1, new QTableWidgetItem("S0"));
//    ui->tableWidget->setItem(7, 1, new QTableWidgetItem("S1"));
//    ui->tableWidget->setItem(8, 1, new QTableWidgetItem("alpha1"));
//    ui->tableWidget->setItem(9, 1, new QTableWidgetItem("S2"));
//    ui->tableWidget->setItem(10, 1, new QTableWidgetItem("alpha2"));
//    ui->tableWidget->setItem(11, 1, new QTableWidgetItem("S3"));
//    ui->tableWidget->setItem(12, 1, new QTableWidgetItem("S4"));
//    ui->tableWidget->setItem(13, 1, new QTableWidgetItem("fi"));
//    ui->tableWidget->setItem(14, 1, new QTableWidgetItem("fi2"));

//    ui->tableWidget->setItem(0, 3, new QTableWidgetItem("м"));
//    ui->tableWidget->setItem(1, 3, new QTableWidgetItem("м"));
//    ui->tableWidget->setItem(2, 3, new QTableWidgetItem("м"));
//    ui->tableWidget->setItem(3, 3, new QTableWidgetItem("об/мин"));
//    ui->tableWidget->setItem(4, 3, new QTableWidgetItem("кг/м3"));
//    ui->tableWidget->setItem(5, 3, new QTableWidgetItem("м2"));
//    ui->tableWidget->setItem(6, 3, new QTableWidgetItem("м2"));
//    ui->tableWidget->setItem(7, 3, new QTableWidgetItem("м2"));
//    ui->tableWidget->setItem(8, 3, new QTableWidgetItem("град."));
//    ui->tableWidget->setItem(9, 3, new QTableWidgetItem("град."));
//    ui->tableWidget->setItem(10, 3, new QTableWidgetItem("alpha2"));
//    ui->tableWidget->setItem(11, 3, new QTableWidgetItem("м2"));
//    ui->tableWidget->setItem(12, 3, new QTableWidgetItem("м2"));
//    ui->tableWidget->setItem(13, 3, new QTableWidgetItem("град."));
//    ui->tableWidget->setItem(14, 3, new QTableWidgetItem("град."));

//    for (int i=0; i<ui->tableWidget->rowCount(); i++)
//    {

//        if (ui->tableWidget->item(i, 1) != 0)
//        {
//            ui->tableWidget->item(i, 1)->setTextAlignment(Qt::AlignCenter);
//        }
//        if (ui->tableWidget->item(i, 3) != 0)
//        {
//            ui->tableWidget->item(i, 3)->setTextAlignment(Qt::AlignCenter);
//        }
//    }

//    //запрет редактирования первого столбца
//    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
//    {
//        if (ui->tableWidget->item(row,0) != 0)
//        {
//            ui->tableWidget->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
//        }
//        if (ui->tableWidget->item(row,1) != 0)
//        {
//            ui->tableWidget->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
//        }
//        if (ui->tableWidget->item(row,2) != 0)
//        {
//            ui->tableWidget->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
//            ui->tableWidget->item(row,2)->setTextAlignment(Qt::AlignCenter);
//        }
//        if (ui->tableWidget->item(row,3) != 0)
//        {
//            ui->tableWidget->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
//        }
//    }

//    QPalette p=ui->tableWidget->palette();
//    p.setColor(QPalette::Base, QColor(255, 255, 191));
//    p.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
//    ui->tableWidget->setPalette(p);

//    CustomHelpDelegate* customHelpDelegate = new CustomHelpDelegate(this); //создание делегата для создания комбобоксов
//    ui->tableWidget->setItemDelegateForColumn(0, customHelpDelegate);
}

vent_model::~vent_model()
{
    delete ui;
}

