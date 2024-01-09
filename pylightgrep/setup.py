import setuptools


setuptools.setup(
    name='lightgrep',
    version='0.1.0',
    author='Joel Uckelman <joel.uckelman@aon.co.uk>',
    packages=['lightgrep'],
    package_data={
        'lightgrep': ['liblightgrep.so', 'liblightgrep.dylib']
    },
    include_package_data=True,
    has_ext_modules=lambda: True
)
