#include "pushbuttondelegate.h"

#include <QPainter>
#include <QPushButton>
#include <QStylePainter>
#include <QDebug>
#include <QTableView>
#include <QSpinBox>
#include <QFileDialog>
#include <QDoubleSpinBox>
#include <QHelpEvent>
#include <QToolTip>
#include "qabstractitemview.h"
#include "qcombobox.h"

ButtonColumnDelegate::ButtonColumnDelegate(QObject *parent) :QStyledItemDelegate(parent)
{
}

QWidget * ButtonColumnDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 0))
    {
        //выбор режима работы программы
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Осциллограф ");
        editor->insertItem(1, "Внутренний источник данных");
        editor->insertItem(2, "Чтение данных из файла для идентификации параметров схемы замещения");
        return editor;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 1))
    {
        //загрузка или сохранение и отображение пути файла
        QPushButton * btn = new QPushButton(parent);
        const QSize BUTTON_SIZE = QSize(22, 22);
        btn->setMinimumSize(BUTTON_SIZE);
        btn->setFixedSize(BUTTON_SIZE);
        btn->setText("...");
        connect(btn,SIGNAL(clicked()), this, SLOT(btn_clicked_5()));
        return btn;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 2))
    {
        //выбор режима работы программы
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Осциллограф + наблюдатель скорости (без датчика скорости)");
        editor->insertItem(1, "Осциллограф + наблюдатель скорости (с датчиком скорости)");
        editor->insertItem(2, "Внутренний источник данных");
        editor->insertItem(3, "Чтение данных из файла для наблюдателя скорости");
        return editor;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 3))
    {
        //загрузка или сохранение и отображение пути файла
        QPushButton * btn = new QPushButton(parent);
        const QSize BUTTON_SIZE = QSize(22, 22);
        btn->setMinimumSize(BUTTON_SIZE);
        btn->setFixedSize(BUTTON_SIZE);
        btn->setText("...");
        connect(btn,SIGNAL(clicked()), this, SLOT(btn_clicked_6()));
        return btn;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 1))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Сохранение данных в картинку");
        editor->insertItem(1, "Сохранение данных в файл данных");
        return editor;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 3))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Сохранение данных в картинку");
        editor->insertItem(1, "Сохранение данных в файл данных");
        return editor;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 5))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Сохранение данных в картинку");
        editor->insertItem(1, "Сохранение данных в файл данных");
        return editor;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 7))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Сохранение данных в картинку");
        editor->insertItem(1, "Сохранение данных в файл данных");
        return editor;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 9))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Сохранение данных в картинку");
        editor->insertItem(1, "Сохранение данных в файл данных");
        return editor;
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 11))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Сохранение данных в картинку");
        editor->insertItem(1, "Сохранение данных в файл данных");
        return editor;
    }
    else if ((index.parent().row() == 1) && (index.row() == 0))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Автоматический");
        editor->insertItem(1, "Ручной");
        return editor;
    }
    else if ((index.parent().row() == 1) && (index.row() == 1))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 1) && (index.row() == 2))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 1) && (index.row() == 3))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 1) && (index.row() == 4))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 1) && (index.row() == 5))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 1) && (index.row() == 6))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 2) && (index.row() == 0))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Режим S1");
        editor->insertItem(1, "Режим S2");
        editor->insertItem(2, "Режим S3");
        editor->insertItem(3, "Режим S4");
        editor->insertItem(4, "Режим S6");
        return editor;
    }
    else if ((index.parent().row() == 2) && (index.row() == 1))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(5);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 2) && (index.row() == 2))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 2) && (index.row() == 3))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else if ((index.parent().row() == 2) && (index.row() == 4))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->insertItem(0, "Прямой пуск");
        editor->insertItem(1, "Управляемый пуск");
        editor->insertItem(2, "Система ТРН-АД");
        editor->insertItem(3, "Система ПЧ-АД");
        return editor;
    }
    else if ((index.parent().row() == 3) && (index.row() == 0))
    {
        QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
        editor->setFrame(false);
        editor->setMinimum(0);
        editor->setMaximum(100);
        return editor;
    }
    else
    {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

//setEditorData
void ButtonColumnDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 0))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        //comboBox->addItem(value);
        if(value == "Осциллограф")
            comboBox->setCurrentIndex(0);
        else if(value == "Внутренний источник данных")
            comboBox->setCurrentIndex(1);
        else if(value == "Чтение данных из файла для идентификации параметров схемы замещения")
            comboBox->setCurrentIndex(2);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 1))
    {
        QPushButton * btn = qobject_cast<QPushButton *>(editor);
        btn->setProperty("data_value", index.data());
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 2))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        //comboBox->addItem(value);
        if(value == "Осциллограф + наблюдатель скорости (без датчика скорости)")
            comboBox->setCurrentIndex(0);
        else if(value == "Осциллограф + наблюдатель скорости (с датчиком скорости)")
            comboBox->setCurrentIndex(1);
        else if(value == "Внутренний источник данных")
            comboBox->setCurrentIndex(2);
        else if(value == "Чтение данных из файла для наблюдателя скорости")
            comboBox->setCurrentIndex(3);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 3))
    {
        QPushButton * btn = qobject_cast<QPushButton *>(editor);
        btn->setProperty("data_value", index.data());
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 1))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Сохранение данных в картинку")
            comboBox->setCurrentIndex(0);
        else if(value == "Сохранение данных в файл данных")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 3))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Сохранение данных в картинку")
            comboBox->setCurrentIndex(0);
        else if(value == "Сохранение данных в файл данных")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 5))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Сохранение данных в картинку")
            comboBox->setCurrentIndex(0);
        else if(value == "Сохранение данных в файл данных")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 7))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Сохранение данных в картинку")
            comboBox->setCurrentIndex(0);
        else if(value == "Сохранение данных в файл данных")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 9))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Сохранение данных в картинку")
            comboBox->setCurrentIndex(0);
        else if(value == "Сохранение данных в файл данных")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 11))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Сохранение данных в картинку")
            comboBox->setCurrentIndex(0);
        else if(value == "Сохранение данных в файл данных")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 1) && (index.row() == 0))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Автоматический")
            comboBox->setCurrentIndex(0);
        else if(value == "Ручной")
            comboBox->setCurrentIndex(1);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 1) && (index.row() == 1))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 1) && (index.row() == 2))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 1) && (index.row() == 3))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 1) && (index.row() == 4))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 1) && (index.row() == 5))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 1) && (index.row() == 6))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 2) && (index.row() == 0))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        if(value == "Режим S1")
            comboBox->setCurrentIndex(0);
        else if(value == "Режим S2")
            comboBox->setCurrentIndex(1);
        else if(value == "Режим S3")
            comboBox->setCurrentIndex(2);
        else if(value == "Режим S4")
            comboBox->setCurrentIndex(3);
        else if(value == "Режим S6")
            comboBox->setCurrentIndex(4);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 2) && (index.row() == 1))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 2) && (index.row() == 2))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 2) && (index.row() == 3))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else if ((index.parent().row() == 2) && (index.row() == 4))
    {
        QString value = index.model()->data(index, Qt::DisplayRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        //comboBox->addItem(value);
        if(value == "Прямой пуск")
            comboBox->setCurrentIndex(0);
        else if(value == "Управляемый пуск")
            comboBox->setCurrentIndex(1);
        else if(value == "Система ТРН-АД")
            comboBox->setCurrentIndex(2);
        else if(value == "Система ПЧ-АД")
            comboBox->setCurrentIndex(3);
        int width=comboBox->minimumSizeHint().width();
        comboBox->view()->setMinimumWidth(width);
    }
    else if ((index.parent().row() == 3) && (index.row() == 0))
    {
        double value = index.model()->data(index, Qt::EditRole).toDouble();
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->setValue(value);
    }
    else
    {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}


void ButtonColumnDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 0))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 1))
    {
        QPushButton *btn = qobject_cast<QPushButton *>(editor);
        model->setData(index, btn->property("data_value"));
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 2))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 1) && (index.row() == 3))
    {
        QPushButton *btn = qobject_cast<QPushButton *>(editor);
        model->setData(index, btn->property("data_value"));
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 1))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 3))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 5))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 7))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 9))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().parent().row() == 0) && (index.parent().row() == 2) && (index.row() == 11))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 1) && (index.row() == 0))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 2) && (index.row() == 1))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    else if ((index.parent().row() == 2) && (index.row() == 2))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    else if ((index.parent().row() == 2) && (index.row() == 3))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    else if ((index.parent().row() == 2) && (index.row() == 4))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 2) && (index.row() == 5))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    else if ((index.parent().row() == 2) && (index.row() == 6))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }

    else if ((index.parent().row() == 2) && (index.row() == 0))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 2) && (index.row() == 1))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    else if ((index.parent().row() == 2) && (index.row() == 2))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    else if ((index.parent().row() == 2) && (index.row() == 3))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    else if ((index.parent().row() == 2) && (index.row() == 4))
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value);
    }
    else if ((index.parent().row() == 3) && (index.row() == 0))
    {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
        spinBox->interpretText();
        double value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
    else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void ButtonColumnDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void ButtonColumnDelegate::btn_clicked_4()
{
    QString projectFile_4 = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.cpp *.h");
    if(projectFile_4 != "")
    {
        emit projectFileSelected_4(projectFile_4);
    }
}

void ButtonColumnDelegate::btn_clicked_5()
{
    QString projectFile_5 = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.cpp *.h");
    if(projectFile_5 != "")
    {
        emit projectFileSelected_5(projectFile_5);
    }
}

void ButtonColumnDelegate::btn_clicked_6()
{
    QString projectFile_6 = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.cpp *.h");
    if(projectFile_6 != "")
    {
        emit projectFileSelected_6(projectFile_6);
    }
}

bool ButtonColumnDelegate::helpEvent( QHelpEvent* e, QAbstractItemView* view,
                                      const QStyleOptionViewItem& option, const QModelIndex& index )
{
    if (!e || !view)
        return false;
    if (e->type() == QEvent::ToolTip)
    {
        QVariant tooltip = index.data(Qt::DisplayRole);
        if (tooltip.canConvert<QString>()) {
            QString src=tooltip.toString();
            QToolTip::showText( e->globalPos(), QString("<div>%1</div>").arg(src.toHtmlEscaped()), view);
            return true;
        }
        if (!QStyledItemDelegate::helpEvent( e, view, option, index))
            QToolTip::hideText();
        return true;
    }

    return QStyledItemDelegate::helpEvent( e, view, option, index);
}
