#ifndef VK_IMG_VIEW
#define VK_IMG_VIEW

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_img_view
{
    PyObject_HEAD
        VkImageView image_view;
} vk_img_view;

PyTypeObject vk_img_view_type;

PyObject *add_vk_img_view_to_module(PyObject *obj);

#endif