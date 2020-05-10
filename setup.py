from distutils.core import setup, Extension

setup(name='pywigner_d', version='1.0',
    ext_modules=[Extension('wigner_d', ['module.c', 'wigner_d.c'])],
)
