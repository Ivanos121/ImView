/********************************************************************************
** Form generated from reading UI file 'about_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_DIALOG_H
#define UI_ABOUT_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_aboutDialog
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QLabel *label_2;

    void setupUi(QDialog *aboutDialog)
    {
        if (aboutDialog->objectName().isEmpty())
            aboutDialog->setObjectName(QString::fromUtf8("aboutDialog"));
        aboutDialog->resize(609, 356);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/img/IM_48x48.png"), QSize(), QIcon::Normal, QIcon::Off);
        aboutDialog->setWindowIcon(icon);
        aboutDialog->setModal(true);
        label = new QLabel(aboutDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 611, 301));
        label->setPixmap(QPixmap(QString::fromUtf8(":/image/data/img/images/zastavka.png")));
        pushButton = new QPushButton(aboutDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(510, 310, 85, 33));
        pushButton->setFocusPolicy(Qt::NoFocus);
        label_2 = new QLabel(aboutDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 320, 111, 21));

        retranslateUi(aboutDialog);

        QMetaObject::connectSlotsByName(aboutDialog);
    } // setupUi

    void retranslateUi(QDialog *aboutDialog)
    {
        aboutDialog->setWindowTitle(QCoreApplication::translate("aboutDialog", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265 IM View", nullptr));
        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("aboutDialog", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
        label_2->setText(QCoreApplication::translate("aboutDialog", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">\320\222\320\265\321\200\321\201\320\270\321\217 0.3.8</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class aboutDialog: public Ui_aboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_DIALOG_H
