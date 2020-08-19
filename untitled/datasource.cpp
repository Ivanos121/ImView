#include "ui_mainwindow.h"
#include "datasource.h"
#include "ui_datas.h"
#include "mainwindow.h"
#include "base.h"
#include <fstream>
#include <QMessageBox>

std::ifstream fin,fin2, fin3, fin4,fin5;

extern Base base;

DataSource::DataSource()
{
    dataTimer = new QTimer(this);
    connect(dataTimer, &QTimer::timeout, this, &DataSource::read);
}

void DataSource::init()
{
    auto uiDatasWindow = mainWindow->ui->widget->ui;

    if(uiDatasWindow->radioButton_2->isChecked())
    {
        fin.open(base.dataSourceFilename.toUtf8(),std::ios::in);
        if(!fin.is_open())
        {
            QMessageBox::critical(nullptr, "Ошибка!", "Не удалось открыть файл!");
            return;
        }
        fin >> X1_1>> ua >> ub >>ia >> ib >> w;
        dataTimer->start();
    }

    if(uiDatasWindow->radioButton->isChecked())
    {
        QMessageBox::information(nullptr,"Инфо","Осциллограф");
    }
}

void DataSource::read()
{
    auto uiDatasWindow = mainWindow->ui->widget->ui;

    if(uiDatasWindow->radioButton_2->isChecked())
    {
      /*  fin >> X1_1 >> ua;
        fin2 >> X2_1 >> ia;
        fin5 >> X5_1 >> ub;
        fin3 >> X3_1 >> ib;
        fin4 >> X4_1 >> w;
       // X4_1=0;
       // w=0; */
        fin >> X1_1>> ua >> ub >>ia >> ib >> w;

    }

    if(uiDatasWindow->radioButton->isChecked())
    {

    }

    emit ready();
}

void DataSource::stop()
{
    dataTimer->stop();
    fin.close();
    //fin2.close();
    //fin3.close();
    //fin4.close();
    //fin5.close();

}

void DataSource::setMainWindow(MainWindow *_mainWindow)
{
    mainWindow = _mainWindow;
}
