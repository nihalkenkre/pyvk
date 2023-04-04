#ifndef VK_DEV_Q_CI
#define VK_DEV_Q_CI

#include <Python.h>
#include <structmember.h>

#include <vulkan/vulkan.h>

typedef struct vk_dev_q_ci
{
    PyObject_HEAD
        uint32_t s_type;
    PyObject *p_next;
    uint32_t flags;
    uint32_t q_fly_idx;
    uint32_t q_count;
    PyObject *priorities;

    VkDeviceQueueCreateInfo ci;
} vk_dev_q_ci;

PyMemberDef vk_dev_q_ci_members[];
PyTypeObject vk_dev_q_ci_type;

PyObject *add_vk_dev_q_ci_to_module(PyObject *mod);


#endif