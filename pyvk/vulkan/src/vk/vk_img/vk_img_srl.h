#ifndef VK_IMG_SRL
#define VK_IMG_SRL

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_img_srl
{
    PyObject_HEAD long aspect_mask;
    uint32_t mip_level;
    uint32_t base_array_layer;
    uint32_t layer_count;

    VkImageSubresourceLayers subresource_layers;
} vk_img_srl;

PyTypeObject vk_img_srl_type;

PyObject *add_vk_img_srl_to_module(PyObject *mod);

#endif