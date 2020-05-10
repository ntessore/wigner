pywigner_d
==========

Python module to compute the Wigner (little) d-function for a range of `l`
values and fixed `m` values and angle `theta`, using the recurrence described in
[`arXiv:1904.09973`](https://arxiv.org/abs/1904.09973). The code is written in C
and by default uses SSE intrinsics to speed up the computation, although this
can be turned off on compilation.

To use:

    $ # clone the repository
    $ git clone https://github.com/ntessore/pywigner_d.git
    $ cd pywigner_d
    $ # build the module in place
    $ python setup.py build_ext --inplace
    $ # run a simple test
    $ python test.py
    [0.         0.         0.9950104  0.98009768 0.96038789 0.93602817
     0.90720014 0.87411839 0.8370287  0.79620601 0.75195212]
