/********************************************************************************
** Form generated from reading UI file 'vent_model.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENT_MODEL_H
#define UI_VENT_MODEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "vent_izm.h"
#include "vent_tract.h"

QT_BEGIN_NAMESPACE

class Ui_vent_model
{
public:
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab_5;
    QWidget *tab;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    vent_izm *widget_2;
    QWidget *tab_3;
    QGridLayout *gridLayout_2;
    Vent_tract *widget;
    QWidget *tab_6;
    QWidget *tab_4;

    void setupUi(QWidget *vent_model)
    {
        if (vent_model->objectName().isEmpty())
            vent_model->setObjectName(QString::fromUtf8("vent_model"));
        vent_model->resize(1096, 673);
        gridLayout = new QGridLayout(vent_model);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(vent_model);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        tabWidget->addTab(tab_5, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        widget_2 = new vent_izm(tab_2);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));

        gridLayout_3->addWidget(widget_2, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        gridLayout_2 = new QGridLayout(tab_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        widget = new Vent_tract(tab_3);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout_2->addWidget(widget, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        tabWidget->addTab(tab_6, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tabWidget->addTab(tab_4, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(vent_model);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(vent_model);
    } // setupUi

    void retranslateUi(QWidget *vent_model)
    {
        vent_model->setWindowTitle(QCoreApplication::translate("vent_model", "Form", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("vent_model", "\320\230\321\201\321\205\320\276\320\264\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("vent_model", "\320\222\320\265\320\275\321\202\320\270\320\273\321\217\321\206\320\270\320\276\320\275\320\275\320\260\321\217 \320\274\320\276\320\264\320\265\320\273\321\214 \320\267\320\260\320\274\320\265\321\211\320\265\320\275\320\270\321\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("vent_model", "\320\240\320\260\321\201\320\277\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\270\320\265 \320\262\320\276\320\267\320\264\321\203\321\210\320\275\320\276\320\263\320\276 \320\277\320\276\321\202\320\276\320\272\320\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("vent_model", "\320\240\320\260\321\201\320\277\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\270\320\265 \321\202\320\265\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QCoreApplication::translate("vent_model", "\320\242\321\200\320\265\320\275\320\264\321\213 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\276\320\262 \320\262\320\265\321\202\320\275\321\202\320\270\320\273\321\217\321\206\320\270\320\276\320\275\320\275\320\276\320\271 \321\201\320\265\321\202\320\270", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("vent_model", "\320\255\320\275\320\265\321\200\320\263\320\265\321\202\320\270\321\207\320\265\321\201\320\272\320\260\321\217 \320\264\320\270\320\260\320\263\321\200\320\260\320\274\320\274\320\260 \320\262\320\265\320\275\321\202\320\270\320\273\321\217\321\202\320\276\321\200\320\260 \320\270 \320\265\320\263\320\276 \321\201\320\262\320\276\320\271\321\201\321\202\320\262\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class vent_model: public Ui_vent_model {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENT_MODEL_H
