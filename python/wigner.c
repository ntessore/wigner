#define PY_SSIZE_T_CLEAN
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <numpy/arrayobject.h>

#include "wigner.h"


static PyObject* _legendre_pl(PyObject* self, PyObject* args)
{
    int lmin, lmax, n;
    double x;
    double* p;
    npy_intp dims[1];
    PyArrayObject* array;

    if(!PyArg_ParseTuple(args, "iid", &lmin, &lmax, &x))
        return NULL;

    if(lmin < 0 || lmax < lmin)
        return PyErr_Format(PyExc_ValueError, "requires 0 <= lmin <= lmax");

    n = lmax-lmin+1;
    dims[0] = n;
    array = (PyArrayObject*)PyArray_SimpleNew(1, dims, NPY_DOUBLE);
    if(!array)
        return NULL;
    p = PyArray_DATA(array);

    legendre_pl(lmin, lmax, x, p);

    return PyArray_Return(array);
}


static PyObject* _wigner_3jj(PyObject* self, PyObject* args)
{
    double l2, l3, m2, m3, l1min, l1max;
    double* thrcof;
    int ier, n;
    npy_intp dims[1];
    PyArrayObject* array;

    if(!PyArg_ParseTuple(args, "dddd", &l2, &l3, &m2, &m3))
        return NULL;

    ier = wigner_3jj(l2, l3, m2, m3, &l1min, &l1max, NULL, 0);

    switch(ier)
    {
    case 0:
        break;
    case 1:
        return PyErr_Format(PyExc_ValueError, "either `l2 < abs(m2)` or `l3 < abs(m3)");
    case 2:
        return PyErr_Format(PyExc_ValueError, "either `l2+abs(m2)` or `l3+abs(m3)` non-integer");
    case 3:
        return PyErr_Format(PyExc_ValueError, "`l1max-l1min` not an integer");
    case 4:
        return PyErr_Format(PyExc_ValueError, "`l1max` less than `l1min`");
    default:
        return PyErr_Format(PyExc_RuntimeError, "unknown error");
    }

    n = l1max-l1min+1.1;
    dims[0] = n;
    array = (PyArrayObject*)PyArray_SimpleNew(1, dims, NPY_DOUBLE);
    if(!array)
        return NULL;
    thrcof = PyArray_DATA(array);

    wigner_3jj(l2, l3, m2, m3, &l1min, &l1max, thrcof, n);

    return Py_BuildValue("ddN", l1min, l1max, array);
}


static PyObject* _wigner_3jm(PyObject* self, PyObject* args)
{
    double l1, l2, l3, m1, m2min, m2max;
    double* thrcof;
    int ier, n;
    npy_intp dims[1];
    PyArrayObject* array;

    if(!PyArg_ParseTuple(args, "dddd", &l1, &l2, &l3, &m1))
        return NULL;

    ier = wigner_3jm(l1, l2, l3, m1, &m2min, &m2max, NULL, 0);

    switch(ier)
    {
    case 0:
        break;
    case 1:
        return PyErr_Format(PyExc_ValueError, "either `l1 < abs(m1)` or `l1+abs(m1)` non-integer");
    case 2:
        return PyErr_Format(PyExc_ValueError, "`abs(l1-l2) <= l3 <= l1+l2` not satisfied");
    case 3:
        return PyErr_Format(PyExc_ValueError, "`l1+l2+l3` not an integer");
    case 4:
        return PyErr_Format(PyExc_ValueError, "`m2max-m2min` not an integer");
    case 5:
        return PyErr_Format(PyExc_ValueError, "`m2max` less than `m2min`");
    default:
        return PyErr_Format(PyExc_RuntimeError, "unknown error");
    }

    n = m2max-m2min+1.1;
    dims[0] = n;
    array = (PyArrayObject*)PyArray_SimpleNew(1, dims, NPY_DOUBLE);
    if(!array)
        return NULL;
    thrcof = PyArray_DATA(array);

    wigner_3jm(l1, l2, l3, m1, &m2min, &m2max, thrcof, n);

    return Py_BuildValue("ddN", m2min, m2max, array);
}


static PyObject* _wigner_dl(PyObject* self, PyObject* args)
{
    int lmin, lmax, m1, m2, n;
    double theta;
    double* d;
    npy_intp dims[1];
    PyArrayObject* array;

    if(!PyArg_ParseTuple(args, "iiiid", &lmin, &lmax, &m1, &m2, &theta))
        return NULL;

    if(lmin < 0 || lmax < lmin)
        return PyErr_Format(PyExc_ValueError, "requires 0 <= lmin <= lmax");

    n = lmax-lmin+1;
    dims[0] = n;
    array = (PyArrayObject*)PyArray_SimpleNew(1, dims, NPY_DOUBLE);
    if(!array)
        return NULL;
    d = PyArray_DATA(array);

    wigner_dl(lmin, lmax, m1, m2, theta, d);

    return PyArray_Return(array);
}


static PyMethodDef methods[] = {
    {"legendre_pl", _legendre_pl, METH_VARARGS, PyDoc_STR(
        "legendre_pl(lmin, lmax, x)\n"
        "--\n"
        "\n"
        "Compute the Legendre polynomials `P_l(x)` for all degrees `l = lmin`\n"
        "to `l = lmax`, with `x` being held fixed.  The arguments `lmin` and\n"
        "`lmax` must be integers, while the argument `x` must be float.\n"
        "Returns a numpy array of size `lmax-lmin+1`.\n"
    )},
    {"wigner_3jj", _wigner_3jj, METH_VARARGS, PyDoc_STR(
        "wigner_3jj(l2, l3, m2, m3)\n"
        "--\n"
        "\n"
        "Evaluate the Wigner 3j symbol\n"
        "\n"
        "    /   l1    l2  l3 \\\n"
        "    \\ -m2-m3  m2  m3 /\n"
        "\n"
        "for all allowable values of `l1`, with the other parameters held\n"
        "fixed.  For physically meaningful outputs, the arguments must be\n"
        "integer or half-integer, although other inputs are allowed.  Returns\n"
        "a tuple `l1min, l1max, thrcof` where `l1min` and `l1max` are the\n"
        "smallest and largest allowable values of `l1`, and `thrcof` is a \n"
        "numpy array of size `l1max-l1min+1` containing the values of the 3j\n"
        "symbol.\n"
    )},
    {"wigner_3jm", _wigner_3jm, METH_VARARGS, PyDoc_STR(
        "wigner_3jm(l1, l2, l3, m1)\n"
        "--\n"
        "\n"
        "Evaluate the Wigner 3j symbol\n"
        "\n"
        "    / l1  l2    l3  \\\n"
        "    \\ m1  m2  -m1-m2/\n"
        "\n"
        "for all allowable values of `m2`, with the other parameters held\n"
        "fixed.  For physically meaningful outputs, the arguments must be\n"
        "integer or half-integer, although other inputs are allowed.  Returns\n"
        "a tuple `m2min, m2max, thrcof` where `m2min` and `m2max` are the\n"
        "smallest and largest allowable values of `m2`, and `thrcof` is a \n"
        "numpy array of size `m2max-m2min+1` containing the values of the 3j\n"
        "symbol.\n"
    )},
    {"wigner_dl", _wigner_dl, METH_VARARGS, PyDoc_STR(
        "wigner_dl(lmin, lmax, m1, m2, theta)\n"
        "--\n"
        "\n"
        "Compute the Wigner d function `d^l_{m1,m2}(theta)` for all degrees\n"
        "`l = lmin` to `l = lmax`, with `m1`, `m2`, and `theta` being held\n"
        "fixed.  The arguments `lmin`, `lmax`, `m1`, `m2` must be integers,\n"
        "and the angle `theta` must be given in radian as float.  Returns a\n"
        "numpy array of size `lmax-lmin+1`.\n"
    )},
    {NULL, NULL}
};


static struct PyModuleDef module_def = {
    PyModuleDef_HEAD_INIT,
    "wigner",
    PyDoc_STR("Wigner d functions and 3j symbols"),
    -1,
    methods
};


PyMODINIT_FUNC
PyInit_wigner(void)
{
    PyObject* module = PyModule_Create(&module_def);
    if(!module)
        return NULL;
    import_array();
    if(PyErr_Occurred())
        return NULL;
    return module;
}
