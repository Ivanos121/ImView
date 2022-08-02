/********************************************************************************
** Form generated from reading UI file 'itogs.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITOGS_H
#define UI_ITOGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Itogs
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QTextEdit *textEdit;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QWidget *widget_2;

    void setupUi(QWidget *Itogs)
    {
        if (Itogs->objectName().isEmpty())
            Itogs->setObjectName(QString::fromUtf8("Itogs"));
        Itogs->resize(1239, 733);
        gridLayout = new QGridLayout(Itogs);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new QWidget(Itogs);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        textEdit = new QTextEdit(widget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout_2->addWidget(textEdit, 0, 0, 1, 1);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setMinimumSize(QSize(0, 40));
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pushButton_2 = new QPushButton(widget_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(widget_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(pushButton_3, 0, 2, 1, 1);

        pushButton = new QPushButton(widget_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_4 = new QPushButton(widget_3);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(pushButton_4, 0, 3, 1, 1);


        gridLayout_2->addWidget(widget_3, 1, 0, 1, 1);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        widget_2 = new QWidget(Itogs);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(500, 0));
        widget_2->setMaximumSize(QSize(500, 16777215));

        gridLayout->addWidget(widget_2, 0, 1, 1, 1);


        retranslateUi(Itogs);

        QMetaObject::connectSlotsByName(Itogs);
    } // setupUi

    void retranslateUi(QWidget *Itogs)
    {
        Itogs->setWindowTitle(QCoreApplication::translate("Itogs", "Form", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Itogs", "\320\237\320\265\321\207\320\260\321\202\321\214", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Itogs", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        pushButton->setText(QCoreApplication::translate("Itogs", "\320\236\321\202\321\207\320\265\321\202", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Itogs", "\320\237\321\200\320\265\320\264\320\276\321\201\320\274\320\276\321\202\321\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Itogs: public Ui_Itogs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITOGS_H
