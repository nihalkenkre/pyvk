#include "vk_img_view_ci.h"
#include "vk_img.h"
#include "vk_comp_map.h"
#include "vk_img_srr.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_img_view_ci_members[] = {
    {"flags", T_LONG, offsetof(vk_img_view_ci, flags), 0, "Creatong flags for the image view"},
    {"image", T_OBJECT_EX, offsetof(vk_img_view_ci, img), 0, "The image to be associated with the image view"},
    {"view_type", T_LONG, offsetof(vk_img_view_ci, view_type), 0, "The type of the image view"},
    {"format", T_LONG, offsetof(vk_img_view_ci, format), 0, "The format of the image view"},
    {"components", T_OBJECT_EX, offsetof(vk_img_view_ci, comps), 0, "Specify the remapping of the color compoents"},
    {"subresource_range", T_OBJECT_EX, offsetof(vk_img_view_ci, srr), 0, "The subresource range for this image view"},
    {NULL},
};

void vk_img_view_ci_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_img_view_ci_dealloc\n");

    vk_img_view_ci *self = (vk_img_view_ci *)self_obj;

    if (!Py_IsNone(self->img))
    {
        Py_XDECREF(self->img);
    }

    if (!Py_IsNone(self->comps))
    {
        Py_XDECREF(self->comps);
    }

    Py_TYPE(self_obj)->tp_free(self_obj);
}

void init_img_view_ci_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_img_view_ci_from_obj\n");

    vk_img_view_ci *obj = (vk_img_view_ci *)obj_obj;
    obj->ci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    obj->ci.pNext = NULL;
    obj->ci.flags = obj->flags;
    obj->ci.image = ((vk_img *)obj->img)->image;
    obj->ci.viewType = obj->view_type;
    obj->ci.format = obj->format;
    obj->ci.components = ((vk_comp_map *)obj->comps)->component_mapping;
    obj->ci.subresourceRange = ((vk_img_srr *)obj->srr)->subresource_range;
}

int vk_img_view_ci_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_img_view_ci_init\n");

    PyObject *img = NULL;
    PyObject *comps = NULL;
    PyObject *srr = NULL;

    PyObject *tmp = NULL;

    char *kwlist[] = {"flags", "image", "view_type", "format", "components", "subresource_range", NULL};

    vk_img_view_ci *self = (vk_img_view_ci *)self_obj;
    PyArg_ParseTupleAndKeywords(args, kwds, "|kOkkOO", kwlist, &self->flags, &img, &self->view_type, &self->format, &comps, &srr);
    if (PyErr_Occurred())
    {
        return -1;
    }

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
    DEBUG_LOG("img_view_ci parsed img\n");

    if(comps)
    {
        tmp = self->comps;
        Py_INCREF(comps);
        self->comps = comps;
        Py_XDECREF(tmp);
    }
    else
    {
        self->comps = Py_None;
    }
    DEBUG_LOG("img_view_ci parsed comps\n");

    if(srr)
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
    DEBUG_LOG("img_view_ci parsed srr\n");

    init_img_view_ci_from_obj(self_obj);
    return 0;
}

PyTypeObject vk_img_view_ci_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.image_view_create_info",
    .tp_basicsize = sizeof(vk_img_view_ci),
    .tp_doc = PyDoc_STR("Vulkan Image View Create Info Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_members = vk_img_view_ci_members,
    .tp_dealloc = vk_img_view_ci_dealloc,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_img_view_ci_init,
};

PyObject *add_vk_img_view_ci_to_module(PyObject *mod)
{
    DEBUG_LOG("adding img_view_ci object\n");

    if (PyType_Ready(&vk_img_view_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready img_view_ci type");

        goto shutdown;
    }

    Py_INCREF(&vk_img_view_ci_type);

    if (PyModule_AddObject(mod, "image_view_create_info", (PyObject *)&vk_img_view_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add img_view_ci type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_img_view_ci_type);

    return NULL;
}