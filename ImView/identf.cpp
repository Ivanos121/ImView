#include "ui_mainwindow.h"
#include "ui_datas.h"
#include "identf.h"
#include "ui_identf.h"
#include "model.h"
#include "plot.h"
#include "base.h"

#include <iostream>
#include <fstream>
#include <cfloat>
#include <QLinearGradient>
#include <QColorDialog>

double key;
Model model;
Modell modell;
const double R1=2.419;
int count = 0;
static double minR2, maxR2, middleR2;
//double P_nom, n_nom, U_fnom, cosf_nom, kpd_nom, muk, n_0;

identf::identf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::identf)
{
    ui->setupUi(this);
    ui->plot->t_max = 10.0;
    ui->plot->U_max = 3.0;
    ui->plot->margin_bottom = 40;
    ui->plot->margin_left = 100;
    ui->plot->reset();

    //dataTimer = new QTimer(this);
    time=new QElapsedTimer();
    //ui->widget->setMaximumSize(ui->widget->maximumWidth(), ui->widget->maximumHeight());

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
   //connect(dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));

    //dataSource = new DataSource();
    //connect(dataSource, &DataSource::ready, this, &identf::realtimeDataSlot);

    this->showMaximized();

    ui->lineEdit_8->setReadOnly(true);
    ui->lineEdit_9->setReadOnly(true);
    ui->lineEdit_10->setReadOnly(true);
    ui->lineEdit_11->setReadOnly(true);
    ui->lineEdit_12->setReadOnly(true);

    ui->lineEdit_8->setAlignment(Qt::AlignCenter);
    ui->lineEdit_9->setAlignment(Qt::AlignCenter);
    ui->lineEdit_10->setAlignment(Qt::AlignCenter);
    ui->lineEdit_11->setAlignment(Qt::AlignCenter);
    ui->lineEdit_12->setAlignment(Qt::AlignCenter);
    ui->lineEdit_13->setAlignment(Qt::AlignCenter);
    ui->lineEdit_14->setAlignment(Qt::AlignCenter);
    ui->lineEdit_15->setAlignment(Qt::AlignCenter);
    ui->lineEdit_16->setAlignment(Qt::AlignCenter);
    ui->lineEdit_17->setAlignment(Qt::AlignCenter);
    ui->lineEdit_18->setAlignment(Qt::AlignCenter);

    ui->buttonGroup->setId(ui->radioButton,1);
    ui->buttonGroup->setId(ui->radioButton_2,2);

    if (ui->buttonGroup->checkedId() == 1)
    {
        ui->lineEdit_13->setEnabled(false);
        ui->lineEdit_14->setEnabled(false);
        ui->lineEdit_15->setEnabled(false);
        ui->lineEdit_16->setEnabled(false);
        ui->lineEdit_17->setEnabled(false);
        ui->lineEdit_18->setEnabled(false);
    }

    ui->lineEdit_13->setValidator(new QRegExpValidator(QRegExp("^[0-9]{1}.[0-9]{3}$")));
    ui->lineEdit_14->setValidator(new QRegExpValidator(QRegExp("^[0-9]{1}.[0-9]{3}$")));
    ui->lineEdit_15->setValidator(new QRegExpValidator(QRegExp("^[0-9]{1}.[0-9]{3}$")));
    ui->lineEdit_16->setValidator(new QRegExpValidator(QRegExp("^[0-9]{1}.[0-9]{3}$")));
    ui->lineEdit_17->setValidator(new QRegExpValidator(QRegExp("^[0-9]{1}.[0-9]{3}$")));
    ui->lineEdit_18->setValidator(new QRegExpValidator(QRegExp("^[0-9]{1}.[0-9]{3}$")));
}

identf::~identf()
{
    delete ui;
}

void identf::realtimeDataSlot()
{
    // calculate two new data points:
    key = time->elapsed()/1000.0; // time elapsed since start of demo, in seconds

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

   if (count == 3)
   {
       middleR2 /= count;

       count = 0;

       if (fabs((maxR2 - minR2)/middleR2) < 0.006)
       {
            dataSource->stop();
            wf->ui->action_9->setEnabled(false);
            wf->ui->action_5->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-start_2.svg"));
            QMessageBox::information(this, tr("Сообщение"), tr("Расчет окончен!"));
       }
       minR2 = DBL_MAX;
       maxR2 = -DBL_MAX;
       middleR2 = 0.0;
   }

   //if (count % 100 == 0)
   if (true)
   {
        ui->plot->addPoint(0, key, model.R2);
        ui->plot->addPoint(1, key, model.L);
        ui->plot->addPoint(2, key, model.L);
        ui->plot->addPoint(3, key, model.Lm);

        ui->lineEdit_8->setText(QString::number(model.Lm,'f',3));
        ui->lineEdit_9->setText(QString::number(model.L,'f',3));
        ui->lineEdit_10->setText(QString::number(model.L,'f',3));
        ui->lineEdit_11->setText(QString::number(model.R2,'f',3));
        ui->lineEdit_12->setText(QString::number(R1));

        //   printf("%f %f %f\n", model.R2, model.L, model.Lm);

    }
}

void identf::raschet_f()
{
    minR2 = DBL_MAX;
    maxR2 = -DBL_MAX;
    middleR2 = 0.0;

   // auto uiDatasWindow = wf->ui->widget->ui;

    //Режим Осциллограф
    if(wf->item88->text() == "Осциллограф")
    {
        dataSource = new DataSourceBVAS();
        connect(dataSource, &DataSource::ready, this, &identf::realtimeDataSlot);
    }

    //Режим Внутренний источник данных
    if (wf->item88->text() == "Внутренний источник данных")
    {
        dataSource = new DataSource_el(base.P_nom, base.n_nom, base.U_fnom, base.cosf_nom, base.kpd_nom, base.muk, base.n_0);
        connect(dataSource, &DataSource::ready, this, &identf::realtimeDataSlot);
    }

    if(wf->item88->text() == "Чтение данных из файла для идентификации параметров схемы замещения")
    {
        QString dataSourceFileName = wf->item106->text();
        base.dataSourceFilename = dataSourceFileName;
        dataSource = new DataSource_file();
        connect(dataSource, &DataSource::ready, this, &identf::realtimeDataSlot);
    }

    dataSource->init();
    model.init(base.P_nom, base.n_nom, base.U_fnom, base.cosf_nom, base.kpd_nom, base.muk, base.n_0,
               ui->lineEdit_13->text().toDouble(),ui->lineEdit_14->text().toDouble(),ui->lineEdit_15->text().toDouble(),
               ui->lineEdit_16->text().toDouble(),ui->lineEdit_17->text().toDouble(),ui->lineEdit_18->text().toDouble());
    ui->plot->clear();
    for (int i = 0; i < wf->graph_Settings->dataLineColors.size(); i++)
    {
        ui->plot->addDataLine(wf->graph_Settings->dataLineColors[i], 0);
    }

    ui->plot->addPoint(0, 0, model.R2);
    ui->plot->addPoint(1, 0, model.L);
    ui->plot->addPoint(2, 0, model.L);
    ui->plot->addPoint(3, 0, model.Lm);

    ui->lineEdit_8->setText(QString::number(model.Lm,'f',3));
    ui->lineEdit_9->setText(QString::number(model.L,'f',3));
    ui->lineEdit_10->setText(QString::number(model.L,'f',3));
    ui->lineEdit_11->setText(QString::number(model.R2,'f',3));
    ui->lineEdit_12->setText(QString::number(R1));

    time->start();
}


void identf::on_pushButton_clicked()
{
    if(ui->lineEdit_12->text().isEmpty() || ui->lineEdit_11->text().isEmpty()
            || ui->lineEdit_10->text().isEmpty() || ui->lineEdit_9->text().isEmpty() || ui->lineEdit_8->text().isEmpty())
    {
        QMessageBox::critical(this, "Ошибка!", "Заполните пустые поля");
    }
    base.R1 = ui->lineEdit_12->text().toDouble();
    base.R2 = ui->lineEdit_11->text().toDouble();
    base.L1 = ui->lineEdit_10->text().toDouble();
    base.L2 = ui->lineEdit_9->text().toDouble();
    base.Lm = ui->lineEdit_8->text().toDouble();
 }

void identf::on_radioButton_2_toggled(bool checked)
{
    if (checked)
    {
        ui->lineEdit_13->setEnabled(true);
        ui->lineEdit_14->setEnabled(true);
        ui->lineEdit_15->setEnabled(true);
        ui->lineEdit_16->setEnabled(true);
        ui->lineEdit_17->setEnabled(true);
        ui->lineEdit_18->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
    }
}

void identf::on_radioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->lineEdit_13->setEnabled(false);
        ui->lineEdit_14->setEnabled(false);
        ui->lineEdit_15->setEnabled(false);
        ui->lineEdit_16->setEnabled(false);
        ui->lineEdit_17->setEnabled(false);
        ui->lineEdit_18->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
    }
}

void identf::on_pushButton_2_clicked()
{
    if(ui->lineEdit_13->text().isEmpty() || ui->lineEdit_14->text().isEmpty()
            || ui->lineEdit_15->text().isEmpty() || ui->lineEdit_16->text().isEmpty() || ui->lineEdit_17->text().isEmpty()
            || ui->lineEdit_18->text().isEmpty())
    {
        QMessageBox::critical(this, "Ошибка!", "Заполните пустые поля");
    }
}

