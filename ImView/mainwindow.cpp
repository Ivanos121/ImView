#include "qimagewriter.h"
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
//#include <cmath>
#include <QUndoCommand>
#include <QPixmap>
#include <QSvgRenderer>

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
#include "customhelpdelegate.h"
#include "math.h"
#include "plot.h"
#include "tepl_nabludatel.h"
#include "ui_tepl_nabludatel.h"

Base base;
Base_tepl base_tepl;
Model modelss;
double teta_0,teta_1,teta_2,teta_3,teta_4,teta_5,teta_k,teta_c,teta_p, teta_v, teta_z, teta_l_1, teta_l_2, teta_pp;
double lambda_10, lambda_21, lambda_c2,lambda_p2,lambda_30,lambda_c3,lambda_p3,lambda_3k,lambda_c4,lambda_pb,lambda_p5,
lambda_k0,lambda_45,lambda_50,lambda_b5,lambda_pz, lambda_zc, lambda_pc, lambda_ppz, lambda_lc, lambda_l4, lambda_pl, lambda_lp,
lambda_zp,lambda_pс,lambda_л2с,lambda_л14,lambda_пл1,lambda_рл2,lambda_l22,lambda_l14,lambda_pl1,lambda_pl2;
double C_0,C_1,C_2,C_3,C_4,C_5,C_k,C_c,C_p,C_v,C_z,C_pp,C_l_1,C_l_2;
double P_0,P_1,P_2,P_3,P_4,P_5,P_c,P_k,P_p,P_z,P_pp,P_l_1,P_l_2,P_v,P_10,P_30,P_k0,P_50,P_3k,P_21,P_c2,P_c3,P_c4,P_45,P_pc,
P_pb,P_b5,P_p5,P_p2;
double dP_zp,dP_zc,dP_c3,dP_pс,dP_pz,dP_l22,dP_l14,dP_pl1,dP_pl2;
double d_teta_zp,d_teta_zc,d_teta_c3,d_teta_pc,d_teta_pz,d_teta_l22,d_teta_l14,d_teta_pl1,d_teta_pl2,
d_teta_10,d_teta_30,d_teta_k0,d_teta_50,d_teta_3k,d_teta_21,d_teta_c2,d_teta_c4,d_teta_45,
d_teta_pb,d_teta_b5,d_teta_p5,d_teta_p2;
double H0, Qmax, Z0, Z1, Z2, Z3, Z4, Z5, Z6, Qp, Hp, Vcp, Pvent;
double Nsv,N, dNptk, dNvpk, dNvk,dNsvp, dNkd;

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

    ui->widget_6->ui->plot->t_max = 0.01;
    ui->widget_6->ui->plot->U_max = 500.0;
    ui->widget_6->ui->plot->margin_bottom = 40;
    ui->widget_6->ui->plot->margin_left = 100;
    ui->widget_6->ui->plot->reset();

    ui->widget_5->ui->widget->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/ax_var/ax_var_2.html").absoluteFilePath()));
    ui->widget_5->ui->widget_5->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/rad_var/rad_var.html").absoluteFilePath()));
    //ui->widget_6->ui->widget_2->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_tract/vent_tract.html").absoluteFilePath()));
    ui->widget_5->ui->widget_3->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/tepl_schen_zam/tepl_tract.html").absoluteFilePath()));
    ui->widget_5->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/tepl_schen_zam/tepl_tract_stator.html").absoluteFilePath()));
    ui->widget_6->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_flow/vent_flow.html").absoluteFilePath()));
    ui->widget_6->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/ventilator/ventilator.html").absoluteFilePath()));
    ui->widget_6->ui->webEngineView_3->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_schem_zam/vent_schem_zam.html").absoluteFilePath()));
    ui->widget_6->ui->webEngineView_4->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_energo_scheme/vent_energo_scheme.html").absoluteFilePath()));
    ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/energo_scheme/energo_scheme.html").absoluteFilePath()));
    ui->widget_5->ui->widget->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));
    ui->widget_5->ui->widget_5->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));
//    ui->widget_6->ui->widget->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));


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
    ui->treeView->setAlternatingRowColors(true);
//    ui->treeView->setAlternatingRowColors(true);
//    ui->treeView->setStyleSheet("QTreeView{alternate-background-color: rgb(255, 255, 152);background: rgb(255, 255, 222);}");
    ui->treeView->setStyleSheet(
                            "*{"
                            "background: rgb(255, 255, 222);"
                            "}"
                            "*{"
                            "alternate-background-color: rgb(255, 255, 191);"
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

    item116 = new QStandardItem(QStringLiteral ("Настройка каналов"));
    item116->setEditable(false);
    //QString w336=item116->text();
    //item116->setToolTip(w336);
    item117 = new QStandardItem(QStringLiteral ("Выбрать каналы"));
    QString w447=item117->text();
    item117->setToolTip(w447);
    items2.append(item116);
    items2.append(item117);
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

    QList<QStandardItem*> items9;
    item31 = new QStandardItem(QStringLiteral ("Вентиляционная модель"));
    item32 = new QStandardItem();
    items9.append(item31);
    items9.append(item32);
    model->appendRow(items9);
    items9.clear();
    item31->setSelectable(false);
    item31->setEditable(false);
    item32->setSelectable(false);
    item32->setEditable(false);
    QFont newFont5("SansSerif", 10, QFont::Bold,false);
    item31->setFont(newFont5);

    QList<QStandardItem*> items10;
    item33 = new QStandardItem(QStringLiteral ("Вентиляционный режим"));
    item33->setEditable(false);
    item34 = new QStandardItem(QStringLiteral ("Выберите режим"));
    items10.append(item33);
    items10.append(item34);
    item31->appendRow(items10);
    items10.clear();
    item35 = new QStandardItem(QStringLiteral ("Конструкция вентиляционной системы электродвигателя"));
    item35->setEditable(false);
    item36 = new QStandardItem(QString ("Выберите конструкцию"));
    items10.append(item35);
    items10.append(item36);
    item31->appendRow(items10);
    items10.clear();
    item37 = new QStandardItem(QStringLiteral ("Условие 12"));
    item37->setEditable(false);
    item38 = new QStandardItem(QStringLiteral ("Значение 12"));
    items10.append(item37);
    items10.append(item38);
    item31->appendRow(items10);
    items10.clear();

    QList<QStandardItem*> items11;
    item39 = new QStandardItem(QStringLiteral ("Прогнозирование температур"));
    item40 = new QStandardItem();
    items11.append(item39);
    items11.append(item40);
    model->appendRow(items11);
    items11.clear();
    //item39->setForeground(QBrush(Qt::white));
    item39->setSelectable(false);
    item39->setEditable(false);
    item40->setSelectable(false);
    item40->setEditable(false);
    QFont newFont6("SansSerif", 10, QFont::Bold,false);
    item39->setFont(newFont6);

    QList<QStandardItem*> items12;
    item41 = new QStandardItem(QStringLiteral ("Условие 13"));
    item41->setEditable(false);
    item42 = new QStandardItem(QStringLiteral ("Значение 13"));
    items12.append(item41);
    items12.append(item42);
    item39->appendRow(items12);
    items12.clear();
    item43 = new QStandardItem(QStringLiteral ("Условие 14"));
    item43->setEditable(false);
    item44 = new QStandardItem(QString ("Значение 14"));
    items12.append(item43);
    items12.append(item44);
    item39->appendRow(items12);
    items12.clear();
    item45 = new QStandardItem(QStringLiteral ("Условие 15"));
    item45->setEditable(false);
    item46 = new QStandardItem(QStringLiteral ("Значение 15"));
    items12.append(item45);
    items12.append(item46);
    item39->appendRow(items12);
    items12.clear();

    QList<QStandardItem*> items13;
    item47 = new QStandardItem(QStringLiteral ("Оценка остаточного теплового ресурса"));
    item48 = new QStandardItem();
    items13.append(item47);
    items13.append(item48);
    model->appendRow(items13);
    items13.clear();
    //item47->setForeground(QBrush(Qt::white));
    item47->setSelectable(false);
    item47->setEditable(false);
    item48->setSelectable(false);
    item48->setEditable(false);
    QFont newFont7("SansSerif", 10, QFont::Bold,false);
    item47->setFont(newFont7);

    QList<QStandardItem*> items14;
    item49 = new QStandardItem(QStringLiteral ("Условие 16"));
    item49->setEditable(false);
    item50 = new QStandardItem(QStringLiteral ("Значение 16"));
    items14.append(item49);
    items14.append(item50);
    item47->appendRow(items14);
    items14.clear();
    item51 = new QStandardItem(QStringLiteral ("Условие 17"));
    item51->setEditable(false);
    item52 = new QStandardItem(QString ("Значение 17"));
    items14.append(item51);
    items14.append(item52);
    item47->appendRow(items14);
    items14.clear();
    item53 = new QStandardItem(QStringLiteral ("Условие 18"));
    item53->setEditable(false);
    item54 = new QStandardItem(QStringLiteral ("Значение 18"));
    items14.append(item53);
    items14.append(item54);
    item47->appendRow(items14);
    items14.clear();

    QList<QStandardItem*> items15;
    item55 = new QStandardItem(QStringLiteral ("Выходные данные"));
    item56 = new QStandardItem();
    items15.append(item55);
    items15.append(item56);
    model->appendRow(items15);
    items15.clear();
    //item55->setForeground(QBrush(Qt::white));
    item55->setSelectable(false);
    item55->setEditable(false);
    item56->setSelectable(false);
    item56->setEditable(false);
    QFont newFont8("SansSerif", 10, QFont::Bold,false);
    item55->setFont(newFont8);

    QList<QStandardItem*> items16;
    item57 = new QStandardItem(QStringLiteral ("Условие 19"));
    item57->setEditable(false);
    item58 = new QStandardItem(QStringLiteral ("Значение 19"));
    items16.append(item57);
    items16.append(item58);
    item55->appendRow(items16);
    items16.clear();
    item59 = new QStandardItem(QStringLiteral ("Условие 20"));
    item59->setEditable(false);
    item60 = new QStandardItem(QString ("Значение 20"));
    items16.append(item59);
    items16.append(item60);
    item55->appendRow(items16);
    items16.clear();
    item61 = new QStandardItem(QStringLiteral ("Условие 21"));
    item61->setEditable(false);
    item62 = new QStandardItem(QStringLiteral ("Значение 21"));
    items16.append(item61);
    items16.append(item62);
    item55->appendRow(items16);
    items16.clear();

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

//    ui->tabWidget->setCurrentWidget();
//            >CurrentIndex(0);
//    QString currentTabText = ui->tabWidget->tabText(0);
//    setWindowTitle(currentTabText + "@" + QString("base") + QString(" - ImView"));

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
    ui->tableWidget_2->setColumnCount(4);
    QStringList name_2;
    name_2 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_2->setHorizontalHeaderLabels(name_2);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->verticalHeader()->setVisible(true);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView :: SingleSelection);

    for(int row = 0; row<ui->tableWidget_2->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_2->columnCount(); column++)
        {
            ui->tableWidget_2->setItem(row, column, new QTableWidgetItem());
        }
    }

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
    ui->tableWidget_2->setItem(24, 0, new QTableWidgetItem("Момент сопротивления, Н*м"));

    ui->tableWidget_2->setItem(0, 1, new QTableWidgetItem("i_dev_a"));
    ui->tableWidget_2->setItem(1, 1, new QTableWidgetItem("u_dev_a"));
    ui->tableWidget_2->setItem(2, 1, new QTableWidgetItem("p_akt_a"));
    ui->tableWidget_2->setItem(3, 1, new QTableWidgetItem("p_reakt_a"));
    ui->tableWidget_2->setItem(4, 1, new QTableWidgetItem("p_poln_a"));
    ui->tableWidget_2->setItem(5, 1, new QTableWidgetItem("cos_f_a"));
    ui->tableWidget_2->setItem(6, 1, new QTableWidgetItem("i_dev_b"));
    ui->tableWidget_2->setItem(7, 1, new QTableWidgetItem("u_dev_b"));
    ui->tableWidget_2->setItem(8, 1, new QTableWidgetItem("p_akt_b"));
    ui->tableWidget_2->setItem(9, 1, new QTableWidgetItem("p_reakt_b"));
    ui->tableWidget_2->setItem(10, 1, new QTableWidgetItem("p_poln_b"));
    ui->tableWidget_2->setItem(11, 1, new QTableWidgetItem("cos_f_b"));
    ui->tableWidget_2->setItem(12, 1, new QTableWidgetItem("i_dev_c"));
    ui->tableWidget_2->setItem(13, 1, new QTableWidgetItem("u_dev_c"));
    ui->tableWidget_2->setItem(14, 1, new QTableWidgetItem("p_akt_c"));
    ui->tableWidget_2->setItem(15, 1, new QTableWidgetItem("p_reakt_c"));
    ui->tableWidget_2->setItem(16, 1, new QTableWidgetItem("p_poln_c"));
    ui->tableWidget_2->setItem(17, 1, new QTableWidgetItem("cos_f_c"));
    ui->tableWidget_2->setItem(18, 1, new QTableWidgetItem("p_akt"));
    ui->tableWidget_2->setItem(19, 1, new QTableWidgetItem("p_reakt"));
    ui->tableWidget_2->setItem(20, 1, new QTableWidgetItem("p_poln"));
    ui->tableWidget_2->setItem(21, 1, new QTableWidgetItem("cos_f"));
    ui->tableWidget_2->setItem(22, 1, new QTableWidgetItem("omega"));
    ui->tableWidget_2->setItem(23, 1, new QTableWidgetItem("M"));
    ui->tableWidget_2->setItem(24, 1, new QTableWidgetItem("Mc"));

    ui->tableWidget_2->setItem(0, 3, new QTableWidgetItem("А"));
    ui->tableWidget_2->setItem(1, 3, new QTableWidgetItem("В"));
    ui->tableWidget_2->setItem(2, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_2->setItem(3, 3, new QTableWidgetItem("ВА"));
    ui->tableWidget_2->setItem(4, 3, new QTableWidgetItem("ВАР"));
    ui->tableWidget_2->setItem(5, 3, new QTableWidgetItem(" - "));
    ui->tableWidget_2->setItem(6, 3, new QTableWidgetItem("А"));
    ui->tableWidget_2->setItem(7, 3, new QTableWidgetItem("В"));
    ui->tableWidget_2->setItem(8, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_2->setItem(9, 3, new QTableWidgetItem("ВА"));
    ui->tableWidget_2->setItem(10, 3, new QTableWidgetItem("ВАР"));
    ui->tableWidget_2->setItem(11, 3, new QTableWidgetItem(" - "));
    ui->tableWidget_2->setItem(12, 3, new QTableWidgetItem("А"));
    ui->tableWidget_2->setItem(13, 3, new QTableWidgetItem("В"));
    ui->tableWidget_2->setItem(14, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_2->setItem(15, 3, new QTableWidgetItem("ВА"));
    ui->tableWidget_2->setItem(16, 3, new QTableWidgetItem("ВАР"));
    ui->tableWidget_2->setItem(17, 3, new QTableWidgetItem(" - "));
    ui->tableWidget_2->setItem(18, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_2->setItem(19, 3, new QTableWidgetItem("ВА"));
    ui->tableWidget_2->setItem(20, 3, new QTableWidgetItem("ВАР"));
    ui->tableWidget_2->setItem(21, 3, new QTableWidgetItem(" - "));
    ui->tableWidget_2->setItem(22, 3, new QTableWidgetItem("рад/с"));
    ui->tableWidget_2->setItem(23, 3, new QTableWidgetItem("Н*м"));
    ui->tableWidget_2->setItem(24, 3, new QTableWidgetItem("Н*м"));

    for (int i=0; i<ui->tableWidget_2->rowCount(); i++)
    {
        if (ui->tableWidget_2->item(i, 1) != 0)
        {
            ui->tableWidget_2->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_2->item(i, 2) != 0)
        {
            ui->tableWidget_2->item(i, 2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_2->item(i, 3) != 0)
        {
            ui->tableWidget_2->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QPalette p2=ui->tableWidget_2->palette();
    p2.setColor(QPalette::Base, QColor(255, 255, 191));
    p2.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_2->setPalette(p2);

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
    ui->tableWidget_4->setColumnCount(4);
    QStringList name_4;
    name_4 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_4->setHorizontalHeaderLabels(name_4);
    ui->tableWidget_4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_4->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_4->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_4->verticalHeader()->setVisible(true);
    ui->tableWidget_4->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_4->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_4->columnCount(); column++)
        {
            ui->tableWidget_4->setItem(row, column, new QTableWidgetItem());

        }
//        if (ui->tableWidget_9->item(row, 1) != 0)
//        {
//            ui->tableWidget_9->item(row, 1)->setTextAlignment(Qt::AlignCenter);
//        }
//        if (ui->tableWidget_9->item(row, 2) != 0)
//        {
//            ui->tableWidget_9->item(row, 2)->setTextAlignment(Qt::AlignCenter);
//        }
//        if (ui->tableWidget_9->item(row, 3) != 0)
//        {
//            ui->tableWidget_9->item(row, 3)->setTextAlignment(Qt::AlignCenter);
//        }
    }

    //Заполнение полей левой части таблицы для пояснения чекбоксов таблицы tableWidget_3
    ui->tableWidget_4->setItem(0, 0, new QTableWidgetItem("Потребляемая двигателем мощность, Вт"));
    ui->tableWidget_4->setItem(1, 0, new QTableWidgetItem("Потери в обмотке статора Вт"));
    ui->tableWidget_4->setItem(2, 0, new QTableWidgetItem("Потери в стали, Вт"));
    ui->tableWidget_4->setItem(3, 0, new QTableWidgetItem("Потери в обмотке ротора, Вт"));
    ui->tableWidget_4->setItem(4, 0, new QTableWidgetItem("Добавочные потери, Вт"));
    ui->tableWidget_4->setItem(5, 0, new QTableWidgetItem("Механические потери, Вт"));
    ui->tableWidget_4->setItem(6, 0, new QTableWidgetItem("Механическая мощность на валу двигателя, Вт"));
    ui->tableWidget_4->setItem(7, 0, new QTableWidgetItem("Коэффициент полезного действия"));
    ui->tableWidget_4->setItem(8, 0, new QTableWidgetItem("Коэффициент мощности"));

    ui->tableWidget_4->setItem(0, 1, new QTableWidgetItem("P1"));
    ui->tableWidget_4->setItem(1, 1, new QTableWidgetItem("ΔPel1"));
    ui->tableWidget_4->setItem(2, 1, new QTableWidgetItem("ΔPct"));
    ui->tableWidget_4->setItem(3, 1, new QTableWidgetItem("ΔPel2"));
    ui->tableWidget_4->setItem(4, 1, new QTableWidgetItem("ΔPdob"));
    ui->tableWidget_4->setItem(5, 1, new QTableWidgetItem("ΔPmech"));
    ui->tableWidget_4->setItem(6, 1, new QTableWidgetItem("P2"));
    ui->tableWidget_4->setItem(7, 1, new QTableWidgetItem("KPD"));
    ui->tableWidget_4->setItem(8, 1, new QTableWidgetItem("cosf"));

    ui->tableWidget_4->setItem(0, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_4->setItem(1, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_4->setItem(2, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_4->setItem(3, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_4->setItem(4, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_4->setItem(5, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_4->setItem(6, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_4->setItem(7, 3, new QTableWidgetItem("--"));
    ui->tableWidget_4->setItem(8, 3, new QTableWidgetItem("--"));

    for (int i=0; i<ui->tableWidget_4->rowCount(); i++)
    {
        if (ui->tableWidget_4->item(i, 1) != 0)
        {
            ui->tableWidget_4->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_4->item(i, 2) != 0)
        {
            ui->tableWidget_4->item(i, 2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_4->item(i, 3) != 0)
        {
            ui->tableWidget_4->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QPalette p4=ui->tableWidget_4->palette();
    p4.setColor(QPalette::Base, QColor(225, 255, 255));
    p4.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_4->setPalette(p4);

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


    ui->tableWidget_13->setRowCount(20);
    ui->tableWidget_13->setColumnCount(4);
    QStringList name_7;
    name_7 << "Сигнал" << "Величина" << "Значение" << "Размерность";
    ui->tableWidget_13->setHorizontalHeaderLabels(name_7);
    ui->tableWidget_13->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_13->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_13->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_13->verticalHeader()->setVisible(true);
    ui->tableWidget_13->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_13->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_13->columnCount(); column++)
        {
            ui->tableWidget_13->setItem(row, column, new QTableWidgetItem());
        }
    }

    ui->tableWidget_13->setItem(0, 0, new QTableWidgetItem("Начальное давление вентилятора"));
    ui->tableWidget_13->setItem(1, 0, new QTableWidgetItem("Максимальный расход воздуха"));
    ui->tableWidget_13->setItem(2, 0, new QTableWidgetItem("Сопротивление входа в кожух через решетку с острыми кромками"));
    ui->tableWidget_13->setItem(3, 0, new QTableWidgetItem("Сопротивление поворота потока за входной решеткой перед входом в вентилятор"));
    ui->tableWidget_13->setItem(4, 0, new QTableWidgetItem("Сопротивление потока за входным вентилятором перед входом в межреберные каналы"));
    ui->tableWidget_13->setItem(5, 0, new QTableWidgetItem("Сопротивление косого входа в межреберные каналы"));
    ui->tableWidget_13->setItem(6, 0, new QTableWidgetItem("Сопротивление поворота потока в межреберных каналах под кожухом"));
    ui->tableWidget_13->setItem(7, 0, new QTableWidgetItem("Сопротивление выхода воздуха из межреберных каналов в воздушное пространство"));
    ui->tableWidget_13->setItem(8, 0, new QTableWidgetItem("Суммарное сопротивление вентиляционной сети"));
    ui->tableWidget_13->setItem(9, 0, new QTableWidgetItem("Рабочий расход воздуха"));
    ui->tableWidget_13->setItem(10, 0, new QTableWidgetItem("Рабочий набор вентилятора"));
    ui->tableWidget_13->setItem(11, 0, new QTableWidgetItem("Средняя скорость воздуха в межреберных каналах"));
    ui->tableWidget_13->setItem(12, 0, new QTableWidgetItem("Потребляемая вентилятором мощность"));

    ui->tableWidget_13->setItem(0, 1, new QTableWidgetItem("H0"));
    ui->tableWidget_13->setItem(1, 1, new QTableWidgetItem("Qmax"));
    ui->tableWidget_13->setItem(2, 1, new QTableWidgetItem("Z1"));
    ui->tableWidget_13->setItem(3, 1, new QTableWidgetItem("Z2"));
    ui->tableWidget_13->setItem(4, 1, new QTableWidgetItem("Z3"));
    ui->tableWidget_13->setItem(5, 1, new QTableWidgetItem("Z4"));
    ui->tableWidget_13->setItem(6, 1, new QTableWidgetItem("Z5"));
    ui->tableWidget_13->setItem(7, 1, new QTableWidgetItem("Z6"));
    ui->tableWidget_13->setItem(8, 1, new QTableWidgetItem("Z0"));
    ui->tableWidget_13->setItem(9, 1, new QTableWidgetItem("Qp"));
    ui->tableWidget_13->setItem(10, 1, new QTableWidgetItem("Hp"));
    ui->tableWidget_13->setItem(11, 1, new QTableWidgetItem("Vsr"));
    ui->tableWidget_13->setItem(12, 1, new QTableWidgetItem("Pvent"));

    ui->tableWidget_13->setItem(0, 3, new QTableWidgetItem("Па"));
    ui->tableWidget_13->setItem(1, 3, new QTableWidgetItem("м3/с"));
    ui->tableWidget_13->setItem(2, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_13->setItem(3, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_13->setItem(4, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_13->setItem(5, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_13->setItem(6, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_13->setItem(7, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_13->setItem(8, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_13->setItem(9, 3, new QTableWidgetItem("м3/с"));
    ui->tableWidget_13->setItem(10, 3, new QTableWidgetItem("Па"));
    ui->tableWidget_13->setItem(11, 3, new QTableWidgetItem("м/c"));
    ui->tableWidget_13->setItem(12, 3, new QTableWidgetItem("Вт"));

    for (int i=0; i<ui->tableWidget_13->rowCount(); i++)
    {
        if (ui->tableWidget_13->item(i, 1) != 0)
        {
            ui->tableWidget_13->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_13->item(i, 3) != 0)
        {
            ui->tableWidget_13->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget->rowCount(); row++)
    {
        if (ui->tableWidget_13->item(row,0) != 0)
        {
            ui->tableWidget_13->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_13->item(row,1) != 0)
        {
            ui->tableWidget_13->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_13->item(row,2) != 0)
        {
            ui->tableWidget_13->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_13->item(row,3) != 0)
        {
            ui->tableWidget_13->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }


    QPalette p107=ui->tableWidget_13->palette();
    p107.setColor(QPalette::Base, QColor(225, 255, 255));
    p107.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_13->setPalette(p106);

    CustomHelpDelegate* customHelpDelegate13 = new CustomHelpDelegate(this); //создание делегата для создания комбобоксов
    ui->tableWidget_13->setItemDelegateForColumn(0, customHelpDelegate13);

//    ui->tableWidget_8->setRowCount(8);
//    ui->tableWidget_8->setColumnCount(3);
//    QStringList name_8;
//    name_8 << " № " << "Сигнал" << "Величина";
//    ui->tableWidget_8->setHorizontalHeaderLabels(name_8);
//    ui->tableWidget_8->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    ui->tableWidget_8->horizontalHeader()->setStretchLastSection(true);
//    ui->tableWidget_8->verticalHeader()->setVisible(false);
//    ui->tableWidget_8->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->tableWidget_8->setSelectionBehavior(QAbstractItemView :: SelectRows);
//    ui->tableWidget_8->setSelectionMode(QAbstractItemView :: SingleSelection);
//    ui->tableWidget_8->setColumnWidth(0, 100);
//    ui->tableWidget_8->setColumnWidth(1, 400);

    ui->tableWidget_8->setRowCount(30);
    ui->tableWidget_8->setColumnCount(4);
    QStringList name_8;
    name_8 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_8->setHorizontalHeaderLabels(name_8);
    ui->tableWidget_8->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_8->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_8->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_8->verticalHeader()->setVisible(true);
    ui->tableWidget_8->resizeColumnsToContents();


    for(int row = 0; row<ui->tableWidget_8->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_8->columnCount(); column++)
        {
            ui->tableWidget_8->setItem(row, column, new QTableWidgetItem());

        }
    }

//    for (int i=0; i<8; i++)
//    {
//        if (ui->tableWidget_8->item(i, 0) != 0)
//        {
//            ui->tableWidget_8->item(i, 0)->setText(QString("%1").arg(i+1));
//            ui->tableWidget_8->item(i, 0)->setTextAlignment(Qt::AlignCenter);
//        }
//    }

    ui->tableWidget_8->setItem(0, 0, new QTableWidgetItem("Статическое давление, Па"));
    ui->tableWidget_8->setItem(1, 0, new QTableWidgetItem("Динамическое давление, Па"));
    ui->tableWidget_8->setItem(2, 0, new QTableWidgetItem("Полное давление, Па"));
    ui->tableWidget_8->setItem(3, 0, new QTableWidgetItem("Производительность, "));
    ui->tableWidget_8->setItem(4, 0, new QTableWidgetItem("Вал, °C"));
    ui->tableWidget_8->setItem(5, 0, new QTableWidgetItem("Клеммная коробка, °C"));
    ui->tableWidget_8->setItem(6, 0, new QTableWidgetItem("Магнитопровод статора слева, °C"));
    ui->tableWidget_8->setItem(7, 0, new QTableWidgetItem("Магнитопровод статора справа, °C"));

    QPalette p108=ui->tableWidget_8->palette();
    p108.setColor(QPalette::Base, QColor(225, 255, 255));
    p108.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_8->setPalette(p108);

    CustomHelpDelegate* customHelpDelegate8 = new CustomHelpDelegate(this); //создание делегата для создания комбобоксов
    ui->tableWidget_8->setItemDelegateForColumn(0, customHelpDelegate8);


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

    //Вывод расчетных данных по теплу в таблицу
    ui->widget_5->ui->tableWidget->setRowCount(76);
    ui->widget_5->ui->tableWidget->setColumnCount(12);
    QStringList name_12;
    name_12 << "Температура" << "Значение" << "Теплоемкость" << "Значение"
            << "Мощность рассеяния" << "Значение"<< "Теплопроводность" << "Значение"
            << "Мощность рассеяния" << "Значение"<< "Падение температуры" << "Значение";
    ui->widget_5->ui->tableWidget->setHorizontalHeaderLabels(name_12);
    ui->widget_5->ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->widget_5->ui->tableWidget->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->widget_5->ui->tableWidget->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->widget_5->ui->tableWidget->verticalHeader()->setVisible(true);
    ui->widget_5->ui->tableWidget->resizeColumnsToContents();
    ui->widget_5->ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int row = 0; row<ui->widget_5->ui->tableWidget->rowCount(); row++)
    {
        for(int column = 0; column<ui->widget_5->ui->tableWidget->columnCount(); column++)
        {
            ui->widget_5->ui->tableWidget->setItem(row, column, new QTableWidgetItem());
        }
    }

    for(int row = 0; row<ui->widget_5->ui->tableWidget->rowCount(); row++)
    {
        if (ui->widget_5->ui->tableWidget->item(row,1) != 0)
        {
            ui->widget_5->ui->tableWidget->item(row,1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->widget_5->ui->tableWidget->item(row,3) != 0)
        {
            ui->widget_5->ui->tableWidget->item(row,3)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->widget_5->ui->tableWidget->item(row,5) != 0)
        {
            ui->widget_5->ui->tableWidget->item(row,5)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->widget_5->ui->tableWidget->item(row,7) != 0)
        {
            ui->widget_5->ui->tableWidget->item(row,7)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->widget_5->ui->tableWidget->item(row,9) != 0)
        {
            ui->widget_5->ui->tableWidget->item(row,9)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->widget_5->ui->tableWidget->item(row,11) != 0)
        {
            ui->widget_5->ui->tableWidget->item(row,11)->setTextAlignment(Qt::AlignCenter);
        }
    }

    QPalette p=ui->widget_5->ui->tableWidget->palette();
    p.setColor(QPalette::Base, QColor(255, 255, 191));
    p.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->widget_5->ui->tableWidget->setPalette(p);

    CustomHelpDelegate* customHelpDelegate = new CustomHelpDelegate(this); //создание делегата для создания комбобоксов
    ui->widget_5->ui->tableWidget->setItemDelegateForColumn(0, customHelpDelegate);
    ui->widget_5->ui->tableWidget->setItemDelegateForColumn(2, customHelpDelegate);
    ui->widget_5->ui->tableWidget->setItemDelegateForColumn(4, customHelpDelegate);
    ui->widget_5->ui->tableWidget->setItemDelegateForColumn(6, customHelpDelegate);
    ui->widget_5->ui->tableWidget->setItemDelegateForColumn(8, customHelpDelegate);
    ui->widget_5->ui->tableWidget->setItemDelegateForColumn(10, customHelpDelegate);
    ui->tableWidget_2->setItemDelegateForColumn(0, customHelpDelegate);
    ui->tableWidget_4->setItemDelegateForColumn(0, customHelpDelegate);
    ui->tableWidget_7->setItemDelegateForColumn(0, customHelpDelegate);
    ui->tableWidget_10->setItemDelegateForColumn(0, customHelpDelegate);
    ui->tableWidget_11->setItemDelegateForColumn(0, customHelpDelegate);
    ui->tableWidget_12->setItemDelegateForColumn(0, customHelpDelegate);

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


    ui->tableWidget_9->setRowCount(40);
    ui->tableWidget_9->setColumnCount(3);
    QStringList name_9;
    name_9 << " № " << "Сигнал" << "Величина";
    ui->tableWidget_9->setHorizontalHeaderLabels(name_9);
    ui->tableWidget_9->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget_9->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_9->verticalHeader()->setVisible(false);
    ui->tableWidget_9->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_9->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_9->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_9->setColumnWidth(0, 100);
    ui->tableWidget_9->setColumnWidth(1, 400);

    for(int row = 0; row<ui->tableWidget_9->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_9->columnCount(); column++)
        {
            ui->tableWidget_9->setItem(row, column, new QTableWidgetItem());

        }
    }

    for (int i=0; i<ui->tableWidget_9->rowCount(); i++)
    {
        if (ui->tableWidget_9->item(i, 0) != 0)
        {
            ui->tableWidget_9->item(i, 0)->setText(QString("%1").arg(i+1));
            ui->tableWidget_9->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ui->tableWidget_9->setItem(0, 1, new QTableWidgetItem("Lambda_ct"));
    ui->tableWidget_9->setItem(1, 1, new QTableWidgetItem("Lambda_adelta1"));
    ui->tableWidget_9->setItem(2, 1, new QTableWidgetItem("Lambda_a1"));
    ui->tableWidget_9->setItem(3, 1, new QTableWidgetItem("Lambda_delta1"));
    ui->tableWidget_9->setItem(4, 1, new QTableWidgetItem("Lambda_sigma"));
    ui->tableWidget_9->setItem(5, 1, new QTableWidgetItem("Lambda_1z1"));
    ui->tableWidget_9->setItem(6, 1, new QTableWidgetItem("Lambda_12"));
    ui->tableWidget_9->setItem(7, 1, new QTableWidgetItem("Lambda_1ip1"));
    ui->tableWidget_9->setItem(8, 1, new QTableWidgetItem("delta"));
    ui->tableWidget_9->setItem(9, 1, new QTableWidgetItem("Lambda_ekv"));
    ui->tableWidget_9->setItem(10, 1, new QTableWidgetItem("Lambda_epz"));
    ui->tableWidget_9->setItem(11, 1, new QTableWidgetItem("Lambda_i1z"));
    ui->tableWidget_9->setItem(12, 1, new QTableWidgetItem("Lambda_z"));
    ui->tableWidget_9->setItem(13, 1, new QTableWidgetItem("Lambda_nz"));
    ui->tableWidget_9->setItem(14, 1, new QTableWidgetItem("Lambda_i1a"));
    ui->tableWidget_9->setItem(15, 1, new QTableWidgetItem("Lambda_ekpa"));
    ui->tableWidget_9->setItem(16, 1, new QTableWidgetItem("Lambda_2ip1"));
    ui->tableWidget_9->setItem(17, 1, new QTableWidgetItem("Lambda_a"));
    ui->tableWidget_9->setItem(18, 1, new QTableWidgetItem("Lambda_na"));
    ui->tableWidget_9->setItem(19, 1, new QTableWidgetItem("Lambda_za"));
    ui->tableWidget_9->setItem(20, 1, new QTableWidgetItem("Lambda_pl"));
    ui->tableWidget_9->setItem(21, 1, new QTableWidgetItem("Lambda_il"));
    ui->tableWidget_9->setItem(22, 1, new QTableWidgetItem("Lambda_el"));
    ui->tableWidget_9->setItem(23, 1, new QTableWidgetItem("Lambda_al1"));
    ui->tableWidget_9->setItem(24, 1, new QTableWidgetItem("Lambda_l1"));
    ui->tableWidget_9->setItem(25, 1, new QTableWidgetItem("Lambda_lp2"));
    ui->tableWidget_9->setItem(26, 1, new QTableWidgetItem("Lambda_a2"));
    ui->tableWidget_9->setItem(27, 1, new QTableWidgetItem("Lambda_l2"));
    ui->tableWidget_9->setItem(28, 1, new QTableWidgetItem("Lambda_asch"));
    ui->tableWidget_9->setItem(29, 1, new QTableWidgetItem("Lambda_ast"));
    ui->tableWidget_9->setItem(30, 1, new QTableWidgetItem("Lambda_ai"));
    ui->tableWidget_9->setItem(31, 1, new QTableWidgetItem("alpha_stsumm"));
    ui->tableWidget_9->setItem(32, 1, new QTableWidgetItem("Lambda_ct1"));
    ui->tableWidget_9->setItem(33, 1, new QTableWidgetItem("Lambda_asch"));
    ui->tableWidget_9->setItem(34, 1, new QTableWidgetItem("Lambda_p"));

    QPalette p9=ui->tableWidget_9->palette();
    p9.setColor(QPalette::Base, QColor(225, 255, 255));
    p9.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_9->setPalette(p9);

    ui->tableWidget_10->setRowCount(10);
    ui->tableWidget_10->setColumnCount(4);
    QStringList name_10;
    name_10 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_10->setHorizontalHeaderLabels(name_10);
    ui->tableWidget_10->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_10->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_10->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_10->verticalHeader()->setVisible(true);
    ui->tableWidget_10->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_10->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_10->columnCount(); column++)
        {
            ui->tableWidget_10->setItem(row, column, new QTableWidgetItem());

        }
    }

    ui->tableWidget_10->setItem(0, 0, new QTableWidgetItem("Внутренний расчетный диаметр вентилятора"));
    ui->tableWidget_10->setItem(1, 0, new QTableWidgetItem("Внешний расчетный диаметр вентилятора"));
    ui->tableWidget_10->setItem(2, 0, new QTableWidgetItem("Ширина лопатки вентилятора"));
    ui->tableWidget_10->setItem(3, 0, new QTableWidgetItem("Частота вращения вентилятора"));
    ui->tableWidget_10->setItem(4, 0, new QTableWidgetItem("Плотность воздуха"));
    ui->tableWidget_10->setItem(5, 0, new QTableWidgetItem("Суммарная площадь отверстий в сетке кожуха"));
    ui->tableWidget_10->setItem(6, 0, new QTableWidgetItem("Общая площадь сетки кожуха"));
    ui->tableWidget_10->setItem(7, 0, new QTableWidgetItem("Площадь сечения в месте поворота к рабочему колесу"));
    ui->tableWidget_10->setItem(8, 0, new QTableWidgetItem("Угол поворота потока к входным кромкам лопаток рабочего колеса"));
    ui->tableWidget_10->setItem(9, 0, new QTableWidgetItem("Площадь сечения в месте поворота перед входом в межреберные каналы"));
    ui->tableWidget_10->setItem(10, 0, new QTableWidgetItem("Угол поворота потока перед входом в межреберные каналы"));
    ui->tableWidget_10->setItem(11, 0, new QTableWidgetItem("Площадь сечения перед входом в межреберные каналы"));
    ui->tableWidget_10->setItem(12, 0, new QTableWidgetItem("Площадь сечения межреберных каналов от станины до кожуха вентилятора"));
    ui->tableWidget_10->setItem(13, 0, new QTableWidgetItem("Угол натекания потока на ребра станины"));
    ui->tableWidget_10->setItem(14, 0, new QTableWidgetItem("Угол поворота потока в межреберных каналах"));

    ui->tableWidget_10->setItem(0, 1, new QTableWidgetItem("D1р"));
    ui->tableWidget_10->setItem(1, 1, new QTableWidgetItem("D2р"));
    ui->tableWidget_10->setItem(2, 1, new QTableWidgetItem("b"));
    ui->tableWidget_10->setItem(3, 1, new QTableWidgetItem("n"));
    ui->tableWidget_10->setItem(4, 1, new QTableWidgetItem("ro"));
    ui->tableWidget_10->setItem(5, 1, new QTableWidgetItem("Sotv"));
    ui->tableWidget_10->setItem(6, 1, new QTableWidgetItem("S0"));
    ui->tableWidget_10->setItem(7, 1, new QTableWidgetItem("S1"));
    ui->tableWidget_10->setItem(8, 1, new QTableWidgetItem("alpha1"));
    ui->tableWidget_10->setItem(9, 1, new QTableWidgetItem("S2"));
    ui->tableWidget_10->setItem(10, 1, new QTableWidgetItem("alpha2"));
    ui->tableWidget_10->setItem(11, 1, new QTableWidgetItem("S3"));
    ui->tableWidget_10->setItem(12, 1, new QTableWidgetItem("S4"));
    ui->tableWidget_10->setItem(13, 1, new QTableWidgetItem("fi"));
    ui->tableWidget_10->setItem(14, 1, new QTableWidgetItem("fi2"));

    ui->tableWidget_10->setItem(0, 3, new QTableWidgetItem("м"));
    ui->tableWidget_10->setItem(1, 3, new QTableWidgetItem("м"));
    ui->tableWidget_10->setItem(2, 3, new QTableWidgetItem("м"));
    ui->tableWidget_10->setItem(3, 3, new QTableWidgetItem("об/мин"));
    ui->tableWidget_10->setItem(4, 3, new QTableWidgetItem("кг/м3"));
    ui->tableWidget_10->setItem(5, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_10->setItem(6, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_10->setItem(7, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_10->setItem(8, 3, new QTableWidgetItem("град."));
    ui->tableWidget_10->setItem(9, 3, new QTableWidgetItem("град."));
    ui->tableWidget_10->setItem(10, 3, new QTableWidgetItem("alpha2"));
    ui->tableWidget_10->setItem(11, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_10->setItem(12, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_10->setItem(13, 3, new QTableWidgetItem("град."));
    ui->tableWidget_10->setItem(14, 3, new QTableWidgetItem("град."));

    for (int i=0; i<ui->tableWidget_10->rowCount(); i++)
    {

        if (ui->tableWidget_10->item(i, 1) != 0)
        {
            ui->tableWidget_10->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_10->item(i, 3) != 0)
        {
            ui->tableWidget_10->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_10->rowCount(); row++)
    {
        if (ui->tableWidget_10->item(row,0) != 0)
        {
            ui->tableWidget_10->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_10->item(row,1) != 0)
        {
            ui->tableWidget_10->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_10->item(row,2) != 0)
        {
            ui->tableWidget_10->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_10->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_10->item(row,3) != 0)
        {
            ui->tableWidget_10->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    QPalette p_10=ui->tableWidget_10->palette();
    p_10.setColor(QPalette::Base, QColor(255, 255, 191));
    p_10.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_10->setPalette(p_10);

    ui->tableWidget_11->setRowCount(10);
    ui->tableWidget_11->setColumnCount(4);
    QStringList name_11;
    name_11 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_11->setHorizontalHeaderLabels(name_11);
    ui->tableWidget_11->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_11->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_11->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_11->verticalHeader()->setVisible(true);
    ui->tableWidget_11->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_11->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_11->columnCount(); column++)
        {
            ui->tableWidget_11->setItem(row, column, new QTableWidgetItem());

        }
    }

    ui->tableWidget_11->setItem(0, 0, new QTableWidgetItem("Потери на местных сопротивлениях и на трение"));
    ui->tableWidget_11->setItem(1, 0, new QTableWidgetItem("Потери на входе в рабочее колесо"));
    ui->tableWidget_11->setItem(2, 0, new QTableWidgetItem("Потери на вихреобразование пр протекании по тока по лопаткам колеса"));
    ui->tableWidget_11->setItem(3, 0, new QTableWidgetItem("Потери на создание и перемещение неупорядоченных потоков в вентиляторе"));
    ui->tableWidget_11->setItem(4, 0, new QTableWidgetItem("Потери при преобразовании кинетической энергии на выходе колеса в статическое давление"));
    ui->tableWidget_11->setItem(5, 0, new QTableWidgetItem("Мощность, потребляемая вентилятором"));
    ui->tableWidget_11->setItem(6, 0, new QTableWidgetItem("Полезная мощность вентилятора"));
//    ui->tableWidget_11->setItem(7, 0, new QTableWidgetItem("Площадь сечения в месте поворота к рабочему колесу"));
//    ui->tableWidget_11->setItem(8, 0, new QTableWidgetItem("Угол поворота потока к входным кромкам лопаток рабочего колеса"));
//    ui->tableWidget_11->setItem(9, 0, new QTableWidgetItem("Площадь сечения в месте поворота перед входом в межреберные каналы"));
//    ui->tableWidget_11->setItem(10, 0, new QTableWidgetItem("Угол поворота потока перед входом в межреберные каналы"));
//    ui->tableWidget_11->setItem(11, 0, new QTableWidgetItem("Площадь сечения перед входом в межреберные каналы"));
//    ui->tableWidget_11->setItem(12, 0, new QTableWidgetItem("Площадь сечения межреберных каналов от станины до кожуха вентилятора"));
//    ui->tableWidget_11->setItem(13, 0, new QTableWidgetItem("Угол натекания потока на ребра станины"));
//    ui->tableWidget_11->setItem(14, 0, new QTableWidgetItem("Угол поворота потока в межреберных каналах"));

    ui->tableWidget_11->setItem(0, 1, new QTableWidgetItem("ΔPптк"));
    ui->tableWidget_11->setItem(1, 1, new QTableWidgetItem("ΔPврк"));
    ui->tableWidget_11->setItem(2, 1, new QTableWidgetItem("ΔPвк"));
    ui->tableWidget_11->setItem(3, 1, new QTableWidgetItem("ΔPсвп"));
    ui->tableWidget_11->setItem(4, 1, new QTableWidgetItem("ΔPкд"));
    ui->tableWidget_11->setItem(5, 1, new QTableWidgetItem("Nsv"));
    ui->tableWidget_11->setItem(6, 1, new QTableWidgetItem("N"));
//    ui->tableWidget_11->setItem(7, 1, new QTableWidgetItem("S1"));
//    ui->tableWidget_11->setItem(8, 1, new QTableWidgetItem("alpha1"));
//    ui->tableWidget_11->setItem(9, 1, new QTableWidgetItem("S2"));
//    ui->tableWidget_11->setItem(10, 1, new QTableWidgetItem("alpha2"));
//    ui->tableWidget_11->setItem(11, 1, new QTableWidgetItem("S3"));
//    ui->tableWidget_11->setItem(12, 1, new QTableWidgetItem("S4"));
//    ui->tableWidget_11->setItem(13, 1, new QTableWidgetItem("fi"));
//    ui->tableWidget_11->setItem(14, 1, new QTableWidgetItem("fi2"));

    ui->tableWidget_11->setItem(0, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_11->setItem(1, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_11->setItem(2, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_11->setItem(3, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_11->setItem(4, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_11->setItem(5, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_11->setItem(6, 3, new QTableWidgetItem("Вт"));
//    ui->tableWidget_11->setItem(7, 3, new QTableWidgetItem("м2"));
//    ui->tableWidget_11->setItem(8, 3, new QTableWidgetItem("град."));
//    ui->tableWidget_11->setItem(9, 3, new QTableWidgetItem("град."));
//    ui->tableWidget_11->setItem(10, 3, new QTableWidgetItem("alpha2"));
//    ui->tableWidget_11->setItem(11, 3, new QTableWidgetItem("м2"));
//    ui->tableWidget_11->setItem(12, 3, new QTableWidgetItem("м2"));
//    ui->tableWidget_11->setItem(13, 3, new QTableWidgetItem("град."));
//    ui->tableWidget_11->setItem(14, 3, new QTableWidgetItem("град."));

    for (int i=0; i<ui->tableWidget_11->rowCount(); i++)
    {

        if (ui->tableWidget_11->item(i, 1) != 0)
        {
            ui->tableWidget_11->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_11->item(i, 3) != 0)
        {
            ui->tableWidget_11->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_11->rowCount(); row++)
    {
        if (ui->tableWidget_11->item(row,0) != 0)
        {
            ui->tableWidget_11->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_11->item(row,1) != 0)
        {
            ui->tableWidget_11->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_11->item(row,2) != 0)
        {
            ui->tableWidget_11->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_11->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_11->item(row,3) != 0)
        {
            ui->tableWidget_11->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    QPalette p11=ui->tableWidget_11->palette();
    p11.setColor(QPalette::Base, QColor(225, 255, 255));
    p11.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_11->setPalette(p11);



    ui->tableWidget_12->setRowCount(10);
    ui->tableWidget_12->setColumnCount(4);
    QStringList name_121;
    name_121 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_12->setHorizontalHeaderLabels(name_121);
    ui->tableWidget_12->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_12->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_12->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_12->verticalHeader()->setVisible(true);
    ui->tableWidget_12->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_12->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_12->columnCount(); column++)
        {
            ui->tableWidget_12->setItem(row, column, new QTableWidgetItem());

        }
    }

//    ui->tableWidget_12->setItem(0, 0, new QTableWidgetItem("Производительность"));
//    ui->tableWidget_12->setItem(1, 0, new QTableWidgetItem("Полное давление вентилятора"));
//    ui->tableWidget_12->setItem(2, 0, new QTableWidgetItem("Динамическое давление вентилятора"));
//    ui->tableWidget_12->setItem(3, 0, new QTableWidgetItem("Статическое давление вентилятора"));
//    ui->tableWidget_12->setItem(4, 0, new QTableWidgetItem("Полезная мощность вентилятора"));
//    ui->tableWidget_12->setItem(5, 0, new QTableWidgetItem("Потребляемая мощность вентилятора"));
//    ui->tableWidget_12->setItem(6, 0, new QTableWidgetItem("Полный к.п.д. вентилятора"));

    ui->tableWidget_12->setItem(0, 0, new QTableWidgetItem("Производительность"));
    ui->tableWidget_12->setItem(1, 0, new QTableWidgetItem("Полное давление вентилятора"));
    ui->tableWidget_12->setItem(2, 0, new QTableWidgetItem("Динамическое давление вентилятора"));
    ui->tableWidget_12->setItem(3, 0, new QTableWidgetItem("Статическое давление вентилятора"));
    ui->tableWidget_12->setItem(4, 0, new QTableWidgetItem("Полезная мощность вентилятора"));
    ui->tableWidget_12->setItem(5, 0, new QTableWidgetItem("Потребляемая мощность вентилятора"));
    ui->tableWidget_12->setItem(6, 0, new QTableWidgetItem("Полный к.п.д. вентилятора"));

    ui->tableWidget_12->setItem(0, 1, new QTableWidgetItem("Q"));
    ui->tableWidget_12->setItem(1, 1, new QTableWidgetItem("Pv"));
    ui->tableWidget_12->setItem(2, 1, new QTableWidgetItem("Pdv"));
    ui->tableWidget_12->setItem(3, 1, new QTableWidgetItem("Psv"));
    ui->tableWidget_12->setItem(4, 1, new QTableWidgetItem("Nsv"));
    ui->tableWidget_12->setItem(5, 1, new QTableWidgetItem("N"));
    ui->tableWidget_12->setItem(6, 1, new QTableWidgetItem("nu"));

    ui->tableWidget_12->setItem(0, 3, new QTableWidgetItem("м3/с"));
    ui->tableWidget_12->setItem(1, 3, new QTableWidgetItem("Па"));
    ui->tableWidget_12->setItem(2, 3, new QTableWidgetItem("Па"));
    ui->tableWidget_12->setItem(3, 3, new QTableWidgetItem("Па"));
    ui->tableWidget_12->setItem(4, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_12->setItem(5, 3, new QTableWidgetItem("Вт"));
    ui->tableWidget_12->setItem(6, 3, new QTableWidgetItem("-"));

    for (int i=0; i<ui->tableWidget_12->rowCount(); i++)
    {

        if (ui->tableWidget_12->item(i, 1) != 0)
        {
            ui->tableWidget_12->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_12->item(i, 3) != 0)
        {
            ui->tableWidget_12->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_12->rowCount(); row++)
    {
        if (ui->tableWidget_12->item(row,0) != 0)
        {
            ui->tableWidget_12->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_12->item(row,1) != 0)
        {
            ui->tableWidget_12->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_12->item(row,2) != 0)
        {
            ui->tableWidget_12->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_11->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_12->item(row,3) != 0)
        {
            ui->tableWidget_12->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    QPalette p12=ui->tableWidget_12->palette();
    p12.setColor(QPalette::Base, QColor(225, 255, 255));
    p12.setColor(QPalette::AlternateBase, QColor(200, 255, 255));
    ui->tableWidget_12->setPalette(p12);


    ui->tableWidget_7->setRowCount(30);
    ui->tableWidget_7->setColumnCount(4);
    QStringList name_77;
    name_77 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_7->setHorizontalHeaderLabels(name_77);
    ui->tableWidget_7->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_7->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_7->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_7->verticalHeader()->setVisible(true);
    ui->tableWidget_7->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_7->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_7->columnCount(); column++)
        {
            ui->tableWidget_7->setItem(row, column, new QTableWidgetItem());

        }
    }

    ui->tableWidget_7->setItem(0, 0, new QTableWidgetItem("Внутренний расчетный диаметр вентилятора"));
    ui->tableWidget_7->setItem(1, 0, new QTableWidgetItem("Внешний расчетный диаметр вентилятора"));
    ui->tableWidget_7->setItem(2, 0, new QTableWidgetItem("Ширина лопатки вентилятора"));
    ui->tableWidget_7->setItem(3, 0, new QTableWidgetItem("Частота вращения вентилятора"));
    ui->tableWidget_7->setItem(4, 0, new QTableWidgetItem("Плотность воздуха"));
    ui->tableWidget_7->setItem(5, 0, new QTableWidgetItem("Суммарная площадь отверстий в сетке кожуха"));
    ui->tableWidget_7->setItem(6, 0, new QTableWidgetItem("Общая площадь сетки кожуха"));
    ui->tableWidget_7->setItem(7, 0, new QTableWidgetItem("Площадь сечения в месте поворота к рабочему колесу"));
    ui->tableWidget_7->setItem(8, 0, new QTableWidgetItem("Угол поворота потока к входным кромкам лопаток рабочего колеса"));
    ui->tableWidget_7->setItem(9, 0, new QTableWidgetItem("Площадь сечения в месте поворота перед входом в межреберные каналы"));
    ui->tableWidget_7->setItem(10, 0, new QTableWidgetItem("Угол поворота потока перед входом в межреберные каналы"));
    ui->tableWidget_7->setItem(11, 0, new QTableWidgetItem("Площадь сечения перед входом в межреберные каналы"));
    ui->tableWidget_7->setItem(12, 0, new QTableWidgetItem("Площадь сечения межреберных каналов от станины до кожуха вентилятора"));
    ui->tableWidget_7->setItem(13, 0, new QTableWidgetItem("Угол натекания потока на ребра станины"));
    ui->tableWidget_7->setItem(14, 0, new QTableWidgetItem("Угол поворота потока в межреберных каналах"));

    ui->tableWidget_7->setItem(0, 1, new QTableWidgetItem("D1р"));
    ui->tableWidget_7->setItem(1, 1, new QTableWidgetItem("D2р"));
    ui->tableWidget_7->setItem(2, 1, new QTableWidgetItem("b"));
    ui->tableWidget_7->setItem(3, 1, new QTableWidgetItem("n"));
    ui->tableWidget_7->setItem(4, 1, new QTableWidgetItem("ro"));
    ui->tableWidget_7->setItem(5, 1, new QTableWidgetItem("Sotv"));
    ui->tableWidget_7->setItem(6, 1, new QTableWidgetItem("S0"));
    ui->tableWidget_7->setItem(7, 1, new QTableWidgetItem("S1"));
    ui->tableWidget_7->setItem(8, 1, new QTableWidgetItem("α1"));
    ui->tableWidget_7->setItem(9, 1, new QTableWidgetItem("S2"));
    ui->tableWidget_7->setItem(10, 1, new QTableWidgetItem("α2"));
    ui->tableWidget_7->setItem(11, 1, new QTableWidgetItem("S3"));
    ui->tableWidget_7->setItem(12, 1, new QTableWidgetItem("S4"));
    ui->tableWidget_7->setItem(13, 1, new QTableWidgetItem("φ"));
    ui->tableWidget_7->setItem(14, 1, new QTableWidgetItem("φ2"));

    ui->tableWidget_7->setItem(0, 3, new QTableWidgetItem("м"));
    ui->tableWidget_7->setItem(1, 3, new QTableWidgetItem("м"));
    ui->tableWidget_7->setItem(2, 3, new QTableWidgetItem("м"));
    ui->tableWidget_7->setItem(3, 3, new QTableWidgetItem("об/мин"));
    ui->tableWidget_7->setItem(4, 3, new QTableWidgetItem("кг/м3"));
    ui->tableWidget_7->setItem(5, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_7->setItem(6, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_7->setItem(7, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_7->setItem(8, 3, new QTableWidgetItem("град."));
    ui->tableWidget_7->setItem(9, 3, new QTableWidgetItem("град."));
    ui->tableWidget_7->setItem(10, 3, new QTableWidgetItem("alpha2"));
    ui->tableWidget_7->setItem(11, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_7->setItem(12, 3, new QTableWidgetItem("м2"));
    ui->tableWidget_7->setItem(13, 3, new QTableWidgetItem("град."));
    ui->tableWidget_7->setItem(14, 3, new QTableWidgetItem("град."));

    for (int i=0; i<ui->tableWidget_7->rowCount(); i++)
    {

        if (ui->tableWidget_7->item(i, 1) != 0)
        {
            ui->tableWidget_7->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_7->item(i, 3) != 0)
        {
            ui->tableWidget_7->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_7->rowCount(); row++)
    {
        if (ui->tableWidget_7->item(row,0) != 0)
        {
            ui->tableWidget_7->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_7->item(row,1) != 0)
        {
            ui->tableWidget_7->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_7->item(row,2) != 0)
        {
            ui->tableWidget_7->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_7->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_7->item(row,3) != 0)
        {
            ui->tableWidget_7->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    QPalette p_13=ui->tableWidget_7->palette();
    p_13.setColor(QPalette::Base, QColor(255, 255, 191));
    p_13.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_7->setPalette(p_13);

    CustomHelpDelegate* customHelpDelegate2 = new CustomHelpDelegate(this); //создание делегата для создания комбобоксов
    ui->tableWidget_7->setItemDelegateForColumn(0, customHelpDelegate2);



    ui->tableWidget_14->setRowCount(30);
    ui->tableWidget_14->setColumnCount(4);
    QStringList name_14;
    name_14 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_14->setHorizontalHeaderLabels(name_14);
    ui->tableWidget_14->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_14->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_14->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_14->verticalHeader()->setVisible(true);
    ui->tableWidget_14->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_14->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_14->columnCount(); column++)
        {
            ui->tableWidget_14->setItem(row, column, new QTableWidgetItem());

        }
    }
    for (int i=0; i<ui->tableWidget_14->rowCount(); i++)
    {

        if (ui->tableWidget_14->item(i, 1) != 0)
        {
            ui->tableWidget_14->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_14->item(i, 3) != 0)
        {
            ui->tableWidget_14->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }

    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_14->rowCount(); row++)
    {
        if (ui->tableWidget_14->item(row,0) != 0)
        {
            ui->tableWidget_14->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_14->item(row,1) != 0)
        {
            ui->tableWidget_14->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_14->item(row,2) != 0)
        {
            ui->tableWidget_14->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_14->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_14->item(row,3) != 0)
        {
            ui->tableWidget_14->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    QPalette p_14=ui->tableWidget_14->palette();
    p_14.setColor(QPalette::Base, QColor(255, 255, 191));
    p_14.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_14->setPalette(p_14);

    CustomHelpDelegate* customHelpDelegate4 = new CustomHelpDelegate(this); //создание делегата для создания комбобоксов
    ui->tableWidget_14->setItemDelegateForColumn(0, customHelpDelegate4);




    ui->tableWidget_15->setRowCount(30);
    ui->tableWidget_15->setColumnCount(4);
    QStringList name_15;
    name_15 << "Величина" << "Обозначение" << "Значение" << "Размерность";
    ui->tableWidget_15->setHorizontalHeaderLabels(name_15);
    ui->tableWidget_15->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_15->setSelectionBehavior(QAbstractItemView :: SelectRows);
    ui->tableWidget_15->setSelectionMode(QAbstractItemView :: SingleSelection);
    ui->tableWidget_15->verticalHeader()->setVisible(true);
    ui->tableWidget_15->resizeColumnsToContents();

    for(int row = 0; row<ui->tableWidget_15->rowCount(); row++)
    {
        for(int column = 0; column<ui->tableWidget_15->columnCount(); column++)
        {
            ui->tableWidget_15->setItem(row, column, new QTableWidgetItem());

        }
    }

    ui->tableWidget_15->setItem(0, 0, new QTableWidgetItem("Внутренний расчетный диаметр вентилятора"));
    ui->tableWidget_15->setItem(1, 0, new QTableWidgetItem("Внешний расчетный диаметр вентилятора"));
    ui->tableWidget_15->setItem(2, 0, new QTableWidgetItem("Ширина лопатки вентилятора"));
    ui->tableWidget_15->setItem(3, 0, new QTableWidgetItem("Частота вращения вентилятора"));
    ui->tableWidget_15->setItem(4, 0, new QTableWidgetItem("Плотность воздуха"));
    ui->tableWidget_15->setItem(5, 0, new QTableWidgetItem("Суммарная площадь отверстий в сетке кожуха"));
    ui->tableWidget_15->setItem(6, 0, new QTableWidgetItem("Общая площадь сетки кожуха"));
    ui->tableWidget_15->setItem(7, 0, new QTableWidgetItem("Площадь сечения в месте поворота к рабочему колесу"));
    ui->tableWidget_15->setItem(8, 0, new QTableWidgetItem("Угол поворота потока к входным кромкам лопаток рабочего колеса"));
    ui->tableWidget_15->setItem(9, 0, new QTableWidgetItem("Площадь сечения в месте поворота перед входом в межреберные каналы"));
    ui->tableWidget_15->setItem(10, 0, new QTableWidgetItem("Угол поворота потока перед входом в межреберные каналы"));
    ui->tableWidget_15->setItem(11, 0, new QTableWidgetItem("Площадь сечения перед входом в межреберные каналы"));
    ui->tableWidget_15->setItem(12, 0, new QTableWidgetItem("Площадь сечения межреберных каналов от станины до кожуха вентилятора"));
    ui->tableWidget_15->setItem(13, 0, new QTableWidgetItem("Угол натекания потока на ребра станины"));
    ui->tableWidget_15->setItem(14, 0, new QTableWidgetItem("Угол поворота потока в межреберных каналах"));

    for (int i=0; i<ui->tableWidget_15->rowCount(); i++)
    {

        if (ui->tableWidget_15->item(i, 1) != 0)
        {
            ui->tableWidget_15->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_15->item(i, 3) != 0)
        {
            ui->tableWidget_15->item(i, 3)->setTextAlignment(Qt::AlignCenter);
        }
    }


    //запрет редактирования первого столбца
    for(int row = 0; row<ui->tableWidget_15->rowCount(); row++)
    {
        if (ui->tableWidget_15->item(row,0) != 0)
        {
            ui->tableWidget_15->item(row,0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_15->item(row,1) != 0)
        {
            ui->tableWidget_15->item(row,1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
        if (ui->tableWidget_15->item(row,2) != 0)
        {
            ui->tableWidget_15->item(row,2)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
            ui->tableWidget_15->item(row,2)->setTextAlignment(Qt::AlignCenter);
        }
        if (ui->tableWidget_15->item(row,3) != 0)
        {
            ui->tableWidget_15->item(row,3)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        }
    }

    QPalette p_15=ui->tableWidget_15->palette();
    p_15.setColor(QPalette::Base, QColor(255, 255, 191));
    p_15.setColor(QPalette::AlternateBase, QColor(255, 255, 222));
    ui->tableWidget_15->setPalette(p_15);

    CustomHelpDelegate* customHelpDelegate15 = new CustomHelpDelegate(this); //создание делегата для создания комбобоксов
    ui->tableWidget_15->setItemDelegateForColumn(0, customHelpDelegate15);


    ui->tabWidget->setCurrentIndex(0);
    ui->widget_5->ui->tabWidget->setCurrentIndex(0);
    ui->widget_5->ui->tabWidget_2->setCurrentIndex(0);
    ui->widget_6->ui->tabWidget->setCurrentIndex(0);
    ui->widget_7->ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget_3->setCurrentIndex(0);

    //Настройка статусбара
    statusbar_label = new QLabel;
    statusbar_label->setPixmap(QPixmap(":/icons/data/img/icons/archivator_red_24.svg"));
    statusbar_label->setAlignment(Qt::AlignTop);
    ui->statusbar->addWidget(statusbar_label);

    statusbar_label_2 = new QLabel("Архиватор не подключен");
    statusbar_label_2->setAlignment(Qt::AlignTop);
    ui->statusbar->addWidget(statusbar_label_2);

    statusbar_label_3 = new QLabel("");
    statusbar_label_3->setPixmap(QPixmap(":/icons/data/img/icons/osc_red_24.svg"));
    statusbar_label_3->setAlignment(Qt::AlignTop);
    ui->statusbar->addWidget(statusbar_label_3);

    statusbar_label_4 = new QLabel("Осциллограф не подключен");
    statusbar_label_4->setAlignment(Qt::AlignTop);
    ui->statusbar->addWidget(statusbar_label_4);

    statusbar_label_5 = new QLabel("");
    statusbar_label_5->setPixmap(QPixmap(":/icons/data/img/icons/plk_red_24.svg"));
    statusbar_label_5->setAlignment(Qt::AlignTop);
    ui->statusbar->addWidget(statusbar_label_5);

    statusbar_label_6 = new QLabel("ПЛК не подключен");
    statusbar_label_6->setAlignment(Qt::AlignTop);
    ui->statusbar->addWidget(statusbar_label_6);

    statusbar_label_7 = new QLabel("");
    statusbar_label_7->setPixmap(QPixmap(":/icons/data/img/icons/moment_red_24.svg"));
    statusbar_label_7->setAlignment(Qt::AlignTop);
    ui->statusbar->addWidget(statusbar_label_7);

    statusbar_label_8 = new QLabel("Управление моментом не подключено");
    statusbar_label_8->setAlignment(Qt::AlignTop);
    ui->statusbar->addWidget(statusbar_label_8);

    QObject::connect(ui->treeView, &QAbstractItemView::activated,this, &MainWindow::itemEdit);

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
    connect(ui->widget_5->ui->tabWidget_2, &QTabWidget::currentChanged, this,&MainWindow::tabClicked_3);
    connect(ui->widget_6->ui->tabWidget, &QTabWidget::currentChanged, this,&MainWindow::tabClicked_4);
    connect(ui->tabWidget_3, &QTabWidget::currentChanged, this,&MainWindow::tabClicked_5);
    connect(ui->widget_7->ui->tabWidget, &QTabWidget::currentChanged, this,&MainWindow::tabClicked_6);

}

QImage fromSvg(const QString &path, int size)
{
    QSvgRenderer renderer(path);

    QImage image(size, size, QImage::Format_ARGB32);
    image.fill(0x00ffffff);
    QPainter painter(&image);
    renderer.render(&painter);

    return image;
}

void MainWindow::itemEdit()
{
//    if(ui->treeView->isHidden())
//            return;

//        int nrFillItems = 0;
//        foreach(QStandardItem* itemm, item)){
//            if(dynamic_cast<QAbstractGraphicsShapeItem*> (item))
//                nrFillItems++;
//        }
//        if(nrFillItems == 0)
//            return;

//        int currentIndex = itemm->currentIndex();
//        QString currrenttext = colorComboBox->itemData(currentIndex).value<QColor>();
//        undoStack->push(new ChangeItemColorCommand(itemm, currrenttext));

}

void MainWindow::createUndoStackAndActions()
{
    undoStack = new QUndoStack(this);
    undoAction = ui->action_7;
    redoAction =  ui->action_8;
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

//        dirName= QString ("%1""%2""%3").arg("Сеанс ").arg(currentTime.toString("hh:mm:ss ").toUtf8().data()).
//                arg(currentDate.toString("dd.MM.yyyy").toUtf8().data());
        dirName= QString ("%1""%2""%3").arg("Сеанс ",currentTime.toString("hh:mm:ss ").toUtf8().data(),
                currentDate.toString("dd.MM.yyyy").toUtf8().data());

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
        //QDir dir(setpath);
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

void MainWindow::on_tabWidget_currentChanged(int index)
{
    QString currentTabText = ui->tabWidget->tabText(index);
    setWindowTitle(currentTabText + "@" + QString("base") + QString(" - ImView"));
}

//void MainWindow::on_tabWidget_currentChanged(int index)
//{
//    QString currentTabText = ui->tabWidget->tabText(index);
//    setWindowTitle(currentTabText + "@" + QString("base") + QString(" - Konfiguretor"));
//    if(sdb.isOpen())
//    {
//        QFileInfo fi5(fileName);
//        QString base5 = fi5.baseName();
//        ui->label_2->setText(base5);
//        QString currentTabText = ui->tabWidget->tabText(index);
//        setWindowTitle(currentTabText + "@" + QString(base5) + QString(" - Konfiguretor"));
//    }
//}
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

    xmlWriter.writeStartElement("combobox_6");
    xmlWriter.writeAttribute("value", (item30->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("time_step");
    xmlWriter.writeAttribute("value", (item107->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_7");
    xmlWriter.writeAttribute("value", (item34->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_8");
    xmlWriter.writeAttribute("value", (item36->text()));
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
                else if(xmlReader.name() == "combobox_6")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item30->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "time_step")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item107->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "combobox_7")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item34->setText(attribute_value);
                        }
                    }
                }
                if(xmlReader.name() == "combobox_8")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item36->setText(attribute_value);
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

void MainWindow::on_action_24_triggered()
{
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
        ui->stackedWidget->setCurrentIndex(11);
    }
    if(ui->tabWidget->currentIndex()==4)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(5);
    }
    if(ui->tabWidget->currentIndex()==5)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(5);
    }
    if(ui->tabWidget->currentIndex()==7)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(7);
    }
}

void MainWindow::tabClicked_2()
{
    if(ui->widget_5->ui->tabWidget->currentIndex() == 0)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(11);
    }
    if(ui->widget_5->ui->tabWidget->currentIndex() == 1)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(6);
    }
    if(ui->widget_5->ui->tabWidget->currentIndex() == 2)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(4);
    }
    if(ui->widget_5->ui->tabWidget->currentIndex() == 3)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(6);
    }
    if(ui->widget_5->ui->tabWidget->currentIndex() == 4)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(9);
    }
    if(ui->widget_5->ui->tabWidget->currentIndex() == 5)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(10);
    }
}

void MainWindow::tabClicked_3()
{
    if(ui->widget_5->ui->tabWidget_2->currentIndex() == 0)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(4);
    }
    if(ui->widget_5->ui->tabWidget_2->currentIndex() == 1)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(4);
    }
    if(ui->widget_5->ui->tabWidget_2->currentIndex() == 2)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(4);
    }
}

void MainWindow::tabClicked_4()
{
    if(ui->widget_6->ui->tabWidget->currentIndex() == 0)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(5);
    }
    if(ui->widget_6->ui->tabWidget->currentIndex() == 1)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(12);
    }
    if(ui->widget_6->ui->tabWidget->currentIndex() == 2)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(16);
    }
    if(ui->widget_6->ui->tabWidget->currentIndex() == 3)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(13);
    }
    if(ui->widget_6->ui->tabWidget->currentIndex() == 4)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(15);
    }
//    if(ui->widget_6->ui->tabWidget->currentIndex() == 5)
//    {
//        ui->stackedWidget->show();
//        ui->stackedWidget->setCurrentIndex(15);
//    }
}

void MainWindow::tabClicked_5()
{
    if(ui->tabWidget_3->currentIndex() == 0)
    {
        ui->tabWidget_2->show();
        ui->tabWidget_2->setCurrentIndex(0);
    }
    if(ui->tabWidget_3->currentIndex() == 1)
    {
        ui->tabWidget_2->show();
        ui->tabWidget_2->setCurrentIndex(1);
    }
}

void MainWindow::tabClicked_6()
{
    if(ui->widget_7->ui->tabWidget->currentIndex() == 0)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(7);
    }
    if(ui->widget_7->ui->tabWidget->currentIndex() == 1)
    {
        ui->stackedWidget->show();
        ui->stackedWidget->setCurrentIndex(8);
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
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1115').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">p</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text931').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">z</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text851').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">3</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text867').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">c</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text975').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">л1</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text943').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">п</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1011').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">л2</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1065').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">2</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1097').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">4</tspan>');"));
            }
        }
        else if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {
//                teta_0=20;
//                teta_1=50;
//                teta_2=80;
//                teta_3=120;
//                teta_k=70;
//                teta_c=90;
//                teta_4=90;
//                teta_5=130;
//                teta_v=60;
//                teta_p=140;

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1231').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">0</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text827').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">0</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1037').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">0</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1239').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">0</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1007').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">1</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1361').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">2</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text839').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">3</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1145').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">к</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text863').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">с</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text919').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">4</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text939').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">5</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text971').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">в</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text947').html('θ<tspan style=\"font-size: 15px;\" dy=\"3\">р</tspan>');"));
           }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
    }
}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
//                teta_p=20;
//                teta_z=50;
//                teta_3=70;
//                teta_c=76;
//                teta_l_1=120;
//                teta_pp=80;
//                teta_l_2=120;
//                teta_2=60;
//                teta_4=40;

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1115').text('%1 °C');").arg(teta_p,0,'f',2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text931' ).text('%1 °C');").arg(teta_z, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text851').text('%1 °C');").arg(teta_3, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text867').text('%1 °C');").arg(teta_c, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text975').text('%1 °C');").arg(teta_l_1, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text943').text('%1 °C');").arg(teta_pp, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1011' ).text('%1 °C');").arg(teta_l_2, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1065').text('%1 °C');").arg(teta_2, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1097' ).text('%1 °C');").arg(teta_4, 0, 'f', 2));
             }
        }
        if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {
                teta_0=20;
                teta_1=50;
                teta_2=80;
                teta_3=120;
                teta_k=70;
                teta_c=90;
                teta_4=90;
                teta_5=130;
                teta_v=60;
                teta_p=140;

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1231').text('%1 °C');").arg(teta_0,0,'f',3));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text827' ).text('%1 °C');").arg(teta_0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1037').text('%1 °C');").arg(teta_0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1239').text('%1 °C');").arg(teta_0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1007').text('%1 °C');").arg(teta_1, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1361').text('%1 °C');").arg(teta_2, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text839' ).text('%1 °C');").arg(teta_3, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1145').text('%1 °C');").arg(teta_k, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text863' ).text('%1 °C');").arg(teta_c, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text919' ).text('%1 °C');").arg(teta_4, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text939' ).text('%1 °C');").arg(teta_5, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text971' ).text('%1 °C');").arg(teta_v, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text947' ).text('%1 °C');").arg(teta_p, 0, 'f', 2));
            }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
    }
}

void MainWindow::on_radioButton_3_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {               
//                C_p=0.034;
//                C_z=0.35;
//                C_3=0.23;
//                C_c=0.034;
//                C_l_1=0.067;
//                C_pp=0.067;
//                C_l_2=0.67;
//                C_4=0.56;
//                C_4=0.059;

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1115').text('%1 Дж/К');").arg(C_p, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text931').text('%1 Дж/К');").arg(C_z, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text851').text('%1 Дж/К');").arg(C_3, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text867').text('%1 Дж/К');").arg(C_c, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text975').text('%1 Дж/К');").arg(C_l_1, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text943').text('%1 Дж/К');").arg(C_pp, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1011').text('%1 Дж/К');").arg(C_l_2, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1065').text('%1 Дж/К');").arg(C_2, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1097').text('%1 Дж/К');").arg(C_4, 0, 'f', 2));
            }
        }
        if (item30->text() == "Статика (упрощенный вариант)")
        {
    if (checked)
    {
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

        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1231').text('%1 Дж/К');").arg(C_0, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text827').text('%1 Дж/К');").arg(C_0, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1037').text('%1 Дж/К');").arg(C_0, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1239').text('%1 Дж/К');").arg(C_0, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1007').text('%1 Дж/К');").arg(C_1, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1361').text('%1 Дж/К');").arg(C_2, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text839').text('%1 Дж/К');").arg(C_3, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1145').text('%1 Дж/К');").arg(C_4, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text863').text('%1 Дж/К');").arg(C_5, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text919').text('%1 Дж/К');").arg(C_k, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text939').text('%1 Дж/К');").arg(C_c, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text971').text('%1 Дж/К');").arg(C_p, 0, 'f', 2));
        ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text947').text('%1 Дж/К');").arg(C_v, 0, 'f', 2));
    }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
    }
}

void MainWindow::on_radioButton_4_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
//                P_p=20;
//                P_z=100;
//                P_3=120;
//                P_c=502;
//                P_l_1=67;
//                P_pp=76;
//                P_l_2=120;
//                P_2=56;
//                P_4=59;

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1115').text('%1 Вт');").arg(P_p, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text931').text('%1 Вт');").arg(P_z, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text851').text('%1 Вт');").arg(P_3, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text867').text('%1 Вт');").arg(P_c, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text975').text('%1 Вт');").arg(P_l_1, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text943').text('%1 Вт');").arg(P_pp, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1011').text('%1 Вт');").arg(P_l_2, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1065').text('%1 Вт');").arg(P_2, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1097').text('%1 Вт');").arg(P_4, 0, 'f', 2));
            }
        }
        if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1231').text('%1 Вт');").arg(P_0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text827'). text('%1 Вт');").arg(P_0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1037').text('%1 Вт');").arg(P_0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1239').text('%1 Вт');").arg(P_0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1007').text('%1 Вт');").arg(P_1, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1361').text('%1 Вт');").arg(P_2, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text839'). text('%1 Вт');").arg(P_3, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1145').text('%1 Вт');").arg(P_4, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text863'). text('%1 Вт');").arg(P_5, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text919'). text('%1 Вт');").arg(P_k, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text939'). text('%1 Вт');").arg(P_c, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text971'). text('%1 Вт');").arg(P_p, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text947'). text('%1 Вт');").arg(P_v, 0, 'f', 2));

            }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
    }
}

void MainWindow::on_radioButton_5_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
//                lambda_zp=0.034;
//                lambda_zc=0.35;
//                lambda_c3=0.23;
//                lambda_pc=0.021;
//                lambda_pz=0.034;
//                lambda_l2c=0.067;
//                lambda_l14=0.067;
//                lambda_pl1=0.67;
//                lambda_pl2=0.56;

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1131').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">zр</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text891').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">zc</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text843').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">c3</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text915').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">пс</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text993').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">пz</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1053').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">л22</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1085').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">л14</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text967').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">пл1</tspan>');"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1029').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">пл2</tspan>');"));
            }
        }
        else if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {
//                lambda_10=0.034;
//                lambda_30=0.034;
//                lambda_k0=0.34;
//                lambda_50=0.93;
//                lambda_3k=0.67;
//                lambda_21=0.35;
//                lambda_c2=0.23;
//                lambda_c3=0.067;
//                lambda_c4=0.56;
//                lambda_45=0.56;
//                lambda_pc=0.067;
//                lambda_pb=0.059;
//                lambda_b5=0.043;
//                lambda_p5=0.0045;
//                lambda_p2=0.021;

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1223').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">10</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text883').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">30</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1195').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">к0</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1113').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">50</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1153').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">3к</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1025').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">21</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1053').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">с2</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text891').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">с3</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1101').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">с4</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1093').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">45</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1065').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">рс</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1073').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">рв</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1081').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">в5</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1253').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">р5</tspan>');"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1171').html('λ<tspan style=\"font-size: 15px;\" dy=\"3\">р2</tspan>');"));
            }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
    }
}

void MainWindow::on_radioButton_6_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
//                lambda_zp=0.034;
//                lambda_zc=0.35;
//                lambda_c3=0.23;
//                lambda_pc=0.021;
//                lambda_pz=0.034;
//                lambda_l22=0.067;
//                lambda_l14=0.067;
//                lambda_pl1=0.67;
//                lambda_pl2=0.56;

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1131').text('%1 Вт/°C');").arg(lambda_zp, 0, 'f', 3));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text891'). text('%1 Вт/°C');").arg(lambda_zc, 0, 'f', 3));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text843'). text('%1 Вт/°C');").arg(lambda_c3, 0, 'f', 3));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text915'). text('%1 Вт/°C');").arg(lambda_pс, 0, 'f', 3));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text993'). text('%1 Вт/°C');").arg(lambda_pz, 0, 'f', 3));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1053').text('%1 Вт/°C');").arg(lambda_l22, 0, 'f', 3));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1085').text('%1 Вт/°C');").arg(lambda_l14, 0, 'f', 3));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text967'). text('%1 Вт/°C');").arg(lambda_pl1, 0, 'f', 3));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1029').text('%1 Вт/°C');").arg(lambda_pl2, 0, 'f', 3));
            }
        }
        else if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {
                //                lambda_10=0.034;
                //                lambda_30=0.034;
                //                lambda_k0=0.34;
                //                lambda_50=0.93;
                //                lambda_3k=0.67;
                //                lambda_21=0.35;
                //                lambda_c2=0.23;
                //                lambda_c3=0.067;
                //                lambda_c4=0.56;
                //                lambda_45=0.56;
                //                lambda_pc=0.067;
                //                lambda_pb=0.059;
                //                lambda_b5=0.043;
                //                lambda_p5=0.0045;
                //                lambda_p2=0.021;
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1223').text('%1 Вт/°C');").arg(lambda_10, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text883' ).text('%1 Вт/°C');").arg(lambda_30, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1195').text('%1 Вт/°C');").arg(lambda_k0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1113').text('%1 Вт/°C');").arg(lambda_50, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1153').text('%1 Вт/°C');").arg(lambda_3k, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1025').text('%1 Вт/°C');").arg(lambda_21, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1053').text('%1 Вт/°C');").arg(lambda_c2, 0, 'f', 2));

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text891' ).text('%1 Вт/°C');").arg(lambda_c3, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1101').text('%1 Вт/°C');").arg(lambda_c4, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1093').text('%1 Вт/°C');").arg(lambda_45, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1065').text('%1 Вт/°C');").arg(lambda_pc, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1073').text('%1 Вт/°C');").arg(lambda_pb, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1253').text('%1 Вт/°C');").arg(lambda_b5, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1171').text('%1 Вт/°C');").arg(lambda_p5, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1081').text('%1 Вт/°C');").arg(lambda_p2, 0, 'f', 2));
            }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
    }
}

void MainWindow::on_radioButton_7_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
//                dP_zp=100;
//                dP_zc=220;
//                dP_c3=230;
//                dP_pс=450;
//                dP_pz=120;
//                dP_l22=340;
//                dP_l14=560;
//                dP_pl1=506;
//                dP_pl2=760;

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1131').text('%1 Вт');").arg(dP_zp, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text891').text('%1 Вт);").arg(dP_zc, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text843').text('%1 Вт');").arg(dP_c3, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text915').text('%1 Вт');").arg(dP_pс, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text993').text('%1 Вт');").arg(dP_pz, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1053').text('%1 Вт');").arg(dP_l22, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1085').text('%1 Вт');").arg(dP_l14, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text967').text('%1 Вт');").arg(dP_pl1, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1029').text('%1 Вт');").arg(dP_pl2, 0, 'f', 2));
            }
        }
        else if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {
//                P_10=100;
//                P_30=220;
//                P_k0=230;
//                P_50=450;
//                P_3k=120;
//                P_21=340;
//                P_c2=560;
//                P_c3=506;
//                P_c4=760;
//                P_45=100;
//                P_pc=220;
//                P_pb=230;
//                P_b5=450;
//                P_p5=120;
//                P_p2=340;

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1223').text('%1 °C');").arg(P_10, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text883').text('%1 °C');").arg(P_30, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1195').text('%1 °C');").arg(P_k0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1113').text('%1 °C');").arg(P_50, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1153').text('%1 °C');").arg(P_3k, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1025').text('%1 °C');").arg(P_21, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1053').text('%1 °C');").arg(P_c2, 0, 'f', 2));

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text891').text('%1 °C');").arg(P_c3, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1101').text('%1 °C');").arg(P_c4, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1093').text('%1 °C');").arg(P_45, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1065').text('%1 °C');").arg(P_pc, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1073').text('%1 °C');").arg(P_pb, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1081').text('%1 °C');").arg(P_b5, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1253').text('%1 °C');").arg(P_p5, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1171').text('%1 °C');").arg(P_p2, 0, 'f', 2));
            }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
    }
}

void MainWindow::on_radioButton_8_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
//                d_teta_zp=10;
//                d_teta_zc=5;
//                d_teta_c3=20;
//                d_teta_pc=30;
//                d_teta_pz=15;
//                d_teta_l22=10;
//                d_teta_l14=5;
//                d_teta_pl1=35;
//                d_teta_pl2=35;

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1131').text('%1 °C');").arg(d_teta_zp, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text891').text('%1 °C');").arg(d_teta_zc, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text843').text('%1 °C');").arg(d_teta_c3, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text915').text('%1 °C');").arg(d_teta_pc, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text993').text('%1 °C');").arg(d_teta_pz, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1053').text('%1 °C');").arg(d_teta_l22, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1085').text('%1 °C');").arg(d_teta_l14, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text967').text('%1 °C');").arg(d_teta_pl1, 0, 'f', 2));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1029').text('%1 °C');").arg(d_teta_pl2, 0, 'f', 2));
            }
        }
        if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {
                //                d_teta_10=100;
                //                d_teta_30=220;
                //                d_teta_k0=230;
                //                d_teta_50=450;
                //                d_teta_3k=120;
                //                d_teta_21=340;
                //                d_teta_c2=560;
                //                d_teta_c3=506;
                //                d_teta_c4=760;
                //                d_teta_45=100;
                //                d_teta_pc=220;
                //                d_teta_pb=230;
                //                d_teta_b5=450;
                //                d_teta_p5=120;
                //                d_teta_p2=340;

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1223').text('%1 Вт');").arg(d_teta_10, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text883').text('%1 Вт');").arg(d_teta_30, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1195').text('%1 Вт');").arg(d_teta_k0, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1113').text('%1 Вт');").arg(d_teta_50, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1153').text('%1 Вт');").arg(d_teta_3k,0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1025').text('%1 Вт');").arg(d_teta_21, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1053').text('%1 Вт');").arg(d_teta_c2, 0, 'f', 2));

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text891').text('%1 Вт');").arg(d_teta_c3, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1101').text('%1 Вт');").arg(d_teta_c4, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1093').text('%1 Вт');").arg(d_teta_45, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1065').text('%1 Вт');").arg(d_teta_pc, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1073').text('%1 Вт');").arg(d_teta_pb, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1081').text('%1 Вт');").arg(d_teta_b5, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1253').text('%1 Вт');").arg(d_teta_p5, 0, 'f', 2));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1171').text('%1 Вт');").arg(d_teta_p2, 0, 'f', 2));
            }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
    }
}

void MainWindow::on_radioButton_9_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
                //ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1131').hide();"));

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1115').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text931').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text851').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text867').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text975').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text943').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1011').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1065').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1097').hide();"));
            }
            else
            {
                //ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1131').show();"));

                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1115').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text931').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text851').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text867').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text975').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text943').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1011').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1065').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1097').show();"));

            }
        }
        else if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1231').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text827').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1037').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1239').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1007').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1361').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text839').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1145').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text863').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text919').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text939').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text971').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text947').hide();"));
            }
            else
            {
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1231').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text827').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1037').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1239').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1007').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1361').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text839').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1145').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text863').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text919').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text939').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text971').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text947').show();"));
            }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
    }
}

void MainWindow::on_radioButton_10_toggled(bool checked)
{
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            if (checked)
            {
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1131').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text891').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text843').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text915').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text993').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1053').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1085').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text967').hide();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1029').hide();"));
            }
            else
            {
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1131').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text891').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text843').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text915').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text993').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1053').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1085').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text967').show();"));
                ui->widget_5->ui->webEngineView_2->page()->runJavaScript(QString("$('#text1029').show();"));
            }
        }
        else if (item30->text() == "Статика (упрощенный вариант)")
        {
            if (checked)
            {
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1223').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text883').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1195').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1113').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1153').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1025').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1053').hide();"));

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text891').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1101').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1093').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1065').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1073').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1081').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1253').hide();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1171').hide();"));
            }
            else
            {
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1223').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text883').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1195').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1113').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1153').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1025').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1053').show();"));

                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text891').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1101').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1093').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1065').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1073').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1081').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1253').show();"));
                ui->widget_5->ui->widget_3->ui->webEngineView->page()->runJavaScript(QString("$('#text1171').show();"));
            }
        }
        else if (item30->text() == "Статика (полный вариант)")
        {
            if (checked)
            {
                QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
            }
        }
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

void MainWindow::on_save_Vent_dannie_clicked()
{
    QString filter2 = "Файл конфигурации вентиляционных данных (*.xml);;Все файлы (*.*)";
    QString str2 = QFileDialog::getSaveFileName(this, "Выбрать имя, под которым сохранить данные", "/home/elf/ImView/data", filter2);

   // QFile file(QString("/home/elf/ImView/data/vent.xml"));
    QFile file(str2);
    file.open(QIODevice::WriteOnly);

    //Создаем объект, с помощью которого осуществляется запись в файл
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);  // Устанавливаем автоформатирование текста
    xmlWriter.writeStartDocument();     // Запускаем запись в документ
    xmlWriter.writeStartElement("resources");   // Записываем первый элемент с его именем
    xmlWriter.writeStartElement("vent_dannie");  // Записываем тег с именем для первого итема

    xmlWriter.writeStartElement("general_settings");

    xmlWriter.writeStartElement("intenal_diameter_ventilator");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(0,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("extenal_diameter_ventilator");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(1,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("shirina_lopatki_ventilatora");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(2,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("chastota_vrasachenia_ventilatora");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(3,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("plotnost_vozducha");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(4,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("summarnaja_ploschad_otverstiy_v_setke_kogucha");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(5,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Obchaja_ploschad_setki_kogucha");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(6,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ploschad_sechenia_v_meste_povorota_k_rabochemu_kolesu");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(7,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ugol_povorota_potoka_k_vchodnim_kromkam_lopatok_rabochego_kolesa");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(8,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ploschad_sechenia_v_meste_povorota_pered_vchodom_v_megrebernye_kanaly");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(9,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ugol_povorota_potoka_pered_vhodom_v_megrebernye_kanaly");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(10,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ploschad_sechenia_pered_vhodom_v_megrebernye_kanaly");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(11,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ploschad_sechenia_megrebernyh_kanalov_ot_staniny_do_koguha_ventilatora");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(12,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ugol_natekania_potoka_na_rebra_staniny");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(13,2)->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("Ugol_povorota_potoka_v_megrebernych_kanalah");
    xmlWriter.writeAttribute("value", (ui->tableWidget_7->item(14,2)->text()));
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

void MainWindow::on_load_Vent_dannie_clicked()
{
    QString filter = "Файл конфигурации тепловых данных (*.xml);;Все файлы (*.*)";
    QString str = QFileDialog::getOpenFileName(this, "Выбрать имя, под которым сохранить данные", "/home/elf/ImView/data", filter);
    LoadVentDannie(str);
}

void MainWindow::LoadVentDannie(QString str)
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
                if(xmlReader.name() == "intenal_diameter_ventilator")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(0,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "extenal_diameter_ventilator")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(1,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "shirina_lopatki_ventilatora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(2,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "chastota_vrasachenia_ventilatora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(3,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "plotnost_vozducha")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(4,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "summarnaja_ploschad_otverstiy_v_setke_kogucha")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(5,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Obchaja_ploschad_setki_kogucha")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(6,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Ploschad_sechenia_v_meste_povorota_k_rabochemu_kolesu")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(7,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Ugol_povorota_potoka_k_vchodnim_kromkam_lopatok_rabochego_kolesa")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(8,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Ploschad_sechenia_v_meste_povorota_pered_vchodom_v_megrebernye_kanaly")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(9,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Ugol_povorota_potoka_pered_vhodom_v_megrebernye_kanaly")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(10,2)->setText(attribute_value);
                        }
                    }
                }

                else if(xmlReader.name() == "Ploschad_sechenia_pered_vhodom_v_megrebernye_kanaly")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(11,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "Ploschad_sechenia_megrebernyh_kanalov_ot_staniny_do_koguha_ventilatora")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(12,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "Ugol_natekania_potoka_na_rebra_staniny")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(13,2)->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "Ugol_povorota_potoka_v_megrebernych_kanalah")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            ui->tableWidget_7->item(14,2)->setText(attribute_value);
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
    if (item30->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item30->text() == "Статика (статор)")
        {
            ui->widget_5->ui->tabWidget->show();
            ui->widget_5->ui->tabWidget->setCurrentIndex(1);

            //СЧИТЫВАНИЕ ИСХОДНЫХ ДАННЫХ

            base_tepl.Da1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(0,1)->text().toDouble();
            base_tepl.Ha1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(1,1)->text().toDouble();
            base_tepl.lambda_c1       = ui->widget_5->ui->widget_2->ui->tableWidget->item(2,1)->text().toDouble();
            base_tepl.L1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(3,1)->text().toDouble();
            base_tepl.delta_ct = ui->widget_5->ui->widget_2->ui->tableWidget->item(4,1)->text().toDouble();
            base_tepl.lambda_ct   = ui->widget_5->ui->widget_2->ui->tableWidget->item(5,1)->text().toDouble();
            base_tepl.lambda_i  = ui->widget_5->ui->widget_2->ui->tableWidget->item(6,1)->text().toDouble();
            base_tepl.delta_ai     = ui->widget_5->ui->widget_2->ui->tableWidget->item(7,1)->text().toDouble();
            base_tepl.Kc1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(8,1)->text().toDouble();
            base_tepl.Di1   = ui->widget_5->ui->widget_2->ui->tableWidget->item(9,1)->text().toDouble();

            base_tepl.Z1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(10,1)->text().toDouble();
            base_tepl.Bz1       = ui->widget_5->ui->widget_2->ui->tableWidget->item(11,1)->text().toDouble();
            base_tepl.lambda_с     = ui->widget_5->ui->widget_2->ui->tableWidget->item(12,1)->text().toDouble();
            base_tepl.Hz1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(13,1)->text().toDouble();
            base_tepl.lambda_ip1    = ui->widget_5->ui->widget_2->ui->tableWidget->item(14,1)->text().toDouble();
            base_tepl.delta_ip1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(15,1)->text().toDouble();
            base_tepl.d1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(16,1)->text().toDouble();
            base_tepl.Kz     = ui->widget_5->ui->widget_2->ui->tableWidget->item(17,1)->text().toDouble();
            //base_tepl.delta     = ui->widget_5->ui->widget_2->ui->tableWidget->item(18,1)->text().toDouble();
            //base_tepl.lambda_ekv   = ui->widget_5->ui->widget_2->ui->tableWidget->item(19,1)->text().toDouble();

            base_tepl.Bp   = ui->widget_5->ui->widget_2->ui->tableWidget->item(20,1)->text().toDouble();
            base_tepl.sigma_ipr    = ui->widget_5->ui->widget_2->ui->tableWidget->item(21,1)->text().toDouble();
            base_tepl.teta_m     = ui->widget_5->ui->widget_2->ui->tableWidget->item(22,1)->text().toDouble();
            base_tepl.Kp     = ui->widget_5->ui->widget_2->ui->tableWidget->item(23,1)->text().toDouble();
            //base_tepl.Kp2       = ui->widget_5->ui->widget_2->ui->tableWidget->item(24,1)->text().toDouble();
            //base_tepl.d12    = ui->widget_5->ui->widget_2->ui->tableWidget->item(25,1)->text().toDouble();
            base_tepl.lambda_l    = ui->widget_5->ui->widget_2->ui->tableWidget->item(26,1)->text().toDouble();
            base_tepl.lambda_em     = ui->widget_5->ui->widget_2->ui->tableWidget->item(27,1)->text().toDouble();
            base_tepl.sigma_i = ui->widget_5->ui->widget_2->ui->tableWidget->item(28,1)->text().toDouble();
            base_tepl.lambda_ek  = ui->widget_5->ui->widget_2->ui->tableWidget->item(29,1)->text().toDouble();

            //base_tepl.lambda_c   = ui->widget_5->ui->widget_2->ui->tableWidget->item(30,1)->text().toDouble();
            base_tepl.lambda_mi     = ui->widget_5->ui->widget_2->ui->tableWidget->item(31,1)->text().toDouble();
            base_tepl.q_mi     = ui->widget_5->ui->widget_2->ui->tableWidget->item(32,1)->text().toDouble();
           // base_tepl.z_i     = ui->widget_5->ui->widget_2->ui->tableWidget->item(33,1)->text().toDouble();
            base_tepl.Lp1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(34,1)->text().toDouble();
            base_tepl.lambda_il     = ui->widget_5->ui->widget_2->ui->tableWidget->item(35,1)->text().toDouble();
            base_tepl.K_l1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(36,1)->text().toDouble();
            base_tepl.delta_il1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(37,1)->text().toDouble();
            base_tepl.lambda_ekuz     = ui->widget_5->ui->widget_2->ui->tableWidget->item(38,1)->text().toDouble();
            base_tepl.lambda_ekpa      = ui->widget_5->ui->widget_2->ui->tableWidget->item(39,1)->text().toDouble();

            //base_tepl.L_li    = ui->widget_5->ui->widget_2->ui->tableWidget->item(40,1)->text().toDouble();
           // base_tepl.alpha_l1    = ui->widget_5->ui->widget_2->ui->tableWidget->item(41,1)->text().toDouble();
            base_tepl.lambda_m2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(42,1)->text().toDouble();
            base_tepl.qc    = ui->widget_5->ui->widget_2->ui->tableWidget->item(43,1)->text().toDouble();
            base_tepl.Z2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(44,1)->text().toDouble();
            base_tepl.L2  = ui->widget_5->ui->widget_2->ui->tableWidget->item(45,1)->text().toDouble();
            base_tepl.Bk    = ui->widget_5->ui->widget_2->ui->tableWidget->item(46,1)->text().toDouble();
            //base_tepl.alpha_а2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(47,1)->text().toDouble();
            base_tepl.S_l2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(48,1)->text().toDouble();
           // base_tepl.alpha_asch      = ui->widget_5->ui->widget_2->ui->tableWidget->item(49,1)->text().toDouble();

            base_tepl.S_isch    = ui->widget_5->ui->widget_2->ui->tableWidget->item(50,1)->text().toDouble();
           // base_tepl.alpha_ast    = ui->widget_5->ui->widget_2->ui->tableWidget->item(51,1)->text().toDouble();
            base_tepl.S_ist    = ui->widget_5->ui->widget_2->ui->tableWidget->item(52,1)->text().toDouble();
            base_tepl.alpha_st    = ui->widget_5->ui->widget_2->ui->tableWidget->item(53,1)->text().toDouble();
            base_tepl.alpha_r    = ui->widget_5->ui->widget_2->ui->tableWidget->item(54,1)->text().toDouble();
            base_tepl.D_ct  = ui->widget_5->ui->widget_2->ui->tableWidget->item(55,1)->text().toDouble();
            //base_tepl.Krp    = ui->widget_5->ui->widget_2->ui->tableWidget->item(56,1)->text().toDouble();
            base_tepl.Hp    = ui->widget_5->ui->widget_2->ui->tableWidget->item(57,1)->text().toDouble();
            base_tepl.tp    = ui->widget_5->ui->widget_2->ui->tableWidget->item(58,1)->text().toDouble();
            base_tepl.alpha_c   = ui->widget_5->ui->widget_2->ui->tableWidget->item(59,1)->text().toDouble();

            base_tepl.delta_Kp  = ui->widget_5->ui->widget_2->ui->tableWidget->item(60,1)->text().toDouble();
            base_tepl.Dp1  = ui->widget_5->ui->widget_2->ui->tableWidget->item(61,1)->text().toDouble();
           // base_tepl.lb_ip   = ui->widget_5->ui->widget_2->ui->tableWidget->item(63,1)->text().toDouble();
           // base_tepl.sig_vp  = ui->widget_5->ui->widget_2->ui->tableWidget->item(64,1)->text().toDouble();
           // base_tepl.h_z2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(65,1)->text().toDouble();
           // base_tepl.b_z2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(66,1)->text().toDouble();
           // base_tepl.D_dp    = ui->widget_5->ui->widget_2->ui->tableWidget->item(67,1)->text().toDouble();
           // base_tepl.d       = ui->widget_5->ui->widget_2->ui->tableWidget->item(68,1)->text().toDouble();
           // base_tepl.d1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(69,1)->text().toDouble();

           // base_tepl.P2      = ui->widget_5->ui->widget_2->ui->tableWidget->item(70,1)->text().toDouble();
           // base_tepl.U1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(71,1)->text().toDouble();
           // base_tepl.n_u     = ui->widget_5->ui->widget_2->ui->tableWidget->item(72,1)->text().toDouble();
           // base_tepl.cos_f   = ui->widget_5->ui->widget_2->ui->tableWidget->item(73,1)->text().toDouble();
           // base_tepl.ro_al   = ui->widget_5->ui->widget_2->ui->tableWidget->item(74,1)->text().toDouble();
           // base_tepl.D_kzk   = ui->widget_5->ui->widget_2->ui->tableWidget->item(75,1)->text().toDouble();

            //ui->widget_5->ui->tableWidget->clearContents();

            //РАСЧЕТ ДАННЫХ

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
            teta_2=gsl_vector_get(x, 0);
            teta_3=gsl_vector_get(x, 1);
            teta_4=gsl_vector_get(x, 2);
            teta_c=gsl_vector_get(x, 3);
            teta_p=gsl_vector_get(x, 0);
            teta_z=gsl_vector_get(x, 1);
            teta_pp=gsl_vector_get(x, 2);
            teta_l_1=gsl_vector_get(x, 3);
            teta_l_2=gsl_vector_get(x, 0);

            gsl_permutation_free (p);
            gsl_vector_free (x);

            //Расчет температур
            teta_p=20;
            teta_z=50;
            teta_3=70;
            teta_c=76;
            teta_l_1=120;
            teta_pp=80;
            teta_l_2=120;
            teta_2=60;
            teta_4=40;

            //Вывод температур в таблицу
            ui->widget_5->ui->tableWidget->item(0,0)->setText("Температура_1, °C");
            ui->widget_5->ui->tableWidget->item(1,0)->setText("Температура_2, °C");
            ui->widget_5->ui->tableWidget->item(2,0)->setText("Температура_3, °C");
            ui->widget_5->ui->tableWidget->item(3,0)->setText("Температура_4, °C");
            ui->widget_5->ui->tableWidget->item(4,0)->setText("Температура_5, °C");
            ui->widget_5->ui->tableWidget->item(5,0)->setText("Температура_6, °C");
            ui->widget_5->ui->tableWidget->item(6,0)->setText("Температура_7, °C");
            ui->widget_5->ui->tableWidget->item(7,0)->setText("Температура_8, °C");
            ui->widget_5->ui->tableWidget->item(8,0)->setText("Температура_9, °C");

            ui->widget_5->ui->tableWidget->item(0,1)->setText(QString::number(teta_p,'f',3));
            ui->widget_5->ui->tableWidget->item(1,1)->setText(QString::number(teta_z,'f',3));
            ui->widget_5->ui->tableWidget->item(2,1)->setText(QString::number(teta_3,'f',3));
            ui->widget_5->ui->tableWidget->item(3,1)->setText(QString::number(teta_c,'f',3));
            ui->widget_5->ui->tableWidget->item(4,1)->setText(QString::number(teta_l_1,'f',3));
            ui->widget_5->ui->tableWidget->item(5,1)->setText(QString::number(teta_pp,'f',3));
            ui->widget_5->ui->tableWidget->item(6,1)->setText(QString::number(teta_l_2,'f',3));
            ui->widget_5->ui->tableWidget->item(7,1)->setText(QString::number(teta_2,'f',3));
            ui->widget_5->ui->tableWidget->item(8,1)->setText(QString::number(teta_4,'f',3));

            //Расчет тепловых проводимостей
            lambda_zp=0.034;
            lambda_zc=0.35;
            lambda_c3=0.23;
            lambda_pc=0.021;
            lambda_pz=0.034;
            lambda_l22=0.067;
            lambda_l14=0.067;
            lambda_pl1=0.67;
            lambda_pl2=0.56;

            //Вывод тепловых проводимостей в таблицу
            ui->widget_5->ui->tableWidget->item(0,2)->setText("Теплопроводность_1, Вт/°C");
            ui->widget_5->ui->tableWidget->item(1,2)->setText("Теплопроводность_2, Вт/°C");
            ui->widget_5->ui->tableWidget->item(2,2)->setText("Теплопроводность_3, Вт/°C");
            ui->widget_5->ui->tableWidget->item(3,2)->setText("Теплопроводность_4, Вт/°C");
            ui->widget_5->ui->tableWidget->item(4,2)->setText("Теплопроводность_5, Вт/°C");
            ui->widget_5->ui->tableWidget->item(5,2)->setText("Теплопроводность_6, Вт/°C");
            ui->widget_5->ui->tableWidget->item(6,2)->setText("Теплопроводность_7, Вт/°C");
            ui->widget_5->ui->tableWidget->item(7,2)->setText("Теплопроводность_8, Вт/°C");
            ui->widget_5->ui->tableWidget->item(8,2)->setText("Теплопроводность_9, Вт/°C");

            ui->widget_5->ui->tableWidget->item(0,3)->setText(QString::number(lambda_zp,'f',3));
            ui->widget_5->ui->tableWidget->item(1,3)->setText(QString::number(lambda_zc,'f',3));
            ui->widget_5->ui->tableWidget->item(2,3)->setText(QString::number(lambda_c3,'f',3));
            ui->widget_5->ui->tableWidget->item(3,3)->setText(QString::number(lambda_pc,'f',3));
            ui->widget_5->ui->tableWidget->item(4,3)->setText(QString::number(lambda_pz,'f',3));
            ui->widget_5->ui->tableWidget->item(5,3)->setText(QString::number(lambda_l22,'f',3));
            ui->widget_5->ui->tableWidget->item(6,3)->setText(QString::number(lambda_l14,'f',3));
            ui->widget_5->ui->tableWidget->item(7,3)->setText(QString::number(lambda_pl1,'f',3));
            ui->widget_5->ui->tableWidget->item(8,3)->setText(QString::number(lambda_pl2,'f',3));

            //Расчет мощности рассеяния
            P_p=20;
            P_z=100;
            P_3=120;
            P_c=502;
            P_l_1=67;
            P_pp=76;
            P_l_2=120;
            P_2=56;
            P_4=59;

            //Вывод мощностей рассеяния в таблицу
            ui->widget_5->ui->tableWidget->item(0,4)->setText("Мощность_рассеяния_1, Вт");
            ui->widget_5->ui->tableWidget->item(1,4)->setText("Мощность_рассеяния_2, Вт");
            ui->widget_5->ui->tableWidget->item(2,4)->setText("Мощность_рассеяния_3, Вт");
            ui->widget_5->ui->tableWidget->item(3,4)->setText("Мощность_рассеяния_4, Вт");
            ui->widget_5->ui->tableWidget->item(4,4)->setText("Мощность_рассеяния_5, Вт");
            ui->widget_5->ui->tableWidget->item(5,4)->setText("Мощность_рассеяния_6, Вт");
            ui->widget_5->ui->tableWidget->item(6,4)->setText("Мощность_рассеяния_7, Вт");
            ui->widget_5->ui->tableWidget->item(7,4)->setText("Мощность_рассеяния_8, Вт");
            ui->widget_5->ui->tableWidget->item(8,4)->setText("Мощность_рассеяния_9, Вт");

            ui->widget_5->ui->tableWidget->item(0,5)->setText(QString::number(P_p,'f',3));
            ui->widget_5->ui->tableWidget->item(1,5)->setText(QString::number(P_z,'f',3));
            ui->widget_5->ui->tableWidget->item(2,5)->setText(QString::number(P_3,'f',3));
            ui->widget_5->ui->tableWidget->item(3,5)->setText(QString::number(P_c,'f',3));
            ui->widget_5->ui->tableWidget->item(4,5)->setText(QString::number(P_l_1,'f',3));
            ui->widget_5->ui->tableWidget->item(5,5)->setText(QString::number(P_pp,'f',3));
            ui->widget_5->ui->tableWidget->item(6,5)->setText(QString::number(P_l_2,'f',3));
            ui->widget_5->ui->tableWidget->item(7,5)->setText(QString::number(P_2,'f',3));
            ui->widget_5->ui->tableWidget->item(8,5)->setText(QString::number(P_4,'f',3));

            //Расчет топлоемкостей
            C_p=0.034;
            C_z=0.35;
            C_3=0.23;
            C_c=0.034;
            C_l_1=0.067;
            C_pp=0.067;
            C_l_2=0.67;
            C_2=0.56;
            C_4=0.059;

            //Вывод тоеплоемкостей в таблицу
            ui->widget_5->ui->tableWidget->item(0,6)->setText("Теплоемкость_1, Дж/К");
            ui->widget_5->ui->tableWidget->item(1,6)->setText("Теплоемкость_2, Дж/К");
            ui->widget_5->ui->tableWidget->item(2,6)->setText("Теплоемкость_3, Дж/К");
            ui->widget_5->ui->tableWidget->item(3,6)->setText("Теплоемкость_4, Дж/К");
            ui->widget_5->ui->tableWidget->item(4,6)->setText("Теплоемкость_5, Дж/К");
            ui->widget_5->ui->tableWidget->item(5,6)->setText("Теплоемкость_6, Дж/К");
            ui->widget_5->ui->tableWidget->item(6,6)->setText("Теплоемкость_7, Дж/К");
            ui->widget_5->ui->tableWidget->item(7,6)->setText("Теплоемкость_8, Дж/К");
            ui->widget_5->ui->tableWidget->item(8,6)->setText("Теплоемкость_9, Дж/К");

            ui->widget_5->ui->tableWidget->item(0,7)->setText(QString::number(C_p,'f',3));
            ui->widget_5->ui->tableWidget->item(1,7)->setText(QString::number(C_z,'f',3));
            ui->widget_5->ui->tableWidget->item(2,7)->setText(QString::number(C_3,'f',3));
            ui->widget_5->ui->tableWidget->item(3,7)->setText(QString::number(C_c,'f',3));
            ui->widget_5->ui->tableWidget->item(4,7)->setText(QString::number(C_l_1,'f',3));
            ui->widget_5->ui->tableWidget->item(5,7)->setText(QString::number(C_pp,'f',3));
            ui->widget_5->ui->tableWidget->item(6,7)->setText(QString::number(C_l_2,'f',3));
            ui->widget_5->ui->tableWidget->item(7,7)->setText(QString::number(C_2,'f',3));
            ui->widget_5->ui->tableWidget->item(8,7)->setText(QString::number(C_4,'f',3));

            //Расчет мощностей рассеяния
            dP_zp=100;
            dP_zc=220;
            dP_c3=230;
            dP_pс=450;
            dP_pz=120;
            dP_l22=340;
            dP_l14=560;
            dP_pl1=506;
            dP_pl2=760;

            //Вывод мощностей рассеяния в таблицу
            ui->widget_5->ui->tableWidget->item(0,8)->setText("Мощность_рассеяния_1, Вт");
            ui->widget_5->ui->tableWidget->item(1,8)->setText("Мощность_рассеяния_2, Вт");
            ui->widget_5->ui->tableWidget->item(2,8)->setText("Мощность_рассеяния_3, Вт");
            ui->widget_5->ui->tableWidget->item(3,8)->setText("Мощность_рассеяния_4, Вт");
            ui->widget_5->ui->tableWidget->item(4,8)->setText("Мощность_рассеяния_5, Вт");
            ui->widget_5->ui->tableWidget->item(5,8)->setText("Мощность_рассеяния_6, Вт");
            ui->widget_5->ui->tableWidget->item(6,8)->setText("Мощность_рассеяния_7, Вт");
            ui->widget_5->ui->tableWidget->item(7,8)->setText("Мощность_рассеяния_8, Вт");
            ui->widget_5->ui->tableWidget->item(8,8)->setText("Мощность_рассеяния_9, Вт");

            ui->widget_5->ui->tableWidget->item(0,9)->setText(QString::number(dP_zp,'f',3));
            ui->widget_5->ui->tableWidget->item(1,9)->setText(QString::number(dP_zc,'f',3));
            ui->widget_5->ui->tableWidget->item(2,9)->setText(QString::number(dP_c3,'f',3));
            ui->widget_5->ui->tableWidget->item(3,9)->setText(QString::number(dP_pс,'f',3));
            ui->widget_5->ui->tableWidget->item(4,9)->setText(QString::number(dP_pz,'f',3));
            ui->widget_5->ui->tableWidget->item(5,9)->setText(QString::number(dP_l22,'f',3));
            ui->widget_5->ui->tableWidget->item(6,9)->setText(QString::number(dP_l14,'f',3));
            ui->widget_5->ui->tableWidget->item(7,9)->setText(QString::number(dP_pl1,'f',3));
            ui->widget_5->ui->tableWidget->item(8,9)->setText(QString::number(dP_pl2,'f',3));

            //Расчет превышений температуры
            d_teta_zp=10;
            d_teta_zc=5;
            d_teta_c3=20;
            d_teta_pc=30;
            d_teta_pz=15;
            d_teta_l22=10;
            d_teta_l14=5;
            d_teta_pl1=35;
            d_teta_pl2=35;

            //Вывод превышений температуры в таблицу
            ui->widget_5->ui->tableWidget->item(0,10)->setText("Температура_1, °C");
            ui->widget_5->ui->tableWidget->item(1,10)->setText("Температура_2, °C");
            ui->widget_5->ui->tableWidget->item(2,10)->setText("Температура_3, °C");
            ui->widget_5->ui->tableWidget->item(3,10)->setText("Температура_4, °C");
            ui->widget_5->ui->tableWidget->item(4,10)->setText("Температура_5, °C");
            ui->widget_5->ui->tableWidget->item(5,10)->setText("Температура_6, °C");
            ui->widget_5->ui->tableWidget->item(6,10)->setText("Температура_7, °C");
            ui->widget_5->ui->tableWidget->item(7,10)->setText("Температура_8, °C");
            ui->widget_5->ui->tableWidget->item(8,10)->setText("Температура_9, °C");

            ui->widget_5->ui->tableWidget->item(0,11)->setText(QString::number(d_teta_zp,'f',3));
            ui->widget_5->ui->tableWidget->item(1,11)->setText(QString::number(d_teta_zc,'f',3));
            ui->widget_5->ui->tableWidget->item(2,11)->setText(QString::number(d_teta_c3,'f',3));
            ui->widget_5->ui->tableWidget->item(3,11)->setText(QString::number(d_teta_pc,'f',3));
            ui->widget_5->ui->tableWidget->item(4,11)->setText(QString::number(d_teta_pz,'f',3));
            ui->widget_5->ui->tableWidget->item(5,11)->setText(QString::number(d_teta_l22,'f',3));
            ui->widget_5->ui->tableWidget->item(6,11)->setText(QString::number(d_teta_l14,'f',3));
            ui->widget_5->ui->tableWidget->item(7,11)->setText(QString::number(d_teta_pl1,'f',3));
            ui->widget_5->ui->tableWidget->item(8,11)->setText(QString::number(d_teta_pl2,'f',3));
        }
        if (item30->text() == "Статика (упрощенный вариант)")
        {
            ui->widget_5->ui->tabWidget->show();
            ui->widget_5->ui->tabWidget->setCurrentIndex(1);
            //ввод данных
            base_tepl.Da1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(0,1)->text().toDouble();
            base_tepl.Ha1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(1,1)->text().toDouble();
            base_tepl.lambda_c1       = ui->widget_5->ui->widget_2->ui->tableWidget->item(2,1)->text().toDouble();
            base_tepl.L1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(3,1)->text().toDouble();
            base_tepl.delta_ct = ui->widget_5->ui->widget_2->ui->tableWidget->item(4,1)->text().toDouble();
            base_tepl.lambda_ct   = ui->widget_5->ui->widget_2->ui->tableWidget->item(5,1)->text().toDouble();
            base_tepl.lambda_i  = ui->widget_5->ui->widget_2->ui->tableWidget->item(6,1)->text().toDouble();
            base_tepl.delta_ai     = ui->widget_5->ui->widget_2->ui->tableWidget->item(7,1)->text().toDouble();
            base_tepl.Kc1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(8,1)->text().toDouble();
            base_tepl.Di1   = ui->widget_5->ui->widget_2->ui->tableWidget->item(9,1)->text().toDouble();

            base_tepl.Z1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(10,1)->text().toDouble();
            base_tepl.Bz1       = ui->widget_5->ui->widget_2->ui->tableWidget->item(11,1)->text().toDouble();
            base_tepl.lambda_с     = ui->widget_5->ui->widget_2->ui->tableWidget->item(12,1)->text().toDouble();
            base_tepl.Hz1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(13,1)->text().toDouble();
            base_tepl.lambda_ip1    = ui->widget_5->ui->widget_2->ui->tableWidget->item(14,1)->text().toDouble();
            base_tepl.delta_ip1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(15,1)->text().toDouble();
            base_tepl.Kz      = ui->widget_5->ui->widget_2->ui->tableWidget->item(16,1)->text().toDouble();
            base_tepl.d1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(17,1)->text().toDouble();
            base_tepl.teta_m     = ui->widget_5->ui->widget_2->ui->tableWidget->item(18,1)->text().toDouble();
            base_tepl.Kp   = ui->widget_5->ui->widget_2->ui->tableWidget->item(19,1)->text().toDouble();

            base_tepl.lambda_l   = ui->widget_5->ui->widget_2->ui->tableWidget->item(20,1)->text().toDouble();
            base_tepl.lambda_em    = ui->widget_5->ui->widget_2->ui->tableWidget->item(21,1)->text().toDouble();
            base_tepl.Bp     = ui->widget_5->ui->widget_2->ui->tableWidget->item(22,1)->text().toDouble();
            base_tepl.sigma_ipr     = ui->widget_5->ui->widget_2->ui->tableWidget->item(23,1)->text().toDouble();
            base_tepl.sigma_i       = ui->widget_5->ui->widget_2->ui->tableWidget->item(24,1)->text().toDouble();
            base_tepl.lambda_ek    = ui->widget_5->ui->widget_2->ui->tableWidget->item(25,1)->text().toDouble();
            base_tepl.lambda_mi    = ui->widget_5->ui->widget_2->ui->tableWidget->item(26,1)->text().toDouble();
            base_tepl.q_mi     = ui->widget_5->ui->widget_2->ui->tableWidget->item(27,1)->text().toDouble();
            base_tepl.Lp1 = ui->widget_5->ui->widget_2->ui->tableWidget->item(28,1)->text().toDouble();
            base_tepl.Lambda_el  = ui->widget_5->ui->widget_2->ui->tableWidget->item(29,1)->text().toDouble();

            base_tepl.lambda_ekuz   = ui->widget_5->ui->widget_2->ui->tableWidget->item(30,1)->text().toDouble();
            base_tepl.lambda_ekpa     = ui->widget_5->ui->widget_2->ui->tableWidget->item(31,1)->text().toDouble();
            base_tepl.n     = ui->widget_5->ui->widget_2->ui->tableWidget->item(32,1)->text().toDouble();
            base_tepl.Dv1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(33,1)->text().toDouble();
            base_tepl.nu     = ui->widget_5->ui->widget_2->ui->tableWidget->item(34,1)->text().toDouble();
            base_tepl.K_l1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(35,1)->text().toDouble();
            base_tepl.lambda_il     = ui->widget_5->ui->widget_2->ui->tableWidget->item(36,1)->text().toDouble();
            base_tepl.delta_il1     = ui->widget_5->ui->widget_2->ui->tableWidget->item(37,1)->text().toDouble();
            base_tepl.lambda_m2     = ui->widget_5->ui->widget_2->ui->tableWidget->item(38,1)->text().toDouble();
            base_tepl.qc      = ui->widget_5->ui->widget_2->ui->tableWidget->item(39,1)->text().toDouble();

            base_tepl.L2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(40,1)->text().toDouble();
            base_tepl.Bk    = ui->widget_5->ui->widget_2->ui->tableWidget->item(41,1)->text().toDouble();
            base_tepl.Z2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(42,1)->text().toDouble();
            base_tepl.u_rot    = ui->widget_5->ui->widget_2->ui->tableWidget->item(43,1)->text().toDouble();
            base_tepl.Dl    = ui->widget_5->ui->widget_2->ui->tableWidget->item(44,1)->text().toDouble();
            base_tepl.S_l2  = ui->widget_5->ui->widget_2->ui->tableWidget->item(45,1)->text().toDouble();
            base_tepl.S_isch    = ui->widget_5->ui->widget_2->ui->tableWidget->item(46,1)->text().toDouble();
            base_tepl.S_ist    = ui->widget_5->ui->widget_2->ui->tableWidget->item(47,1)->text().toDouble();
            base_tepl.alpha_r    = ui->widget_5->ui->widget_2->ui->tableWidget->item(48,1)->text().toDouble();

            base_tepl.alpha_st      = ui->widget_5->ui->widget_2->ui->tableWidget->item(49,1)->text().toDouble();
            base_tepl.h_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(50,1)->text().toDouble();
            base_tepl.t_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(51,1)->text().toDouble();
            base_tepl.n_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(52,1)->text().toDouble();
            base_tepl.a_p    = ui->widget_5->ui->widget_2->ui->tableWidget->item(53,1)->text().toDouble();
            base_tepl.D_ct    = ui->widget_5->ui->widget_2->ui->tableWidget->item(54,1)->text().toDouble();
            base_tepl.u2  = ui->widget_5->ui->widget_2->ui->tableWidget->item(55,1)->text().toDouble();
            //base_tepl.Krp    = ui->widget_5->ui->widget_2->ui->tableWidget->item(56,1)->text().toDouble();
            //base_tepl.Hp    = ui->widget_5->ui->widget_2->ui->tableWidget->item(57,1)->text().toDouble();
           // base_tepl.tp    = ui->widget_5->ui->widget_2->ui->tableWidget->item(58,1)->text().toDouble();

            base_tepl.alpha_c   = ui->widget_5->ui->widget_2->ui->tableWidget->item(59,1)->text().toDouble();
            base_tepl.delta_Kp  = ui->widget_5->ui->widget_2->ui->tableWidget->item(60,1)->text().toDouble();
            base_tepl.Dp1  = ui->widget_5->ui->widget_2->ui->tableWidget->item(61,1)->text().toDouble();
            base_tepl.lambda_v   = ui->widget_5->ui->widget_2->ui->tableWidget->item(62,1)->text().toDouble();
           // base_tepl.sig_vp  = ui->widget_5->ui->widget_2->ui->tableWidget->item(64,1)->text().toDouble();
           // base_tepl.h_z2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(65,1)->text().toDouble();
           // base_tepl.b_z2    = ui->widget_5->ui->widget_2->ui->tableWidget->item(66,1)->text().toDouble();
           // base_tepl.D_dp    = ui->widget_5->ui->widget_2->ui->tableWidget->item(67,1)->text().toDouble();
           // base_tepl.d       = ui->widget_5->ui->widget_2->ui->tableWidget->item(68,1)->text().toDouble();
           // base_tepl.d1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(69,1)->text().toDouble();

           // base_tepl.P2      = ui->widget_5->ui->widget_2->ui->tableWidget->item(70,1)->text().toDouble();
           // base_tepl.U1      = ui->widget_5->ui->widget_2->ui->tableWidget->item(71,1)->text().toDouble();
           // base_tepl.n_u     = ui->widget_5->ui->widget_2->ui->tableWidget->item(72,1)->text().toDouble();
           // base_tepl.cos_f   = ui->widget_5->ui->widget_2->ui->tableWidget->item(73,1)->text().toDouble();
           // base_tepl.ro_al   = ui->widget_5->ui->widget_2->ui->tableWidget->item(74,1)->text().toDouble();
           // base_tepl.D_kzk   = ui->widget_5->ui->widget_2->ui->tableWidget->item(75,1)->text().toDouble();


            //Расчет тепловых проводимостей



//            1+Da1 – внешний диаметр сердечника статора, м;
//            2+ha1 – высота оси вращения, м;
//            3+lambda_c1 – коэффициент теплопроводности стали сердечника;
//            4+L1 – длина сердечника статора, м;
//            5+k(c1) – коэффициент заполнения сердечника сталью;
            //6            +lambda(i) – коэффициент теплопроводности воздуха;
//            7+delta(ai) – контактный зазор между сердечником статора и станиной, м;
//            8+delta(ст) – толщина станины, м;
//            9+lambda(ст) – коэффициент проводимости материала станины;
//            10+Di1- внутренний диаметр сердечника статора, м;
//            11+alpha(sigma) – коэффициент теплоотдачи в воздушном зазоре;
//            12+z1 – число зубцов статора;
//            13+bz1 – ширина паза статора, м;
//            14+lambda(с) – ddd
//            15+Hz1 – высота зубца статора, м;
//            16+lambda(ип1) – коэффициент теплопроводности пазовой изоляции;
//            17+delta(ип1) – толщина пазовой изоляции;
//            18+d’ – диаметр провода, м;
//            19+sigma(ипр) – толщина изоляции провода, м;
//            20+lambda(экв) – эквивалентный	 коэффициент теплопроводности обмотки;
//            21+Кз – коэффициент заполнения паза;
//            22+delta - fff
            //23+Bp - fff
            //24+teta(м) – допускаемая температура обмотки статора для данного класса нагревостойкости пазовой изоляции;
//            25+Kп -коэффициент пропитки;
            //26+Kp2 - fff;
            //27+d12 - fff;
//            28+lambda(л) – коэффициент теплопроводности пропиточного лака;
//            29+lambda(эм) - коэффициент теплопроводности изоляции обмоточного провода;
//            30+sigma(i) - ddd;
//            31+lambda(i) – коэффициент теплопроводности воздуха;
//            32+Bz1- средняя ширина зубца статора;
//            33+Bп1 – средняя ширина паза, м;
            //34+lambda_ek - fdff;
            //35+lambda_c - dd;
//            36+q(mi) – суммарное сечение проводников в пазу статора;
//            37+lambda(mi) – коэффициент теплопроводности материала обмотки статора;
            //38+z_i - ddd;
            //39+Lp1 - fff;
//            40+lambda(ил1) – коэффициент теплопроводности лобовых частей;
//            41+delta(ил1) – толщина изоляции лобовых частей;
//            42+Kл1 – коэффициент обдува лобовых частей;
            //43+lambda_ekuz - fff;
            //44+lambda_ekpa - fff;
            //45+L_li - fff;
//            46+alpha(л1) – средний коэффициент теплоотдачи с лобовых частей;
//            47+qc – сечение стержня клетки ротора;
            //48+Z2 - dcdd;
            //49+L2 - fff;
//            50+lambda(м2) – коэффициент теплопроводности материала обмотки;
            //51+Bk - fff;
//            52Br – ширина короткозамыкающего кольца;
//            53+alpha(а2) – коэффициент теплоотдачи с поверхности лобовых частей обмотки ротора;
//            54+S(л2) – поверхность двух лобовых частей обмотки ротора;
//            55+alpha(ащ) – средний коэффициент теплоотдачи с внутренней поверхности подшипникового щита;
//            56+alpha(аст) – средний коэффициент теплоотдачи с внутренней поверхности станины;
//            57+S(iщ) – площадь внутренней поверхности двух подшипниковых щитов;
//            58+S(iст) – площадь внутренней поверхности станины;
//            59+Dст – наружный диаметр станины;
//            60Kpп – коэффициент оребрения станины с учетом внутреннего теплового сопротивления ребер;
//            61+alpha(ст) – коэффициент конвективной теплоотдачи станины;
//            62+alpha(r) – коэффициент теплоотдачи излучением;
//            63alpha(стсумм) – суммарный коэффициент теплоотдачи станины;
//            64Bp – средняя толщина ребра;
//            65deltaKp – коэффициент, определяющий долю неоребренных участков от всей теплоотражающей поверхности;



            double Lambda_ct,Lambda_adelta1,Lambda_a1,Lambda_delta1,Lambda_sigma,Lambda_1z1,Lambda_12,Lambda_1ip1,
                    delta,Lambda_epz,Lambda_ekv,Lambda_i1z,Lambda_z,Lambda_nz,Lambda_i1a,Lambda_ekpa,
                    Lambda_2ip1,Lambda_a,Lambda_na,Lambda_za,Lambda_pl,Lambda_il,Lambda_el,Lambda_al1,Lambda_l1,
                    Lambda_lp2,Lambda_a2,Lambda_l2,Lambda_asch,Lambda_ast,Lambda_ai,alpha_stsumm,Lambda_ct1,ro_t,Krp1,Lambda_p,
                    alpha_sigma,Lambda_sch;
            double Re1,wl,dek,Nu1,alpha_l1,Re2,Nu2,alpha_а2,wr,alpha_asch,alpha_ast,k_p,delta_Kp,alpha_1sch,alpha_2sch;



            //+Тепловая проводимость станины
            Lambda_ct = (M_PI*(base_tepl.Da1 + base_tepl.delta_ct) * base_tepl.L1 * base_tepl.lambda_ct) / (base_tepl.delta_ct);

            //+Тепловая проводимость зазора между сердечником статора и станиной
            Lambda_adelta1 = (M_PI * base_tepl.Da1 * base_tepl.L1 * base_tepl.lambda_i)/base_tepl.delta_ai;

            //+Тепловая проводимость спинки статора
            Lambda_a1 = M_PI * base_tepl.L1 * base_tepl.lambda_c1 * base_tepl.Kc1 * (2 * base_tepl.Da1 - base_tepl.Ha1) / base_tepl.Ha1;

            //+Общая тепловая проводимость между сердечником статора и станиной
            Lambda_delta1 = 1/((1/ Lambda_a1)+(1/ Lambda_adelta1)+(1/ Lambda_ct));

            //+Коэффициент теплоотдачи от ротора к внутреннему воздуху
            alpha_sigma = (((2*base_tepl.delta_ai)/(base_tepl.Dp1/2))*(base_tepl.lambda_v/(2*base_tepl.delta_ai)))/
            log(1+(base_tepl.delta_ai/(base_tepl.Dp1/2)));

            //+Тепловая проводимость воздушного зазора:
            Lambda_sigma = (M_PI / 2) * (base_tepl.Di1 * base_tepl.L1 * alpha_sigma);

            //+Тепловая проводимость зубцов статора:
            Lambda_1z1 = (2 * base_tepl.Z1 * base_tepl.Bz1 * base_tepl.L1 * base_tepl.Kc1 * base_tepl.lambda_c1) / base_tepl.Hz1;

            //+Общая тепловая проводимость между статором и ротором
            Lambda_12 = (Lambda_sigma * Lambda_1z1)/( Lambda_sigma + Lambda_1z1);

            //+Тепловая проводимость пазовой изоляции
            Lambda_1ip1 = (2 * base_tepl.Hz1 * base_tepl.Z1 * base_tepl.L1 * base_tepl.lambda_ip1)/base_tepl.delta_ip1;

            //+Воздушный зазор между проводами в пазе статора
            delta = base_tepl.d1 * (0.022 + 0.5 * (1 / sqrt(base_tepl.Kz) - 1));

            //+Эквивалентный коэффициент теплопроводности обмотки
            Lambda_ekv = 0.00165*(1 + 0.0007 * base_tepl.teta_m)*(1 - 3.2 * base_tepl.d1 * (1 - 9.2 * base_tepl.Kp + 5.2 *
            pow(base_tepl.Kp,2)) + 81 * pow(base_tepl.d1,2))*( 2.11 * pow(base_tepl.Kz,1.5) * 1.15 - 0.32)*pow((base_tepl.lambda_l / 0.00162 ),0.33) *
            pow((base_tepl.lambda_em/ 0.00143),0.25);

            //+Эквивалентная тепловая проводимость обмотки к зубцам
            Lambda_epz = ((base_tepl.d1 + delta) * Lambda_ekv * 2 * base_tepl.Hz1 * base_tepl.Z1 * base_tepl.L1)/
            ((base_tepl.Bp - 2 * base_tepl.delta_ip1) * (base_tepl.sigma_ipr + delta));

            //+Тепловая проводимость воздушного зазора между пазовой изоляцией и зубцами статора
            Lambda_i1z = (2 * base_tepl.Hz1 * base_tepl.L1 * base_tepl.Z1 * base_tepl.lambda_i)/base_tepl.sigma_i;

            //+Проводимость зубца статора в направлении теплового потока от пазовой части проводки
            Lambda_z = base_tepl.Bz1 / (base_tepl.Z1 * base_tepl.Hz1 * base_tepl.L1 * base_tepl.Kc1 * base_tepl.lambda_с);

            //+Общая тепловая проводимость между пазовой частью обмотки статора и зубцами
            Lambda_nz = 1/((1/Lambda_1ip1)+(1/Lambda_epz)+(1/Lambda_i1z)+(1/Lambda_z));

            //+Тепловая проводимость воздушного зазора между пазовой изоляцией и спинкой статора
            Lambda_i1a = (base_tepl.Bp * base_tepl.L1 * base_tepl.Z1 * base_tepl.lambda_i)/base_tepl.sigma_i;

            //+Эквивалентная тепловая проводимость обмотки к спинке
            Lambda_ekpa = ((base_tepl.d1 + delta) * base_tepl.lambda_ek * base_tepl.Bp * base_tepl.L1 * base_tepl.Z1) /
            ((base_tepl.Hz1 - 2 * base_tepl.delta_ip1) * (base_tepl.sigma_ipr + delta));

            //+Тепловая проводимость пазовой изоляции
            Lambda_2ip1 = (base_tepl.Z1 * base_tepl.Bp * base_tepl.L1 * base_tepl.lambda_ip1)/base_tepl.delta_ip1;

            //+Проводимость спинки статора в направлении теплового потока от пазовой части обмотки
            Lambda_a = base_tepl.Ha1/((0.5 * 3.14 * (base_tepl.Da1 - base_tepl.Ha1) + base_tepl.Z1 * base_tepl.Bp) *
            base_tepl.L1 * base_tepl.Kc1 * base_tepl.lambda_c1);

            //+Общая тепловая проводимость между пазовой частью обмотки и спинкой статора
            Lambda_na = 1/((1/Lambda_2ip1) + (1/Lambda_ekpa)+(1/Lambda_i1a)+(1/Lambda_a));

            //+Проводимость между зубцом и спинкой статора
            Lambda_za = base_tepl.L1 * base_tepl.Kc1 * base_tepl.lambda_c1/(base_tepl.Hz1/( 2 * base_tepl.Z1 * base_tepl.Bz1) +
            base_tepl.Ha1 / (2 * 3.14 * (base_tepl.Da1 - base_tepl.Ha1)));

            //+hТепловая проводимость между пазовой и лобовой частями обмотки статора
            Lambda_pl = 12 * base_tepl.lambda_mi * base_tepl.q_mi * base_tepl.Z1 / (base_tepl.L1 + base_tepl.Lp1);

            //+Тепловая проводимость изоляции
            Lambda_il= (base_tepl.lambda_il * 2 * (base_tepl.Hz1 + base_tepl.Bp) * base_tepl.L1 * base_tepl.Z1 *
            base_tepl.K_l1) / base_tepl.delta_il1;

            //+Эквивалентная тепловая проводимость лобовой части
            Lambda_el = (base_tepl.lambda_ekuz + base_tepl.lambda_ekpa) * base_tepl.Lp1 / base_tepl.L1;

            //+Тепловая проводимость лобовых частей
            wl = 0.022 *base_tepl.n * base_tepl.Dv1;
            dek = 4 * base_tepl.Bp * base_tepl.Hz1 /(2 * base_tepl.Bp + base_tepl.Hz1);
            Re1 = (wl * dek) / base_tepl.nu;
            Nu1 = 0.103 * pow(Re1,0.66);
            alpha_l1 = (Nu1 * base_tepl.lambda_v)/ base_tepl.Da1;
            Lambda_al1 = alpha_l1 * 2 * (base_tepl.Hz1 + base_tepl.Bp) * base_tepl.Lp1 * base_tepl.Z1 * base_tepl.K_l1;

            //+Полная тепловая проводимость лобовой части обмотки статора к окружающей среде
            Lambda_l1 = 1 / ((1 / Lambda_il) + (1 / Lambda_al1) + (1 / Lambda_el));

            //+Общая тепловая проводимость между лобовой и пазовой частями клетки статора
            Lambda_lp2 = (12 * base_tepl.lambda_m2 * base_tepl.qc * base_tepl.Z2)/(base_tepl.L2 + base_tepl.Bk);

            //+тепловая проводимость лобовых частей обмоток статора, обращенных к ротору
            Re2=(base_tepl.u_rot * base_tepl.Dl) / (2*base_tepl.nu);
            Nu2 = 0.456 * pow(Re2,0.6);
            alpha_а2 = (Nu2 * base_tepl.lambda_v)/ base_tepl.Dl;
            Lambda_a2 = alpha_а2 * base_tepl.S_l2;

            //+Общая тепловая проводимость лобовой части обмотки ротора к внутреннему воздуху
            Lambda_l2 = (Lambda_lp2 * Lambda_a2) / (Lambda_lp2 + Lambda_a2);

            //+Тепловая проводимость внутреннего воздуха к подшипниковым щитам
            wr = (3.14 * base_tepl.Dl * base_tepl.u_rot ) / 60;
            alpha_asch = 15 + 6.5 * pow(wr,0.7);
            Lambda_asch = alpha_asch * base_tepl.S_isch;

            //+Тепловая проводимость внутреннего воздуха к станине
            wr = (3.14 * base_tepl.Dl * base_tepl.u_rot ) / 60;
            alpha_ast = 4.58 * pow(wr,0.74);
            Lambda_ast = alpha_ast * base_tepl.S_ist;

            //+Общая тепловая проводимость внутреннего воздуха к оболочке двигателя
            Lambda_ai = Lambda_asch + Lambda_ast;

            //+суммарный коэффициент теплоотдачи станины
            alpha_stsumm = base_tepl.alpha_st + base_tepl.alpha_r;

            //Тепловая проводимость станины к окружающей среде
            k_p = base_tepl.h_p * (base_tepl.t_p / 3.14) * base_tepl.D_ct;
            delta_Kp = base_tepl.n_p * base_tepl.a_p / 3.14 * base_tepl.D_ct * k_p;
            ro_t  = sqrt((2 * base_tepl.alpha_st)/(base_tepl.lambda_ct * base_tepl.Bp));
            Krp1 = (1 / (ro_t * base_tepl.h_p)) * (tanh(ro_t * base_tepl.h_p) * (2 * base_tepl.h_p/ base_tepl.t_p) *
            (1-(base_tepl.alpha_r / alpha_stsumm)) + ro_t * base_tepl.h_p *delta_Kp);
            Lambda_ct1 = alpha_stsumm * 3.14 * base_tepl.D_ct * k_p * Krp1;

            //Параметр теплоотдачи
            alpha_1sch = 20 + 14.3 * pow((0.5 * base_tepl.u2),0.6);
            alpha_2sch = 20 + 2.6 * pow((0.5 * base_tepl.u2),0.9);
            Lambda_sch = 0.5 * ( alpha_1sch + alpha_2sch) * 3.14 * pow(base_tepl.D_ct,2);

            //Тепловая проводимость оболочки двигателя к окружающей среде
            Lambda_p = Lambda_ct1 + Lambda_sch;

            if (ui->tableWidget_9->item(0, 2) != 0)
            {
                ui->tableWidget_9->item(0, 2)->setText(QString::number(Lambda_ct,'f',3));
            }

            if (ui->tableWidget_9->item(1, 2) != 0)
            {
                ui->tableWidget_9->item(1, 2)->setText(QString::number(Lambda_adelta1,'f',3));
            }

            if (ui->tableWidget_9->item(2, 2) != 0)
            {
                ui->tableWidget_9->item(2, 2)->setText(QString::number(Lambda_a1,'f',3));
            }

            if (ui->tableWidget_9->item(3, 2) != 0)
            {
                ui->tableWidget_9->item(3, 2)->setText(QString::number(Lambda_delta1,'f',3));
            }

            if (ui->tableWidget_9->item(4, 2) != 0)
            {
                ui->tableWidget_9->item(4, 2)->setText(QString::number(Lambda_sigma,'f',3));
            }

            if (ui->tableWidget_9->item(5, 2) != 0)
            {
                ui->tableWidget_9->item(5, 2)->setText(QString::number(Lambda_1z1,'f',3));
            }

            if (ui->tableWidget_9->item(6, 2) != 0)
            {
                ui->tableWidget_9->item(6, 2)->setText(QString::number(Lambda_12,'f',3));
            }

            if (ui->tableWidget_9->item(7, 2) != 0)
            {
                ui->tableWidget_9->item(7, 2)->setText(QString::number(Lambda_1ip1,'f',3));
            }

            if (ui->tableWidget_9->item(8, 2) != 0)
            {
                ui->tableWidget_9->item(8, 2)->setText(QString::number(delta,'f',6));
            }

            if (ui->tableWidget_9->item(9, 2) != 0)
            {
                ui->tableWidget_9->item(9, 2)->setText(QString::number(Lambda_ekv,'f',6));
            }

            if (ui->tableWidget_9->item(10, 2) != 0)
            {
                ui->tableWidget_9->item(10, 2)->setText(QString::number(Lambda_epz,'f',6));
            }

            if (ui->tableWidget_9->item(11, 2) != 0)
            {
                ui->tableWidget_9->item(11, 2)->setText(QString::number(Lambda_i1z,'f',6));
            }

            if (ui->tableWidget_9->item(12, 2) != 0)
            {
                ui->tableWidget_9->item(12, 2)->setText(QString::number(Lambda_z,'f',6));
            }

            if (ui->tableWidget_9->item(13, 2) != 0)
            {
                ui->tableWidget_9->item(13, 2)->setText(QString::number(Lambda_nz,'f',6));
            }

            if (ui->tableWidget_9->item(14, 2) != 0)
            {
                ui->tableWidget_9->item(14, 2)->setText(QString::number(Lambda_i1a,'f',6));
            }

            if (ui->tableWidget_9->item(15, 2) != 0)
            {
                ui->tableWidget_9->item(15, 2)->setText(QString::number(Lambda_ekpa,'f',6));
            }

            if (ui->tableWidget_9->item(16, 2) != 0)
            {
                ui->tableWidget_9->item(16, 2)->setText(QString::number(Lambda_2ip1,'f',6));
            }

            if (ui->tableWidget_9->item(17, 2) != 0)
            {
                ui->tableWidget_9->item(17, 2)->setText(QString::number(Lambda_a,'f',6));
            }

            if (ui->tableWidget_9->item(18, 2) != 0)
            {
                ui->tableWidget_9->item(18, 2)->setText(QString::number(Lambda_na,'f',6));
            }

            if (ui->tableWidget_9->item(19, 2) != 0)
            {
                ui->tableWidget_9->item(19, 2)->setText(QString::number(Lambda_za,'f',6));
            }

            if (ui->tableWidget_9->item(20, 2) != 0)
            {
                ui->tableWidget_9->item(20, 2)->setText(QString::number(Lambda_pl,'f',6));
            }

            if (ui->tableWidget_9->item(21, 2) != 0)
            {
                ui->tableWidget_9->item(21, 2)->setText(QString::number(Lambda_il,'f',6));
            }

            if (ui->tableWidget_9->item(22, 2) != 0)
            {
                ui->tableWidget_9->item(22, 2)->setText(QString::number(Lambda_el,'f',6));
            }
            if (ui->tableWidget_9->item(23, 2) != 0)
            {
                ui->tableWidget_9->item(23, 2)->setText(QString::number(Lambda_al1,'f',6));
            }

            if (ui->tableWidget_9->item(24, 2) != 0)
            {
                ui->tableWidget_9->item(24, 2)->setText(QString::number(Lambda_l1,'f',6));
            }

            if (ui->tableWidget_9->item(25, 2) != 0)
            {
                ui->tableWidget_9->item(25, 2)->setText(QString::number(Lambda_lp2,'f',6));
            }

            if (ui->tableWidget_9->item(26, 2) != 0)
            {
                ui->tableWidget_9->item(26, 2)->setText(QString::number(Lambda_a2,'f',6));
            }

            if (ui->tableWidget_9->item(27, 2) != 0)
            {
                ui->tableWidget_9->item(27, 2)->setText(QString::number(Lambda_l2,'f',6));
            }

            if (ui->tableWidget_9->item(28, 2) != 0)
            {
                ui->tableWidget_9->item(28, 2)->setText(QString::number(Lambda_asch,'f',6));
            }

            if (ui->tableWidget_9->item(29, 2) != 0)
            {
                ui->tableWidget_9->item(29, 2)->setText(QString::number(Lambda_ast,'f',6));
            }

            if (ui->tableWidget_9->item(30, 2) != 0)
            {
                ui->tableWidget_9->item(30, 2)->setText(QString::number(Lambda_ai,'f',6));
            }

            if (ui->tableWidget_9->item(31, 2) != 0)
            {
                ui->tableWidget_9->item(31, 2)->setText(QString::number(alpha_stsumm,'f',6));
            }

            if (ui->tableWidget_9->item(32, 2) != 0)
            {
                ui->tableWidget_9->item(32, 2)->setText(QString::number(Lambda_ct1,'f',6));
            }

            if (ui->tableWidget_9->item(33, 2) != 0)
            {
                ui->tableWidget_9->item(33, 2)->setText(QString::number(Lambda_sch,'f',6));
            }

            if (ui->tableWidget_9->item(34, 2) != 0)
            {
                ui->tableWidget_9->item(34, 2)->setText(QString::number(Lambda_p,'f',6));
            }


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
            teta_4=gsl_vector_get(x, 0);
            teta_5=gsl_vector_get(x, 1);
            teta_k=gsl_vector_get(x, 2);
            teta_c=gsl_vector_get(x, 3);
            teta_p=gsl_vector_get(x, 0);
            teta_v=gsl_vector_get(x, 1);

            gsl_permutation_free (p);
            gsl_vector_free (x);

            //Расчет температур
            teta_p=20;
            teta_z=50;
            teta_3=70;
            teta_c=76;
            teta_l_1=120;
            teta_pp=80;
            teta_l_2=120;
            teta_2=60;
            teta_4=40;

            //Вывод температур в таблицу
            ui->widget_5->ui->tableWidget->item(0,0)->setText("Температура_1, °C");
            ui->widget_5->ui->tableWidget->item(1,0)->setText("Температура_2, °C");
            ui->widget_5->ui->tableWidget->item(2,0)->setText("Температура_3, °C");
            ui->widget_5->ui->tableWidget->item(3,0)->setText("Температура_4, °C");
            ui->widget_5->ui->tableWidget->item(4,0)->setText("Температура_5, °C");
            ui->widget_5->ui->tableWidget->item(5,0)->setText("Температура_6, °C");
            ui->widget_5->ui->tableWidget->item(6,0)->setText("Температура_7, °C");
            ui->widget_5->ui->tableWidget->item(7,0)->setText("Температура_8, °C");
            ui->widget_5->ui->tableWidget->item(8,0)->setText("Температура_9, °C");
            ui->widget_5->ui->tableWidget->item(9,0)->setText("Температура_10, °C");

            ui->widget_5->ui->tableWidget->item(0,1)->setText(QString::number(teta_0,'f',3));
            ui->widget_5->ui->tableWidget->item(1,1)->setText(QString::number(teta_1,'f',3));
            ui->widget_5->ui->tableWidget->item(2,1)->setText(QString::number(teta_2,'f',3));
            ui->widget_5->ui->tableWidget->item(3,1)->setText(QString::number(teta_3,'f',3));
            ui->widget_5->ui->tableWidget->item(4,1)->setText(QString::number(teta_4,'f',3));
            ui->widget_5->ui->tableWidget->item(5,1)->setText(QString::number(teta_5,'f',3));
            ui->widget_5->ui->tableWidget->item(6,1)->setText(QString::number(teta_k,'f',3));
            ui->widget_5->ui->tableWidget->item(7,1)->setText(QString::number(teta_c,'f',3));
            ui->widget_5->ui->tableWidget->item(8,1)->setText(QString::number(teta_p,'f',3));
            ui->widget_5->ui->tableWidget->item(9,1)->setText(QString::number(teta_v,'f',3));

            //Расчет тоеплоемкостей в таблицу
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

            //вывод тоеплоемкостей в таблицу
            ui->widget_5->ui->tableWidget->item(0,2)->setText("Теплоемкость_1, Дж/К");
            ui->widget_5->ui->tableWidget->item(1,2)->setText("Теплоемкость_2, Дж/К");
            ui->widget_5->ui->tableWidget->item(2,2)->setText("Теплоемкость_3, Дж/К");
            ui->widget_5->ui->tableWidget->item(3,2)->setText("Теплоемкость_4, Дж/К");
            ui->widget_5->ui->tableWidget->item(4,2)->setText("Теплоемкость_5, Дж/К");
            ui->widget_5->ui->tableWidget->item(5,2)->setText("Теплоемкость_6, Дж/К");
            ui->widget_5->ui->tableWidget->item(6,2)->setText("Теплоемкость_7, Дж/К");
            ui->widget_5->ui->tableWidget->item(7,2)->setText("Теплоемкость_8, Дж/К");
            ui->widget_5->ui->tableWidget->item(8,2)->setText("Теплоемкость_9, Дж/К");
            ui->widget_5->ui->tableWidget->item(9,2)->setText("Теплоемкость_10, Дж/К");

            ui->widget_5->ui->tableWidget->item(0,3)->setText(QString::number(C_0,'f',3));
            ui->widget_5->ui->tableWidget->item(1,3)->setText(QString::number(C_1,'f',3));
            ui->widget_5->ui->tableWidget->item(2,3)->setText(QString::number(C_2,'f',3));
            ui->widget_5->ui->tableWidget->item(3,3)->setText(QString::number(C_3,'f',3));
            ui->widget_5->ui->tableWidget->item(4,3)->setText(QString::number(C_4,'f',3));
            ui->widget_5->ui->tableWidget->item(5,3)->setText(QString::number(C_5,'f',3));
            ui->widget_5->ui->tableWidget->item(6,3)->setText(QString::number(C_k,'f',3));
            ui->widget_5->ui->tableWidget->item(7,3)->setText(QString::number(C_c,'f',3));
            ui->widget_5->ui->tableWidget->item(8,3)->setText(QString::number(C_p,'f',3));
            ui->widget_5->ui->tableWidget->item(9,3)->setText(QString::number(C_v,'f',3));

            //Расчет мощностей рассеяния в таблицу
            P_0=0.034;
            P_1=0.35;
            P_2=0.23;
            P_3=0.021;
            P_4=0.034;
            P_5=0.067;
            P_k=0.067;
            P_c=0.67;
            P_p=0.56;
            P_v=0.059;

            //Вывод мощностей рассеяния в таблицу
            ui->widget_5->ui->tableWidget->item(0,4)->setText("Мощность_рассеяния_1, Вт");
            ui->widget_5->ui->tableWidget->item(1,4)->setText("Мощность_рассеяния_2, Вт");
            ui->widget_5->ui->tableWidget->item(2,4)->setText("Мощность_рассеяния_3, Вт");
            ui->widget_5->ui->tableWidget->item(3,4)->setText("Мощность_рассеяния_4, Вт");
            ui->widget_5->ui->tableWidget->item(4,4)->setText("Мощность_рассеяния_5, Вт");
            ui->widget_5->ui->tableWidget->item(5,4)->setText("Мощность_рассеяния_6, Вт");
            ui->widget_5->ui->tableWidget->item(6,4)->setText("Мощность_рассеяния_7, Вт");
            ui->widget_5->ui->tableWidget->item(7,4)->setText("Мощность_рассеяния_8, Вт");
            ui->widget_5->ui->tableWidget->item(8,4)->setText("Мощность_рассеяния_9, Вт");
            ui->widget_5->ui->tableWidget->item(9,4)->setText("Мощность_рассеяния_10, Вт");

            ui->widget_5->ui->tableWidget->item(0,5)->setText(QString::number(P_0,'f',3));
            ui->widget_5->ui->tableWidget->item(1,5)->setText(QString::number(P_1,'f',3));
            ui->widget_5->ui->tableWidget->item(2,5)->setText(QString::number(P_2,'f',3));
            ui->widget_5->ui->tableWidget->item(3,5)->setText(QString::number(P_3,'f',3));
            ui->widget_5->ui->tableWidget->item(4,5)->setText(QString::number(P_4,'f',3));
            ui->widget_5->ui->tableWidget->item(5,5)->setText(QString::number(P_5,'f',3));
            ui->widget_5->ui->tableWidget->item(6,5)->setText(QString::number(P_k,'f',3));
            ui->widget_5->ui->tableWidget->item(7,5)->setText(QString::number(P_c,'f',3));
            ui->widget_5->ui->tableWidget->item(8,5)->setText(QString::number(P_p,'f',3));
            ui->widget_5->ui->tableWidget->item(9,5)->setText(QString::number(P_v,'f',3));

            //вывод тепловых проводимостей в таблицу
            //lambda_10=0.034;
            lambda_10=Lambda_1z1;
            //lambda_30=0.034;
            lambda_30=Lambda_sigma;
            lambda_k0=0.34;
            lambda_50=0.93;
            lambda_3k=0.67;
            lambda_21=0.35;
            lambda_c2=0.23;
            lambda_c3=0.067;
            lambda_c4=0.56;
            lambda_45=0.56;
            lambda_pc=0.067;
            lambda_pb=0.059;
            lambda_b5=0.043;
            lambda_p5=0.0045;
            lambda_p2=0.021;

            ui->widget_5->ui->tableWidget->item(0,6)->setText("Теплопроводность_1, Вт/°C");
            ui->widget_5->ui->tableWidget->item(1,6)->setText("Теплопроводность_2, Вт/°C");
            ui->widget_5->ui->tableWidget->item(2,6)->setText("Теплопроводность_3, Вт/°C");
            ui->widget_5->ui->tableWidget->item(3,6)->setText("Теплопроводность_4, Вт/°C");
            ui->widget_5->ui->tableWidget->item(4,6)->setText("Теплопроводность_5, Вт/°C");
            ui->widget_5->ui->tableWidget->item(5,6)->setText("Теплопроводность_6, Вт/°C");
            ui->widget_5->ui->tableWidget->item(6,6)->setText("Теплопроводность_7, Вт/°C");
            ui->widget_5->ui->tableWidget->item(7,6)->setText("Теплопроводность_8, Вт/°C");
            ui->widget_5->ui->tableWidget->item(8,6)->setText("Теплопроводность_9, Вт/°C");
            ui->widget_5->ui->tableWidget->item(9,6)->setText("Теплопроводность_10, Вт/°C");
            ui->widget_5->ui->tableWidget->item(10,6)->setText("Теплопроводность_11, Вт/°C");
            ui->widget_5->ui->tableWidget->item(11,6)->setText("Теплопроводность_12, Вт/°C");
            ui->widget_5->ui->tableWidget->item(12,6)->setText("Теплопроводность_13, Вт/°C");
            ui->widget_5->ui->tableWidget->item(13,6)->setText("Теплопроводность_14, Вт/°C");
            ui->widget_5->ui->tableWidget->item(14,6)->setText("Теплопроводность_15, Вт/°C");

            ui->widget_5->ui->tableWidget->item(0,7)->setText(QString::number(lambda_10,'f',3));
            ui->widget_5->ui->tableWidget->item(1,7)->setText(QString::number(lambda_30,'f',3));
            ui->widget_5->ui->tableWidget->item(2,7)->setText(QString::number(lambda_k0,'f',3));
            ui->widget_5->ui->tableWidget->item(3,7)->setText(QString::number(lambda_50,'f',3));
            ui->widget_5->ui->tableWidget->item(4,7)->setText(QString::number(lambda_3k,'f',3));
            ui->widget_5->ui->tableWidget->item(5,7)->setText(QString::number(lambda_21,'f',3));
            ui->widget_5->ui->tableWidget->item(6,7)->setText(QString::number(lambda_c2,'f',3));
            ui->widget_5->ui->tableWidget->item(7,7)->setText(QString::number(lambda_c3,'f',3));
            ui->widget_5->ui->tableWidget->item(8,7)->setText(QString::number(lambda_c4,'f',3));
            ui->widget_5->ui->tableWidget->item(9,7)->setText(QString::number(lambda_45,'f',3));
            ui->widget_5->ui->tableWidget->item(10,7)->setText(QString::number(lambda_pc,'f',3));
            ui->widget_5->ui->tableWidget->item(11,7)->setText(QString::number(lambda_pb,'f',3));
            ui->widget_5->ui->tableWidget->item(12,7)->setText(QString::number(lambda_b5,'f',3));
            ui->widget_5->ui->tableWidget->item(13,7)->setText(QString::number(lambda_p5,'f',3));
            ui->widget_5->ui->tableWidget->item(14,7)->setText(QString::number(lambda_p2,'f',3));

            //Расчет мощностей рассеяния
            P_10=100;
            P_30=220;
            P_k0=230;
            P_50=450;
            P_3k=120;
            P_21=340;
            P_c2=560;
            P_c3=506;
            P_c4=760;
            P_45=100;
            P_pc=220;
            P_pb=230;
            P_b5=450;
            P_p5=120;
            P_p2=340;

            //Вывод тепловых проводимостей в таблицу
            ui->widget_5->ui->tableWidget->item(0,8)->setText("Мощность_рассеяния_1, Вт");
            ui->widget_5->ui->tableWidget->item(1,8)->setText("Мощность_рассеяния_2, Вт");
            ui->widget_5->ui->tableWidget->item(2,8)->setText("Мощность_рассеяния_3, Вт");
            ui->widget_5->ui->tableWidget->item(3,8)->setText("Мощность_рассеяния_4, Вт");
            ui->widget_5->ui->tableWidget->item(4,8)->setText("Мощность_рассеяния_5, Вт");
            ui->widget_5->ui->tableWidget->item(5,8)->setText("Мощность_рассеяния_6, Вт");
            ui->widget_5->ui->tableWidget->item(6,8)->setText("Мощность_рассеяния_7, Вт");
            ui->widget_5->ui->tableWidget->item(7,8)->setText("Мощность_рассеяния_8, Вт");
            ui->widget_5->ui->tableWidget->item(8,8)->setText("Мощность_рассеяния_9, Вт");
            ui->widget_5->ui->tableWidget->item(9,8)->setText("Мощность_рассеяния_10, Вт");
            ui->widget_5->ui->tableWidget->item(10,8)->setText("Мощность_рассеяния_11, Вт");
            ui->widget_5->ui->tableWidget->item(11,8)->setText("Мощность_рассеяния_12, Вт");
            ui->widget_5->ui->tableWidget->item(12,8)->setText("Мощность_рассеяния_13, Вт");
            ui->widget_5->ui->tableWidget->item(13,8)->setText("Мощность_рассеяния_14, Вт");
            ui->widget_5->ui->tableWidget->item(14,8)->setText("Мощность_рассеяния_15, Вт");

            ui->widget_5->ui->tableWidget->item(0,9)->setText(QString::number(P_10,'f',3));
            ui->widget_5->ui->tableWidget->item(1,9)->setText(QString::number(P_30,'f',3));
            ui->widget_5->ui->tableWidget->item(2,9)->setText(QString::number(P_k0,'f',3));
            ui->widget_5->ui->tableWidget->item(3,9)->setText(QString::number(P_50,'f',3));
            ui->widget_5->ui->tableWidget->item(4,9)->setText(QString::number(P_3k,'f',3));
            ui->widget_5->ui->tableWidget->item(5,9)->setText(QString::number(P_21,'f',3));
            ui->widget_5->ui->tableWidget->item(6,9)->setText(QString::number(P_c2,'f',3));
            ui->widget_5->ui->tableWidget->item(7,9)->setText(QString::number(P_c3,'f',3));
            ui->widget_5->ui->tableWidget->item(8,9)->setText(QString::number(P_c4,'f',3));
            ui->widget_5->ui->tableWidget->item(9,9)->setText(QString::number(P_45,'f',3));
            ui->widget_5->ui->tableWidget->item(10,9)->setText(QString::number(P_pc,'f',3));
            ui->widget_5->ui->tableWidget->item(11,9)->setText(QString::number(P_pb,'f',3));
            ui->widget_5->ui->tableWidget->item(12,9)->setText(QString::number(P_b5,'f',3));
            ui->widget_5->ui->tableWidget->item(13,9)->setText(QString::number(P_p5,'f',3));
            ui->widget_5->ui->tableWidget->item(14,9)->setText(QString::number(P_p2,'f',3));

            //Расчет падений температур
            d_teta_10=10;
            d_teta_30=22;
            d_teta_k0=23;
            d_teta_50=45;
            d_teta_3k=12;
            d_teta_21=34;
            d_teta_c2=56;
            d_teta_c3=50;
            d_teta_c4=76;
            d_teta_45=10;
            d_teta_pc=22;
            d_teta_pb=23;
            d_teta_b5=45;
            d_teta_p5=12;
            d_teta_p2=34;

            //Вывод падений температур в таблицу
            ui->widget_5->ui->tableWidget->item(0,10)->setText("Падение_температуры_1, °C");
            ui->widget_5->ui->tableWidget->item(1,10)->setText("Падение_температуры_2, °C");
            ui->widget_5->ui->tableWidget->item(2,10)->setText("Падение_температуры_3, °C");
            ui->widget_5->ui->tableWidget->item(3,10)->setText("Падение_температуры_4, °C");
            ui->widget_5->ui->tableWidget->item(4,10)->setText("Падение_температуры_5, °C");
            ui->widget_5->ui->tableWidget->item(5,10)->setText("Падение_температуры_6, °C");
            ui->widget_5->ui->tableWidget->item(6,10)->setText("Падение_температуры_7, °C");
            ui->widget_5->ui->tableWidget->item(7,10)->setText("Падение_температуры_8, °C");
            ui->widget_5->ui->tableWidget->item(8,10)->setText("Падение_температуры_9, °C");
            ui->widget_5->ui->tableWidget->item(9,10)->setText("Падение_температуры_10, °C");
            ui->widget_5->ui->tableWidget->item(10,10)->setText("Падение_температуры_11, °C");
            ui->widget_5->ui->tableWidget->item(11,10)->setText("Падение_температуры_12, °C");
            ui->widget_5->ui->tableWidget->item(12,10)->setText("Падение_температуры_13, °C");
            ui->widget_5->ui->tableWidget->item(13,10)->setText("Падение_температуры_14, °C");
            ui->widget_5->ui->tableWidget->item(14,10)->setText("Падение_температуры_15, °C");

            ui->widget_5->ui->tableWidget->item(0,11)->setText(QString::number(d_teta_10,'f',3));
            ui->widget_5->ui->tableWidget->item(1,11)->setText(QString::number(d_teta_30,'f',3));
            ui->widget_5->ui->tableWidget->item(2,11)->setText(QString::number(d_teta_k0,'f',3));
            ui->widget_5->ui->tableWidget->item(3,11)->setText(QString::number(d_teta_50,'f',3));
            ui->widget_5->ui->tableWidget->item(4,11)->setText(QString::number(d_teta_3k,'f',3));
            ui->widget_5->ui->tableWidget->item(5,11)->setText(QString::number(d_teta_21,'f',3));
            ui->widget_5->ui->tableWidget->item(6,11)->setText(QString::number(d_teta_c2,'f',3));
            ui->widget_5->ui->tableWidget->item(7,11)->setText(QString::number(d_teta_c3,'f',3));
            ui->widget_5->ui->tableWidget->item(8,11)->setText(QString::number(d_teta_c4,'f',3));
            ui->widget_5->ui->tableWidget->item(9,11)->setText(QString::number(d_teta_45,'f',3));
            ui->widget_5->ui->tableWidget->item(10,11)->setText(QString::number(d_teta_pc,'f',3));
            ui->widget_5->ui->tableWidget->item(11,11)->setText(QString::number(d_teta_pb,'f',3));
            ui->widget_5->ui->tableWidget->item(12,11)->setText(QString::number(d_teta_b5,'f',3));
            ui->widget_5->ui->tableWidget->item(13,11)->setText(QString::number(d_teta_p5,'f',3));
            ui->widget_5->ui->tableWidget->item(14,11)->setText(QString::number(d_teta_p2,'f',3));
        }
        if (item30->text() == "Статика (полный вариант)")
        {
            QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
        }
        if (item30->text() == "Динамика (расчет)")
        {
//            ui->widget_5->ui->tabWidget->show();
//            ui->widget_5->ui->tabWidget->setCurrentIndex(3);
            ui->tepl_result->setCheckable(true);
            if(ui->tepl_result->isChecked())
            {
                progress->setVisible(true);
                progress->setRange(0, 64 - 1);
                progress->reset();
                ui->widget_5->ui->widget_4->startTeplo();
            }
            else
            {
                ui->widget_5->ui->widget_4->stopTeplo();
            }
        }
        if (item30->text() == "Динамика (эксперимент)")
        {
            QMessageBox::information(this, "вариант 3!", "Статика (полный вариант)");
        }
    }
}

void MainWindow::on_vent_result_clicked()
{

    if (item34->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item34->text() == "Статика")
        {
            base_tepl.D1p      = ui->tableWidget_7->item(0,2)->text().toDouble();
            base_tepl.D2p      = ui->tableWidget_7->item(1,2)->text().toDouble();
            base_tepl.b       = ui->tableWidget_7->item(2,2)->text().toDouble();
            base_tepl.n2     = ui->tableWidget_7->item(3,2)->text().toDouble();
            base_tepl.ro = ui->tableWidget_7->item(4,2)->text().toDouble();
            base_tepl.Sotv   = ui->tableWidget_7->item(5,2)->text().toDouble();
            base_tepl.S0  = ui->tableWidget_7->item(6,2)->text().toDouble();
            base_tepl.S1     = ui->tableWidget_7->item(7,2)->text().toDouble();
            base_tepl.alpha1     = ui->tableWidget_7->item(8,2)->text().toDouble();
            base_tepl.S2   = ui->tableWidget_7->item(9,2)->text().toDouble();
            base_tepl.alpha2     = ui->tableWidget_7->item(10,2)->text().toDouble();
            base_tepl.S3   = ui->tableWidget_7->item(11,2)->text().toDouble();
            base_tepl.S4   = ui->tableWidget_7->item(12,2)->text().toDouble();
            base_tepl.fi     = ui->tableWidget_7->item(13,2)->text().toDouble();
            base_tepl.fi2   = ui->tableWidget_7->item(14,2)->text().toDouble();

            //Начальное давление вентилятора:
            H0=0.00695 * pow(base_tepl.n2,2) * (pow(base_tepl.D2p,2) - pow(base_tepl.D1p,2));

            //Максимальный расход воздуха:
            Qmax = 0.006 * pow(base_tepl.D2p,2) * base_tepl.b * base_tepl.n2;

            //Сопротивление входа в кожух через решетку с острыми кромками
            base_tepl.epsilon1 = 0.5;
            Z1 = base_tepl.epsilon1 * (base_tepl.ro / (2 * pow(base_tepl.Sotv,2)));

            //Сопротивление поворота потока за входной решеткой перед входом в вентилятор
            base_tepl.epsilon2 = 0.5;
            Z2 = base_tepl.epsilon2 * (base_tepl.ro / (2 * pow(base_tepl.S1,2)));

            //Сопротивление потока за входным вентилятором перед входом в межреберные каналы
            base_tepl.epsilon3 = 0.5;
            Z3 = base_tepl.epsilon3 * (base_tepl.ro / (2 * pow(base_tepl.S2,2)));

            //Сопротивление косого входа в межреберные каналы
            base_tepl.epsilon4 = 0.5;
            base_tepl.cosf = 0.7;
            Z4 = base_tepl.epsilon4 * (base_tepl.ro / (2 * pow( base_tepl.S4,2) * pow(base_tepl.cosf,2)));

            //Сопротивление поворота потока в межреберных каналах под кожухом
            base_tepl.epsilon5 = 0.5;
            Z5 = base_tepl.epsilon5 * (base_tepl.ro / (2 * pow(base_tepl.S4,2)));

            //Сопротивление выхода воздуха из межреберных каналов в воздушное пространство
            base_tepl.epsilon6 = 0.5;
            Z6 = base_tepl.epsilon6 * (base_tepl.ro / (2 * pow(base_tepl.S4,2)));

            //Суммарное сопротивление вентиляционной сети
            Z0=1.2 *(Z1 + Z2 + Z3 + Z4 + Z5 + Z6);

            //Рабочий расход воздуха
            Qp = Qmax * sqrt(H0 /(H0 + Z0 * pow(Qmax,2)));

            //Рабочий набор вентилятора
            Hp = Z0 * pow(Qp,2);

            //Средняя скорость воздуха в межреберных каналах
            base_tepl.K = 1;
            Vcp = base_tepl.K *Qp /base_tepl.S4;

            //Потребляемая вентилятором мощность
            base_tepl.nu2 = 0.7;
            Pvent = 9.81 * (Qp * Hp / base_tepl.nu2);



            if (ui->tableWidget_13->item(0, 2) != 0)
            {
                ui->tableWidget_13->item(0, 2)->setText(QString::number(H0,'f',3));
            }

            if (ui->tableWidget_13->item(1, 2) != 0)
            {
                ui->tableWidget_13->item(1, 2)->setText(QString::number(Qmax,'f',3));
            }

            if (ui->tableWidget_13->item(2, 2) != 0)
            {
                ui->tableWidget_13->item(2, 2)->setText(QString::number(Z1,'f',3));
            }

            if (ui->tableWidget_13->item(3, 2) != 0)
            {
                ui->tableWidget_13->item(3, 2)->setText(QString::number(Z2,'f',3));
            }
            if (ui->tableWidget_13->item(4, 2) != 0)
            {
                ui->tableWidget_13->item(4, 2)->setText(QString::number(Z3,'f',3));
            }

            if (ui->tableWidget_13->item(5, 2) != 0)
            {
                ui->tableWidget_13->item(5, 2)->setText(QString::number(Z4,'f',3));
            }

            if (ui->tableWidget_13->item(6, 2) != 0)
            {
                ui->tableWidget_13->item(6, 2)->setText(QString::number(Z5,'f',3));
            }

            if (ui->tableWidget_13->item(7, 2) != 0)
            {
                ui->tableWidget_13->item(7, 2)->setText(QString::number(Z6,'f',3));
            }

            if (ui->tableWidget_13->item(8, 2) != 0)
            {
                ui->tableWidget_13->item(8, 2)->setText(QString::number(Z0,'f',6));
            }

            if (ui->tableWidget_13->item(9, 2) != 0)
            {
                ui->tableWidget_13->item(9, 2)->setText(QString::number(Qp,'f',6));
            }

            if (ui->tableWidget_13->item(10, 2) != 0)
            {
                ui->tableWidget_13->item(10, 2)->setText(QString::number(Hp,'f',6));
            }

            if (ui->tableWidget_13->item(11, 2) != 0)
            {
                ui->tableWidget_13->item(11, 2)->setText(QString::number(Vcp,'f',6));
            }

            if (ui->tableWidget_13->item(12, 2) != 0)
            {
                ui->tableWidget_13->item(12, 2)->setText(QString::number(Pvent,'f',6));
            }
        }
    }

    double Q =0;
    double H1 = 0;
    double H2 = 0;
    double ne;
    double Pv;
    ui->widget_6->ui->plot_2->clear();
    ui->widget_6->ui->plot_2->addDataLine(QColor(Qt::red), 0);
    ui->widget_6->ui->plot_2->addDataLine(QColor(Qt::green), 0);
    for (int i=0;i<100; i++)
    {
        Q+=0.0001;
        H1 = Z0 * pow(Q,2);
        H2 = H0 *(1 - pow((Q/Qmax),2));
        ui->widget_6->ui->plot_2->addPoint(0, Q, H1);
        ui->widget_6->ui->plot_2->addPoint(1, Q, H2);
        qDebug() << H1 << H2 << Qt::endl;
    }
    ne=0.19*sin(M_PI)*(Qp/Qmax);

    Pv=(Qp*Hp);
    double dPvk=0.01;
    double dPsvp=0.001;
    double dPkd=0.6;

    double eps = 0.07;
    double dPptk = eps * base_tepl.ro * pow((Qp/base_tepl.S1),2);
    double dPvpk = eps * base_tepl.ro * pow((Qp/base_tepl.S1),2);
    qDebug() << Pv;

    //Расчет составляющих энергетической диаграммы вентилятора

    if (ui->tableWidget_11->item(5, 2) != 0)
    {
        ui->tableWidget_11->item(5, 2)->setText(QString::number(Pvent,'f',3));
    }
    if (ui->tableWidget_11->item(6, 2) != 0)
    {
        ui->tableWidget_11->item(6, 2)->setText(QString::number(Pv,'f',3));
    }
    if (ui->tableWidget_11->item(0, 2) != 0)
    {
        ui->tableWidget_11->item(0, 2)->setText(QString::number(dPptk,'f',3));
    }
    if (ui->tableWidget_11->item(1, 2) != 0)
    {
        ui->tableWidget_11->item(1, 2)->setText(QString::number(dPvpk,'f',3));
    }
    if (ui->tableWidget_11->item(2, 2) != 0)
    {
        ui->tableWidget_11->item(2, 2)->setText(QString::number(dPvk,'f',3));
    }
    if (ui->tableWidget_11->item(3, 2) != 0)
    {
        ui->tableWidget_11->item(3, 2)->setText(QString::number(dPsvp,'f',3));
    }
    if (ui->tableWidget_11->item(4, 2) != 0)
    {
        ui->tableWidget_11->item(4, 2)->setText(QString::number(dPkd,'f',3));
    }

    ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text139\").text('Nsv = %1 Вт');").arg(Pvent, 0, 'f', 3));
    ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text75\").text('N = %1 Вт');").arg(Pv, 0, 'f', 3));
    ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text113\").text('ΔNptk = %1 Вт');").arg(dPptk, 0, 'f', 3));
    ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text91\").text('ΔNvpk = %1 Вт');").arg(dPvpk, 0, 'f', 3));
    ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text33\").text('ΔNvk = %1 Вт');").arg(dPvk, 0, 'f', 3));
    ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text53\").text('ΔNsvp = %1 Вт');").arg(dPsvp, 0, 'f', 3));
    ui->widget_6->ui->webEngineView_4->page()->runJavaScript(QString("$(\"#text185\").text('ΔNkd = %1 Вт');").arg(dPkd, 0, 'f', 3));

//    if (item34->text() == "Выберите режим")
//    {
//        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
//    }
//    else
//    {
//        if (item34->text() == "Динамика (расчет)")
//        {

//            QMessageBox::critical(this, "Привет!", "сеанс2");
//        }
//    }
//    if (item34->text() == "Выберите режим")
//    {
//        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
//    }
//    else
//    {
//        if (item34->text() == "Динамика (эксперимент)")
//        {
//            QMessageBox::critical(this, "Привет!", "сеанс3");
//        }
//    }
    }

void MainWindow::on_save_electromagn_graph_file_clicked()
{
    QString filters;
    foreach(QByteArray byte, QImageWriter::supportedImageFormats())
    {
        QString format = byte;
        filters += QString("%1 (%2)\n").arg(format.toUpper(),"*." + format);
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as..."), "img.png", filters);
    if (fileName.isEmpty() || fileName.isNull())
        return;

    ui->widget_2->ui->plot->grab().save(fileName);
}


void MainWindow::on_save_electromagn2_file_clicked()
{
    QString filters;
    foreach(QByteArray byte, QImageWriter::supportedImageFormats())
    {
        QString format = byte;
        filters += QString("%1 (%2)\n").arg(format.toUpper(),"*." + format);
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as..."), "img.png", filters);
    if (fileName.isEmpty() || fileName.isNull())
        return;

    ui->widget_3->ui->plot->grab().save(fileName);
}


void MainWindow::on_save_tepl_graph_file_clicked()
{
    QString filters;
    foreach(QByteArray byte, QImageWriter::supportedImageFormats())
    {
        QString format = byte;
        filters += QString("%1 (%2)\n").arg(format.toUpper(),"*." + format);
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as..."), "img.png", filters);
    if (fileName.isEmpty() || fileName.isNull())
        return;

    ui->widget_5->ui->widget_4->ui->plot->grab().save(fileName);
}



void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->lineEdit->setText(QString("%1").arg(value / 99.0 * 30));
}


void MainWindow::on_radioButton_11_toggled(bool checked)
{
    if (item34->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item34->text() == "Статика")
        {
            if (checked)
            {
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text909').html('Z<tspan style=\"font-size: 15px;\" dy=\"3\">1</tspan>');"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text913').html('Z<tspan style=\"font-size: 15px;\" dy=\"3\">2</tspan>');"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text917').html('Z<tspan style=\"font-size: 15px;\" dy=\"3\">3</tspan>');"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text921').html('Z<tspan style=\"font-size: 15px;\" dy=\"3\">4</tspan>');"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text925').html('Z<tspan style=\"font-size: 15px;\" dy=\"3\">5</tspan>');"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text929').html('Z<tspan style=\"font-size: 15px;\" dy=\"3\">6</tspan>');"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text953').html('Q<tspan style=\"font-size: 15px;\" dy=\"3\">p</tspan>');"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text941').html('H<tspan style=\"font-size: 15px;\" dy=\"3\">p</tspan>');"));

            }
        }
    }
}


void MainWindow::on_radioButton_12_toggled(bool checked)
{
    if (item34->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item34->text() == "Статика")
        {
            if (checked)
            {
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text909').text('%1 кг·с²/м⁸');").arg(Z1,0,'f',3));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text913' ).text('%1 кг·с²/м⁸');").arg(Z2, 0, 'f', 2));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text917').text('%1 кг·с²/м⁸');").arg(Z3, 0, 'f', 2));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text921').text('%1 кг·с²/м⁸');").arg(Z4, 0, 'f', 2));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text925').text('%1 кг·с²/м⁸');").arg(Z5, 0, 'f', 2));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text929').text('%1 кг·с²/м⁸');").arg(Z6, 0, 'f', 2));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text953' ).text('%1 м³/с');").arg(Qp, 0, 'f', 2));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text941').text('%1 Па');").arg(Hp, 0, 'f', 2));                           }
        }
    }
}


void MainWindow::on_radioButton_13_toggled(bool checked)
{
    if (item34->text() == "Выберите режим")
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите тип эксперимента в настройках сеанса");
    }
    else
    {
        if (item34->text() == "Статика")
        {
            if (checked)
            {
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text909').hide();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text913').hide();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text917').hide();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text921').hide();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text925').hide();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text929').hide();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text953').hide();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text941').hide();"));
            }
            else
            {
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text909').show();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text913').show();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text917').show();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text921').show();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text925').show();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text929').show();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text1011').show();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text953').show();"));
                ui->widget_6->ui->webEngineView_3->page()->runJavaScript(QString("$('#text941').show();"));
            }
        }
    }
}

SettinsKanals::SettinsKanals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settinsKanals)
{
    ui->setupUi(this);
}

