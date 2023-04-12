#include "vk_surface_fmt_khr.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_surface_fmt_khr_members[] = {
    {"format", T_LONG, offsetof(vk_surface_fmt_khr, format), 1, "Format compatible with the surface"},
    {"color_space", T_LONG, offsetof(vk_surface_fmt_khr, color_space), 1, "Color space compatible with the surface"},
    {NULL},
};

PyTypeObject vk_surface_fmt_khr_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.surface_formats_khr",
    .tp_basicsize = sizeof(vk_surface_fmt_khr),
    .tp_doc = PyDoc_STR("Vulkan Surface"),
    .tp_members = vk_surface_fmt_khr_members,
};

PyObject *add_vk_surface_fmt_khr_to_module(PyObject *mod)
{
    DEBUG_LOG("adding surface_format_khr object\n");

    if (PyType_Ready(&vk_surface_fmt_khr_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready surface_fmt_khr_type");

        goto shutdown;
    }

    Py_INCREF(&vk_surface_fmt_khr_type);

    if (PyModule_AddObject(mod, "surface_format_khr", (PyObject *)&vk_surface_fmt_khr_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add surface_fmt_khr_type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_surface_fmt_khr_type);

    return NULL;
}