/********************************************************************************
** Form generated from reading UI file 'vent_tract.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENT_TRACT_H
#define UI_VENT_TRACT_H

#include <QtCore/QVariant>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Vent_tract
{
public:
    QGridLayout *gridLayout;
    QWebEngineView *webEngineView;
    QSlider *verticalSlider;
    QSlider *verticalSlider_2;
    QWebEngineView *webEngineView_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableWidget *tableWidget;
    QLabel *label_2;
    QTableWidget *tableWidget_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QWidget *Vent_tract)
    {
        if (Vent_tract->objectName().isEmpty())
            Vent_tract->setObjectName(QString::fromUtf8("Vent_tract"));
        Vent_tract->resize(1166, 630);
        gridLayout = new QGridLayout(Vent_tract);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        webEngineView = new QWebEngineView(Vent_tract);
        webEngineView->setObjectName(QString::fromUtf8("webEngineView"));
        webEngineView->setUrl(QUrl(QString::fromUtf8("about:blank")));

        gridLayout->addWidget(webEngineView, 0, 0, 1, 1);

        verticalSlider = new QSlider(Vent_tract);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(verticalSlider, 0, 1, 1, 1);

        verticalSlider_2 = new QSlider(Vent_tract);
        verticalSlider_2->setObjectName(QString::fromUtf8("verticalSlider_2"));
        verticalSlider_2->setOrientation(Qt::Vertical);

        gridLayout->addWidget(verticalSlider_2, 0, 2, 1, 1);

        webEngineView_2 = new QWebEngineView(Vent_tract);
        webEngineView_2->setObjectName(QString::fromUtf8("webEngineView_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(webEngineView_2->sizePolicy().hasHeightForWidth());
        webEngineView_2->setSizePolicy(sizePolicy);
        webEngineView_2->setMinimumSize(QSize(150, 0));
        webEngineView_2->setUrl(QUrl(QString::fromUtf8("about:blank")));

        gridLayout->addWidget(webEngineView_2, 0, 3, 1, 1);

        groupBox = new QGroupBox(Vent_tract);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(500, 0));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        tableWidget = new QTableWidget(groupBox);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setAlternatingRowColors(true);

        verticalLayout->addWidget(tableWidget);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        tableWidget_2 = new QTableWidget(groupBox);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setAlternatingRowColors(true);

        verticalLayout->addWidget(tableWidget_2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);


        gridLayout->addWidget(groupBox, 0, 4, 1, 1);

        verticalSlider->raise();
        verticalSlider_2->raise();
        webEngineView_2->raise();
        groupBox->raise();
        webEngineView->raise();

        retranslateUi(Vent_tract);

        QMetaObject::connectSlotsByName(Vent_tract);
    } // setupUi

    void retranslateUi(QWidget *Vent_tract)
    {
        Vent_tract->setWindowTitle(QCoreApplication::translate("Vent_tract", "Form", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("Vent_tract", "<html><head/><body><p><span style=\" font-size:16pt;\">\320\230\321\201\321\205\320\276\320\264\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("Vent_tract", "<html><head/><body><p><span style=\" font-size:16pt;\">\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("Vent_tract", "0 speed", nullptr));
        label_4->setText(QCoreApplication::translate("Vent_tract", "0 moment", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Vent_tract: public Ui_Vent_tract {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENT_TRACT_H
