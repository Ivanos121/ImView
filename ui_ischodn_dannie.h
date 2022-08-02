/********************************************************************************
** Form generated from reading UI file 'ischodn_dannie.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ISCHODN_DANNIE_H
#define UI_ISCHODN_DANNIE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ischodn_dannie
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *ischodn_dannie)
    {
        if (ischodn_dannie->objectName().isEmpty())
            ischodn_dannie->setObjectName(QString::fromUtf8("ischodn_dannie"));
        ischodn_dannie->resize(536, 474);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/data/img/icons/IM_16x16.png"), QSize(), QIcon::Normal, QIcon::Off);
        ischodn_dannie->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(ischodn_dannie);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidget = new QTableWidget(ischodn_dannie);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        widget = new QWidget(ischodn_dannie);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addWidget(widget);


        retranslateUi(ischodn_dannie);

        QMetaObject::connectSlotsByName(ischodn_dannie);
    } // setupUi

    void retranslateUi(QWidget *ischodn_dannie)
    {
        ischodn_dannie->setWindowTitle(QCoreApplication::translate("ischodn_dannie", "\320\222\320\262\320\276\320\264 \320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        pushButton->setText(QCoreApplication::translate("ischodn_dannie", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ischodn_dannie", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ischodn_dannie: public Ui_ischodn_dannie {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ISCHODN_DANNIE_H
