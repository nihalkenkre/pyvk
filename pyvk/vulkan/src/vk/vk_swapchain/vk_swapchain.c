#include "vk_swapchain.h"

#include "log.h"

PyTypeObject vk_swapchain_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.swapchain",
    .tp_basicsize = sizeof(vk_swapchain),
    .tp_doc = PyDoc_STR("Vulkan Swapchain Docs"),
};

PyObject *add_vk_swapchain_to_module(PyObject *mod)
{
    DEBUG_LOG("adding swapchain object\n");

    if (PyType_Ready(&vk_swapchain_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready swapchain type");

        goto shutdown;
    }

    Py_INCREF(&vk_swapchain_type);

    if (PyModule_AddObject(mod, "swapchain", (PyObject *)&vk_swapchain_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add swapchain type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_swapchain_type);

    return NULL;
}