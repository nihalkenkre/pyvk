#ifndef VK_INSTANCE_CI
#define VK_INSTANCE_CI

#include <Python.h>
#include <structmember.h>

#include <vulkan/vulkan.h>

typedef struct vk_instance_ci
{
    PyObject_HEAD
        unsigned long s_type;
    PyObject *p_next;
    uint32_t flags;
    PyObject *app_info;
    PyObject *enabled_layers;
    PyObject *enabled_extensions;

    VkInstanceCreateInfo ci;
} vk_instance_ci;

PyObject *add_vk_instance_ci_to_module(PyObject *mod);

PyTypeObject vk_instance_ci_type;

#endif