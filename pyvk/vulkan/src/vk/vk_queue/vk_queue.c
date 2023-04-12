#include "vk_queue.h"

#include "log.h"

PyTypeObject vk_queue_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.queue",
    .tp_basicsize = sizeof(vk_queue),
    .tp_doc = PyDoc_STR("Vulkan Queue Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
};

PyObject *add_vk_queue_to_module(PyObject *mod)
{
    DEBUG_LOG("adding queue object\n");

    if (PyType_Ready(&vk_queue_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready queue type");

        goto shutdown;
    }

    Py_INCREF(&vk_queue_type);

    if (PyModule_AddObject(mod, "queue", (PyObject *)&vk_queue_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add queue type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_queue_type);

    return NULL;
}