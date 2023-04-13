#include "vk_img.h"

PyTypeObject vk_img_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.image",
    .tp_basicsize = sizeof(vk_img),
    .tp_doc = PyDoc_STR("Vulkan Image Docs"),
};

PyObject *add_vk_img_to_module(PyObject *mod)
{
    DEBUG_LOG("adding img object\n");

    if (PyType_Ready(&vk_img_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready img type");

        goto shutdown;
    }

    Py_INCREF(&vk_img_type);

    if (PyModule_AddObject(mod, "image", (PyObject *)&vk_img_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add img type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_img_type);

    return NULL;
}