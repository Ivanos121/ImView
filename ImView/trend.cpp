#include "trend.h"
#include "ui_teplschem.h"
#include "ui_trend.h"

#include <iostream>
#include <fstream>
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
double a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16;
double b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15,b16;
double w_w,w_0,M_M,M_k,s_s,s_k,R_1,R_2;



Trend::Trend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Trend),
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

    connect(&timer, &QTimer::timeout, this, &Trend::on_timerTimeout);

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
}


Trend::~Trend()
{
    delete ui;
}

void Trend::startTeplo()
{
    y_0=20*(1-exp(-t/20)) +wf->item28->text().toDouble();//станина
    y_1=54*(1-exp(-t/20)) +wf->item28->text().toDouble();//Подшипниковый узел справа сзади
    y_2=120*(1-exp(-t/25))+wf->item28->text().toDouble();//Лобовая часть слева спереди
    y_3=56*(1-exp(-t/25)) +wf->item28->text().toDouble();//Подшипниковый узел слева спереди
    y_4=120*(1-exp(-t/25))+wf->item28->text().toDouble();//Лобовая часть слева сзади
    y_5=90*(1-exp(-t/25)) +wf->item28->text().toDouble();//станина
    y_6=120*(1-exp(-t/25))+wf->item28->text().toDouble();//Лобовая часть справа спереди
    y_7=120*(1-exp(-t/25))+wf->item28->text().toDouble();//Лобовая часть справа сзади
    y_8=90*(1-exp(-t/25)) +wf->item28->text().toDouble();//Магнитопровод статора
    y_9=60*(1-exp(-t/20)) +wf->item28->text().toDouble();//Подшипниковый узел справа спереди
    y_10=56*(1-exp(-t/20))+wf->item28->text().toDouble();//Подшипниковый узел слева сзади
    y_11=80*(1-exp(-t/20))+wf->item28->text().toDouble();//Ротор сверху
    y_12=80*(1-exp(-t/20))+wf->item28->text().toDouble();//Ротор снизу
    y_13=40*(1-exp(-t/20))+wf->item28->text().toDouble();//Станина слева
    y_14=40*(1-exp(-t/20))+wf->item28->text().toDouble();//Станина слева
    y_15=60*(1-exp(-t/20))+wf->item28->text().toDouble();//Вал
    y_16=50*(1-exp(-t/20))+wf->item28->text().toDouble();//Клеммная коробка

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

    wf->ui->widget_6->ui->widget->ui->verticalSlider->setValue(50);
    wf->ui->widget_6->ui->widget->ui->verticalSlider_2->setValue(20);
}


void Trend::stopTeplo()
{
    timer.stop();
}

void Trend::on_timerTimeout()
{
    y_0=20*(1-exp(-t/20)) +wf->item28->text().toDouble();
    y_1=54*(1-exp(-t/20)) +wf->item28->text().toDouble();
    y_2=120*(1-exp(-t/25))+wf->item28->text().toDouble();
    y_3=56*(1-exp(-t/25)) +wf->item28->text().toDouble();
    y_4=120*(1-exp(-t/25))+wf->item28->text().toDouble();
    y_5=90*(1-exp(-t/25)) +wf->item28->text().toDouble();
    y_6=120*(1-exp(-t/25))+wf->item28->text().toDouble();
    y_7=120*(1-exp(-t/25))+wf->item28->text().toDouble();
    y_8=90*(1-exp(-t/25)) +wf->item28->text().toDouble();
    y_9=60*(1-exp(-t/25)) +wf->item28->text().toDouble();
    y_10=56*(1-exp(-t/25))+wf->item28->text().toDouble();
    y_11=80*(1-exp(-t/20))+wf->item28->text().toDouble();
    y_12=80*(1-exp(-t/20))+wf->item28->text().toDouble();
    y_13=40*(1-exp(-t/20))+wf->item28->text().toDouble();
    y_14=40*(1-exp(-t/20))+wf->item28->text().toDouble();
    y_15=60*(1-exp(-t/20))+wf->item28->text().toDouble();
    y_16=50*(1-exp(-t/20))+wf->item28->text().toDouble();

    w_0=314;
    w_w=147;
    M_k=44;
    s_k=0.1;
    s_s=(w_0-w_w)/w_0;
    M_M=M_k*2/(s_s/s_k+s_k/s_s);

    std::ofstream fout;

    fout.open(QString(base.teplFilename).toStdString(),std::ios::out | std::ios::app);

    fout << QString("%1").arg(t).toStdString() << ";";
    fout << QString("%1").arg(y_0).toStdString() << ";";
    fout << QString("%1").arg(y_1).toStdString() << ";";
    fout << QString("%1").arg(y_2).toStdString() << ";";
    fout << QString("%1").arg(y_3).toStdString() << ";";
    fout << QString("%1").arg(y_4).toStdString() << ";";
    fout << QString("%1").arg(y_5).toStdString() << ";";
    fout << QString("%1").arg(y_6).toStdString() << ";";
    fout << QString("%1").arg(y_7).toStdString() << ";";
    fout << QString("%1").arg(y_8).toStdString() << ";";
    fout << QString("%1").arg(y_9).toStdString() << ";";
    fout << QString("%1").arg(y_10).toStdString() << ";";
    fout << QString("%1").arg(y_11).toStdString() << ";";
    fout << QString("%1").arg(y_12).toStdString() << ";";
    fout << QString("%1").arg(y_13).toStdString() << ";";
    fout << QString("%1").arg(y_14).toStdString() << ";";
    fout << QString("%1").arg(y_15).toStdString() << ";";
    fout << QString("%1").arg(y_16).toStdString() << ";";

    fout << std::endl;
    fout.close();


    //Отображение данных в tableWidget_5 Draw Line
    if (wf->ui->tableWidget_5->item(0, 2) != 0)
    {
        wf->ui->tableWidget_5->item(0, 2)->setText(QString("%1").arg(QString::number(y_0,'f',1)));
        wf->ui->tableWidget_5->item(0, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_5->item(1, 2) != 0)
    {
        wf->ui->tableWidget_5->item(1, 2)->setText(QString("%1").arg(QString::number(y_1,'f',1)));
        wf->ui->tableWidget_5->item(1, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_5->item(2, 2) != 0)
    {
        wf->ui->tableWidget_5->item(2, 2)->setText(QString("%1").arg(QString::number(y_2,'f',1)));
        wf->ui->tableWidget_5->item(2, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_5->item(3, 2) != 0)
    {
        wf->ui->tableWidget_5->item(3, 2)->setText(QString("%1").arg(QString::number(y_3,'f',1)));
        wf->ui->tableWidget_5->item(3, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_5->item(4, 2) != 0)
    {
        wf->ui->tableWidget_5->item(4, 2)->setText(QString("%1").arg(QString::number(y_4,'f',1)));
        wf->ui->tableWidget_5->item(4, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_5->item(5, 2) != 0)
    {
        wf->ui->tableWidget_5->item(5, 2)->setText(QString("%1").arg(QString::number(y_5,'f',1)));
        wf->ui->tableWidget_5->item(5, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_5->item(6, 2) != 0)
    {
        wf->ui->tableWidget_5->item(6, 2)->setText(QString("%1").arg(QString::number(y_6,'f',1)));
        wf->ui->tableWidget_5->item(6, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_5->item(7, 2) != 0)
    {
        wf->ui->tableWidget_5->item(7, 2)->setText(QString("%1").arg(QString::number(y_7,'f',1)));
        wf->ui->tableWidget_5->item(7, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_5->item(8, 2) != 0)
    {
        wf->ui->tableWidget_5->item(8, 2)->setText(QString("%1").arg(QString::number(y_8,'f',1)));
        wf->ui->tableWidget_5->item(8, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_5->item(9, 2) != 0)
    {
        wf->ui->tableWidget_5->item(9, 2)->setText(QString("%1").arg(QString::number(y_9,'f',1)));
        wf->ui->tableWidget_5->item(9, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_5->item(10, 2) != 0)
    {
        wf->ui->tableWidget_5->item(10, 2)->setText(QString("%1").arg(QString::number(y_10,'f',1)));
        wf->ui->tableWidget_5->item(10, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_5->item(11, 2) != 0)
    {
        wf->ui->tableWidget_5->item(11, 2)->setText(QString("%1").arg(QString::number(y_11,'f',1)));
        wf->ui->tableWidget_5->item(11, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_5->item(12, 2) != 0)
    {
        wf->ui->tableWidget_5->item(12, 2)->setText(QString("%1").arg(QString::number(y_12,'f',1)));
        wf->ui->tableWidget_5->item(12, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_5->item(13, 2) != 0)
    {
        wf->ui->tableWidget_5->item(13, 2)->setText(QString("%1").arg(QString::number(y_13,'f',1)));
        wf->ui->tableWidget_5->item(13, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_5->item(14, 2) != 0)
    {
        wf->ui->tableWidget_5->item(14, 2)->setText(QString("%1").arg(QString::number(y_14,'f',1)));
        wf->ui->tableWidget_5->item(14, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_5->item(15, 2) != 0)
    {
        wf->ui->tableWidget_5->item(15, 2)->setText(QString("%1").arg(QString::number(y_15,'f',1)));
        wf->ui->tableWidget_5->item(15, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_5->item(16, 2) != 0)
    {
        wf->ui->tableWidget_5->item(16, 2)->setText(QString("%1").arg(QString::number(y_16,'f',1)));
        wf->ui->tableWidget_5->item(16, 2)->setTextAlignment(Qt::AlignCenter);
    }

    //Отображение данных в tableWidget_5 Draw poper
    if (wf->ui->tableWidget_6->item(0, 2) != 0)
    {
        wf->ui->tableWidget_6->item(0, 2)->setText(QString("%1").arg(QString::number(y_11,'f',1)));
        wf->ui->tableWidget_6->item(0, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_6->item(1, 2) != 0)
    {
        wf->ui->tableWidget_6->item(1, 2)->setText(QString("%1").arg(QString::number(y_12,'f',1)));
        wf->ui->tableWidget_6->item(1, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_6->item(2, 2) != 0)
    {
        wf->ui->tableWidget_6->item(2, 2)->setText(QString("%1").arg(QString::number(y_13,'f',1)));
        wf->ui->tableWidget_6->item(2, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_6->item(3, 2) != 0)
    {
        wf->ui->tableWidget_6->item(3, 2)->setText(QString("%1").arg(QString::number(y_14,'f',1)));
        wf->ui->tableWidget_6->item(3, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_6->item(4, 2) != 0)
    {
        wf->ui->tableWidget_6->item(4, 2)->setText(QString("%1").arg(QString::number(y_15,'f',1)));
        wf->ui->tableWidget_6->item(4, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_6->item(5, 2) != 0)
    {
        wf->ui->tableWidget_6->item(5, 2)->setText(QString("%1").arg(QString::number(y_16,'f',1)));
        wf->ui->tableWidget_6->item(5, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_6->item(6, 2) != 0)
    {
        wf->ui->tableWidget_6->item(6, 2)->setText(QString("%1").arg(QString::number(y_8,'f',1)));
        wf->ui->tableWidget_6->item(6, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_6->item(7, 2) != 0)
    {
        wf->ui->tableWidget_6->item(7, 2)->setText(QString("%1").arg(QString::number(y_8,'f',1)));
        wf->ui->tableWidget_6->item(7, 2)->setTextAlignment(Qt::AlignCenter);
    }

    //Считывание коэффициентов
    a0=wf->ui->tableWidget->item(0,4)->text().toDouble();
    a1=wf->ui->tableWidget->item(1,4)->text().toDouble();
    a2=wf->ui->tableWidget->item(2,4)->text().toDouble();
    a3=wf->ui->tableWidget->item(3,4)->text().toDouble();
    a4=wf->ui->tableWidget->item(4,4)->text().toDouble();
    a5=wf->ui->tableWidget->item(5,4)->text().toDouble();
    a6=wf->ui->tableWidget->item(6,4)->text().toDouble();
    a7=wf->ui->tableWidget->item(7,4)->text().toDouble();
    a8=wf->ui->tableWidget->item(8,4)->text().toDouble();
    a9=wf->ui->tableWidget->item(9,4)->text().toDouble();
    a10=wf->ui->tableWidget->item(10,4)->text().toDouble();
    a11=wf->ui->tableWidget->item(11,4)->text().toDouble();
    a12=wf->ui->tableWidget->item(12,4)->text().toDouble();
    a13=wf->ui->tableWidget->item(13,4)->text().toDouble();
    a14=wf->ui->tableWidget->item(14,4)->text().toDouble();
    a15=wf->ui->tableWidget->item(15,4)->text().toDouble();
    a16=wf->ui->tableWidget->item(16,4)->text().toDouble();

    //a0=ui->tableWidget_2->item(0,4)->text().toDouble();
//    a1=ui->tableWidget_2->item(1,4)->text().toDouble();
//    a2=ui->tableWidget_2->item(2,4)->text().toDouble();
//    a3=ui->tableWidget_2->item(3,4)->text().toDouble();
//    a4=ui->tableWidget_2->item(4,4)->text().toDouble();
//    a5=ui->tableWidget_2->item(5,4)->text().toDouble();
//    a6=ui->tableWidget_2->item(6,4)->text().toDouble();
//    a7=ui->tableWidget_2->item(7,4)->text().toDouble();
//    a8=ui->tableWidget_2->item(8,4)->text().toDouble();
//    a9=ui->tableWidget_2->item(9,4)->text().toDouble();
//    a10=ui->tableWidget_2->item(10,4)->text().toDouble();
//    a11=ui->tableWidget_2->item(11,4)->text().toDouble();
//    a12=ui->tableWidget_2->item(12,4)->text().toDouble();
//    a13=ui->tableWidget_2->item(9,4)->text().toDouble();
//    a14=ui->tableWidget_2->item(10,4)->text().toDouble();
//    a15=ui->tableWidget_2->item(11,4)->text().toDouble();
//    a16=ui->tableWidget_2->item(12,4)->text().toDouble();

    b0=wf->ui->tableWidget->item(0,3)->text().toDouble();
    b1=wf->ui->tableWidget->item(1,3)->text().toDouble();
    b2=wf->ui->tableWidget->item(2,3)->text().toDouble();
    b3=wf->ui->tableWidget->item(3,3)->text().toDouble();
    b4=wf->ui->tableWidget->item(4,3)->text().toDouble();
    b5=wf->ui->tableWidget->item(5,3)->text().toDouble();
    b6=wf->ui->tableWidget->item(6,3)->text().toDouble();
    b7=wf->ui->tableWidget->item(7,3)->text().toDouble();
    b8=wf->ui->tableWidget->item(8,3)->text().toDouble();
    b9=wf->ui->tableWidget->item(9,3)->text().toDouble();
    b10=wf->ui->tableWidget->item(10,3)->text().toDouble();
    b11=wf->ui->tableWidget->item(11,3)->text().toDouble();
    b12=wf->ui->tableWidget->item(12,3)->text().toDouble();
    b13=wf->ui->tableWidget->item(13,3)->text().toDouble();
    b14=wf->ui->tableWidget->item(14,3)->text().toDouble();
    b15=wf->ui->tableWidget->item(15,3)->text().toDouble();
    b16=wf->ui->tableWidget->item(16,3)->text().toDouble();

//    b0=ui->tableWidget_2->item(0,5)->text().toDouble();
//    b1=ui->tableWidget_2->item(1,5)->text().toDouble();
//    b2=ui->tableWidget_2->item(2,5)->text().toDouble();
//    b3=ui->tableWidget_2->item(3,5)->text().toDouble();
//    b4=ui->tableWidget_2->item(4,5)->text().toDouble();
//    b5=ui->tableWidget_2->item(5,5)->text().toDouble();
//    b6=ui->tableWidget_2->item(6,5)->text().toDouble();
//    b7=ui->tableWidget_2->item(7,5)->text().toDouble();
//    b8=ui->tableWidget_2->item(8,5)->text().toDouble();
//    b9=ui->tableWidget_2->item(9,5)->text().toDouble();
//    b10=ui->tableWidget_2->item(10,5)->text().toDouble();
//    b11=ui->tableWidget_2->item(11,5)->text().toDouble();
//    b12=ui->tableWidget_2->item(12,5)->text().toDouble();
//    b13=ui->tableWidget_2->item(9,5)->text().toDouble();
//    b14=ui->tableWidget_2->item(10,5)->text().toDouble();
//    b15=ui->tableWidget_2->item(11,5)->text().toDouble();
//    b16=ui->tableWidget_2->item(12,5)->text().toDouble();

    if(wf->ui->tableWidget->model()->index(0,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(0, t, b0+a0*y_0);
    }

    if(wf->ui->tableWidget->model()->index(1,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(1, t, b1+a1*y_1);
    }

    if(wf->ui->tableWidget->model()->index(2,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(2, t, b2+a2*y_2);
    }

    if(wf->ui->tableWidget->model()->index(3,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(3, t, b3+a3*y_3);
    }

    if(wf->ui->tableWidget->model()->index(4,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(4, t, b4+a4*y_4);
    }

    if(wf->ui->tableWidget->model()->index(5,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(5, t, b5+a5*y_5);
    }

    if(wf->ui->tableWidget->model()->index(6,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(6, t, b6+a6*y_6);
    }

    if(wf->ui->tableWidget->model()->index(7,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(7, t, b7+a7*y_7);
    }

    if(wf->ui->tableWidget->model()->index(8,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(8, t, b8+a8*y_8);
    }

    if(wf->ui->tableWidget->model()->index(9,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(9, t, b9+a9*y_9);
    }

    if(wf->ui->tableWidget->model()->index(10,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(10, t, b10+a10*y_10);
    }

    if(wf->ui->tableWidget->model()->index(11,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(11, t, b11+a11*y_11);
    }

    if(wf->ui->tableWidget->model()->index(12,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(12, t, b12+a12*y_12);
    }

    if(wf->ui->tableWidget->model()->index(13,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(13, t, b13+a13*y_13);
    }

    if(wf->ui->tableWidget->model()->index(14,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(14, t, b14+a14*y_14);
    }

    if(wf->ui->tableWidget->model()->index(15,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(15, t, b15+a15*y_15);
    }

    if(wf->ui->tableWidget->model()->index(16,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(16, t, b16+a16*y_16);
    }

    t += 1.0;

    //запись измеренных температур в tablewidget_3
    if (wf->ui->tableWidget_3->item(0, 2) != 0)
    {
        wf->ui->tableWidget_3->item(0, 2)->setText(QString("%1").arg(QString::number(b0+a0*y_0,'f',1)));
        wf->ui->tableWidget_3->item(0, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_3->item(1, 2) != 0)
    {
        wf->ui->tableWidget_3->item(1, 2)->setText(QString("%1").arg(QString::number(b1+a1*y_1,'f',1)));
        wf->ui->tableWidget_3->item(1, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_3->item(2, 2) != 0)
    {
        wf->ui->tableWidget_3->item(2, 2)->setText(QString("%1").arg(QString::number(b2+a2*y_2,'f',1)));
        wf->ui->tableWidget_3->item(2, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_3->item(3, 2) != 0)
    {
        wf->ui->tableWidget_3->item(3, 2)->setText(QString("%1").arg(QString::number(b3+a3*y_3,'f',1)));
        wf->ui->tableWidget_3->item(3, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_3->item(4, 2) != 0)
    {
        wf->ui->tableWidget_3->item(4, 2)->setText(QString("%1").arg(QString::number(b4+a4*y_4,'f',1)));
        wf->ui->tableWidget_3->item(4, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_3->item(5, 2) != 0)
    {
        wf->ui->tableWidget_3->item(5, 2)->setText(QString("%1").arg(QString::number(b5+a5*y_5,'f',1)));
        wf->ui->tableWidget_3->item(5, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_3->item(6, 2) != 0)
    {
        wf->ui->tableWidget_3->item(6, 2)->setText(QString("%1").arg(QString::number(b6+a6*y_6,'f',1)));
        wf->ui->tableWidget_3->item(6, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_3->item(7, 2) != 0)
    {
        wf->ui->tableWidget_3->item(7, 2)->setText(QString("%1").arg(QString::number(b7+a7*y_7,'f',1)));
        wf->ui->tableWidget_3->item(7, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_3->item(8, 2) != 0)
    {
        wf->ui->tableWidget_3->item(8, 2)->setText(QString("%1").arg(QString::number(b8+a8*y_8,'f',1)));
        wf->ui->tableWidget_3->item(8, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_3->item(9, 2) != 0)
    {
        wf->ui->tableWidget_3->item(9, 2)->setText(QString("%1").arg(QString::number(b9+a9*y_9,'f',1)));
        wf->ui->tableWidget_3->item(9, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_3->item(10, 2) != 0)
    {
        wf->ui->tableWidget_3->item(10, 2)->setText(QString("%1").arg(QString::number(b10+a10*y_10,'f',1)));
        wf->ui->tableWidget_3->item(10, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_3->item(11, 2) != 0)
    {
        wf->ui->tableWidget_3->item(11, 2)->setText(QString("%1").arg(QString::number(b11+a11*y_11,'f',1)));
        wf->ui->tableWidget_3->item(11, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_3->item(12, 2) != 0)
    {
        wf->ui->tableWidget_3->item(12, 2)->setText(QString("%1").arg(QString::number(b12+a12*y_12,'f',1)));
        wf->ui->tableWidget_3->item(12, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_3->item(13, 2) != 0)
    {
        wf->ui->tableWidget_3->item(13, 2)->setText(QString("%1").arg(QString::number(b13+a13*y_13,'f',1)));
        wf->ui->tableWidget_3->item(13, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_3->item(14, 2) != 0)
    {
        wf->ui->tableWidget_3->item(14, 2)->setText(QString("%1").arg(QString::number(b14+a14*y_14,'f',1)));
        wf->ui->tableWidget_3->item(14, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_3->item(15, 2) != 0)
    {
        wf->ui->tableWidget_3->item(15, 2)->setText(QString("%1").arg(QString::number(b15+a15*y_15,'f',1)));
        wf->ui->tableWidget_3->item(15, 2)->setTextAlignment(Qt::AlignCenter);
    }

    if (wf->ui->tableWidget_3->item(16, 2) != 0)
    {
        wf->ui->tableWidget_3->item(16, 2)->setText(QString("%1").arg(QString::number(b16+a16*y_16,'f',1)));
        wf->ui->tableWidget_3->item(16, 2)->setTextAlignment(Qt::AlignCenter);
    }


//    if (ui->tableWidget->item(0, 2) != 0)
//    {
//        ui->tableWidget->item(0, 2)->setText(QString("%1").arg(QString::number(b0+a0*y_0,'f',1)));
//        ui->tableWidget->item(0, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (ui->tableWidget->item(1, 2) != 0)
//    {
//        ui->tableWidget->item(1, 2)->setText(QString("%1").arg(QString::number(b1+a1*y_1,'f',1)));
//        ui->tableWidget->item(1, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (ui->tableWidget->item(2, 2) != 0)
//    {
//        ui->tableWidget->item(2, 2)->setText(QString("%1").arg(QString::number(b2+a2*y_2,'f',1)));
//        ui->tableWidget->item(2, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (ui->tableWidget->item(3, 2) != 0)
//    {
//        ui->tableWidget->item(3, 2)->setText(QString("%1").arg(QString::number(b3+a3*y_3,'f',1)));
//        ui->tableWidget->item(3, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (ui->tableWidget->item(4, 2) != 0)
//    {
//        ui->tableWidget->item(4, 2)->setText(QString("%1").arg(QString::number(b4+a4*y_4,'f',1)));
//        ui->tableWidget->item(4, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (ui->tableWidget->item(5, 2) != 0)
//    {
//        ui->tableWidget->item(5, 2)->setText(QString("%1").arg(QString::number(b5+a5*y_5,'f',1)));
//        ui->tableWidget->item(5, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (ui->tableWidget->item(6, 2) != 0)
//    {
//        ui->tableWidget->item(6, 2)->setText(QString("%1").arg(QString::number(b6+a6*y_6,'f',1)));
//        ui->tableWidget->item(6, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (ui->tableWidget->item(7, 2) != 0)
//    {
//        ui->tableWidget->item(7, 2)->setText(QString("%1").arg(QString::number(b7+a7*y_7,'f',1)));
//        ui->tableWidget->item(7, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (ui->tableWidget->item(8, 2) != 0)
//    {
//        ui->tableWidget->item(8, 2)->setText(QString("%1").arg(QString::number(b8+a8*y_8,'f',1)));
//        ui->tableWidget->item(8, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (ui->tableWidget->item(9, 2) != 0)
//    {
//        ui->tableWidget->item(9, 2)->setText(QString("%1").arg(QString::number(b9+a9*y_9,'f',1)));
//        ui->tableWidget->item(9, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (ui->tableWidget->item(10, 2) != 0)
//    {
//        ui->tableWidget->item(10, 2)->setText(QString("%1").arg(QString::number(b10+a10*y_10,'f',1)));
//        ui->tableWidget->item(10, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (ui->tableWidget->item(11, 2) != 0)
//    {
//        ui->tableWidget->item(11, 2)->setText(QString("%1").arg(QString::number(b11+a11*y_11,'f',1)));
//        ui->tableWidget->item(11, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (ui->tableWidget->item(12, 2) != 0)
//    {
//        ui->tableWidget->item(12, 2)->setText(QString("%1").arg(QString::number(b12+a12*y_12,'f',1)));
//        ui->tableWidget->item(12, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (ui->tableWidget->item(13, 2) != 0)
//    {
//        ui->tableWidget->item(13, 2)->setText(QString("%1").arg(QString::number(b13+a13*y_13,'f',1)));
//        ui->tableWidget->item(13, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (ui->tableWidget->item(14, 2) != 0)
//    {
//        ui->tableWidget->item(14, 2)->setText(QString("%1").arg(QString::number(b14+a14*y_14,'f',1)));
//        ui->tableWidget->item(14, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (ui->tableWidget->item(15, 2) != 0)
//    {
//        ui->tableWidget->item(15, 2)->setText(QString("%1").arg(QString::number(b15+a15*y_15,'f',1)));
//        ui->tableWidget->item(15, 2)->setTextAlignment(Qt::AlignCenter);
//    }

//    if (ui->tableWidget->item(16, 2) != 0)
//    {
//        ui->tableWidget->item(16, 2)->setText(QString("%1").arg(QString::number(b16+a16*y_16,'f',1)));
//        ui->tableWidget->item(16, 2)->setTextAlignment(Qt::AlignCenter);
//    }

   // Расчет значений цветов

   int color_0 = 225 - (y_0 - wf->item28->text().toDouble()) / (140.0 - wf->item28->text().toDouble()) * 220.0;
//    ui->label->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_0));

    int color_1 = 225 - (y_1 - wf->item28->text().toDouble()) / (140.0 - wf->item28->text().toDouble()) * 220.0;
//    ui->label_4->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_1));

    int color_2 = 225 - (y_2 - wf->item28->text().toDouble()) / (140.0 - wf->item28->text().toDouble()) * 220.0;
//    ui->label_5->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_2));

   int color_3 = 225 - (y_3 - wf->item28->text().toDouble()) / (140.0 - wf->item28->text().toDouble()) * 220.0;
//    ui->label_6->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_3));

    int color_4 = 225 - (y_4 - wf->item28->text().toDouble()) / (140.0 - wf->item28->text().toDouble()) * 220.0;
//    ui->label_7->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_4));

    int color_5 = 225 - (y_5 - wf->item28->text().toDouble()) / (140.0 - wf->item28->text().toDouble()) * 220.0;
//    ui->label_8->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_5));

    int color_6 = 225 - (y_6 - wf->item28->text().toDouble()) / (140.0 - wf->item28->text().toDouble()) * 220.0;
//    ui->label_9->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_6));

    int color_7 = 225 - (y_7 - wf->item28->text().toDouble()) / (140.0 - wf->item28->text().toDouble()) * 220.0;
//    ui->label_10->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_7));

    int color_8 = 225 - (y_8 - wf->item28->text().toDouble()) / (140.0 - wf->item28->text().toDouble()) * 220.0;
//    ui->label_11->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_8));

    int color_9 = 225 - (y_9 - wf->item28->text().toDouble()) / (140.0 - wf->item28->text().toDouble()) * 220.0;
//    ui->label_12->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_9));

    int color_10 = 225 - (y_10 - wf->item28->text().toDouble()) / (140.0 - wf->item28->text().toDouble()) * 220.0;
//    ui->label_13->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_10));

    int color_11 = 225 - (y_11 - wf->item28->text().toDouble()) / (140.0 - wf->item28->text().toDouble()) * 220.0;
//    ui->label_14->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_11));

    int color_12 = 225 - (y_12 - wf->item28->text().toDouble()) / (140.0 - wf->item28->text().toDouble()) * 220.0;
//    ui->label_2->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_12));

    int color_13 = 225 - (y_13 - wf->item28->text().toDouble()) / (140.0 - wf->item28->text().toDouble()) * 220.0;
//    ui->label_17->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_13));

   int color_14 = 225 - (y_14 - wf->item28->text().toDouble()) / (140.0 - wf->item28->text().toDouble()) * 220.0;
//    ui->label_18->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_14));

    int color_15 = 225 - (y_15 - wf->item28->text().toDouble()) / (140.0 - wf->item28->text().toDouble()) * 220.0;
//    ui->label_19->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_15));

    int color_16 = 225 - (y_16 - wf->item28->text().toDouble()) / (140.0 - wf->item28->text().toDouble()) * 220.0;
//    ui->label_20->setStyleSheet(QString("background-color: hsl(%1, 100%, 50%)").arg(color_16));


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

    wf->ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text255').text('%1 °C');").arg(y_8, 0, 'f', 1));



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

            double miny=wf->item28->text().toDouble();
           //double miny=20.0;
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
