#include "vk_img_blit.h"
#include "vk_img_srl.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_img_blit_members[] = {
    {"src_subresource", T_OBJECT_EX, offsetof(vk_img_blit, src_srl), 0, "The subresource to blit from"},
    {"src_offsets", T_OBJECT_EX, offsetof(vk_img_blit, src_offsets), 0, "Two VkOffset3D specifying the bounds of the src region within the src_subresource"},
    {"dst_subresource", T_OBJECT_EX, offsetof(vk_img_blit, dst_srl), 0, "The subresource to blit into"},
    {"dst_offsets", T_OBJECT_EX, offsetof(vk_img_blit, dst_offsets), 0, "Two VkOffset3D specifying the bounds of the dst region within the dst_subresource"},
    {NULL},
};

void vk_img_blit_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_img_blit_dealloc\n");

    vk_img_blit *self = (vk_img_blit *)self_obj;

    if (!Py_IsNone(self->src_srl))
    {
        Py_XDECREF(self->src_srl);
    }

    if (!Py_IsNone(self->src_offsets))
    {
        Py_XDECREF(self->dst_offsets);
    }

    if (!Py_IsNone(self->dst_srl))
    {
        Py_XDECREF(self->dst_srl);
    }

    if (!Py_IsNone(self->dst_offsets))
    {
        Py_XDECREF(self->dst_offsets);
    }

    Py_TYPE(self_obj)->tp_free(self_obj);
}

void init_img_blit_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_img_blit_from_obj\n");

    vk_img_blit *obj = (vk_img_blit *)obj_obj;

    obj->image_blit.srcSubresource = ((vk_img_srl *)obj->src_srl)->subresource_layers;

    obj->image_blit.srcOffsets[0].x = PyLong_AsLong(PyTuple_GetItem(PyList_GetItem(obj->src_offsets, 0), 0));
    obj->image_blit.srcOffsets[0].y = PyLong_AsLong(PyTuple_GetItem(PyList_GetItem(obj->src_offsets, 0), 1));
    obj->image_blit.srcOffsets[0].z = PyLong_AsLong(PyTuple_GetItem(PyList_GetItem(obj->src_offsets, 0), 2));

    obj->image_blit.srcOffsets[1].x = PyLong_AsLong(PyTuple_GetItem(PyList_GetItem(obj->src_offsets, 1), 0));
    obj->image_blit.srcOffsets[1].y = PyLong_AsLong(PyTuple_GetItem(PyList_GetItem(obj->src_offsets, 1), 1));
    obj->image_blit.srcOffsets[1].z = PyLong_AsLong(PyTuple_GetItem(PyList_GetItem(obj->src_offsets, 1), 2));

    obj->image_blit.dstSubresource = ((vk_img_srl *)obj->dst_srl)->subresource_layers;

    obj->image_blit.dstOffsets[0].x = PyLong_AsLong(PyTuple_GetItem(PyList_GetItem(obj->dst_offsets, 0), 0));
    obj->image_blit.dstOffsets[0].y = PyLong_AsLong(PyTuple_GetItem(PyList_GetItem(obj->dst_offsets, 0), 1));
    obj->image_blit.dstOffsets[0].z = PyLong_AsLong(PyTuple_GetItem(PyList_GetItem(obj->dst_offsets, 0), 2));

    obj->image_blit.dstOffsets[1].x = PyLong_AsLong(PyTuple_GetItem(PyList_GetItem(obj->dst_offsets, 1), 0));
    obj->image_blit.dstOffsets[1].y = PyLong_AsLong(PyTuple_GetItem(PyList_GetItem(obj->dst_offsets, 1), 1));
    obj->image_blit.dstOffsets[1].z = PyLong_AsLong(PyTuple_GetItem(PyList_GetItem(obj->dst_offsets, 1), 2));
}

int vk_img_blit_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_img_blit_init\n");

    PyObject *src_srl = NULL;
    PyObject *src_offsets = NULL;
    PyObject *dst_srl = NULL;
    PyObject *dst_offsets = NULL;

    PyObject *tmp = NULL;

    char *kwlist[] = {"src_subresource", "src_offsets", "dst_subresource", "dst_offsets", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OOOO", kwlist, &src_srl, &src_offsets, &dst_srl, &dst_offsets);
    if (PyErr_Occurred())
    {
        return -1;
    }

    vk_img_blit *self = (vk_img_blit *)self_obj;

    if (src_srl)
    {
        tmp = self->src_srl;
        Py_INCREF(src_srl);
        self->src_srl = src_srl;
        Py_XDECREF(tmp);
    }
    else
    {
        self->src_srl = Py_None;
    }
    DEBUG_LOG("img_blit parsed src_srl\n");

    if (src_offsets)
    {
        tmp = self->src_offsets;
        Py_INCREF(src_offsets);
        self->src_offsets = src_offsets;
        Py_XDECREF(tmp);
    }
    else
    {
        self->src_offsets = Py_None;
    }
    DEBUG_LOG("img_blit parsed src_offsets\n");

    if (dst_srl)
    {
        tmp = self->dst_srl;
        Py_INCREF(dst_srl);
        self->dst_srl = dst_srl;
        Py_XDECREF(tmp);
    }
    else
    {
        self->dst_srl = Py_None;
    }
    DEBUG_LOG("img_blit parsed dst_srl\n");

    if (dst_offsets)
    {
        tmp = self->dst_offsets;
        Py_INCREF(dst_offsets);
        self->dst_offsets = dst_offsets;
        Py_XDECREF(tmp);
    }
    else
    {
        self->dst_offsets = Py_None;
    }
    DEBUG_LOG("img_blit parsed dst_offsets\n");

    init_img_blit_from_obj(self_obj);

    return 0;
}

PyTypeObject vk_img_blit_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.image_blit",
    .tp_basicsize = sizeof(vk_img_blit),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = PyDoc_STR("Vulkan Image Blit Docs"),
    .tp_members = vk_img_blit_members,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_img_blit_init,
    .tp_dealloc = vk_img_blit_dealloc,
};

PyObject *add_vk_img_blit_to_module(PyObject *mod)
{
    DEBUG_LOG("adding img_blit object\n");

    if (PyType_Ready(&vk_img_blit_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready img_blit type");

        goto shutdown;
    }

    Py_INCREF(&vk_img_blit_type);

    if (PyModule_AddObject(mod, "image_blit", (PyObject *)&vk_img_blit_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add img_blit type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_img_blit_type);

    return NULL;
}