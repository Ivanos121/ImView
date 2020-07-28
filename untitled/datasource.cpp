#include "datasource.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <fstream>

std::ifstream fin,fin2, fin3, fin4,fin5;

DataSource::DataSource()
{
    dataTimer = new QTimer(this);
    connect(dataTimer, &QTimer::timeout, this, &DataSource::read);
}

void DataSource::init()
{
    Ui_MainWindow *uiMainWindow = mainWindow->ui;

    if(uiMainWindow->action_23->isChecked())
    {
      /*      // делаешь что нужно
        fin.open("/home/elf/Dropbox/Наблюдатель/injterfece/build-untitled-Desktop-Debug/datasource/uaa.txt",std::ios::in);
        fin >> X1_1 >> ua;

        fin5.open("/home/elf/Dropbox/Наблюдатель/injterfece/build-untitled-Desktop-Debug/datasource/ubb.txt",std::ios::in);
        fin5 >> X5_1 >> ub;

        fin2.open("/home/elf/Dropbox/Наблюдатель/injterfece/build-untitled-Desktop-Debug/datasource/iaa.txt",std::ios::in);
        fin2 >> X2_1 >> ia ;

        fin3.open("/home/elf/Dropbox/Наблюдатель/injterfece/build-untitled-Desktop-Debug/datasource/ibb.txt",std::ios::in);
        fin3 >> X3_1 >> ib ;

        fin4.open("/home/elf/Dropbox/Наблюдатель/injterfece/build-untitled-Desktop-Debug/datasource/ww.txt",std::ios::in);
        fin4 >> X4_1 >> w;
        //X4_1=0;
        //w=0;*/
        fin.open("/home/elf/Dropbox/Наблюдатель/injterfece/build-untitled-Desktop-Debug/datasource/isvh.txt",std::ios::in);
        fin >> X1_1>> ua >> ub >>ia >> ib >> w;
        dataTimer->start();
    }

    if(uiMainWindow->action_22->isChecked())
    {
        QMessageBox::information(nullptr,"Инфо","Осциллограф");
    }


}

void DataSource::read()
{
    Ui_MainWindow *uiMainWindow = mainWindow->ui;

    if(uiMainWindow->action_23->isChecked())
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

    if(uiMainWindow->action_23->isChecked())
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
