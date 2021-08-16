#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>

class DataSource : public QObject
{
    Q_OBJECT
public:
    DataSource();

    virtual double getUa() {return 0;};
    virtual double getUb() {return 0;};
    virtual double getIa() {return 0;};
    virtual double getIb() {return 0;};
    virtual double getW() {return 0;};

    virtual void init() {};
    virtual void stop() {};

signals:
    void ready();
};

#endif // DATASOURCE_H
