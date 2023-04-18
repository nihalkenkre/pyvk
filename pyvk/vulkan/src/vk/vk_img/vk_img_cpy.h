#ifndef VK_IMG_CPY
#define VK_IMG_CPY

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_img_cpy
{
    PyObject_HEAD
        PyObject *src_subresource;
    PyObject *src_offset;
    PyObject *dst_subresource;
    PyObject *dst_offset;
    PyObject *extent;

    VkImageCopy img_cpy;
} vk_img_cpy;

PyTypeObject vk_img_cpy_type;

PyObject *add_vk_img_cpy_to_module(PyObject *mod);

#endif