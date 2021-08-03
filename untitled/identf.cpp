#include "identf.h"
#include "ui_identf.h"
#include "model.h"
#include "base.h"

#include <iostream>
#include <fstream>
#include <cfloat>
#include <QLinearGradient>

double key;
//Model model;
const double R1=2.419;
int count = 0;
static double minR2, maxR2, middleR2;
//double P_nom, n_nom, U_fnom, cosf_nom, kpd_nom, muk, n_0;

identf::identf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::identf)
{
    ui->setupUi(this);
    ui->widget->t_max = 0.1;
    ui->widget->U_max = 800.0;
    ui->widget->margin_bottom = 40;
    ui->widget->margin_left = 100;
    ui->widget->reset();


    //dataTimer = new QTimer(this);
    time=new QElapsedTimer();
    ui->widget->setMaximumSize(ui->widget->maximumWidth(), ui->widget->maximumHeight());

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
//    key = time->elapsed()/1000.0; // time elapsed since start of demo, in seconds
//    static double lastPointKey = 0;

//    model.rasch(dataSource);

//       if (model.R2 > maxR2)
//           {
//               maxR2 = model.R2;
//           }

//           if (model.R2 < minR2)
//           {
//               minR2 = model.R2;
//           }

//           middleR2 += model.R2;
//           count++;

//   if (count == 10000)
//   {
//       middleR2 /= count;

//       count = 0;
//       //printf("%f\n", fabs((maxR2 - minR2)/middleR2));
//       if (fabs((maxR2 - minR2)/middleR2) < 0.06)
//       {
//            dataSource->stop();
//            QMessageBox::information(this, tr("Сообщение"), tr("Расчет окончен!"));
//       }
//       minR2 = DBL_MAX;
//       maxR2 = -DBL_MAX;
//       middleR2 = 0.0;
//   }

//   if (count % 100 == 0)
//   {
//        ui->widget->graph(0)->addData(key, model.R2);
//        ui->widget->graph(1)->addData(key, model.L);
//        ui->widget->graph(2)->addData(key, model.Lm);

//   //  ui->label->setText(QString::number(key));
//        ui->lineEdit_8->setText(QString::number(model.Lm));
//        ui->lineEdit_9->setText(QString::number(model.L));
//        ui->lineEdit_10->setText(QString::number(model.L));
//        ui->lineEdit_11->setText(QString::number(model.R2));
//        ui->lineEdit_12->setText(QString::number(R1));
//      // rescale value (vertical) axis to fit the current data:
//        ui->widget->graph(0)->rescaleValueAxis();
//        ui->widget->graph(1)->rescaleValueAxis(true);
//        lastPointKey = key;
//    //}
//    // make key axis range scroll with the data (at a constant range size of 8):
//    ui->widget->xAxis->setRange(key, 8, Qt::AlignRight);
//    ui->widget->replot();
//    }
}

void identf::raschet_f()
{
//    minR2 = DBL_MAX;
//    maxR2 = -DBL_MAX;
//    middleR2 = 0.0;

//    ui->lineEdit->setText(QString("%1").arg(base.P_nom));
//    ui->lineEdit_2->setText(QString("%1").arg(base.n_nom));
//    ui->lineEdit_3->setText(QString("%1").arg(base.U_fnom));
//    ui->lineEdit_4->setText(QString("%1").arg(base.cosf_nom));
//    ui->lineEdit_5->setText(QString("%1").arg(base.kpd_nom));
//    ui->lineEdit_6->setText(QString("%1").arg(base.muk));
//    ui->lineEdit_7->setText(QString("%1").arg(base.n_0));
//    dataSource->init();
//    model.init(base.P_nom, base.n_nom, base.U_fnom, base.cosf_nom, base.kpd_nom, base.muk, base.n_0);
//    ui->widget->graph(0)->data()->clear();
//    ui->widget->graph(1)->data()->clear();
//    ui->widget->graph(2)->data()->clear();
//    ui->widget->replot();
//    time->start();
}


void identf::on_pushButton_clicked()
{
    base.R1 = ui->lineEdit_12->text().toDouble();
    base.R2 = ui->lineEdit_11->text().toDouble();
    base.L1 = ui->lineEdit_10->text().toDouble();
    base.L2 = ui->lineEdit_9->text().toDouble();
    base.Lm = ui->lineEdit_8->text().toDouble();
    printf("R1=%f R2=%f L1=%f L2=%f Lm=%f", base.R1, base.R2, base.L1, base.L2, base.Lm);
 }
