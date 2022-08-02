/********************************************************************************
** Form generated from reading UI file 'teplschem.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEPLSCHEM_H
#define UI_TEPLSCHEM_H

#include <QtCore/QVariant>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_teplschem
{
public:
    QGridLayout *gridLayout;
    QWebEngineView *webEngineView;
    QButtonGroup *buttonGroup_2;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *teplschem)
    {
        if (teplschem->objectName().isEmpty())
            teplschem->setObjectName(QString::fromUtf8("teplschem"));
        teplschem->resize(984, 707);
        gridLayout = new QGridLayout(teplschem);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        webEngineView = new QWebEngineView(teplschem);
        webEngineView->setObjectName(QString::fromUtf8("webEngineView"));
        webEngineView->setUrl(QUrl(QString::fromUtf8("about:blank")));

        gridLayout->addWidget(webEngineView, 0, 1, 1, 1);


        retranslateUi(teplschem);

        QMetaObject::connectSlotsByName(teplschem);
    } // setupUi

    void retranslateUi(QWidget *teplschem)
    {
        teplschem->setWindowTitle(QCoreApplication::translate("teplschem", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class teplschem: public Ui_teplschem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEPLSCHEM_H
