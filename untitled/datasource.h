#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>

class DataSource : public QObject
{
    Q_OBJECT
public:
    DataSource();

    virtual double* getUa() {return nullptr;};
    virtual double* getUb() {return nullptr;};
    virtual double* getUc() {return nullptr;};
    virtual double* getIa() {return nullptr;};
    virtual double* getIb() {return nullptr;};
    virtual double* getIc() {return nullptr;};
    virtual double* getW() {return nullptr;};

    virtual void init() {};
    virtual void stop() {};

signals:
    void ready();
};

#endif // DATASOURCE_H
