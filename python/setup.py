import setuptools

with open('README.md', 'r') as fh:
    long_description = fh.read()

setuptools.setup(
    name='wigner_d', # Replace with your own username
    version='1.0.0',
    author='Nicolas Tessore',
    author_email='n.tessore@ucl.ac.uk',
    description='compute Wigner D-function values',
    long_description=long_description,
    long_description_content_type='text/markdown',
    url='https://github.com/ntessore/wigner_d',
    classifiers=[
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
    ],
    python_requires='>=3.6',
    include_dirs=['../c'],
    ext_modules=[
        setuptools.Extension('wigner_d', [
            'module.c', '../c/wigner_d.c'
        ])
    ],
)
