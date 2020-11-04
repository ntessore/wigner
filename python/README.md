wigner
======

*Functions for rotations: Wigner D-matrix, 3j-symbols, more as needed.*

Install the module with pip:

    $ pip install wigner


Low-level functions
-------------------

The `wigner.c` Python module contains low-level bindings to the C functions
with minimal wrapping.

    >>> import wigner.c
    >>> wigner.c.wigner_3j_l(2, 3, -1, 2)
    (1.0, 5.0, [-0.308, -4.280e-17, 0.188, -0.197, 0.101])

The following functions are available:

- `wigner_d_l`
- `wigner_3j_l`
