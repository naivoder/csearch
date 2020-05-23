from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

csearch_extension = Extension(
    name="csearch",
    sources=["csearch.pyx"],
    libraries=["examples"],
    library_dirs=["lib"],
    include_dirs=["lib"]
)
setup(
    name="csearch",
    ext_modules=cythonize([csearch_extension])
)
