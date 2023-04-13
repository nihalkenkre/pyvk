#ifndef VK_CMD_POOL_CI
#define VK_CMD_POOL_CI

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_cmd_pool_ci
{
    PyObject_HEAD
        PyObject *p_next;
    long flags;
    uint32_t q_fly_idx;

    VkCommandPoolCreateInfo ci;
} vk_cmd_pool_ci;

PyTypeObject vk_cmd_pool_ci_type;

PyObject *add_vk_cmd_pool_ci_to_module(PyObject *mod);

#endif