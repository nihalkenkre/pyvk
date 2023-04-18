#ifndef VK_IMG_MEM_BAR
#define VK_IMG_MEM_BAR

#include <Python.h>

#include <vulkan/vulkan.h>

typedef struct vk_img_mem_bar
{
    PyObject_HEAD
        PyObject *p_next;
    uint32_t src_access_mask;
    uint32_t dst_access_mask;
    long old_layout;
    long new_layout;
    uint32_t src_q_fly_idx;
    uint32_t dst_q_fly_idx;
    PyObject *img;
    PyObject *srl;

    VkImageMemoryBarrier memory_barrier;
} vk_img_mem_bar;

PyTypeObject vk_img_mem_bar_type;

PyObject *add_vk_img_mem_bar_to_module(PyObject *mod);

#endif