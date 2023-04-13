#ifndef VK_FENCE
#define VK_FENCE

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_fence
{
    PyObject_HEAD
        VkFence fence;
} vk_fence;

PyTypeObject vk_fence_type;

PyObject *add_vk_fence_to_module(PyObject *mod);

#endif