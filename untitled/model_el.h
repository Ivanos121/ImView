#ifndef MODEL_EL_H
#define MODEL_EL_H

#include <QTimer>
#include "datasource.h"

class model_el : public QObject
{
    Q_OBJECT
public:
    model_el();
    double Ua, Ub, Ia, Ib,psi2a,psi2b,omega,sigma,alpha, beta, kk, Ts, t, M, Mc,w;
    double Ua_prev, Ub_prev, omega_prev, psi2a_prev, psi2b_prev, Ia_prev, Ib_prev;
    double R1, L2, Lm, J, pn;
    double tp, Tc, Mc_n, S;
    void init_el(double _R1,double _R2, double _L1, double _L2, double _Lm, int _S, double _tp, double _Tc, double _Mc);
    void rasch();

    void stop();

    QTimer timer;

public slots:
    void timerTimeout();

signals:
    void ready();
};

#endif // MODEL_EL_H
