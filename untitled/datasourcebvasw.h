#ifndef DATASOURCEBVASW_H
#define DATASOURCEBVASW_H

#include <QWidget>
#include <QTimer>
#include "datasource.h"

class DataSourceBVASw: public DataSource
{
    Q_OBJECT
public:
    double w;
    DataSourceBVASw();
    void init();
    void read();
    QTimer *dataTimer;
};

#endif // DATASOURCEBVASW_H
