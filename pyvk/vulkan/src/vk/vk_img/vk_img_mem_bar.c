#include "vk_img_mem_bar.h"
#include "vk_img_srl.h"
#include "vk_img.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_img_mem_bar_members[] = {
    {"p_next", T_OBJECT_EX, offsetof(vk_img_mem_bar, p_next), 0, "TODO: Pass None for now"},
    {"src_access_mask", T_UINT, offsetof(vk_img_mem_bar, src_access_mask), 0, "Bitmask specifying source access mask"},
    {"dst_access_mask", T_UINT, offsetof(vk_img_mem_bar, dst_access_mask), 0, "Bitmask specifying destination access mask"},
    {"old_layout", T_LONG, offsetof(vk_img_mem_bar, old_layout), 0, "The old layout"},
    {"new_layout", T_LONG, offsetof(vk_img_mem_bar, new_layout), 0, "The new layout"},
    {"src_queue_family_index", T_UINT, offsetof(vk_img_mem_bar, src_q_fly_idx), 0, "The source queue family for a ownership transfer"},
    {"dst_queue_family_index", T_UINT, offsetof(vk_img_mem_bar, dst_q_fly_idx), 0, "The destination queue family for a ownership transfer"},
    {"image", T_OBJECT_EX, offsetof(vk_img_mem_bar, img), 0, "The image affected by this barrier"},
    {"subresource_range", T_OBJECT_EX, offsetof(vk_img_mem_bar, srl), 0, "The subresource range within the image affected by this barrier"},
    {NULL},
};

void init_img_mem_bar_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_img_mem_bar_from_obj\n");

    vk_img_mem_bar *obj = (vk_img_mem_bar *)obj_obj;

    obj->memory_barrier.srcAccessMask = obj->src_access_mask;
    obj->memory_barrier.dstAccessMask = obj->dst_access_mask;
    obj->memory_barrier.oldLayout = obj->old_layout;
    obj->memory_barrier.newLayout = obj->new_layout;
    obj->memory_barrier.srcQueueFamilyIndex = obj->src_q_fly_idx;
    obj->memory_barrier.dstQueueFamilyIndex = obj->dst_q_fly_idx;
    obj->memory_barrier.image = ((vk_img *)(obj->img))->image;
    obj->memory_barrier.subresourceRange = ((vk_img_srl *)obj->srl)->subresource;
}

void vk_img_mem_bar_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_img_mem_bar_dealloc\n");

    vk_img_mem_bar *self = (vk_img_mem_bar *)self_obj;

    if (!Py_IsNone(self->p_next))
    {
        Py_XDECREF(self->p_next);
    }

    if (!Py_IsNone(self->))
}