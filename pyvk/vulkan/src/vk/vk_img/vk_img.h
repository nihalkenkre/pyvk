#ifndef VK_IMG
#define VK_IMG

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_img
{
    PyObject_HEAD

        VkImage image;
} vk_img;

PyTypeObject vk_img_type;

PyObject *add_vk_img_to_module(PyObject *mod);

#endif