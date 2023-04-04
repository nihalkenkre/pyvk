#ifndef VK_MEM_HEAP
#define VK_MEM_HEAP

#include <Python.h>
#include <structmember.h>

typedef struct vk_mem_heap
{
    PyObject_HEAD
        uint64_t size;
    uint32_t flags;
} vk_mem_heap;

PyMemberDef vk_mem_heap_members[];
PyTypeObject vk_mem_heap_type;

PyObject* add_vk_mem_heap_to_module(PyObject* mod);

#endif // VK_MEM_HEAP