#ifndef BASE_TEPL_H
#define BASE_TEPL_H

#include <QString>

struct Base_tepl
{
double n;
double pn;
double h;
double D_c;
double l_sv_pr;
double l_cvv;
double sig_pr;
double z_c;
double h_c;
double sig_p;

double D_vent;
double D_a;
double D;
double l_p;
double Z_1;
double k_sh;
double b1;
double b2;
double h_p;
double k_z;

double h_sl1;
double b_sl1;
double h_z1;
double b_z;
double w_i;
double a;
double l_sr;
double l_lr;
double k_p;
double sig_okr;

double sig_ip;
double D_rot;
double Z_2;
double b_k;
double a_k;
double a_l;
double b_l;
double z_l;
double n_l;
double sig;

double nu;
double t_cp;
double lb_b;
double lb_m;
double lb_a;
double lb_c;
double d_b_iz;
double d_iz;
double k_pr;
double lb_p;

double lp_iz;
double D_vlch;
double lb_okr;
double lb_ip;
double sig_vp;
double h_z2;
double b_z2;
double D_dp;
double d;
double d1;

double h_z3;
double nu_l;
double t_p;
double m_i;
double n_el;
double gm_m;
double c_m;
double gm_c;
double c_ct;
double ro_m;

double P2;
double U1;
double n_u;
double cos_f;
double ro_al;
double D_kzk;
double k_obm;
double k_sk;
};
extern Base_tepl *base_tepl;
#endif // BASE_TEPL_H
