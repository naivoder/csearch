# csearch
Wrapping a C library with Cython - custom tool for searching for a string pattern in all files of directory tree.

Search function written in C for performance, directory navigation written in python for ease of use and modularity.

### dependencies 
cython: `pip install cython`

GNU compiler collection

python 3.7

### installation 
makefiles included for convenience
1) `cd lib`
2) `make`
3) `cd ..`
4) `make`

### usage (single file search)
`python3 main.py` 
