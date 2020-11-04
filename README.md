wigner
======

*Functions for rotations: Wigner D-matrix, 3j-symbols, more as needed.*

A collection of fast numerical routines in C to compute functions associated
with rotations and statistics on the sphere. Hand-coded and dependency-free
Python interfaces are provided.

Interfaces:

- [C](c/)
- [Python](python/)


Wigner D-matrix
---------------

### `wigner_d_l`

Code to compute the Wigner D-function for a range of `l` values and fixed `m`
and angle, using the recurrence described in [`arXiv:1904.09973`]. The code is
written in C and by default uses SSE intrinsics to speed up the computation,
although this can be turned off on compilation.

[`arXiv:1904.09973`]: https://arxiv.org/abs/1904.09973


Wigner 3j-symbols
-----------------

### `wigner_3j_l`

Evaluate the 3j symbol

    f(l1) = (  l1   l2 l3)
            (-m2-m3 m2 m3)

for all allowed values of `l1`, the other parameters being held fixed. The code
is a translation of the [SLATEC] function `drc3jj` to C.

[SLATEC]: http://www.netlib.org/slatec
