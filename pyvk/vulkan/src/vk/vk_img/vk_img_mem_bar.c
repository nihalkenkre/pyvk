#include "vk_img_mem_bar.h"
#include "vk_img_srr.h"
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
    {"subresource_range", T_OBJECT_EX, offsetof(vk_img_mem_bar, srr), 0, "The subresource range within the image affected by this barrier"},
    {NULL},
};

void vk_img_mem_bar_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_img_mem_bar_dealloc\n");

    vk_img_mem_bar *self = (vk_img_mem_bar *)self_obj;

    if (!Py_IsNone(self->p_next))
    {
        Py_XDECREF(self->p_next);
    }

    if (!Py_IsNone(self->img))
    {
        Py_XDECREF(self->img);
    }

    if (!Py_IsNone(self->srr))
    {
        Py_XDECREF(self->srr);
    }

    Py_TYPE(self_obj)->tp_free(self_obj);
}

void init_img_mem_bar_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_img_mem_bar_from_obj\n");

    vk_img_mem_bar *obj = (vk_img_mem_bar *)obj_obj;

    obj->memory_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    obj->memory_barrier.pNext = NULL;
    obj->memory_barrier.srcAccessMask = obj->src_access_mask;
    obj->memory_barrier.dstAccessMask = obj->dst_access_mask;
    obj->memory_barrier.oldLayout = obj->old_layout;
    obj->memory_barrier.newLayout = obj->new_layout;
    obj->memory_barrier.srcQueueFamilyIndex = obj->src_q_fly_idx;
    obj->memory_barrier.dstQueueFamilyIndex = obj->dst_q_fly_idx;
    obj->memory_barrier.image = ((vk_img *)(obj->img))->image;
    obj->memory_barrier.subresourceRange = ((vk_img_srr *)obj->srr)->subresource;
}

int vk_img_mem_bar_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_img_mem_bar_init\n");

    PyObject *p_next = NULL;
    PyObject *img = NULL;
    PyObject *srr = NULL;

    PyObject *tmp = NULL;

    char *kwlist[] = {"p_next", "src_access_mask", "dst_access_mask", "old_layout", "new_layout",
                      "src_queue_family_index", "dst_queue_family_index", "image", "image_subresource_range", NULL};

    vk_img_mem_bar *self = (vk_img_mem_bar *)self_obj;

    PyArg_ParseTupleAndKeywords(args, kwds, "|OIIkkIIOO", kwlist, &p_next, &self->src_access_mask, &self->dst_access_mask,
                                &self->old_layout, &self->new_layout, &self->src_q_fly_idx, &self->dst_q_fly_idx, &img, &srr);

    if (PyErr_Occurred())
    {
        return -1;
    }

    if (p_next)
    {
        tmp = self->p_next;
        Py_INCREF(p_next);
        self->p_next = p_next;
        Py_XDECREF(tmp);
    }
    else
    {
        self->p_next = Py_None;
    }
    DEBUG_LOG("img_mem_bar parsed p_next\n");

    if (img)
    {
        tmp = self->img;
        Py_INCREF(img);
        self->img = img;
        Py_XDECREF(tmp);
    }
    else
    {
        self->img = Py_None;
    }
    DEBUG_LOG("img_mem_bar parsed img\n");

    if (srr)
    {
        tmp = self->srr;
        Py_INCREF(srr);
        self->srr = srr;
        Py_XDECREF(tmp);
    }
    else
    {
        self->srr = Py_None;
    }
    DEBUG_LOG("img_mem_bar parsed srr\n");

    init_img_mem_bar_from_obj(self_obj);

    return 0;
}

PyTypeObject vk_img_mem_bar_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.image_memory_barrier",
    .tp_basicsize = sizeof(vk_img_mem_bar),
    .tp_doc = "Vulkan Image Memory Barrier Docs",
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_members = vk_img_mem_bar_members,
    .tp_dealloc = vk_img_mem_bar_dealloc,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_img_mem_bar_init,
};

PyObject *add_vk_img_mem_bar_to_module(PyObject *mod)
{
    DEBUG_LOG("adding img_mem_bar object\n");

    if (PyType_Ready(&vk_img_mem_bar_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready img_mem_bar type");

        goto shutdown;
    }

    Py_INCREF(&vk_img_mem_bar_type);

    if (PyModule_AddObject(mod, "image_memory_barrier", (PyObject *)&vk_img_mem_bar_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add img_mem_bar type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_img_mem_bar_type);

    return NULL;
}