#include "ui_mainwindow.h"
#include "datasource_file.h"
#include "ui_datas.h"
#include "mainwindow.h"
#include "base.h"
#include <fstream>
#include <QMessageBox>

std::ifstream fin;

DataSource_file::DataSource_file()
{
    dataTimer = new QTimer(this);
    connect(dataTimer, &QTimer::timeout, this, &DataSource_file::read);
}

void DataSource_file::init()
{
    fin.open(base.dataSourceFilename.toUtf8(),std::ios::in);
    if(!fin.is_open())
    {
        QMessageBox::critical(nullptr, "Ошибка!", "Не удалось открыть файл!");
        return;
    }
    double X1_1;
    fin >> X1_1>> ua >> ub >>ia >> ib >> w;
    dataTimer->start();
}

void DataSource_file::read()
{
    double X1_1;
    fin >> X1_1 >> ua >> ub >>ia >> ib >> w;

    emit ready();
}

void DataSource_file::stop()
{
    dataTimer->stop();
    fin.close();
}

