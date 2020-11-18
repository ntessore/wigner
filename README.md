wigner
======

*Functions for rotations: Wigner D-matrix, 3j-symbols, more as needed.*

A collection of fast numerical routines in C to compute functions associated
with rotations and statistics on the sphere. Hand-coded and dependency-free
Python interfaces are provided.

[Interfaces](#interfaces):

- [C](#c)
- [Python](#python)

[Functions](#functions):

- [Wigner D-matrix](#wigner-d-matrix)
- [Wigner 3j-symbols](#wigner-3j-symbols)


Interfaces
----------

## C

[Source](c/)


## Python

[Source](python/)

Install with pip:

    $ pip install wigner

The `wigner` Python module contains low-level bindings to the C library
[functions](#functions) with minimal wrapping.

    >>> import wigner
    >>> wigner.wigner_3j_l(2, 3, -1, 2)
    (1.0, 5.0, [-0.308, -4.280e-17, 0.188, -0.197, 0.101])


Functions
---------

### Wigner D-matrix

- [`wigner_d_l`](#wigner_d_l)
  compute the Wigner D-function for a range of `l` values


#### `wigner_d_l`

Code to compute the Wigner D-function for a range of `l` values and fixed `m`
and angle, using the recurrence described in [arXiv:1904.09973]. The code is
written in C and by default uses SSE intrinsics to speed up the computation,
although this can be turned off on compilation.


### Wigner 3j-symbols

- [`wigner_3j_l`](#wigner_3j_l)
  evaluate the Wigner 3j-symbol for all allowed values of `l1`
- [`wigner_3j_m`](#wigner_3j_m)
  evaluate the Wigner 3j-symbol for all allowed values of `m2`


#### `wigner_3j_l`

Evaluate the Wigner 3j-symbol

    f(l1) = ⎛  l1   l2 l3 ⎞
            ⎝-m2-m3 m2 m3 ⎠

for all allowed values of `l1`, the other parameters being held fixed. The code
is a translation of the [SLATEC] function `drc3jj` to C.


#### `wigner_3j_m`

Evaluate the Wigner 3j-symbol

    g(m2) = ⎛ l1 l2   l3  ⎞
            ⎝ m1 m2 -m1-m2⎠

for all allowed values of `m2`, the other parameters being held fixed. The code
is a translation of the [SLATEC] function `drc3jm` to C.


<!-- References -->

[arXiv:1904.09973]: https://arxiv.org/abs/1904.09973
[SLATEC]: http://www.netlib.org/slatec
