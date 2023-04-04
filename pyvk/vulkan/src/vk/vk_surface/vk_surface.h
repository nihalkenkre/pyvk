#ifndef VK_SURFACE_H
#define VK_SURFACE_H

#include <Python.h>
#include <vulkan/vulkan.h>

typedef struct vk_surface
{
    PyObject_HEAD
        VkSurfaceKHR surface;
} vk_surface;

PyObject *add_vk_surface_to_module(PyObject *mod);

PyMethodDef vk_surface_methods[];
PyTypeObject vk_surface_type;

#endif // VK_SURFACE