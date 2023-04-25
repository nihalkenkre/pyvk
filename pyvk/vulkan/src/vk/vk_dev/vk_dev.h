#ifndef VK_DEV
#define VK_DEV

#include <Python.h>
#include <vulkan/vulkan.h>

typedef struct vk_dev
{
    PyObject_HEAD
        VkDevice device;

    void **mapped_datas;
    uint32_t mapped_datas_count;
} vk_dev;

PyObject *add_vk_dev_to_module(PyObject *mod);

PyTypeObject vk_dev_type;

#endif // VK_DEV