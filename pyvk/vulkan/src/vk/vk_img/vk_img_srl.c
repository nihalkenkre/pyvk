#include "vk_img_srl.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_img_srl_members[] = {
    {"aspect_mask", T_LONG, offsetof(vk_img_srl, aspect_mask), 0, "The aspect mask to select the color, depth and / or stencil bits to be copied"},
    {"mip_level", T_UINT, offsetof(vk_img_srl, mip_level), 0, "The mip level to copy"},
    {"base_array_layer", T_UINT, offsetof(vk_img_srl, base_array_layer), 0, "The starting layer to copy"},
    {"layer_count", T_UINT, offsetof(vk_img_srl, layer_count), 0, "The number of layers to copy"},
    {NULL},
};

void init_img_srl_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_img_srl_from_obj\n");

    vk_img_srl *obj = (vk_img_srl *)obj_obj;

    obj->subresource_layers.aspectMask = obj->aspect_mask;
    obj->subresource_layers.mipLevel = obj->mip_level;
    obj->subresource_layers.baseArrayLayer = obj->base_array_layer;
    obj->subresource_layers.layerCount = obj->layer_count;
}

int vk_img_srl_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_img_srl_init\n");

    char *kwlist[] = {"aspect_mask", "mip_level", "base_array_layer", "layer_count", NULL};

    vk_img_srl *self = (vk_img_srl *)self_obj;
    PyArg_ParseTupleAndKeywords(args, kwds, "|kIII", kwlist, &self->aspect_mask, &self->mip_level, &self->base_array_layer, &self->layer_count);
    if (PyErr_Occurred())
    {
        return -1;
    }

    init_img_srl_from_obj(self_obj);

    return 0;
}

PyTypeObject vk_img_srl_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.image_subresource_layers",
    .tp_basicsize = sizeof(vk_img_srl),
    .tp_doc = PyDoc_STR("Vulkan Image Subresource Layers Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_members = vk_img_srl_members,
    .tp_init = vk_img_srl_init,
    .tp_new = PyType_GenericNew,
};

PyObject *add_vk_img_srl_to_module(PyObject *mod)
{
    DEBUG_LOG("adding img_srl object\n");

    if (PyType_Ready(&vk_img_srl_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready img_srl type");

        goto shutdown;
    }

    Py_INCREF(&vk_img_srl_type);

    if (PyModule_AddObject(mod, "image_subresource_layers", (PyObject *)&vk_img_srl_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add img_srl type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_img_srl_type);

    return NULL;
}