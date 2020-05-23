LIB_DIR = lib

default: csearch

csearch: setup.py csearch.pyx $(LIB_DIR)/libexamples.a
	python3 setup.py build_ext --inplace && rm -f csearch.c && rm -Rf build

$(LIB_DIR)/libexamples.a:
	make -C $(LIB_DIR) libexamples.a

clean:
	rm *.so
