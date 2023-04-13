#include "vk_sem.h"

#include <structmember.h>

#include "log.h"

PyTypeObject vk_sem_type = {
    .tp_name = "vulkan.semaphore",
    .tp_basicsize = sizeof(vk_sem),
    .tp_doc = PyDoc_STR("Vulkan Semaphore Docs"),
};

PyObject *add_vk_sem_to_module(PyObject *mod)
{
    DEBUG_LOG("adding sem object\n");

    if (PyType_Ready(&vk_sem_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready sem type");
        goto shutdown;
    }

    Py_INCREF(&vk_sem_type);

    if (PyModule_AddObject(mod, "semaphore", (PyObject *)&vk_sem_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add sem type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_sem_type);

    return NULL;
}