#include "vk_surface_caps_khr.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_surface_caps_khr_members[] = {
    {"min_image_count", T_UINT, offsetof(vk_surface_caps_khr, min_image_count), 1, "The minimum number of images supported by a swapchain created for the surface"},
    {"max_image_count", T_UINT, offsetof(vk_surface_caps_khr, max_image_count), 1, "The maximum number of images supported by a swapchain created for the surface"},
    {"current_extent", T_OBJECT_EX, offsetof(vk_surface_caps_khr, current_extent), 1, "The current width and height of the surface"},
    {"min_image_extent", T_OBJECT_EX, offsetof(vk_surface_caps_khr, min_image_extent), 1, "The smallest valid swapchain extent for the surface"},
    {"max_image_extent", T_OBJECT_EX, offsetof(vk_surface_caps_khr, max_image_extent), 1, "The largest valid swapchain extent for the surface"},
    {"max_image_array_layers", T_UINT, offsetof(vk_surface_caps_khr, max_image_array_layers), 1, "The maximum number of layers the presentable images can have for a swapchain for this surface"},
    {"supported_transforms", T_LONG, offsetof(vk_surface_caps_khr, supported_transforms), 1, "Bitmask of the presentation transforms supported by this surface"},
    {"current_transform", T_LONG, offsetof(vk_surface_caps_khr, current_transform), 1, "The surface's current transform relative to the engine's natural transform"},
    {"supported_composite_alpha", T_LONG, offsetof(vk_surface_caps_khr, supported_composite_alpha), 1, "Bitmask of the alpha compositing mode supported by the presentation engine for the surfae on the specified device"},
    {"supported_usage_flags", T_LONG, offsetof(vk_surface_caps_khr, supported_usage_flags), 1, "Bitmask of the ways the application can use the images of the swapchain"},
    {NULL},
};

void vk_surface_caps_khr_dealloc(vk_surface_caps_khr *self)
{
    DEBUG_LOG("vk_surface_caps_khr_dealloc\n");

    Py_XDECREF(self->current_extent);
    Py_XDECREF(self->min_image_extent);
    Py_XDECREF(self->max_image_extent);

    Py_TYPE((PyObject *)self)->tp_free((PyObject *)self);
}

PyTypeObject vk_surface_caps_khr_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.surface_capabilities_khr",
    .tp_basicsize = sizeof(vk_surface_caps_khr),
    .tp_doc = PyDoc_STR("Vulkan Surface Capabilities KHR"),
    .tp_members = vk_surface_caps_khr_members,
    .tp_dealloc = vk_surface_caps_khr_dealloc,
};

PyObject *add_vk_surface_caps_khr_to_module(PyObject *mod)
{
    DEBUG_LOG("adding surface_caps_khr object\n");

    if (PyType_Ready(&vk_surface_caps_khr_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready surface_caps_khr_type");

        goto shutdown;
    }

    Py_INCREF(&vk_surface_caps_khr_type);

    if (PyModule_AddObject(mod, "surface_capabilities_khr", (PyObject *)&vk_surface_caps_khr_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add surface_caps_khr_type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_surface_caps_khr_type);

    return NULL;
}
