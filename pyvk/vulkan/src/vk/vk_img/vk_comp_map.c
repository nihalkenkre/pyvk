#include "vk_comp_map.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_comp_map_members[] = {
    {"r", T_LONG, offsetof(vk_comp_map, r), 0, "The swizzle type for the r component"},
    {"g", T_LONG, offsetof(vk_comp_map, g), 0, "The swizzle type for the g component"},
    {"b", T_LONG, offsetof(vk_comp_map, b), 0, "The swizzle type for the b component"},
    {"a", T_LONG, offsetof(vk_comp_map, a), 0, "The swizzle type for the a component"},
    {NULL},
};

void init_comp_map_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_comp_map_from+obj\n");

    vk_comp_map *obj = (vk_comp_map *)obj_obj;

    obj->component_mapping.r = obj->r;
    obj->component_mapping.g = obj->g;
    obj->component_mapping.b = obj->b;
    obj->component_mapping.a = obj->a;
}

int vk_comp_map_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_comp_map_init\n");

    vk_comp_map *self = (vk_comp_map *)self_obj;

    char *kwlist[] = {"r", "g", "b", "a", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|kkkk", kwlist, &self->r, &self->g, &self->b, &self->a);
    if (PyErr_Occurred())
    {
        return -1;
    }

    init_comp_map_from_obj(self_obj);

    return 0;
}

PyTypeObject vk_comp_map_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.component_mapping",
    .tp_basicsize = sizeof(vk_comp_map),
    .tp_doc = PyDoc_STR("Vulkan Component Mapping Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_members = vk_comp_map_members,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_comp_map_init,
};

PyObject *add_vk_comp_map_to_module(PyObject *mod)
{
    DEBUG_LOG("adding comp_map object\n");

    if (PyType_Ready(&vk_comp_map_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready comp_map type");
        goto shutdown;
    }

    Py_INCREF(&vk_comp_map_type);

    if (PyModule_AddObject(mod, "component_mapping", (PyObject *)&vk_comp_map_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add comp_map type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_comp_map_type);

    return NULL;
}
