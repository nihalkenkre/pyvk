#include "vk_dev_mem.h"

#include "log.h"

PyTypeObject vk_dev_mem_type = {
    .tp_name="vulkan.device_memory",
    .tp_basicsize = sizeof(vk_dev_mem),
    .tp_doc = PyDoc_STR("Vulkan Device Memory Docs"),
};

PyObject *add_vk_dev_mem_to_module(PyObject *mod)
{
    DEBUG_LOG("adding dev_mem object\n");

    if (PyType_Ready(&vk_dev_mem_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready dev_mem type");
        goto shutdown;
    }

    Py_INCREF(&vk_dev_mem_type);

    if (PyModule_AddObject(mod, "device_memory", (PyObject *)&vk_dev_mem_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add dev_mem type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_dev_mem_type);

    return NULL;
}