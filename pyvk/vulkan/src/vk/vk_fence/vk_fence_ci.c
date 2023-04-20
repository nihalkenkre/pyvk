#include "vk_fence_ci.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_fence_ci_members[] = {
    {"p_next", T_OBJECT_EX, offsetof(vk_fence_ci, p_next), 0, "TODO: Pass None for now"},
    {"flags", T_LONG, offsetof(vk_fence_ci, flags), 0, "Fence creation flags"},
    {NULL},
};

void vk_fence_ci_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_fence_ci_dealloc\n");

    vk_fence_ci *self = (vk_fence_ci *)self_obj;

    if (self->p_next != Py_None)
    {
        Py_XDECREF(self->p_next);
    }

    Py_TYPE(self_obj)->tp_free(self_obj);
}

void init_fence_ci_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_fence_ci_from_obj\n");

    vk_fence_ci *obj = (vk_fence_ci *)obj_obj;

    obj->ci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    obj->ci.pNext = NULL;
    obj->ci.flags = obj->flags;
}

int vk_fence_ci_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_fence_ci_init\n");

    vk_fence_ci *self = (vk_fence_ci *)self_obj;
    PyObject *p_next = NULL;

    PyObject *tmp = NULL;

    char *kwlist[] = {"p_next", "flags", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|Ok", kwlist, &p_next, &self->flags);
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

    init_fence_ci_from_obj(self_obj);

    return 0;
}

PyTypeObject vk_fence_ci_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.fence_create_info",
    .tp_basicsize = sizeof(vk_fence_ci),
    .tp_doc = PyDoc_STR("Vulkan Fence Create Info"),
    .tp_members = vk_fence_ci_members,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = vk_fence_ci_dealloc,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_fence_ci_init,
};

PyObject *add_vk_fence_ci_to_module(PyObject *mod)
{
    DEBUG_LOG("adding fence_ci object\n");

    if (PyType_Ready(&vk_fence_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready fence_ci type");
        goto shutdown;
    }

    Py_INCREF(&vk_fence_ci_type);

    if (PyModule_AddObject(mod, "fence_create_info", (PyObject *)&vk_fence_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add fence_ci type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_fence_ci_type);

    return NULL;
}