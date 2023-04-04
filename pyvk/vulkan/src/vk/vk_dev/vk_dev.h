#ifndef VK_DEV
#define VK_DEV

#include <Python.h>
#include <vulkan/vulkan.h>

typedef struct vk_dev
{
    PyObject_HEAD
        VkDevice device;
} vk_dev;

PyObject *add_vk_dev_to_module(PyObject *mod);

PyTypeObject vk_dev_type;

#endif // VK_DEV