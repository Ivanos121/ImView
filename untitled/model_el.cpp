#include "model_el.h"
#include <fstream>
#include <cmath>



model_el::model_el()
{
    connect(&timer, &QTimer::timeout, this, &model_el::timerTimeout);
}

void model_el::init_el(double _R1, double _R2, double _L1, double _L2, double _Lm)
{

    double L1 = _L1;
    R1 = _R1;
    double R2 = _R2;
    L2 = _L2;
    Lm = _Lm;

    sigma=L1-((Lm*Lm)/(L2));
    alpha=R2/L2;
    beta=Lm/(sigma*L2);
    pn=2;
    J=0.01;
    t=0;
    M=0;
    Mc=0;
    kk=1;
    Ua_prev = 0.0;
    Ub_prev = 0.0;
    omega_prev = 0.0;
    psi2a_prev = 0.0;
    psi2b_prev = 0.0;
    Ia_prev = 0.0;
    Ib_prev = 0.0;

    timer.start();
}

void model_el::rasch()
{
    double Ts=0.000032;
    t=t+Ts;
    Ua=311*sin(314*t);
    Ub=311*sin(314*t-M_PI/2);
    Ia=((((4*pow(Ts,2)*beta*psi2a_prev+4*pow(Ts,2)*Ia_prev)*pow(omega,2)+4*pow(Ts,2)*beta*omega_prev*psi2a_prev*omega)*pow(kk,2)*pow(pn,2)+((((4*Lm*pow(Ts,2)*alpha*pow(beta,2)-4*pow(Ts,2)*alpha*beta)*psi2b_prev+8*Lm*pow(Ts,2)*alpha*beta*Ib_prev)*omega+(4*Lm*pow(Ts,2)*alpha*pow(beta,2)+4*pow(Ts,2)*alpha*beta)*omega_prev*psi2b_prev)*pow(kk,2)+(8*Ts*beta*psi2b_prev*omega+8*Ts*beta*omega_prev*psi2b_prev)*kk)*pn+((8*Lm*pow(Ts,2)*pow(alpha,2)*pow(beta,2)+8*pow(Ts,2)*pow(alpha,2)*beta)*psi2a_prev+(4*pow(Ts,2)*pow(alpha,2)-4*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*pow(beta,2))*Ia_prev)*pow(kk,2)+(16*Ts*alpha*beta*psi2a_prev+16*Ts*alpha*Ia_prev)*kk+16*Ia_prev)*pow(sigma,2)+((2*pow(Ts,3)*pow(omega,2)*Ua+(2*pow(Ts,3)*Ua_prev+2*R1*pow(Ts,3)*beta*psi2a_prev)*pow(omega,2)+2*R1*pow(Ts,3)*beta*omega_prev*psi2a_prev*omega)*pow(kk,3)*pow(pn,2)+((omega*(Lm*pow(Ts,3)*alpha*beta*(2*Ub+2*Ub_prev)-2*R1*pow(Ts,3)*alpha*beta*psi2b_prev)+2*R1*pow(Ts,3)*alpha*beta*omega_prev*psi2b_prev)*pow(kk,3)+(4*R1*pow(Ts,2)*beta*psi2b_prev*omega+4*R1*pow(Ts,2)*beta*omega_prev*psi2b_prev)*pow(kk,2))*pn+((2*Lm*pow(Ts,3)*pow(alpha,2)*beta+2*pow(Ts,3)*pow(alpha,2))*Ua+(2*Lm*pow(Ts,3)*pow(alpha,2)*beta+2*pow(Ts,3)*pow(alpha,2))*Ua_prev+4*R1*pow(Ts,3)*pow(alpha,2)*beta*psi2a_prev-4*Lm*R1*pow(Ts,3)*pow(alpha,2)*beta*Ia_prev)*pow(kk,3)+((4*Lm*pow(Ts,2)*alpha*beta+8*pow(Ts,2)*alpha)*Ua+(4*Lm*pow(Ts,2)*alpha*beta+8*pow(Ts,2)*alpha)*Ua_prev+8*R1*pow(Ts,2)*alpha*beta*psi2a_prev-8*Lm*R1*pow(Ts,2)*alpha*beta*Ia_prev)*pow(kk,2)+(8*Ts*Ua+8*Ts*Ua_prev)*kk)*sigma+(R1*pow(Ts,4)*pow(omega,2)*Ua+(R1*pow(Ts,4)*Ua_prev-pow(R1,2)*pow(Ts,4)*Ia_prev)*pow(omega,2))*pow(kk,4)*pow(pn,2)+(R1*pow(Ts,4)*pow(alpha,2)*Ua+R1*pow(Ts,4)*pow(alpha,2)*Ua_prev-pow(R1,2)*pow(Ts,4)*pow(alpha,2)*Ia_prev)*pow(kk,4)+(4*R1*pow(Ts,3)*alpha*Ua+4*R1*pow(Ts,3)*alpha*Ua_prev-4*pow(R1,2)*pow(Ts,3)*alpha*Ia_prev)*pow(kk,3)+(4*R1*pow(Ts,2)*Ua+4*R1*pow(Ts,2)*Ua_prev-4*pow(R1,2)*pow(Ts,2)*Ia_prev)*pow(kk,2))/((4*pow(Ts,2)*pow(omega,2)*pow(kk,2)*pow(pn,2)+(4*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*pow(beta,2)+8*Lm*pow(Ts,2)*pow(alpha,2)*beta+4*pow(Ts,2)*pow(alpha,2))*pow(kk,2)+(16*Lm*Ts*alpha*beta+16*Ts*alpha)*kk+16)*pow(sigma,2)+(4*R1*pow(Ts,3)*pow(omega,2)*pow(kk,3)*pow(pn,2)+(4*Lm*R1*pow(Ts,3)*pow(alpha,2)*beta+4*R1*pow(Ts,3)*pow(alpha,2))*pow(kk,3)+(8*Lm*R1*pow(Ts,2)*alpha*beta+16*R1*pow(Ts,2)*alpha)*pow(kk,2)+16*R1*Ts*kk)*sigma+pow(R1,2)*pow(Ts,4)*pow(omega,2)*pow(kk,4)*pow(pn,2)+pow(R1,2)*pow(Ts,4)*pow(alpha,2)*pow(kk,4)+4*pow(R1,2)*pow(Ts,3)*alpha*pow(kk,3)+4*pow(R1,2)*pow(Ts,2)*pow(kk,2));
    Ib=((((4*pow(Ts,2)*beta*psi2b_prev+4*pow(Ts,2)*Ib_prev)*pow(omega,2)+4*pow(Ts,2)*beta*omega_prev*psi2b_prev*omega)*pow(kk,2)*pow(pn,2)+((((4*pow(Ts,2)*alpha*beta-4*Lm*pow(Ts,2)*alpha*pow(beta,2))*psi2a_prev-8*Lm*pow(Ts,2)*alpha*beta*Ia_prev)*omega+(-4*Lm*pow(Ts,2)*alpha*pow(beta,2)-4*pow(Ts,2)*alpha*beta)*omega_prev*psi2a_prev)*pow(kk,2)+(-8*Ts*beta*psi2a_prev*omega-8*Ts*beta*omega_prev*psi2a_prev)*kk)*pn+((8*Lm*pow(Ts,2)*pow(alpha,2)*pow(beta,2)+8*pow(Ts,2)*pow(alpha,2)*beta)*psi2b_prev-4*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*pow(beta,2)*Ib_prev+4*pow(Ts,2)*pow(alpha,2)*Ib_prev)*pow(kk,2)+(16*Ts*alpha*beta*psi2b_prev+16*Ts*alpha*Ib_prev)*kk+16*Ib_prev)*pow(sigma,2)+((pow(omega,2)*(pow(Ts,3)*(2*Ub+2*Ub_prev)+2*R1*pow(Ts,3)*beta*psi2b_prev)+2*R1*pow(Ts,3)*beta*omega_prev*psi2b_prev*omega)*pow(kk,3)*pow(pn,2)+((-2*Lm*pow(Ts,3)*alpha*beta*omega*Ua+(2*R1*pow(Ts,3)*alpha*beta*psi2a_prev-2*Lm*pow(Ts,3)*alpha*beta*Ua_prev)*omega-2*R1*pow(Ts,3)*alpha*beta*omega_prev*psi2a_prev)*pow(kk,3)+(-4*R1*pow(Ts,2)*beta*psi2a_prev*omega-4*R1*pow(Ts,2)*beta*omega_prev*psi2a_prev)*pow(kk,2))*pn+(pow(Ts,3)*pow(alpha,2)*beta*(Lm*(2*Ub+2*Ub_prev)-4*Lm*R1*Ib_prev)+pow(Ts,3)*pow(alpha,2)*(2*Ub+2*Ub_prev)+4*R1*pow(Ts,3)*pow(alpha,2)*beta*psi2b_prev)*pow(kk,3)+(pow(Ts,2)*alpha*beta*(Lm*(4*Ub+4*Ub_prev)-8*Lm*R1*Ib_prev)+pow(Ts,2)*alpha*(8*Ub+8*Ub_prev)+8*R1*pow(Ts,2)*alpha*beta*psi2b_prev)*pow(kk,2)+Ts*(8*Ub+8*Ub_prev)*kk)*sigma+pow(Ts,4)*pow(omega,2)*(R1*(Ub+Ub_prev)-pow(R1,2)*Ib_prev)*pow(kk,4)*pow(pn,2)+pow(Ts,4)*pow(alpha,2)*(R1*(Ub+Ub_prev)-pow(R1,2)*Ib_prev)*pow(kk,4)+pow(Ts,3)*alpha*(R1*(4*Ub+4*Ub_prev)-4*pow(R1,2)*Ib_prev)*pow(kk,3)+pow(Ts,2)*(R1*(4*Ub+4*Ub_prev)-4*pow(R1,2)*Ib_prev)*pow(kk,2))/((4*pow(Ts,2)*pow(omega,2)*pow(kk,2)*pow(pn,2)+(4*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*pow(beta,2)+8*Lm*pow(Ts,2)*pow(alpha,2)*beta+4*pow(Ts,2)*pow(alpha,2))*pow(kk,2)+(16*Lm*Ts*alpha*beta+16*Ts*alpha)*kk+16)*pow(sigma,2)+(4*R1*pow(Ts,3)*pow(omega,2)*pow(kk,3)*pow(pn,2)+(4*Lm*R1*pow(Ts,3)*pow(alpha,2)*beta+4*R1*pow(Ts,3)*pow(alpha,2))*pow(kk,3)+(8*Lm*R1*pow(Ts,2)*alpha*beta+16*R1*pow(Ts,2)*alpha)*pow(kk,2)+16*R1*Ts*kk)*sigma+pow(R1,2)*pow(Ts,4)*pow(omega,2)*pow(kk,4)*pow(pn,2)+pow(R1,2)*pow(Ts,4)*pow(alpha,2)*pow(kk,4)+4*pow(R1,2)*pow(Ts,3)*alpha*pow(kk,3)+4*pow(R1,2)*pow(Ts,2)*pow(kk,2));
    psi2a=-((4*pow(Ts,2)*omega_prev*psi2a_prev*omega*pow(kk,2)*pow(pn,2)+((((4*Lm*pow(Ts,2)*alpha*beta-4*pow(Ts,2)*alpha)*psi2b_prev+8*Lm*pow(Ts,2)*alpha*Ib_prev)*omega+(4*Lm*pow(Ts,2)*alpha*beta+4*pow(Ts,2)*alpha)*omega_prev*psi2b_prev)*pow(kk,2)+(8*Ts*psi2b_prev*omega+8*Ts*omega_prev*psi2b_prev)*kk)*pn+((4*pow(Ts,2)*pow(alpha,2)-4*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*pow(beta,2))*psi2a_prev+(-8*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*beta-8*Lm*pow(Ts,2)*pow(alpha,2))*Ia_prev)*pow(kk,2)+(-16*Lm*Ts*alpha*beta*psi2a_prev-16*Lm*Ts*alpha*Ia_prev)*kk-16*psi2a_prev)*pow(sigma,2)+(4*R1*pow(Ts,3)*omega_prev*psi2a_prev*omega*pow(kk,3)*pow(pn,2)+((omega*(pow(Ts,3)*alpha*(Lm*(2*Ub+2*Ub_prev)+4*Lm*R1*Ib_prev)+(2*Lm*R1*pow(Ts,3)*alpha*beta-4*R1*pow(Ts,3)*alpha)*psi2b_prev)+(2*Lm*R1*pow(Ts,3)*alpha*beta+4*R1*pow(Ts,3)*alpha)*omega_prev*psi2b_prev)*pow(kk,3)+(8*R1*pow(Ts,2)*psi2b_prev*omega+8*R1*pow(Ts,2)*omega_prev*psi2b_prev)*pow(kk,2))*pn+((-2*pow(Lm,2)*pow(Ts,3)*pow(alpha,2)*beta-2*Lm*pow(Ts,3)*pow(alpha,2))*Ua+(-2*pow(Lm,2)*pow(Ts,3)*pow(alpha,2)*beta-2*Lm*pow(Ts,3)*pow(alpha,2))*Ua_prev+4*R1*pow(Ts,3)*pow(alpha,2)*psi2a_prev-4*Lm*R1*pow(Ts,3)*pow(alpha,2)*Ia_prev)*pow(kk,3)+(-4*Lm*pow(Ts,2)*alpha*Ua-4*Lm*pow(Ts,2)*alpha*Ua_prev-8*Lm*R1*pow(Ts,2)*alpha*beta*psi2a_prev-8*Lm*R1*pow(Ts,2)*alpha*Ia_prev)*pow(kk,2)-16*R1*Ts*psi2a_prev*kk)*sigma+pow(R1,2)*pow(Ts,4)*omega_prev*psi2a_prev*omega*pow(kk,4)*pow(pn,2)+((omega*(Lm*R1*pow(Ts,4)*alpha*(Ub+Ub_prev)-pow(R1,2)*pow(Ts,4)*alpha*psi2b_prev)+pow(R1,2)*pow(Ts,4)*alpha*omega_prev*psi2b_prev)*pow(kk,4)+(2*pow(R1,2)*pow(Ts,3)*psi2b_prev*omega+2*pow(R1,2)*pow(Ts,3)*omega_prev*psi2b_prev)*pow(kk,3))*pn+(-Lm*R1*pow(Ts,4)*pow(alpha,2)*Ua-Lm*R1*pow(Ts,4)*pow(alpha,2)*Ua_prev+pow(R1,2)*pow(Ts,4)*pow(alpha,2)*psi2a_prev)*pow(kk,4)+(-2*Lm*R1*pow(Ts,3)*alpha*Ua-2*Lm*R1*pow(Ts,3)*alpha*Ua_prev)*pow(kk,3)-4*pow(R1,2)*pow(Ts,2)*psi2a_prev*pow(kk,2))/((4*pow(Ts,2)*pow(omega,2)*pow(kk,2)*pow(pn,2)+(4*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*pow(beta,2)+8*Lm*pow(Ts,2)*pow(alpha,2)*beta+4*pow(Ts,2)*pow(alpha,2))*pow(kk,2)+(16*Lm*Ts*alpha*beta+16*Ts*alpha)*kk+16)*pow(sigma,2)+(4*R1*pow(Ts,3)*pow(omega,2)*pow(kk,3)*pow(pn,2)+(4*Lm*R1*pow(Ts,3)*pow(alpha,2)*beta+4*R1*pow(Ts,3)*pow(alpha,2))*pow(kk,3)+(8*Lm*R1*pow(Ts,2)*alpha*beta+16*R1*pow(Ts,2)*alpha)*pow(kk,2)+16*R1*Ts*kk)*sigma+pow(R1,2)*pow(Ts,4)*pow(omega,2)*pow(kk,4)*pow(pn,2)+pow(R1,2)*pow(Ts,4)*pow(alpha,2)*pow(kk,4)+4*pow(R1,2)*pow(Ts,3)*alpha*pow(kk,3)+4*pow(R1,2)*pow(Ts,2)*pow(kk,2));
    psi2b=-((4*pow(Ts,2)*omega_prev*psi2b_prev*omega*pow(kk,2)*pow(pn,2)+((((4*pow(Ts,2)*alpha-4*Lm*pow(Ts,2)*alpha*beta)*psi2a_prev-8*Lm*pow(Ts,2)*alpha*Ia_prev)*omega+(-4*Lm*pow(Ts,2)*alpha*beta-4*pow(Ts,2)*alpha)*omega_prev*psi2a_prev)*pow(kk,2)+(-8*Ts*psi2a_prev*omega-8*Ts*omega_prev*psi2a_prev)*kk)*pn+((4*pow(Ts,2)*pow(alpha,2)-4*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*pow(beta,2))*psi2b_prev-8*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*beta*Ib_prev-8*Lm*pow(Ts,2)*pow(alpha,2)*Ib_prev)*pow(kk,2)+(-16*Lm*Ts*alpha*beta*psi2b_prev-16*Lm*Ts*alpha*Ib_prev)*kk-16*psi2b_prev)*pow(sigma,2)+(4*R1*pow(Ts,3)*omega_prev*psi2b_prev*omega*pow(kk,3)*pow(pn,2)+((-2*Lm*pow(Ts,3)*alpha*omega*Ua+(-2*Lm*pow(Ts,3)*alpha*Ua_prev+(4*R1*pow(Ts,3)*alpha-2*Lm*R1*pow(Ts,3)*alpha*beta)*psi2a_prev-4*Lm*R1*pow(Ts,3)*alpha*Ia_prev)*omega+(-2*Lm*R1*pow(Ts,3)*alpha*beta-4*R1*pow(Ts,3)*alpha)*omega_prev*psi2a_prev)*pow(kk,3)+(-8*R1*pow(Ts,2)*psi2a_prev*omega-8*R1*pow(Ts,2)*omega_prev*psi2a_prev)*pow(kk,2))*pn+(pow(Lm,2)*pow(Ts,3)*pow(alpha,2)*beta*(-2*Ub-2*Ub_prev)+pow(Ts,3)*pow(alpha,2)*(Lm*(-2*Ub-2*Ub_prev)-4*Lm*R1*Ib_prev)+4*R1*pow(Ts,3)*pow(alpha,2)*psi2b_prev)*pow(kk,3)+(pow(Ts,2)*alpha*(Lm*(-4*Ub-4*Ub_prev)-8*Lm*R1*Ib_prev)-8*Lm*R1*pow(Ts,2)*alpha*beta*psi2b_prev)*pow(kk,2)-16*R1*Ts*psi2b_prev*kk)*sigma+pow(R1,2)*pow(Ts,4)*omega_prev*psi2b_prev*omega*pow(kk,4)*pow(pn,2)+((-Lm*R1*pow(Ts,4)*alpha*omega*Ua+(pow(R1,2)*pow(Ts,4)*alpha*psi2a_prev-Lm*R1*pow(Ts,4)*alpha*Ua_prev)*omega-pow(R1,2)*pow(Ts,4)*alpha*omega_prev*psi2a_prev)*pow(kk,4)+(-2*pow(R1,2)*pow(Ts,3)*psi2a_prev*omega-2*pow(R1,2)*pow(Ts,3)*omega_prev*psi2a_prev)*pow(kk,3))*pn+(Lm*R1*pow(Ts,4)*pow(alpha,2)*(-Ub-Ub_prev)+pow(R1,2)*pow(Ts,4)*pow(alpha,2)*psi2b_prev)*pow(kk,4)+Lm*R1*pow(Ts,3)*alpha*(-2*Ub-2*Ub_prev)*pow(kk,3)-4*pow(R1,2)*pow(Ts,2)*psi2b_prev*pow(kk,2))/((4*pow(Ts,2)*pow(omega,2)*pow(kk,2)*pow(pn,2)+(4*pow(Lm,2)*pow(Ts,2)*pow(alpha,2)*pow(beta,2)+8*Lm*pow(Ts,2)*pow(alpha,2)*beta+4*pow(Ts,2)*pow(alpha,2))*pow(kk,2)+(16*Lm*Ts*alpha*beta+16*Ts*alpha)*kk+16)*pow(sigma,2)+(4*R1*pow(Ts,3)*pow(omega,2)*pow(kk,3)*pow(pn,2)+(4*Lm*R1*pow(Ts,3)*pow(alpha,2)*beta+4*R1*pow(Ts,3)*pow(alpha,2))*pow(kk,3)+(8*Lm*R1*pow(Ts,2)*alpha*beta+16*R1*pow(Ts,2)*alpha)*pow(kk,2)+16*R1*Ts*kk)*sigma+pow(R1,2)*pow(Ts,4)*pow(omega,2)*pow(kk,4)*pow(pn,2)+pow(R1,2)*pow(Ts,4)*pow(alpha,2)*pow(kk,4)+4*pow(R1,2)*pow(Ts,3)*alpha*pow(kk,3)+4*pow(R1,2)*pow(Ts,2)*pow(kk,2));
    omega=omega_prev+0.5*kk*Ts*(1.5*Lm*pn*(-psi2b*Ia+Ib*psi2a)/L2-Mc)/J+0.5*kk*Ts*(1.5*Lm*pn*(-psi2b_prev*Ia_prev+Ib_prev*psi2a_prev)/L2-Mc)/J;
    M = (3/2)*Lm*pn*(-psi2b*Ia+Ib*psi2a)/L2;

    printf("t=%f Ua=%f Ub=%f Ia=%f Ib=%f M=%f omega=%f\n", t, Ua, Ub, Ia, Ib, M, omega);

    Ua_prev = Ua;
    Ub_prev = Ub;
    omega_prev = omega;
    psi2a_prev = psi2a;
    psi2b_prev = psi2b;
    Ia_prev = Ia;
    Ib_prev = Ib;
}

void model_el::timerTimeout()
{
    emit ready();
}

void model_el::stop()
{
    timer.stop();
}
