#include "ui_mainwindow.h"
#include "datasource_el.h"
#include "ui_datas.h"

datasource_el::datasource_el()
{
    dataTimer2 = new QTimer(this);
    connect(dataTimer2, &QTimer::timeout, this, &datasource_el::read_el);
}

void datasource_el::read_el()
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
 //       fin >> X1_1>> ua >> ub >>ia >> ib >> w;

    }

    if(uiDatasWindow->radioButton->isChecked())
    {

    }

    emit ready_el();
}

void datasource_el::stop_el()
{
    dataTimer2->stop();
//    fin.close();

}

void datasource_el::setMainWindow(MainWindow *_mainWindow)
{
    mainWindow = _mainWindow;
}

