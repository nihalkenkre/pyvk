#ifndef VK_CMD_BUF
#define VK_CMD_BUF

#include <Python.h>
#include <vulkan/vulkan.h>

typedef struct vk_cmd_buf
{
    PyObject_HEAD

        VkCommandBuffer command_buffer;
} vk_cmd_buf;

PyTypeObject vk_cmd_buf_type;

PyObject *add_vk_cmd_buf_to_module(PyObject *mod);

#endif