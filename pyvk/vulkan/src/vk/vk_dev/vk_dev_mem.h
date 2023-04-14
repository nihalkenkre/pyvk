#ifndef VK_DEV_MEM
#define VK_DEV_MEM

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_dev_mem
{
    PyObject_HEAD

    VkDeviceMemory device_memory;
} vk_dev_mem;

PyTypeObject vk_dev_mem_type;

PyObject* add_vk_dev_mem_to_module(PyObject* mod);

#endif