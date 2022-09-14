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
