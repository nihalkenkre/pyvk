#ifndef VK_CMD_BUF_AI
#define VK_CMD_BUF_AI

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_cmd_buf_ai
{
    PyObject_HEAD
        PyObject *cmd_pool;
    unsigned long level;
    uint32_t cmd_buf_count;

    VkCommandBufferAllocateInfo ai;
} vk_cmd_buf_ai;

PyTypeObject vk_cmd_buf_ai_type;

PyObject *add_vk_cmd_buf_ai_to_module(PyObject *mod);

#endif