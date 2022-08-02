/********************************************************************************
** Form generated from reading UI file 'draw_poper.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAW_POPER_H
#define UI_DRAW_POPER_H

#include <QtCore/QVariant>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_draw_poper
{
public:
    QHBoxLayout *horizontalLayout;
    QWebEngineView *webEngineView;
    QWebEngineView *webEngineView_2;

    void setupUi(QWidget *draw_poper)
    {
        if (draw_poper->objectName().isEmpty())
            draw_poper->setObjectName(QString::fromUtf8("draw_poper"));
        draw_poper->resize(941, 631);
        horizontalLayout = new QHBoxLayout(draw_poper);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        webEngineView = new QWebEngineView(draw_poper);
        webEngineView->setObjectName(QString::fromUtf8("webEngineView"));
        webEngineView->setUrl(QUrl(QString::fromUtf8("about:blank")));

        horizontalLayout->addWidget(webEngineView);

        webEngineView_2 = new QWebEngineView(draw_poper);
        webEngineView_2->setObjectName(QString::fromUtf8("webEngineView_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(webEngineView_2->sizePolicy().hasHeightForWidth());
        webEngineView_2->setSizePolicy(sizePolicy);
        webEngineView_2->setMinimumSize(QSize(150, 0));
        webEngineView_2->setUrl(QUrl(QString::fromUtf8("about:blank")));

        horizontalLayout->addWidget(webEngineView_2);


        retranslateUi(draw_poper);

        QMetaObject::connectSlotsByName(draw_poper);
    } // setupUi

    void retranslateUi(QWidget *draw_poper)
    {
        draw_poper->setWindowTitle(QCoreApplication::translate("draw_poper", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class draw_poper: public Ui_draw_poper {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAW_POPER_H
