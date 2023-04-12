#include "vk_cmd_pool.h"

#include "log.h"

PyTypeObject vk_cmd_pool_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.command_pool",
    .tp_basicsize = sizeof(vk_cmd_pool),
    .tp_doc = PyDoc_STR("Vulkan Command Pool Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
};

PyObject *add_vk_cmd_pool_to_module(PyObject *mod)
{
    DEBUG_LOG("adding cmd_pool object\n");

    if (PyType_Ready(&vk_cmd_pool_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready cmd_pool type to module");
        goto shutdown;
    }

    Py_INCREF(&vk_cmd_pool_type);

    if (PyModule_AddObject(mod, "command_pool", (PyObject *)&vk_cmd_pool_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add cmd_pool type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_cmd_pool_type);

    return NULL;
}
