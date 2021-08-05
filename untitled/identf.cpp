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

    dataSource = new DataSource();
    connect(dataSource, &DataSource::ready, this, &identf::realtimeDataSlot);

    this->showMaximized();

    ui->tableWidget->setRowCount(4); //задание количества строк таблицы
    ui->tableWidget->setColumnCount(4); //задание количества столбцов
    QStringList name2; //объявление указателя на тип QStringList
    name2 << "№" << "Цвет" << "Свойство" << "Значение"; //перечисление заголовков
    ui->tableWidget->setHorizontalHeaderLabels(name2); //установка заголовков в таблицу
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //Устанавливает ограничения на то, как размер заголовка может быть изменен до тех, которые описаны в данном режиме
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView :: NoSelection);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnWidth(0, 100);

    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
        {
          ui->tableWidget->setItem(row, column, new QTableWidgetItem());
        }
      //  ui->tableWidget->item(1, 1)->setBackground(QColor(0,0,255));
    }

    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("Сопротивление ротора R2, Ом:"));
    ui->tableWidget->setItem(1, 2, new QTableWidgetItem("Индуктивность обмотки статора L1, Гн:"));
    ui->tableWidget->setItem(2, 2, new QTableWidgetItem("Индуктивность обмотки ротора L2, Гн:"));
    ui->tableWidget->setItem(3, 2, new QTableWidgetItem("Индуктивность взаимоиндукции Lm, Гн:"));

    for (int i=0; i<5; i++)
    {
        if (ui->tableWidget->item(i, 0) != 0)
        {
            ui->tableWidget->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }


    std::vector<QColor> lineColors(64);

    for (int i = 0; i < 5; i++)
    {
        lineColors[i] = QColor(QRandomGenerator::global()->bounded(255),
                               QRandomGenerator::global()->bounded(255),
                               QRandomGenerator::global()->bounded(255));
        ui->plot->addDataLine(lineColors[i], 0);
    }

    for (int i = 0; i < 4; i++)
    {
        ui->tableWidget->item(i, 1)->setBackground(lineColors[i]);
    }

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
        ui->plot->addPoint(0, key, model.R2);
        ui->plot->addPoint(1, key, model.L);
        ui->plot->addPoint(2, key, model.Lm);

   //  ui->label->setText(QString::number(key));
        ui->lineEdit_8->setText(QString::number(model.Lm));
        ui->lineEdit_9->setText(QString::number(model.L));
        ui->lineEdit_10->setText(QString::number(model.L));
        ui->lineEdit_11->setText(QString::number(model.R2));
        ui->lineEdit_12->setText(QString::number(R1));
      // rescale value (vertical) axis to fit the current data:
        lastPointKey = key;
    //}
    // make key axis range scroll with the data (at a constant range size of 8):
    }
}

void identf::raschet_f()
{
    minR2 = DBL_MAX;
    maxR2 = -DBL_MAX;
    middleR2 = 0.0;

//    ui->lineEdit->setText(QString("%1").arg(base.P_nom));
//    ui->lineEdit_2->setText(QString("%1").arg(base.n_nom));
//    ui->lineEdit_3->setText(QString("%1").arg(base.U_fnom));
//    ui->lineEdit_4->setText(QString("%1").arg(base.cosf_nom));
//    ui->lineEdit_5->setText(QString("%1").arg(base.kpd_nom));
//    ui->lineEdit_6->setText(QString("%1").arg(base.muk));
//    ui->lineEdit_7->setText(QString("%1").arg(base.n_0));
    dataSource->init();
    model.init(base.P_nom, base.n_nom, base.U_fnom, base.cosf_nom, base.kpd_nom, base.muk, base.n_0);
    ui->plot->clear();
    ui->plot->addDataLine(Qt::red, 0.0);
    ui->plot->addDataLine(Qt::green, 0.0);
    ui->plot->addDataLine(Qt::cyan, 0.0);
    time->start();
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

void identf::setcolorincell(int row, int column)
{
    if (column == 1)
    {
        row = ui->tableWidget->currentRow();
        QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
        ui->tableWidget->item(row, column)->setBackground(chosenColor);
        ui->plot->setLineDataColor(row, chosenColor);
    }
}
