#include "identf.h"
#include "ui_identf.h"
#include "model.h"
#include "base.h"

#include <iostream>
#include <fstream>
#include <cfloat>
#include <QLinearGradient>

double key;
Model model;
const double R1=2.419;
int count = 0;
static double minR2, maxR2, middleR2;
//double P_nom, n_nom, U_fnom, cosf_nom, kpd_nom, muk, n_0;

identf::identf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::identf)
{
    ui->setupUi(this);
    ui->widget->setBufferDevicePixelRatio(.5);


    //dataTimer = new QTimer(this);
    time=new QElapsedTimer();
    ui->widget->setMaximumSize(ui->widget->maximumWidth(), ui->widget->maximumHeight());;
    ui->widget->setOpenGl(true);

    ui->widget->legend->setVisible(true);
    ui->widget->legend->setFont(QFont("Hevlrtika",9));
    ui->widget->setLocale(QLocale(QLocale::Russian, QLocale::Russia));
    ui->widget->clearGraphs();
    ui->widget->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);

    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    ui->widget->setBackground(plotGradient);

    ui->widget->addGraph(); // blue line
    ui->widget->graph(0)->setName("Идентификация сопротивления ротора R2");
    ui->widget->graph(0)->setPen(QPen(Qt::red, 1));
    ui->widget->addGraph(); // red line
    ui->widget->graph(1)->setName("Идентификация индуктивности фазы L1 и l2");
    ui->widget->graph(1)->setPen(QPen(Qt::green, 1));
    ui->widget->addGraph(); // red line
    ui->widget->graph(2)->setName("Идентификация межфазной индуктивности фазы Lm");
    ui->widget->graph(2)->setPen(QPen(Qt::cyan, 1));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->widget->xAxis->setTicker(timeTicker);
    ui->widget->xAxis->setBasePen(QPen(Qt::white, 4));
    ui->widget->yAxis->setBasePen(QPen(Qt::white, 4));
    ui->widget->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->widget->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->widget->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->widget->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->widget->xAxis->setTickLabelColor(Qt::white);
    ui->widget->yAxis->setTickLabelColor(Qt::white);
    ui->widget->xAxis->grid()->setVisible(true);
    ui->widget->xAxis->grid()->setSubGridVisible(true);
    ui->widget->xAxis->grid()->setAntialiased(true);
    ui->widget->xAxis->grid()->setAntialiasedSubGrid(true);
    ui->widget->yAxis->setRange(-1.2, 1.2);
    ui->widget->xAxis->grid()->setPen(QPen(Qt::white, 1, Qt::SolidLine));
    ui->widget->xAxis->grid()->setSubGridPen(QPen(Qt::white, 0.5, Qt::DotLine));
    ui->widget->yAxis->grid()->setVisible(true);
    ui->widget->yAxis->grid()->setSubGridVisible(true);
    ui->widget->yAxis->grid()->setAntialiased(true);
    ui->widget->yAxis->grid()->setAntialiasedSubGrid(true);
    ui->widget->yAxis->grid()->setPen(QPen(Qt::white, 1, Qt::SolidLine));
    ui->widget->yAxis->grid()->setSubGridPen(QPen(Qt::white, 0.5, Qt::DotLine));

    ui->widget->xAxis2->setBasePen(QPen(Qt::white, 4));
    ui->widget->yAxis2->setBasePen(QPen(Qt::white, 4));
    ui->widget->xAxis2->setTickPen(QPen(Qt::white, 1));
    ui->widget->yAxis2->setTickPen(QPen(Qt::white, 1));
    ui->widget->xAxis2->setSubTickPen(QPen(Qt::white, 1));
    ui->widget->yAxis2->setSubTickPen(QPen(Qt::white, 1));
    ui->widget->xAxis2->setTickLabelColor(Qt::white);
    ui->widget->yAxis2->setTickLabelColor(Qt::white);
    ui->widget->yAxis2->grid()->setVisible(true);
    ui->widget->yAxis2->grid()->setSubGridVisible(true);
    ui->widget->yAxis2->grid()->setAntialiased(true);
    ui->widget->yAxis2->grid()->setAntialiasedSubGrid(true);
    ui->widget->yAxis2->grid()->setPen(QPen(Qt::white, 1, Qt::SolidLine));
    ui->widget->yAxis2->grid()->setSubGridPen(QPen(Qt::white, 0.5, Qt::DotLine));
    ui->widget->axisRect()->setupFullAxesBox();

    connect(ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
   //connect(dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));

    dataSource = new DataSource();
    connect(dataSource, &DataSource::ready, this, &identf::realtimeDataSlot);

    this->showMaximized();
}

identf::~identf()
{
    delete ui;
}

void identf::realtimeDataSlot()
{
    // calculate two new data points:
    key = time->elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;

    model.rasch(dataSource);

       if (model.R2 > maxR2)
           {
               maxR2 = model.R2;
           }

           if (model.R2 < minR2)
           {
               minR2 = model.R2;
           }

           middleR2 += model.R2;
           count++;

   if (count == 10000)
   {
       middleR2 /= count;

       count = 0;
       //printf("%f\n", fabs((maxR2 - minR2)/middleR2));
       if (fabs((maxR2 - minR2)/middleR2) < 0.06)
       {
            dataSource->stop();
            QMessageBox::information(this, tr("Сообщение"), tr("Расчет окончен!"));
       }
       minR2 = DBL_MAX;
       maxR2 = -DBL_MAX;
       middleR2 = 0.0;
   }

   if (count % 100 == 0)
   {
        ui->widget->graph(0)->addData(key, model.R2);
        ui->widget->graph(1)->addData(key, model.L);
        ui->widget->graph(2)->addData(key, model.Lm);

   //  ui->label->setText(QString::number(key));
        ui->lineEdit_8->setText(QString::number(model.Lm));
        ui->lineEdit_9->setText(QString::number(model.L));
        ui->lineEdit_10->setText(QString::number(model.L));
        ui->lineEdit_11->setText(QString::number(model.R2));
        ui->lineEdit_12->setText(QString::number(R1));
      // rescale value (vertical) axis to fit the current data:
        ui->widget->graph(0)->rescaleValueAxis();
        ui->widget->graph(1)->rescaleValueAxis(true);
        lastPointKey = key;
    //}
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->widget->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->widget->replot();
    }
}

void identf::raschet_f()
{
    minR2 = DBL_MAX;
    maxR2 = -DBL_MAX;
    middleR2 = 0.0;

    ui->lineEdit->setText(QString("%1").arg(base.P_nom));
    ui->lineEdit_2->setText(QString("%1").arg(base.n_nom));
    ui->lineEdit_3->setText(QString("%1").arg(base.U_fnom));
    ui->lineEdit_4->setText(QString("%1").arg(base.cosf_nom));
    ui->lineEdit_5->setText(QString("%1").arg(base.kpd_nom));
    ui->lineEdit_6->setText(QString("%1").arg(base.muk));
    ui->lineEdit_7->setText(QString("%1").arg(base.n_0));
    dataSource->init();
    model.init(base.P_nom, base.n_nom, base.U_fnom, base.cosf_nom, base.kpd_nom, base.muk, base.n_0);
    ui->widget->graph(0)->data()->clear();
    ui->widget->graph(1)->data()->clear();
    ui->widget->graph(2)->data()->clear();
    ui->widget->replot();
    time->start();
}

