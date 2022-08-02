/********************************************************************************
** Form generated from reading UI file 'graph_Settings.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPH_SETTINGS_H
#define UI_GRAPH_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_graph_Settings
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTableWidget *tableWidget;
    QPushButton *pushButton;

    void setupUi(QDialog *graph_Settings)
    {
        if (graph_Settings->objectName().isEmpty())
            graph_Settings->setObjectName(QString::fromUtf8("graph_Settings"));
        graph_Settings->resize(547, 568);
        gridLayout = new QGridLayout(graph_Settings);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_4 = new QGroupBox(graph_Settings);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        groupBox_4->setMinimumSize(QSize(500, 0));
        groupBox_4->setAutoFillBackground(false);
        verticalLayout_2 = new QVBoxLayout(groupBox_4);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        tableWidget = new QTableWidget(groupBox_4);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        tableWidget->setMinimumSize(QSize(0, 0));
        tableWidget->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_2->addWidget(tableWidget);


        gridLayout->addWidget(groupBox_4, 0, 0, 1, 1);

        pushButton = new QPushButton(graph_Settings);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);


        retranslateUi(graph_Settings);

        QMetaObject::connectSlotsByName(graph_Settings);
    } // setupUi

    void retranslateUi(QDialog *graph_Settings)
    {
        graph_Settings->setWindowTitle(QCoreApplication::translate("graph_Settings", "Dialog", nullptr));
        groupBox_4->setTitle(QString());
        label->setText(QCoreApplication::translate("graph_Settings", "<html><head/><body><p><span style=\" font-size:14pt;\">\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\263\321\200\320\260\321\204\320\270\320\272\320\276\320\262</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("graph_Settings", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class graph_Settings: public Ui_graph_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPH_SETTINGS_H
