/********************************************************************************
** Form generated from reading UI file 'vent_izm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENT_IZM_H
#define UI_VENT_IZM_H

#include <QtCore/QVariant>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_vent_izm
{
public:
    QGridLayout *gridLayout;
    QWebEngineView *webEngineView;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer;
    QTableWidget *tableWidget;
    QLabel *label;

    void setupUi(QWidget *vent_izm)
    {
        if (vent_izm->objectName().isEmpty())
            vent_izm->setObjectName(QString::fromUtf8("vent_izm"));
        vent_izm->resize(1091, 660);
        gridLayout = new QGridLayout(vent_izm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        webEngineView = new QWebEngineView(vent_izm);
        webEngineView->setObjectName(QString::fromUtf8("webEngineView"));
        webEngineView->setUrl(QUrl(QString::fromUtf8("about:blank")));

        gridLayout->addWidget(webEngineView, 0, 0, 1, 1);

        groupBox = new QGroupBox(vent_izm);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(500, 0));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 2, 0, 1, 1);

        tableWidget = new QTableWidget(groupBox);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        tableWidget->setMinimumSize(QSize(0, 500));

        gridLayout_3->addWidget(tableWidget, 1, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox, 0, 1, 1, 1);


        retranslateUi(vent_izm);

        QMetaObject::connectSlotsByName(vent_izm);
    } // setupUi

    void retranslateUi(QWidget *vent_izm)
    {
        vent_izm->setWindowTitle(QCoreApplication::translate("vent_izm", "Form", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("vent_izm", "<html><head/><body><p><span style=\" font-size:14pt;\">\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\320\271</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class vent_izm: public Ui_vent_izm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENT_IZM_H
