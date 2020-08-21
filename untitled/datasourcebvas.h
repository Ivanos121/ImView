#ifndef DATASOURCEBVAS_H
#define DATASOURCEBVAS_H

#include <QTimer>
#include <QWidget>
#include <QThread>

#include "device.h"

class BVASThread;

class DataSourceBVAS: public QObject
{
    Q_OBJECT
public:
    DataSourceBVAS();
    void init();
    void stop();

    BVASThread *bvasThread;
    Device *bvasDevice;

    //double Ua, Ub, Uc, Ia, Ib, Ic;
    double Ua[BUF_SIZE];
    double Ub[BUF_SIZE];
    double Uc[BUF_SIZE];

    double Ia[BUF_SIZE];
    double Ib[BUF_SIZE];
    double Ic[BUF_SIZE];

    double UaZeroLevel;
    double UbZeroLevel;
    double UcZeroLevel;

    double IaZeroLevel;
    double IbZeroLevel;
    double IcZeroLevel;

    double UaCalibrationCoeff;
    double UbCalibrationCoeff;
    double UcCalibrationCoeff;

    double IaCalibrationCoeff;
    double IbCalibrationCoeff;
    double IcCalibrationCoeff;

public slots:
    void read();

signals:
    void ready();

};

#endif // DATASOURCEBVAS_H

