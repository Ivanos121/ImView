/********************************************************************************
** Form generated from reading UI file 'identf.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IDENTF_H
#define UI_IDENTF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include "plot.h"

QT_BEGIN_NAMESPACE

class Ui_identf
{
public:
    QGridLayout *gridLayout;
    Plot *plot;

    void setupUi(QWidget *identf)
    {
        if (identf->objectName().isEmpty())
            identf->setObjectName(QString::fromUtf8("identf"));
        identf->resize(1172, 886);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(identf->sizePolicy().hasHeightForWidth());
        identf->setSizePolicy(sizePolicy);
        identf->setMinimumSize(QSize(0, 0));
        identf->setAutoFillBackground(true);
        gridLayout = new QGridLayout(identf);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        plot = new Plot(identf);
        plot->setObjectName(QString::fromUtf8("plot"));
        sizePolicy.setHeightForWidth(plot->sizePolicy().hasHeightForWidth());
        plot->setSizePolicy(sizePolicy);

        gridLayout->addWidget(plot, 0, 0, 1, 1);


        retranslateUi(identf);

        QMetaObject::connectSlotsByName(identf);
    } // setupUi

    void retranslateUi(QWidget *identf)
    {
        identf->setWindowTitle(QCoreApplication::translate("identf", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class identf: public Ui_identf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IDENTF_H
