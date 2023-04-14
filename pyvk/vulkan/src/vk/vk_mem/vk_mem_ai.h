#ifndef VK_MEM_AI
#define VK_MEM_AI

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_mem_ai
{
    PyObject_HEAD
        PyObject *p_next;
    unsigned long alloc_size;
    uint32_t mem_type_idx;

    VkMemoryAllocateInfo ai;
} vk_mem_ai;

PyTypeObject vk_mem_ai_type;

PyObject *add_vk_mem_ai_to_module(PyObject *mod);

#endif