#pragma once

void legendre_pl(int lmin, int lmax, double x, double* p);

int wigner_3jj(double l2, double l3, double m2, double m3, double* l1min,
               double* l1max, double* thrcof, int ndim);

int wigner_3jm(double l1, double l2, double l3, double m1, double* m2min,
               double* m2max, double* thrcof, int ndim);

int wigner_6j(double l2, double l3, double l4, double l5, double l6,
              double* l1min, double* l1max, double* sixcof, int ndim);

void wigner_dl(int lmin, int lmax, int m1, int m2, double theta, double* d);
