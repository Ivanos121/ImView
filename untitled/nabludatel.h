#ifndef NABLUDATEL_H
#define NABLUDATEL_H

#include "datasourcebvas.h"


class Nabludatel
{
public:
    double Ua, Ub, Uc, Ia, Ib, Ic, psi2a,psi2b,omega,sigma,alpha, beta, kk, Ts, t, M, Mc,w;
    double R1, L2, Lm, J, pn;
    double p_akt_a, p_akt_b, p_akt_c, p_akt, i_dev_a, i_dev_b, i_dev_c, u_dev_a, u_dev_b, u_dev_c,
    p_poln_a, p_poln_b, p_poln_c, p_poln, p_reakt_a, p_reakt_b, p_reakt_c=0, p_reakt, cos_f_a,
    cos_f_b, cos_f_c, cos_f;
    Nabludatel();
    void init(double _R1, double _R2, double _L1, double _L2, double _Lm);
    void rasch(DataSourceBVAS *dataSourceBVAS);

};

#endif // NABLUDATEL_H
