/********************************************************************************
** Form generated from reading UI file 'electromagn.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ELECTROMAGN_H
#define UI_ELECTROMAGN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include "plot.h"

QT_BEGIN_NAMESPACE

class Ui_electromagn
{
public:
    QHBoxLayout *horizontalLayout;
    Plot *plot;

    void setupUi(QWidget *electromagn)
    {
        if (electromagn->objectName().isEmpty())
            electromagn->setObjectName(QString::fromUtf8("electromagn"));
        electromagn->resize(1251, 1025);
        horizontalLayout = new QHBoxLayout(electromagn);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        plot = new Plot(electromagn);
        plot->setObjectName(QString::fromUtf8("plot"));

        horizontalLayout->addWidget(plot);


        retranslateUi(electromagn);

        QMetaObject::connectSlotsByName(electromagn);
    } // setupUi

    void retranslateUi(QWidget *electromagn)
    {
        electromagn->setWindowTitle(QCoreApplication::translate("electromagn", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class electromagn: public Ui_electromagn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ELECTROMAGN_H
