#define PY_SSIZE_T_CLEAN
#include <Python.h>

extern void wigner_d(int l0, int l1, int n, int m, double theta, double* d);

static PyObject* _wigner_d(PyObject* self, PyObject* args)
{
    int l0, l1, n, m;
    PyObject* angle;
    double phi, theta, gamma;
    double* d;
    PyObject* list;

    if(!PyArg_ParseTuple(args, "iiiiO", &l0, &l1, &n, &m, &angle))
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

    if(l0 < 0 || l1 < l0)
    {
        PyErr_SetString(PyExc_ValueError, "requires 0 <= l0 <= l1");
        return NULL;
    }

    d = malloc((l1-l0+1)*sizeof(double));
    if(!d)
        return PyErr_NoMemory();

    wigner_d(l0, l1, n, m, theta, d);

    list = PyList_New(l1-l0+1);
    if(phi == HUGE_VAL)
    {
        for(l1 = l1-l0+1, l0=0; l0 < l1; ++l0)
            PyList_SetItem(list, l0, PyFloat_FromDouble(d[l0]));
    }
    else
    {
        const double a = n*phi + m*gamma;
        const double c = cos(a);
        const double s = sin(a);
        for(l1 = l1-l0+1, l0=0; l0 < l1; ++l0)
            PyList_SetItem(list, l0, PyComplex_FromDoubles(c*d[l0], s*d[l0]));
    }

    free(d);

    return list;
}

static PyMethodDef methods[] = {
    {"wigner_d", _wigner_d, METH_VARARGS,
     "wigner_d(l0, l1, n, m, angle, /)\n--\n\nWigner D-function for range l = "
     "l0, ..., l1 and n, m, angle [rad] fixed. If a single angle is given, the "
     "Wigner (little) d-function is computed, and a list of real numbers is "
     "returned. If a tuple (phi, theta, gamma) of angles is given, the Wigner "
     "(big) D-function is computed, and a list of complex numbers is returned. "
     "The rotation in matrix form is R_z(phi)*R_y(theta)*R_z(gamma)."
    },
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "wigner_d",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC
PyInit_wigner_d(void)
{
    return PyModule_Create(&module);
}
