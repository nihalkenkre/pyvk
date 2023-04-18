#include "vk_img_srr.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_img_srr_members[] = {
    {"aspect_mask", T_LONG, offsetof(vk_img_srr, aspect_mask), 0, "The aspect mask to select the color, depth and / or stencil bits to be copied"},
    {"base_mip_level", T_UINT, offsetof(vk_img_srr, base_mip_level), 0, "The first mip level to copy"},
    {"level_count", T_UINT, offsetof(vk_img_srr, level_count), 0, "The number of mipmap levels to copy"},
    {"base_array_layer", T_UINT, offsetof(vk_img_srr, base_array_layer), 0, "The starting layer to copy"},
    {"layer_count", T_UINT, offsetof(vk_img_srr, layer_count), 0, "The number of layers to copy"},
    {NULL},
};

void init_img_srr_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_img_srr_from_obj\n");

    vk_img_srr *obj = (vk_img_srr *)obj_obj;

    obj->subresource.aspectMask = obj->aspect_mask;
    obj->subresource.baseMipLevel = obj->base_mip_level;
    obj->subresource.levelCount = obj->level_count;
    obj->subresource.baseArrayLayer = obj->base_array_layer;
    obj->subresource.layerCount = obj->layer_count;
}

int vk_img_srr_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_img_srr_init\n");

    char *kwlist[] = {"aspect_mask", "base_mip_level", "level_count", "base_array_layer", "layer_count", NULL};

    vk_img_srr *self = (vk_img_srr *)self_obj;
    PyArg_ParseTupleAndKeywords(args, kwds, "|kIIII", kwlist, &self->aspect_mask, &self->base_mip_level, &self->level_count, &self->base_array_layer, &self->layer_count);
    if (PyErr_Occurred())
    {
        return -1;
    }

    init_img_srr_from_obj(self_obj);

    return 0;
}

PyTypeObject vk_img_srr_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.image_subresource_layers",
    .tp_basicsize = sizeof(vk_img_srr),
    .tp_doc = PyDoc_STR("Vulkan Image Subresource Layers Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_members = vk_img_srr_members,
    .tp_init = vk_img_srr_init,
    .tp_new = PyType_GenericNew,
};

PyObject *add_vk_img_srr_to_module(PyObject *mod)
{
    DEBUG_LOG("adding img_srr object\n");

    if (PyType_Ready(&vk_img_srr_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready img_srr type");

        goto shutdown;
    }

    Py_INCREF(&vk_img_srr_type);

    if (PyModule_AddObject(mod, "image_subresource_range", (PyObject *)&vk_img_srr_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add img_srr type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_img_srr_type);

    return NULL;
}