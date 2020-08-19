#include "nabludatel_part.h"
#include "base.h"

Nabludatel_part::Nabludatel_part()
{

}

void Nabludatel_part::init(double _R1, double _R2, double _L1, double _L2, double _Lm)
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

void Nabludatel_part::rasch(DataSourceBVASw *dataSourceBVASw)
{

}
