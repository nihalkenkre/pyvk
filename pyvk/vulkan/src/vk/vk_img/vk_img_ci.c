#include "vk_img_ci.h"

#include <structmember.h>

#include "log.h"
#include "utils.h"

PyMemberDef vk_img_ci_members[] = {
    {"p_next", T_OBJECT_EX, offsetof(vk_img_ci, p_next), 0, "TODO: Pass None for now"},
    {"flags", T_UINT, offsetof(vk_img_ci, flags), 0, "Image Creation flags"},
    {"image_type", T_LONG, offsetof(vk_img_ci, image_type), 0, "The image type"},
    {"format", T_LONG, offsetof(vk_img_ci, format), 0, "The format of the image"},
    {"extent", T_OBJECT_EX, offsetof(vk_img_ci, extent), 0, "The extent of the image"},
    {"mip_levels", T_UINT, offsetof(vk_img_ci, mip_levels), 0, "The number of mip map levels"},
    {"array_layers", T_UINT, offsetof(vk_img_ci, array_layers), 0, "The number of array layers"},
    {"tiling", T_LONG, offsetof(vk_img_ci, tiling), 0, "The tiling"},
    {"usage", T_LONG, offsetof(vk_img_ci, usage), 0, "The usage"},
    {"sharing_mode", T_LONG, offsetof(vk_img_ci, sharing_mode), 0, "The sharing mode"},
    {"queue_family_indices", T_OBJECT_EX, offsetof(vk_img_ci, q_fly_idx), 0, "The indices of the queue family that this images can be used with"},
    {"initial_layout", T_LONG, offsetof(vk_img_ci, initial_layout), 0, "The initial layout of the image"},
    {NULL},
};

void vk_img_ci_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_img_ci_dealloc\n");

    vk_img_ci *self = (vk_img_ci *)self_obj;

    if (!Py_IsNone(self->p_next))
    {
        Py_XDECREF(self->p_next);
    }

    if (!Py_IsNone(self->extent))
    {
        Py_XDECREF(self->extent);
    }

    if (!Py_IsNone(self->q_fly_idx))
    {
        Py_XDECREF(self->q_fly_idx);
    }

    Py_TYPE(self_obj)->tp_free(self_obj);
}

void init_img_ci_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_img_ci_from_obj\n");

    vk_img_ci *obj = (vk_img_ci *)obj_obj;

    obj->ci.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    obj->ci.pNext = NULL;
    obj->ci.flags = obj->flags;
    obj->ci.imageType = obj->image_type;
    obj->ci.format = obj->format;

    obj->ci.extent.width = (uint32_t)PyLong_AsLong(PyTuple_GetItem(obj->extent, 0));
    obj->ci.extent.height = (uint32_t)PyLong_AsLong(PyTuple_GetItem(obj->extent, 1));
    obj->ci.extent.depth = (uint32_t)PyLong_AsLong(PyTuple_GetItem(obj->extent, 2));

    obj->ci.mipLevels = obj->mip_levels;
    obj->ci.arrayLayers = obj->array_layers;
    obj->ci.samples = obj->samples;
    obj->ci.tiling = obj->tiling;
    obj->ci.usage = obj->usage;
    obj->ci.sharingMode = obj->sharing_mode;

    get_uint32s_from_list(obj->q_fly_idx, &obj->ci.pQueueFamilyIndices, &obj->ci.queueFamilyIndexCount);

    obj->ci.initialLayout = obj->initial_layout;
}

int vk_img_ci_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_img_ci_init\n");

    PyObject *p_next = NULL;
    PyObject *extent = NULL;
    PyObject *q_fly_idx = NULL;

    PyObject *tmp = NULL;

    vk_img_ci *self = (vk_img_ci *)self_obj;

    char *kwlist[] = {"p_next", "flags", "image_type", "format", "extent", "mip_levels", "array_layers", "samples",
                      "tiling", "usage", "sharing_mode", "queue_family_indices", "initial_layout", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OIkkOIIkkkkOk", kwlist, &p_next, &self->flags, &self->image_type,
                                &self->format, &extent, &self->mip_levels, &self->array_layers, &self->samples,
                                &self->tiling, &self->usage, &self->sharing_mode, &q_fly_idx, &self->initial_layout);
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
    DEBUG_LOG("img_ci parsed p_next\n");

    if (extent)
    {
        tmp = self->extent;
        Py_INCREF(extent);
        self->extent = extent;
        Py_XDECREF(tmp);
    }
    else
    {
        self->extent = Py_None;
    }
    DEBUG_LOG("img_ci parsed extent\n");

    if (q_fly_idx)
    {
        tmp = self->q_fly_idx;
        Py_INCREF(q_fly_idx);
        self->q_fly_idx = q_fly_idx;
        Py_XDECREF(tmp);
    }
    else
    {
        self->q_fly_idx = Py_None;
    }
    DEBUG_LOG("img_ci parsed q_fly_idx\n");

    init_img_ci_from_obj(self_obj);
    if (PyErr_Occurred())
    {
        return -1;
    }

    return 0;
}

PyTypeObject vk_img_ci_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.image_create_info",
    .tp_basicsize = sizeof(vk_img_ci),
    .tp_doc = PyDoc_STR("Vulkan Image Create Info Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = vk_img_ci_dealloc,
    .tp_members = vk_img_ci_members,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_img_ci_init,
};

PyObject *add_vk_img_ci_to_module(PyObject *mod)
{
    DEBUG_LOG("adding img_ci object\n");

    if (PyType_Ready(&vk_img_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready img_ci type");

        goto shutdown;
    }

    Py_INCREF(&vk_img_ci_type);

    if (PyModule_AddObject(mod, "image_create_info", (PyObject *)&vk_img_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add img_ci type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_img_ci_type);

    return NULL;
}