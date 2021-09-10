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

    for (int i=0; i<5; i++)
    {
        if (ui->tableWidget->item(i, 3) != 0)
        {
            ui->tableWidget->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->lineEdit_8->setAlignment(Qt::AlignCenter);
    ui->lineEdit_9->setAlignment(Qt::AlignCenter);
    ui->lineEdit_10->setAlignment(Qt::AlignCenter);
    ui->lineEdit_11->setAlignment(Qt::AlignCenter);
    ui->lineEdit_12->setAlignment(Qt::AlignCenter);

    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);

    for (int i = 0; i < dataLineColors.size(); i++)
    {
        ui->plot->addDataLine(dataLineColors[i], 0);
    }

    for (int i = 0; i < dataLineColors.size(); i++)
    {
        ui->tableWidget->item(i, 1)->setBackground(dataLineColors[i]);
    }
    connect(ui->tableWidget, &QTableWidget::cellClicked,this, &identf::setcolorincell);

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

        if (ui->tableWidget->item(0, 3) != 0)
        {
            ui->tableWidget->item(0, 3)->setText(QString::number(model.R2,'f',3));
        }

        if (ui->tableWidget->item(1, 3) != 0)
        {
            ui->tableWidget->item(1, 3)->setText(QString::number(model.L,'f',3));
        }

        if (ui->tableWidget->item(2, 3) != 0)
        {
            ui->tableWidget->item(2, 3)->setText(QString::number(model.L,'f',3));
        }

        if (ui->tableWidget->item(3, 3) != 0)
        {
            ui->tableWidget->item(3, 3)->setText(QString::number(model.Lm,'f',3));
        }

    }
}

void identf::raschet_f()
{
    minR2 = DBL_MAX;
    maxR2 = -DBL_MAX;
    middleR2 = 0.0;

    auto uiDatasWindow = mainWindow->ui->widget->ui;

    if(uiDatasWindow->radioButton_2->isChecked())
    {
        dataSource = new DataSource_file();
        connect(dataSource, &DataSource::ready, this, &identf::realtimeDataSlot);
    }

    if(uiDatasWindow->radioButton->isChecked())
    {
        //dataSource = new DataSource();
        //connect(dataSource, &DataSource::ready, this, &identf::realtimeDataSlot);
    }

    if(uiDatasWindow->radioButton_3->isChecked())
    {
        dataSource = new DataSource_el(base.P_nom, base.n_nom, base.U_fnom, base.cosf_nom, base.kpd_nom, base.muk, base.n_0);
        connect(dataSource, &DataSource::ready, this, &identf::realtimeDataSlot);
    }

    dataSource->init();
    model.init(base.P_nom, base.n_nom, base.U_fnom, base.cosf_nom, base.kpd_nom, base.muk, base.n_0);
    ui->plot->clear();
    for (int i = 0; i < dataLineColors.size(); i++)
    {
        ui->plot->addDataLine(dataLineColors[i], 0);
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

void identf::setcolorincell(int row, int column)
{
    if (column == 1)
    {
        row = ui->tableWidget->currentRow();
        QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
        ui->tableWidget->item(row, column)->setBackground(chosenColor);
        ui->plot->setDataLineColor(row, chosenColor);
        dataLineColors[row] = chosenColor;
        repaint();
    }
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
    }
}

void identf::setMainWindow(MainWindow* wind)
{
    mainWindow = wind;
}
