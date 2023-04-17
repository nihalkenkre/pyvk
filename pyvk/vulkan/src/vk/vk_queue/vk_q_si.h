#ifndef VK_Q_SI
#define VK_Q_SI

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_q_si
{
    PyObject_HEAD

        PyObject *p_next;
    PyObject *wait_sems;
    PyObject *stg_msks;
    PyObject *cmd_bufs;
    PyObject *sig_sems;

    VkSubmitInfo si;
} vk_q_si;

PyTypeObject vk_q_si_type;

PyObject *add_vk_q_si_to_module(PyObject *mod);

#endif