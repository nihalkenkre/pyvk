#ifndef UTILS
#define UTILS

#include <Python.h>

void get_names_from_list(PyObject *obj, char ***names, uint32_t *names_count);
void get_floats_from_list(PyObject *obj, float **values);

#endif