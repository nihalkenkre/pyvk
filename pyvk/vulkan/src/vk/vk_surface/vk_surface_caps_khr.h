#ifndef VK_SURFACE_CAPS_KHR
#define VK_SURFACE_CAPS_KHR

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_surface_caps_khr
{
    PyObject_HEAD
        uint32_t min_image_count;
    uint32_t max_image_count;
    PyObject *current_extent;
    PyObject *min_image_extent;
    PyObject *max_image_extent;
    uint32_t max_image_array_layers;
    long supported_transforms;
    long current_transform;
    long supported_composite_alpha;
    long supported_usage_flags;

    VkSurfaceCapabilitiesKHR caps;
} vk_surface_caps_khr;

PyTypeObject vk_surface_caps_khr_type;

PyObject* add_vk_surface_caps_khr_to_module(PyObject* mod);

#endif