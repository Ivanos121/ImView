/********************************************************************************
** Form generated from reading UI file 'datas.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAS_H
#define UI_DATAS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_datas
{
public:
    QGridLayout *gridLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *enterDannie;
    QPushButton *saveDannie;
    QPushButton *deleteDannie;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_12;
    QTableView *tableView;

    void setupUi(QWidget *datas)
    {
        if (datas->objectName().isEmpty())
            datas->setObjectName(QString::fromUtf8("datas"));
        datas->resize(1366, 757);
        gridLayout = new QGridLayout(datas);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget_2 = new QWidget(datas);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMaximumSize(QSize(16777215, 55));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        enterDannie = new QPushButton(widget_2);
        enterDannie->setObjectName(QString::fromUtf8("enterDannie"));
        enterDannie->setMinimumSize(QSize(0, 33));
        enterDannie->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_2->addWidget(enterDannie);

        saveDannie = new QPushButton(widget_2);
        saveDannie->setObjectName(QString::fromUtf8("saveDannie"));
        saveDannie->setMinimumSize(QSize(0, 33));
        saveDannie->setMaximumSize(QSize(150, 33));

        horizontalLayout_2->addWidget(saveDannie);

        deleteDannie = new QPushButton(widget_2);
        deleteDannie->setObjectName(QString::fromUtf8("deleteDannie"));
        deleteDannie->setMinimumSize(QSize(0, 33));
        deleteDannie->setMaximumSize(QSize(150, 33));

        horizontalLayout_2->addWidget(deleteDannie, 0, Qt::AlignVCenter);


        gridLayout->addWidget(widget_2, 2, 0, 1, 1);

        groupBox_2 = new QGroupBox(datas);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        verticalLayout->addWidget(label_12);

        tableView = new QTableView(groupBox_2);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(tableView);


        gridLayout->addWidget(groupBox_2, 0, 0, 2, 1);

        QWidget::setTabOrder(saveDannie, deleteDannie);
        QWidget::setTabOrder(deleteDannie, tableView);

        retranslateUi(datas);

        QMetaObject::connectSlotsByName(datas);
    } // setupUi

    void retranslateUi(QWidget *datas)
    {
        datas->setWindowTitle(QCoreApplication::translate("datas", "Form", nullptr));
        enterDannie->setText(QCoreApplication::translate("datas", "\320\222\320\262\320\265\321\201\321\202\320\270 \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
        saveDannie->setText(QCoreApplication::translate("datas", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
        deleteDannie->setText(QCoreApplication::translate("datas", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
        label_12->setText(QCoreApplication::translate("datas", "<html><head/><body><p><span style=\" font-size:14pt;\">\320\241\320\277\320\270\321\201\320\276\320\272 \321\201\320\276\321\205\321\200\320\260\320\275\320\265\320\275\320\275\321\213\321\205 \320\264\320\262\320\270\320\263\320\260\321\202\320\265\320\273\320\265\320\271</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class datas: public Ui_datas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAS_H
