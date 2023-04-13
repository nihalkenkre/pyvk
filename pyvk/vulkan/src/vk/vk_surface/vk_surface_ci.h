#ifndef VK_SURFACE_CI
#define VK_SURFACE_CI

#include <Python.h>

#include <Windows.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

typedef struct vk_surface_ci
{
    PyObject_HEAD
    PyObject *p_next;
    uint32_t flags;
    long h_wnd;

    VkWin32SurfaceCreateInfoKHR ci;
} vk_surface_ci;

PyObject *add_vk_surface_ci_to_module(PyObject *mod);

PyTypeObject vk_surface_ci_type;

#endif