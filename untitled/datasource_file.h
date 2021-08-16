#ifndef DATASOURCE_FILE_H
#define DATASOURCE_FILE_H

#include <QWidget>
#include <QTimer>
#include "datasource.h"
#include "mainwindow.h"

class DataSource_file : public DataSource
{
    Q_OBJECT
public:
    DataSource_file();
    void init();
    void stop();

    QTimer *dataTimer;

    double getUa() {return ua;};
    double getUb() {return ub;};
    double getIa() {return ia;};
    double getIb() {return ib;};
    double getW() {return w;};

private:
    double ua,ub,ia,ib,w;

public slots:
    void read();

};

#endif // DATASOURCE_FILE_H
