#include "electromagn.h"
#include "ui_electromagn.h"
#include "base.h"
#include "model_el.h"
#include "nabludatel.h"
#include "nabludatel_part.h"
#include <QLinearGradient>
#include <QMessageBox>

model_el model_el;
QPoint p1,p2;
QCursor curs;

electromagn::electromagn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::electromagn)
{
    ui->setupUi(this);
    ui->widget->setBufferDevicePixelRatio(.5);

    time=new QElapsedTimer();
    ui->widget->setMaximumSize(ui->widget->maximumWidth(), ui->widget->maximumHeight());
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

    ui->widget->setMouseTracking(true);
    ui->widget->addGraph();
    ui->widget->graph(0)->setName("График напряжения статора Ua");
    ui->widget->graph(0)->setPen(QPen(Qt::blue));
    ui->widget->addGraph();
    ui->widget->graph(1)->setName("График напряжения статора Ub");
    ui->widget->graph(1)->setPen(QPen(Qt::red));
    ui->widget->addGraph();
    ui->widget->graph(2)->setName("График напряжения статора Uс");
    ui->widget->graph(2)->setPen(QPen(Qt::green));
    ui->widget->addGraph();
    ui->widget->graph(3)->setName("График тока статора Iа");
    ui->widget->graph(3)->setPen(QPen(Qt::cyan));
    ui->widget->addGraph();
    ui->widget->graph(4)->setName("График тока статора Ib");
    ui->widget->graph(4)->setPen(QPen(QColor(47, 15, 163)));
    ui->widget->addGraph();
    ui->widget->graph(5)->setName("График тока статора Ic");
    ui->widget->graph(5)->setPen(QPen(QColor(47, 15, 163)));
    ui->widget->addGraph();
    ui->widget->graph(6)->setName("График скорости вращения вала w");
    ui->widget->graph(6)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget->addGraph();
    ui->widget->graph(7)->setName("График момента на валу M");
    ui->widget->graph(7)->setPen(QPen(QColor(102, 245, 7)));
    ui->widget->addGraph();
    ui->widget->graph(8)->setName("График момента Mc");
    ui->widget->graph(8)->setPen(QPen(QColor(102, 245, 7)));


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

    this->showMaximized();

    //Заполнение таблицы результатов
    ui->tableWidget->setRowCount(24);
    ui->tableWidget->setColumnCount(2);
    QStringList name;
    name << "Сигнал" << "Величина";
    ui->tableWidget->setHorizontalHeaderLabels(name);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    //ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
   ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget->verticalHeader()->setVisible(false);
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

    QColor c=QColor(Qt::green).lighter(180);
    for (int i=0; i<24; i++)
            for(int j=0;j<1;j++)
           {
               ui->tableWidget->item(i,j)->setBackground(c);
           }
    ui->tableWidget->item(0,0)->setBackground(c);

    //Заполнений таблицы настроек
    ui->tableWidget_2->setRowCount(20);
    ui->tableWidget_2->setColumnCount(2);
    QStringList name_2;
    name << "Свойство" << "Значение";
    ui->tableWidget_2->setHorizontalHeaderLabels(name);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_2->verticalHeader()->setVisible(true);
    ui->tableWidget_2->setItem(0, 0, new QTableWidgetItem("Отображение графика №1"));
    ui->tableWidget_2->setItem(1, 0, new QTableWidgetItem("Отображение графика №2"));
    ui->tableWidget_2->setItem(2, 0, new QTableWidgetItem("Отображение графика №3"));
    ui->tableWidget_2->setItem(3, 0, new QTableWidgetItem("Отображение графика №4"));
    ui->tableWidget_2->setItem(4, 0, new QTableWidgetItem("Отображение графика №5"));
    ui->tableWidget_2->setItem(5, 0, new QTableWidgetItem("Отображение графика №6"));
    QTableWidgetItem *item = new QTableWidgetItem("Item");
    item->setCheckState(Qt::Checked);
    item->setText("Напряжение фазы А");
    ui->tableWidget_2->setItem(0, 1, item);
    QTableWidgetItem *item2 = new QTableWidgetItem("Item2");
    item2->setCheckState(Qt::Checked);
    item2->setText("Напряжение фазы В");
    ui->tableWidget_2->setItem(1, 1, item2);
    QTableWidgetItem *item3 = new QTableWidgetItem("Item3");
    item3->setCheckState(Qt::Checked);
    item3->setText("Напряжение фазы С");
    ui->tableWidget_2->setItem(2, 1, item3);
    QTableWidgetItem *item4 = new QTableWidgetItem("Item4");
    item4->setCheckState(Qt::Checked);
    item4->setText("Ток фазы А");
    ui->tableWidget_2->setItem(3, 1, item4);
    QTableWidgetItem *item5 = new QTableWidgetItem("Item5");
    item5->setCheckState(Qt::Checked);
    item5->setText("Ток фазы В");
    ui->tableWidget_2->setItem(4, 1, item5);
    QTableWidgetItem *item6 = new QTableWidgetItem("Item6");
    item6->setCheckState(Qt::Checked);
    item6->setText("Ток фазы С");
    ui->tableWidget_2->setItem(5, 1, item6);
    QTableWidgetItem *item7 = new QTableWidgetItem("Item7");
    item7->setCheckState(Qt::Checked);
    item7->setText("Частота вращения");
    ui->tableWidget_2->setItem(18, 1, item7);
    QTableWidgetItem *item8 = new QTableWidgetItem("Item8");
    item8->setCheckState(Qt::Checked);
    item8->setText("Момент");
    ui->tableWidget_2->setItem(19, 1, item8);

    ui->tableWidget_2->setItem(18, 0, new QTableWidgetItem("Отображение графика №7"));
    ui->tableWidget_2->setItem(19, 0, new QTableWidgetItem("Отображение графика №8"));

    ui->tableWidget_2->setItem(6, 0, new QTableWidgetItem("Амплитуда напряжения фазы А"));
    ui->tableWidget_2->setItem(6, 1, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->setItem(7, 0, new QTableWidgetItem("Амплитуда напряжения фазы В"));
    ui->tableWidget_2->setItem(7, 1, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->setItem(8, 0, new QTableWidgetItem("Амплитуда напряжения фазы С"));
    ui->tableWidget_2->setItem(8, 1, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->setItem(9, 0, new QTableWidgetItem("Смещение напряжения фазы А"));
    ui->tableWidget_2->setItem(9, 1, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->setItem(10, 0, new QTableWidgetItem("Смещение напряжения фазы В"));
    ui->tableWidget_2->setItem(10, 1, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->setItem(11, 0, new QTableWidgetItem("Смещение напряжения фазы С"));
    ui->tableWidget_2->setItem(11, 1, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->setItem(12, 0, new QTableWidgetItem("Амплитуда тока фазы А"));
    ui->tableWidget_2->setItem(12, 1, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->setItem(13, 0, new QTableWidgetItem("Амплитуда тока фазы В"));
    ui->tableWidget_2->setItem(13, 1, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->setItem(14, 0, new QTableWidgetItem("Амплитуда тока фазы С"));
    ui->tableWidget_2->setItem(14, 1, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_2->setItem(15, 0, new QTableWidgetItem("Смещение тока фазы А"));
    ui->tableWidget_2->setItem(15, 1, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->setItem(16, 0, new QTableWidgetItem("Смещение тока фазы В"));
    ui->tableWidget_2->setItem(16, 1, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_2->setItem(17, 0, new QTableWidgetItem("Смещение тока фазы С"));
    ui->tableWidget_2->setItem(17, 1, new QTableWidgetItem(QString("%1").arg(0)));

    //цветовая палитра таблицы tableWidget_2
    QPalette p=ui->tableWidget_2->palette();
    p.setColor(QPalette::Base, QColor(191, 255, 191));
    p.setColor(QPalette::AlternateBase, QColor(222, 255, 222));
    ui->tableWidget_2->setPalette(p);

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

    //Заполнение полей левой части таблицы для пояснения чекбоксов таблицы tableWidget_3
    ui->tableWidget_3->setItem(5, 0, new QTableWidgetItem("Отображение графика №1"));
    ui->tableWidget_3->setItem(6, 0, new QTableWidgetItem("Отображение графика №2"));
    ui->tableWidget_3->setItem(7, 0, new QTableWidgetItem("Отображение графика №3"));
    ui->tableWidget_3->setItem(8, 0, new QTableWidgetItem("Отображение графика №4"));
    ui->tableWidget_3->setItem(9, 0, new QTableWidgetItem("Отображение графика №5"));
    ui->tableWidget_3->setItem(10, 0, new QTableWidgetItem("Отображение графика №6"));
    ui->tableWidget_3->setItem(11, 0, new QTableWidgetItem("Отображение графика №7"));
    ui->tableWidget_3->setItem(12, 0, new QTableWidgetItem("Отображение графика №8"));
    ui->tableWidget_3->setItem(29, 0, new QTableWidgetItem("Отображение графика №9"));

    //вставка чекбоксов таблицы tableWidget_3
    QTableWidgetItem *item11 = new QTableWidgetItem("Item11");
    item11->setCheckState(Qt::Checked);
    item11->setText("Напряжение фазы А");
    ui->tableWidget_3->setItem(5, 1, item11);

    QTableWidgetItem *item12 = new QTableWidgetItem("Item12");
    item12->setCheckState(Qt::Checked);
    item12->setText("Напряжение фазы В");
    ui->tableWidget_3->setItem(6, 1, item12);

    QTableWidgetItem *item13 = new QTableWidgetItem("Item13");
    item13->setCheckState(Qt::Checked);
    item13->setText("Напряжение фазы С");
    ui->tableWidget_3->setItem(7, 1, item13);

    QTableWidgetItem *item14 = new QTableWidgetItem("Item14");
    item14->setCheckState(Qt::Checked);
    item14->setText("Ток фазы А");
    ui->tableWidget_3->setItem(8, 1, item14);

    QTableWidgetItem *item15 = new QTableWidgetItem("Item15");
    item15->setCheckState(Qt::Checked);
    item15->setText("Ток фазы В");
    ui->tableWidget_3->setItem(9, 1, item15);

    QTableWidgetItem *item16 = new QTableWidgetItem("Item16");
    item16->setCheckState(Qt::Checked);
    item16->setText("Ток фазы С");
    ui->tableWidget_3->setItem(10, 1, item16);

    QTableWidgetItem *item17 = new QTableWidgetItem("Item17");
    item17->setCheckState(Qt::Checked);
    item17->setText("скорость вращения");
    ui->tableWidget_3->setItem(11, 1, item17);

    QTableWidgetItem *item18 = new QTableWidgetItem("Item18");
    item18->setCheckState(Qt::Checked);
    item18->setText("Момент на валу");
    ui->tableWidget_3->setItem(12, 1, item18);

    QTableWidgetItem *item19 = new QTableWidgetItem("Item19");
    item19->setCheckState(Qt::Checked);
    item19->setText("Момент Mc");
    ui->tableWidget_3->setItem(29, 1, item19);

    //Программирование настроек сигналов таблицы tableWidget_3
    ui->tableWidget_3->setItem(13, 0, new QTableWidgetItem("Амплитуда напряжения фазы А"));
    ui->tableWidget_3->setItem(13, 1, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_3->setItem(14, 0, new QTableWidgetItem("Амплитуда напряжения фазы В"));
    ui->tableWidget_3->setItem(14, 1, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_3->setItem(15, 0, new QTableWidgetItem("Амплитуда напряжения фазы С"));
    ui->tableWidget_3->setItem(15, 1, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_3->setItem(16, 0, new QTableWidgetItem("Смещение напряжения фазы А"));
    ui->tableWidget_3->setItem(16, 1, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_3->setItem(17, 0, new QTableWidgetItem("Смещение напряжения фазы В"));
    ui->tableWidget_3->setItem(17, 1, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_3->setItem(18, 0, new QTableWidgetItem("Смещение напряжения фазы С"));
    ui->tableWidget_3->setItem(18, 1, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_3->setItem(19, 0, new QTableWidgetItem("Амплитуда тока фазы А"));
    ui->tableWidget_3->setItem(19, 1, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_3->setItem(20, 0, new QTableWidgetItem("Амплитуда тока фазы В"));
    ui->tableWidget_3->setItem(20, 1, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_3->setItem(21, 0, new QTableWidgetItem("Амплитуда тока фазы С"));
    ui->tableWidget_3->setItem(21, 1, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_3->setItem(22, 0, new QTableWidgetItem("Смещение тока фазы А"));
    ui->tableWidget_3->setItem(22, 1, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_3->setItem(23, 0, new QTableWidgetItem("Смещение тока фазы В"));
    ui->tableWidget_3->setItem(23, 1, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_3->setItem(24, 0, new QTableWidgetItem("Смещение тока фазы С"));
    ui->tableWidget_3->setItem(24, 1, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_3->setItem(25, 0, new QTableWidgetItem("Амплитуда скорости вращения"));
    ui->tableWidget_3->setItem(25, 1, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_3->setItem(26, 0, new QTableWidgetItem("Амплитуда момента на валу"));
    ui->tableWidget_3->setItem(26, 1, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget_3->setItem(27, 0, new QTableWidgetItem("Смещение скорости вращения"));
    ui->tableWidget_3->setItem(27, 1, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget_3->setItem(28, 0, new QTableWidgetItem("Смещение момента на валу"));
    ui->tableWidget_3->setItem(28, 1, new QTableWidgetItem(QString("%1").arg(0)));

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
}


electromagn::~electromagn()
{
    delete ui;
}

void electromagn::realtimeDataSlot()
{
    double a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12;
    key = time->elapsed()/1000.0;

    if(ui->radioButton->isChecked())
    {
        nabludatel.rasch(&dataSourceBVAS);

        //Считывание коэффициента изменения амплитуды напряжения фазы А

        if(ui->tableWidget_2->item(6,1)!=0)
        {
            a1=ui->tableWidget_2->item(6,1)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды напряжения фазы В

        if(ui->tableWidget_2->item(7,1)!=0)
        {
            a2=ui->tableWidget_2->item(7,1)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды напряжения фазы С

        if(ui->tableWidget_2->item(8,1)!=0)
        {
            a3=ui->tableWidget_2->item(8,1)->text().toDouble();
        }

        //Считывание коэффициента смещения напряжения фазы А

        if(ui->tableWidget_2->item(9,1)!=0)
        {
            a4=ui->tableWidget_2->item(9,1)->text().toDouble();
        }

        //Считывание коэффициента смещения напряжения фазы В

        if(ui->tableWidget_2->item(10,1)!=0)
        {
            a5=ui->tableWidget_2->item(10,1)->text().toDouble();
        }

        //Считывание коэффициента смещения напряжения фазы С

        if(ui->tableWidget_2->item(11,1)!=0)
        {
            a6=ui->tableWidget_2->item(11,1)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды тока фазы А

        if(ui->tableWidget_2->item(12,1)!=0)
        {
            a7=ui->tableWidget_2->item(12,1)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды тока фазы В

        if(ui->tableWidget_2->item(13,1)!=0)
        {
            a8=ui->tableWidget_2->item(13,1)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды тока фазы С

        if(ui->tableWidget_2->item(14,1)!=0)
        {
            a9=ui->tableWidget_2->item(14,1)->text().toDouble();
        }

        //Считывание коэффициента смещения тока фазы А

        if(ui->tableWidget_2->item(15,1)!=0)
        {
            a10=ui->tableWidget_2->item(15,1)->text().toDouble();
        }

        //Считывание коэффициента смещения тока фазы В

        if(ui->tableWidget_2->item(16,1)!=0)
        {
            a11=ui->tableWidget_2->item(16,1)->text().toDouble();
        }

        //Считывание коэффициента смещения тока фазы С

        if(ui->tableWidget_2->item(17,1)!=0)
        {
            a12=ui->tableWidget_2->item(17,1)->text().toDouble();
        }


    if(ui->tableWidget_2->model()->index(0,1).data(Qt::CheckStateRole)==Qt::Checked)
    {
        //ui->widget->graph(0)->data()->clear();
        ui->widget->graph(0)->addData(key, a4+a1*nabludatel.u_dev_a);
        ui->widget->graph(0)->rescaleValueAxis();
        //ui->widget->xAxis->setRange(key, 8, Qt::AlignRight);
        //ui->widget->replot();
    }

    if(ui->tableWidget_2->model()->index(1,1).data(Qt::CheckStateRole)==Qt::Checked)
    {
        //ui->widget->graph(1)->data()->clear();
        ui->widget->graph(1)->addData(key, a5+a2*nabludatel.u_dev_b);
        ui->widget->graph(1)->rescaleValueAxis(true);
        //ui->widget->xAxis->setRange(key, 8, Qt::AlignRight);
        //ui->widget->replot();
    }

    if(ui->tableWidget_2->model()->index(2,1).data(Qt::CheckStateRole)==Qt::Checked)
    {
        //ui->widget->graph(2)->data()->clear();
        ui->widget->graph(2)->addData(key, a6+a3*nabludatel.u_dev_c);
        ui->widget->graph(2)->rescaleValueAxis(true);
        //ui->widget->xAxis->setRange(key, 8, Qt::AlignRight);
        //ui->widget->replot();
    }

    if(ui->tableWidget_2->model()->index(3,1).data(Qt::CheckStateRole)==Qt::Checked)
    {
        //ui->widget->graph(3)->data()->clear();
        ui->widget->graph(3)->addData(key, a10+a7*nabludatel.i_dev_a);
        ui->widget->graph(3)->rescaleValueAxis(true);
        //ui->widget->xAxis->setRange(key, 8, Qt::AlignRight);
        //ui->widget->replot();
    }

    if(ui->tableWidget_2->model()->index(4,1).data(Qt::CheckStateRole)==Qt::Checked)
    {
        //ui->widget->graph(4)->data()->clear();
        ui->widget->graph(4)->addData(key, a11+a8*nabludatel.i_dev_b);
        ui->widget->graph(4)->rescaleValueAxis(true);
        //ui->widget->xAxis->setRange(key, 8, Qt::AlignRight);
        //ui->widget->replot();
    }

    if(ui->tableWidget_2->model()->index(5,1).data(Qt::CheckStateRole)==Qt::Checked)
    {
        //ui->widget->graph(5)->data()->clear();
        ui->widget->graph(5)->addData(key, a12+a9*nabludatel.i_dev_c);
        ui->widget->graph(5)->rescaleValueAxis(true);
        //ui->widget->xAxis->setRange(key, 8, Qt::AlignRight);
        //ui->widget->replot();
    }

    if(ui->tableWidget_2->model()->index(18,1).data(Qt::CheckStateRole)==Qt::Checked)
    {
        //ui->widget->graph(5)->data()->clear();
        ui->widget->graph(6)->addData(key, nabludatel.w);
        ui->widget->graph(6)->rescaleValueAxis(true);
        //ui->widget->xAxis->setRange(key, 8, Qt::AlignRight);
        //ui->widget->replot();
    }

    if(ui->tableWidget_2->model()->index(19,1).data(Qt::CheckStateRole)==Qt::Checked)
    {
        //ui->widget->graph(5)->data()->clear();
        ui->widget->graph(7)->addData(key, nabludatel.M_sr);
        ui->widget->graph(7)->rescaleValueAxis(true);
        //ui->widget->xAxis->setRange(key, 8, Qt::AlignRight);
        //ui->widget->replot();
    }

    ui->widget->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->widget->replot();

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
        nabludatel_part.rasch(&dataSourceBVASw);
        count++;

        if (count % 100 == 0)
        {
            count = 1;

            ui->widget->graph(0)->addData(key, nabludatel_part.Ua);
            ui->widget->graph(1)->addData(key, nabludatel_part.Ub);
            ui->widget->graph(2)->addData(key, nabludatel_part.Ia);
            ui->widget->graph(3)->addData(key, nabludatel_part.Ib);
            ui->widget->graph(4)->addData(key, nabludatel_part.M);
            ui->widget->graph(5)->addData(key, dataSourceBVASw.w);

            ui->widget->graph(0)->rescaleValueAxis();
            ui->widget->graph(1)->rescaleValueAxis(true);
            ui->widget->graph(2)->rescaleValueAxis(true);
            ui->widget->graph(3)->rescaleValueAxis(true);
            ui->widget->graph(4)->rescaleValueAxis(true);
            ui->widget->graph(5)->rescaleValueAxis(true);
            ui->widget->xAxis->setRange(key, 8, Qt::AlignRight);
            ui->widget->replot();
        }
    }

    if(ui->radioButton_3->isChecked())
    {
        double b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15,b16;
        for (int i = 0; i < 1000; i++)
        {
            model_el.rasch();
        }

        //Считывание значения времени цикла Тц

        if(ui->tableWidget_3->item(1,1)!=0)
        {
            model_el.Tc=ui->tableWidget_3->item(1,1)->text().toDouble();
        }

        //Считывание значения времени работы tp

        if(ui->tableWidget_3->item(2,1)!=0)
        {
            model_el.tp=ui->tableWidget_3->item(2,1)->text().toDouble();
        }

        //Считывание значения времени работы Mc

        if(ui->tableWidget_3->item(3,1)!=0)
        {
            model_el.Mc_n=ui->tableWidget_3->item(3,1)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды напряжения фазы А

        if(ui->tableWidget_3->item(13,1)!=0)
        {
            b1=ui->tableWidget_3->item(13,1)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды напряжения фазы В

        if(ui->tableWidget_3->item(14,1)!=0)
        {
            b2=ui->tableWidget_3->item(14,1)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды напряжения фазы С

        if(ui->tableWidget_3->item(15,1)!=0)
        {
            b3=ui->tableWidget_3->item(15,1)->text().toDouble();
        }

        //Считывание коэффициента смещения напряжения фазы А

        if(ui->tableWidget_3->item(16,1)!=0)
        {
            b4=ui->tableWidget_3->item(16,1)->text().toDouble();
        }

        //Считывание коэффициента смещения напряжения фазы В

        if(ui->tableWidget_3->item(17,1)!=0)
        {
            b5=ui->tableWidget_3->item(17,1)->text().toDouble();
        }

        //Считывание коэффициента смещения напряжения фазы С

        if(ui->tableWidget_3->item(18,1)!=0)
        {
            b6=ui->tableWidget_3->item(18,1)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды тока фазы А

        if(ui->tableWidget_3->item(19,1)!=0)
        {
            b7=ui->tableWidget_3->item(20,1)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды тока фазы В

        if(ui->tableWidget_3->item(20,1)!=0)
        {
            b8=ui->tableWidget_3->item(20,1)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды тока фазы С

        if(ui->tableWidget_3->item(21,1)!=0)
        {
            b9=ui->tableWidget_3->item(21,1)->text().toDouble();
        }

        //Считывание коэффициента смещения тока фазы А

        if(ui->tableWidget_3->item(22,1)!=0)
        {
            b10=ui->tableWidget_3->item(22,1)->text().toDouble();
        }

        //Считывание коэффициента смещения тока фазы В

        if(ui->tableWidget_3->item(23,1)!=0)
        {
            b11=ui->tableWidget_3->item(23,1)->text().toDouble();
        }

        //Считывание коэффициента смещения тока фазы С

        if(ui->tableWidget_3->item(24,1)!=0)
        {
            b12=ui->tableWidget_3->item(24,1)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды скорости вращения

        if(ui->tableWidget_3->item(25,1)!=0)
        {
            b13=ui->tableWidget_3->item(25,1)->text().toDouble();
        }

        //Считывание коэффициента изменения амплитуды момента на валу

        if(ui->tableWidget_3->item(26,1)!=0)
        {
            b14=ui->tableWidget_3->item(26,1)->text().toDouble();
        }

        //Считывание коэффициента смещения скорости вращения

        if(ui->tableWidget_3->item(27,1)!=0)
        {
            b15=ui->tableWidget_3->item(27,1)->text().toDouble();
        }

        //Считывание коэффициента смещения момента на валу

        if(ui->tableWidget_3->item(28,1)!=0)
        {
            b16=ui->tableWidget_3->item(28,1)->text().toDouble();
        }

        key = model_el.t;

        //вывод на qcustomPlot графика напряжения Ua после преобразования 2 в 3

        if(ui->tableWidget_3->model()->index(5,1).data(Qt::CheckStateRole)==Qt::Checked)
        {
           // ui->widget->graph(0)->addData(key, b4+b1*(0.8165*model_el.Ua));
            ui->widget->graph(0)->addData(key, b4+b1*(model_el.u_dev_a));
            ui->widget->graph(0)->rescaleValueAxis();
        }

        //вывод на qcustomPlot графика напряжения Ub после преобразования 2 в 3

        if(ui->tableWidget_3->model()->index(6,1).data(Qt::CheckStateRole)==Qt::Checked)
        {
           // ui->widget->graph(1)->addData(key, b5+b2*(-0.4082*model_el.Ua+0.7071*model_el.Ub));
            ui->widget->graph(1)->addData(key, b5+b2*(model_el.u_dev_b));
            ui->widget->graph(1)->rescaleValueAxis(true);
        }

        //вывод на qcustomPlot графика напряжения Uc после преобразования 2 в 3

        if(ui->tableWidget_3->model()->index(7,1).data(Qt::CheckStateRole)==Qt::Checked)
        {
            ui->widget->graph(2)->addData(key, b6+b3*(model_el.u_dev_c));
            ui->widget->graph(2)->rescaleValueAxis(true);
        }

        //вывод на qcustomPlot графика напряжения Ia после преобразования 2 в 3

        if(ui->tableWidget_3->model()->index(8,1).data(Qt::CheckStateRole)==Qt::Checked)
        {
            ui->widget->graph(3)->addData(key, b10+b7*(model_el.i_dev_a));
            ui->widget->graph(3)->rescaleValueAxis(true);
        }

        //вывод на qcustomPlot графика напряжения Ib после преобразования 2 в 3

        if(ui->tableWidget_3->model()->index(9,1).data(Qt::CheckStateRole)==Qt::Checked)
        {
            ui->widget->graph(4)->addData(key, b11+b8*(model_el.i_dev_b));
            ui->widget->graph(4)->rescaleValueAxis(true);
        }

        //вывод на qcustomPlot графика напряжения Ic после преобразования 2 в 3

        if(ui->tableWidget_3->model()->index(10,1).data(Qt::CheckStateRole)==Qt::Checked)
        {
            ui->widget->graph(5)->addData(key, b12+b9*(model_el.i_dev_c));
            ui->widget->graph(5)->rescaleValueAxis(true);
       }

        //вывод на qcustomPlot графика скорости omega

        if(ui->tableWidget_3->model()->index(11,1).data(Qt::CheckStateRole)==Qt::Checked)
        {
            ui->widget->graph(6)->addData(key, b15+b13*model_el.omega);
            ui->widget->graph(6)->rescaleValueAxis(true);
        }

        //вывод на qcustomPlot момента на валу M

        if(ui->tableWidget_3->model()->index(12,1).data(Qt::CheckStateRole)==Qt::Checked)
        {
            ui->widget->graph(7)->addData(key, b16+b14*model_el.M);
            ui->widget->graph(7)->rescaleValueAxis(true);
        }

        //вывод на qcustomPlot момента Mс

        if(ui->tableWidget_3->model()->index(29,1).data(Qt::CheckStateRole)==Qt::Checked)
        {
            ui->widget->graph(8)->addData(key, model_el.Mc);
            ui->widget->graph(8)->rescaleValueAxis(true);
        }

        //Занесение итоговых данных в таблицу
        if (ui->tableWidget->item(0, 1) != 0)
        {
            ui->tableWidget->item(0, 1)->setText(QString("%1").arg(model_el.i_dev_a));
        }

        if (ui->tableWidget->item(1, 1) != 0)
        {
            ui->tableWidget->item(1, 1)->setText(QString("%1").arg(model_el.u_dev_a));
        }

        if (ui->tableWidget->item(2, 1) != 0)
        {
            ui->tableWidget->item(2, 1)->setText(QString("%1").arg(model_el.p_akt_a));
        }

        if (ui->tableWidget->item(3, 1) != 0)
        {
            ui->tableWidget->item(3, 1)->setText(QString("%1").arg(model_el.p_reakt_a));
        }

        if (ui->tableWidget->item(4, 1) != 0)
        {
            ui->tableWidget->item(4, 1)->setText(QString("%1").arg(model_el.p_poln_a));
        }

        if (ui->tableWidget->item(5, 1) != 0)
        {
            ui->tableWidget->item(5, 1)->setText(QString("%1").arg(model_el.cos_f_a));
        }

        if (ui->tableWidget->item(6, 1) != 0)
        {
            ui->tableWidget->item(6, 1)->setText(QString("%1").arg(model_el.i_dev_b));
        }

        if (ui->tableWidget->item(7, 1) != 0)
        {
            ui->tableWidget->item(7, 1)->setText(QString("%1").arg(model_el.u_dev_b));
        }

        if (ui->tableWidget->item(8, 1) != 0)
        {
            ui->tableWidget->item(8, 1)->setText(QString("%1").arg(model_el.p_akt_b));
        }

        if (ui->tableWidget->item(9, 1) != 0)
        {
            ui->tableWidget->item(9, 1)->setText(QString("%1").arg(model_el.p_reakt_b));
        }

        if (ui->tableWidget->item(10, 1) != 0)
        {
            ui->tableWidget->item(10, 1)->setText(QString("%1").arg(model_el.p_poln_b));
        }

        if (ui->tableWidget->item(11, 1) != 0)
        {
            ui->tableWidget->item(11, 1)->setText(QString("%1").arg(model_el.cos_f_b));
        }

        if (ui->tableWidget->item(12, 1) != 0)
        {
            ui->tableWidget->item(12, 1)->setText(QString("%1").arg(model_el.i_dev_c));
        }

        if (ui->tableWidget->item(13, 1) != 0)
        {
            ui->tableWidget->item(13, 1)->setText(QString("%1").arg(model_el.u_dev_c));
        }

        if (ui->tableWidget->item(14, 1) != 0)
        {
            ui->tableWidget->item(14, 1)->setText(QString("%1").arg(model_el.p_akt_c));
        }

        if (ui->tableWidget->item(15, 1) != 0)
        {
            ui->tableWidget->item(15, 1)->setText(QString("%1").arg(model_el.p_reakt_c));
        }

        if (ui->tableWidget->item(16, 1) != 0)
        {
            ui->tableWidget->item(16, 1)->setText(QString("%1").arg(model_el.p_poln_c));
        }

        if (ui->tableWidget->item(17, 1) != 0)
        {
            ui->tableWidget->item(17, 1)->setText(QString("%1").arg(model_el.cos_f_c));
        }

        if (ui->tableWidget->item(18, 1) != 0)
        {
            ui->tableWidget->item(18, 1)->setText(QString("%1").arg(model_el.p_akt));
        }

        if (ui->tableWidget->item(19, 1) != 0)
        {
            ui->tableWidget->item(19, 1)->setText(QString("%1").arg(model_el.p_reakt));
        }

        if (ui->tableWidget->item(20, 1) != 0)
        {
            ui->tableWidget->item(20, 1)->setText(QString("%1").arg(model_el.p_poln));
        }

        if (ui->tableWidget->item(21, 1) != 0)
        {
            ui->tableWidget->item(21, 1)->setText(QString("%1").arg(model_el.cos_f));
        }

        if (ui->tableWidget->item(22, 1) != 0)
        {
            ui->tableWidget->item(22, 1)->setText(QString("%1").arg(model_el.omega));
        }
        if (ui->tableWidget->item(23, 1) != 0)
        {
            ui->tableWidget->item(23, 1)->setText(QString("%1").arg(model_el.M));
        }

        ui->widget->xAxis->setRange(key, 8, Qt::AlignRight);
        ui->widget->replot();

        if (ui->tableWidget_4->item(0, 1) != 0)
        {
            ui->tableWidget_4->item(0, 1)->setText(QString("%1").arg(model_el.P1));
        }

        if (ui->tableWidget_4->item(1, 1) != 0)
        {
            ui->tableWidget_4->item(1, 1)->setText(QString("%1").arg(model_el.dPel1));
        }

        if (ui->tableWidget_4->item(2, 1) != 0)
        {
            ui->tableWidget_4->item(2, 1)->setText(QString("%1").arg(model_el.dPct));
        }

        if (ui->tableWidget_4->item(3, 1) != 0)
        {
            ui->tableWidget_4->item(3, 1)->setText(QString("%1").arg(model_el.dPel2));
        }

        if (ui->tableWidget_4->item(4, 1) != 0)
        {
            ui->tableWidget_4->item(4, 1)->setText(QString("%1").arg(model_el.dPdob));
        }

        if (ui->tableWidget_4->item(5, 1) != 0)
        {
            ui->tableWidget_4->item(5, 1)->setText(QString("%1").arg(model_el.dPmech));
        }

        if (ui->tableWidget_4->item(6, 1) != 0)
        {
            ui->tableWidget_4->item(6, 1)->setText(QString("%1").arg(model_el.P2));
        }

        if (ui->tableWidget_4->item(7, 1) != 0)
        {
            ui->tableWidget_4->item(7, 1)->setText(QString("%1").arg(model_el.kpd));
        }

        if (ui->tableWidget_4->item(8, 1) != 0)
        {
            ui->tableWidget_4->item(8, 1)->setText(QString("%1").arg(model_el.cos_f));
        }




     /*   count++;

        if (count % 1000 == 0)
        {
            count = 1;

          //  ui->widget->graph(0)->addData(key, sqrt(pow(model_el.Ua,2)+pow(model_el.Ub,2)));
            ui->widget->graph(0)->addData(key, model_el.Ua);
            ui->widget->graph(1)->addData(key, model_el.Ub);
          //  ui->widget->graph(2)->addData(key, sqrt(pow(model_el.Ia,2)+pow(model_el.Ib,2)));
            ui->widget->graph(2)->addData(key, model_el.Ia);
            ui->widget->graph(3)->addData(key, model_el.Ib);

            ui->widget->graph(4)->addData(key, model_el.M);
            ui->widget->graph(5)->addData(key, model_el.omega);

            ui->widget->graph(0)->rescaleValueAxis();
            ui->widget->graph(1)->rescaleValueAxis(true);
            ui->widget->graph(2)->rescaleValueAxis(true);
            ui->widget->graph(3)->rescaleValueAxis(true);
            ui->widget->graph(4)->rescaleValueAxis(true);
            ui->widget->graph(5)->rescaleValueAxis(true);
            ui->widget->xAxis->setRange(key, 8, Qt::AlignRight);
            ui->widget->replot();
        }*/
    }
}

void electromagn::raschet_el()
{
    if(ui->radioButton->isChecked())
    {
        //БВАС без датчика скорости + наблюдатель скорости
        QSettings settings;

        dataSourceBVAS.IaZeroLevel = settings.value("calibration/IaZero", 0.0).toDouble();
        dataSourceBVAS.IbZeroLevel = settings.value("calibration/IbZero", 0.0).toDouble();
        dataSourceBVAS.IcZeroLevel = settings.value("calibration/IcZero", 0.0).toDouble();

        dataSourceBVAS.UaZeroLevel = settings.value("calibration/UaZero", 0.0).toDouble();
        dataSourceBVAS.UbZeroLevel = settings.value("calibration/UbZero", 0.0).toDouble();
        dataSourceBVAS.UcZeroLevel = settings.value("calibration/UcZero", 0.0).toDouble();

        dataSourceBVAS.IaCalibrationCoeff = settings.value("calibration/IaCoeff", 1.0).toDouble();
        dataSourceBVAS.IbCalibrationCoeff = settings.value("calibration/IbCoeff", 1.0).toDouble();
        dataSourceBVAS.IcCalibrationCoeff = settings.value("calibration/IcCoeff", 1.0).toDouble();

        dataSourceBVAS.UaCalibrationCoeff = settings.value("calibration/UaCoeff", 1.0).toDouble();
        dataSourceBVAS.UbCalibrationCoeff = settings.value("calibration/UbCoeff", 1.0).toDouble();
        dataSourceBVAS.UcCalibrationCoeff = settings.value("calibration/UcCoeff", 1.0).toDouble();

        dataSourceBVAS.init();
        nabludatel.init(base.R1, base.R2, base.L1, base.L2, base.Lm);
        connect(&dataSourceBVAS, &DataSourceBVAS::ready, this, &electromagn::realtimeDataSlot);

    }

    if(ui->radioButton_2->isChecked())
    {
        //БВАС с датчиком скорости + наблюдатель частично (момента)
        dataSourceBVASw.init();
        nabludatel_part.init(base.R1, base.R2, base.L1, base.L2, base.Lm);
    }

    if(ui->radioButton_3->isChecked())
    {
        //Модель двигателя
        model_el.init_el(base.R1, base.R2, base.L1, base.L2, base.Lm, combo->currentIndex(),
                         ui->tableWidget_3->model()->index(3,1).data().toDouble(),
                         ui->tableWidget_3->model()->index(2,1).data().toDouble(),
                         ui->tableWidget_3->model()->index(4,1).data().toDouble());
                         connect(&model_el, &model_el::ready, this, &electromagn::realtimeDataSlot);

    }
    ui->widget->graph(0)->data()->clear();
    ui->widget->graph(1)->data()->clear();
    ui->widget->graph(2)->data()->clear();
    ui->widget->graph(3)->data()->clear();
    ui->widget->graph(4)->data()->clear();
    ui->widget->graph(5)->data()->clear();
    ui->widget->replot();
    time->start();
}

void electromagn::stop()
{
    count = 0;

    disconnect(&dataSourceBVAS, &DataSourceBVAS::ready, this, &electromagn::realtimeDataSlot);

    disconnect(&model_el, &model_el::ready, this, &electromagn::realtimeDataSlot);

    if(ui->radioButton->isChecked())
    {
        dataSourceBVAS.stop();
    }

    if(ui->radioButton_2->isChecked())
    {

    }

    if(ui->radioButton_3->isChecked())
    {
        model_el.stop();
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




