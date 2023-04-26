#ifndef VK_IMG_SRR
#define VK_IMG_SRR

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_img_srr
{
    PyObject_HEAD long aspect_mask;
    uint32_t base_mip_level;
    uint32_t level_count;
    uint32_t base_array_layer;
    uint32_t layer_count;

    VkImageSubresourceRange subresource_range;
} vk_img_srr;

PyTypeObject vk_img_srr_type;

PyObject *add_vk_img_srr_to_module(PyObject *mod);

#endif