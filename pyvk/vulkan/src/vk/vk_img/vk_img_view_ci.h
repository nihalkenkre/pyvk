#ifndef VK_IMG_VIEW_CI
#define VK_IMG_VIEW_CI

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_img_view_ci
{
    PyObject_HEAD
        uint32_t flags;
    PyObject *img;
    long view_type;
    long format;
    PyObject *comps;
    PyObject *srr;

    VkImageViewCreateInfo ci;
} vk_img_view_ci;

PyTypeObject vk_img_view_ci_type;

PyObject *add_vk_img_view_ci_to_module(PyObject *mod);

#endif