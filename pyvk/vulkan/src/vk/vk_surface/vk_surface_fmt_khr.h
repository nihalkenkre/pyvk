#ifndef VK_SURF_FMT
#define VK_SURF_FMT

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_surface_fmt_khr
{
    PyObject_HEAD 

    long format;
    long color_space;

    VkSurfaceFormatKHR fmt;
} vk_surface_fmt_khr;

PyTypeObject vk_surface_fmt_khr_type;

PyObject *add_vk_surface_fmt_khr_to_module(PyObject *mod);

#endif