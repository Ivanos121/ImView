/********************************************************************************
** Form generated from reading UI file 'draw_line.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAW_LINE_H
#define UI_DRAW_LINE_H

#include <QtCore/QVariant>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_draw_line
{
public:
    QGridLayout *gridLayout;
    QWebEngineView *webEngineView;
    QWebEngineView *webEngineView_2;

    void setupUi(QWidget *draw_line)
    {
        if (draw_line->objectName().isEmpty())
            draw_line->setObjectName(QString::fromUtf8("draw_line"));
        draw_line->resize(882, 631);
        gridLayout = new QGridLayout(draw_line);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        webEngineView = new QWebEngineView(draw_line);
        webEngineView->setObjectName(QString::fromUtf8("webEngineView"));
        webEngineView->setUrl(QUrl(QString::fromUtf8("about:blank")));

        gridLayout->addWidget(webEngineView, 0, 0, 1, 1);

        webEngineView_2 = new QWebEngineView(draw_line);
        webEngineView_2->setObjectName(QString::fromUtf8("webEngineView_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(webEngineView_2->sizePolicy().hasHeightForWidth());
        webEngineView_2->setSizePolicy(sizePolicy);
        webEngineView_2->setMinimumSize(QSize(150, 0));
        webEngineView_2->setUrl(QUrl(QString::fromUtf8("about:blank")));

        gridLayout->addWidget(webEngineView_2, 0, 1, 1, 1);


        retranslateUi(draw_line);

        QMetaObject::connectSlotsByName(draw_line);
    } // setupUi

    void retranslateUi(QWidget *draw_line)
    {
        draw_line->setWindowTitle(QCoreApplication::translate("draw_line", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class draw_line: public Ui_draw_line {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAW_LINE_H
