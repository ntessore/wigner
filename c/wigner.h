#pragma once

void legendre_p(double x, int lmin, int lmax, double* p);

void wigner_d_l(int lmin, int lmax, int m1, int m2, double theta, double* d);

int wigner_3j_l(double l2, double l3, double m2, double m3, double* l1min,
                double* l1max, double* thrcof, int ndim);

int wigner_3j_m(double l1, double l2, double l3, double m1, double* m2min,
                double* m2max, double* thrcof, int ndim);
