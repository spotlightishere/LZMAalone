#include "LZMAalone_object.h"

char decompress_docs[] = "Decompresses LZMA data via 7-zip.";

PyMethodDef LZMAalone_funcs[] = {
	{"decompress", (PyCFunction)decompress, METH_VARARGS, decompress_docs},
	{NULL, NULL, 0, NULL}
};

char LZMAalone_docs[] =
	"An object permitting decompression of LZMA data via 7-zip.";

PyModuleDef LZMAalone_mod = {
	PyModuleDef_HEAD_INIT,
	"LZMAalone",
	LZMAalone_docs,
	-1,
	LZMAalone_funcs,
	NULL,
	NULL,
	NULL,
	NULL
};

PyMODINIT_FUNC PyInit_LZMAalone(void) {
  return PyModule_Create(&LZMAalone_mod);
}