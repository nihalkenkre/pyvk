#ifndef VK_MEM_REQ
#define VK_MEM_REQ

#include <Python.h>

// #include <vulkan/vulkan.h>

typedef struct vk_mem_req {
    PyObject_HEAD
    unsigned long size;
    unsigned long alignment;
    uint32_t mem_type_bits;

    // VkMemoryRequirements mem_req;
} vk_mem_req;

PyTypeObject vk_mem_req_type;

PyObject* add_vk_mem_req_to_module(PyObject* mod);

#endif