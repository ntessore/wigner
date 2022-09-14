***wigner*** package for Python
===============================

The ***wigner*** package for Python contains bindings to the *wigner* C library
for computing Wigner d functions and 3j symbols.

Functions are provided with minimal wrapping:

```py
>>> import wigner
>>> wigner.wigner_3jj(2, 3, -1, 2)
(1.0, 5.0, [-0.308, -4.280e-17, 0.188, -0.197, 0.101])
```


Installation
------------

The package can be installed with pip:

```console
$ pip install wigner
```

The only dependency is numpy.


Functions
---------

- [***legendre_pl***](#legendre_pl) – Legendre polynomial as function of *l*
- [***wigner_3jj***](#wigner_3jj) – Wigner 3j symbol as function of *l1*
- [***wigner_3jm***](#wigner_3jm) – Wigner 3j symbol as function of *m2*
- [***wigner_dl***](#wigner_dl) – Wigner d function as function of *l*


### legendre_pl

***legendre_pl**(lmin, lmax, x)*

Compute the Legendre polynomials *P_l(x)* for all degrees *l = lmin* to *l =
lmax*, with *x* being held fixed.  The arguments *lmin* and *lmax* must be
integers, while the argument *x* must be float.  Returns a numpy array of size
*lmax-lmin+1*.


### wigner_3jj

***wigner_3jj**(l2, l3, m2, m3)*

Evaluate the Wigner 3j symbol

    /   l1    l2  l3 \
    \ -m2-m3  m2  m3 /

for all allowable values of *l1*, with the other parameters held fixed.  For
physically meaningful outputs, the arguments must be integer or half-integer,
although other inputs are allowed.  Returns a tuple *l1min, l1max, thrcof*
where *l1min* and *l1max* are the smallest and largest allowable values of *l1*,
and *thrcof* is a numpy array of size *l1max-l1min+1* containing the values of
the 3j symbol.


### wigner_3jm

***wigner_3jm**(l1, l2, l3, m1)*

Evaluate the Wigner 3j symbol

    / l1  l2    l3  \
    \ m1  m2  -m1-m2/

for all allowable values of *m2*, with the other parameters held fixed.  For
physically meaningful outputs, the arguments must be integer or half-integer,
although other inputs are allowed.  Returns a tuple *m2min, m2max, thrcof* where
*m2min* and *m2max* are the smallest and largest allowable values of *m2*, and
*thrcof* is a numpy array of size *m2max-m2min+1* containing the values of the
3j symbol.


### wigner_dl

***wigner_dl**(lmin, lmax, m1, m2, theta)*

Compute the Wigner d function *d^l_{m1,m2}(theta)* for all degrees *l = lmin* to
*l = lmax*, with *m1*, *m2*, and *theta* being held fixed.  The arguments
*lmin*, *lmax*, *m1*, *m2* must be integers, and the angle *theta* must be given
in radian as float.  Returns a numpy array of size *lmax-lmin+1*.
