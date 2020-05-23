cdef extern from "examples.h":
    int search_file(char *str, char *fname)

def _find(str, fname):
    return search_file(str, fname)
