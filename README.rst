======
wigner
======

*Functions for rotations: Wigner D-matrix, 3j-symbols, more as needed.*

A collection of fast numerical routines in C to compute functions associated
with rotations and statistics on the sphere. Hand-coded and dependency-free
Python interfaces are provided.

`Interfaces`_:

- `C`_
- `Python`_

`Functions`_:

- `Wigner D-matrix`_
- `Wigner 3j-symbols`_


Interfaces
==========

C
-


Python
------

Install with pip::

    $ pip install wigner

The ``wigner`` Python module contains low-level bindings to the C library
`functions`_ with minimal wrapping. ::

    >>> import wigner
    >>> wigner.wigner_3j_l(2, 3, -1, 2)
    (1.0, 5.0, [-0.308, -4.280e-17, 0.188, -0.197, 0.101])


Functions
=========

Wigner D-matrix
---------------

`wigner_d_l`_
  Compute the Wigner D-function for a range of ``l`` values.


``wigner_d_l``
~~~~~~~~~~~~~~

Code to compute the Wigner D-function for a range of ``l`` values and fixed
``m`` and angle, using the recurrence described in `arXiv:1904.09973`_. The
code is written in C and by default uses SSE intrinsics to speed up the
computation, although this can be turned off on compilation.


Wigner 3j-symbols
-----------------

`wigner_3j_l`_
  Evaluate the Wigner 3j-symbol for all allowed values of ``l1``.

`wigner_3j_m`_
  Evaluate the Wigner 3j-symbol for all allowed values of ``m2``.


``wigner_3j_l``
~~~~~~~~~~~~~~~

Evaluate the Wigner 3j-symbol ::

    f(l1) = ⎛  l1   l2 l3 ⎞
            ⎝-m2-m3 m2 m3 ⎠

for all allowed values of ``l1``, the other parameters being held fixed. The
code is a translation of the `SLATEC`_ function ``drc3jj`` to C.


``wigner_3j_m``
~~~~~~~~~~~~~~~

Evaluate the Wigner 3j-symbol ::

    g(m2) = ⎛ l1 l2   l3  ⎞
            ⎝ m1 m2 -m1-m2⎠

for all allowed values of ``m2``, the other parameters being held fixed. The
code is a translation of the `SLATEC`_ function ``drc3jm`` to C.


..
    References

.. _arXiv:1904.09973: https://arxiv.org/abs/1904.09973
.. _SLATEC: http://www.netlib.org/slatec
