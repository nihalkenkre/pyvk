#include "vk_surface.h"

PyTypeObject vk_surface_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.surface",
    .tp_basicsize = sizeof(vk_surface),
    .tp_doc = PyDoc_STR("Vulkan Surface Docs"),
};

PyObject* add_vk_surface_to_module(PyObject* module)
{
    DEBUG_LOG("adding surface object\n");

    if (PyType_Ready(&vk_surface_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready surface type");

        goto shutdown;
    }

    Py_INCREF(&vk_surface_type);

    if (PyModule_AddObject(module, "surface", (PyObject *)&vk_surface_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add surface type to module");
        goto shutdown;
    }

    return module;

shutdown:
    Py_XDECREF(&vk_surface_type);

    return NULL;
}