#ifndef MODEL_H
#define MODEL_H

#include "datasource.h"

class Model
{
public:
    Model();
    void init (double P_nom, double n_nom, double U_fnom,
               double cosf_nom, double kpd_nom, double muk, double n_0);
    void rasch(DataSource *dataSource);
    double R2,L,Lm;
    const double Ts=0.0001;
};

#endif // MODEL_H
