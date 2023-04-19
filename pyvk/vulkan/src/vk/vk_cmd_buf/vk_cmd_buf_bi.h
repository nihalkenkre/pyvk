#ifndef VK_CMD_BUF_BI
#define VK_CMD_BUF_BI

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_cmd_buf_bi
{
    PyObject_HEAD 
    long flags;

    VkCommandBufferBeginInfo bi;
} vk_cmd_buf_bi;

PyTypeObject vk_cmd_buf_bi_type;

PyObject *add_vk_cmd_buf_bi_to_module(PyObject *mod);

#endif