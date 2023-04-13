#ifndef VK_APP_INFO
#define VK_APP_INFO

#include <Python.h>
#include <structmember.h>

#include <vulkan/vulkan.h>

typedef struct vk_app_info
{
    PyObject_HEAD
    PyObject *p_next;
    const char *app_name;
    PyObject *app_ver;
    const char *engine_name;
    PyObject *engine_ver;
    PyObject *api_ver;

    VkApplicationInfo app_info;
} vk_app_info;

PyObject *add_vk_app_info_to_module(PyObject *mod);

PyTypeObject vk_app_info_type;

#endif // VK_APP_INFO