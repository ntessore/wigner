wigner
======

*Functions for rotations: Wigner D-matrix, 3j-symbols, more as needed.*

Install the module with pip:

    $ pip install wigner


Wigner D-matrix
---------------

### `wigner_d_l`

Code to compute the Wigner D-function for a range of `l` values and fixed `m`
and angle, using the recurrence described in [`arXiv:1904.09973`].

Compute a number of Wigner D-function values:

    >>> from wigner import wigner_d_l

    >>> # compute d^l_{22}(0.1) for l = 0, ..., 10
    >>> wigner_d_l(0, 10, 2, 2, 0.1)
    [0.0, 0.0, 0.995010, 0.980097, 0.960387, 0.936028,
    0.907200, 0.874118, 0.837028, 0.796206, 0.751952]

    >>> # compute D^l_{22}(0.1, 0.2, 0.3) for l = 0, ..., 10
    >>> wigner_d_l(0, 10, 2, 2, (0.1, 0.2, 0.3))
    [0j, 0j, (0.682+0.703j), (0.642+0.661j), (0.589+0.606j), (0.526+0.542j),
    (0.455+0.469j), (0.378+0.389j), (0.297+0.305j), (0.213+0.220j),
    (0.131+0.135j)]

Documentation:

    wigner_d_l(lmin, lmax, m1, m2, angle, /)
        Wigner D-function for range l = lmin, ..., lmax and m1, m2, angle
    [rad] fixed. If a single angle is given, the Wigner (little) d-function
    is computed, and a list of real numbers is returned. If a tuple (phi,
    theta, gamma) of angles is given, the Wigner (big) D-function is computed,
    and a list of complex numbers is returned. The given rotation in matrix
    form is R_z(phi)*R_y(theta)*R_z(gamma).

[`arXiv:1904.09973`]: https://arxiv.org/abs/1904.09973
