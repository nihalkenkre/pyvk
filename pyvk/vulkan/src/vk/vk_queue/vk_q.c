#include "vk_q.h"

#include "log.h"

PyTypeObject vk_q_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.q",
    .tp_basicsize = sizeof(vk_q),
    .tp_doc = PyDoc_STR("Vulkan Queue Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
};

PyObject *add_vk_q_to_module(PyObject *mod)
{
    DEBUG_LOG("adding queue object\n");

    if (PyType_Ready(&vk_q_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready q type");

        goto shutdown;
    }

    Py_INCREF(&vk_q_type);

    if (PyModule_AddObject(mod, "queue", (PyObject *)&vk_q_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add q type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_q_type);

    return NULL;
}