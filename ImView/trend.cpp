#include "trend.h"
#include "ui_trend.h"

#include "cmath"
#include "plot.h"
#include <math.h>
#include <QtSvg>
#include <QSvgWidget>
#include <QGraphicsPixmapItem>
#include "ui_mainwindow.h"
#include "ui_draw_poper.h"
#include "ui_draw_line.h"
#include "ui_vent_tract.h"
#include "ui_teplovent.h"
#include "ui_vent_model.h"

int position_2;
double t_max;

double y_0,y_1,y_2,y_3,y_4,y_5,y_6,y_7,y_8,y_9,y_10,y_11,y_12,y_13,y_14,y_15,y_16;
double a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16;
double b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15,b16;
double w_w,w_0,M_M,M_k,s_s,s_k,R_1,R_2;


trend::trend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::trend),
    t(0.0)
{
    maxY2 = 0;
    minY2 = 200;

    count = 0;

    ui->setupUi(this);

    //Настройки виджета Plot
    ui->plot->t_max = 10;
    ui->plot->U_max = 20.0;
    ui->plot->margin_bottom = 40;
    ui->plot->margin_left = 100;
    ui->plot->reset();

    connect(&timer, &QTimer::timeout, this, &trend::on_timerTimeout);

    //Первоначальная цветовая настройка лейблов
    ui->label->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_4->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_5->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_6->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_7->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_8->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_9->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_10->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_11->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_12->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_13->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_14->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_2->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_17->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_18->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_19->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));
    ui->label_20->setStyleSheet(QString("background-color: hsl(235, 100%, 30%)"));


    ui->tableWidget->setRowCount(17);
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

    for (int i=0; i<17; i++)
    {
        if (ui->tableWidget->item(i, 0) != 0)
        {
            ui->tableWidget->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget->setItem(0,  1, new QTableWidgetItem("Станина, °C"));
    ui->tableWidget->setItem(1,  1, new QTableWidgetItem("Подшипниковый узел справа сзади, °C"));
    ui->tableWidget->setItem(2,  1, new QTableWidgetItem("Лобовая часть слева спереди, °C"));
    ui->tableWidget->setItem(3,  1, new QTableWidgetItem("Подшипниковый узел слева спереди, °C"));
    ui->tableWidget->setItem(4,  1, new QTableWidgetItem("Лобовая часть слева сзади, °C"));
    ui->tableWidget->setItem(5,  1, new QTableWidgetItem("Станина, °C"));
    ui->tableWidget->setItem(6,  1, new QTableWidgetItem("Лобовая часть справа спереди, °C"));
    ui->tableWidget->setItem(7,  1, new QTableWidgetItem("Лобовая часть справа сзади, °C"));
    ui->tableWidget->setItem(8,  1, new QTableWidgetItem("Магнитопровод статора, °C"));
    ui->tableWidget->setItem(9,  1, new QTableWidgetItem("Подшипниковый узел справа спереди, °C"));
    ui->tableWidget->setItem(10, 1, new QTableWidgetItem("Подшипниковый узел слева сзади, °C"));
    ui->tableWidget->setItem(11, 1, new QTableWidgetItem("Ротор сверху, °C"));
    ui->tableWidget->setItem(12, 1, new QTableWidgetItem("Ротор снизу, °C"));
    ui->tableWidget->setItem(13, 1, new QTableWidgetItem("Станина слева, °C"));
    ui->tableWidget->setItem(14, 1, new QTableWidgetItem("Станина справа, °C"));
    ui->tableWidget->setItem(15, 1, new QTableWidgetItem("Вал, °C"));
    ui->tableWidget->setItem(16, 1, new QTableWidgetItem("Клеммная коробка, °C"));

    QPalette p99=ui->tableWidget->palette();
    p99.setColor(QPalette::Base, QColor(225, 255, 255));
    p99.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget->setPalette(p99);

    ui->tableWidget_2->setRowCount(17); //задание количества строк таблицы
    ui->tableWidget_2->setColumnCount(6); //задание количества столбцов
    QStringList name5; //объявление указателя на тип QStringList
    name5 << "№" << "Цвет" << "Свойство" << "Значение" << "Масштабирование" << "Смещение"; //перечисление заголовков
    ui->tableWidget_2->setHorizontalHeaderLabels(name5); //установка заголовков в таблицу
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //Устанавливает ограничения на то, как размер заголовка может быть изменен до тех, которые описаны в данном режиме
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tableWidget_2->resizeColumnsToContents();
    // ui->tableWidget_5->setEditTriggers(QAbstractItemView::AnyKeyPressed);
    ui->tableWidget_2->setColumnWidth(0, 100);

    for(int row = 0; row<ui->tableWidget_2->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_2->columnCount(); column++)
        {
            ui->tableWidget_2->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<17; i++)
    {
        if (ui->tableWidget_2->item(i, 0) != 0)
        {
            ui->tableWidget_2->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget_2->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_2->item(i, 3) != 0)
        {
            ui->tableWidget_2->item(i, 3)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }

        if (ui->tableWidget_2->item(i, 4) != 0)
        {
            ui->tableWidget_2->item(i, 4)->setTextAlignment(Qt::AlignCenter);
        }

        if (ui->tableWidget_2->item(i, 5) != 0)
        {
            ui->tableWidget_2->item(i, 5)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget_2->item(0, 2)->setTextAlignment(Qt::AlignCenter);

    QTableWidgetItem *item51 = new QTableWidgetItem("Item51");
    item51->setCheckState(Qt::Checked);
    item51->setText("Станина, °C:");
    ui->tableWidget_2->setItem(0, 2, item51);

    QTableWidgetItem *item52 = new QTableWidgetItem("Item52");
    item52->setCheckState(Qt::Checked);
    item52->setText("Подшипниковый узел справа сзади, °C:");
    ui->tableWidget_2->setItem(1, 2, item52);

    QTableWidgetItem *item53 = new QTableWidgetItem("Item53");
    item53->setCheckState(Qt::Checked);
    item53->setText("Лобовая часть слева спереди, °C:");
    ui->tableWidget_2->setItem(2, 2, item53);

    QTableWidgetItem *item54 = new QTableWidgetItem("Item54");
    item54->setCheckState(Qt::Checked);
    item54->setText("Подшипниковый узел слева спереди, °C:");
    ui->tableWidget_2->setItem(3, 2, item54);

    QTableWidgetItem *item55 = new QTableWidgetItem("Item55");
    item55->setCheckState(Qt::Checked);
    item55->setText("Лобовая часть слева сзади, °C:");
    ui->tableWidget_2->setItem(4, 2, item55);

    QTableWidgetItem *item56 = new QTableWidgetItem("Item56");
    item56->setCheckState(Qt::Checked);
    item56->setText("Станина, °C:");
    ui->tableWidget_2->setItem(5, 2, item56);

    QTableWidgetItem *item57 = new QTableWidgetItem("Item57");
    item57->setCheckState(Qt::Checked);
    item57->setText("Лобовая часть справа спереди, °C:");
    ui->tableWidget_2->setItem(6, 2, item57);

    QTableWidgetItem *item58 = new QTableWidgetItem("Item58");
    item58->setCheckState(Qt::Checked);
    item58->setText("Лобовая часть справа сзади, °C:");
    ui->tableWidget_2->setItem(7, 2, item58);

    QTableWidgetItem *item59 = new QTableWidgetItem("Item59");
    item59->setCheckState(Qt::Checked);
    item59->setText("Магнитопровод статора, °C:");
    ui->tableWidget_2->setItem(8, 2, item59);

    QTableWidgetItem *item60 = new QTableWidgetItem("Item60");
    item60->setCheckState(Qt::Checked);
    item60->setText("Подшипниковый узел справа спереди, °C:");
    ui->tableWidget_2->setItem(9, 2, item60);

    QTableWidgetItem *item61 = new QTableWidgetItem("Item61");
    item61->setCheckState(Qt::Checked);
    item61->setText("Подшипниковый узел слева сзади, °C:");
    ui->tableWidget_2->setItem(10, 2, item61);

    QTableWidgetItem *item62 = new QTableWidgetItem("Item62");
    item62->setCheckState(Qt::Checked);
    item62->setText("Ротор сверху, °C:");
    ui->tableWidget_2->setItem(11, 2, item62);

    QTableWidgetItem *item63 = new QTableWidgetItem("Item63");
    item63->setCheckState(Qt::Checked);
    item63->setText("Ротор снизу, °C:");
    ui->tableWidget_2->setItem(12, 2, item63);

    QTableWidgetItem *item64 = new QTableWidgetItem("Item64");
    item64->setCheckState(Qt::Checked);
    item64->setText("Станина слева, °C:");
    ui->tableWidget_2->setItem(13, 2, item64);

    QTableWidgetItem *item65 = new QTableWidgetItem("Item65");
    item65->setCheckState(Qt::Checked);
    item65->setText("Станина справа, °C:");
    ui->tableWidget_2->setItem(14, 2, item65);

    QTableWidgetItem *item66 = new QTableWidgetItem("Item66");
    item66->setCheckState(Qt::Checked);
    item66->setText("Станина справа, °C:");
    ui->tableWidget_2->setItem(15, 2, item66);

    QTableWidgetItem *item67 = new QTableWidgetItem("Item67");
    item67->setCheckState(Qt::Checked);
    item67->setText("Клеммная коробка, °C:");
    ui->tableWidget_2->setItem(16, 2, item67);

    ui->tableWidget_2->setItem(0, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(0,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(0, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(0,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(1, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(1,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(1, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(1,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(2, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(2,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(2, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(2,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(3, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(3,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(3, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(3,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(4, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(4,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(4, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(4,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(5, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(5,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(5, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(5,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(6, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(6,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(6, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(6,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(7, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(7,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(7, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(7,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(8, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(8,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(8, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(8,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(9, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(9,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(9, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(9,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(10, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(10,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(10, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(10,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(11, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(11,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(11, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(11,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(12, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(12,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(12, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(12,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(13, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(13,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(13, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(13,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(14, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(14,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(14, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(14,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(15, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(15,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(15, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(15,5)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(16, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->item(16,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget_2->setItem(16, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->item(16,5)->setTextAlignment(Qt::AlignCenter);

    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::magenta);
    dataLineColors.append(Qt::blue);
    dataLineColors.append(Qt::darkGreen);
    dataLineColors.append(Qt::darkBlue);
    dataLineColors.append(Qt::darkYellow);
    dataLineColors.append(Qt::darkMagenta);
    dataLineColors.append(Qt::darkCyan);
    dataLineColors.append(Qt::darkMagenta);
    dataLineColors.append(Qt::darkCyan);
    dataLineColors.append(Qt::darkMagenta);
    dataLineColors.append(Qt::darkCyan);
    dataLineColors.append(Qt::darkMagenta);
    dataLineColors.append(Qt::darkCyan);

    for (int i = 0; i < dataLineColors.size(); i++)
    {
        ui->plot->addDataLine(dataLineColors[i], 0);
    }

    for (int i = 0; i < dataLineColors.size(); i++)
    {
        ui->tableWidget_2->item(i, 1)->setBackground(dataLineColors[i]);
    }
    connect(ui->tableWidget_2, &QTableWidget::cellClicked,this, &trend::setcolorincell);
 }

void trend::setcolorincell(int row, int column)
{
    if (column == 1)
    {
        row = ui->tableWidget_2->currentRow();
        QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
        ui->tableWidget_2->item(row, column)->setBackground(chosenColor);
        ui->plot->setDataLineColor(row, chosenColor);
        dataLineColors[row] = chosenColor;
        repaint();
    }
}

trend::~trend()
{
    delete ui;
}

void trend::startTeplo()
{
    y_0=20*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//станина
    y_1=54*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Подшипниковый узел справа сзади
    y_2=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Лобовая часть слева спереди
    y_3=56*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Подшипниковый узел слева спереди
    y_4=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Лобовая часть слева сзади
    y_5=90*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//станина
    y_6=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Лобовая часть справа спереди
    y_7=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Лобовая часть справа сзади
    y_8=90*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Магнитопровод статора
    y_9=60*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Подшипниковый узел справа спереди
    y_10=56*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Подшипниковый узел слева сзади
    y_11=80*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Ротор сверху
    y_12=80*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Ротор снизу
    y_13=40*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Станина слева
    y_14=40*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Станина слева
    y_15=60*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Вал
    y_16=50*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Клеммная коробка

    ui->plot->addPoint(0, t, y_0);
    ui->plot->addPoint(1, t, y_1);
    ui->plot->addPoint(2, t, y_2);
    ui->plot->addPoint(3, t, y_3);
    ui->plot->addPoint(4, t, y_4);
    ui->plot->addPoint(5, t, y_5);
    ui->plot->addPoint(6, t, y_6);
    ui->plot->addPoint(7, t, y_7);
    ui->plot->addPoint(8, t, y_8);
    ui->plot->addPoint(9, t, y_9);
    ui->plot->addPoint(10, t, y_10);
    ui->plot->addPoint(11, t, y_10);
    ui->plot->addPoint(12, t, y_10);
    ui->plot->addPoint(13, t, y_9);
    ui->plot->addPoint(14, t, y_10);
    ui->plot->addPoint(15, t, y_10);
    ui->plot->addPoint(16, t, y_10);

    timer.start(1000);

    t += 10.0;

    wf->ui->widget_6->ui->widget->ui->verticalSlider->setValue(50);
    wf->ui->widget_6->ui->widget->ui->verticalSlider_2->setValue(20);

   // ui->label_4->setText(QString("%1 moment").arg(moment, 0, 'f', 1));
}


void trend::stopTeplo()
{
    timer.stop();
}

void trend::on_timerTimeout()
{
    y_0=20*(1-exp(-t/20))+ui->lineEdit->text().toDouble();
    y_1=54*(1-exp(-t/20))+ui->lineEdit->text().toDouble();
    y_2=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_3=56*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_4=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_5=90*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_6=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_7=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_8=90*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_9=60*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_10=56*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
    y_11=80*(1-exp(-t/20))+ui->lineEdit->text().toDouble();
    y_12=80*(1-exp(-t/20))+ui->lineEdit->text().toDouble();
    y_13=40*(1-exp(-t/20))+ui->lineEdit->text().toDouble();
    y_14=40*(1-exp(-t/20))+ui->lineEdit->text().toDouble();
    y_15=60*(1-exp(-t/20))+ui->lineEdit->text().toDouble();
    y_16=50*(1-exp(-t/20))+ui->lineEdit->text().toDouble();

    w_0=314;
    w_w=147;
    M_k=44;
    s_k=0.1;
    s_s=(w_0-w_w)/w_0;
    M_M=M_k*2/(s_s/s_k+s_k/s_s);



    if (wf->ui->widget_5->ui->widget->ui->tableWidget->item(0, 2) != 0)
    {
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(0, 2)->setText(QString("%1").arg(QString::number(y_0,'f',1)));
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(0, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget->ui->tableWidget->item(1, 2) != 0)
    {
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(1, 2)->setText(QString("%1").arg(QString::number(y_1,'f',1)));
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(1, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget->ui->tableWidget->item(2, 2) != 0)
    {
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(2, 2)->setText(QString("%1").arg(QString::number(y_2,'f',1)));
       wf->ui->widget_5->ui->widget->ui->tableWidget->item(2, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget->ui->tableWidget->item(3, 2) != 0)
    {
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(3, 2)->setText(QString("%1").arg(QString::number(y_3,'f',1)));
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(3, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget->ui->tableWidget->item(4, 2) != 0)
    {
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(4, 2)->setText(QString("%1").arg(QString::number(y_4,'f',1)));
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(4, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget->ui->tableWidget->item(5, 2) != 0)
    {
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(5, 2)->setText(QString("%1").arg(QString::number(y_5,'f',1)));
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(5, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget->ui->tableWidget->item(6, 2) != 0)
    {
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(6, 2)->setText(QString("%1").arg(QString::number(y_6,'f',1)));
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(6, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget->ui->tableWidget->item(7, 2) != 0)
    {
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(7, 2)->setText(QString("%1").arg(QString::number(y_7,'f',1)));
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(7, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget->ui->tableWidget->item(8, 2) != 0)
    {
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(8, 2)->setText(QString("%1").arg(QString::number(y_8,'f',1)));
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(8, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget->ui->tableWidget->item(9, 2) != 0)
    {
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(9, 2)->setText(QString("%1").arg(QString::number(y_9,'f',1)));
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(9, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget->ui->tableWidget->item(10, 2) != 0)
    {
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(10, 2)->setText(QString("%1").arg(QString::number(y_10,'f',1)));
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(10, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget->ui->tableWidget->item(11, 2) != 0)
    {
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(11, 2)->setText(QString("%1").arg(QString::number(y_11,'f',1)));
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(11, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget->ui->tableWidget->item(12, 2) != 0)
    {
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(12, 2)->setText(QString("%1").arg(QString::number(y_12,'f',1)));
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(12, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget->ui->tableWidget->item(13, 2) != 0)
    {
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(13, 2)->setText(QString("%1").arg(QString::number(y_13,'f',1)));
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(13, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget->ui->tableWidget->item(14, 2) != 0)
    {
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(14, 2)->setText(QString("%1").arg(QString::number(y_14,'f',1)));
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(14, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget->ui->tableWidget->item(15, 2) != 0)
    {
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(15, 2)->setText(QString("%1").arg(QString::number(y_15,'f',1)));
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(15, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget->ui->tableWidget->item(16, 2) != 0)
    {
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(16, 2)->setText(QString("%1").arg(QString::number(y_16,'f',1)));
        wf->ui->widget_5->ui->widget->ui->tableWidget->item(16, 2)->setTextAlignment(Qt::AlignCenter);
    }

    //вывод температур в таблицу draw_poper_new
    if (wf->ui->widget_5->ui->widget_5->ui->tableWidget->item(0, 2) != 0)
    {
        wf->ui->widget_5->ui->widget_5->ui->tableWidget->item(0, 2)->setText(QString("%1").arg(QString::number(y_11,'f',1)));
        wf->ui->widget_5->ui->widget_5->ui->tableWidget->item(0, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget_5->ui->tableWidget->item(1, 2) != 0)
    {
        wf->ui->widget_5->ui->widget_5->ui->tableWidget->item(1, 2)->setText(QString("%1").arg(QString::number(y_12,'f',1)));
        wf->ui->widget_5->ui->widget_5->ui->tableWidget->item(1, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget_5->ui->tableWidget->item(2, 2) != 0)
    {
        wf->ui->widget_5->ui->widget_5->ui->tableWidget->item(2, 2)->setText(QString("%1").arg(QString::number(y_13,'f',1)));
        wf->ui->widget_5->ui->widget_5->ui->tableWidget->item(2, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->widget_5->ui->widget_5->ui->tableWidget->item(3, 2) != 0)
    {
        wf->ui->widget_5->ui->widget_5->ui->tableWidget->item(3, 2)->setText(QString("%1").arg(QString::number(y_14,'f',1)));
        wf->ui->widget_5->ui->widget_5->ui->tableWidget->item(3, 2)->setTextAlignment(Qt::AlignCenter);
    }

//    if (mw->ui->widget_8->ui->tableWidget->item(4, 2) != 0)
//    {
//        mw->ui->widget_8->ui->tableWidget->item(4, 2)->setText(QString("%1").arg(QString::number(y_15,'f',1)));
//        mw->ui->widget_8->ui->tableWidget->item(4, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (mw->ui->widget_8->ui->tableWidget->item(5, 2) != 0)
//    {
//        mw->ui->widget_8->ui->tableWidget->item(5, 2)->setText(QString("%1").arg(QString::number(y_16,'f',1)));
//        mw->ui->widget_8->ui->tableWidget->item(5, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (mw->ui->widget_8->ui->tableWidget->item(6, 2) != 0)
//    {
//        mw->ui->widget_8->ui->tableWidget->item(6, 2)->setText(QString("%1").arg(QString::number(y_8,'f',1)));
//        mw->ui->widget_8->ui->tableWidget->item(6, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (mw->ui->widget_8->ui->tableWidget->item(7, 2) != 0)
//    {
//        mw->ui->widget_8->ui->tableWidget->item(7, 2)->setText(QString("%1").arg(QString::number(y_8,'f',1)));
//        mw->ui->widget_8->ui->tableWidget->item(7, 2)->setTextAlignment(Qt::AlignCenter);
//    }



    a0=ui->tableWidget_2->item(0,4)->text().toDouble();
    a1=ui->tableWidget_2->item(1,4)->text().toDouble();
    a2=ui->tableWidget_2->item(2,4)->text().toDouble();
    a3=ui->tableWidget_2->item(3,4)->text().toDouble();
    a4=ui->tableWidget_2->item(4,4)->text().toDouble();
    a5=ui->tableWidget_2->item(5,4)->text().toDouble();
    a6=ui->tableWidget_2->item(6,4)->text().toDouble();
    a7=ui->tableWidget_2->item(7,4)->text().toDouble();
    a8=ui->tableWidget_2->item(8,4)->text().toDouble();
    a9=ui->tableWidget_2->item(9,4)->text().toDouble();
    a10=ui->tableWidget_2->item(10,4)->text().toDouble();
    a11=ui->tableWidget_2->item(11,4)->text().toDouble();
    a12=ui->tableWidget_2->item(12,4)->text().toDouble();
    a13=ui->tableWidget_2->item(9,4)->text().toDouble();
    a14=ui->tableWidget_2->item(10,4)->text().toDouble();
    a15=ui->tableWidget_2->item(11,4)->text().toDouble();
    a16=ui->tableWidget_2->item(12,4)->text().toDouble();

    b0=ui->tableWidget_2->item(0,5)->text().toDouble();
    b1=ui->tableWidget_2->item(1,5)->text().toDouble();
    b2=ui->tableWidget_2->item(2,5)->text().toDouble();
    b3=ui->tableWidget_2->item(3,5)->text().toDouble();
    b4=ui->tableWidget_2->item(4,5)->text().toDouble();
    b5=ui->tableWidget_2->item(5,5)->text().toDouble();
    b6=ui->tableWidget_2->item(6,5)->text().toDouble();
    b7=ui->tableWidget_2->item(7,5)->text().toDouble();
    b8=ui->tableWidget_2->item(8,5)->text().toDouble();
    b9=ui->tableWidget_2->item(9,5)->text().toDouble();
    b10=ui->tableWidget_2->item(10,5)->text().toDouble();
    b11=ui->tableWidget_2->item(11,5)->text().toDouble();
    b12=ui->tableWidget_2->item(12,5)->text().toDouble();
    b13=ui->tableWidget_2->item(9,5)->text().toDouble();
    b14=ui->tableWidget_2->item(10,5)->text().toDouble();
    b15=ui->tableWidget_2->item(11,5)->text().toDouble();
    b16=ui->tableWidget_2->item(12,5)->text().toDouble();

    if(ui->tableWidget_2->model()->index(0,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(0, t, b0+a0*y_0);
    }

    if(ui->tableWidget_2->model()->index(1,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(1, t, b1+a1*y_1);
    }

    if(ui->tableWidget_2->model()->index(2,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(2, t, b2+a2*y_2);
    }

    if(ui->tableWidget_2->model()->index(3,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(3, t, b3+a3*y_3);
    }

    if(ui->tableWidget_2->model()->index(4,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(4, t, b4+a4*y_4);
    }

    if(ui->tableWidget_2->model()->index(5,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(5, t, b5+a5*y_5);
    }

    if(ui->tableWidget_2->model()->index(6,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(6, t, b6+a6*y_6);
    }

    if(ui->tableWidget_2->model()->index(7,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(7, t, b7+a7*y_7);
    }

    if(ui->tableWidget_2->model()->index(8,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(8, t, b8+a8*y_8);
    }

    if(ui->tableWidget_2->model()->index(9,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(9, t, b9+a9*y_9);
    }

    if(ui->tableWidget_2->model()->index(10,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(10, t, b10+a10*y_10);
    }

    if(ui->tableWidget_2->model()->index(11,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(11, t, b11+a11*y_11);
    }

    if(ui->tableWidget_2->model()->index(12,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(12, t, b12+a12*y_12);
    }

    if(ui->tableWidget_2->model()->index(13,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(13, t, b13+a13*y_13);
    }

    if(ui->tableWidget_2->model()->index(14,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(14, t, b14+a14*y_14);
    }

    if(ui->tableWidget_2->model()->index(15,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(15, t, b15+a15*y_15);
    }

    if(ui->tableWidget_2->model()->index(16,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(16, t, b16+a16*y_16);
    }

    t += 1.0;


    if (ui->tableWidget_2->item(0, 3) != 0)
    {
        ui->tableWidget_2->item(0, 3)->setText(QString("%1").arg(QString::number(b0+a0*y_0,'f',1)));
    }

    if (ui->tableWidget_2->item(1, 3) != 0)
    {
        ui->tableWidget_2->item(1, 3)->setText(QString("%1").arg(QString::number(b1+a1*y_1,'f',1)));
    }

    if (ui->tableWidget_2->item(2, 3) != 0)
    {
        ui->tableWidget_2->item(2, 3)->setText(QString("%1").arg(QString::number(b2+a2*y_2,'f',1)));
    }

    if (ui->tableWidget_2->item(3, 3) != 0)
    {
        ui->tableWidget_2->item(3, 3)->setText(QString("%1").arg(QString::number(b3+a3*y_3,'f',1)));
    }

    if (ui->tableWidget_2->item(4, 3) != 0)
    {
        ui->tableWidget_2->item(4, 3)->setText(QString("%1").arg(QString::number(b4+a4*y_4,'f',1)));
    }

    if (ui->tableWidget_2->item(5, 3) != 0)
    {
        ui->tableWidget_2->item(5, 3)->setText(QString("%1").arg(QString::number(b5+a5*y_5,'f',1)));
    }

    if (ui->tableWidget_2->item(6, 3) != 0)
    {
        ui->tableWidget_2->item(6, 3)->setText(QString("%1").arg(QString::number(b6+a6*y_6,'f',1)));
    }

    if (ui->tableWidget_2->item(7, 3) != 0)
    {
        ui->tableWidget_2->item(7, 3)->setText(QString("%1").arg(QString::number(b7+a7*y_7,'f',1)));
    }

    if (ui->tableWidget_2->item(8, 3) != 0)
    {
        ui->tableWidget_2->item(8, 3)->setText(QString("%1").arg(QString::number(b8+a8*y_8,'f',1)));
    }

    if (ui->tableWidget_2->item(9, 3) != 0)
    {
        ui->tableWidget_2->item(9, 3)->setText(QString("%1").arg(QString::number(b9+a9*y_9,'f',1)));
    }

    if (ui->tableWidget_2->item(10, 3) != 0)
    {
        ui->tableWidget_2->item(10, 3)->setText(QString("%1").arg(QString::number(b10+a10*y_10,'f',1)));
    }

    if (ui->tableWidget_2->item(11, 3) != 0)
    {
        ui->tableWidget_2->item(11, 3)->setText(QString("%1").arg(QString::number(b11+a11*y_11,'f',1)));
    }

    if (ui->tableWidget_2->item(12, 3) != 0)
    {
        ui->tableWidget_2->item(12, 3)->setText(QString("%1").arg(QString::number(b12+a12*y_12,'f',1)));
    }

    if (ui->tableWidget_2->item(13, 3) != 0)
    {
        ui->tableWidget_2->item(13, 3)->setText(QString("%1").arg(QString::number(b13+a13*y_13,'f',1)));
    }

    if (ui->tableWidget_2->item(14, 3) != 0)
    {
        ui->tableWidget_2->item(14, 3)->setText(QString("%1").arg(QString::number(b14+a14*y_14,'f',1)));
    }

    if (ui->tableWidget_2->item(15, 3) != 0)
    {
        ui->tableWidget_2->item(15, 3)->setText(QString("%1").arg(QString::number(b15+a15*y_15,'f',1)));
    }

    if (ui->tableWidget_2->item(16, 3) != 0)
    {
        ui->tableWidget_2->item(16, 3)->setText(QString("%1").arg(QString::number(b16+a16*y_16,'f',1)));
    }


    if (ui->tableWidget->item(0, 2) != 0)
    {
        ui->tableWidget->item(0, 2)->setText(QString("%1").arg(QString::number(b0+a0*y_0,'f',1)));
        ui->tableWidget->item(0, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(1, 2) != 0)
    {
        ui->tableWidget->item(1, 2)->setText(QString("%1").arg(QString::number(b1+a1*y_1,'f',1)));
        ui->tableWidget->item(1, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(2, 2) != 0)
    {
        ui->tableWidget->item(2, 2)->setText(QString("%1").arg(QString::number(b2+a2*y_2,'f',1)));
        ui->tableWidget->item(2, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(3, 2) != 0)
    {
        ui->tableWidget->item(3, 2)->setText(QString("%1").arg(QString::number(b3+a3*y_3,'f',1)));
        ui->tableWidget->item(3, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(4, 2) != 0)
    {
        ui->tableWidget->item(4, 2)->setText(QString("%1").arg(QString::number(b4+a4*y_4,'f',1)));
        ui->tableWidget->item(4, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(5, 2) != 0)
    {
        ui->tableWidget->item(5, 2)->setText(QString("%1").arg(QString::number(b5+a5*y_5,'f',1)));
        ui->tableWidget->item(5, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(6, 2) != 0)
    {
        ui->tableWidget->item(6, 2)->setText(QString("%1").arg(QString::number(b6+a6*y_6,'f',1)));
        ui->tableWidget->item(6, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(7, 2) != 0)
    {
        ui->tableWidget->item(7, 2)->setText(QString("%1").arg(QString::number(b7+a7*y_7,'f',1)));
        ui->tableWidget->item(7, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(8, 2) != 0)
    {
        ui->tableWidget->item(8, 2)->setText(QString("%1").arg(QString::number(b8+a8*y_8,'f',1)));
        ui->tableWidget->item(8, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(9, 2) != 0)
    {
        ui->tableWidget->item(9, 2)->setText(QString("%1").arg(QString::number(b9+a9*y_9,'f',1)));
        ui->tableWidget->item(9, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(10, 2) != 0)
    {
        ui->tableWidget->item(10, 2)->setText(QString("%1").arg(QString::number(b10+a10*y_10,'f',1)));
        ui->tableWidget->item(10, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(11, 2) != 0)
    {
        ui->tableWidget->item(11, 2)->setText(QString("%1").arg(QString::number(b11+a11*y_11,'f',1)));
        ui->tableWidget->item(11, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(12, 2) != 0)
    {
        ui->tableWidget->item(12, 2)->setText(QString("%1").arg(QString::number(b12+a12*y_12,'f',1)));
        ui->tableWidget->item(12, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(13, 2) != 0)
    {
        ui->tableWidget->item(13, 2)->setText(QString("%1").arg(QString::number(b13+a13*y_13,'f',1)));
        ui->tableWidget->item(13, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(14, 2) != 0)
    {
        ui->tableWidget->item(14, 2)->setText(QString("%1").arg(QString::number(b14+a14*y_14,'f',1)));
        ui->tableWidget->item(14, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(15, 2) != 0)
    {
        ui->tableWidget->item(15, 2)->setText(QString("%1").arg(QString::number(b15+a15*y_15,'f',1)));
        ui->tableWidget->item(15, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (ui->tableWidget->item(16, 2) != 0)
    {
        ui->tableWidget->item(16, 2)->setText(QString("%1").arg(QString::number(b16+a16*y_16,'f',1)));
        ui->tableWidget->item(16, 2)->setTextAlignment(Qt::AlignCenter);
    }

   // Расчет значений цветов

    int color_0 = 225 - (y_0 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_0));

    int color_1 = 225 - (y_1 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_4->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_1));

    int color_2 = 225 - (y_2 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_5->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_2));

    int color_3 = 225 - (y_3 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_6->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_3));

    int color_4 = 225 - (y_4 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_7->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_4));

    int color_5 = 225 - (y_5 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_8->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_5));

    int color_6 = 225 - (y_6 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_9->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_6));

    int color_7 = 225 - (y_7 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_10->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_7));

    int color_8 = 225 - (y_8 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_11->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_8));

    int color_9 = 225 - (y_9 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_12->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_9));

    int color_10 = 225 - (y_10 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_13->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_10));

    int color_11 = 225 - (y_11 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_14->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_11));

    int color_12 = 225 - (y_12 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_2->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_12));

    int color_13 = 225 - (y_13 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_17->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_13));

    int color_14 = 225 - (y_14 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_18->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_14));

    int color_15 = 225 - (y_15 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_19->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_15));

    int color_16 = 225 - (y_16 - ui->lineEdit->text().toDouble()) / (140.0 - ui->lineEdit->text().toDouble()) * 220.0;
    ui->label_20->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_16));


    //Отрисовка draw_line
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1548\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_2));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1544\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_4));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1598\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_6));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1594\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_7));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#rect1539\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_8));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1588\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_8));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1558\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_3));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1560\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_3));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1562\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_3));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1564\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_3));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1566\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_3));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1628\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_10));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1620\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_10));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1622\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_10));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1624\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_10));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1626\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_10));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1584\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_9));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1576\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_9));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1578\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_9));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1580\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_9));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1582\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_9));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1600\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1602\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1604\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1606\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1608\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1546\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_11));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1590\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_12));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1550\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_11));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1596\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_11));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1592\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_11));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1542\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_11));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1554\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_13));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1586\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_14));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1556\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_16));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1574\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_15));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1572\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_15));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1568\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_15));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1570\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_15));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1610\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_15));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path995\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_15));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1616\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_15));

    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6\").text('%1 °C');").arg(y_2, 0, 'f', 1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-5\").text('%1 °C');").arg(y_4, 0, 'f', 1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-1\").text('%1 °C');").arg(y_6, 0, 'f', 1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-5-9\").text('%1 °C');").arg(y_7, 0, 'f', 1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-2\").text('%1 °C');").arg(y_8, 0, 'f', 1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-2-8-3\").text('%1 °C');").arg(y_8, 0, 'f', 1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-3\").text('%1 °C');").arg(y_3, 0, 'f', 1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-3-9\").text('%1 °C');").arg(y_10, 0, 'f', 1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-3-8\").text('%1 °C');").arg(y_9, 0, 'f', 1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-3-9-1\").text('%1 °C');").arg(y_1, 0, 'f', 1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-2-8\").text('%1 °C');").arg(y_11, 0, 'f', 1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-2-6\").text('%1 °C');").arg(y_12, 0, 'f', 1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-2-8-8-0\").text('%1 °C');").arg(y_13, 0, 'f', 1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-2-8-8-1\").text('%1 °C');").arg(y_14, 0, 'f', 1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-2-4\").text('%1 °C');").arg(y_16, 0, 'f', 1));
    wf->ui->widget_5->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan2545-6-2-8-8\").text('%1 °C');").arg(y_15, 0, 'f', 1));

    //Отрисовка draw_poper
    wf->ui->widget_5->ui->widget_5->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1488\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_8));
    wf->ui->widget_5->ui->widget_5->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1088\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_15));
    wf->ui->widget_5->ui->widget_5->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1086\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_16));
    wf->ui->widget_5->ui->widget_5->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1490\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_12));
    wf->ui->widget_5->ui->widget_5->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1492\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_15));

    wf->ui->widget_5->ui->widget_5->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan3714-2\").text('%1 °C');").arg(y_8, 0, 'f', 1));
    wf->ui->widget_5->ui->widget_5->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan3714-2-7\").text('%1 °C');").arg(y_8, 0, 'f', 1));
    wf->ui->widget_5->ui->widget_5->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan3714\").text('%1 °C');").arg(y_15, 0, 'f', 1));
    wf->ui->widget_5->ui->widget_5->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan3714-11-7\").text('%1 °C');").arg(y_13, 0, 'f', 1));
    wf->ui->widget_5->ui->widget_5->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan3714-1-9\").text('%1 °C');").arg(y_14, 0, 'f', 1));
    wf->ui->widget_5->ui->widget_5->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan3714-2-0\").text('%1 °C');").arg(y_16, 0, 'f', 1));
    wf->ui->widget_5->ui->widget_5->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan3714-11\").text('%1 °C');").arg(y_11, 0, 'f', 1));
    wf->ui->widget_5->ui->widget_5->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan3714-1\").text('%1 °C');").arg(y_12, 0, 'f', 1));


    //отрисовка vent_tract
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1285\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_8));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1289\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_4));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1277\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_11));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1291\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_11));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1159\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_15));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1161\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_15));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1163\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_15));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1165\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_15));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1243\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_10));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1269\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_10));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1271\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_10));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1273\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_10));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1275\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_10));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1241\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_10));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1261\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_10));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1263\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_10));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1265\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_10));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1267\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_10));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1287\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_8));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1295\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_7));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1279\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_12));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1297\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_12));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1167\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_13));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1293\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_11));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1299\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_12));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#path1169\").attr(\"style\", \"fill: hsl(%1, 100%, 50%);stroke-dasharray:0, 8.26299195;stroke-width:.75118;stroke:#000\");").arg(color_13));

    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan1010\").text('%1 °C');").arg(y_8, 0, 'f', 1));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan1010-8\").text('%1 °C');").arg(y_4, 0, 'f', 1));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan1010-0\").text('%1 °C');").arg(y_11, 0, 'f', 1));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan1010-0-1\").text('%1 °C');").arg(y_8, 0, 'f', 1));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan1010-8-5\").text('%1 °C');").arg(y_7, 0, 'f', 1));
    wf->ui->widget_6->ui->widget->ui->webEngineView->page()->runJavaScript(QString("$(\"#tspan1010-9\").text('%1 °C');").arg(y_12, 0, 'f', 1));




//    y_0=20*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//станина
//    y_1=54*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Подшипниковый узел справа сзади
//    y_2=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Лобовая часть слева спереди
//    y_3=56*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Подшипниковый узел слева спереди
//    y_4=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Лобовая часть слева сзади
//    y_5=90*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//станина
//    y_6=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Лобовая часть справа спереди
//    y_7=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Лобовая часть справа сзади
//    y_8=90*(1-exp(-t/25))+ui->lineEdit->text().toDouble();//Магнитопровод статора
//    y_9=60*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Подшипниковый узел справа спереди
//    y_10=56*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Подшипниковый узел слева сзади
//    y_11=80*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Ротор сверху
//    y_12=80*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Ротор снизу
//    y_13=40*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Станина слева
//    y_14=40*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Станина слева
//    y_15=60*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Вал
//    y_16=50*(1-exp(-t/20))+ui->lineEdit->text().toDouble();//Клеммная коробка

//    y_0=20*(1-exp(-t/20))+ui->lineEdit->text().toDouble();
//    y_1=54*(1-exp(-t/20))+ui->lineEdit->text().toDouble();
//    y_2=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
//    y_3=56*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
//    y_4=120*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
//    y_5=90*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
//    y_6=99*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
//    y_7=111*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
//    y_8=90*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
//    y_9=60*(1-exp(-t/25))+ui->lineEdit->text().toDouble();
//    y_10=56*(1-exp(-t/25))+ui->lineEdit->text().toDouble();


//Проверка условия окончания расчета

    if (y_2 > maxY2)
           {
               maxY2 = y_2;
           }

           if (y_2 < minY2)
           {
               minY2 = y_2;
           }

           count++;

   if (count == 3)
   {

       if ((maxY2 - minY2)/maxY2 < 0.005)
       {
            timer.stop();

            if(y_0>y_1)
            {
                max=y_1;
            }
            else max=y_0;

            if(max<y_2)
            {
                max=y_2;
            }
            if(max<y_3)
            {
                max=y_3;
            }
            if(max<y_4)
            {
                max=y_4;
            }
            if(max<y_5)
            {
                max=y_5;
            }
            if(max<y_6)
            {
               max=y_6;
            }
            if(max<y_7)
            {
                max=y_7;
            }
            if(max<y_8)
            {
                max=y_8;
            }
            if(max<y_9)
            {
                max=y_9;
            }
            if(max<y_10)
            {
                max=y_10;
            }
            if(max<y_11)
            {
                max=y_11;
            }
            if(max<y_12)
            {
                max=y_12;
            }
            if(max<y_13)
            {
                max=y_13;
            }
            if(max<y_14)
            {
                max=y_14;
            }
            if(max<y_15)
            {
                max=y_15;
            }
            if(max<y_16)
            {
                max=y_16;
            }

            double miny=ui->lineEdit->text().toDouble();
            double h=(max-miny)/9;
            double shag1=miny+h;
            double shag2=shag1+h;
            double shag3=shag2+h;
            double shag4=shag3+h;
            double shag5=shag4+h;
            double shag6=shag5+h;
            double shag7=shag6+h;
            double shag8=shag7+h;

            //Отображение градиентного столбца на форме draw_line после окончания расчетов

            wf->ui->widget_5->ui->widget->ui->webEngineView_2->show();
            wf->ui->widget_5->ui->widget->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));


            wf->ui->widget_5->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan901\").text('%1');").arg(max, 0, 'f', 1));
            wf->ui->widget_5->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan865\").text('%1');").arg(miny, 0, 'f', 1));
            wf->ui->widget_5->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan869\").text('%1');").arg(shag1, 0, 'f', 1));
            wf->ui->widget_5->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan873\").text('%1');").arg(shag2, 0, 'f', 1));
            wf->ui->widget_5->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan877\").text('%1');").arg(shag3, 0, 'f', 1));
            wf->ui->widget_5->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan881\").text('%1');").arg(shag4, 0, 'f', 1));
            wf->ui->widget_5->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan885\").text('%1');").arg(shag5, 0, 'f', 1));
            wf->ui->widget_5->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan889\").text('%1');").arg(shag6, 0, 'f', 1));
            wf->ui->widget_5->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan893\").text('%1');").arg(shag7, 0, 'f', 1));
            wf->ui->widget_5->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan897\").text('%1');").arg(shag8, 0, 'f', 1));

            //Отображение градиентного столбца на форме draw_poper после окончания расчетов

            wf->ui->widget_5->ui->widget_5->ui->webEngineView_2->show();
            wf->ui->widget_5->ui->widget_5->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));

            wf->ui->widget_5->ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan901\").text('%1');").arg(max, 0, 'f', 1));
            wf->ui->widget_5->ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan865\").text('%1');").arg(miny, 0, 'f', 1));
            wf->ui->widget_5->ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan869\").text('%1');").arg(shag1, 0, 'f', 1));
            wf->ui->widget_5->ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan873\").text('%1');").arg(shag2, 0, 'f', 1));
            wf->ui->widget_5->ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan877\").text('%1');").arg(shag3, 0, 'f', 1));
            wf->ui->widget_5->ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan881\").text('%1');").arg(shag4, 0, 'f', 1));
            wf->ui->widget_5->ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan885\").text('%1');").arg(shag5, 0, 'f', 1));
            wf->ui->widget_5->ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan889\").text('%1');").arg(shag6, 0, 'f', 1));
            wf->ui->widget_5->ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan893\").text('%1');").arg(shag7, 0, 'f', 1));
            wf->ui->widget_5->ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan897\").text('%1');").arg(shag8, 0, 'f', 1));

            //Отображение градиентного столбца на форме vent_tract после окончания расчетов

            wf->ui->widget_6->ui->widget->ui->webEngineView_2->show();
            wf->ui->widget_6->ui->widget->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));

            wf->ui->widget_6->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan901\").text('%1');").arg(max, 0, 'f', 1));
            wf->ui->widget_6->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan865\").text('%1');").arg(miny, 0, 'f', 1));
            wf->ui->widget_6->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan869\").text('%1');").arg(shag1, 0, 'f', 1));
            wf->ui->widget_6->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan873\").text('%1');").arg(shag2, 0, 'f', 1));
            wf->ui->widget_6->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan877\").text('%1');").arg(shag3, 0, 'f', 1));
            wf->ui->widget_6->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan881\").text('%1');").arg(shag4, 0, 'f', 1));
            wf->ui->widget_6->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan885\").text('%1');").arg(shag5, 0, 'f', 1));
            wf->ui->widget_6->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan889\").text('%1');").arg(shag6, 0, 'f', 1));
            wf->ui->widget_6->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan893\").text('%1');").arg(shag7, 0, 'f', 1));
            wf->ui->widget_6->ui->widget->ui->webEngineView_2->page()->runJavaScript(QString("$(\"#tspan897\").text('%1');").arg(shag8, 0, 'f', 1));

            //Вывод сообщзения об окончании расчетов

            QMessageBox::information(this, tr("Сообщение"), tr("Расчет окончен!"));
       }

       maxY2 = 0;
       minY2 = 200;

       count = 0;
   }
}
