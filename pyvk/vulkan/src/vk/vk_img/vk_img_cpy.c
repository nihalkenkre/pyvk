#include "vk_img_cpy.h"
#include "vk_img_srl.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_img_cpy_members[] = {
    {"src_subresource", T_OBJECT_EX, offsetof(vk_img_cpy, src_subresource), 0, "Image sub resources for the source image"},
    {"src_offset", T_OBJECT_EX, offsetof(vk_img_cpy, src_offset), 0, "Offset in texels of the subregions of the source image"},
    {"dst_subresource", T_OBJECT_EX, offsetof(vk_img_cpy, dst_subresource), 0, "Image sub resources for the destination image"},
    {"dst_offset", T_OBJECT_EX, offsetof(vk_img_cpy, dst_offset), 0, "Offset in texels of the subregions of the destination image"},
    {"extent", T_OBJECT_EX, offsetof(vk_img_cpy, extent), 0, "The size in texels of image to copy"},
    {NULL},
};

void vk_img_cpy_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_img_cpy_dealloc\n");

    vk_img_cpy *self = (vk_img_cpy *)self_obj;

    if (!Py_IsNone(self->src_subresource))
    {
        Py_XDECREF(self->src_subresource);
    }

    if (!Py_IsNone(self->src_offset))
    {
        Py_XDECREF(self->src_offset);
    }

    if (!Py_IsNone(self->dst_subresource))
    {
        Py_XDECREF(self->dst_subresource);
    }

    if (!Py_IsNone(self->dst_offset))
    {
        Py_XDECREF(self->dst_offset);
    }

    if (!Py_IsNone(self->extent))
    {
        Py_XDECREF(self->extent);
    }

    Py_TYPE(self_obj)->tp_free(self_obj);
}

void init_img_cpy_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_img_cpy_from_obj\n");

    vk_img_cpy *obj = (vk_img_cpy *)obj_obj;

    obj->img_cpy.srcSubresource = ((vk_img_srl *)obj->src_subresource)->subresource;

    obj->img_cpy.srcOffset.x = (int32_t)PyLong_asLong(PyTuple_GetItem(obj->src_offset, 0));
    obj->img_cpy.srcOffset.y = (int32_t)PyLong_asLong(PyTuple_GetItem(obj->src_offset, 1));
    obj->img_cpy.srcOffset.z = (int32_t)PyLong_asLong(PyTuple_GetItem(obj->src_offset, 2));

    obj->img_cpy.dstSubresource = ((vk_img_srl *)obj->dst_subresource)->subresource;

    obj->img_cpy.dstOffset.x = PyLong_asLong(PyTuple_GetItem(obj->dst_offset, 0));
    obj->img_cpy.dstOffset.y = PyLong_asLong(PyTuple_GetItem(obj->dst_offset, 1));
    obj->img_cpy.dstOffset.z = PyLong_asLong(PyTuple_GetItem(obj->dst_offset, 2));

    obj->img_cpy.extent.width = (uint32_t)Pylong_asLong(PyTuple_GetItem(obj->extent, 0));
    obj->img_cpy.extent.height = (uint32_t)Pylong_asLong(PyTuple_GetItem(obj->extent, 1));
    obj->img_cpy.extent.depth = (uint32_t)Pylong_asLong(PyTuple_GetItem(obj->extent, 2));
}

int vk_img_cpy_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_img_cpy_init\n");

    PyObject *src_sub_re = NULL;
    PyObject *src_offset = NULL;
    PyObject *dst_sub_re = NULL;
    PyObject *dst_offset = NULL;
    PyObject *extent = NULL;

    PyObject *tmp = NULL;

    char *kwlist[] = {"src_subresource", "src_offset", "dst_subresource", "dst_offset", "extent", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OOOO", kwlist, &src_sub_re, &src_offset, &dst_sub_re, &dst_offset, &extent);
    if (PyErr_Occurred())
    {
        return -1;
    }

    vk_img_cpy *self = (vk_img_cpy *)self_obj;

    if (src_sub_re)
    {
        tmp = self->src_subresource;
        Py_INCREF(src_sub_re);
        self->src_subresource = src_sub_re;
        Py_XDECREF(tmp);
    }
    else
    {
        self->src_subresource = Py_None;
    }
    DEBUG_LOG("img_cpy parsed src_subresource \n");

    if (src_offset)
    {
        tmp = self->src_offset;
        Py_INCREF(src_offset);
        self->src_offset = src_offset;
        Py_XDECREF(tmp);
    }
    else
    {
        self->src_offset = Py_None;
    }
    DEBUG_LOG("img_cpy parsed src_subresource \n");

    if (dst_sub_re)
    {
        tmp = self->dst_subresource;
        Py_INCREF(dst_sub_re);
        self->dst_subresource = dst_sub_re;
        Py_XDECREF(tmp);
    }
    else
    {
        self->dst_subresource = Py_None;
    }
    DEBUG_LOG("img_cpy parsed dst_subresource \n");

    if (dst_offset)
    {
        tmp = self->dst_offset;
        Py_INCREF(dst_offset);
        self->dst_offset = dst_offset;
        Py_XDECREF(tmp);
    }
    else
    {
        self->dst_offset = Py_None;
    }
    DEBUG_LOG("img_cpy parsed dst_subresource \n");

    init_img_cpy_from_obj(self_obj);

    return 0;
}