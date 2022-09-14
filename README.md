wigner
======

A collection of fast numerical routines in C to compute functions associated
with statistics on the sphere.  Handmade Python interfaces that only require
numpy are also provided.


Functions
---------

- [***legendre_pl***](#legendre_pl) – Legendre polynomial as function of *l*
- [***wigner_3jj***](#wigner_3jj) – Wigner 3j symbol as function of *l1*
- [***wigner_3jm***](#wigner_3jm) – Wigner 3j symbol as function of *m2*
- [***wigner_dl***](#wigner_dl) – Wigner d function as function of *l*


### legendre_pl

*void **legendre_pl**(int lmin, int lmax, double x, double\* p)*
[[source]](src/wigner_dl.c)

Compute the Legendre polynomials *P_l(x)* for all degrees *l = lmin* to *l =
lmax*, with *x* being held fixed.  The results are stored in the array *p*,
which must have a size of at least *lmax-lmin+1*.

The code uses the well-known recurrence.  This is the special case *m1 = m2 = 0*
of [*wigner_dl*](#wigner_dl).


### wigner_3jj

*int **wigner_3jj**(double l2, double l3, double m2, double m3, double\* l1min,
                    double\* l1max, double\* thrcof, int ndim)*
[[source]](src/wigner_3jj.c)

Evaluate the Wigner 3j symbol

    /   l1    l2  l3 \
    \ -m2-m3  m2  m3 /

for all allowable values of *l1*, with the other parameters held fixed.  For
physically meaningful outputs, the arguments *l2*, *l3*, *m2*, *m3* must be
integer or half-integer, although other inputs are allowed.  On return, *l1min*
and *l1max* contain the smallest and largest allowable values of *l1*,
respectively.  The values of the 3j symbols are stored in the array pointed to
by *thrcof*.  Its allocated size is passed as *ndim*, which must be at least
*l1max-l1min+1*.  If *thrcof* is *NULL*, the function returns after checking
the inputs and setting *l1min* and *l1max*, so that an array of appropriate size
can be allocated.  The function returns an error flag:

- *0* if no errors,
- *1* if either *l2 < abs(m2)* or *l3 < abs(m3)*,
- *2* if either *l2+abs(m2)* or *l3+abs(m3)* non-integer,
- *3* if *l1max-l1min* not an integer,
- *4* if *l1max* less than *l1min*,
- *5* if *ndim* less than *l1max-l1min+1*.

The code is a reimplementation of the [SLATEC] routine *drc3jj* in C.


### wigner_3jm

*int **wigner_3jm**(double l1, double l2, double l3, double m1, double\* m2min,
                    double\* m2max, double\* thrcof, int ndim)*
[[source]](src/wigner_3jm.c)

Evaluate the Wigner 3j symbol

    / l1  l2    l3   \
    \ m1  m2  -m1-m2 /

for all allowable values of *m2*, with the other parameters held fixed.  For
physically meaningful outputs, the arguments *l1*, *l2*, *l3*, *m1* must be
integer or half-integer, although other inputs are allowed.  On return, *m2min*
and *m2max* contain the smallest and largest allowable values of *m2*,
respectively.  The values of the 3j symbols are stored in the array pointed to
by *thrcof*.  Its allocated size is passed as *ndim*, which must be at least
*m2max-m2min+1*.  If *thrcof* is *NULL*, the function returns after checking
the inputs and setting *m2min* and *m2max*, so that an array of appropriate size
can be allocated.  The function returns an error flag:

- *0* if no errors,
- *1* if either *l1 < abs(m1)* or *l1+abs(m1)* non-integer,
- *2* if *abs(l1-l2) <= l3 <= l1+l2* not satisfied,
- *3* if *l1+l2+l3* not an integer,
- *4* if *m2max-m2min* not an integer,
- *5* if *m2max* less than *m2min*,
- *6* if *ndim* less than *m2max-m2min+1*.

The code is a reimplementation of the [SLATEC] routine *drc3jj* in C.


### wigner_dl

*void **wigner_dl**(int lmin, int lmax, int m1, int m2, double theta,
                    double\* d)*
[[source]](src/wigner_dl.c)

Compute the Wigner d functions *d^l_{m1, m2}(theta)* for all degrees *l = lmin*
to *l = lmax*, with *m1*, *m2*, and *theta* being held fixed.  The angle *theta*
is given in radian.  The results are stored in the array *d*, which must have a
size of at least *lmax-lmin+1*.

The code uses the recurrence described in *[arXiv:1904.09973]*.  By default, SSE
intrinsics are used to speed up the computation, if available, although this can
be turned off at compile time using *-DNOSSE*.


[arXiv:1904.09973]: https://arxiv.org/abs/1904.09973
[SLATEC]: http://www.netlib.org/slatec
