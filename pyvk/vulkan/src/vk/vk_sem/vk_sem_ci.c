#include "vk_sem_ci.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_sem_ci_members[] = {
    {"p_next", T_OBJECT_EX, offsetof(vk_sem_ci, p_next), 0, "TODO: Pass None for now"},
    {"flags", T_ULONG, offsetof(vk_sem_ci, flags), 0, "Semaphore creation flags"},
    {NULL},
};

void vk_sem_ci_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_sem_ci_dealloc\n");

    vk_sem_ci *self = (vk_sem_ci *)self_obj;

    if (self->p_next != Py_None)
    {
        Py_XDECREF(self->p_next);
    }

    Py_TYPE(self_obj)->tp_free(self_obj);
}

void init_sem_ci_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_sem_ci_from_obj\n");

    vk_sem_ci *obj = (vk_sem_ci *)obj_obj;

    obj->ci.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    obj->ci.pNext = NULL;
    obj->ci.flags = obj->flags;
}

int vk_sem_ci_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_sem_ci_init\n");

    vk_sem_ci *self = (vk_sem_ci *)self_obj;
    PyObject *p_next = NULL;

    PyObject *tmp = NULL;

    char *kwlist[] = {"p_next", "flags", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OK", kwlist, &p_next, &self->flags);
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

    init_sem_ci_from_obj(self_obj);

    return 0;
}

PyTypeObject vk_sem_ci_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.semaphore_create_info",
    .tp_basicsize = sizeof(vk_sem_ci),
    .tp_doc = PyDoc_STR("Vulkan Semaphore Create Info"),
    .tp_members = vk_sem_ci_members,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = vk_sem_ci_dealloc,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_sem_ci_init,
};

PyObject *add_vk_sem_ci_to_module(PyObject *mod)
{
    DEBUG_LOG("adding sem_ci object\n");

    if (PyType_Ready(&vk_sem_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready sem_ci type");
        goto shutdown;
    }

    Py_INCREF(&vk_sem_ci_type);

    if (PyModule_AddObject(mod, "semaphore_create_info", (PyObject *)&vk_sem_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add sem_ci type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_sem_ci_type);

    return NULL;
}