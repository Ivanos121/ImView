#ifndef DATASOURCEBVAS_H
#define DATASOURCEBVAS_H

#include <QTimer>
#include <QWidget>
#include <QThread>
#include "datasource.h"
#include "device.h"

class BVASThread;

class DataSourceBVAS: public DataSource
{
    Q_OBJECT
public:
    DataSourceBVAS();
    void init();
    void stop();

    BVASThread *bvasThread;
    Device *bvasDevice;

    double* getUa() {return Ua;};
    double* getUb() {return Ub;};
    double* getUc() {return Uc;};
    double* getIa() {return Ia;};
    double* getIb() {return Ib;};
    double* getIc() {return Ic;};
    double* getW() {return nullptr;};

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

private:
    double Ua[BUF_SIZE];
    double Ub[BUF_SIZE];
    double Uc[BUF_SIZE];

    double Ia[BUF_SIZE];
    double Ib[BUF_SIZE];
    double Ic[BUF_SIZE];

public slots:
    void read();

};

#endif // DATASOURCEBVAS_H

