#ifndef VK_Q_PI
#define VK_Q_PI

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_q_pi
{
    PyObject_HEAD
        PyObject *wait_sems;
    PyObject *scs;
    PyObject *image_idx;

    VkPresentInfoKHR pi;
} vk_q_pi;

PyTypeObject vk_q_pi_type;

PyObject* add_vk_q_pi_to_module(PyObject* mod);

#endif