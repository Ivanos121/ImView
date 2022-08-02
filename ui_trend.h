/********************************************************************************
** Form generated from reading UI file 'trend.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TREND_H
#define UI_TREND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include "plot.h"

QT_BEGIN_NAMESPACE

class Ui_Trend
{
public:
    QHBoxLayout *horizontalLayout;
    Plot *plot;

    void setupUi(QWidget *Trend)
    {
        if (Trend->objectName().isEmpty())
            Trend->setObjectName(QString::fromUtf8("Trend"));
        Trend->resize(1144, 828);
        horizontalLayout = new QHBoxLayout(Trend);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        plot = new Plot(Trend);
        plot->setObjectName(QString::fromUtf8("plot"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(plot->sizePolicy().hasHeightForWidth());
        plot->setSizePolicy(sizePolicy);
        plot->setMinimumSize(QSize(0, 0));
        plot->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(plot);


        retranslateUi(Trend);

        QMetaObject::connectSlotsByName(Trend);
    } // setupUi

    void retranslateUi(QWidget *Trend)
    {
        Trend->setWindowTitle(QCoreApplication::translate("Trend", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Trend: public Ui_Trend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TREND_H
