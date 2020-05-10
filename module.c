#define PY_SSIZE_T_CLEAN
#include <Python.h>

extern void wigner_d(int l0, int l1, int n, int m, double theta, double* d);

static PyObject* pywigner_d(PyObject* self, PyObject* args)
{
    int l0, l1, n, m;
    double theta;
    double* d;
    PyObject* list;

    if(!PyArg_ParseTuple(args, "iiiid", &l0, &l1, &n, &m, &theta))
        return NULL;

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
    for(l1 = l1-l0+1, l0=0; l0 < l1; ++l0)
        PyList_SetItem(list, l0, Py_BuildValue("d", d[l0]));

    return list;
}

static PyMethodDef methods[] = {
    {"wigner_d",  pywigner_d, METH_VARARGS,
     "wigner_d(l0, l1, n, m, theta, /)\n--\n\nWigner (little) d-function for "
     "l = l0, ..., l1 and n, m, theta [rad] fixed."},
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
