#ifndef VK_DEV_CI
#define VK_DEV_CI

#include <Python.h>
#include <structmember.h>

#include <vulkan/vulkan.h>

typedef struct vk_dev_ci
{
    PyObject_HEAD
        PyObject *p_next;
    uint32_t flags;
    PyObject *queue_create_infos;
    PyObject *enabled_layers;
    PyObject *enabled_extensions;
    PyObject *enabled_features;

    VkDeviceCreateInfo ci;
} vk_dev_ci;

PyTypeObject vk_dev_ci_type;

PyObject *add_vk_dev_ci_to_module(PyObject *mod);

#endif