#ifndef VK_SEM
#define VK_SEM

#include <Python.h>
#include <vulkan/vulkan.h>

typedef struct vk_sem
{
    PyObject_HEAD

        VkSemaphore semaphore;
} vk_sem;

PyTypeObject vk_sem_type;

PyObject* add_vk_sem_to_module(PyObject* mod);

#endif