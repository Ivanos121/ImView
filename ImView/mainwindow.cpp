#include "ui_mainwindow.h"
#include "mainwindow.h"

#include <QStyle>
#include <QDesktopWidget>
#include <QClipboard>
#include <QScreen>
#include <QSpinBox>
#include <QSplitter>
#include <QMessageBox>
#include <QuaZip-Qt5-1.3/quazip/JlCompress.h>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QColorDialog>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix_double.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_vector_double.h>
#include <iostream>
#include <fstream>
#include <cmath>

#include "base.h"
#include "model.h"
#include "datas.h"
#include "ui_datas.h"
#include "identf.h"
#include "ui_identf.h"
#include "electromagn.h"
#include "kalibr.h"
#include "teplovent.h"
#include "tepl_dannie.h"
#include "ui_tepl_dannie.h"
#include "ui_teplovent.h"
#include "ui_electromagn.h"
#include "ui_draw_line.h"
#include "ui_draw_poper.h"
#include "ui_teplschem.h"
#include "ui_vent_model.h"
#include "ui_trend.h"
#include "ui_vent_izm.h"
#include "ui_datas.h"
#include "vent_model.h"
#include "ui_vent_model.h"
#include "ui_vent_tract.h"
#include "gridlinedelegate.h"

Base base;
Base_tepl base_tepl;
Model modelss;
double teta_0,teta_1,teta_2,teta_3,teta_4,teta_5,teta_k,teta_c,teta_p, teta_v;
double lambda_10, lambda_21, lambda_c2,lambda_p2,lambda_30,lambda_c3,lambda_p3,lambda_3k,lambda_c4,lambda_pb,lambda_p5,
lambda_k0,lambda_45,lambda_50,lambda_b5;
double C_0,C_1,C_2,C_3,C_4,C_5,C_k,C_c,C_p,C_v;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->widget_2->wf=this;
    ui->widget_3->wf=this;
    ui->widget_5->wf=this;
    ui->widget_6->wf=this;
    ui->widget_5->ui->widget_4->wf=this;
    ui->widget->wf=this;

    ui->widget_5->ui->widget->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/ax_var/ax_var_2.html").absoluteFilePath()));
    ui->widget_5->ui->widget_5->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/rad_var/rad_var.html").absoluteFilePath()));
    ui->widget_6->ui->widget_2->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_tract/vent_tract.html").absoluteFilePath()));
    ui->widget_5->ui->widget_3->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/tepl_schen_zam/tepl_tract.html").absoluteFilePath()));

    ui->widget_5->ui->widget->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));
    ui->widget_5->ui->widget_5->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));
    ui->widget_6->ui->widget->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));


    showMaximized();
    ui->action_9->setEnabled(false);
    ui->action_21->setEnabled(false);

    ui->pushButton_5->setCheckable(true);
    ui->pushButton_5->setChecked(true);
    QObject::connect(ui->pushButton_5, &QPushButton::clicked, ui->stackedWidget, &MainWindow::setVisible);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::on_pushButton_5_clicked);

    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->action_15, &QAction::triggered, this, &MainWindow::onButtonClicked);
    connect(ui->action_23, &QAction::triggered, this, &MainWindow::onButtonClicked2);

    ui->treeView->setSelectionBehavior(QTreeView :: SelectRows); // Выбираем всю строку за раз
    ui->treeView->setSelectionMode(QTreeView :: SingleSelection); // Одиночный выбор, при этом вся строка над ним является одной строкой меню
    ui->treeView->setAlternatingRowColors(true); // Цвет каждой строки интервала разный, при наличии qss этот атрибут недействителен
    ui->treeView->setFocusPolicy(Qt :: NoFocus);
    ui->treeView->setExpandsOnDoubleClick(true);
    ui->treeView->setRootIsDecorated(true);
    QFont newFontt("DroidSans", 10, QFont::Normal, false);
    ui->treeView->setFont(newFontt);
    ui->treeView->setBackgroundRole(QPalette :: Dark);

    ui->treeView->setExpandsOnDoubleClick(false);
    QObject::connect(ui->treeView, &QTreeView::clicked, [this]()
    {
        if (ui->treeView->isExpanded(ui->treeView->currentIndex()))
        {
            ui->treeView->collapse(ui->treeView->currentIndex());
        }else{
            ui->treeView->expand(ui->treeView->currentIndex());
        }
    });

    QStandardItemModel* model=new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels (QStringList () << QStringLiteral ("Наименование") << QStringLiteral ("Свойство")); // Установить заголовок столбца
    ui->treeView->header()->setDefaultAlignment(Qt::AlignCenter);

        ui->treeView->setStyleSheet(
                            "*{"
                            "background: rgb(255, 255, 222);"
                            "}"
                            "*::item{"
                            "    border-top-width: 0px;"
                            "    border-right-width: 1px;"
                            "    border-bottom-width: 1px;"
                            "    border-left-width: 0px;"
                            "    border-style: solid;"
                            "    border-color: silver;"
                            "}"
                            "*::item:selected{"
                            "    background: palette(Highlight);"
                            "}"
//                            "*::item:has-children{"
//                            "    background: rgb(128,128,128);"
//                            "}"
                                    "::branch:has-children:!has-siblings:closed,"
                                    "::branch:closed:has-children:has-siblings {"
                                    "        border-image: none;"
                                    "        image: url(:/image/data/img/icons/branch-closed.png);"
                                    "}"
                                    "::branch:open:has-children:!has-siblings,"
                                    "::branch:open:has-children:has-siblings  {"
                                   "        border-image: none;"
                                    "        image: url(:/image/data/img/icons/branch-open.png);"
                                    "}"
                                    );

    QList<QStandardItem*> items1;
    item1 = new QStandardItem(QStringLiteral ("Общее название сеанса"));
    QString w0=item1->text();
    item1->setToolTip(w0);
    item2 = new QStandardItem();
    items1.append(item1);
    items1.append(item2);
    model->appendRow(items1);
    item1->setSelectable(false);
    item1->setEditable(false);
    item2->setSelectable(false);
    item2->setEditable(false);
    QFont newFont("DroidSans", 10, QFont::Bold,false);
    item1->setFont(newFont);

    QList<QStandardItem*> items2;
    item3 = new QStandardItem(QStringLiteral ("Название сеанса"));
    item3->setEditable(false);
    QString w1=item3->text();
    item3->setToolTip(w1);
    item4 = new QStandardItem(QStringLiteral ("Имя сеанса"));
    QString w2=item4->text();
    item4->setToolTip(w2);
    items2.append(item3);
    items2.append(item4);
    item1->appendRow(items2);
    items2.clear();

    item7 = new QStandardItem(QStringLiteral ("Тип эксперимента"));
    item7->setEditable(false);
    QString w9=item7->text();
    item7->setToolTip(w9);
    QFont newFont10("DroidSans", 10, QFont::Bold,false);
    item7->setFont(newFont10);
    item8 = new QStandardItem();
    item8->setEditable(false);
    items2.append(item7);
    items2.append(item8);
    item1->appendRow(items2);
    items2.clear();

    item87 = new QStandardItem(QStringLiteral ("Идентификация данных схемы замещения"));
    item87->setEditable(false);
    QString w10=item87->text();
    item87->setToolTip(w10);
    item88 = new QStandardItem(QStringLiteral ("Выбрать тип эксперимента"));
    QString w11=item88->text();
    item88->setToolTip(w11);
    items2.append(item87);
    items2.append(item88);
    item7->appendRow(items2);
    items2.clear();

    item105 = new QStandardItem(QStringLiteral ("Загрузка данных ручной идентификации"));
    item105->setEditable(false);
    item105->setEnabled(false);
    QString w12=item105->text();
    item105->setToolTip(w12);
    item106 = new QStandardItem(QStringLiteral ("Указать каталог"));
    item106->setEnabled(false);
    QString w13=item106->text();
    item106->setToolTip(w13);
    items2.append(item105);
    items2.append(item106);
    item7->appendRow(items2);
    items2.clear();

    item79 = new QStandardItem(QStringLiteral ("Наблюдатель состояния"));
    item79->setEditable(false);
    QString w14=item79->text();
    item79->setToolTip(w14);
    item80 = new QStandardItem(QStringLiteral ("Выбрать тип эксперимента"));
    QString w15=item80->text();
    item80->setToolTip(w15);
    items2.append(item79);
    items2.append(item80);
    item7->appendRow(items2);
    items2.clear();

    item81 = new QStandardItem(QStringLiteral ("Чтение данных для наблюдателя скорости"));
    item81->setEditable(false);
    item81->setEnabled(false);
    QString w16=item81->text();
    item81->setToolTip(w16);
    item82 = new QStandardItem(QStringLiteral ("Указать каталог"));
    item82->setEnabled(false);
    QString w17=item82->text();
    item82->setToolTip(w17);
    items2.append(item81);
    items2.append(item82);
    item7->appendRow(items2);
    items2.clear();


    item65 = new QStandardItem(QStringLiteral ("Сохранение данных"));
    item65->setEditable(false);
    QFont newFont11("DroidSans", 10, QFont::Bold,false);
    item65->setFont(newFont11);
    QString w18=item65->text();
    item65->setToolTip(w18);
    item66 = new QStandardItem();
    item66->setEditable(false);
    items2.append(item65);
    items2.append(item66);
    item1->appendRow(items2);
    items2.clear();

    item67 = new QStandardItem(QStringLiteral ("Данные идентификации"));
    item67->setEditable(false);
    QString w19=item67->text();
    item67->setToolTip(w19);
    item68 = new QStandardItem();
    item68->setEditable(false);
    item68->setCheckable(true);
    item68->setToolTip(QStringLiteral ("Выкл"));
    items2.append(item67);
    items2.append(item68);
    item65->appendRow(items2);
    items2.clear();

    item69 = new QStandardItem(QStringLiteral ("Данные электромагнитных процессов"));
    item69->setEditable(false);
    QString w21=item69->text();
    item69->setToolTip(w21);
    item70 = new QStandardItem();
    item70->setEditable(false);
    item70->setCheckable(true);
    item70->setToolTip(QStringLiteral ("Выкл"));
    items2.append(item69);
    items2.append(item70);
    item65->appendRow(items2);
    items2.clear();

    item71 = new QStandardItem(QStringLiteral ("Данные тепловых процессов"));
    item71->setEditable(false);
    QString w23=item71->text();
    item71->setToolTip(w23);
    item72 = new QStandardItem();
    item72->setEditable(false);
    item72->setCheckable(true);
    item72->setToolTip(QStringLiteral ("Выкл"));
    items2.append(item71);
    items2.append(item72);
    item65->appendRow(items2);
    items2.clear();

    item73 = new QStandardItem(QStringLiteral ("Данные вентиляционных процессов"));
    item73->setEditable(false);
    QString w25=item73->text();
    item73->setToolTip(w25);
    item74 = new QStandardItem();
    item74->setEditable(false);
    item74->setCheckable(true);
    item74->setToolTip(QStringLiteral ("Выкл"));
    items2.append(item73);
    items2.append(item74);
    item65->appendRow(items2);
    items2.clear();

    item75 = new QStandardItem(QStringLiteral ("Данные прогноза температур"));
    item75->setEditable(false);
    QString w27=item75->text();
    item75->setToolTip(w27);
    item76 = new QStandardItem();
    item76->setEditable(false);
    item76->setCheckable(true);
    item76->setToolTip(QStringLiteral ("Выкл"));
    items2.append(item75);
    items2.append(item76);
    item65->appendRow(items2);
    items2.clear();

    item77 = new QStandardItem(QStringLiteral ("Данные остаточного теплового ресурса"));
    item77->setEditable(false);
    QString w29=item77->text();
    item77->setToolTip(w29);
    item78 = new QStandardItem();
    item78->setEditable(false);
    item78->setCheckable(true);
    item78->setToolTip(QStringLiteral ("Выкл"));
    items2.append(item77);
    items2.append(item78);
    item65->appendRow(items2);
    items2.clear();

    QList<QStandardItem*> items3;
    item9 = new QStandardItem(QStringLiteral ("Идентификация параметров схемы замещения"));
    item10 = new QStandardItem();
    items3.append(item9);
    items3.append(item10);
    model->appendRow(items3);
    items3.clear();
    item9->setSelectable(false);
    item9->setEditable(false);
    QString w31=item9->text();
    item9->setToolTip(w31);
    item10->setSelectable(false);
    item10->setEditable(false);
    QString w32=item10->text();
    item10->setToolTip(w32);
    QFont newFont2("SansSerif", 10, QFont::Bold,false);
    item9->setFont(newFont2);

    QList<QStandardItem*> items4;
    item13 = new QStandardItem(QStringLiteral ("Режим расчета"));
    item13->setEditable(false);
    QString w35=item13->text();
    item13->setToolTip(w35);
    item14 = new QStandardItem(QStringLiteral ("Выберите режим"));
    QString w73=item14->text();
    item14->setToolTip(w73);
    items4.append(item13);
    items4.append(item14);
    item9->appendRow(items4);
    items4.clear();

    item93 = new QStandardItem(QStringLiteral ("Настроечный коэффициент gd="));
    item93->setEditable(false);
    item93->setEnabled(false);
    QString w37=item93->text();
    item93->setToolTip(w37);
    item94 = new QStandardItem(QStringLiteral ("0"));
    item94->setEnabled(false);
    item94->setCheckable(false);
    QString w38=item94->text();
    item94->setToolTip(w38);
    items4.append(item93);
    items4.append(item94);
    item9->appendRow(items4);
    items4.clear();

    item95 = new QStandardItem(QStringLiteral ("Настроечный коэффициент ki="));
    item95->setEditable(false);
    item95->setEnabled(false);
    QString w39=item95->text();
    item95->setToolTip(w39);
    item96 = new QStandardItem(QStringLiteral ("0"));
    item96->setEnabled(false);
    item96->setCheckable(false);
    QString w40=item96->text();
    item96->setToolTip(w40);
    items4.append(item95);
    items4.append(item96);
    item9->appendRow(items4);
    items4.clear();

    item97 = new QStandardItem(QStringLiteral ("Настроечный коэффициент gb="));
    item97->setEditable(false);
    item97->setEnabled(false);
    QString w41=item97->text();
    item97->setToolTip(w41);
    item98 = new QStandardItem(QStringLiteral ("0"));
    item98->setEnabled(false);
    item98->setCheckable(false);
    QString w42=item98->text();
    item98->setToolTip(w42);
    items4.append(item97);
    items4.append(item98);
    item9->appendRow(items4);
    items4.clear();

    item99 = new QStandardItem(QStringLiteral ("Настроечный коэффициент kpsi="));
    item99->setEditable(false);
    item99->setEnabled(false);
    QString w43=item99->text();
    item99->setToolTip(w43);
    item100 = new QStandardItem(QStringLiteral ("0"));
    item100->setEnabled(false);
    item100->setCheckable(false);
    QString w44=item100->text();
    item100->setToolTip(w44);
    items4.append(item99);
    items4.append(item100);
    item9->appendRow(items4);
    items4.clear();

    item101 = new QStandardItem(QStringLiteral ("Настроечный коэффициент gp="));
    item101->setEditable(false);
    item101->setEnabled(false);
    QString w45=item101->text();
    item101->setToolTip(w45);
    item102 = new QStandardItem(QStringLiteral ("0"));
    item102->setEnabled(false);
    item102->setCheckable(false);
    QString w46=item102->text();
    item102->setToolTip(w46);
    items4.append(item101);
    items4.append(item102);
    item9->appendRow(items4);
    items4.clear();

    item103 = new QStandardItem(QStringLiteral ("Настроечный коэффициент gpsi="));
    item103->setEditable(false);
    item103->setEnabled(false);
    QString w47=item103->text();
    item103->setToolTip(w47);
    item104 = new QStandardItem(QStringLiteral ("0"));
    item104->setEnabled(false);
    item104->setCheckable(false);
    QString w48=item104->text();
    item104->setToolTip(w48);
    items4.append(item103);
    items4.append(item104);
    item9->appendRow(items4);
    items4.clear();

    QList<QStandardItem*> items5;
    item17 = new QStandardItem(QStringLiteral ("Электромагнитная модель"));
    item18 = new QStandardItem();
    items5.append(item17);
    items5.append(item18);
    model->appendRow(items5);
    items5.clear();
    item17->setSelectable(false);
    item17->setEditable(false);
    QString w49=item17->text();
    item17->setToolTip(w49);
    item18->setSelectable(false);
    item18->setEditable(false);
    QFont newFont3("SansSerif", 10, QFont::Bold,false);
    item17->setFont(newFont3);

    QList<QStandardItem*> items6;
    item19 = new QStandardItem(QStringLiteral ("Pежим работы двигателя"));
    item19->setEditable(false);
    QString w50=item19->text();
    item19->setToolTip(w50);
    item20 = new QStandardItem(QStringLiteral ("Выбрать режим"));
    QString w51=item20->text();
    item20->setToolTip(w51);
    items6.append(item19);
    items6.append(item20);
    item17->appendRow(items6);
    items6.clear();

    item21 = new QStandardItem(QStringLiteral ("Время цикла, с:"));
    item21->setEditable(false);
    QString w52=item21->text();
    item21->setToolTip(w52);
    item22 = new QStandardItem(QStringLiteral ("0"));
    QString w53=item22->text();
    item22->setToolTip(w53);
    items6.append(item21);
    items6.append(item22);
    item17->appendRow(items6);
    items6.clear();

    item23 = new QStandardItem(QStringLiteral ("Время работы, с:"));
    item23->setEditable(false);
    QString w54=item23->text();
    item23->setToolTip(w54);
    item24 = new QStandardItem(QStringLiteral ("0"));
    QString w55=item24->text();
    item24->setToolTip(w55);
    items6.append(item23);
    items6.append(item24);
    item17->appendRow(items6);
    items6.clear();

    item89 = new QStandardItem(QStringLiteral ("Значение момента нагрузки, Нм:"));
    item89->setEditable(false);
    QString w56=item89->text();
    item89->setToolTip(w56);
    item90 = new QStandardItem(QStringLiteral ("0"));
    QString w57=item90->text();
    item90->setToolTip(w57);
    items6.append(item89);
    items6.append(item90);
    item17->appendRow(items6);
    items6.clear();

    item91 = new QStandardItem(QStringLiteral ("Выбор системы электропривода"));
    item91->setEditable(false);
    QString w58=item91->text();
    item91->setToolTip(w58);
    item92 = new QStandardItem(QStringLiteral ("Выбрать режим"));
    QString w59=item92->text();
    item92->setToolTip(w59);
    items6.append(item91);
    items6.append(item92);
    item17->appendRow(items6);
    items6.clear();

    QList<QStandardItem*> items7;
    item25 = new QStandardItem(QStringLiteral ("Тепловая модель"));
    item26 = new QStandardItem();
    items7.append(item25);
    items7.append(item26);
    model->appendRow(items7);
    items7.clear();
    //item25->setForeground(QBrush(Qt::white));
    item25->setSelectable(false);
    item25->setEditable(false);
    item26->setSelectable(false);
    item26->setEditable(false);
    QFont newFont4("SansSerif", 10, QFont::Bold,false);
    item25->setFont(newFont4);

    QList<QStandardItem*> items8;
    item27 = new QStandardItem(QStringLiteral ("Начальное значение температуры, °C"));
    item27->setEditable(false);
    item28 = new QStandardItem(QStringLiteral ("Введите значение"));
    items8.append(item27);
    items8.append(item28);
    item25->appendRow(items8);
    items8.clear();

    item29 = new QStandardItem(QStringLiteral ("Температурный режим"));
    item29->setEditable(false);
    item30 = new QStandardItem(QStringLiteral ("Выберите режим"));
    items8.append(item29);
    items8.append(item30);
    item25->appendRow(items8);
    items8.clear();
    item23 = new QStandardItem(QStringLiteral ("Шаг выбора точек"));
    item23->setEditable(false);
    item107 = new QStandardItem(QStringLiteral ("Введите значение"));
    items8.append(item23);
    items8.append(item107);
    item25->appendRow(items8);
    items8.clear();

//    QList<QStandardItem*> items9;
//    item31 = new QStandardItem(QStringLiteral ("Вентиляционная модель"));
//    item32 = new QStandardItem();
//    items9.append(item31);
//    items9.append(item32);
//    model->appendRow(items9);
//    items9.clear();
//    //item31->setForeground(QBrush(Qt::white));
//    item31->setSelectable(false);
//    item31->setEditable(false);
//    item32->setSelectable(false);
//    item32->setEditable(false);
//    QFont newFont5("SansSerif", 10, QFont::Bold,false);
//    item31->setFont(newFont5);

//    QList<QStandardItem*> items10;
//    item33 = new QStandardItem(QStringLiteral ("Условие 10"));
//    item33->setEditable(false);
//    item34 = new QStandardItem(QStringLiteral ("Значение 10"));
//    items10.append(item33);
//    items10.append(item34);
//    item31->appendRow(items10);
//    items10.clear();
//    item35 = new QStandardItem(QStringLiteral ("Условие 11"));
//    item35->setEditable(false);
//    item36 = new QStandardItem(QString ("Значение 11"));
//    items10.append(item35);
//    items10.append(item36);
//    item31->appendRow(items10);
//    items10.clear();
//    item37 = new QStandardItem(QStringLiteral ("Условие 12"));
//    item37->setEditable(false);
//    item38 = new QStandardItem(QStringLiteral ("Значение 12"));
//    items10.append(item37);
//    items10.append(item38);
//    item31->appendRow(items10);
//    items10.clear();

//    QList<QStandardItem*> items11;
//    item39 = new QStandardItem(QStringLiteral ("Прогнозирование температур"));
//    item40 = new QStandardItem();
//    items11.append(item39);
//    items11.append(item40);
//    model->appendRow(items11);
//    items11.clear();
//    //item39->setForeground(QBrush(Qt::white));
//    item39->setSelectable(false);
//    item39->setEditable(false);
//    item40->setSelectable(false);
//    item40->setEditable(false);
//    QFont newFont6("SansSerif", 10, QFont::Bold,false);
//    item39->setFont(newFont6);

//    QList<QStandardItem*> items12;
//    item41 = new QStandardItem(QStringLiteral ("Условие 13"));
//    item41->setEditable(false);
//    item42 = new QStandardItem(QStringLiteral ("Значение 13"));
//    items12.append(item41);
//    items12.append(item42);
//    item39->appendRow(items12);
//    items12.clear();
//    item43 = new QStandardItem(QStringLiteral ("Условие 14"));
//    item43->setEditable(false);
//    item44 = new QStandardItem(QString ("Значение 14"));
//    items12.append(item43);
//    items12.append(item44);
//    item39->appendRow(items12);
//    items12.clear();
//    item45 = new QStandardItem(QStringLiteral ("Условие 15"));
//    item45->setEditable(false);
//    item46 = new QStandardItem(QStringLiteral ("Значение 15"));
//    items12.append(item45);
//    items12.append(item46);
//    item39->appendRow(items12);
//    items12.clear();

//    QList<QStandardItem*> items13;
//    item47 = new QStandardItem(QStringLiteral ("Оценка остаточного теплового ресурса"));
//    item48 = new QStandardItem();
//    items13.append(item47);
//    items13.append(item48);
//    model->appendRow(items13);
//    items13.clear();
//    //item47->setForeground(QBrush(Qt::white));
//    item47->setSelectable(false);
//    item47->setEditable(false);
//    item48->setSelectable(false);
//    item48->setEditable(false);
//    QFont newFont7("SansSerif", 10, QFont::Bold,false);
//    item47->setFont(newFont7);

//    QList<QStandardItem*> items14;
//    item49 = new QStandardItem(QStringLiteral ("Условие 16"));
//    item49->setEditable(false);
//    item50 = new QStandardItem(QStringLiteral ("Значение 16"));
//    items14.append(item49);
//    items14.append(item50);
//    item47->appendRow(items14);
//    items14.clear();
//    item51 = new QStandardItem(QStringLiteral ("Условие 17"));
//    item51->setEditable(false);
//    item52 = new QStandardItem(QString ("Значение 17"));
//    items14.append(item51);
//    items14.append(item52);
//    item47->appendRow(items14);
//    items14.clear();
//    item53 = new QStandardItem(QStringLiteral ("Условие 18"));
//    item53->setEditable(false);
//    item54 = new QStandardItem(QStringLiteral ("Значение 18"));
//    items14.append(item53);
//    items14.append(item54);
//    item47->appendRow(items14);
//    items14.clear();

//    QList<QStandardItem*> items15;
//    item55 = new QStandardItem(QStringLiteral ("Выходные данные"));
//    item56 = new QStandardItem();
//    items15.append(item55);
//    items15.append(item56);
//    model->appendRow(items15);
//    items15.clear();
//    //item55->setForeground(QBrush(Qt::white));
//    item55->setSelectable(false);
//    item55->setEditable(false);
//    item56->setSelectable(false);
//    item56->setEditable(false);
//    QFont newFont8("SansSerif", 10, QFont::Bold,false);
//    item55->setFont(newFont8);

//    QList<QStandardItem*> items16;
//    item57 = new QStandardItem(QStringLiteral ("Условие 19"));
//    item57->setEditable(false);
//    item58 = new QStandardItem(QStringLiteral ("Значение 19"));
//    items16.append(item57);
//    items16.append(item58);
//    item55->appendRow(items16);
//    items16.clear();
//    item59 = new QStandardItem(QStringLiteral ("Условие 20"));
//    item59->setEditable(false);
//    item60 = new QStandardItem(QString ("Значение 20"));
//    items16.append(item59);
//    items16.append(item60);
//    item55->appendRow(items16);
//    items16.clear();
//    item61 = new QStandardItem(QStringLiteral ("Условие 21"));
//    item61->setEditable(false);
//    item62 = new QStandardItem(QStringLiteral ("Значение 21"));
//    items16.append(item61);
//    items16.append(item62);
//    item55->appendRow(items16);
//    items16.clear();

    ui->treeView->setModel(model);

    ui->treeView->header()->resizeSection(0,270);
    ui->treeView->header()->setSectionResizeMode(0,QHeaderView::Interactive);
    ui->treeView->header()->setSectionResizeMode(1,QHeaderView::Fixed);
    ui->treeView->expandAll();

    ButtonColumnDelegate* buttonColumnDelegate = new ButtonColumnDelegate(this); //создание делегата для создания комбобоксов
    ui->treeView->setItemDelegateForColumn(1, buttonColumnDelegate);
//    ui->treeView->setItemDelegate( new ButtonColumnDelegate( ui->treeView ) );

    QPalette p99=ui->treeView->palette();
    p99.setColor(QPalette::Base, QColor(255, 255, 222));
    p99.setColor(QPalette::AlternateBase, QColor(255, 255, 191));
    ui->treeView->setPalette(p99);

    ui->tabWidget->setCurrentIndex(0);
    QString currentTabText = ui->tabWidget->tabText(0);
    setWindowTitle(currentTabText + "@" + QString("base") + QString(" - ImView"));

    ui->tableWidget->setRowCount(30); //задание количества строк таблицы
    ui->tableWidget->setColumnCount(5); //задание количества столбцов
    QStringList name2; //объявление указателя на тип QStringList
    name2 << "№" << "Цвет" << "Свойство" << "Смещение" << "Масштаб"; //перечисление заголовков
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
    }

    QTableWidgetItem *item251 = new QTableWidgetItem("Item251");
    item251->setCheckState(Qt::Checked);
    item251->setText("Сопротивление ротора R2, Ом");
    ui->tableWidget->setItem(0, 2, item251);

    QTableWidgetItem *item252 = new QTableWidgetItem("Item252");
    item252->setCheckState(Qt::Checked);
    item252->setText("Индуктивность обмотки статора L1, Гн");
    ui->tableWidget->setItem(1, 2, item252);

    QTableWidgetItem *item253 = new QTableWidgetItem("Item253");
    item253->setCheckState(Qt::Checked);
    item253->setText("Индуктивность обмотки ротора L2, Гн");
    ui->tableWidget->setItem(2, 2, item253);

    QTableWidgetItem *item254 = new QTableWidgetItem("Item254");
    item254->setCheckState(Qt::Checked);
    item254->setText("Индуктивность взаимоиндукции Lm, Гн");
    ui->tableWidget->setItem(3, 2, item254);

    QTableWidgetItem *item255 = new QTableWidgetItem("Item255");
    item255->setCheckState(Qt::Checked);
    item255->setText("Напряжение фазы А, В");
    ui->tableWidget->setItem(4, 2, item255);

    QTableWidgetItem *item256 = new QTableWidgetItem("Item256");
    item256->setCheckState(Qt::Checked);
    item256->setText("Напряжение фазы B, В");
    ui->tableWidget->setItem(5, 2, item256);

    QTableWidgetItem *item257 = new QTableWidgetItem("Item257");
    item257->setCheckState(Qt::Checked);
    item257->setText("Напряжение фазы C, В");
    ui->tableWidget->setItem(6, 2, item257);

    QTableWidgetItem *item258 = new QTableWidgetItem("Item258");
    item258->setCheckState(Qt::Checked);
    item258->setText("Ток фазы А, А");
    ui->tableWidget->setItem(7, 2, item258);

    QTableWidgetItem *item259 = new QTableWidgetItem("Item259");
    item259->setCheckState(Qt::Checked);
    item259->setText("Ток фазы B, А");
    ui->tableWidget->setItem(8, 2, item259);

    QTableWidgetItem *item260 = new QTableWidgetItem("Item260");
    item260->setCheckState(Qt::Checked);
    item260->setText("Ток фазы C, А");
    ui->tableWidget->setItem(9, 2, item260);

    QTableWidgetItem *item261 = new QTableWidgetItem("Item261");
    item261->setCheckState(Qt::Checked);
    item261->setText("Частота вращения, рад/с");
    ui->tableWidget->setItem(10, 2, item261);

    QTableWidgetItem *item262 = new QTableWidgetItem("Item262");
    item262->setCheckState(Qt::Checked);
    item262->setText("Момент на валу, Н*м");
    ui->tableWidget->setItem(11, 2, item262);

    QTableWidgetItem *item263 = new QTableWidgetItem("Item263");
    item263->setCheckState(Qt::Checked);
    item263->setText("Момент Мс, Н*м");
    ui->tableWidget->setItem(12, 2, item263);

    QTableWidgetItem *item264 = new QTableWidgetItem("Item264");
    item264->setCheckState(Qt::Checked);
    item264->setText("Станина, °C");
    ui->tableWidget->setItem(13, 2, item264);

    QTableWidgetItem *item265 = new QTableWidgetItem("Item265");
    item265->setCheckState(Qt::Checked);
    item265->setText("Подшипниковый узел справа сзади, °C");
    ui->tableWidget->setItem(14, 2, item265);

    QTableWidgetItem *item266 = new QTableWidgetItem("Item266");
    item266->setCheckState(Qt::Checked);
    item266->setText("Лобовая часть слева спереди, °C");
    ui->tableWidget->setItem(15, 2, item266);

    QTableWidgetItem *item267 = new QTableWidgetItem("Item267");
    item267->setCheckState(Qt::Checked);
    item267->setText("Подшипниковый узел слева спереди, °C");
    ui->tableWidget->setItem(16, 2, item267);

    QTableWidgetItem *item268 = new QTableWidgetItem("Item268");
    item268->setCheckState(Qt::Checked);
    item268->setText("Лобовая часть слева сзади, °C");
    ui->tableWidget->setItem(17, 2, item268);

    QTableWidgetItem *item269 = new QTableWidgetItem("Item269");
    item269->setCheckState(Qt::Checked);
    item269->setText("Станина, °C");
    ui->tableWidget->setItem(18, 2, item269);

    QTableWidgetItem *item270 = new QTableWidgetItem("Item270");
    item270->setCheckState(Qt::Checked);
    item270->setText("Лобовая часть справа спереди, °C");
    ui->tableWidget->setItem(19, 2, item270);

    QTableWidgetItem *item271 = new QTableWidgetItem("Item271");
    item271->setCheckState(Qt::Checked);
    item271->setText("Лобовая часть справа сзади, °C");
    ui->tableWidget->setItem(20, 2, item271);

    QTableWidgetItem *item272 = new QTableWidgetItem("Item272");
    item272->setCheckState(Qt::Checked);
    item272->setText("Магнитопровод статора, °C");
    ui->tableWidget->setItem(21, 2, item272);

    QTableWidgetItem *item273 = new QTableWidgetItem("Item273");
    item273->setCheckState(Qt::Checked);
    item273->setText("Подшипниковый узел справа спереди, °C");
    ui->tableWidget->setItem(22, 2, item273);

    QTableWidgetItem *item274 = new QTableWidgetItem("Item274");
    item274->setCheckState(Qt::Checked);
    item274->setText("одшипниковый узел слева сзади, °C");
    ui->tableWidget->setItem(23, 2, item274);

    QTableWidgetItem *item275 = new QTableWidgetItem("Item275");
    item275->setCheckState(Qt::Checked);
    item275->setText("Ротор сверху, °C");
    ui->tableWidget->setItem(24, 2, item275);

    QTableWidgetItem *item276 = new QTableWidgetItem("Item276");
    item276->setCheckState(Qt::Checked);
    item276->setText("Ротор снизу, °C");
    ui->tableWidget->setItem(25, 2, item276);

    QTableWidgetItem *item277 = new QTableWidgetItem("Item277");
    item277->setCheckState(Qt::Checked);
    item277->setText("Станина слева, °C");
    ui->tableWidget->setItem(26, 2, item277);

    QTableWidgetItem *item278 = new QTableWidgetItem("Item278");
    item278->setCheckState(Qt::Checked);
    item278->setText("Станина справа, °C");
    ui->tableWidget->setItem(27, 2, item278);


    QTableWidgetItem *item279 = new QTableWidgetItem("Item279");
    item279->setCheckState(Qt::Checked);
    item279->setText("Вал, °C");
    ui->tableWidget->setItem(28, 2, item279);

    QTableWidgetItem *item280 = new QTableWidgetItem("Item280");
    item280->setCheckState(Qt::Checked);
    item280->setText("Клеммная коробка, °C");
    ui->tableWidget->setItem(29, 2, item280);

    for (int i=0; i<34; i++)
    {
        if (ui->tableWidget->item(i, 0) != 0)
        {
            ui->tableWidget->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }


    for (int i=0; i<34; i++)
    {
        if (ui->tableWidget->item(i, 3) != 0)
        {
            ui->tableWidget->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }

        if (ui->tableWidget->item(i, 4) != 0)
        {
            ui->tableWidget->item(i, 4)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget->setItem(0, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(1, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(1, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(2, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(2, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(3, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(3, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(4, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(4, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(5, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(5, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(6, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(6, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(7, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(7, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(8, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(8, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(9, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(9, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(10, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(10, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(11, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(11, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(12, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(12, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(13, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(13, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(14, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(14, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(15, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(15, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(16, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(16, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(17, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(17, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(18, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(18, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(19, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(19, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(20, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(20, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(21, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(21, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(22, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(22, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(23, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(23, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(24, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(24, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(25, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(25, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(26, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(26, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(27, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(27, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(28, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(28, 4, new QTableWidgetItem(QString("%1").arg(1)));
    ui->tableWidget->setItem(29, 3, new QTableWidgetItem(QString("%1").arg(0)));
    ui->tableWidget->setItem(29, 4, new QTableWidgetItem(QString("%1").arg(1)));

    //Заполнение таблицы результатов
    ui->tableWidget_2->setRowCount(25);
    ui->tableWidget_2->setColumnCount(2);
    QStringList name_2;
    name_2 << "Сигнал" << "Величина";
    ui->tableWidget_2->setHorizontalHeaderLabels(name_2);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->verticalHeader()->setVisible(true);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView :: SingleSelection);

    ui->tableWidget_2->setItem(0, 0, new QTableWidgetItem("Ток фазы А, А"));
    ui->tableWidget_2->setItem(1, 0, new QTableWidgetItem("Напряжение фазы А, В"));
    ui->tableWidget_2->setItem(2, 0, new QTableWidgetItem("Активная мошность фазы А, Вт"));
    ui->tableWidget_2->setItem(3, 0, new QTableWidgetItem("Реактивная мошность фазы А, ВА"));
    ui->tableWidget_2->setItem(4, 0, new QTableWidgetItem("Полная мошность фазы А, ВАР"));
    ui->tableWidget_2->setItem(5, 0, new QTableWidgetItem("Коэффициент мощности фазы А"));
    ui->tableWidget_2->setItem(6, 0, new QTableWidgetItem("Ток фазы В, А"));
    ui->tableWidget_2->setItem(7, 0, new QTableWidgetItem("Напряжение фазы В, В"));
    ui->tableWidget_2->setItem(8, 0, new QTableWidgetItem("Активная мошность фазы В, Вт"));
    ui->tableWidget_2->setItem(9, 0, new QTableWidgetItem("Реактивная мошность фазы В, ВА"));
    ui->tableWidget_2->setItem(10, 0, new QTableWidgetItem("Полная мошность фазы В, ВАР"));
    ui->tableWidget_2->setItem(11, 0, new QTableWidgetItem("Коэффициент мощности фазы В"));
    ui->tableWidget_2->setItem(12, 0, new QTableWidgetItem("Ток фазы С, А"));
    ui->tableWidget_2->setItem(13, 0, new QTableWidgetItem("Напряжение фазы С, В"));
    ui->tableWidget_2->setItem(14, 0, new QTableWidgetItem("Активная мошность фазы С, Вт"));
    ui->tableWidget_2->setItem(15, 0, new QTableWidgetItem("Реактивная мошность фазы С, ВА"));
    ui->tableWidget_2->setItem(16, 0, new QTableWidgetItem("Полная мошность фазы С, ВАР"));
    ui->tableWidget_2->setItem(17, 0, new QTableWidgetItem("Коэффициент мощности фазы С"));
    ui->tableWidget_2->setItem(18, 0, new QTableWidgetItem("трехфазная активная мошность, Вт"));
    ui->tableWidget_2->setItem(19, 0, new QTableWidgetItem("Трехфазная реактивная мошность, ВА"));
    ui->tableWidget_2->setItem(20, 0, new QTableWidgetItem("Трехфазная полная мошность, ВАР"));
    ui->tableWidget_2->setItem(21, 0, new QTableWidgetItem("Коэффициент мощности"));
    ui->tableWidget_2->setItem(22, 0, new QTableWidgetItem("Скорость вращения ротора, рад/с"));
    ui->tableWidget_2->setItem(23, 0, new QTableWidgetItem("Момент, Н*м"));
    ui->tableWidget_2->setItem(0, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(1, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(2, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(3, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(4, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(5, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(6, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(7, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(8, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(9, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(10, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(11, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(12, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(13, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(14, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(15, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(16, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(17, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(18, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(19, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(20, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(21, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(22, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(23, 1, new QTableWidgetItem());
    ui->tableWidget_2->setItem(24, 1, new QTableWidgetItem());

    QPalette p100=ui->tableWidget->palette();
    p100.setColor(QPalette::Base, QColor(225, 255, 255));
    p100.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_2->setPalette(p100);

    //вставка таблицы тепловые характеристики
    ui->tableWidget_3->setRowCount(17);
    ui->tableWidget_3->setColumnCount(3);
    QStringList name;
    name << " № " << "Сигнал" << "Величина";
    ui->tableWidget_3->setHorizontalHeaderLabels(name);
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_3->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_3->verticalHeader()->setVisible(false);
    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_3->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_3->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_3->setColumnWidth(0, 100);

    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_3->columnCount(); column++)
        {
            ui->tableWidget_3->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<17; i++)
    {
        if (ui->tableWidget_3->item(i, 0) != 0)
        {
            ui->tableWidget_3->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget_3->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget_3->setItem(0,  1, new QTableWidgetItem("Станина, °C"));
    ui->tableWidget_3->setItem(1,  1, new QTableWidgetItem("Подшипниковый узел справа сзади, °C"));
    ui->tableWidget_3->setItem(2,  1, new QTableWidgetItem("Лобовая часть слева спереди, °C"));
    ui->tableWidget_3->setItem(3,  1, new QTableWidgetItem("Подшипниковый узел слева спереди, °C"));
    ui->tableWidget_3->setItem(4,  1, new QTableWidgetItem("Лобовая часть слева сзади, °C"));
    ui->tableWidget_3->setItem(5,  1, new QTableWidgetItem("Станина, °C"));
    ui->tableWidget_3->setItem(6,  1, new QTableWidgetItem("Лобовая часть справа спереди, °C"));
    ui->tableWidget_3->setItem(7,  1, new QTableWidgetItem("Лобовая часть справа сзади, °C"));
    ui->tableWidget_3->setItem(8,  1, new QTableWidgetItem("Магнитопровод статора, °C"));
    ui->tableWidget_3->setItem(9,  1, new QTableWidgetItem("Подшипниковый узел справа спереди, °C"));
    ui->tableWidget_3->setItem(10, 1, new QTableWidgetItem("Подшипниковый узел слева сзади, °C"));
    ui->tableWidget_3->setItem(11, 1, new QTableWidgetItem("Ротор сверху, °C"));
    ui->tableWidget_3->setItem(12, 1, new QTableWidgetItem("Ротор снизу, °C"));
    ui->tableWidget_3->setItem(13, 1, new QTableWidgetItem("Станина слева, °C"));
    ui->tableWidget_3->setItem(14, 1, new QTableWidgetItem("Станина справа, °C"));
    ui->tableWidget_3->setItem(15, 1, new QTableWidgetItem("Вал, °C"));
    ui->tableWidget_3->setItem(16, 1, new QTableWidgetItem("Клеммная коробка, °C"));

    QPalette p102=ui->tableWidget_3->palette();
    p102.setColor(QPalette::Base, QColor(225, 255, 255));
    p102.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_3->setPalette(p102);

    //вставка таблицы Энергетические характеристики таблицы tableWidget_4
    ui->tableWidget_4->setRowCount(30);
    ui->tableWidget_4->setColumnCount(2);
    QStringList name_3;
    name_3 << "Свойство" << "Значение";
    ui->tableWidget_4->setHorizontalHeaderLabels(name_3);
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

    ui->tableWidget_5->setRowCount(17);
    ui->tableWidget_5->setColumnCount(3);
    QStringList name_5;
    name_5 << " № " << "Сигнал" << "Величина";
    ui->tableWidget_5->setHorizontalHeaderLabels(name);
    ui->tableWidget_5->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_5->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_5->verticalHeader()->setVisible(false);
    ui->tableWidget_5->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_5->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_5->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_5->setColumnWidth(0, 100);

    for(int row = 0; row<ui->tableWidget_5->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_5->columnCount(); column++)
        {
            ui->tableWidget_5->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<17; i++)
    {
        if (ui->tableWidget_5->item(i, 0) != 0)
        {
            ui->tableWidget_5->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget_5->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget_5->setItem(0,  1, new QTableWidgetItem("Станина, °C"));
    ui->tableWidget_5->setItem(1,  1, new QTableWidgetItem("Подшипниковый узел справа сзади, °C"));
    ui->tableWidget_5->setItem(2,  1, new QTableWidgetItem("Лобовая часть слева спереди, °C"));
    ui->tableWidget_5->setItem(3,  1, new QTableWidgetItem("Подшипниковый узел слева спереди, °C"));
    ui->tableWidget_5->setItem(4,  1, new QTableWidgetItem("Лобовая часть слева сзади, °C"));
    ui->tableWidget_5->setItem(5,  1, new QTableWidgetItem("Станина, °C"));
    ui->tableWidget_5->setItem(6,  1, new QTableWidgetItem("Лобовая часть справа спереди, °C"));
    ui->tableWidget_5->setItem(7,  1, new QTableWidgetItem("Лобовая часть справа сзади, °C"));
    ui->tableWidget_5->setItem(8,  1, new QTableWidgetItem("Магнитопровод статора, °C"));
    ui->tableWidget_5->setItem(9,  1, new QTableWidgetItem("Подшипниковый узел справа спереди, °C"));
    ui->tableWidget_5->setItem(10, 1, new QTableWidgetItem("Подшипниковый узел слева сзади, °C"));
    ui->tableWidget_5->setItem(11, 1, new QTableWidgetItem("Ротор сверху, °C"));
    ui->tableWidget_5->setItem(12, 1, new QTableWidgetItem("Ротор снизу, °C"));
    ui->tableWidget_5->setItem(13, 1, new QTableWidgetItem("Станина слева, °C"));
    ui->tableWidget_5->setItem(14, 1, new QTableWidgetItem("Станина справа, °C"));
    ui->tableWidget_5->setItem(15, 1, new QTableWidgetItem("Вал, °C"));
    ui->tableWidget_5->setItem(16, 1, new QTableWidgetItem("Клеммная коробка, °C"));

    QPalette p105=ui->tableWidget_5->palette();
    p105.setColor(QPalette::Base, QColor(225, 255, 255));
    p105.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_5->setPalette(p105);

    ui->tableWidget_6->setRowCount(8);
    ui->tableWidget_6->setColumnCount(3);
    QStringList name_6;
    name_6 << " № " << "Сигнал" << "Величина";
    ui->tableWidget_6->setHorizontalHeaderLabels(name_6);
    ui->tableWidget_6->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_6->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_6->verticalHeader()->setVisible(false);
    ui->tableWidget_6->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_6->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_6->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_6->setColumnWidth(0, 100);
    ui->tableWidget_6->setColumnWidth(1, 400);

    for(int row = 0; row<ui->tableWidget_6->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_6->columnCount(); column++)
        {
            ui->tableWidget_6->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<8; i++)
    {
        if (ui->tableWidget_6->item(i, 0) != 0)
        {
            ui->tableWidget_6->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget_6->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget_6->setItem(0, 1, new QTableWidgetItem("Ротор слева, °C"));
    ui->tableWidget_6->setItem(1, 1, new QTableWidgetItem("Ротор справа, °C"));
    ui->tableWidget_6->setItem(2, 1, new QTableWidgetItem("Станина слева, °C"));
    ui->tableWidget_6->setItem(3, 1, new QTableWidgetItem("Станина справа, °C"));
    ui->tableWidget_6->setItem(4, 1, new QTableWidgetItem("Вал, °C"));
    ui->tableWidget_6->setItem(5, 1, new QTableWidgetItem("Клеммная коробка, °C"));
    ui->tableWidget_6->setItem(6, 1, new QTableWidgetItem("Магнитопровод статора слева, °C"));
    ui->tableWidget_6->setItem(7, 1, new QTableWidgetItem("Магнитопровод статора справа, °C"));

    QPalette p106=ui->tableWidget_6->palette();
    p106.setColor(QPalette::Base, QColor(225, 255, 255));
    p106.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_6->setPalette(p106);

    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::cyan);
    dataLineColors.append(Qt::yellow);
    dataLineColors.append(Qt::red);
    dataLineColors.append(Qt::green);
    dataLineColors.append(Qt::yellow);

    for (int i = 0; i < dataLineColors.size(); i++)
    {
        ui->tableWidget->item(i, 1)->setBackground(dataLineColors[i]);
    }

    connect(ui->tableWidget, &QTableWidget::cellClicked,this, &MainWindow::setcolorincell);

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

    connect(item14->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot);
    connect(item88->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_2);
    connect(item80->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_3);
    connect(item68->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_4);

    connect(buttonColumnDelegate, &ButtonColumnDelegate::projectFileSelected, this, &MainWindow::projectFileSelectedSlot);
    connect(buttonColumnDelegate, &ButtonColumnDelegate::projectFileSelected_2, this, &MainWindow::projectFileSelectedSlot_2);
    connect(buttonColumnDelegate, &ButtonColumnDelegate::projectFileSelected_3, this, &MainWindow::projectFileSelectedSlot_3);
    connect(buttonColumnDelegate, &ButtonColumnDelegate::projectFileSelected_5, this, &MainWindow::projectFileSelectedSlot_5);
    connect(buttonColumnDelegate, &ButtonColumnDelegate::projectFileSelected_6, this, &MainWindow::projectFileSelectedSlot_6);

    connect(ui->tabWidget, &QTabWidget::currentChanged, this,&MainWindow::tabClicked);
    connect(ui->widget_5->ui->tabWidget, &QTabWidget::currentChanged, this,&MainWindow::tabClicked_2);

}

void MainWindow::closeEvent (QCloseEvent *)
{
    ui->widget_3->stop();
    QDir dir("/tmp/imview");
    dir.removeRecursively();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionabout_triggered()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    rsc= new AboutDialog(this);
    rsc->exec();
    rsc->setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    rsc->size(),
                    screen->geometry()));
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionhelp_triggered()
{
    view = new QWebEngineView;
    connect(view, &QWebEngineView::titleChanged, this, &MainWindow::titleChanged);
    view->setUrl(QUrl::fromLocalFile(QFileInfo("../help/index.html").absoluteFilePath()));
    view->setWindowIcon(QIcon::fromTheme("help-contents"));
    view->showMaximized();
}

void MainWindow::titleChanged(const QString &title)
{
    view->setWindowTitle(title);
}

void MainWindow::on_action_16_triggered()
{
    ui->widget->on_enterDannie_clicked();
}

void MainWindow::on_action_12_triggered()
{

}

void MainWindow::on_action_17_triggered()
{
    ui->widget->on_deleteDannie_clicked();
}

void MainWindow::on_action_19_triggered()
{

}

void MainWindow::on_action_5_triggered()
{
    if (item88->text() == "Выбрать тип эксперимента")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        ui->tabWidget->show();
        ui->tabWidget->setCurrentIndex( 1 );
        QPixmap pixmap(":/system_icons/data/img/system_icons/go-previous.svg");
        QIcon ButtonIcon_1(pixmap);
        ui->pushButton_5->setIcon(ButtonIcon_1);
        ui->stackedWidget->hide();
        QModelIndex myIndex, myIndex2, myIndex3,myIndex4,myIndex5,myIndex6,myIndex7;
        myIndex = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 2, QModelIndex());
        base.P_nom=ui->widget->ui->tableView->model()->data(myIndex).toDouble();
        myIndex2 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 3, QModelIndex());
        base.n_nom=ui->widget->ui->tableView->model()->data(myIndex2).toDouble();
        myIndex3 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 4, QModelIndex());
        base.U_fnom=ui->widget->ui->tableView->model()->data(myIndex3).toDouble();
        myIndex4 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 5, QModelIndex());
        base.cosf_nom=ui->widget->ui->tableView->model()->data(myIndex4).toDouble();
        myIndex5 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 6, QModelIndex());
        base.kpd_nom=ui->widget->ui->tableView->model()->data(myIndex5).toDouble();
        myIndex6 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 7, QModelIndex());
        base.muk=ui->widget->ui->tableView->model()->data(myIndex6).toDouble();
        myIndex7 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 8, QModelIndex());
        base.n_0=ui->widget->ui->tableView->model()->data(myIndex7).toDouble();

        ui->action_5->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-paused.svg"));
        ui->action_9->setEnabled(true);

        //создание папки текущего сеанса
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QTime currentTime = currentDateTime.time();
        QDate currentDate = currentDateTime.date();

        QString setpath = "/home/elf/ImView/Output";
        QDir dir(setpath);

        dirName= QString ("%1""%2""%3").arg("Сеанс ").arg(currentTime.toString("hh:mm:ss ").toUtf8().data()).
                arg(currentDate.toString("dd.MM.yyyy").toUtf8().data());
        dir.mkdir(dirName);

        if(item68->checkState() == Qt::Checked)
        {
            QString filename = "result_identf.csv";
            //создание файла сохранений идентификации параметров схемы замещения
            std::ofstream fout;

            base.identfFilename = setpath+QDir::separator()+dirName+QDir::separator()+filename;

            fout.open(QString(base.identfFilename).toStdString(),std::ios::out | std::ios::app);
            fout << std::endl << "Начало измерений " << currentTime.toString("hh:mm:ss ").toUtf8().data() <<
                    currentDate.toString("dd.MM.yyyy").toUtf8().data() << std::endl;
            fout << std::endl;

            fout << "Канал №1" << " - " << "Активное сопротивление фазы ротора" << std::endl;
            fout << "Канал №2" << " - " << "Индуктивность фазы статора" << std::endl;
            fout << "Канал №3" << " - " << "Индуктивность фазы ротора" << std::endl;
            fout << "Канал №2" << " - " << "Индуктивность взаимоиндукции" << std::endl;

            fout << std::endl;

            fout << "Время;";

            for (int i=0; i<4; i++)
            {
                fout << QString("Канал №%1").arg(i+1).toUtf8().data() << ";";
                //fout << modelss.R2 << modelss.L << modelss.L << modelss.Lm;
            }

            fout << std::endl;

            fout.close();
        }

//        if(item70->checkState() == Qt::Checked)
//        {
//            QString filename = "result_tepl.csv";
//            //создание файла сохранений идентификации параметров схемы замещения
//            std::ofstream fout;

//            base.teplFilename = setpath+QDir::separator()+dirName+QDir::separator()+filename;

//            fout.open(QString(base.teplFilename).toStdString(),std::ios::out | std::ios::app);
//            fout << std::endl << "Начало измерений " << currentTime.toString("hh:mm:ss ").toUtf8().data() <<
//                    currentDate.toString("dd.MM.yyyy").toUtf8().data() << std::endl;
//            fout << std::endl;

//            fout << "Канал №1"  << " - " << "Cтанина" << std::endl;
//            fout << "Канал №2"  << " - " << "Подшипниковый узел справа сзади" << std::endl;
//            fout << "Канал №3"  << " - " << "Лобовая часть слева спереди" << std::endl;
//            fout << "Канал №4"  << " - " << "Подшипниковый узел слева спереди" << std::endl;
//            fout << "Канал №5"  << " - " << "Подшипниковый узел слева спереди" << std::endl;
//            fout << "Канал №6"  << " - " << "Лобовая часть слева сзади" << std::endl;
//            fout << "Канал №7"  << " - " << "Лобовая часть справа спереди" << std::endl;
//            fout << "Канал №8"  << " - " << "Лобовая часть справа сзади" << std::endl;
//            fout << "Канал №9"  << " - " << "Магнитопровод статора" << std::endl;
//            fout << "Канал №10" << " - " << "Подшипниковый узел справа спереди" << std::endl;
//            fout << "Канал №11" << " - " << "Подшипниковый узел слева сзади" << std::endl;
//            fout << "Канал №12" << " - " << "Ротор сверху" << std::endl;
//            fout << "Канал №13" << " - " << "Ротор снизу" << std::endl;
//            fout << "Канал №14" << " - " << "Станина слева" << std::endl;
//            fout << "Канал №15" << " - " << "Станина слева" << std::endl;
//            fout << "Канал №16" << " - " << "Вал" << std::endl;
//            fout << "Канал №17" << " - " << "Клеммная коробка" << std::endl;

//            fout << std::endl;

//            fout << "Время;";

//            for (int i=0; i<17; i++)
//            {
//                fout << QString("Канал №%1").arg(i+1).toUtf8().data() << ";";
//            }

//            fout << std::endl;

//            fout.close();
//        }
        ui->widget_2->raschet_f();
    }
}

void MainWindow::on_action_9_triggered()
{
    ui->action_5->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-start_2.svg"));
    ui->action_9->setEnabled(false);
    ui->widget_2->dataSource->stop();
}

void MainWindow::on_action_20_triggered()
{
    ui->tabWidget->show();
    ui->tabWidget->setCurrentIndex(2);
    ui->stackedWidget->show();
    ui->stackedWidget->setCurrentIndex(3);
    QPixmap pixmap(":/system_icons/data/img/system_icons/go-previous.svg");
    QIcon ButtonIcon_1(pixmap);
    ui->pushButton_5->setIcon(ButtonIcon_1);
    //ui->stackedWidget->hide();
    base.R1 = ui->lineEdit_12->text().toDouble();
    base.R2 = ui->lineEdit_11->text().toDouble();
    base.L1 = ui->lineEdit_10->text().toDouble();
    base.L2 = ui->lineEdit_9->text().toDouble();
    base.Lm = ui->lineEdit_8->text().toDouble();
    ui->action_20->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-paused.svg"));
    ui->action_21->setEnabled(true);

    if(item70->checkState() == Qt::Checked)
    {
        //создание файла сохранений идентификации параметров схемы замещения
        std::ofstream fout;
        QString filename = "result_electromagn.csv";
        QString setpath = "/home/elf/ImView/Output";
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QTime currentTime = currentDateTime.time();
        QDate currentDate = currentDateTime.date();
        base.electromagnFilename = setpath+QDir::separator()+dirName+QDir::separator()+filename;

        fout.open(QString(base.electromagnFilename).toStdString(),std::ios::out | std::ios::app);

        fout << std::endl << "Начало измерений " << currentTime.toString("hh:mm:ss ").toUtf8().data() <<
                currentDate.toString("dd.MM.yyyy").toUtf8().data() << std::endl;
        fout << std::endl;

        fout << "Канал №1" << " - " << "Напряжение фазы А, В" << std::endl;
        fout << "Канал №2" << " - " << "Напряжение фазы В, В" << std::endl;
        fout << "Канал №3" << " - " << "Напряжение фазы С, В" << std::endl;
        fout << "Канал №4" << " - " << "Ток фазы А, В" << std::endl;
        fout << "Канал №5" << " - " << "Ток фазы В, В" << std::endl;
        fout << "Канал №6" << " - " << "Ток фазы С, В" << std::endl;
        fout << "Канал №7" << " - " << "Частота вращения, рад/с" << std::endl;
        fout << "Канал №8" << " - " << "Момент на валу, Н*м" << std::endl;
        fout << "Канал №9" << " - " << "Момент Мс, Н*м" << std::endl;

        fout << std::endl;

        fout << "Время;";

        for (int i=0; i<9; i++)
        {
            fout << QString("Канал №%1").arg(i+1).toUtf8().data() << ";";
        }

        fout << std::endl;

        fout.close();
    }

    if(item70->checkState() == Qt::Checked)
    {
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QTime currentTime = currentDateTime.time();
        QDate currentDate = currentDateTime.date();
        QString setpath = "/home/elf/ImView/Output";
        QDir dir(setpath);
        QString filename = "result_tepl.csv";

        //создание файла сохранений идентификации параметров схемы замещения
        std::ofstream fout;

        base.teplFilename = setpath+QDir::separator()+dirName+QDir::separator()+filename;

        fout.open(QString(base.teplFilename).toStdString(),std::ios::out | std::ios::app);
        fout << std::endl << "Начало измерений " << currentTime.toString("hh:mm:ss ").toUtf8().data() <<
                currentDate.toString("dd.MM.yyyy").toUtf8().data() << std::endl;
        fout << std::endl;

        fout << "Канал №1"  << " - " << "Cтанина" << std::endl;
        fout << "Канал №2"  << " - " << "Подшипниковый узел справа сзади" << std::endl;
        fout << "Канал №3"  << " - " << "Лобовая часть слева спереди" << std::endl;
        fout << "Канал №4"  << " - " << "Подшипниковый узел слева спереди" << std::endl;
        fout << "Канал №5"  << " - " << "Подшипниковый узел слева спереди" << std::endl;
        fout << "Канал №6"  << " - " << "Лобовая часть слева сзади" << std::endl;
        fout << "Канал №7"  << " - " << "Лобовая часть справа спереди" << std::endl;
        fout << "Канал №8"  << " - " << "Лобовая часть справа сзади" << std::endl;
        fout << "Канал №9"  << " - " << "Магнитопровод статора" << std::endl;
        fout << "Канал №10" << " - " << "Подшипниковый узел справа спереди" << std::endl;
        fout << "Канал №11" << " - " << "Подшипниковый узел слева сзади" << std::endl;
        fout << "Канал №12" << " - " << "Ротор сверху" << std::endl;
        fout << "Канал №13" << " - " << "Ротор снизу" << std::endl;
        fout << "Канал №14" << " - " << "Станина слева" << std::endl;
        fout << "Канал №15" << " - " << "Станина слева" << std::endl;
        fout << "Канал №16" << " - " << "Вал" << std::endl;
        fout << "Канал №17" << " - " << "Клеммная коробка" << std::endl;

        fout << std::endl;

        fout << "Время;";

        for (int i=0; i<17; i++)
        {
            fout << QString("Канал №%1").arg(i+1).toUtf8().data() << ";";
        }

        fout << std::endl;

        fout.close();
    }

    ui->widget_3->ui->plot->clear();

    for (int i = 0; i < dataLineColors.size(); i++)
    {
        ui->widget_3->ui->plot->addDataLine(dataLineColors[i], 0);
    }

    ui->widget_3->raschet_el();
    ui->widget_5->ui->widget_4->startTeplo();
}

void MainWindow::on_action_21_triggered()
{
    ui->action_20->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-start.svg"));
    ui->action_21->setEnabled(false);
    ui->widget_5->ui->widget_4->stopTeplo();
    ui->widget_3->stop();
}

void MainWindow::on_tabWidget_currentChanged(int)
{

}

void MainWindow::on_action_22_triggered()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    kalibr=new Kalibr(this);
    kalibr->showMaximized();
    kalibr->setGeometry(
    QStyle::alignedRect(
    Qt::LeftToRight,
    Qt::AlignCenter,
    kalibr->size(),
    screen->geometry()));
}

//Graph_Settings::Graph_Settings(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::graph_Settings)
//{
//    ui->setupUi(this);
//    ui->tableWidget->setRowCount(30); //задание количества строк таблицы
//    ui->tableWidget->setColumnCount(5); //задание количества столбцов
//    QStringList name2; //объявление указателя на тип QStringList
//    name2 << "№" << "Цвет" << "Свойство" << "Смещение" << "Масштаб"; //перечисление заголовков
//    ui->tableWidget->setHorizontalHeaderLabels(name2); //установка заголовков в таблицу
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); //Устанавливает ограничения на то, как размер заголовка может быть изменен до тех, которые описаны в данном режиме
//    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
//    ui->tableWidget->setSelectionMode(QAbstractItemView :: NoSelection);
//    ui->tableWidget->verticalHeader()->setVisible(false);
//    ui->tableWidget->resizeColumnsToContents();
//    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->tableWidget->setColumnWidth(0, 100);

//    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
//    {
//        for(int column = 0; column<ui->tableWidget->columnCount(); column++)
//        {
//          ui->tableWidget->setItem(row, column, new QTableWidgetItem());
//        }
//    }

//    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("Сопротивление ротора R2, Ом"));
//    ui->tableWidget->setItem(1, 2, new QTableWidgetItem("Индуктивность обмотки статора L1, Гн"));
//    ui->tableWidget->setItem(2, 2, new QTableWidgetItem("Индуктивность обмотки ротора L2, Гн"));
//    ui->tableWidget->setItem(3, 2, new QTableWidgetItem("Индуктивность взаимоиндукции Lm, Гн"));
//    ui->tableWidget->setItem(4, 2, new QTableWidgetItem("Напряжение фазы А, В"));
//    ui->tableWidget->setItem(5, 2, new QTableWidgetItem("Напряжение фазы B, В"));
//    ui->tableWidget->setItem(6, 2, new QTableWidgetItem("Напряжение фазы C, В"));
//    ui->tableWidget->setItem(7, 2, new QTableWidgetItem("Ток фазы А, А"));
//    ui->tableWidget->setItem(8, 2, new QTableWidgetItem("Ток фазы B, А"));
//    ui->tableWidget->setItem(9, 2, new QTableWidgetItem("Ток фазы C, А"));
//    ui->tableWidget->setItem(10, 2, new QTableWidgetItem("Частота вращения, рад/с"));
//    ui->tableWidget->setItem(11, 2, new QTableWidgetItem("Момент на валу, Н*м"));
//    ui->tableWidget->setItem(12, 2, new QTableWidgetItem("Момент Мс, Н*м"));
//    ui->tableWidget->setItem(13,  2, new QTableWidgetItem("Станина, °C"));
//    ui->tableWidget->setItem(14,  2, new QTableWidgetItem("Подшипниковый узел справа сзади, °C"));
//    ui->tableWidget->setItem(15,  2, new QTableWidgetItem("Лобовая часть слева спереди, °C"));
//    ui->tableWidget->setItem(16,  2, new QTableWidgetItem("Подшипниковый узел слева спереди, °C"));
//    ui->tableWidget->setItem(17,  2, new QTableWidgetItem("Лобовая часть слева сзади, °C"));
//    ui->tableWidget->setItem(18,  2, new QTableWidgetItem("Станина, °C"));
//    ui->tableWidget->setItem(19,  2, new QTableWidgetItem("Лобовая часть справа спереди, °C"));
//    ui->tableWidget->setItem(20,  2, new QTableWidgetItem("Лобовая часть справа сзади, °C"));
//    ui->tableWidget->setItem(21,  2, new QTableWidgetItem("Магнитопровод статора, °C"));
//    ui->tableWidget->setItem(22,  2, new QTableWidgetItem("Подшипниковый узел справа спереди, °C"));
//    ui->tableWidget->setItem(23, 2, new QTableWidgetItem("Подшипниковый узел слева сзади, °C"));
//    ui->tableWidget->setItem(24, 2, new QTableWidgetItem("Ротор сверху, °C"));
//    ui->tableWidget->setItem(25, 2, new QTableWidgetItem("Ротор снизу, °C"));
//    ui->tableWidget->setItem(26, 2, new QTableWidgetItem("Станина слева, °C"));
//    ui->tableWidget->setItem(27, 2, new QTableWidgetItem("Станина справа, °C"));
//    ui->tableWidget->setItem(28, 2, new QTableWidgetItem("Вал, °C"));
//    ui->tableWidget->setItem(29, 2, new QTableWidgetItem("Клеммная коробка, °C"));


//    for (int i=0; i<34; i++)
//    {
//        if (ui->tableWidget->item(i, 0) != 0)
//        {
//            ui->tableWidget->item(i, 0)->setText(QString("%1").arg(i+1));
//            ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
//        }
//    }

//    for (int i=0; i<4; i++)
//    {
//        if (ui->tableWidget->item(i, 3) != 0)
//        {
//            ui->tableWidget->item(i, 3)->setTextAlignment(Qt::AlignCenter);
//        }
//    }

//    dataLineColors.append(Qt::red);
//    dataLineColors.append(Qt::green);
//    dataLineColors.append(Qt::cyan);
//    dataLineColors.append(Qt::yellow);

    /*for (int i = 0; i < dataLineColors.size(); i++)
    {
        MainWindow* mainWnd = (MainWindow*)parent;
        mainWnd->ui->widget_2->ui->plot->addDataLine(dataLineColors[i], 0);
    }*/

//    for (int i = 0; i < dataLineColors.size(); i++)
//    {
//        ui->tableWidget->item(i, 1)->setBackground(dataLineColors[i]);
//    }
//  //  connect(ui->tableWidget, &QTableWidget::cellClicked,this, &Graph_Settings::setcolorincell);

//}

//void Graph_Settings::on_pushButton_clicked()
//{
//    close();
//}

//void Graph_Settings::setcolorincell(int row, int column)
//{
//    if (column == 1)
//    {
//        row = ui->tableWidget->currentRow();
//        QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
//        ui->tableWidget->item(row, column)->setBackground(chosenColor);
////        ui->plot->setDataLineColor(row, chosenColor);
//        dataLineColors[row] = chosenColor;
//        repaint();
//    }
//}

void MainWindow::on_action_23_triggered()
{
    QPixmap pixmap(":/system_icons/data/img/system_icons/go-next.svg");
    QIcon ButtonIcon_2(pixmap);
    ui->pushButton_5->setIcon(ButtonIcon_2);
    ui->stackedWidget->show();
    ui->stackedWidget->setCurrentIndex( 2 );
}

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi(this);
}

void AboutDialog::on_pushButton_clicked()
{
    close();
}

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    QListWidgetItem *item_1=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/folder.svg"), "Интерфейс");
    ui->listWidget->addItem(item_1);
    QListWidgetItem *item_2=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/labplot-axis-vertical.svg"), "Исходные данные");
    ui->listWidget->addItem(item_2);
    QListWidgetItem *item_3=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/labplot-matrix-new.svg"), "Идентификация параметров");
    ui->listWidget->addItem(item_3);
    QListWidgetItem *item_4=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/labplot-xy-interpolation-curve.svg"), "Энергетические показатели");
    ui->listWidget->addItem(item_4);
    QListWidgetItem *item_5=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/labplot-zoom-out-y.svg"), "Тепловентиляция");
    ui->listWidget->addItem(item_5);
    QListWidgetItem *item_6=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/map-flat.svg"), "Выходные данные");
    ui->listWidget->addItem(item_6);

    QModelIndex firstRow = ui->listWidget->model()->index(0, 0);
    ui->listWidget->selectionModel()->select(firstRow,
                                   QItemSelectionModel::ClearAndSelect |
                                   QItemSelectionModel::Rows);

    ui->listWidget->setFocus();

    connect(ui->listWidget, &QListWidget::itemSelectionChanged, this, &Settings::on_listWidget_itemSelectionChanged);

    ui->stackedWidget->setCurrentIndex(0);
}

void Settings::on_pushButton_clicked()
{
    close();
}

void Settings::on_pushButton_3_clicked()
{
    close();
}

void Settings::on_listWidget_itemSelectionChanged()
{
    ui->stackedWidget->setCurrentIndex(ui->listWidget->currentRow());
}

void MainWindow::on_action_15_triggered()
{
//    QScreen *screen = QGuiApplication::primaryScreen();
//        rsc2= new Settings(this);
//        rsc2->exec();
//        rsc2->setGeometry(
//            QStyle::alignedRect(
//            Qt::LeftToRight,
//            Qt::AlignCenter,
//            rsc2->size(),
//            screen->geometry()));
    QPixmap pixmap(":/system_icons//data/img/system_icons/go-next.svg");
    QIcon ButtonIcon_2(pixmap);
    ui->pushButton_5->setIcon(ButtonIcon_2);
    ui->stackedWidget->show();
    ui->stackedWidget->setCurrentIndex( 0 );
}

void MainWindow::modelItemChangedSlot(QStandardItem *item)
{
    if (item == item14)
    {
        if (item->text() == "Ручной")
        {
            item93->setEnabled(true);
            item94->setEnabled(true);
            item95->setEnabled(true);
            item96->setEnabled(true);
            item97->setEnabled(true);
            item98->setEnabled(true);
            item99->setEnabled(true);
            item100->setEnabled(true);
            item101->setEnabled(true);
            item102->setEnabled(true);
            item103->setEnabled(true);
            item104->setEnabled(true);
        }
        else
        {
            item93->setEnabled(false);
            item94->setEnabled(false);
            item95->setEnabled(false);
            item96->setEnabled(false);
            item97->setEnabled(false);
            item98->setEnabled(false);
            item99->setEnabled(false);
            item100->setEnabled(false);
            item101->setEnabled(false);
            item102->setEnabled(false);
            item103->setEnabled(false);
            item104->setEnabled(false);
        }
    }
}

void MainWindow::projectFileSelectedSlot(QString projectFile)
{
    item6->setText(projectFile);
}

void MainWindow::projectFileSelectedSlot_2(QString projectFile_2)
{
    item84->setData(projectFile_2, Qt::DisplayRole);
    item84->setData(projectFile_2, Qt::UserRole);
}

void MainWindow::projectFileSelectedSlot_3(QString projectFile_3)
{
    item86->setData(projectFile_3, Qt::DisplayRole);
    item86->setData(projectFile_3, Qt::UserRole);
}

void MainWindow::projectFileSelectedSlot_4(QString projectFile_4)
{
    item86->setData(projectFile_4, Qt::DisplayRole);
    item86->setData(projectFile_4, Qt::UserRole);
}

void MainWindow::projectFileSelectedSlot_5(QString projectFile_5)
{
    item106->setData(projectFile_5, Qt::DisplayRole);
    item106->setData(projectFile_5, Qt::UserRole);
}

void MainWindow::projectFileSelectedSlot_6(QString projectFile_6)
{
    item82->setData(projectFile_6, Qt::DisplayRole);
    item82->setData(projectFile_6, Qt::UserRole);
}

void MainWindow::modelItemChangedSlot_2(QStandardItem *item)
{
    if (item == item88)
    {
        if (item->text() == "Чтение данных из файла для идентификации параметров схемы замещения")
        {
            item105->setEnabled(true);
            item106->setEnabled(true);
        }
        else
        {
            item105->setEnabled(false);
            item106->setEnabled(false);
        }
    }
}

void MainWindow::modelItemChangedSlot_3(QStandardItem *item)
{
    if (item == item80)
    {
        if (item->text() == "Чтение данных из файла для наблюдателя скорости")
        {
            item81->setEnabled(true);
            item82->setEnabled(true);
        }
        else
        {
            item81->setEnabled(false);
            item82->setEnabled(false);
        }
    }
}

void MainWindow::modelItemChangedSlot_4(QStandardItem *item)
{
    if (item == item68)
    {
        if (item->checkState() == Qt::Checked)
        {
            item68->setToolTip(QStringLiteral ("Вкл"));
        }
        else
        {
            item68->setToolTip(QStringLiteral ("Выкл"));
        }
    }
    else
    if (item == item70)
    {
        if (item->checkState() == Qt::Checked)
        {
            item70->setToolTip(QStringLiteral ("Вкл"));
        }
        else
        {
            item70->setToolTip(QStringLiteral ("Выкл"));
        }
    }
    else
    if (item == item72)
    {
        if (item->checkState() == Qt::Checked)
        {
            item72->setToolTip(QStringLiteral ("Вкл"));
        }
        else
        {
            item72->setToolTip(QStringLiteral ("Выкл"));
        }
    }
    else
    if (item == item74)
    {
        if (item->checkState() == Qt::Checked)
        {
            item74->setToolTip(QStringLiteral ("Вкл"));
        }
        else
        {
            item74->setToolTip(QStringLiteral ("Выкл"));
        }
    }
    else
    if (item == item76)
    {
        if (item->checkState() == Qt::Checked)
        {
            item76->setToolTip(QStringLiteral ("Вкл"));
        }
        else
        {
            item76->setToolTip(QStringLiteral ("Выкл"));
        }
    }
    else
    if (item == item78)
    {
        if (item->checkState() == Qt::Checked)
        {
            item78->setToolTip(QStringLiteral ("Вкл"));
        }
        else
        {
            item78->setToolTip(QStringLiteral ("Выкл"));
        }
    }
    else
    if (item == item14)
    {
        if (item->checkState() == Qt::Checked)
        {
            item14->setToolTip(QStringLiteral ("Вкл"));
        }
        else
        {
            item14->setToolTip(QStringLiteral ("Выкл"));
        }
    }
    else
    if (item == item94)
    {
        QString w101=item94->text();
        item94->setToolTip(w101);
    }
    else
    if (item == item96)
    {
        QString w102=item96->text();
        item96->setToolTip(w102);
    }
    else
    if (item == item98)
    {
        QString w103=item98->text();
        item98->setToolTip(w103);
    }
    else
    if (item == item100)
    {
        QString w104=item100->text();
        item100->setToolTip(w104);
    }
    else
    if (item == item102)
    {
        QString w105=item102->text();
        item102->setToolTip(w105);
    }
    else
    if (item == item104)
    {
        QString w106=item104->text();
        item104->setToolTip(w106);
    }
    else
    if (item == item20)
    {
        QString w107=item20->text();
        item20->setToolTip(w107);
    }
    else
    if (item == item22)
    {
        QString w108=item22->text();
        item22->setToolTip(w108);
    }
    else
    if (item == item24)
    {
        QString w109=item24->text();
        item24->setToolTip(w109);
    }
    else
    if (item == item90)
    {
        QString w110=item90->text();
        item90->setToolTip(w110);
    }
    else
    if (item == item92)
    {
        QString w111=item92->text();
        item92->setToolTip(w111);
    }
}

void MainWindow::on_SaveProgectToFile_clicked()
{
    QString filter = "Файл конфигурации проекта (*.imview);;Все файлы (*.*)";
    //QString filter = "Файл конфигурации проекта (*.xml);;Все файлы (*.*)";
    QString str = QFileDialog::getSaveFileName(this, "Выбрать имя, под которым сохранить данные", "/home/elf/ImView/data", filter);

    QFile file(QString("/home/elf/ImView/data/project.xml"));
    file.open(QIODevice::WriteOnly);

    //Создаем объект, с помощью которого осуществляется запись в файл
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ
    xmlWriter.writeStartElement("resources");   // Записываем первый элемент с его именем
    xmlWriter.writeStartElement("project");  // Записываем тег с именем для первого итема

    xmlWriter.writeStartElement("general_settings");

    xmlWriter.writeStartElement("project_name");
    xmlWriter.writeAttribute("value", (item4->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_1");
    xmlWriter.writeAttribute("value", (item88->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("project_path");
    xmlWriter.writeAttribute("value", (item106->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_2");
    xmlWriter.writeAttribute("value", (item80->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("project_path_2");
    xmlWriter.writeAttribute("value", (item82->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("checkbox_1");
    xmlWriter.writeAttribute("boolean", (item68->checkState()? "true" : "false"));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("checkbox_2");
    xmlWriter.writeAttribute("boolean", (item70->checkState()? "true" : "false"));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("checkbox_3");
    xmlWriter.writeAttribute("boolean", (item72->checkState()? "true" : "false"));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("checkbox_4");
    xmlWriter.writeAttribute("boolean", (item74->checkState()? "true" : "false"));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("checkbox_5");
    xmlWriter.writeAttribute("boolean", (item76->checkState()? "true" : "false"));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("checkbox_6");
    xmlWriter.writeAttribute("boolean", (item78->checkState()? "true" : "false"));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_3");
    xmlWriter.writeAttribute("value", (item14->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_1");
    xmlWriter.writeAttribute("value", (item94->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_2");
    xmlWriter.writeAttribute("value", (item96->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_3");
    xmlWriter.writeAttribute("value", (item98->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_4");
    xmlWriter.writeAttribute("value", (item100->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_5");
    xmlWriter.writeAttribute("value", (item102->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("coeff_6");
    xmlWriter.writeAttribute("value", (item104->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_4");
    xmlWriter.writeAttribute("value", (item20->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("time_cikle");
    xmlWriter.writeAttribute("value", (item22->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("time_raboty");
    xmlWriter.writeAttribute("value", (item24->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("moment");
    xmlWriter.writeAttribute("value", (item90->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_5");
    xmlWriter.writeAttribute("value", (item92->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("start_temp");
    xmlWriter.writeAttribute("value", (item28->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();   // Закрываем файл

    JlCompress::compressDir(str, "/home/elf/ImView/data/");
}

void MainWindow::on_LoadProgect_clicked()
{
    QString filter = "Файл конфигурации проекта (*.imview);;Все файлы (*.*)";
    QString str = QFileDialog::getOpenFileName(this, "Выбрать имя, под которым сохранить данные", "/home/elf/ImView/data", filter);
    LoadProject(str);
}

void MainWindow::LoadProject(QString str)
{
    QDir().mkdir("/tmp/imview");
    JlCompress::extractDir(str,"/tmp/imview");
    QFile file(QString("/tmp/imview/project.xml"));
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Ошибка файла", "Не удалось открыть файл", QMessageBox::Ok);
    }
    else
    {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();
        while(!xmlReader.atEnd())
        {
            if(xmlReader.isStartElement())
            {
                if(xmlReader.name() == "project_name")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item4->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_1")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item88->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "project_path")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item106->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item80->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "project_path_2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item82->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "checkbox_1")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "boolean")
                        {
                            QString attribute_value = attr.value().toString();
                            if(attribute_value=="true")
                            {
                                item68->setCheckState(Qt::Checked);
                            }
                            else
                            {
                                item68->setCheckState(Qt::Unchecked);
                            };
                        }
                    }
                }

                else if(xmlReader.name() == "checkbox_2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "boolean")
                        {
                            QString attribute_value = attr.value().toString();
                            if(attribute_value=="true"){
                                item70->setCheckState(Qt::Checked);}
                            else {item70->setCheckState(Qt::Unchecked);};
                        }
                    }
                }

                else if(xmlReader.name() == "checkbox_3")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "boolean")
                        {
                            QString attribute_value = attr.value().toString();
                            if(attribute_value=="true"){
                            item72->setCheckState(Qt::Checked);}
                            else {item72->setCheckState(Qt::Unchecked);};
                        }
                    }
                }

                else if(xmlReader.name() == "checkbox_4")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "boolean")
                        {
                            QString attribute_value = attr.value().toString();
                            if(attribute_value=="true"){
                            item74->setCheckState(Qt::Checked);}
                            else {item74->setCheckState(Qt::Unchecked);};
                        }
                    }
                }

                else if(xmlReader.name() == "checkbox_5")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "boolean")
                        {
                            QString attribute_value = attr.value().toString();
                            if(attribute_value=="true"){
                            item76->setCheckState(Qt::Checked);}
                            else {item76->setCheckState(Qt::Unchecked);};
                        }
                    }
                }

                else if(xmlReader.name() == "checkbox_6")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "boolean")
                        {
                            QString attribute_value = attr.value().toString();
                            if(attribute_value=="true"){
                            item78->setCheckState(Qt::Checked);}
                            else {item78->setCheckState(Qt::Unchecked);};
                        }
                    }
                }

                else if(xmlReader.name() == "combobox_3")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item14->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_1")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item94->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item96->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_3")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item98->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_4")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item100->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_5")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item102->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "coeff_6")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item104->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_4")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item20->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "time_cikle")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item22->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "time_raboty")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item24->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "moment")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item90->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "combobox_5")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item92->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "start_temp")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item28->setText(attribute_value);
                        }
                    }
                }
             }
        xmlReader.readNext(); // Переходим к следующему элементу файла
        }
    file.close(); // Закрываем файл
    }
}

void MainWindow::on_pushButton_5_clicked(bool checked)
{
    if(checked)
    {
        QPixmap pixmap(":/system_icons/data/img/system_icons/go-next.svg");
        QIcon ButtonIcon_1(pixmap);
        ui->pushButton_5->setIcon(ButtonIcon_1);
    }
    else
    {
        QPixmap pixmap(":/system_icons/data/img/system_icons/go-previous.svg");
        QIcon ButtonIcon_2(pixmap);
        ui->pushButton_5->setIcon(ButtonIcon_2);
    }
}

void MainWindow::onButtonClicked()
{
    ui->stackedWidget->setCurrentIndex( 0 );
}

void MainWindow::onButtonClicked2()
{
    ui->stackedWidget->setCurrentIndex( 1 );
}

//void MainWindow::on_item_itemSelectionChanged()
//{
//    QString w11=item88->text();
//    item88->setToolTip(w11);
//}

void MainWindow::on_action_24_triggered()
{
//    QPixmap pixmap(":/system_icons/data/img/system_icons/go-next.svg");
//    QIcon ButtonIcon_2(pixmap);
//    ui->pushButton_5->setIcon(ButtonIcon_2);
    ui->stackedWidget->show();
    ui->stackedWidget->setCurrentIndex( 3 );
}

void MainWindow::on_action_25_triggered()
{
    ui->stackedWidget->show();
    ui->stackedWidget->setCurrentIndex( 2 );
}

void MainWindow::tabClicked()
{
    if(ui->tabWidget->currentIndex()==0)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(0);
    }
    if(ui->tabWidget->currentIndex()==1)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(2);
    }
    if(ui->tabWidget->currentIndex()==2)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(3);
    }
    if(ui->tabWidget->currentIndex()==3)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(9);
    }
}

void MainWindow::tabClicked_2()
{
    if(ui->widget_5->ui->tabWidget->currentIndex() == 0)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(9);
    }
    if(ui->widget_5->ui->tabWidget->currentIndex() == 1)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(4);
    }
    if(ui->widget_5->ui->tabWidget->currentIndex() == 2)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(5);
    }
    if(ui->widget_5->ui->tabWidget->currentIndex() == 3)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(6);
    }
    if(ui->widget_5->ui->tabWidget->currentIndex() == 4)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(7);
    }
}

void MainWindow::setcolorincell(int row, int column)
{
    if ((column == 1) && (row >= 0) && (row <= 3))
    {
        //identf
        QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
        ui->tableWidget->item(row, column)->setBackground(chosenColor);
        ui->widget_2->ui->plot->setDataLineColor(row, chosenColor);
        dataLineColors[row] = chosenColor;
        repaint();
    }
    if ((column == 1) && (row >= 4) && (row <= 12))
    {
        //electromagn
        QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
        ui->tableWidget->item(row, column)->setBackground(chosenColor);
        ui->widget_3->ui->plot->setDataLineColor(row - 4, chosenColor);
        dataLineColors[row - 4] = chosenColor;
        repaint();
    }
    if ((column == 1) && (row >= 13) && (row <= 29))
    {
        //trend
        QColor chosenColor = QColorDialog::getColor(); //return the color chosen by user
        ui->tableWidget->item(row, column)->setBackground(chosenColor);
        ui->widget_5->ui->widget_4->ui->plot->setDataLineColor(row - 13, chosenColor);
        dataLineColors[row - 13] = chosenColor;
        repaint();
    }
}

void MainWindow::on_radioButton_toggled(bool checked)
{
    if (checked)
    {
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1231').text('θ₀');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text827').text('θ₀');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1037').text('θ₀');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1239').text('θ₀');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1007').text('θ₁');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1361').text('θ₂');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text839').text('θ₃');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1145').text('θₖ');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text863').text('θс');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text919').text('θ₄');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text939').text('θ₅');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text971').text('θв');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text947').text('θₚ');"));
    }
    else
    {

    }

}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    if (checked)
    {
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1231').text('%1 °C');").arg(teta_0,0,'f',3));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text827' ).text('%1 °C');").arg(teta_0, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1037').text('%1 °C');").arg(teta_0, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1239').text('%1 °C');").arg(teta_0, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1007').text('%1 °C');").arg(teta_1, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1361').text('%1 °C');").arg(teta_2, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text839' ).text('%1 °C');").arg(teta_3, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1145').text('%1 °C');").arg(teta_4, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text863' ).text('%1 °C');").arg(teta_5, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text919' ).text('%1 °C');").arg(teta_k, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text939' ).text('%1 °C');").arg(teta_c, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text971' ).text('%1 °C');").arg(teta_p, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text947' ).text('%1 °C');").arg(teta_v, 0, 'f', 2));
    }
    else
    {

    }
}

void MainWindow::on_radioButton_3_toggled(bool checked)
{
    if (checked)
    {
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1231').text('%1 Дж');").arg(2000.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text827').text('%1 Дж');").arg(1500.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1037').text('%1 Дж');").arg(500.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1239').text('%1 Дж');").arg(800.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1007').text('%1 Дж');").arg(400.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1361').text('%1 Дж');").arg(400.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text839').text('%1 Дж');").arg(400.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1145').text('%1 Дж');").arg(1500.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text863').text('%1 Дж');").arg(500.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text919').text('%1 Дж');").arg(800.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text939').text('%1 Дж');").arg(400.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text971').text('%1 Дж');").arg(500.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text947').text('%1 Дж');").arg(200.00, 0, 'f', 2));
    }
    else
    {

    }
}

void MainWindow::on_radioButton_4_toggled(bool checked)
{
    if (checked)
    {
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1231').text('%1 Вт');").arg(300.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text827').text('%1 Вт');").arg(200.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1037').text('%1 Вт');").arg(100.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1239').text('%1 Вт');").arg(800.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1007').text('%1 Вт');").arg(500.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1361').text('%1 Вт');").arg(600.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text839').text('%1 Вт');").arg(880.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1145').text('%1 Вт');").arg(200.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text863').text('%1 Вт');").arg(100.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text919').text('%1 Вт');").arg(900.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text939').text('%1 Вт');").arg(600.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text971').text('%1 Вт');").arg(200.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text947').text('%1 Вт');").arg(100.00, 0, 'f', 2));
    }
    else
    {

    }
}

void MainWindow::on_radioButton_5_toggled(bool checked)
{
    if (checked)
    {
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1223').text('λ₁₀');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text883').text('λ₃₀');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1195').text('λₖ₀');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1113').text('λ₅₀');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1153').text('λ₃ₖ');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1025').text('λ₂₁');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1053').text('λс₂');"));

        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text891').text('λс₂');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1101').text('λс₄');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1093').text('λ₄₅');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1065').text('λₚ₂');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1073').text('λₚв');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1081').text('λв₅');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1253').text('λₚ₅');"));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1171').text('λₚ₅');"));
    }
    else
    {

    }

}

void MainWindow::on_radioButton_6_toggled(bool checked)
{
    if (checked)
    {
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1223').text('%1 Вт/°C');").arg(lambda_10, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text883' ).text('%1 Вт/°C');").arg(lambda_21, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1195').text('%1 Вт/°C');").arg(lambda_c2, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1113').text('%1 Вт/°C');").arg(lambda_p2, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1153').text('%1 Вт/°C');").arg(lambda_30, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1025').text('%1 Вт/°C');").arg(lambda_c3, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1053').text('%1 Вт/°C');").arg(lambda_p3, 0, 'f', 2));

        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text891' ).text('%1 Вт/°C');").arg(lambda_3k, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1101').text('%1 Вт/°C');").arg(lambda_c4, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1093').text('%1 Вт/°C');").arg(lambda_pb, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1065').text('%1 Вт/°C');").arg(lambda_p5, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1073').text('%1 Вт/°C');").arg(lambda_k0, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1253').text('%1 Вт/°C');").arg(lambda_45, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1171').text('%1 Вт/°C');").arg(lambda_50, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1081').text('%1 Вт/°C');").arg(lambda_b5, 0, 'f', 2));
    }
    else
    {

    }
}

void MainWindow::on_radioButton_7_toggled(bool checked)
{
    if (checked)
    {
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1223').text('%1 Дж');").arg(2000.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text883').text('%1 Дж');").arg(1500.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1195').text('%1 Дж');").arg(500.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1113').text('%1 Дж');").arg(800.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1153').text('%1 Дж');").arg(400.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1025').text('%1 Дж');").arg(400.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1053').text('%1 Дж');").arg(400.00, 0, 'f', 2));

        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text891').text('%1 Дж');").arg(1500.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1101').text('%1 Дж');").arg(500.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1093').text('%1 Дж');").arg(800.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1065').text('%1 Дж');").arg(400.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1073').text('%1 Дж');").arg(500.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1081').text('%1 Дж');").arg(200.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1253').text('%1 Дж');").arg(200.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1171').text('%1 Дж');").arg(200.00, 0, 'f', 2));
    }
    else
    {

    }
}

void MainWindow::on_radioButton_8_toggled(bool checked)
{
    if (checked)
    {
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1223').text('%1 Вт');").arg(300.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text883').text('%1 Вт');").arg(200.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1195').text('%1 Вт');").arg(100.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1113').text('%1 Вт');").arg(800.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1153').text('%1 Вт');").arg(500.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1025').text('%1 Вт');").arg(600.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1053').text('%1 Вт');").arg(880.00, 0, 'f', 2));

        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text891').text('%1 Вт');").arg(200.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1101').text('%1 Вт');").arg(100.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1093').text('%1 Вт');").arg(900.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1065').text('%1 Вт');").arg(600.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1073').text('%1 Вт');").arg(200.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1081').text('%1 Вт');").arg(100.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1253').text('%1 Вт');").arg(100.00, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1171').text('%1 Вт');").arg(100.00, 0, 'f', 2));

    }
    else
    {

    }
}

void MainWindow::on_save_tepl_dannie_clicked()
{
    QString filter = "Файл конфигурации тепловых данных (*.xml);;Все файлы (*.*)";
    QString str = QFileDialog::getSaveFileName(this, "Выбрать имя, под которым сохранить данные", "/home/elf/ImView/data", filter);

   // QFile file(QString("/home/elf/ImView/data/tepl.xml"));
    QFile file(str);
    file.open(QIODevice::WriteOnly);

    //Создаем объект, с помощью которого осуществляется запись в файл
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ
    xmlWriter.writeStartElement("resources");   // Записываем первый элемент с его именем
    xmlWriter.writeStartElement("tepl_dannie");  // Записываем тег с именем для первого итема

    xmlWriter.writeStartElement("general_settings");

    xmlWriter.writeStartElement("sinxr_scorost");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(0,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kol-vo_par_polusov");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(1,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_osi_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(2,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("diametr_staniny_v_osnovanii_reber");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(3,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("dlina_staniny_so_storony_privoda");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(4,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("dlina_staniny_so_storony_ventilatora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(5,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("zazor_megdu_diffuzorom_i_schitom");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(6,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kolichestvo_reber_staniny");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(7,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_rebra_staniny");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(8,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tolschina_rebra_staniny");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(9,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("vneshny_diametr_ventilatora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(10,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("vneshny_diametr_serdechnika_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(11,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("vnutrenny_diametr_serdechnika_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(12,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("dlina_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(13,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chislo_pazov_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(14,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_shtrichovki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(15,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("bolshaya_shirina_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(16,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("menshaya_shirina_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(17,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(18,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shirina_slica");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(19,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_zubca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(20,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shirina_zubca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(21,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kol-vo_vitkov_v_obmotke_statore");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(22,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chislo_parallelnych_vetvey");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(23,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("srednaja_dlina_obmotki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(24,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("dlina_vileta_lobovoi_chasti_obmotki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(25,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_propitki_obmotki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(26,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tolshina_okraski_obmotki_v_lobovoi_chasty");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(27,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tolschina_pazovoi_izolacii");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(28,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("vneshniy_diametr_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(29,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chislo_pazov_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(30,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shirina_korotkozamakauchego_kolca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(31,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_korotkozamakauchego_kolca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(32,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shirina_lopatki_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(33,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_lopatki_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(34,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kol-vo_lopatok_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(35,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_kachestva_lopatki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(36,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tolschina_zazora_megdu_statorom_i_rotorom");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(37,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kinematicheskaja_vaskost_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(38,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chtlyaja_temperatura_obmotki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(39,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koeff-t_teploprovodnosty_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(40,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koeff-t_teploprovodnosty_medi");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(41,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koeff-t_teploprovodnosty_alumimia");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(42,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koeff-t_teploprovodnosty_stali_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(43,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("diametr_provoda_bez_izolacii");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(44,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("diametr_izolirovannogo_provoda");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(45,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefficient_propitki_obmotki");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(46,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_teploprovodnosty_propitochnogo_sostava");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(47,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_teploprovodnosty_izolacii_provodnikov");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(48,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("vneshnid_diametr_lobovoi_chasti");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(49,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefft_teploprovodnosti_okraski_obmotki_v_lobovoi_chasti");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(50,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefft_teploprovodnosty_izolacii_provodnikov_2");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(51,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("tolshina_vozdushnych_prosloek");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(52,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_zubca_3");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(53,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("srednaja_shirina_zubca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(54,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("diametr_okrugnosti_kasatelnoi_k_dnu_pazov");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(55,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("bolshaja_shirina_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(56,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("menshaja_shirina_paza");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(57,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("visota_paza_2");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(58,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koef-t_kachestva_lopatki_rotora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(59,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shag_reber_staniny");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(60,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chislo_faz_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(61,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("kol-vo_elementarnych_provodnikov");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(62,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("plotnost_medi");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(63,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("udelnaja_teploemkost_medi_obmotki_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(64,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("plotnost_stali");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(65,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("udelnaja_teploemkost_medi_stali");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(66,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("udelnaje_soprotivlenie_medi");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(67,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("poleznaja_mochnost");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(68,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("napragenie_pitanija");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(69,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefficient_poleznogo_deistvia");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(70,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefficient_mochnosti");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(71,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("udelnaje_soprotivlenie_aluminia");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(72,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("srednij_diametr_korotkozamykauchego_kolca");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(73,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("obmotochny_koefficient_obmotki_statora");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(74,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("koefficient_ckosa_pazov");
    xmlWriter.writeAttribute("value", (ui->widget_5->ui->widget_2->ui->tableWidget->item(75,1)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();   // Закрываем файл

    //JlCompress::compressDir(str, "/home/elf/ImView/data/");
}

void MainWindow::on_load_tepl_dannie_clicked()
{
    QString filter = "Файл конфигурации тепловых данных (*.xml);;Все файлы (*.*)";
    QString str = QFileDialog::getOpenFileName(this, "Выбрать имя, под которым сохранить данные", "/home/elf/ImView/data", filter);
    LoadTeplDannie(str);
}

void MainWindow::LoadTeplDannie(QString str)
{
//    QDir().mkdir("/tmp/imview");
//    JlCompress::extractDir(str,"/tmp/imview");


    QFile file(str);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Ошибка файла", "Не удалось открыть файл", QMessageBox::Ok);
    }
    else
    {
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();
        while(!xmlReader.atEnd())
        {
            if(xmlReader.isStartElement())
            {
                if(xmlReader.name() == "sinxr_scorost")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(0,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "kol-vo_par_polusov")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(1,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_osi_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(2,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "diametr_staniny_v_osnovanii_reber")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(3,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "dlina_staniny_so_storony_privoda")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(4,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "dlina_staniny_so_storony_ventilatora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(5,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "zazor_megdu_diffuzorom_i_schitom")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(6,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "kolichestvo_reber_staniny")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(7,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "visota_rebra_staniny")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(8,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "tolschina_rebra_staniny")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(9,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "vneshny_diametr_ventilatora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(10,1)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "vneshny_diametr_serdechnika_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(11,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "vnutrenny_diametr_serdechnika_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(12,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "dlina_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(13,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chislo_pazov_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(14,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_shtrichovki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(15,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "bolshaya_shirina_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(16,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "menshaya_shirina_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(17,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(18,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shirina_slica")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(19,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_zubca")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(20,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shirina_zubca")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(21,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "kol-vo_vitkov_v_obmotke_statore")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(22,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chislo_parallelnych_vetvey")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(23,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "srednaja_dlina_obmotki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(24,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "dlina_vileta_lobovoi_chasti_obmotki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(25,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_propitki_obmotki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(26,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "tolshina_okraski_obmotki_v_lobovoi_chasty")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(27,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "tolschina_pazovoi_izolacii")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(28,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "vneshniy_diametr_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(29,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chislo_pazov_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(30,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shirina_korotkozamakauchego_kolca")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(31,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_korotkozamakauchego_kolca")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(32,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shirina_lopatki_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(33,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_lopatki_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(34,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "kol-vo_lopatok_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(35,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_kachestva_lopatki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(36,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "tolschina_zazora_megdu_statorom_i_rotorom")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(37,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "kinematicheskaja_vaskost_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(38,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chtlyaja_temperatura_obmotki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(39,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koeff-t_teploprovodnosty_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(40,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koeff-t_teploprovodnosty_medi")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(41,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koeff-t_teploprovodnosty_alumimia")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(42,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koeff-t_teploprovodnosty_stali_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(43,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "diametr_provoda_bez_izolacii")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(44,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "diametr_izolirovannogo_provoda")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(45,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koefficient_propitki_obmotki")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(46,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_teploprovodnosty_propitochnogo_sostava")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(47,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_teploprovodnosty_izolacii_provodnikov")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(48,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "vneshnid_diametr_lobovoi_chasti")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(49,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koefft_teploprovodnosti_okraski_obmotki_v_lobovoi_chasti")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(50,1)->setText(attribute_value);
                            qDebug() << attribute_value;
                        }
                    }
                }
                else if(xmlReader.name() == "koefft_teploprovodnosty_izolacii_provodnikov_2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(51,1)->setText(attribute_value);
                            qDebug() << attribute_value;
                        }
                    }
                }
                else if(xmlReader.name() == "tolshina_vozdushnych_prosloek")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(52,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_zubca_3")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(53,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "srednaja_shirina_zubca")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(54,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "diametr_okrugnosti_kasatelnoi_k_dnu_pazov")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(55,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "bolshaja_shirina_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(56,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "menshaja_shirina_paza")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(57,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "visota_paza_2")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(58,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "koef-t_kachestva_lopatki_rotora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(59,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shag_reber_staniny")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(60,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chislo_faz_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(61,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "kol-vo_elementarnych_provodnikov")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(62,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "plotnost_medi")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(63,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "udelnaja_teploemkost_medi_obmotki_statora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(64,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "plotnost_stali")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(65,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "udelnaja_teploemkost_medi_stali")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(66,1)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "udelnaje_soprotivlenie_medi")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->widget_5->ui->widget_2->ui->tableWidget->item(67,1)->setText(attribute_value);
                        }
                    }
                }
            else if(xmlReader.name() == "poleznaja_mochnost")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if (attr.name().toString() == "value")
                    {
                        QString attribute_value = attr.value().toString();
                        ui->widget_5->ui->widget_2->ui->tableWidget->item(68,1)->setText(attribute_value);
                    }
                }
            }
            else if(xmlReader.name() == "napragenie_pitanija")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if (attr.name().toString() == "value")
                    {
                        QString attribute_value = attr.value().toString();
                        ui->widget_5->ui->widget_2->ui->tableWidget->item(69,1)->setText(attribute_value);
                    }
                }
            }
            else if(xmlReader.name() == "koefficient_poleznogo_deistvia")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if (attr.name().toString() == "value")
                    {
                        QString attribute_value = attr.value().toString();
                        ui->widget_5->ui->widget_2->ui->tableWidget->item(70,1)->setText(attribute_value);
                    }
                }
            }
            else if(xmlReader.name() == "koefficient_mochnosti")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if (attr.name().toString() == "value")
                    {
                        QString attribute_value = attr.value().toString();
                        ui->widget_5->ui->widget_2->ui->tableWidget->item(71,1)->setText(attribute_value);
                    }
                }
            }
            else if(xmlReader.name() == "udelnaje_soprotivlenie_aluminia")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if (attr.name().toString() == "value")
                    {
                        QString attribute_value = attr.value().toString();
                        ui->widget_5->ui->widget_2->ui->tableWidget->item(72,1)->setText(attribute_value);
                    }
                }
            }
            else if(xmlReader.name() == "srednij_diametr_korotkozamykauchego_kolca")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if (attr.name().toString() == "value")
                    {
                        QString attribute_value = attr.value().toString();
                        ui->widget_5->ui->widget_2->ui->tableWidget->item(73,1)->setText(attribute_value);
                    }
                }
            }
            else if(xmlReader.name() == "obmotochny_koefficient_obmotki_statora")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if (attr.name().toString() == "value")
                    {
                        QString attribute_value = attr.value().toString();
                        ui->widget_5->ui->widget_2->ui->tableWidget->item(74,1)->setText(attribute_value);
                    }
                }
            }
            else if(xmlReader.name() == "koefficient_ckosa_pazov")
            {
                foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                {
                    if (attr.name().toString() == "value")
                    {
                        QString attribute_value = attr.value().toString();
                        ui->widget_5->ui->widget_2->ui->tableWidget->item(75,1)->setText(attribute_value);
                    }
                }
            }
        }
        xmlReader.readNext(); // Переходим к следующему элементу файла
     }
        file.close(); // Закрываем файл
  }
}

void MainWindow::on_tepl_result_clicked()
{
    double L_a1;
    //ввод данных
    base_tepl.n0      = ui->widget_5->ui->widget_2->ui->tableWidget->item(0,1)->text().toDouble();
    base_tepl.pn      = ui->widget_5->ui->widget_2->ui->tableWidget->item(1,1)->text().toDouble();
    base_tepl.h       = ui->widget_5->ui->widget_2->ui->tableWidget->item(2,1)->text().toDouble();
    base_tepl.D_c     = ui->widget_5->ui->widget_2->ui->tableWidget->item(3,1)->text().toDouble();
    base_tepl.l_sv_pr = ui->widget_5->ui->widget_2->ui->tableWidget->item(4,1)->text().toDouble();
    base_tepl.l_cvv   = ui->widget_5->ui->widget_2->ui->tableWidget->item(5,1)->text().toDouble();
    base_tepl.sig_pr  = ui->widget_5->ui->widget_2->ui->tableWidget->item(6,1)->text().toDouble();
    base_tepl.z_c     = ui->widget_5->ui->widget_2->ui->tableWidget->item(7,1)->text().toDouble();
    base_tepl.h_c     = ui->widget_5->ui->widget_2->ui->tableWidget->item(8,1)->text().toDouble();
    base_tepl.sig_p   = ui->widget_5->ui->widget_2->ui->tableWidget->item(9,1)->text().toDouble();

    base_tepl.D_vent  = ui->widget_5->ui->widget_2->ui->tableWidget->item(10,1)->text().toDouble();
    base_tepl.D_a     = ui->widget_5->ui->widget_2->ui->tableWidget->item(11,1)->text().toDouble();
    base_tepl.D       = ui->widget_5->ui->widget_2->ui->tableWidget->item(12,1)->text().toDouble();
    base_tepl.l_p     = ui->widget_5->ui->widget_2->ui->tableWidget->item(13,1)->text().toDouble();
    base_tepl.Z_1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(14,1)->text().toDouble();
    base_tepl.k_sh    = ui->widget_5->ui->widget_2->ui->tableWidget->item(15,1)->text().toDouble();
    base_tepl.b1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(16,1)->text().toDouble();
    base_tepl.b2      = ui->widget_5->ui->widget_2->ui->tableWidget->item(17,1)->text().toDouble();
    base_tepl.h_p     = ui->widget_5->ui->widget_2->ui->tableWidget->item(18,1)->text().toDouble();
    base_tepl.k_z     = ui->widget_5->ui->widget_2->ui->tableWidget->item(19,1)->text().toDouble();

    base_tepl.h_sl1   = ui->widget_5->ui->widget_2->ui->tableWidget->item(20,1)->text().toDouble();
    base_tepl.b_sl1   = ui->widget_5->ui->widget_2->ui->tableWidget->item(21,1)->text().toDouble();
    base_tepl.h_z1    = ui->widget_5->ui->widget_2->ui->tableWidget->item(22,1)->text().toDouble();
    base_tepl.b_z     = ui->widget_5->ui->widget_2->ui->tableWidget->item(23,1)->text().toDouble();
    base_tepl.w_i     = ui->widget_5->ui->widget_2->ui->tableWidget->item(24,1)->text().toDouble();
    base_tepl.a       = ui->widget_5->ui->widget_2->ui->tableWidget->item(25,1)->text().toDouble();
    base_tepl.l_sr    = ui->widget_5->ui->widget_2->ui->tableWidget->item(26,1)->text().toDouble();
    base_tepl.l_lr    = ui->widget_5->ui->widget_2->ui->tableWidget->item(27,1)->text().toDouble();
    base_tepl.k_p     = ui->widget_5->ui->widget_2->ui->tableWidget->item(28,1)->text().toDouble();
    base_tepl.sig_okr = ui->widget_5->ui->widget_2->ui->tableWidget->item(29,1)->text().toDouble();

    base_tepl.sig_ip  = ui->widget_5->ui->widget_2->ui->tableWidget->item(30,1)->text().toDouble();
    base_tepl.D_rot   = ui->widget_5->ui->widget_2->ui->tableWidget->item(31,1)->text().toDouble();
    base_tepl.Z_2     = ui->widget_5->ui->widget_2->ui->tableWidget->item(32,1)->text().toDouble();
    base_tepl.b_k     = ui->widget_5->ui->widget_2->ui->tableWidget->item(33,1)->text().toDouble();
    base_tepl.a_k     = ui->widget_5->ui->widget_2->ui->tableWidget->item(34,1)->text().toDouble();
    base_tepl.a_l     = ui->widget_5->ui->widget_2->ui->tableWidget->item(35,1)->text().toDouble();
    base_tepl.b_l     = ui->widget_5->ui->widget_2->ui->tableWidget->item(36,1)->text().toDouble();
    base_tepl.z_l     = ui->widget_5->ui->widget_2->ui->tableWidget->item(37,1)->text().toDouble();
    base_tepl.n_l     = ui->widget_5->ui->widget_2->ui->tableWidget->item(38,1)->text().toDouble();
    base_tepl.sig     = ui->widget_5->ui->widget_2->ui->tableWidget->item(39,1)->text().toDouble();

    base_tepl.nu      = ui->widget_5->ui->widget_2->ui->tableWidget->item(40,1)->text().toDouble();
    base_tepl.t_cp    = ui->widget_5->ui->widget_2->ui->tableWidget->item(41,1)->text().toDouble();
    base_tepl.lb_b    = ui->widget_5->ui->widget_2->ui->tableWidget->item(42,1)->text().toDouble();
    base_tepl.lb_m    = ui->widget_5->ui->widget_2->ui->tableWidget->item(43,1)->text().toDouble();
    base_tepl.lb_a    = ui->widget_5->ui->widget_2->ui->tableWidget->item(44,1)->text().toDouble();
    base_tepl.lb_c    = ui->widget_5->ui->widget_2->ui->tableWidget->item(45,1)->text().toDouble();
    base_tepl.d_b_iz  = ui->widget_5->ui->widget_2->ui->tableWidget->item(46,1)->text().toDouble();
    base_tepl.d_iz    = ui->widget_5->ui->widget_2->ui->tableWidget->item(47,1)->text().toDouble();
    base_tepl.k_pr    = ui->widget_5->ui->widget_2->ui->tableWidget->item(48,1)->text().toDouble();
    base_tepl.lb_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(49,1)->text().toDouble();

    base_tepl.nu      = ui->widget_5->ui->widget_2->ui->tableWidget->item(50,1)->text().toDouble();
    base_tepl.t_cp    = ui->widget_5->ui->widget_2->ui->tableWidget->item(51,1)->text().toDouble();
    base_tepl.lb_b    = ui->widget_5->ui->widget_2->ui->tableWidget->item(52,1)->text().toDouble();
    base_tepl.lb_m    = ui->widget_5->ui->widget_2->ui->tableWidget->item(53,1)->text().toDouble();
    base_tepl.lb_a    = ui->widget_5->ui->widget_2->ui->tableWidget->item(54,1)->text().toDouble();
    base_tepl.lb_c    = ui->widget_5->ui->widget_2->ui->tableWidget->item(55,1)->text().toDouble();
    base_tepl.d_b_iz  = ui->widget_5->ui->widget_2->ui->tableWidget->item(56,1)->text().toDouble();
    base_tepl.d_iz    = ui->widget_5->ui->widget_2->ui->tableWidget->item(57,1)->text().toDouble();
    base_tepl.k_pr    = ui->widget_5->ui->widget_2->ui->tableWidget->item(58,1)->text().toDouble();
    base_tepl.lb_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(59,1)->text().toDouble();

    base_tepl.lp_iz   = ui->widget_5->ui->widget_2->ui->tableWidget->item(60,1)->text().toDouble();
    base_tepl.D_vlch  = ui->widget_5->ui->widget_2->ui->tableWidget->item(61,1)->text().toDouble();
    base_tepl.lb_okr  = ui->widget_5->ui->widget_2->ui->tableWidget->item(62,1)->text().toDouble();
    base_tepl.lb_ip   = ui->widget_5->ui->widget_2->ui->tableWidget->item(63,1)->text().toDouble();
    base_tepl.sig_vp  = ui->widget_5->ui->widget_2->ui->tableWidget->item(64,1)->text().toDouble();
    base_tepl.h_z2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(65,1)->text().toDouble();
    base_tepl.b_z2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(66,1)->text().toDouble();
    base_tepl.D_dp    = ui->widget_5->ui->widget_2->ui->tableWidget->item(67,1)->text().toDouble();
    base_tepl.d       = ui->widget_5->ui->widget_2->ui->tableWidget->item(68,1)->text().toDouble();
    base_tepl.d1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(69,1)->text().toDouble();

    base_tepl.P2      = ui->widget_5->ui->widget_2->ui->tableWidget->item(70,1)->text().toDouble();
    base_tepl.U1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(71,1)->text().toDouble();
    base_tepl.n_u     = ui->widget_5->ui->widget_2->ui->tableWidget->item(72,1)->text().toDouble();
    base_tepl.cos_f   = ui->widget_5->ui->widget_2->ui->tableWidget->item(73,1)->text().toDouble();
    base_tepl.ro_al   = ui->widget_5->ui->widget_2->ui->tableWidget->item(74,1)->text().toDouble();
    base_tepl.D_kzk   = ui->widget_5->ui->widget_2->ui->tableWidget->item(75,1)->text().toDouble();


    //Расчет тепловых проводимостей
    //общая тепловая проводимость между сердечником статора и станиной
//    L_a1 = M_PI*l_1*
//    L_d1 = 1/(1/((L_a1)+(1/L_da1)+(1/L_st)));

    //Решение СЛАУ

    double a_data[] = { 0.18, 0.60, 0.57, 0.96,
                        0.41, 0.24, 0.99, 0.58,
                        0.14, 0.30, 0.97, 0.66,
                        0.51, 0.13, 0.19, 0.85 };

    double b_data[] = { 1.0, 2.0, 3.0, 4.0 };

    gsl_matrix_view m = gsl_matrix_view_array (a_data, 4, 4);

    gsl_vector_view b = gsl_vector_view_array (b_data, 4);

    gsl_vector *x = gsl_vector_alloc (4);

    int s;

    gsl_permutation * p = gsl_permutation_alloc (4);

    gsl_linalg_LU_decomp (&m.matrix, p, &s);

    gsl_linalg_LU_solve (&m.matrix, p, &b.vector, x);

    //ВЫВОД ДАННЫХ В ТАБЛИЦЫ

    //вывод температур в таблицу
    teta_0=gsl_vector_get(x, 0);
    teta_1=gsl_vector_get(x, 1);
    teta_2=gsl_vector_get(x, 2);
    teta_3=gsl_vector_get(x, 3);
    //teta_4=gsl_vector_get(x, 4);
    //teta_5=gsl_vector_get(x, 5);
    //teta_k=gsl_vector_get(x, 6);
    //teta_c=gsl_vector_get(x, 7);
    //teta_p=gsl_vector_get(x, 8);
    //teta_v=gsl_vector_get(x, 9);

    gsl_permutation_free (p);
    gsl_vector_free (x);

    ui->widget_5->ui->widget_2->ui->tableWidget_3->item(0,1)->setText(QString::number(teta_0,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_3->item(1,1)->setText(QString::number(teta_1,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_3->item(2,1)->setText(QString::number(teta_2,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_3->item(3,1)->setText(QString::number(teta_3,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_3->item(4,1)->setText(QString::number(teta_4,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_3->item(5,1)->setText(QString::number(teta_5,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_3->item(6,1)->setText(QString::number(teta_k,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_3->item(7,1)->setText(QString::number(teta_c,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_3->item(8,1)->setText(QString::number(teta_p,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_3->item(9,1)->setText(QString::number(teta_v,'f',3));

    //вывод тепловых проводимостей в таблицу
    lambda_10=0.034;
    lambda_21=0.35;
    lambda_c2=0.23;
    lambda_p2=0.021;
    lambda_30=0.034;
    lambda_c3=0.067;
    lambda_p3=0.067;
    lambda_3k=0.67;
    lambda_c4=0.56;
    lambda_pb=0.059;
    lambda_p5=0.0045;
    lambda_k0=0.34;
    lambda_45=0.56;
    lambda_50=0.93;
    lambda_b5=0.043;

    ui->widget_5->ui->widget_2->ui->tableWidget_2->item(0,1)->setText(QString::number(lambda_10,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_2->item(1,1)->setText(QString::number(lambda_21,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_2->item(2,1)->setText(QString::number(lambda_c2,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_2->item(3,1)->setText(QString::number(lambda_p2,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_2->item(4,1)->setText(QString::number(lambda_30,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_2->item(5,1)->setText(QString::number(lambda_c3,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_2->item(6,1)->setText(QString::number(lambda_p3,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_2->item(7,1)->setText(QString::number(lambda_3k,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_2->item(8,1)->setText(QString::number(lambda_c4,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_2->item(9,1)->setText(QString::number(lambda_pb,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_2->item(10,1)->setText(QString::number(lambda_p5,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_2->item(11,1)->setText(QString::number(lambda_k0,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_2->item(12,1)->setText(QString::number(lambda_45,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_2->item(13,1)->setText(QString::number(lambda_50,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_2->item(14,1)->setText(QString::number(lambda_b5,'f',3));

    //вывод тоеплоемкостей в таблицу
    C_0=0.034;
    C_1=0.35;
    C_2=0.23;
    C_3=0.021;
    C_4=0.034;
    C_5=0.067;
    C_k=0.067;
    C_c=0.67;
    C_p=0.56;
    C_v=0.059;

    ui->widget_5->ui->widget_2->ui->tableWidget_4->item(0,1)->setText(QString::number(C_0,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_4->item(1,1)->setText(QString::number(C_1,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_4->item(2,1)->setText(QString::number(C_2,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_4->item(3,1)->setText(QString::number(C_3,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_4->item(4,1)->setText(QString::number(C_4,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_4->item(5,1)->setText(QString::number(C_5,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_4->item(6,1)->setText(QString::number(C_k,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_4->item(7,1)->setText(QString::number(C_c,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_4->item(8,1)->setText(QString::number(C_p,'f',3));
    ui->widget_5->ui->widget_2->ui->tableWidget_4->item(9,1)->setText(QString::number(C_v,'f',3));


}
