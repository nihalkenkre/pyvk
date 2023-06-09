#include "utils.h"
#include "log.h"
#include "vk_sem.h"

#include <vulkan/vulkan.h>

void get_names_from_list(PyObject *obj, char ***names, uint32_t *names_count)
{
    DEBUG_LOG("get_names_from_list_or_tuple\n");

    *names_count = (uint32_t)PyList_Size(obj);
    if (*names_count == 0)
    {
        return;
    }

    *names = (char **)malloc(sizeof(char *) * *names_count);

    for (uint32_t name_idx = 0; name_idx < *names_count; ++name_idx)
    {
        PyObject *name_obj = PyList_GetItem(obj, name_idx);

        if (PyUnicode_Check(name_obj))
        {
            PyObject *ascii_name = PyUnicode_AsASCIIString(name_obj);
            uint32_t unicode_length = (uint32_t)PyUnicode_GET_LENGTH(name_obj);

            Py_ssize_t bytes_count = 0;
            char *bytes = NULL;
            PyBytes_AsStringAndSize(ascii_name, &bytes, &bytes_count);

            *(*names + name_idx) = (char *)malloc(sizeof(char) * (bytes_count + 1));
            memcpy(*(*names + name_idx), bytes, sizeof(char) * (bytes_count + 1));

            Py_DECREF(ascii_name);
        }
    }
}

void get_floats_from_list(PyObject *obj, float **values)
{
    DEBUG_LOG("get_floats_from_list\n");

    uint32_t values_count = (uint32_t)PyList_Size(obj);

    if (values_count == 0)
    {
        return;
    }

    *values = (float *)malloc(sizeof(float) * values_count);

    for (uint32_t v_idx = 0; v_idx < values_count; ++v_idx)
    {
        PyObject *value_obj = PyList_GetItem(obj, v_idx);

        *(*values + v_idx) = (float)PyFloat_AsDouble(value_obj);
    }
}

void get_uint32s_from_list(PyObject *obj, uint32_t **values, uint32_t *values_count)
{
    DEBUG_LOG("get_floats_from_list\n");

    *values_count = (uint32_t)PyList_Size(obj);

    if (*values_count == 0)
    {
        return;
    }

    *values = (uint32_t *)malloc(sizeof(uint32_t) * *values_count);

    for (uint32_t v_idx = 0; v_idx < *values_count; ++v_idx)
    {
        PyObject *value_obj = PyList_GetItem(obj, v_idx);

        *(*values + v_idx) = (uint32_t)PyLong_AsUnsignedLong(value_obj);
    }
}

void get_semaphores_from_list(PyObject *obj, VkSemaphore **sems, uint32_t *sems_count)
{
    DEBUG_LOG("get_semaphores_from_list\n");

    *sems_count = (uint32_t)PyList_Size(obj);
    *sems = (VkSemaphore *)malloc(sizeof(VkSemaphore) * *sems_count);

    for (uint32_t idx = 0; idx < *sems_count; ++idx)
    {
        *(*sems + idx) = ((vk_sem *)PyList_GetItem(obj, idx))->semaphore;
    }
}