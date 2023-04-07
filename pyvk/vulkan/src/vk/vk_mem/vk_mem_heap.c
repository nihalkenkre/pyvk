#include "vk_mem_heap.h"
#include "log.h"

PyMemberDef vk_mem_heap_members[] = {
    {"size", T_ULONG, offsetof(vk_mem_heap, size), 1, "Size of the memory heap"},
    {"flags", T_UINT, offsetof(vk_mem_heap, flags), 1, "Flags of the memory heap"},
    {NULL},
};

PyTypeObject vk_mem_heap_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.memory_heap",
    .tp_basicsize = sizeof(vk_mem_heap),
    .tp_doc = PyDoc_STR("Vulkan Memory Heap Docs"),
    .tp_members = vk_mem_heap_members,
};

PyObject *add_vk_mem_heap_to_module(PyObject *mod)
{
    DEBUG_LOG("adding memory_heap object\n");

    if (PyType_Ready(&vk_mem_heap_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready mem_heap type to module");
        goto shutdown;
    }

    Py_INCREF(&vk_mem_heap_type);

    if (PyModule_AddObject(mod, "memory_heap", (PyObject *)&vk_mem_heap_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add mem_heap type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_mem_heap_type);

    return NULL;
}