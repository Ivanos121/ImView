/********************************************************************************
** Form generated from reading UI file 'teplovent.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEPLOVENT_H
#define UI_TEPLOVENT_H

#include <QtCore/QVariant>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "draw_line.h"
#include "draw_poper.h"
#include "tepl_dannie.h"
#include "teplschem.h"
#include "trend.h"

QT_BEGIN_NAMESPACE

class Ui_teplovent
{
public:
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    Tepl_dannie *widget_2;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget_2;
    QWidget *tab_5;
    QGridLayout *gridLayout_7;
    QWebEngineView *webEngineView_2;
    QWidget *tab_6;
    QGridLayout *gridLayout_6;
    teplschem *widget_3;
    QWidget *tab_7;
    QGridLayout *gridLayout_8;
    QWebEngineView *webEngineView;
    QWidget *tab_4;
    QGridLayout *gridLayout;
    Trend *widget_4;
    QWidget *tab_3;
    QGridLayout *gridLayout_4;
    draw_line *widget;
    QWidget *tab_13;
    QGridLayout *gridLayout_5;
    draw_poper *widget_5;

    void setupUi(QWidget *teplovent)
    {
        if (teplovent->objectName().isEmpty())
            teplovent->setObjectName(QString::fromUtf8("teplovent"));
        teplovent->resize(1183, 720);
        horizontalLayout = new QHBoxLayout(teplovent);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(teplovent);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widget_2 = new Tepl_dannie(tab);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));

        gridLayout_2->addWidget(widget_2, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tabWidget_2 = new QTabWidget(tab_2);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        gridLayout_7 = new QGridLayout(tab_5);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        webEngineView_2 = new QWebEngineView(tab_5);
        webEngineView_2->setObjectName(QString::fromUtf8("webEngineView_2"));
        webEngineView_2->setUrl(QUrl(QString::fromUtf8("about:blank")));

        gridLayout_7->addWidget(webEngineView_2, 0, 0, 1, 1);

        tabWidget_2->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        gridLayout_6 = new QGridLayout(tab_6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        widget_3 = new teplschem(tab_6);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));

        gridLayout_6->addWidget(widget_3, 0, 0, 1, 1);

        tabWidget_2->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        gridLayout_8 = new QGridLayout(tab_7);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        webEngineView = new QWebEngineView(tab_7);
        webEngineView->setObjectName(QString::fromUtf8("webEngineView"));
        webEngineView->setUrl(QUrl(QString::fromUtf8("about:blank")));

        gridLayout_8->addWidget(webEngineView, 0, 0, 1, 1);

        tabWidget_2->addTab(tab_7, QString());

        gridLayout_3->addWidget(tabWidget_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        gridLayout = new QGridLayout(tab_4);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget_4 = new Trend(tab_4);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));

        gridLayout->addWidget(widget_4, 0, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_4 = new QGridLayout(tab_3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        widget = new draw_line(tab_3);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout_4->addWidget(widget, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_13 = new QWidget();
        tab_13->setObjectName(QString::fromUtf8("tab_13"));
        gridLayout_5 = new QGridLayout(tab_13);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        widget_5 = new draw_poper(tab_13);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));

        gridLayout_5->addWidget(widget_5, 0, 0, 1, 1);

        tabWidget->addTab(tab_13, QString());

        horizontalLayout->addWidget(tabWidget);


        retranslateUi(teplovent);

        tabWidget->setCurrentIndex(3);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(teplovent);
    } // setupUi

    void retranslateUi(QWidget *teplovent)
    {
        teplovent->setWindowTitle(QCoreApplication::translate("teplovent", "Form", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("teplovent", "\320\230\321\201\321\205\320\276\320\264\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QCoreApplication::translate("teplovent", "\320\241\321\205\320\265\320\274\320\260 \320\267\320\260\320\274\320\265\321\211\320\265\320\275\320\270\321\217 \321\201\321\202\320\260\321\202\320\276\321\200\320\260", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QCoreApplication::translate("teplovent", "\320\243\320\277\321\200\320\276\321\211\320\265\320\275\320\275\320\260\321\217 \321\201\321\205\320\265\320\274\320\260 \320\267\320\260\320\274\320\265\321\211\320\265\320\275\320\270\321\217 \320\264\320\262\320\270\320\263\320\260\321\202\320\265\320\273\321\217", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_7), QCoreApplication::translate("teplovent", "\320\237\320\276\320\273\320\275\320\260\321\217 \321\201\321\205\320\265\320\274\320\260 \320\267\320\260\320\274\320\265\321\211\320\265\320\275\320\270\321\217 \320\264\320\262\320\270\320\263\320\260\321\202\320\265\320\273\321\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("teplovent", "\320\242\320\265\320\277\320\273\320\276\320\262\320\260\321\217 \321\201\321\205\320\265\320\274\320\260 \320\267\320\260\320\274\320\265\321\211\320\265\320\275\320\270\321\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("teplovent", "\320\242\321\200\320\265\320\275\320\264\321\213 \321\202\320\265\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("teplovent", "\320\240\320\260\321\201\320\277\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\270\320\265 \321\202\320\265\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200 \320\277\320\276 \320\277\321\200\320\276\320\264\320\276\320\273\321\214\320\275\320\276\320\274\321\203 \321\201\320\265\321\207\320\265\320\275\320\270\321\216", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_13), QCoreApplication::translate("teplovent", "\320\240\320\260\321\201\320\277\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\270\320\265 \321\202\320\265\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200 \320\277\320\276 \320\277\320\276\320\277\320\265\321\200\320\265\321\207\320\275\320\276\320\274\321\203 \321\201\320\265\321\207\320\265\320\275\320\270\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class teplovent: public Ui_teplovent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEPLOVENT_H
