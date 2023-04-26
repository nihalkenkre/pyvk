#include "vk_img_view.h"

#include <structmember.h>

#include "log.h"

PyTypeObject vk_img_view_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.image_view",
    .tp_basicsize = sizeof(vk_img_view),
    .tp_doc = PyDoc_STR("Vulkan Image View Docs"),
};

PyObject *add_vk_img_view_to_module(PyObject *mod)
{
    DEBUG_LOG("adding img_view object\n");

    if (PyType_Ready(&vk_img_view_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready img_view type");

        goto shutdown;
    }

    Py_INCREF(&vk_img_view_type);

    if (PyModule_AddObject(mod, "image_view", (PyObject *)&vk_img_view_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add img_view type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_img_view_type);

    return NULL;
}
