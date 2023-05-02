#ifndef VK_IMG_BLIT
#define VK_IMG_BLIT

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_img_blit
{
    PyObject_HEAD
        PyObject *src_srl;
    PyObject *src_offsets;
    PyObject *dst_srl;
    PyObject *dst_offsets;

    VkImageBlit image_blit;
} vk_img_blit;

PyTypeObject vk_img_blit_type;

PyObject *add_vk_img_blit_to_module(PyObject *mod);

#endif