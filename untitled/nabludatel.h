#ifndef NABLUDATEL_H
#define NABLUDATEL_H

#include "datasourcebvas.h"

class ZeroCorrector
{
public:
    double u_prev=0, z_prev=0, z_int_prev=0, y_prev=0;
    double apply(double z, double K, double K1, double K2, double Ts);
};

class Nabludatel
{
public:
    double Ua, Ub, Uc, Ia, Ib, Ic, omega,sigma,alpha, beta, kk, Ts, t, M, Mc;
    double R1, L2, Lm, J, pn;
    double p_akt_a, p_akt_b, p_akt_c, p_akt, i_dev_a, i_dev_b, i_dev_c, u_dev_a, u_dev_b, u_dev_c,
    p_poln_a, p_poln_b, p_poln_c, p_poln, p_reakt_a, p_reakt_b, p_reakt_c=0, p_reakt, cos_f_a,
    cos_f_b, cos_f_c, cos_f;
    double a1,a2,a3,a4,a5,a6,b1,b2,g1,g2,g3,g4,k,cc,Kint,ba1,ba2,ba3,ba4,Kint1,kp,ki;
    double ma11,ma12,ma13,ma14,ma21,ma22,ma23,ma24,ma31,ma32,ma33,ma34,ma41,ma42,ma43,ma44;
    double w, w_prev,ua,ub,ia,ib,psi1a,psi1a_prev,psi1b,psi1b_prev,iaizm,iaizm_prev,ibizm,ibizm_prev,uaizm,uaizm_prev,ubizm,ubizm_prev,
    psi2a,psi2a_prev,psi2b,psi2b_prev,ia_prev,ib_prev;
    Nabludatel();
    void init(double _R1, double _R2, double _L1, double _L2, double _Lm);
    void rasch(DataSourceBVAS *dataSourceBVAS);

    ZeroCorrector uaCorrector;
    ZeroCorrector ubCorrector;
    ZeroCorrector iaCorrector;
    ZeroCorrector ibCorrector;

};



#endif // NABLUDATEL_H
