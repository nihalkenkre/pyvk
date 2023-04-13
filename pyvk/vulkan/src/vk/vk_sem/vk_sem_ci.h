#ifndef VK_SEM_CI
#define VK_SEM_CI

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_sem_ci
{
    PyObject_HEAD
        PyObject *p_next;
    unsigned long flags;

    VkSemaphoreCreateInfo ci;
} vk_sem_ci;

PyTypeObject vk_sem_ci_type;

PyObject *add_vk_sem_ci_to_module(PyObject *mod);

#endif