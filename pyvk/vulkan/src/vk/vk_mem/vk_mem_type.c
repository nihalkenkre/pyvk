#include "vk_mem_type.h"

#include "log.h"

PyMemberDef vk_mem_type_members[] = {
    {"property_flags", T_UINT, offsetof(vk_mem_type, property_flags), 1, "Property flags for this memory type"},
    {"heap_index", T_UINT, offsetof(vk_mem_type, heap_index), 1, "Heap index of the memory type"},
    {NULL},
};

PyTypeObject vk_mem_type_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.memory_type",
    .tp_basicsize = sizeof(vk_mem_type),
    .tp_doc = PyDoc_STR("Vulkan Memory Type Docs"),
    .tp_members = vk_mem_type_members,
};

PyObject *add_vk_mem_type_to_module(PyObject *mod)
{
    DEBUG_LOG("adding mem_type object\n");

    if (PyType_Ready(&vk_mem_type_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready mem_type type to module");
        goto shutdown;
    }

    Py_INCREF(&vk_mem_type_type);

    if (PyModule_AddObject(mod, "memory_type", (PyObject *)&vk_mem_type_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add mem_type type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_mem_type_type);

    return NULL;
}