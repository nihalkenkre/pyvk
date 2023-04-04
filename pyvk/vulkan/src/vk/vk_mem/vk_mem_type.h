#ifndef VK_MEM_TYPE
#define VK_MEM_TYPE

#include <Python.h>
#include <structmember.h>

typedef struct vk_mem_type
{
    PyObject_HEAD
        uint32_t property_flags;
    uint32_t heap_index;
} vk_mem_type;

PyMemberDef vk_mem_type_members[];
PyTypeObject vk_mem_type_type;

PyObject* add_vk_mem_type_to_module(PyObject* mod);

#endif // VK_MEM_TYPE