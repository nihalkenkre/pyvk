#include "vk_fence.h"

#include "log.h"

PyTypeObject vk_fence_type = {
    .tp_name = "vulkan.fence",
    .tp_basicsize = sizeof(vk_fence),
    .tp_doc = PyDoc_STR("Vulkan Fence Docs"),
};

PyObject *add_vk_fence_to_module(PyObject *mod)
{
    DEBUG_LOG("adding fence object\n");

    if (PyType_Ready(&vk_fence_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready fence type");
        goto shutdown;
    }

    Py_INCREF(&vk_fence_type);

    if (PyModule_AddObject(mod, "fence", (PyObject *)&vk_fence_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add fence type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_fence_type);

    return NULL;
}