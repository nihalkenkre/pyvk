#ifndef VK_IMG_CI
#define VK_IMG_CI

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_img_ci
{
    PyObject_HEAD

        PyObject *p_next;
    uint32_t flags;
    long image_type;
    long format;
    PyObject *extent;
    uint32_t mip_levels;
    uint32_t array_layers;
    long samples;
    long tiling;
    long usage;
    long sharing_mode;
    PyObject *q_fly_idx;
    long initial_layout;

    VkImageCreateInfo ci;
} vk_img_ci;

PyTypeObject vk_img_ci_type;

PyObject *add_vk_img_ci_to_module(PyObject *mod);

#endif
