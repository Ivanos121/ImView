#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QWidget>
#include <QTimer>
#include "mainwindow.h"

class DataSource : public QObject
{
    Q_OBJECT
public:
    DataSource();
    void init();
    void stop();

    void setMainWindow(MainWindow *_mainWindow);

    double ua,ub,ia,ib,w,X1_1,X2_1,X3_1,X4_1,X5_1;
    QTimer *dataTimer;

    MainWindow *mainWindow;

public slots:
    void read();

signals:
    void ready();
};

#endif // DATASOURCE_H
