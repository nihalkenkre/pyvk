#ifndef VK_SWAPCHAIN
#define VK_SWAPCHAIN

#include <Python.h>
#include <vulkan/vulkan.h>

typedef struct vk_swapchain
{
    PyObject_HEAD
        VkSwapchainKHR swapchain;
} vk_swapchain;

PyObject* add_vk_swapchain_to_module(PyObject* mod);

PyTypeObject vk_swapchain_type;

#endif