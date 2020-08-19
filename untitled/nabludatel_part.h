#ifndef NABLUDATEL_PART_H
#define NABLUDATEL_PART_H

#include "datasourcebvasw.h"

class Nabludatel_part
{
public:
    double Ua, Ub, Ia,Ib,psi2a,psi2b,omega,sigma,alpha, beta, kk, Ts, t, M, Mc,w;
    double R1, L2, Lm, J, pn;
    Nabludatel_part();
    void init(double _R1, double _R2, double _L1, double _L2, double _Lm);
    void rasch(DataSourceBVASw *dataSourceBVASw);
};

#endif // NABLUDATEL_PART_H
