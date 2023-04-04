#ifndef VK_SWAPCHAIN_CI
#define VK_SWAPCHAIN_CI

#include <Python.h>
#include <structmember.h>

#include <vulkan/vulkan.h>

#include <stdbool.h>

typedef struct vk_swapchain_ci
{
    PyObject_HEAD
    uint32_t s_type;
    PyObject* p_next;
    uint32_t flags;
    PyObject* surface;
    uint32_t min_image_count;
    long image_format;
    long image_color_space;
    PyObject* image_extent;
    uint32_t image_array_layers;
    uint32_t image_usage_flags;
    long image_sharing_mode;
    PyObject* queue_family_indices;
    long pre_transform;
    long composite_alpha;
    long present_mode_khr;
    bool clipped;
    PyObject* old_swapchain;
    
    VkSwapchainCreateInfoKHR ci;
} vk_swapchain_ci;

PyObject* add_vk_swapchain_ci_to_module(PyObject* mod);

PyTypeObject vk_swapchain_ci_type;

#endif