#include "vk_cmd_buf.h"

#include "log.h"

PyTypeObject vk_cmd_buf_type = {
    .tp_name = "vulkan.command_buffer",
    .tp_basicsize = sizeof(vk_cmd_buf),
    .tp_doc = PyDoc_STR("Vulkan Command Buffer Docs"),
};

PyObject *add_vk_cmd_buf_to_module(PyObject *mod)
{
    DEBUG_LOG("adding cmd_buf object\n");

    if (PyType_Ready(&vk_cmd_buf_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready cmd_buf type");

        goto shutdown;
    }

    Py_INCREF(&vk_cmd_buf_type);

    if (PyModule_AddObject(mod, "command_buffer", (PyObject *)&vk_cmd_buf_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add cmd_buf type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_cmd_buf_type);

    return NULL;
}