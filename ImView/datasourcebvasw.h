#ifndef DATASOURCEBVASW_H
#define DATASOURCEBVASW_H

#include <QWidget>
#include <QTimer>
#include <QSerialPort>

#include "device.h"
#include "datasource.h"

class BVASThread;

class DataSourceBVASw: public DataSource
{
    Q_OBJECT
public:
    DataSourceBVASw();
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
    double* getW() {return w;};

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
    double w[BUF_SIZE];

    QSerialPort serialPort;

public slots:
    void read();
    void bvasFailureSlot();

signals:
    void bvasFailure();

};

#endif // DATASOURCEBVASW_H
