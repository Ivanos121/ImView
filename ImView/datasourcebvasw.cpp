#include "datasourcebvasw.h"

DataSourceBVASw::DataSourceBVASw()
{
    dataTimer = new QTimer(this);
    connect(dataTimer, &QTimer::timeout, this, &DataSourceBVASw::read);

}

void DataSourceBVASw::init()
{
dataTimer->start();
}

void DataSourceBVASw::read()
{

}
