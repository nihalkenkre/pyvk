#include "vk_q_si.h"
#include "vk_sem.h"
#include "vk_cmd_buf.h"

#include <structmember.h>

#include "log.h"
#include "utils.h"

PyMemberDef vk_q_si_members[] = {
    {"p_next", T_OBJECT_EX, offsetof(vk_q_si, p_next), 0, "TODO: Pass None for now"},
    {"wait_semaphores", T_OBJECT_EX, offsetof(vk_q_si, wait_sems), 0, "A list of semaphores to wait on"},
    {"wait_dst_stage_masks", T_OBJECT_EX, offsetof(vk_q_si, stg_msks), 0, "List of stage flags at which the semphore wait occurs"},
    {"command_buffers", T_OBJECT_EX, offsetof(vk_q_si, cmd_bufs), 0, "List of command buffers to execute"},
    {"signal_semphores", T_OBJECT_EX, offsetof(vk_q_si, sig_sems), 0, "List of semaphores to siganl when the command buffers have completed execution"},
    {NULL},
};

void vk_q_si_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_q_si_dealloc\n");

    vk_q_si *self = (vk_q_si *)self_obj;

    if (!Py_IsNone(self->p_next))
    {
        Py_XDECREF(self->p_next);
    }

    if (!Py_IsNone(self->wait_sems))
    {
        Py_XDECREF(self->wait_sems);
    }

    if (!Py_IsNone(self->stg_msks))
    {
        Py_XDECREF(self->stg_msks);
    }

    if (!Py_IsNone(self->cmd_bufs))
    {
        Py_XDECREF(self->cmd_bufs);
    }

    if (!Py_IsNone(self->sig_sems))
    {
        Py_XDECREF(self->sig_sems);
    }

    if (self->si.pCommandBuffers != NULL)
    {
        free((void *)self->si.pCommandBuffers);
    }

    if (self->si.pSignalSemaphores != NULL)
    {
        free((void *)self->si.pSignalSemaphores);
    }

    if (self->si.pWaitSemaphores != NULL)
    {
        free((void *)self->si.pWaitSemaphores);
    }

    if (self->si.pWaitDstStageMask != NULL)
    {
        free((void *)self->si.pWaitDstStageMask);
    }

    Py_TYPE(self_obj)->tp_free(self_obj);
}

void get_cmd_bufs_from_list(PyObject *obj, VkCommandBuffer **cmd_bufs, uint32_t *cmd_bufs_count)
{
    DEBUG_LOG("get_cmd_bufs_from_list\n");

    *cmd_bufs_count = (uint32_t)PyList_Size(obj);
    *cmd_bufs = (VkCommandBuffer *)malloc(sizeof(VkCommandBuffer) * *cmd_bufs_count);

    for (uint32_t idx = 0; idx < *cmd_bufs_count; ++idx)
    {
        *(*cmd_bufs + idx) = ((vk_cmd_buf *)PyList_GetItem(obj, idx))->command_buffer;
    }
}

void init_q_si_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_q_si_from_obj\n");

    vk_q_si *obj = (vk_q_si *)obj_obj;

    obj->si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    obj->si.pNext = NULL;

    get_semaphores_from_list(obj->wait_sems, (VkSemaphore **)&obj->si.pWaitSemaphores, &obj->si.waitSemaphoreCount);

    uint32_t stg_count = 0;
    get_uint32s_from_list(obj->stg_msks, &obj->si.pWaitDstStageMask, &stg_count);

    get_cmd_bufs_from_list(obj->cmd_bufs, (VkCommandBuffer **)&obj->si.pCommandBuffers, &obj->si.commandBufferCount);
    get_semaphores_from_list(obj->sig_sems, (VkSemaphore **)&obj->si.pSignalSemaphores, &obj->si.signalSemaphoreCount);
}

int vk_q_si_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_q_si_init\n");

    PyObject *p_next = NULL;
    PyObject *wait_sems = NULL;
    PyObject *stg_msks = NULL;
    PyObject *cmd_bufs = NULL;
    PyObject *sig_sems = NULL;

    PyObject *tmp = NULL;

    char *kwlist[] = {"p_next", "wait_semaphores", "wait_dst_stage_masks", "command_buffers", "signal_semaphores", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OOOOO", kwlist, &p_next, &wait_sems, &stg_msks, &cmd_bufs, &sig_sems);
    if (PyErr_Occurred())
    {
        return -1;
    }

    vk_q_si *self = (vk_q_si *)self_obj;

    if (p_next)
    {
        tmp = self->p_next;
        Py_INCREF(p_next);
        self->p_next = p_next;
        Py_XDECREF(tmp);
    }
    else
    {
        self->p_next = Py_None;
    }
    DEBUG_LOG("q_si parsed p_next\n");

    if (wait_sems)
    {
        tmp = self->wait_sems;
        Py_INCREF(wait_sems);
        self->wait_sems = wait_sems;
        Py_XDECREF(tmp);
    }
    else
    {
        self->wait_sems = Py_None;
    }
    DEBUG_LOG("q_si parsed wait_sems\n");

    if (stg_msks)
    {
        tmp = self->stg_msks;
        Py_INCREF(stg_msks);
        self->stg_msks = stg_msks;
        Py_XDECREF(tmp);
    }
    else
    {
        self->stg_msks = Py_None;
    }
    DEBUG_LOG("q_si parsed stg_msks\n");

    if (cmd_bufs)
    {
        tmp = self->cmd_bufs;
        Py_INCREF(cmd_bufs);
        self->cmd_bufs = cmd_bufs;
        Py_XDECREF(tmp);
    }
    else
    {
        self->cmd_bufs = Py_None;
    }
    DEBUG_LOG("q_si parsed cmd_bufs\n");

    if (sig_sems)
    {
        tmp = self->sig_sems;
        Py_INCREF(sig_sems);
        self->sig_sems = sig_sems;
        Py_XDECREF(tmp);
    }
    else
    {
        self->sig_sems = Py_None;
    }
    DEBUG_LOG("q_si parsed sig_sems\n");

    init_q_si_from_obj(self_obj);

    return 0;
}

PyTypeObject vk_q_si_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.submit_info",
    .tp_basicsize = sizeof(vk_q_si),
    .tp_doc = PyDoc_STR("Vulkan Submit Info Docs"),
    .tp_members = vk_q_si_members,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = vk_q_si_dealloc,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_q_si_init,
};

PyObject *add_vk_q_si_to_module(PyObject *mod)
{
    DEBUG_LOG("adding q_si object\n");

    if (PyType_Ready(&vk_q_si_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready q_si type");

        goto shutdown;
    }

    Py_INCREF(&vk_q_si_type);

    if (PyModule_AddObject(mod, "submit_info", (PyObject *)&vk_q_si_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add q_si type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_q_si_type);

    return NULL;
}