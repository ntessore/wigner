pywigner_d
==========

Python module to compute the Wigner (little) d-function for a range of `l`
values and fixed `m` values and angle `theta`, using the recurrence described in
[`arXiv:1904.09973`](https://arxiv.org/abs/1904.09973). The code is written in C
and by default uses SSE intrinsics to speed up the computation, although this
can be turned off on compilation.
