This repository contains a fast routine in C to compute the Wigner d-matrix for
a range of angular momentum values l and fixed m. This is done via a recurrence
in l, which is described in https://arxiv.org/abs/1904.09973.

To use the routine, simply copy the `wigner_d.c` source file into your project,
and let your code know about the new function by including the `wigner_d.h`
header, or by putting

    extern void wigner_d(int l0, int l1, int m, int k, double x, double* d);

near the top of your source.

Included here is a program `cl_to_xi` that converts power spectra C_l to the
two-point functions xi(theta) for generic spin-n random fields on the sphere.

    usage: cl_to_xi l0 l1 m1 m2 th0 th1 nth [file]
    
    Convert the modes C_l of a power spectrum to the two-point function. The
    values of m1 and m2 are the spins of the random fields, with signs (+,+) to
    obtain xi+, or signs (+,-) to get xi-. The two-point function is calculated
    for angles in the range [th0, th1] in degrees. The input power spectrum is
    read from file or stdin, and must be in the space-separated format "l C_l"
    in each row. The power spectrum is evaluated at the integers l0, ..., l1
    using linear interpolation.

An additional program to print the `wigner_d` function values is also included.

    usage: showdl l0 l1 m k theta
    
    Compute the Wigner d-matrix elements `d^l_{m,k}(theta)` for angular
    momentum l = l0, .., l1 and fixed values m, k, theta.

Both programs are compiled using `make`.
