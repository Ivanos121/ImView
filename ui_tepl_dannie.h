/********************************************************************************
** Form generated from reading UI file 'tepl_dannie.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEPL_DANNIE_H
#define UI_TEPL_DANNIE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tepl_dannie
{
public:
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_4;
    QTableWidget *tableWidget_3;
    QLabel *label_2;
    QTableWidget *tableWidget_2;
    QTableWidget *tableWidget;
    QTableWidget *tableWidget_4;

    void setupUi(QWidget *Tepl_dannie)
    {
        if (Tepl_dannie->objectName().isEmpty())
            Tepl_dannie->setObjectName(QString::fromUtf8("Tepl_dannie"));
        Tepl_dannie->resize(961, 744);
        gridLayout = new QGridLayout(Tepl_dannie);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(Tepl_dannie);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 3, 1, 1);

        label = new QLabel(Tepl_dannie);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_4 = new QLabel(Tepl_dannie);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 3, 1, 1);

        tableWidget_3 = new QTableWidget(Tepl_dannie);
        tableWidget_3->setObjectName(QString::fromUtf8("tableWidget_3"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget_3->sizePolicy().hasHeightForWidth());
        tableWidget_3->setSizePolicy(sizePolicy);
        tableWidget_3->setMinimumSize(QSize(0, 328));
        tableWidget_3->setMaximumSize(QSize(16777215, 16777215));
        tableWidget_3->setAlternatingRowColors(true);

        gridLayout->addWidget(tableWidget_3, 1, 3, 1, 1);

        label_2 = new QLabel(Tepl_dannie);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        tableWidget_2 = new QTableWidget(Tepl_dannie);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setAlternatingRowColors(true);

        gridLayout->addWidget(tableWidget_2, 1, 2, 3, 1);

        tableWidget = new QTableWidget(Tepl_dannie);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setAlternatingRowColors(true);

        gridLayout->addWidget(tableWidget, 1, 0, 3, 1);

        tableWidget_4 = new QTableWidget(Tepl_dannie);
        tableWidget_4->setObjectName(QString::fromUtf8("tableWidget_4"));
        sizePolicy.setHeightForWidth(tableWidget_4->sizePolicy().hasHeightForWidth());
        tableWidget_4->setSizePolicy(sizePolicy);
        tableWidget_4->setMinimumSize(QSize(0, 328));

        gridLayout->addWidget(tableWidget_4, 3, 3, 1, 1);


        retranslateUi(Tepl_dannie);

        QMetaObject::connectSlotsByName(Tepl_dannie);
    } // setupUi

    void retranslateUi(QWidget *Tepl_dannie)
    {
        Tepl_dannie->setWindowTitle(QCoreApplication::translate("Tepl_dannie", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("Tepl_dannie", "<html><head/><body><p><span style=\" font-size:14pt;\">\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \321\200\320\260\321\201\321\207\320\265\321\202\320\260 \321\202\320\265\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("Tepl_dannie", "<html><head/><body><p><span style=\" font-size:14pt;\">\320\230\321\201\321\205\320\276\320\264\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("Tepl_dannie", "<html><head/><body><p><span style=\" font-size:14pt;\">\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \321\200\320\260\321\201\321\207\320\265\321\202\320\260 \321\202\320\265\320\277\320\273\320\276\320\265\320\274\320\272\320\276\321\201\321\202\320\265\320\271</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("Tepl_dannie", "<html><head/><body><p><span style=\" font-size:14pt;\">\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \321\200\320\260\321\201\321\207\320\265\321\202\320\260 \321\202\320\265\320\277\320\273\320\276\320\262\321\213\321\205 \320\277\321\200\320\276\320\262\320\276\320\264\320\270\320\274\320\276\321\201\321\202\320\265\320\271</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tepl_dannie: public Ui_Tepl_dannie {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEPL_DANNIE_H
