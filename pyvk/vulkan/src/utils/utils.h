#ifndef UTILS
#define UTILS

#include <Python.h>

#include <vulkan/vulkan.h>

void get_names_from_list(PyObject *obj, char ***names, uint32_t *names_count);
void get_floats_from_list(PyObject *obj, float **values);
void get_uint32s_from_list(PyObject *obj, uint32_t **values, uint32_t* value_count);
void get_semaphores_from_list(PyObject *obj, VkSemaphore **sems, uint32_t *sems_count);

#endif