#include "vk_mem_req.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_mem_req_members[] = {
    {"size", T_ULONG, offsetof(vk_mem_req, size), 0, "The size in bytes of the allocation"},
    {"alignment", T_ULONG, offsetof(vk_mem_req, alignment), 0, "The alignment in bytes of the offset within the allocation"},
    {"memory_type_bits", T_UINT, offsetof(vk_mem_req, mem_type_bits), 0, "A bitmask with one bit set of every supported memory type for the resource"},
    {NULL},
};

PyTypeObject vk_mem_req_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name="vulkan.memory_requirements",
    .tp_basicsize = sizeof(vk_mem_req),
    .tp_doc = PyDoc_STR("Vulkan Memory Requirements Docs"),
    .tp_flags= Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_members = vk_mem_req_members,
};

PyObject *add_vk_mem_req_to_module(PyObject *mod)
{
    DEBUG_LOG("adding mem_req object\n");

    if (PyType_Ready(&vk_mem_req_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready mem_req type");

        goto shutdown;
    }

    Py_INCREF(&vk_mem_req_type);

    if (PyModule_AddObject(mod, "memory_requirements", (PyObject *)&vk_mem_req_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add mem_req type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_mem_req_type);

    return NULL;
}