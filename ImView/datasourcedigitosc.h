#ifndef DATASOURCEDIGITOSC_H
#define DATASOURCEDIGITOSC_H

#include <QObject>
#include <QTimer>
#include <QWidget>
#include <QThread>

#include "datasource.h"
#include "devicedigitosc.h"

class DigitOscThread;

class DataSourceDigitOsc : public DataSource
{
    Q_OBJECT
public:
    DataSourceDigitOsc();

    void init();
    void stop();

    DigitOscThread *digitOscThread;
    DeviceDigitOsc *deviceDigitOsc;

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

public slots:
    void read();
    void bvasFailureSlot();

signals:
    void bvasFailure();
};

#endif // DATASOURCEDIGITOSC_H
