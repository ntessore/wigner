`wigner_d`
==========

Code to compute the Wigner D-function for a range of `l` values and fixed `m`
and angle, using the recurrence described in [`arXiv:1904.09973`]. The code is
written in C and by default uses SSE intrinsics to speed up the computation,
although this can be turned off on compilation. A Python interface without any
dependencies is provided.

[`arXiv:1904.09973`]: https://arxiv.org/abs/1904.09973

Interfaces:

- [C](c/)
- [Python](python/)
