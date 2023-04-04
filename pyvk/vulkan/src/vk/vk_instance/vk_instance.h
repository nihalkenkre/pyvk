#ifndef VK_INSTANCE
#define VK_INSTANCE

#include <Python.h>
#include <vulkan/vulkan.h>

typedef struct vk_instance
{
    PyObject_HEAD
        VkInstance instance;
} vk_instance;

PyObject *add_vk_instance_to_module(PyObject *module);

PyTypeObject vk_instance_type;

#endif // VK_INSTANCE