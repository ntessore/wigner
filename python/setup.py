import setuptools

with open('README.md', 'r') as fh:
    long_description = fh.read()

setuptools.setup(
    name='wigner',
    version='0.9.0',
    author='Nicolas Tessore',
    author_email='n.tessore@ucl.ac.uk',
    description='functions for rotations: Wigner D-matrix, 3j-symbols',
    long_description=long_description,
    long_description_content_type='text/markdown',
    url='https://github.com/ntessore/wigner',
    classifiers=[
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
    ],
    python_requires='>=3.6',
    include_dirs=['../c'],
    ext_modules=[
        setuptools.Extension('wigner', [
            'module.c', '../c/wigner_d_l.c'
        ])
    ],
)
