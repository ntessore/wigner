import numpy as np
import ctypes as ct
import numpy.ctypeslib as ctl
import os.path

dll = os.path.join(os.path.dirname(__file__), 'wigner_d.so')
lib = ct.cdll.LoadLibrary(dll)
lib.wigner_d.restype
lib.wigner_d.argtypes = [
    ct.c_int, ct.c_int, ct.c_int, ct.c_int, ct.c_double,
    ctl.ndpointer(dtype=ct.c_double, ndim=1, flags=('C', 'W'))
]

def wigner_d(lmin, lmax, m1, m2, theta):
    '''Wigner (little) d-function.

    Returns the Wigner (little) d-function for an array of l values and fixed
    m values and angle theta.
    '''
    d = np.empty(lmax-lmin+1, dtype=ct.c_double)
    lib.wigner_d(lmin, lmax, m1, m2, theta, d)
    return d
