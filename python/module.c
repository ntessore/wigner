#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "wigner.h"

static PyObject* pywigner_d_l(PyObject* self, PyObject* args)
{
    int lmin, lmax, m1, m2, i, n;
    PyObject* angle;
    double phi, theta, gamma;
    double* d;
    PyObject* list;

    if(!PyArg_ParseTuple(args, "iiiiO", &lmin, &lmax, &m1, &m2, &angle))
        return NULL;

    if(PyFloat_Check(angle))
    {
        theta = PyFloat_AsDouble(angle);
        phi = gamma = HUGE_VAL;
    }
    else if(PyTuple_Check(angle))
    {
        Py_ssize_t nangle = PyTuple_Size(angle);
        if(nangle == 1)
        {
            if(!PyArg_ParseTuple(angle, "d", &theta))
                return NULL;
            phi = gamma = HUGE_VAL;
        }
        else if(nangle == 3)
        {
            if(!PyArg_ParseTuple(angle, "ddd", &phi, &theta, &gamma))
                return NULL;
        }
        else
        {
            PyErr_SetString(PyExc_TypeError, "requires 1 or 3 angles");
            return NULL;
        }
    }
    else
    {
        PyErr_SetString(PyExc_TypeError, "angle must be float or tuple");
        return NULL;
    }

    if(lmin < 0 || lmax < lmin)
    {
        PyErr_SetString(PyExc_ValueError, "requires 0 <= lmin <= lmax");
        return NULL;
    }

    n = lmax-lmin+1;
    d = malloc(n*sizeof(double));
    if(!d)
        return PyErr_NoMemory();

    wigner_d_l(lmin, lmax, m1, m2, theta, d);

    list = PyList_New(n);
    if(phi == HUGE_VAL)
    {
        for(i = 0; i < n; ++i)
            PyList_SetItem(list, i, PyFloat_FromDouble(d[i]));
    }
    else
    {
        const double a = m1*phi + m2*gamma;
        const double c = cos(a);
        const double s = sin(a);
        for(i = 0; i < n; ++i)
            PyList_SetItem(list, i, PyComplex_FromDoubles(c*d[i], s*d[i]));
    }

    free(d);

    return list;
}

static PyMethodDef methods[] = {
    {"wigner_d_l", pywigner_d_l, METH_VARARGS,
     "wigner_d_l(lmin, lmax, m1, m2, angle, /)\n--\n\nWigner D-function for "
     "range l = lmin, ..., lmax and m1, m2, angle [rad] fixed. If a single "
     "angle is given, the Wigner (little) d-function is computed, and a list "
     "of real numbers is returned. If a tuple (phi, theta, gamma) of angles "
     "is given, the Wigner (big) D-function is computed, and a list of complex "
     "numbers is returned. The rotation in matrix form is "
     "R_z(phi)*R_y(theta)*R_z(gamma)."
    },
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "wigner",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC
PyInit_wigner(void)
{
    return PyModule_Create(&module);
}
