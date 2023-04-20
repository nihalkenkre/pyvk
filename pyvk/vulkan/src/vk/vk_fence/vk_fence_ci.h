#ifndef VK_FENCE_CI
#define VK_FENCE_CI

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_fence_ci
{
    PyObject_HEAD
        PyObject *p_next;
    long flags;

    VkFenceCreateInfo ci;
} vk_fence_ci;

PyTypeObject vk_fence_ci_type;

PyObject *add_vk_fence_ci_to_module(PyObject *mod);

#endif