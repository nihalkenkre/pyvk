#ifndef VK_CMD_POOL
#define VK_CMD_POOL

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_cmd_pool
{
    PyObject_HEAD

        VkCommandPool command_pool;
} vk_cmd_pool;

PyTypeObject vk_cmd_pool_type;

PyObject* vk_add_cmd_pool_to_module(PyObject* mod);

#endif