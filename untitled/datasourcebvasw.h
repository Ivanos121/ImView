#ifndef DATASOURCEBVASW_H
#define DATASOURCEBVASW_H

#include <QWidget>
#include <QTimer>

class DataSourceBVASw: public QObject
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
