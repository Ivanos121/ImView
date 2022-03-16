#include "datas.h"
#include "ui_datas.h"
#include "base.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include "QStandardItemModel"
#include "QStandardItem"
#include <stdio.h>
#include <QTableView>
#include <QStyle>
#include <QDesktopWidget>
#include <QPainter>
#include <QIntValidator>
#include <QFileDialog>

datas::datas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::datas)
{
    ui->setupUi(this);

    sdb = QSqlDatabase::addDatabase("QSQLITE");
    //sdb.setDatabaseName("/home/elf/Dropbox/Наблюдатель/injterfece/build-untitled-Desktop-Debug/mydb.db");
    sdb.setDatabaseName(QFileInfo("../data/base_db/mydb.db").absoluteFilePath());
    table();

    ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp( "^[А-Я]{3}\[0-9]{3}\[A-Z]{1}\[0-9]{1}\[А-Я]{1}\[1-9]{1}$" )));
    ui->lineEdit_3->setValidator(new QIntValidator(1,1000));
    ui->lineEdit_4->setValidator(new QIntValidator(1,1000));
    ui->lineEdit_5->setValidator(new QIntValidator(1,1000));
    ui->lineEdit_6->setValidator(new QRegExpValidator(QRegExp("^[0-9]{1}.[0-9]{3}$")));
    ui->lineEdit_7->setValidator(new QRegExpValidator(QRegExp("^[0-9]{1}.[0-9]{3}$")));
    ui->lineEdit_8->setValidator(new QRegExpValidator(QRegExp("^[0-9]{1}.[0-9]{3}$")));
    ui->lineEdit_9->setValidator(new QIntValidator(1,1000));

    ui->lineEdit_2->setAlignment(Qt::AlignCenter);
    ui->lineEdit_3->setAlignment(Qt::AlignCenter);
    ui->lineEdit_4->setAlignment(Qt::AlignCenter);
    ui->lineEdit_5->setAlignment(Qt::AlignCenter);
    ui->lineEdit_6->setAlignment(Qt::AlignCenter);
    ui->lineEdit_7->setAlignment(Qt::AlignCenter);
    ui->lineEdit_8->setAlignment(Qt::AlignCenter);
    ui->lineEdit_9->setAlignment(Qt::AlignCenter);
}

datas::~datas()
{
    delete ui;
}

void datas::on_pushButton_3_clicked()
{
    if(ui->lineEdit_2->text().isEmpty() || ui->lineEdit_3->text().isEmpty()
            || ui->lineEdit_4->text().isEmpty() || ui->lineEdit_5->text().isEmpty() || ui->lineEdit_6->text().isEmpty()
            || ui->lineEdit_7->text().isEmpty() || ui->lineEdit_8->text().isEmpty() || ui->lineEdit_9->text().isEmpty())
        {
        QMessageBox::critical(this, "Ошибка!", "Заполните пустые поля");
        }
    else
        {
        zapis();
        table();
        }

}

void datas::on_pushButton_4_clicked()
{
    QItemSelectionModel *selectModel = ui->tableView->selectionModel();
    if(selectModel->selectedRows().isEmpty())
    {
    QMessageBox::critical(this, "Ошибка!", "Выберите необходимую строку");
    }
    else
    {
    int rowNumber = ui->tableView->selectionModel()->selection().indexes()[0].row();
    ui->lineEdit_2->setText(ui->tableView->model()->index(rowNumber, 1).data().toString());
    ui->lineEdit_3->setText(ui->tableView->model()->index(rowNumber, 2).data().toString());
    ui->lineEdit_4->setText(ui->tableView->model()->index(rowNumber, 3).data().toString());
    ui->lineEdit_5->setText(ui->tableView->model()->index(rowNumber, 4).data().toString());
    ui->lineEdit_6->setText(ui->tableView->model()->index(rowNumber, 5).data().toString());
    ui->lineEdit_7->setText(ui->tableView->model()->index(rowNumber, 6).data().toString());
    ui->lineEdit_8->setText(ui->tableView->model()->index(rowNumber, 7).data().toString());
    ui->lineEdit_9->setText(ui->tableView->model()->index(rowNumber, 8).data().toString());
    }
}

void datas::table()
{
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("dvigatels");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true); //скрытие колонки id
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //выделение строки
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); //выделение одной строки
}

void datas::zapis()
{
    QSqlQuery query=QSqlQuery(sdb);
    query.prepare("INSERT INTO dvigatels (id, name, pn, n, un, cosf, kpd, mk, n0) "
                  "VALUES (:id, :name, :pn, :n, :un, :cosf, :kpd, :mk, :n0)");
    query.bindValue(":id", QVariant(QVariant::String));
    query.bindValue(":name", ui->lineEdit_2->text());
    query.bindValue(":pn",ui->lineEdit_3->text());
    query.bindValue(":n",ui->lineEdit_4->text());
    query.bindValue(":un",ui->lineEdit_5->text());
    query.bindValue(":cosf",ui->lineEdit_6->text());
    query.bindValue(":kpd",ui->lineEdit_7->text());
    query.bindValue(":mk",ui->lineEdit_8->text());
    query.bindValue(":n0",ui->lineEdit_9->text());
    if(!query.exec()){
        qDebug() << query.lastError().databaseText();
        qDebug() << query.lastError().driverText();
        return;
    }

}

void datas::on_pushButton_6_clicked()
{
    QItemSelectionModel *selectModel = ui->tableView->selectionModel();
    if(selectModel->selectedRows().isEmpty())
    {
        QMessageBox::critical(this, "Ошибка!", "Выберите необходимую строку");
    }
    else
    {
    QSqlQuery query=QSqlQuery(sdb);
    int rowNumber = ui->tableView->selectionModel()->selection().indexes()[0].row();
    query.prepare("DELETE FROM dvigatels WHERE id=:id");
    query.bindValue(":id", ui->tableView->model()->index(rowNumber, 0).data().toString());
    query.exec();
    table();
    }
}

void datas::on_pushButton_clicked()
{
    if(ui->lineEdit_2->text().isEmpty() || ui->lineEdit_3->text().isEmpty()
            || ui->lineEdit_4->text().isEmpty() || ui->lineEdit_5->text().isEmpty() || ui->lineEdit_6->text().isEmpty()
            || ui->lineEdit_7->text().isEmpty() || ui->lineEdit_8->text().isEmpty() || ui->lineEdit_9->text().isEmpty())
        {
        QMessageBox::critical(this, "Ошибка!", "Заполните пустые поля");
        return;
        }

        base.name = ui->lineEdit_2->text();
        base.P_nom = ui->lineEdit_3->text().toDouble();
        base.n_nom = ui->lineEdit_4->text().toDouble();
        base.U_fnom = ui->lineEdit_5->text().toDouble();
        base.cosf_nom = ui->lineEdit_6->text().toDouble();
        base.kpd_nom = ui->lineEdit_7->text().toDouble();
        base.muk = ui->lineEdit_8->text().toDouble();
        base.n_0 = ui->lineEdit_9->text().toDouble();

        if (ui->buttonGroup->checkedButton() == ui->radioButton_2)
        {
            if (dataSourceFilename.isEmpty())
            {
                QMessageBox::critical(this, tr("Ошибка!"), tr("Файл не выбран!"));
                return;
            }

            base.dataSourceFilename = dataSourceFilename;
        }
}

void datas::on_pushButton_2_clicked()
{
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();
}

void datas::on_pushButton_5_clicked()
{
    QSettings settings;
    dataSourceFilename = QFileDialog::getOpenFileName(this,
                                QString::fromUtf8("Открыть файл"),

                                settings.value("dataSource/LastPath", "").toString(),
                                "txt files (*.txt);;All files (*.*)");

    if (!dataSourceFilename.isEmpty())
    {
        settings.setValue("dataSource/LastPath",  QFileInfo(dataSourceFilename).absoluteDir().absolutePath());
    }
}

void datas::on_radioButton_2_toggled(bool checked)
{
    if (checked)
    {
       ui->pushButton_5->setEnabled(true);
    }
}

void datas::on_radioButton_toggled(bool checked)
{
    if (checked)
    {
       ui->pushButton_5->setEnabled(false);
    }
}

void datas::on_radioButton_3_toggled(bool checked)
{
    if (checked)
    {
       ui->pushButton_5->setEnabled(false);
    }
}

