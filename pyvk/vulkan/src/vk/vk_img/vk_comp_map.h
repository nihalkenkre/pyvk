#ifndef VK_COMP_MAP
#define VK_COMP_MAP

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_comp_map
{
    PyObject_HEAD long r;
    long g;
    long b;
    long a;

    VkComponentMapping component_mapping;
} vk_comp_map;

PyTypeObject vk_comp_map_type;

PyObject *add_vk_comp_map_to_module(PyObject *mod);

#endif