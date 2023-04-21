#include "vk_q_pi.h"
#include "vk_swapchain.h"
#include "vk_sem.h"

#include <structmember.h>

#include "log.h"
#include "utils.h"

PyMemberDef vk_q_pi_members[] = {
    {"wait_semaphores", T_OBJECT_EX, offsetof(vk_q_pi, wait_sems), 0, "The semaphores to wait for before issuing the present request"},
    {"swapchain", T_OBJECT_EX, offsetof(vk_q_pi, scs), 0, "The swapchains being presented to by this command"},
    {"image_indices", T_OBJECT_EX, offsetof(vk_q_pi, image_idx), 0, "The the indices into the array of each swapchains presentable images"},
    {NULL},
};

void vk_q_pi_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_q_pi_dealloc\n");

    vk_q_pi *self = (vk_q_pi *)self_obj;

    if (!Py_IsNone(self->wait_sems))
    {
        Py_XDECREF(self->wait_sems);
    }

    if (!Py_IsNone(self->scs))
    {
        Py_XDECREF(self->scs);
    }

    if (!Py_IsNone(self->image_idx))
    {
        Py_XDECREF(self->image_idx);
    }

    if (self->pi.pWaitSemaphores != NULL)
    {
        free(self->pi.pWaitSemaphores);
    }

    if (self->pi.pImageIndices != NULL)
    {
        free(self->pi.pImageIndices);
    }

    if (self->pi.pSwapchains != NULL)
    {
        free(self->pi.pSwapchains);
    }

    Py_TYPE(self_obj)->tp_free(self_obj);
}

void get_swapchains_from_list(PyObject *obj, VkSwapchainKHR **sc, uint32_t *sc_count)
{
    DEBUG_LOG("get_swapchain_from_obj\n");

    *sc_count = (uint32_t)PyList_Size(obj);
    *sc = (VkSwapchainKHR *)malloc(sizeof(VkSwapchainKHR) * *sc_count);

    for (uint32_t idx = 0; idx < *sc_count; ++idx)
    {
        *(*sc + idx) = ((vk_swapchain *)PyList_GetItem(obj, idx))->swapchain;
    }
}

/*
void get_semaphores_from_list(PyObject *obj, VkSemaphore **sems, uint32_t *sems_count)
{
    DEBUG_LOG("get_semaphores_from_list\n");

    *sems_count = (uint32_t)PyList_Size(obj);
    *sems = (VkSemaphore *)malloc(sizeof(VkSemaphore) * *sems_count);

    for (uint32_t idx = 0; idx < *sems_count; ++idx)
    {
        *(*sems + idx) = ((vk_sem *)PyList_GetItem(obj, idx))->semaphore;
    }
}
*/

void init_q_pi_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_q_pi_from_obj\n");

    vk_q_pi *obj = (vk_q_pi *)obj_obj;

    obj->pi.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    obj->pi.pNext = NULL;

    get_swapchains_from_list(obj->scs, &obj->pi.pSwapchains, &obj->pi.swapchainCount);
    get_semaphores_from_list(obj->wait_sems, &obj->pi.pWaitSemaphores, &obj->pi.waitSemaphoreCount);

    uint32_t image_idx_count = 0;
    get_uint32s_from_list(obj->image_idx, &obj->pi.pImageIndices, &image_idx_count);

    obj->pi.pResults = NULL;
}

int vk_q_pi_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_q_pi_init\n");

    PyObject *wait_sems = NULL;
    PyObject *scs = NULL;
    PyObject *image_idx = NULL;

    PyObject *tmp = NULL;

    char *kwlist[] = {"wait_semaphores", "swapchains", "image_indices", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OOO", kwlist, &wait_sems, &scs, &image_idx);
    if (PyErr_Occurred())
    {
        return -1;
    }

    vk_q_pi *self = (vk_q_pi *)self_obj;

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

    if (scs)
    {
        tmp = self->scs;
        Py_INCREF(scs);
        self->scs = scs;
        Py_XDECREF(tmp);
    }
    else
    {
        self->scs = Py_None;
    }
    DEBUG_LOG("q_si parsed scs\n");

    if (image_idx)
    {
        tmp = self->image_idx;
        Py_INCREF(image_idx);
        self->image_idx = image_idx;
        Py_XDECREF(tmp);
    }
    else
    {
        self->image_idx = Py_None;
    }
    DEBUG_LOG("q_si parsed image_idx\n");

    init_q_pi_from_obj(self_obj);

    return 0;
}

PyTypeObject vk_q_pi_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.present_info",
    .tp_basicsize = sizeof(vk_q_pi),
    .tp_doc = PyDoc_STR("Vulkan Present Info Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_members = vk_q_pi_members,
    .tp_dealloc = vk_q_pi_dealloc,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_q_pi_init,
};

PyObject *add_vk_q_pi_to_module(PyObject *mod)
{
    DEBUG_LOG("adding q_pi object\n");

    if (PyType_Ready(&vk_q_pi_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready q_pi type");

        goto shutdown;
    }

    Py_INCREF(&vk_q_pi_type);

    if (PyModule_AddObject(mod, "present_info", (PyObject *)&vk_q_pi_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add q_pi type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_q_pi_type);

    return NULL;
}