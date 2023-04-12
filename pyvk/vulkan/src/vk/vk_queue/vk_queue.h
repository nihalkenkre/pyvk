#ifndef VK_QUEUE
#define VK_QUEUE

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_queue
{
    PyObject_HEAD

        VkQueue queue;
} vk_queue;

PyTypeObject vk_queue_type;

PyObject *add_vk_queue_to_module(PyObject *mod);

#endif