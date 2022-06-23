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
#include <QScreen>

datas::datas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::datas)
{
    ui->setupUi(this);

    sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(QFileInfo("/home/elf/ImView/data/base_db/mydb.db").absoluteFilePath());

    table();
}

datas::~datas()
{
    delete ui;
}

//void datas::on_pushButton_clicked()
//{
//    zapis();
//    table();
//}

void datas::table()
{
    model = new QSqlTableModel;

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
    query.bindValue(":name", QString(base.name));
    query.bindValue(":pn",QString("%1").arg(base.P_nom, 0, 'f', 3));
    query.bindValue(":n",QString("%1").arg(base.n_nom, 0, 'f', 3));
    query.bindValue(":un",QString("%1").arg(base.U_fnom, 0, 'f', 3));
    query.bindValue(":cosf",QString("%1").arg(base.cosf_nom, 0, 'f', 3));
    query.bindValue(":kpd",QString("%1").arg(base.kpd_nom, 0, 'f', 3));
    query.bindValue(":mk",QString("%1").arg(base.muk, 0, 'f', 3));
    query.bindValue(":n0",QString("%1").arg(base.n_0, 0, 'f', 3));
    if(!query.exec()){
        qDebug() << query.lastError().databaseText();
        qDebug() << query.lastError().driverText();
        return;
    }

}

void datas::on_deleteDannie_clicked()
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

void datas::on_dannieIdent_clicked()
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

void datas::on_saveDannie_clicked()
{
//    zapis();
//    table();

    model->database().transaction();
        if(model->submitAll())
            model->database().commit();
        else
            model->database().rollback();
}

void datas::on_enterDannie_clicked()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    isdn=new ischodn_dannie(this);
    isdn->wf = this;
    isdn->exec();
    isdn->setGeometry(
    QStyle::alignedRect(
    Qt::LeftToRight,
    Qt::AlignCenter,
    isdn->size(),
    screen->geometry()));
}

//void datas::on_oscNoSpeed_toggled(bool checked)
//{
//    if (checked)
//    {
//       ui->dannieIdent->setEnabled(false);
//       ui->dannieNabl->setEnabled(false);
//    }
//}

//void datas::on_oscWithSpeed_toggled(bool checked)
//{
//    if (checked)
//    {
//       ui->dannieIdent->setEnabled(true);
//       ui->dannieNabl->setEnabled(false);
//    }
//}

//void datas::on_internalDataSource_toggled(bool checked)
//{
//    if (checked)
//    {
//       ui->dannieIdent->setEnabled(false);
//       ui->dannieNabl->setEnabled(false);
//    }
//}

//void datas::on_ReadNabl_toggled(bool checked)
//{
//    if (checked)
//    {
//       ui->dannieIdent->setEnabled(false);
//       ui->dannieNabl->setEnabled(true);
//    }
//}

//void datas::on_radioButton_4_toggled(bool checked)
//{
//    if (checked)
//    {
//       ui->dannieIdent->setEnabled(false);
//       ui->dannieNabl->setEnabled(false);
//    }
//}

