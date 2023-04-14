#include "vk_mem_ai.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_mem_ai_members[] = {
    {"p_next", T_OBJECT_EX, offsetof(vk_mem_ai, p_next), 0, "TODO: Pass None for now"},
    {"allocation_size", T_ULONG, offsetof(vk_mem_ai, alloc_size), 0, "The allocation size"},
    {"memory_type_index", T_UINT, offsetof(vk_mem_ai, mem_type_idx), 0, "THe memory type"},
    {NULL},
};

void vk_mem_ai_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_mem_ai_dealloc\n");

    vk_mem_ai *self = (vk_mem_ai *)self_obj;

    if (!Py_IsNone(self->p_next))
    {
        Py_XDECREF(self->p_next);
    }

    Py_TYPE(self_obj)->tp_free(self_obj);
}

void init_mem_ai_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_mem_ai_from_obj\n");

    vk_mem_ai *obj = (vk_mem_ai *)obj_obj;

    obj->ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    obj->ai.pNext = NULL;
    obj->ai.allocationSize = obj->alloc_size;
    obj->ai.memoryTypeIndex = obj->mem_type_idx;
}

int vk_mem_ai_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_mem_ai_init\n");

    vk_mem_ai *self = (vk_mem_ai *)self_obj;

    PyObject *p_next = NULL;

    PyObject *tmp = NULL;

    char *kwlist[] = {"p_next", "allocation_size", "memory_type_index", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OKI", kwlist, &p_next, &self->alloc_size, &self->mem_type_idx);
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
    DEBUG_LOG("vk_mem_ai parsed p_next\n");

    init_mem_ai_from_obj(self_obj);

    return 0;
}

PyTypeObject vk_mem_ai_type = {
    .tp_name = "vulkan.memory_allocate_info",
    .tp_basicsize = sizeof(vk_mem_ai),
    .tp_doc = PyDoc_STR("Vulkan Memory Allocate Info Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = vk_mem_ai_dealloc,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_mem_ai_init,
};

PyObject *add_vk_mem_ai_to_module(PyObject *mod)
{
    DEBUG_LOG("adding mem_ai object\n");

    if (PyType_Ready(&vk_mem_ai_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready mem_ai type");
        goto shutdown;
    }

    Py_INCREF(&vk_mem_ai_type);

    if (PyModule_AddObject(mod, "memory_allocate_info", (PyObject *)&vk_mem_ai_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add mem_ai type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_mem_ai_type);

    return NULL;
}