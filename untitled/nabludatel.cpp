#include "nabludatel.h"
#include "base.h"
#include "math.h"

Nabludatel::Nabludatel()
{

}

void Nabludatel::init(double _R1, double _R2, double _L1, double _L2, double _Lm)
{
    R1=_R1;
    double R2 = _R2;
    double L1 = _L1;
    L2 = _L2;
    Lm = _Lm;

    sigma=L1-((Lm*Lm)/(L2));
    alpha=R2/L2;
    beta=Lm/(sigma*L2);
    pn=2;
    J=0.01;
    Ia=0;
    Ib=0;
    psi2a=0;
    psi2b=0;
    omega=0;
    Ua=0;
    Ub=0;
    t=0;
    M=0;
    Mc=0;
    kk=1;
}

void Nabludatel::rasch(DataSourceBVAS *dataSourceBVAS)
{
    /*Ua = 0.0;
    Ub = 0.0;
    Uc = 0.0;

    Ia = 0.0;
    Ib = 0.0;
    Ic = 0.0;

    for (int i = 0; i < BUF_SIZE; i++)
    {
      Ua += dataSourceBVAS->Ua[i];
      Ub += dataSourceBVAS->Ub[i];
      Uc += dataSourceBVAS->Uc[i];

      Ia += dataSourceBVAS->Ia[i];
      Ib += dataSourceBVAS->Ib[i];
      Ic += dataSourceBVAS->Ic[i];
    }

    Ua /= BUF_SIZE;
    Ub /= BUF_SIZE;
    Uc /= BUF_SIZE;

    Ia /= BUF_SIZE;
    Ib /= BUF_SIZE;
    Ic /= BUF_SIZE;

    M = 10.0;
    w = 20.0; */

    p_akt_a = 0.0;
    p_akt_b = 0.0;
    p_akt_c = 0.0;
    p_akt=0.0;
    i_dev_a=0.0;
    i_dev_b=0.0;
    i_dev_c=0.0;
    u_dev_a=0.0;
    u_dev_b=0.0;
    u_dev_c=0.0;
    p_poln_a=0.0;
    p_poln_b=0.0;
    p_poln_c=0.0;
    p_poln=0.0;
    p_reakt_a=0;
    p_reakt_b=0;
    p_reakt_c=0;
    p_reakt=0;
    cos_f_a=0.0;
    cos_f_b=0.0;
    cos_f_c=0.0;
    cos_f=0.0;

    //Расчет массивов
    for (int i=0; i<BUF_SIZE; i++)
    {
        p_akt_a += dataSourceBVAS->Ua[i]*dataSourceBVAS->Ia[i];
        p_akt_b += dataSourceBVAS->Ub[i]*dataSourceBVAS->Ib[i];;
        p_akt_c += dataSourceBVAS->Uc[i]*dataSourceBVAS->Ic[i];;
        i_dev_a += pow(dataSourceBVAS->Ia[i],2);
        i_dev_b += pow(dataSourceBVAS->Ib[i],2);
        i_dev_c += pow(dataSourceBVAS->Ic[i],2);
        u_dev_a += pow(dataSourceBVAS->Ua[i],2);
        u_dev_b += pow(dataSourceBVAS->Ub[i],2);
        u_dev_c += pow(dataSourceBVAS->Uc[i],2);
    }

    //Расчет активных мощностей
    p_akt_a /= BUF_SIZE;
    p_akt_b /= BUF_SIZE;
    p_akt_c /= BUF_SIZE;

    //Расчет действующих значений токов
    i_dev_a /= BUF_SIZE;
    i_dev_a = sqrt(i_dev_a);
    i_dev_b /= BUF_SIZE;
    i_dev_b = sqrt(i_dev_b);
    i_dev_c /= BUF_SIZE;
    i_dev_c = sqrt(i_dev_c);

    //Расчет действующих значений напряжений
    u_dev_a /= BUF_SIZE;
    u_dev_a = sqrt(u_dev_a);
    u_dev_b /= BUF_SIZE;
    u_dev_b = sqrt(u_dev_b);
    u_dev_c /= BUF_SIZE;
    u_dev_c = sqrt(u_dev_c);

    //Расчет полных мощностей
    p_poln_a=i_dev_a*u_dev_a;
    p_poln_b=i_dev_a*u_dev_b;
    p_poln_c=i_dev_a*u_dev_c;

    //расчет реактивных мощностей
    p_reakt_a=sqrt(pow(p_poln_a,2)-pow(p_akt_a,2));
    p_reakt_b=sqrt(pow(p_poln_b,2)-pow(p_akt_b,2));
    p_reakt_c=sqrt(pow(p_poln_c,2)-pow(p_akt_c,2));

    //Расчет активных мощностей
    p_akt=p_akt_a+p_akt_b+p_akt_c;
    p_poln=p_poln_a+p_poln_b+p_poln_c;
    p_reakt=sqrt(pow(p_poln,2)-pow(p_akt,2));

    //Расчет коэффициентов мощности
    cos_f_a=p_akt_a/p_poln_a;
    cos_f_b=p_akt_b/p_poln_b;
    cos_f_c=p_akt_c/p_poln_c;
    cos_f=p_akt/p_poln;
}
