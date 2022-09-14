import setuptools
import numpy as np

setuptools.setup(
    ext_modules=[
        setuptools.Extension(
            'wigner',
            sources=[
                'python/wigner.c',
                'src/wigner_3jj.c',
                'src/wigner_3jm.c',
                'src/wigner_dl.c',
            ],
            include_dirs=[
                'include',
                np.get_include(),
            ],
        ),
    ],
)
