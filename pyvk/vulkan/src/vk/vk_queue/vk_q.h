#ifndef VK_QUEUE
#define VK_QUEUE

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_q
{
    PyObject_HEAD

        VkQueue queue;
} vk_q;

PyTypeObject vk_q_type;

PyObject *add_vk_q_to_module(PyObject *mod);

#endif