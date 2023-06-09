#include "vk_surface_ci.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_surface_ci_members[] = {
    {"p_next", T_OBJECT_EX, offsetof(vk_surface_ci, p_next), 0, "TODO: Pass None for now"},
    {"flags", T_UINT, offsetof(vk_surface_ci, flags), 0, "Surface Creation Flags"},
    {"h_wnd", T_LONG, offsetof(vk_surface_ci, h_wnd), 0, "The handle of the window"},
    {NULL},
};

void vk_surface_ci_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_surface_ci_dealloc\n");

    vk_surface_ci *self = (vk_surface_ci *)self_obj;

    if (self->p_next != Py_None)
    {
        Py_XDECREF(self->p_next);
    }

    Py_TYPE((PyObject *)self)->tp_free((PyObject *)self);
}

void init_surface_ci_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_surface_from_obj\n");

    vk_surface_ci *obj = (vk_surface_ci *)obj_obj;

    obj->ci.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    obj->ci.pNext = NULL;
    obj->ci.flags = obj->flags;
    obj->ci.hwnd = (HWND)obj->h_wnd;
    obj->ci.hinstance = (HINSTANCE)GetModuleHandle(NULL);
}

int vk_surface_ci_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_surface_ci_init\n");

    vk_surface_ci *self = (vk_surface_ci *)self_obj;

    PyObject *p_next = NULL;
    PyObject *tmp = NULL;

    char *kwlist[] = {"p_next", "flags", "h_wnd", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OIk", kwlist, &p_next, &self->flags, &self->h_wnd);
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
    DEBUG_LOG("surface_ci parsed p_next\n");

    init_surface_ci_from_obj(self_obj);

    return 0;
}

PyTypeObject vk_surface_ci_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.surface_create_info",
    .tp_basicsize = sizeof(vk_surface_ci),
    .tp_doc = PyDoc_STR("Vulkan Surface Create Info Docs"),
    .tp_members = vk_surface_ci_members,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = vk_surface_ci_dealloc,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_surface_ci_init,
};

PyObject *add_vk_surface_ci_to_module(PyObject *mod)
{
    DEBUG_LOG("adding surface_ci object\n");

    if (PyType_Ready(&vk_surface_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready surface_ci type");
        goto shutdown;
    }

    Py_INCREF(&vk_surface_ci_type);

    if (PyModule_AddObject(mod, "surface_create_info", (PyObject *)&vk_surface_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add surface_ci type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_surface_ci_type);

    return NULL;
}