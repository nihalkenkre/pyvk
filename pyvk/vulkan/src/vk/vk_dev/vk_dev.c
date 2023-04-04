#include "vk_dev.h"
#include "log.h"

void vk_dev_dealloc(PyObject *self)
{
    DEBUG_LOG("vk_dev_dealloc\n");
    Py_TYPE(self)->tp_free(self);
}

PyTypeObject vk_dev_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.device",
    .tp_basicsize = sizeof(vk_dev),
    .tp_doc = PyDoc_STR("Vulkan Device Docs"),
    .tp_dealloc = vk_dev_dealloc,
};

PyObject *add_vk_dev_to_module(PyObject *mod)
{
    DEBUG_LOG("adding device object\n");

    if (PyType_Ready(&vk_dev_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready dev type to module");
        goto shutdown;
    }

    Py_INCREF(&vk_dev_type);

    if (PyModule_AddObject(mod, "device", (PyObject *)&vk_dev_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add dev type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_dev_type);

    return NULL;
}
