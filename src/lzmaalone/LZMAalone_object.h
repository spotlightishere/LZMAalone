#ifndef __LZMAalone_object_h__
#define __LZMAalone_object_h__

#define PY_SSIZE_T_CLEAN 1
#include <Python.h>

extern "C" {
	PyObject* decompress(PyObject* self, PyObject *args);
}

#endif /* __LZMAalone_object_h__ */