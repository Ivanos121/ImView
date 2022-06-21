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

#include "base.h"
#include "datas.h"
#include "ui_datas.h"
#include "identf.h"
#include "electromagn.h"
#include "kalibr.h"
#include "teplovent.h"
#include "ui_teplovent.h"
#include "ui_draw_line.h"
#include "ui_draw_poper.h"
#include "ui_teplschem.h"
#include "ui_vent_model.h"
#include "ui_vent_izm.h"
#include "ui_datas.h"
#include "vent_model.h"
#include "ui_vent_model.h"
#include "ui_vent_tract.h"
#include "gridlinedelegate.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

Base base;

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
    ui->widget_5->ui->widget_5->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/rad_var/rad_var_2.html").absoluteFilePath()));
    ui->widget_6->ui->widget_2->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_tract/vent_tract.html").absoluteFilePath()));
    ui->widget_5->ui->widget_3->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/tepl_schen_zam/vent_tract.html").absoluteFilePath()));

    ui->widget_5->ui->widget->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));
    ui->widget_5->ui->widget_5->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));
    ui->widget_6->ui->widget->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));

    showMaximized();
    ui->action_9->setEnabled(false);
    ui->action_21->setEnabled(false);

    ui->pushButton_5->setCheckable(true);
    ui->pushButton_5->setChecked(true);
    QObject::connect(ui->pushButton_5, SIGNAL(clicked(bool)), ui->groupBox, SLOT(setVisible(bool)));

    ui->treeView->setSelectionBehavior(QTreeView :: SelectRows); // Выбираем всю строку за раз
    ui->treeView->setSelectionMode(QTreeView :: SingleSelection); // Одиночный выбор, при этом вся строка над ним является одной строкой меню
    ui->treeView->setAlternatingRowColors(true); // Цвет каждой строки интервала разный, при наличии qss этот атрибут недействителен
    ui->treeView->setFocusPolicy(Qt :: NoFocus);
    ui->treeView->setExpandsOnDoubleClick(true);
    ui->treeView->setRootIsDecorated(true);
    QFont newFontt("DroidSans", 10, QFont::Normal, false);
    ui->treeView->setFont(newFontt);

    ui->treeView->setExpandsOnDoubleClick(false);
    QObject::connect(ui->treeView, &QTreeView::clicked, [this]() {
        if (ui->treeView->isExpanded(ui->treeView->currentIndex())) {
            ui->treeView->collapse(ui->treeView->currentIndex());
        }else{
            ui->treeView->expand(ui->treeView->currentIndex());
        }
    });

    QStandardItemModel* model=new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels (QStringList () << QStringLiteral ("Наименование") << QStringLiteral ("Свойство")); // Установить заголовок столбца
    ui->treeView->header()->setDefaultAlignment(Qt::AlignCenter);

        ui->treeView->setStyleSheet("*::item{"
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
                                    "        image: url(branch-closed.png);"
                                    "}"
                                    "::branch:open:has-children:!has-siblings,"
                                    "::branch:open:has-children:has-siblings  {"
                                   "        border-image: none;"
                                    "        image: url(branch-open.png);"
                                    "}"
                                    );

    QList<QStandardItem*> items1;
    item1 = new QStandardItem(QStringLiteral ("Общие настройки проекта"));
    QString w0=item1->text();
    item1->setToolTip(w0);
    item2 = new QStandardItem();
    items1.append(item1);
    items1.append(item2);
    model->appendRow(items1);
    //item1->setForeground(QBrush(Qt::white));
    item1->setSelectable(false);
    item1->setEditable(false);
    item2->setSelectable(false);
    item2->setEditable(false);
    QFont newFont("DroidSans", 10, QFont::Bold,false);
    item1->setFont(newFont);

    QList<QStandardItem*> items2;
    item3 = new QStandardItem(QStringLiteral ("Название проекта"));
    item3->setEditable(false);
    QString w1=item3->text();
    item3->setToolTip(w1);
    item4 = new QStandardItem(QStringLiteral ("Имя проекта"));
    QString w2=item4->text();
    item4->setToolTip(w2);
    items2.append(item3);
    items2.append(item4);
    item1->appendRow(items2);
    items2.clear();

    if(item4->parent())
    item5 = new QStandardItem(QStringLiteral ("Расположение файла проекта"));
    item5->setEditable(false);
    QString w3=item5->text();
    item5->setToolTip(w3);
    item6 = new QStandardItem(QStringLiteral ("Выбрать файл"));
    QString w4=item6->text();
    item6->setToolTip(w4);
    items2.append(item5);
    items2.append(item6);
    item1->appendRow(items2);
    items2.clear();

    item83 = new QStandardItem(QStringLiteral ("Расположение файла базы данных двигателей"));
    item83->setEditable(false);
    QString w5=item83->text();
    item83->setToolTip(w5);
    item84 = new QStandardItem(QStringLiteral ("Выбрать файл"));
    QString w6=item84->text();
    item84->setToolTip(w6);
    items2.append(item83);
    items2.append(item84);
    item1->appendRow(items2);
    items2.clear();

    item85 = new QStandardItem(QStringLiteral ("Расположение файла базы данных настроек"));
    item85->setEditable(false);
    QString w7=item85->text();
    item85->setToolTip(w7);
    item86 = new QStandardItem(QStringLiteral ("Выбрать файл"));
    QString w8=item86->text();
    item86->setToolTip(w8);
    items2.append(item85);
    items2.append(item86);
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
    item11 = new QStandardItem(QStringLiteral ("Настройки поправочных коэффициентов"));
    item11->setEditable(false);
    QFont newFont12("SansSerif", 10, QFont::Bold,false);
    item11->setFont(newFont12);
    QString w33=item11->text();
    item11->setToolTip(w33);
    item12 = new QStandardItem();
    item12->setEditable(false);
    QString w34=item12->text();
    item12->setToolTip(w34);
    items4.append(item11);
    items4.append(item12);
    item9->appendRow(items4);
    items4.clear();

    item13 = new QStandardItem(QStringLiteral ("Автоматический режим"));
    item13->setEditable(false);
    QString w35=item13->text();
    item13->setToolTip(w35);
    item14 = new QStandardItem();
    item14->setEditable(false);
    item14->setCheckable(true);
    item14->setToolTip(QStringLiteral ("Выкл"));
    items4.append(item13);
    items4.append(item14);
    item11->appendRow(items4);
    items4.clear();

    item15 = new QStandardItem(QStringLiteral ("Ручной режим"));
    item15->setEditable(false);
    QString w36=item15->text();
    item15->setToolTip(w36);
    item16 = new QStandardItem();
    item16->setEditable(false);
    item16->setCheckable(true);
    item16->setToolTip(QStringLiteral ("Выкл"));
    items4.append(item15);
    items4.append(item16);
    item11->appendRow(items4);
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
    item15->appendRow(items4);
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
    item15->appendRow(items4);
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
    item15->appendRow(items4);
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
    item15->appendRow(items4);
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
    item15->appendRow(items4);
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
    item15->appendRow(items4);
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
    item27 = new QStandardItem(QStringLiteral ("Условие 7"));
    item27->setEditable(false);
    item28 = new QStandardItem(QStringLiteral ("Значение 7"));
    items8.append(item27);
    items8.append(item28);
    item25->appendRow(items8);
    items8.clear();
    item29 = new QStandardItem(QStringLiteral ("Условие 8"));
    item29->setEditable(false);
    item30 = new QStandardItem(QString ("Значение 8"));
    items8.append(item29);
    items8.append(item30);
    item25->appendRow(items8);
    items8.clear();
    item23 = new QStandardItem(QStringLiteral ("Условие 9"));
    item23->setEditable(false);
    item107 = new QStandardItem(QStringLiteral ("Значение 9"));
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
    //item31->setForeground(QBrush(Qt::white));
    item31->setSelectable(false);
    item31->setEditable(false);
    item32->setSelectable(false);
    item32->setEditable(false);
    QFont newFont5("SansSerif", 10, QFont::Bold,false);
    item31->setFont(newFont5);

    QList<QStandardItem*> items10;
    item33 = new QStandardItem(QStringLiteral ("Условие 10"));
    item33->setEditable(false);
    item34 = new QStandardItem(QStringLiteral ("Значение 10"));
    items10.append(item33);
    items10.append(item34);
    item31->appendRow(items10);
    items10.clear();
    item35 = new QStandardItem(QStringLiteral ("Условие 11"));
    item35->setEditable(false);
    item36 = new QStandardItem(QString ("Значение 11"));
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

    QPalette p99=ui->treeView->palette();
    p99.setColor(QPalette::Base, QColor(255, 255, 222));
    p99.setColor(QPalette::AlternateBase, QColor(255, 255, 191));
    ui->treeView->setPalette(p99);

    ui->tabWidget->setCurrentIndex(0);
    QString currentTabText = ui->tabWidget->tabText(0);
    setWindowTitle(currentTabText + "@" + QString("base") + QString(" - ImView"));

    connect(item16->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot);
    connect(item88->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_2);
    connect(item80->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_3);
    connect(item68->model(), &QStandardItemModel::itemChanged, this, &MainWindow::modelItemChangedSlot_4);

    connect(buttonColumnDelegate, &ButtonColumnDelegate::projectFileSelected, this, &MainWindow::projectFileSelectedSlot);
    connect(buttonColumnDelegate, &ButtonColumnDelegate::projectFileSelected_2, this, &MainWindow::projectFileSelectedSlot_2);
    connect(buttonColumnDelegate, &ButtonColumnDelegate::projectFileSelected_3, this, &MainWindow::projectFileSelectedSlot_3);
    connect(buttonColumnDelegate, &ButtonColumnDelegate::projectFileSelected_5, this, &MainWindow::projectFileSelectedSlot_5);
    connect(buttonColumnDelegate, &ButtonColumnDelegate::projectFileSelected_6, this, &MainWindow::projectFileSelectedSlot_6);

}

void MainWindow::closeEvent (QCloseEvent *)
{
    ui->widget_3->stop();
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
//qDebug() << QString("%1").arg(base.P_nom);

    ui->action_5->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-paused.svg"));
    ui->action_9->setEnabled(true);
    ui->widget_2->raschet_f();
}

void MainWindow::on_action_9_triggered()
{
    ui->action_5->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-start_2.svg"));
    ui->action_9->setEnabled(false);
    ui->widget_2->dataSource->stop();
}

void MainWindow::on_action_20_triggered()
{
    ui->action_20->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-paused.svg"));
    ui->action_21->setEnabled(true);
    ui->widget_5->ui->widget_4->startTeplo();
    ui->widget_3->raschet_el();
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

void MainWindow::on_action_23_triggered()
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
    QScreen *screen = QGuiApplication::primaryScreen();
        rsc2= new Settings(this);
        rsc2->exec();
        rsc2->setGeometry(
            QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            rsc2->size(),
            screen->geometry()));
}

void MainWindow::modelItemChangedSlot(QStandardItem *item)
{
    if (item == item16)
    {
        if (item->checkState() == Qt::Checked)
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
    QString str = QFileDialog::getSaveFileName(this, "Выбрать имя, под которым сохранить данные", "/home/elf/progeqts_QT/treeviewprogect/Out", filter);

    QFile file(QString("/home/elf/progeqts_QT/treeviewprogect/Data/project.xml"));
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

    xmlWriter.writeStartElement("project_path");
    xmlWriter.writeAttribute("value", (item6->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("project_path_2");
    xmlWriter.writeAttribute("value", (item84->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("project_path_3");
    xmlWriter.writeAttribute("value", (item86->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_1");
    xmlWriter.writeAttribute("value", (item88->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("project_path_4");
    xmlWriter.writeAttribute("value", (item106->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("combobox_2");
    xmlWriter.writeAttribute("value", (item80->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("project_path_5");
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

    xmlWriter.writeStartElement("checkbox_7");
    xmlWriter.writeAttribute("boolean", (item14->checkState()? "true" : "false"));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("checkbox_8");
    xmlWriter.writeAttribute("boolean", (item16->checkState()? "true" : "false"));
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

    xmlWriter.writeStartElement("combobox_3");
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

    xmlWriter.writeStartElement("regim_ep");
    xmlWriter.writeAttribute("value", (item92->text()));
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();   // Закрываем файл

    JlCompress::compressDir(str, "/home/elf/progeqts_QT/treeviewprogect/Data/");
}

void MainWindow::on_LoadProgect_clicked()
{
    QString filter = "Файл конфигурации проекта (*.imview);;Все файлы (*.*)";
    QString str = QFileDialog::getOpenFileName(this, "Выбрать имя, под которым сохранить данные", "/home/elf/progeqts_QT/treeviewprogect/Out", filter);
    //QDir().mkdir("/home/elf/progeqts_QT/treeviewprogect/Data/");
    JlCompress::extractDir(str,"/home/elf/progeqts_QT/treeviewprogect/Data/");
    QFile file(QString("/home/elf/progeqts_QT/treeviewprogect/Data/project.xml"));
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
                else if(xmlReader.name() == "project_path")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item6->setText(attribute_value);
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
                            item84->setText(attribute_value);
                        }
                    }
                }
                else if(xmlReader.name() == "project_path_3")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "value")
                        {
                            QString attribute_value = attr.value().toString();
                            item86->setText(attribute_value);
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
                else if(xmlReader.name() == "project_path_4")
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
                else if(xmlReader.name() == "project_path_5")
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
                else if(xmlReader.name() == "checkbox_7")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "boolean")
                        {
                            QString attribute_value = attr.value().toString();
                            if(attribute_value=="true"){
                            item14->setCheckState(Qt::Checked);}
                            else {item14->setCheckState(Qt::Unchecked);};
                        }
                    }
                }
                else if(xmlReader.name() == "checkbox_8")
                {
                    foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
                    {
                        if (attr.name().toString() == "boolean")
                        {
                            QString attribute_value = attr.value().toString();
                            if(attribute_value=="true"){
                            item16->setCheckState(Qt::Checked);}
                            else {item16->setCheckState(Qt::Unchecked);};
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
                else if(xmlReader.name() == "combobox_3")
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
                else if(xmlReader.name() == "regim_ep")
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
             }
        xmlReader.readNext(); // Переходим к следующему элементу файла
        }
    file.close(); // Закрываем файл
    }
}

void MainWindow::on_PushButton_5_clicked(bool clicked)
{
    if(clicked)
    {
        ui->groupBox->setVisible(false);
    }
}







