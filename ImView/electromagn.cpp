#include "electromagn.h"
#include "ui_electromagn.h"
#include "base.h"
#include "model_el.h"
#include "nabludatel.h"
#include "nabludatel_part.h"
#include "plot.h"
#include "datasource_file.h"
#include"ui_mainwindow.h"

#include <QLinearGradient>
#include <QMessageBox>
#include <QColorDialog>
#include <QFileDialog>
#include <QScrollArea>


DataSource_file dataSource_file;
Model_el Model_el;
QPoint p1,p2;
QCursor curs;

electromagn::electromagn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::electromagn),
    dataSource(nullptr)
{
    ui->setupUi(this);
    ui->plot->t_max = 10.0;
    ui->plot->U_max = 500.0;
    ui->plot->margin_bottom = 40;
    ui->plot->margin_left = 100;
    ui->plot->reset();
    time=new QElapsedTimer();
    //ui->widget->setMaximumSize(ui->widget->maximumWidth(), ui->widget->maximumHeight());

    this->showMaximized();

    //Заполнение таблицы результатов
    ui->tableWidget->setRowCount(24);
    ui->tableWidget->setColumnCount(2);
    QStringList name;
    name << "Сигнал" << "Величина";
    ui->tableWidget->setHorizontalHeaderLabels(name);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setVisible(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);

    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Ток фазы А, А"));
    ui->tableWidget->setItem(1, 0, new QTableWidgetItem("Напряжение фазы А, В"));
    ui->tableWidget->setItem(2, 0, new QTableWidgetItem("Активная мошность фазы А, Вт"));
    ui->tableWidget->setItem(3, 0, new QTableWidgetItem("Реактивная мошность фазы А, ВА"));
    ui->tableWidget->setItem(4, 0, new QTableWidgetItem("Полная мошность фазы А, ВАР"));
    ui->tableWidget->setItem(5, 0, new QTableWidgetItem("Коэффициент мощности фазы А"));
    ui->tableWidget->setItem(6, 0, new QTableWidgetItem("Ток фазы В, А"));
    ui->tableWidget->setItem(7, 0, new QTableWidgetItem("Напряжение фазы В, В"));
    ui->tableWidget->setItem(8, 0, new QTableWidgetItem("Активная мошность фазы В, Вт"));
    ui->tableWidget->setItem(9, 0, new QTableWidgetItem("Реактивная мошность фазы В, ВА"));
    ui->tableWidget->setItem(10, 0, new QTableWidgetItem("Полная мошность фазы В, ВАР"));
    ui->tableWidget->setItem(11, 0, new QTableWidgetItem("Коэффициент мощности фазы В"));
    ui->tableWidget->setItem(12, 0, new QTableWidgetItem("Ток фазы С, А"));
    ui->tableWidget->setItem(13, 0, new QTableWidgetItem("Напряжение фазы С, В"));
    ui->tableWidget->setItem(14, 0, new QTableWidgetItem("Активная мошность фазы С, Вт"));
    ui->tableWidget->setItem(15, 0, new QTableWidgetItem("Реактивная мошность фазы С, ВА"));
    ui->tableWidget->setItem(16, 0, new QTableWidgetItem("Полная мошность фазы С, ВАР"));
    ui->tableWidget->setItem(17, 0, new QTableWidgetItem("Коэффициент мощности фазы С"));
    ui->tableWidget->setItem(18, 0, new QTableWidgetItem("трехфазная активная мошность, Вт"));
    ui->tableWidget->setItem(19, 0, new QTableWidgetItem("Трехфазная реактивная мошность, ВА"));
    ui->tableWidget->setItem(20, 0, new QTableWidgetItem("Трехфазная полная мошность, ВАР"));
    ui->tableWidget->setItem(21, 0, new QTableWidgetItem("Коэффициент мощности"));
    ui->tableWidget->setItem(22, 0, new QTableWidgetItem("Скорость вращения ротора, рад/с"));
    ui->tableWidget->setItem(23, 0, new QTableWidgetItem("Момент, Н*м"));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(1, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(2, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(3, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(4, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(5, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(6, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(7, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(8, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(9, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(10, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(11, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(12, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(13, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(14, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(15, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(16, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(17, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(18, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(19, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(20, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(21, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(22, 1, new QTableWidgetItem());
    ui->tableWidget->setItem(23, 1, new QTableWidgetItem());

    QPalette p99=ui->tableWidget->palette();
    p99.setColor(QPalette::Base, QColor(225, 255, 255));
    p99.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget->setPalette(p99);

    //вставка таблицы Настройки внутренней модели таблицы tableWidget_3
    ui->tableWidget_3->setRowCount(30);
    ui->tableWidget_3->setColumnCount(2);
    QStringList name3;
    name3 << "Свойство" << "Значение";
    ui->tableWidget_3->setHorizontalHeaderLabels(name);
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_3->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_3->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_3->verticalHeader()->setVisible(true);

    //вставка комбобокса Режим работы АД таблицы tableWidget_3
    ui->tableWidget_3->setCellWidget(0,1,combo);
    ui->tableWidget_3->setItem(0, 0, new QTableWidgetItem("Режим работы двигателя"));
    ui->tableWidget_3->setItem(1, 0, new QTableWidgetItem("Время цикла, с"));
    ui->tableWidget_3->setItem(2, 0, new QTableWidgetItem("Время работы, с"));
    ui->tableWidget_3->setItem(3, 0, new QTableWidgetItem("Значение момента Мс, Н*м"));
    ui->tableWidget_3->setItem(4, 0, new QTableWidgetItem("Выбор системы электропривода"));
    combo->addItem("Режим S1");
    combo->addItem("Режим S2");
    combo->addItem("Режим S3");
    combo->addItem("Режим S4");
    combo->addItem("Режим S6");

    //вставка комбобокса Выбор системы электропривода таблицы tableWidget_3
    ui->tableWidget_3->setCellWidget(4,1,combo2);
    combo2->addItem("Прямой пуск");
    combo2->addItem("Система ТРН-АД");
    combo2->addItem("Система ПЧ-АД");

    //цветовая палитра таблицы tableWidget_3
    QPalette p2=ui->tableWidget_3->palette();
    p2.setColor(QPalette::Base, QColor(199, 255, 255));
    p2.setColor(QPalette::AlternateBase, QColor(230, 255, 255));
    ui->tableWidget_3->setPalette(p2);


    //вставка таблицы Энергетические характеристики таблицы tableWidget_4
    ui->tableWidget_4->setRowCount(30);
    ui->tableWidget_4->setColumnCount(2);
    QStringList name4;
    name3 << "Свойство" << "Значение";
    ui->tableWidget_4->setHorizontalHeaderLabels(name);
    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_4->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_4->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_4->verticalHeader()->setVisible(true);

    //Заполнение полей левой части таблицы для пояснения чекбоксов таблицы tableWidget_3
    ui->tableWidget_4->setItem(0, 0, new QTableWidgetItem("Потребляемая двигателем мощность P1, Вт"));
    ui->tableWidget_4->setItem(1, 0, new QTableWidgetItem("Потери в обмотке статора dPel1, Вт"));
    ui->tableWidget_4->setItem(2, 0, new QTableWidgetItem("Потери в стали dPct, Вт"));
    ui->tableWidget_4->setItem(3, 0, new QTableWidgetItem("Потери в обмотке ротора dPel2, Вт"));
    ui->tableWidget_4->setItem(4, 0, new QTableWidgetItem("Добавочные потери dPdob, Вт"));
    ui->tableWidget_4->setItem(5, 0, new QTableWidgetItem("Механические потери dPmech, Вт"));
    ui->tableWidget_4->setItem(6, 0, new QTableWidgetItem("Механическая мощность на валу двигателя P2, Вт"));
    ui->tableWidget_4->setItem(7, 0, new QTableWidgetItem("Коэффициент полезного действия"));
    ui->tableWidget_4->setItem(8, 0, new QTableWidgetItem("Коэффициент мощности"));
    ui->tableWidget_4->setItem(0, 1, new QTableWidgetItem());
    ui->tableWidget_4->setItem(1, 1, new QTableWidgetItem());
    ui->tableWidget_4->setItem(2, 1, new QTableWidgetItem());
    ui->tableWidget_4->setItem(3, 1, new QTableWidgetItem());
    ui->tableWidget_4->setItem(4, 1, new QTableWidgetItem());
    ui->tableWidget_4->setItem(5, 1, new QTableWidgetItem());
    ui->tableWidget_4->setItem(6, 1, new QTableWidgetItem());
    ui->tableWidget_4->setItem(7, 1, new QTableWidgetItem());
    ui->tableWidget_4->setItem(8, 1, new QTableWidgetItem());

    QPalette p3=ui->tableWidget_4->palette();
    p3.setColor(QPalette::Base, QColor(255, 255, 191));
    p3.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_4->setPalette(p3);

    ui->tableWidget_5->setRowCount(9); //задание количества строк таблицы
    ui->tableWidget_5->setColumnCount(6); //задание количества столбцов
    QStringList name5; //объявление указателя на тип QStringList
    name5 << "№" << "Цвет" << "Свойство" << "Значение" << "Масштабирование" << "Смещение"; //перечисление заголовков
    ui->tableWidget_5->setHorizontalHeaderLabels(name5); //установка заголовков в таблицу
    ui->tableWidget_5->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //Устанавливает ограничения на то, как размер заголовка может быть изменен до тех, которые описаны в данном режиме
    ui->tableWidget_5->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_5->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_5->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_5->verticalHeader()->setVisible(false);
    ui->tableWidget_5->resizeColumnsToContents();
   // ui->tableWidget_5->setEditTriggers(QAbstractItemView::AnyKeyPressed);
    ui->tableWidget_5->setColumnWidth(0, 100);

    for(int row = 0; row<ui->tableWidget_5->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_5->columnCount(); column++)
        {
          ui->tableWidget_5->setItem(row, column, new QTableWidgetItem());
        }
    }

    QTableWidgetItem *item51 = new QTableWidgetItem("Item51");
    item51->setCheckState(Qt::Checked);
    item51->setText("Напряжение фазы А, В:");
    ui->tableWidget_5->setItem(0, 2, item51);

    QTableWidgetItem *item52 = new QTableWidgetItem("Item52");
    item52->setCheckState(Qt::Checked);
    item52->setText("Напряжение фазы B, В:");
    ui->tableWidget_5->setItem(1, 2, item52);

    QTableWidgetItem *item53 = new QTableWidgetItem("Item53");
    item53->setCheckState(Qt::Checked);
    item53->setText("Напряжение фазы C, В:");
    ui->tableWidget_5->setItem(2, 2, item53);

    QTableWidgetItem *item54 = new QTableWidgetItem("Item54");
    item54->setCheckState(Qt::Checked);
    item54->setText("Ток фазы А, А:");
    ui->tableWidget_5->setItem(3, 2, item54);

    QTableWidgetItem *item55 = new QTableWidgetItem("Item55");
    item55->setCheckState(Qt::Checked);
    item55->setText("Ток фазы B, А:");
    ui->tableWidget_5->setItem(4, 2, item55);

    QTableWidgetItem *item56 = new QTableWidgetItem("Item56");
    item56->setCheckState(Qt::Checked);
    item56->setText("Ток фазы С, А:");
    ui->tableWidget_5->setItem(5, 2, item56);

    QTableWidgetItem *item57 = new QTableWidgetItem("Item57");
    item57->setCheckState(Qt::Checked);
    item57->setText("Частота вращения, рад/с:");
    ui->tableWidget_5->setItem(6, 2, item57);

    QTableWidgetItem *item58 = new QTableWidgetItem("Item58");
    item58->setCheckState(Qt::Checked);
    item58->setText("Момент на валу, Н*м:");
    ui->tableWidget_5->setItem(7, 2, item58);

    QTableWidgetItem *item59 = new QTableWidgetItem("Item59");
    item59->setCheckState(Qt::Checked);
    item59->setText("Момент Мс, Н*м:");
    ui->tableWidget_5->setItem(8, 2, item59);

    for (int i=0; i<10; i++)
    {
        if (ui->tableWidget_5->item(i, 0) != 0)
        {
            ui->tableWidget_5->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget_5->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

    for (int i=0; i<10; i++)
    {
        if (ui->tableWidget_5->item(i, 3) != 0)
        {
            ui->tableWidget_5->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }

        if (ui->tableWidget_5->item(i, 4) != 0)
        {
            ui->tableWidget_5->item(i, 4)->setTextAlignment(Qt::AlignCenter);
        }
    }


    for (int i=0; i<10; i++)
    {
        if (ui->tableWidget_5->item(i, 5) != 0)
        {
            //ui->tableWidget_5->item(i, 5)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget_5->setItem(0, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_5->setItem(0, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_5->setItem(1, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_5->setItem(1, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_5->setItem(2, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_5->setItem(2, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_5->setItem(3, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_5->setItem(3, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_5->setItem(4, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_5->setItem(4, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_5->setItem(5, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_5->setItem(5, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_5->setItem(6, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_5->setItem(6, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_5->setItem(7, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_5->setItem(7, 5, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_5->setItem(8, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_5->setItem(8, 5, new QTableWidgetItem(QString("%1").arg(0)));

    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::yellow);

    for (int i = 0; i < dataLineColors.size(); i++)
    {
        ui->plot->addDataLine(dataLineColors[i], 0);
    }

    for (int i = 0; i < dataLineColors.size(); i++)
    {
        ui->tableWidget_5->item(i, 1)->setBackground(dataLineColors[i]);
    }
    connect(ui->tableWidget_5, &QTableWidget::cellClicked,this, &electromagn::setcolorincell);
}


electromagn::~electromagn()
{
    delete ui;
}

void electromagn::setcolorincell(int row, int column)
{
    if (column == 1)
    {
        row = ui->tableWidget_5->currentRow();
        QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
        ui->tableWidget_5->item(row, column)->setBackground(chosenColor);
        ui->plot->setDataLineColor(row, chosenColor);
        dataLineColors[row] = chosenColor;
        repaint();
    }
}

void electromagn::realtimeDataSlot()
{
    double a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18;
    key = time->elapsed()/1000.0;

    if(ui->radioButton->isChecked())
    {
        nabludatel.rasch(dataSource);

    //Занесение итоговых данных в таблицу
    if (ui->tableWidget->item(0, 1) != 0)
    {
        ui->tableWidget->item(0, 1)->setText(QString("%1").arg(nabludatel.i_dev_a));
    }

    if (ui->tableWidget->item(1, 1) != 0)
    {
        ui->tableWidget->item(1, 1)->setText(QString("%1").arg(nabludatel.u_dev_a));
    }

    if (ui->tableWidget->item(2, 1) != 0)
    {
        ui->tableWidget->item(2, 1)->setText(QString("%1").arg(nabludatel.p_akt_a));
    }

    if (ui->tableWidget->item(3, 1) != 0)
    {
        ui->tableWidget->item(3, 1)->setText(QString("%1").arg(nabludatel.p_reakt_a));
    }

    if (ui->tableWidget->item(4, 1) != 0)
    {
        ui->tableWidget->item(4, 1)->setText(QString("%1").arg(nabludatel.p_poln_a));
    }

    if (ui->tableWidget->item(5, 1) != 0)
    {
        ui->tableWidget->item(5, 1)->setText(QString("%1").arg(nabludatel.cos_f_a));
    }

    if (ui->tableWidget->item(6, 1) != 0)
    {
        ui->tableWidget->item(6, 1)->setText(QString("%1").arg(nabludatel.i_dev_b));
    }

    if (ui->tableWidget->item(7, 1) != 0)
    {
        ui->tableWidget->item(7, 1)->setText(QString("%1").arg(nabludatel.u_dev_b));
    }
    if (ui->tableWidget->item(8, 1) != 0)
    {
        ui->tableWidget->item(8, 1)->setText(QString("%1").arg(nabludatel.p_akt_b));
    }

    if (ui->tableWidget->item(9, 1) != 0)
    {
        ui->tableWidget->item(9, 1)->setText(QString("%1").arg(nabludatel.p_reakt_b));
    }

    if (ui->tableWidget->item(10, 1) != 0)
    {
        ui->tableWidget->item(10, 1)->setText(QString("%1").arg(nabludatel.p_poln_b));
    }

    if (ui->tableWidget->item(11, 1) != 0)
    {
        ui->tableWidget->item(11, 1)->setText(QString("%1").arg(nabludatel.cos_f_b));
    }

    if (ui->tableWidget->item(12, 1) != 0)
    {
        ui->tableWidget->item(12, 1)->setText(QString("%1").arg(nabludatel.i_dev_c));
    }

    if (ui->tableWidget->item(13, 1) != 0)
    {
        ui->tableWidget->item(13, 1)->setText(QString("%1").arg(nabludatel.u_dev_c));
    }

    if (ui->tableWidget->item(14, 1) != 0)
    {
        ui->tableWidget->item(14, 1)->setText(QString("%1").arg(nabludatel.p_akt_c));
    }

    if (ui->tableWidget->item(15, 1) != 0)
    {
        ui->tableWidget->item(15, 1)->setText(QString("%1").arg(nabludatel.p_reakt_c));
    }

    if (ui->tableWidget->item(16, 1) != 0)
    {
        ui->tableWidget->item(16, 1)->setText(QString("%1").arg(nabludatel.p_poln_c));
    }

    if (ui->tableWidget->item(17, 1) != 0)
    {
        ui->tableWidget->item(17, 1)->setText(QString("%1").arg(nabludatel.cos_f_c));
    }

    if (ui->tableWidget->item(18, 1) != 0)
    {
        ui->tableWidget->item(18, 1)->setText(QString("%1").arg(nabludatel.p_akt));
    }

    if (ui->tableWidget->item(19, 1) != 0)
    {
        ui->tableWidget->item(19, 1)->setText(QString("%1").arg(nabludatel.p_reakt));
    }
    if (ui->tableWidget->item(20, 1) != 0)
    {
        ui->tableWidget->item(20, 1)->setText(QString("%1").arg(nabludatel.p_poln));
    }
    if (ui->tableWidget->item(21, 1) != 0)
    {
        ui->tableWidget->item(21, 1)->setText(QString("%1").arg(nabludatel.cos_f));
    }
}

    if(ui->radioButton_2->isChecked())
    {
        nabludatel_part.rasch(dataSource);
        count++;

        if (count % 100 == 0)
        {
            count = 1;
        }
    }

    if(ui->radioButton_3->isChecked())
    {
        double b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15,b16;
        for (int i = 0; i < 1000; i++)
        {
            Model_el.rasch();
        }

        //Считывание значения времени цикла Тц

        if(ui->tableWidget_3->item(1,1)!=0)
        {
            Model_el.Tc=ui->tableWidget_3->item(1,1)->text().toDouble();
        }

        //Считывание значения времени работы tp

        if(ui->tableWidget_3->item(2,1)!=0)
        {
            Model_el.tp=ui->tableWidget_3->item(2,1)->text().toDouble();
        }

        //Считывание значения времени работы Mc

        if(ui->tableWidget_3->item(3,1)!=0)
        {
            Model_el.Mc_n=ui->tableWidget_3->item(3,1)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды напряжения фазы А

        if(ui->tableWidget_5->item(0,4)!=0)
        {
            b1=ui->tableWidget_5->item(0,4)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды напряжения фазы В

        if(ui->tableWidget_5->item(1,4)!=0)
        {
            b2=ui->tableWidget_5->item(1,4)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды напряжения фазы С

        if(ui->tableWidget_5->item(2,4)!=0)
        {
            b3=ui->tableWidget_5->item(2,4)->text().toDouble();
        }

        //Считывание коэффициента смещения напряжения фазы А

        if(ui->tableWidget_5->item(0,5)!=0)
        {
            b4=ui->tableWidget_5->item(0,5)->text().toDouble();
        }

        //Считывание коэффициента смещения напряжения фазы В

        if(ui->tableWidget_5->item(1,5)!=0)
        {
            b5=ui->tableWidget_5->item(1,5)->text().toDouble();
        }

        //Считывание коэффициента смещения напряжения фазы С

        if(ui->tableWidget_5->item(2,5)!=0)
        {
            b6=ui->tableWidget_5->item(2,5)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды тока фазы А

        if(ui->tableWidget_5->item(3,4)!=0)
        {
            b7=ui->tableWidget_5->item(3,4)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды тока фазы В

        if(ui->tableWidget_5->item(4,4)!=0)
        {
            b8=ui->tableWidget_5->item(4,4)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды тока фазы С

        if(ui->tableWidget_5->item(5,4)!=0)
        {
            b9=ui->tableWidget_5->item(5,4)->text().toDouble();
        }

        //Считывание коэффициента смещения тока фазы А

        if(ui->tableWidget_5->item(3,5)!=0)
        {
            b10=ui->tableWidget_5->item(3,5)->text().toDouble();
        }

        //Считывание коэффициента смещения тока фазы В

        if(ui->tableWidget_5->item(4,5)!=0)
        {
            b11=ui->tableWidget_5->item(4,5)->text().toDouble();
        }

        //Считывание коэффициента смещения тока фазы С

        if(ui->tableWidget_5->item(5,5)!=0)
        {
            b12=ui->tableWidget_5->item(5,5)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды скорости вращения

        if(ui->tableWidget_5->item(6,4)!=0)
        {
            b13=ui->tableWidget_5->item(6,4)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды момента на валу

        if(ui->tableWidget_5->item(7,4)!=0)
        {
            b14=ui->tableWidget_5->item(7,4)->text().toDouble();
        }

        //Считывание коэффициента смещения скорости вращения

        if(ui->tableWidget_5->item(6,5)!=0)
        {
            b15=ui->tableWidget_5->item(6,5)->text().toDouble();
        }

        //Считывание коэффициента смещения момента на валу

        if(ui->tableWidget_5->item(7,5)!=0)
        {
            b16=ui->tableWidget_5->item(7,5)->text().toDouble();
        }

        key = Model_el.t;
        //key=dataSource_file.getTime();

        //вывод на qcustomPlot графика напряжения Ua после преобразования 2 в 3

        if(ui->tableWidget_5->model()->index(0,2).data(Qt::CheckStateRole)==Qt::Checked)
        {
            ui->plot->addPoint(0, key, b4+b1*(Model_el.u_dev_a));
        }

        //вывод на qcustomPlot графика напряжения Ub после преобразования 2 в 3

        if(ui->tableWidget_5->model()->index(1,2).data(Qt::CheckStateRole)==Qt::Checked)
        {
            ui->plot->addPoint(1, key, b5+b2*(Model_el.u_dev_b));

        }

        //вывод на qcustomPlot графика напряжения Uc после преобразования 2 в 3

        if(ui->tableWidget_5->model()->index(2,2).data(Qt::CheckStateRole)==Qt::Checked)
        {
            ui->plot->addPoint(2, key, b6+b3*(Model_el.u_dev_c));
        }

        //вывод на qcustomPlot графика напряжения Ia после преобразования 2 в 3

        if(ui->tableWidget_5->model()->index(3,2).data(Qt::CheckStateRole)==Qt::Checked)
        {
            ui->plot->addPoint(3, key, b10+b7*(Model_el.i_dev_a));
        }

        //вывод на qcustomPlot графика напряжения Ib после преобразования 2 в 3

        if(ui->tableWidget_5->model()->index(4,2).data(Qt::CheckStateRole)==Qt::Checked)
        {
            ui->plot->addPoint(4, key, b11+b8*(Model_el.i_dev_b));
        }

        //вывод на qcustomPlot графика напряжения Ic после преобразования 2 в 3

        if(ui->tableWidget_5->model()->index(5,2).data(Qt::CheckStateRole)==Qt::Checked)
        {
            ui->plot->addPoint(5, key, b12+b9*(Model_el.i_dev_c));
       }

        //вывод на qcustomPlot графика скорости omega

        if(ui->tableWidget_5->model()->index(6,2).data(Qt::CheckStateRole)==Qt::Checked)
        {
            ui->plot->addPoint(6, key, b15+b13*Model_el.omega);
        }

        //вывод на qcustomPlot момента на валу M

        if(ui->tableWidget_5->model()->index(7,2).data(Qt::CheckStateRole)==Qt::Checked)
        {
            ui->plot->addPoint(7, key, b16+b14*Model_el.M);
        }

        //вывод на qcustomPlot момента Mс

        if(ui->tableWidget_3->model()->index(8,2).data(Qt::CheckStateRole)==Qt::Checked)
        {
            ui->plot->addPoint(8, key, Model_el.Mc);
        }

        //Занесение итоговых данных в таблицу
        if (ui->tableWidget->item(0, 1) != 0)
        {
            ui->tableWidget->item(0, 1)->setText(QString::number(Model_el.i_dev_a,'f',3));
        }

        if (ui->tableWidget->item(1, 1) != 0)
        {
            ui->tableWidget->item(1, 1)->setText(QString::number(Model_el.u_dev_a,'f',3));
        }

        if (ui->tableWidget->item(2, 1) != 0)
        {
            ui->tableWidget->item(2, 1)->setText(QString::number(Model_el.p_akt_a,'f',3));
        }

        if (ui->tableWidget->item(3, 1) != 0)
        {
            ui->tableWidget->item(3, 1)->setText(QString::number(Model_el.p_reakt_a,'f',3));
        }

        if (ui->tableWidget->item(4, 1) != 0)
        {
            ui->tableWidget->item(4, 1)->setText(QString::number(Model_el.p_poln_a,'f',3));
        }

        if (ui->tableWidget->item(5, 1) != 0)
        {
            ui->tableWidget->item(5, 1)->setText(QString::number(Model_el.cos_f_a,'f',3));
        }

        if (ui->tableWidget->item(6, 1) != 0)
        {
            ui->tableWidget->item(6, 1)->setText(QString::number(Model_el.i_dev_b,'f',3));
        }

        if (ui->tableWidget->item(7, 1) != 0)
        {
            ui->tableWidget->item(7, 1)->setText(QString::number(Model_el.u_dev_b,'f',3));
        }

        if (ui->tableWidget->item(8, 1) != 0)
        {
            ui->tableWidget->item(8, 1)->setText(QString::number(Model_el.p_akt_b,'f',3));
        }

        if (ui->tableWidget->item(9, 1) != 0)
        {
            ui->tableWidget->item(9, 1)->setText(QString::number(Model_el.p_reakt_b,'f',3));
        }

        if (ui->tableWidget->item(10, 1) != 0)
        {
            ui->tableWidget->item(10, 1)->setText(QString::number(Model_el.p_poln_b,'f',3));
        }

        if (ui->tableWidget->item(11, 1) != 0)
        {
            ui->tableWidget->item(11, 1)->setText(QString::number(Model_el.cos_f_b,'f',3));
        }

        if (ui->tableWidget->item(12, 1) != 0)
        {
            ui->tableWidget->item(12, 1)->setText(QString::number(Model_el.i_dev_c,'f',3));
        }

        if (ui->tableWidget->item(13, 1) != 0)
        {
            ui->tableWidget->item(13, 1)->setText(QString::number(Model_el.u_dev_c,'f',3));
        }

        if (ui->tableWidget->item(14, 1) != 0)
        {
            ui->tableWidget->item(14, 1)->setText(QString::number(Model_el.p_akt_c,'f',3));
        }

        if (ui->tableWidget->item(15, 1) != 0)
        {
            ui->tableWidget->item(15, 1)->setText(QString::number(Model_el.p_reakt_c,'f',3));
        }

        if (ui->tableWidget->item(16, 1) != 0)
        {
            ui->tableWidget->item(16, 1)->setText(QString::number(Model_el.p_poln_c,'f',3));
        }

        if (ui->tableWidget->item(17, 1) != 0)
        {
            ui->tableWidget->item(17, 1)->setText(QString::number(Model_el.cos_f_c,'f',3));
        }

        if (ui->tableWidget->item(18, 1) != 0)
        {
            ui->tableWidget->item(18, 1)->setText(QString::number(Model_el.p_akt,'f',3));
        }

        if (ui->tableWidget->item(19, 1) != 0)
        {
            ui->tableWidget->item(19, 1)->setText(QString::number(Model_el.p_reakt,'f',3));
        }

        if (ui->tableWidget->item(20, 1) != 0)
        {
            ui->tableWidget->item(20, 1)->setText(QString::number(Model_el.p_poln,'f',3));
        }

        if (ui->tableWidget->item(21, 1) != 0)
        {
            ui->tableWidget->item(21, 1)->setText(QString::number(Model_el.cos_f,'f',3));
        }

        if (ui->tableWidget->item(22, 1) != 0)
        {
            ui->tableWidget->item(22, 1)->setText(QString::number(Model_el.omega,'f',3));
        }
        if (ui->tableWidget->item(23, 1) != 0)
        {
            ui->tableWidget->item(23, 1)->setText(QString::number(Model_el.M,'f',3));
        }

        if (ui->tableWidget_4->item(0, 1) != 0)
        {
            ui->tableWidget_4->item(0, 1)->setText(QString::number(Model_el.P1,'f',3));
        }

        if (ui->tableWidget_4->item(1, 1) != 0)
        {
            ui->tableWidget_4->item(1, 1)->setText(QString::number(Model_el.dPel1,'f',3));
        }

        if (ui->tableWidget_4->item(2, 1) != 0)
        {
            ui->tableWidget_4->item(2, 1)->setText(QString::number(Model_el.dPct,'f',3));
        }

        if (ui->tableWidget_4->item(3, 1) != 0)
        {
            ui->tableWidget_4->item(3, 1)->setText(QString::number(Model_el.dPel2,'f',3));
        }

        if (ui->tableWidget_4->item(4, 1) != 0)
        {
            ui->tableWidget_4->item(4, 1)->setText(QString::number(Model_el.dPdob,'f',3));
        }

        if (ui->tableWidget_4->item(5, 1) != 0)
        {
            ui->tableWidget_4->item(5, 1)->setText(QString::number(Model_el.dPmech,'f',3));
        }

        if (ui->tableWidget_4->item(6, 1) != 0)
        {
            ui->tableWidget_4->item(6, 1)->setText(QString::number(Model_el.P2,'f',3));
        }

        if (ui->tableWidget_4->item(7, 1) != 0)
        {
            ui->tableWidget_4->item(7, 1)->setText(QString::number(Model_el.kpd,'f',3));
        }

        if (ui->tableWidget_4->item(8, 1) != 0)
        {
            ui->tableWidget_4->item(8, 1)->setText(QString::number(Model_el.cos_f,'f',3));
        }

        if (ui->tableWidget_5->item(0, 3) != 0)
        {
            ui->tableWidget_5->item(0, 3)->setText(QString::number(Model_el.u_dev_a,'f',3));
        }

        if (ui->tableWidget_5->item(1, 3) != 0)
        {
            ui->tableWidget_5->item(1, 3)->setText(QString::number(Model_el.u_dev_b,'f',3));
        }

        if (ui->tableWidget_5->item(2, 3) != 0)
        {
            ui->tableWidget_5->item(2, 3)->setText(QString::number(Model_el.u_dev_c,'f',3));
        }

        if (ui->tableWidget_5->item(3, 3) != 0)
        {
            ui->tableWidget_5->item(3, 3)->setText(QString::number(Model_el.i_dev_a,'f',3));
        }

        if (ui->tableWidget_5->item(4, 3) != 0)
        {
            ui->tableWidget_5->item(4, 3)->setText(QString::number(Model_el.i_dev_b,'f',3));
        }

        if (ui->tableWidget_5->item(5, 3) != 0)
        {
            ui->tableWidget_5->item(5, 3)->setText(QString::number(Model_el.i_dev_c,'f',3));
        }

        if (ui->tableWidget_5->item(6, 3) != 0)
        {
            ui->tableWidget_5->item(6, 3)->setText(QString::number(Model_el.omega,'f',3));
        }

        if (ui->tableWidget_5->item(7, 3) != 0)
        {
            ui->tableWidget_5->item(7, 3)->setText(QString::number(Model_el.M,'f',3));
        }

        if (ui->tableWidget_5->item(8, 3) != 0)
        {
            ui->tableWidget_5->item(8, 3)->setText(QString::number(Model_el.Mc,'f',3));
        }
    }

    if(ui->radioButton_4->isChecked())
    {
        nabludatel.rasch(dataSource);

        //Считывание коэффициента изменения амплитуды напряжения фазы А
        a1=ui->tableWidget_5->item(0,4)->text().toDouble();

        //Считывание коэффициента изменения амплитуды напряжения фазы В
        a2=ui->tableWidget_5->item(1,4)->text().toDouble();

        //Считывание коэффициента изменения амплитуды напряжения фазы С
        a3=ui->tableWidget_5->item(2,4)->text().toDouble();

        //Считывание коэффициента смещения напряжения фазы А
        a4=ui->tableWidget_5->item(0,5)->text().toDouble();

        //Считывание коэффициента смещения напряжения фазы В
        a5=ui->tableWidget_5->item(1,5)->text().toDouble();

        //Считывание коэффициента смещения напряжения фазы С
        a6=ui->tableWidget_5->item(2,5)->text().toDouble();

        //Считывание коэффициента изменения амплитуды тока фазы А
        a7=ui->tableWidget_5->item(3,4)->text().toDouble();

        //Считывание коэффициента изменения амплитуды тока фазы В
        a8=ui->tableWidget_5->item(4,4)->text().toDouble();

        //Считывание коэффициента изменения амплитуды тока фазы С
        a9=ui->tableWidget_5->item(5,4)->text().toDouble();

        //Считывание коэффициента смещения тока фазы А
        a10=ui->tableWidget_5->item(3,5)->text().toDouble();

        //Считывание коэффициента смещения тока фазы В
        a11=ui->tableWidget_5->item(4,5)->text().toDouble();

        //Считывание коэффициента смещения тока фазы С
        a12=ui->tableWidget_5->item(5,5)->text().toDouble();

        //Считывание коэффициента изменения амплитуды частоты вращения
        a13=ui->tableWidget_5->item(6,4)->text().toDouble();

        //Считывание коэффициента изменения амплитуды электромагнитного момента M
        a14=ui->tableWidget_5->item(7,4)->text().toDouble();

        //Считывание коэффициента изменения амплитуды момента Mc
        a15=ui->tableWidget_5->item(8,4)->text().toDouble();

        //Считывание коэффициента смещения частоты вращения
        a16=ui->tableWidget_5->item(6,5)->text().toDouble();

        //Считывание коэффициента смещения электромагнитного момента M
        a17=ui->tableWidget_5->item(7,5)->text().toDouble();

        //Считывание коэффициента смещения момента Mc
        a18=ui->tableWidget_5->item(8,5)->text().toDouble();


    if(ui->tableWidget_5->model()->index(0,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(0, key, a4+a1*nabludatel.u_dev_a);
    }

    if(ui->tableWidget_5->model()->index(1,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(1, key, a5+a2*nabludatel.u_dev_b);
    }

    if(ui->tableWidget_5->model()->index(2,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(2, key, a6+a3*nabludatel.u_dev_c);
    }

    if(ui->tableWidget_5->model()->index(3,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(3, key, a10+a7*nabludatel.i_dev_a);
    }

    if(ui->tableWidget_5->model()->index(4,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(4, key, a11+a8*nabludatel.i_dev_b);
    }

    if(ui->tableWidget_5->model()->index(5,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(5, key, a12+a9*nabludatel.i_dev_c);
    }

    if(ui->tableWidget_5->model()->index(6,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(6, key, nabludatel.w_sr);
    }

    if(ui->tableWidget_5->model()->index(7,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(7, key, nabludatel.M_sr);
    }

    //Занесение итоговых данных в таблицу
    if (ui->tableWidget->item(0, 1) != 0)
    {
        ui->tableWidget->item(0, 1)->setText(QString("%1").arg(nabludatel.i_dev_a));
    }

    if (ui->tableWidget->item(1, 1) != 0)
    {
        ui->tableWidget->item(1, 1)->setText(QString("%1").arg(nabludatel.u_dev_a));
    }

    if (ui->tableWidget->item(2, 1) != 0)
    {
        ui->tableWidget->item(2, 1)->setText(QString("%1").arg(nabludatel.p_akt_a));
    }

    if (ui->tableWidget->item(3, 1) != 0)
    {
        ui->tableWidget->item(3, 1)->setText(QString("%1").arg(nabludatel.p_reakt_a));
    }

    if (ui->tableWidget->item(4, 1) != 0)
    {
        ui->tableWidget->item(4, 1)->setText(QString("%1").arg(nabludatel.p_poln_a));
    }

    if (ui->tableWidget->item(5, 1) != 0)
    {
        ui->tableWidget->item(5, 1)->setText(QString("%1").arg(nabludatel.cos_f_a));
    }

    if (ui->tableWidget->item(6, 1) != 0)
    {
        ui->tableWidget->item(6, 1)->setText(QString("%1").arg(nabludatel.i_dev_b));
    }

    if (ui->tableWidget->item(7, 1) != 0)
    {
        ui->tableWidget->item(7, 1)->setText(QString("%1").arg(nabludatel.u_dev_b));
    }
    if (ui->tableWidget->item(8, 1) != 0)
    {
        ui->tableWidget->item(8, 1)->setText(QString("%1").arg(nabludatel.p_akt_b));
    }

    if (ui->tableWidget->item(9, 1) != 0)
    {
        ui->tableWidget->item(9, 1)->setText(QString("%1").arg(nabludatel.p_reakt_b));
    }

    if (ui->tableWidget->item(10, 1) != 0)
    {
        ui->tableWidget->item(10, 1)->setText(QString("%1").arg(nabludatel.p_poln_b));
    }

    if (ui->tableWidget->item(11, 1) != 0)
    {
        ui->tableWidget->item(11, 1)->setText(QString("%1").arg(nabludatel.cos_f_b));
    }

    if (ui->tableWidget->item(12, 1) != 0)
    {
        ui->tableWidget->item(12, 1)->setText(QString("%1").arg(nabludatel.i_dev_c));
    }

    if (ui->tableWidget->item(13, 1) != 0)
    {
        ui->tableWidget->item(13, 1)->setText(QString("%1").arg(nabludatel.u_dev_c));
    }

    if (ui->tableWidget->item(14, 1) != 0)
    {
        ui->tableWidget->item(14, 1)->setText(QString("%1").arg(nabludatel.p_akt_c));
    }

    if (ui->tableWidget->item(15, 1) != 0)
    {
        ui->tableWidget->item(15, 1)->setText(QString("%1").arg(nabludatel.p_reakt_c));
    }

    if (ui->tableWidget->item(16, 1) != 0)
    {
        ui->tableWidget->item(16, 1)->setText(QString("%1").arg(nabludatel.p_poln_c));
    }

    if (ui->tableWidget->item(17, 1) != 0)
    {
        ui->tableWidget->item(17, 1)->setText(QString("%1").arg(nabludatel.cos_f_c));
    }

    if (ui->tableWidget->item(18, 1) != 0)
    {
        ui->tableWidget->item(18, 1)->setText(QString("%1").arg(nabludatel.p_akt));
    }

    if (ui->tableWidget->item(19, 1) != 0)
    {
        ui->tableWidget->item(19, 1)->setText(QString("%1").arg(nabludatel.p_reakt));
    }
    if (ui->tableWidget->item(20, 1) != 0)
    {
        ui->tableWidget->item(20, 1)->setText(QString("%1").arg(nabludatel.p_poln));
    }
    if (ui->tableWidget->item(21, 1) != 0)
    {
        ui->tableWidget->item(21, 1)->setText(QString("%1").arg(nabludatel.cos_f));
    }
    if (ui->tableWidget->item(22, 1) != 0)
    {
        ui->tableWidget->item(22, 1)->setText(QString("%1").arg(nabludatel.w_sr));
    }
    if (ui->tableWidget->item(23, 1) != 0)
    {
        ui->tableWidget->item(23, 1)->setText(QString("%1").arg(nabludatel.M_sr));
    }
    if (ui->tableWidget_4->item(0, 1) != 0)
    {
        ui->tableWidget_4->item(0, 1)->setText(QString::number(nabludatel.P1,'f',3));
    }

    if (ui->tableWidget_4->item(1, 1) != 0)
    {
        ui->tableWidget_4->item(1, 1)->setText(QString::number(nabludatel.dPel1,'f',3));
    }

    if (ui->tableWidget_4->item(2, 1) != 0)
    {
        ui->tableWidget_4->item(2, 1)->setText(QString::number(nabludatel.dPct,'f',3));
    }

    if (ui->tableWidget_4->item(3, 1) != 0)
    {
        ui->tableWidget_4->item(3, 1)->setText(QString::number(nabludatel.dPel2,'f',3));
    }

    if (ui->tableWidget_4->item(4, 1) != 0)
    {
        ui->tableWidget_4->item(4, 1)->setText(QString::number(nabludatel.dPdob,'f',3));
    }

    if (ui->tableWidget_4->item(5, 1) != 0)
    {
        ui->tableWidget_4->item(5, 1)->setText(QString::number(nabludatel.dPmech,'f',3));
    }

    if (ui->tableWidget_4->item(6, 1) != 0)
    {
        ui->tableWidget_4->item(6, 1)->setText(QString::number(nabludatel.P2,'f',3));
    }

    if (ui->tableWidget_4->item(7, 1) != 0)
    {
        ui->tableWidget_4->item(7, 1)->setText(QString::number(nabludatel.kpd,'f',3));
    }

    if (ui->tableWidget_4->item(8, 1) != 0)
    {
        ui->tableWidget_4->item(8, 1)->setText(QString::number(nabludatel.cos_f,'f',3));
    }

    if (ui->tableWidget_5->item(0, 3) != 0)
    {
        ui->tableWidget_5->item(0, 3)->setText(QString::number(nabludatel.u_dev_a,'f',3));
    }

    if (ui->tableWidget_5->item(1, 3) != 0)
    {
        ui->tableWidget_5->item(1, 3)->setText(QString::number(nabludatel.u_dev_b,'f',3));
    }

    if (ui->tableWidget_5->item(2, 3) != 0)
    {
        ui->tableWidget_5->item(2, 3)->setText(QString::number(nabludatel.u_dev_c,'f',3));
    }

    if (ui->tableWidget_5->item(3, 3) != 0)
    {
        ui->tableWidget_5->item(3, 3)->setText(QString::number(nabludatel.i_dev_a,'f',3));
    }

    if (ui->tableWidget_5->item(4, 3) != 0)
    {
        ui->tableWidget_5->item(4, 3)->setText(QString::number(nabludatel.i_dev_b,'f',3));
    }

    if (ui->tableWidget_5->item(5, 3) != 0)
    {
        ui->tableWidget_5->item(5, 3)->setText(QString::number(nabludatel.i_dev_c,'f',3));
    }

    if (ui->tableWidget_5->item(6, 3) != 0)
    {
        ui->tableWidget_5->item(6, 3)->setText(QString::number(nabludatel.w_sr,'f',3));
    }

    if (ui->tableWidget_5->item(7, 3) != 0)
    {
        ui->tableWidget_5->item(7, 3)->setText(QString::number(nabludatel.M_sr,'f',3));
    }

    if (ui->tableWidget_5->item(8, 3) != 0)
    {
        ui->tableWidget_5->item(8, 3)->setText(QString::number(nabludatel.Mc,'f',3));
    }

    //вывод графиков на экран plot

    if(ui->tableWidget_5->model()->index(0,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(0, key, a4+a1*nabludatel.u_dev_a);
    }

    if(ui->tableWidget_5->model()->index(1,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(1, key, a5+a2*nabludatel.u_dev_b);
    }

    if(ui->tableWidget_5->model()->index(2,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(2, key, a6+a3*nabludatel.u_dev_c);
    }

    if(ui->tableWidget_5->model()->index(3,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(3, key, a10+a7*nabludatel.i_dev_a);
    }

    if(ui->tableWidget_5->model()->index(4,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(4, key, a11+a8*nabludatel.i_dev_b);
    }

    if(ui->tableWidget_5->model()->index(5,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(5, key, a12+a9*nabludatel.i_dev_c);
    }

    if(ui->tableWidget_5->model()->index(6,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(6, key, a16+a13*nabludatel.w_sr);
    }

    if(ui->tableWidget_5->model()->index(7,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(7, key, a17+a14*nabludatel.M_sr);
    }

    if(ui->tableWidget_5->model()->index(8,2).data(Qt::CheckStateRole)==Qt::Checked)
    {
        ui->plot->addPoint(8, key, a18+a15*nabludatel.Mc);
    }

    }
}

void electromagn::raschet_el()
{
    if(ui->radioButton->isChecked())
    {
        //БВАС без датчика скорости + наблюдатель скорости
        QSettings settings;

        DataSourceBVAS* dataSourceBVAS = new DataSourceBVAS();

        dataSourceBVAS->IaZeroLevel = settings.value("calibration/IaZero", 0.0).toDouble();
        dataSourceBVAS->IbZeroLevel = settings.value("calibration/IbZero", 0.0).toDouble();
        dataSourceBVAS->IcZeroLevel = settings.value("calibration/IcZero", 0.0).toDouble();

        dataSourceBVAS->UaZeroLevel = settings.value("calibration/UaZero", 0.0).toDouble();
        dataSourceBVAS->UbZeroLevel = settings.value("calibration/UbZero", 0.0).toDouble();
        dataSourceBVAS->UcZeroLevel = settings.value("calibration/UcZero", 0.0).toDouble();

        dataSourceBVAS->IaCalibrationCoeff = settings.value("calibration/IaCoeff", 1.0).toDouble();
        dataSourceBVAS->IbCalibrationCoeff = settings.value("calibration/IbCoeff", 1.0).toDouble();
        dataSourceBVAS->IcCalibrationCoeff = settings.value("calibration/IcCoeff", 1.0).toDouble();

        dataSourceBVAS->UaCalibrationCoeff = settings.value("calibration/UaCoeff", 1.0).toDouble();
        dataSourceBVAS->UbCalibrationCoeff = settings.value("calibration/UbCoeff", 1.0).toDouble();
        dataSourceBVAS->UcCalibrationCoeff = settings.value("calibration/UcCoeff", 1.0).toDouble();

        dataSource = dataSourceBVAS;

        dataSource->init();
        nabludatel.init(base.R1, base.R2, base.L1, base.L2, base.Lm);
        connect(dataSource, &DataSource::ready, this, &electromagn::realtimeDataSlot);
        connect(dataSourceBVAS, &DataSourceBVAS::bvasFailure, this, &electromagn::bvasFailureSlot);

    }

    if(ui->radioButton_2->isChecked())
    {
        //БВАС с датчиком скорости + наблюдатель частично (момента)
        //dataSource->init();
        //nabludatel_part.init(base.R1, base.R2, base.L1, base.L2, base.Lm);

    }

    if(ui->radioButton_3->isChecked())
    {
        //Модель двигателя
        Model_el.init_el(base.R1, base.R2, base.L1, base.L2, base.Lm, combo->currentIndex(),
                         ui->tableWidget_3->model()->index(3,1).data().toDouble(),
                         ui->tableWidget_3->model()->index(2,1).data().toDouble(),
                         ui->tableWidget_3->model()->index(4,1).data().toDouble());
                         connect(&Model_el, &Model_el::ready, this, &electromagn::realtimeDataSlot);

    }

    if(ui->radioButton_4->isChecked())
    {
        dataSource = new DataSource_file();


        dataSource->init();
        nabludatel.init(base.R1, base.R2, base.L1, base.L2, base.Lm);
        connect(dataSource, &DataSource::ready, this, &electromagn::realtimeDataSlot);

    }

    ui->plot->clear();
    for (int i = 0; i < dataLineColors.size(); i++)
    {
        ui->plot->addDataLine(dataLineColors[i], 0);
    }
   // addDataLines();
    time->start();
}

void electromagn::stop()
{
    count = 0;

    if((ui->radioButton->isChecked()) || (ui->radioButton_4->isChecked()))
    {
        if (dataSource != nullptr )
        {
          dataSource->stop();
          disconnect(dataSource, &DataSource::ready, this, &electromagn::realtimeDataSlot);
          delete dataSource;
        }
    }

    if(ui->radioButton_2->isChecked())
    {

    }

    if(ui->radioButton_3->isChecked())
    {
        Model_el.stop();
        disconnect(&Model_el, &Model_el::ready, this, &electromagn::realtimeDataSlot);
    }
}

void electromagn::on_pushButton_clicked()
{
    base.i_a=ui->tableWidget->item(0,1)->text().toDouble();
    base.u_a=ui->tableWidget->item(1,1)->text().toDouble();
    base.p_akt_a=ui->tableWidget->item(2,1)->text().toDouble();
    base.p_react_a=ui->tableWidget->item(3,1)->text().toDouble();
    base.p_poln_a=ui->tableWidget->item(4,1)->text().toDouble();
    base.cosf_a=ui->tableWidget->item(5,1)->text().toDouble();

    base.i_b=ui->tableWidget->item(6,1)->text().toDouble();
    base.u_b=ui->tableWidget->item(7,1)->text().toDouble();
    base.p_akt_b=ui->tableWidget->item(8,1)->text().toDouble();
    base.p_react_b=ui->tableWidget->item(9,1)->text().toDouble();
    base.p_poln_b=ui->tableWidget->item(10,1)->text().toDouble();
    base.cosf_b=ui->tableWidget->item(11,1)->text().toDouble();

    base.i_c=ui->tableWidget->item(12,1)->text().toDouble();
    base.u_c=ui->tableWidget->item(13,1)->text().toDouble();
    base.p_akt_c=ui->tableWidget->item(14,1)->text().toDouble();
    base.p_react_c=ui->tableWidget->item(15,1)->text().toDouble();
    base.p_poln_c=ui->tableWidget->item(16,1)->text().toDouble();
    base.cosf_c=ui->tableWidget->item(17,1)->text().toDouble();

    base.p_akt=ui->tableWidget->item(18,1)->text().toDouble();
    base.p_react=ui->tableWidget->item(19,1)->text().toDouble();
    base.p_poln=ui->tableWidget->item(20,1)->text().toDouble();
    base.cosf=ui->tableWidget->item(21,1)->text().toDouble();
}

void electromagn::addDataLines()
{
//    ui->plot->addDataLine(Qt::blue, 0);
//    ui->plot->addDataLine(Qt::red, 0);
//    ui->plot->addDataLine(Qt::green, 0);
//    ui->plot->addDataLine(Qt::cyan, 0);
//    ui->plot->addDataLine(QColor(47, 15, 163), 0);
//    ui->plot->addDataLine(QColor(47, 15, 163), 0);
//    ui->plot->addDataLine(QColor(102, 245, 7), 0);
//    ui->plot->addDataLine(QColor(102, 245, 7), 0);
//    ui->plot->addDataLine(QColor(102, 245, 7), 0);
}


void electromagn::on_pushButton_2_clicked()
{
    QSettings settings;
    base.dataSourceFilename = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),

                                settings.value("dataSource/LastPath", "").toString(),
                                "txt files (*.txt);;All files (*.*)");
}


void electromagn::on_radioButton_toggled(bool checked)
{
    if (checked)
    {
       ui->pushButton_2->setEnabled(false);
    }
}


void electromagn::on_radioButton_2_toggled(bool checked)
{
    if (checked)
    {
       ui->pushButton_2->setEnabled(false);
    }
}


void electromagn::on_radioButton_3_toggled(bool checked)
{
    if (checked)
    {
       ui->pushButton_2->setEnabled(false);
    }
}


void electromagn::on_radioButton_4_toggled(bool checked)
{
    if (checked)
    {
       ui->pushButton_2->setEnabled(true);
    }
}


void electromagn::on_radioButton_4_clicked()
{

}


void electromagn::on_radioButton_3_clicked()
{

}

void electromagn::bvasFailureSlot()
{
    wf->ui->action_20->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-start.svg"));
    wf->ui->action_21->setEnabled(false);
    QMessageBox::critical(this, "Ошибка!", "Ошибка подключения BVAS!");
}

