#ifndef BASE_H
#define BASE_H

#include <QString>

struct Base
{
    double P_nom;
    double n_nom;
    double U_fnom;
    double cosf_nom;
    double kpd_nom;
    double muk;
    double n_0;
    QString dataSourceFilename;
};

extern Base base;

#endif // BASE_H
