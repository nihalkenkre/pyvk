#include "vk_cmd_pool_ci.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_cmd_pool_ci_members[] = {
    {"p_next", T_OBJECT_EX, offsetof(vk_cmd_pool_ci, p_next), 0, "TODO: Pass None for now"},
    {"flags", T_UINT, offsetof(vk_cmd_pool_ci, flags), 0, "Command Pool Create Info Creation flags"},
    {"queue_family_index", T_UINT, offsetof(vk_cmd_pool_ci, q_fly_idx), 0, "The index of the queue family where the command buffers created from this pool must be submitted"},
    {NULL},
};

void vk_cmd_pool_ci_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_cmd_pool_ci_dealloc\n");

    vk_cmd_pool_ci *self = (vk_cmd_pool_ci *)self_obj;

    if (self->p_next != Py_None)
    {
        Py_XDECREF(self->p_next);
    }

    Py_TYPE((PyObject *)self)->tp_free((PyObject *)self);
}

void init_cmd_pool_ci_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_cmd_pool_ci_from_oj\n");

    vk_cmd_pool_ci* obj = (vk_cmd_pool_ci*) obj_obj;

    obj->ci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    obj->ci.pNext = NULL;
    obj->ci.flags = obj->flags;
    obj->ci.queueFamilyIndex = obj->q_fly_idx;
}

int vk_cmd_pool_ci_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_cmd_pool_ci_init\n");

    vk_cmd_pool_ci *self = (vk_cmd_pool_ci *)self_obj;

    PyObject *p_next = NULL;
    PyObject *tmp = NULL;

    char *kwlist[] = {"p_next", "flags", "queue_family_index", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OII", kwlist, &p_next, &self->flags, &self->q_fly_idx);
    if (PyErr_Occurred())
    {
        return -1;
    }

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
    DEBUG_LOG("vk_cmd_pool_ci parsed p_next\n");

    init_cmd_pool_ci_from_obj(self_obj);

    return 0;
}

PyTypeObject vk_cmd_pool_ci_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.command_pool_create_info",
    .tp_basicsize = sizeof(vk_cmd_pool_ci),
    .tp_doc = PyDoc_STR("Vulkan Command Pool Create Info Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_members = vk_cmd_pool_ci_members,
    .tp_dealloc = vk_cmd_pool_ci_dealloc,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_cmd_pool_ci_init,
};

PyObject *add_vk_cmd_pool_ci_to_module(PyObject *mod)
{
    DEBUG_LOG("adding cmd_pool_ci object\n");

    if (PyType_Ready(&vk_cmd_pool_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready cmd_pool_ci type");
        goto shutdown;
    }

    Py_INCREF(&vk_cmd_pool_ci_type);

    if (PyModule_AddObject(mod, "command_pool_create_info", (PyObject *)&vk_cmd_pool_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add cmd_pool_ci type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_cmd_pool_ci_type);

    return NULL;
}