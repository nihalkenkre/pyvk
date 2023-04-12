#include "vk_q_fly_props.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_q_fly_props_members[] = {
    {"queue_flags", T_UINT, offsetof(vk_q_fly_props, q_flags), 1, "Bit mask of capabilities of this queue famliy"},
    {"queue_count", T_UINT, offsetof(vk_q_fly_props, q_count), 1, "The number of queues in this queue family"},
    {"timestamp_valid_bits", T_UINT, offsetof(vk_q_fly_props, timestamp_valid_bits), 1, "The count of meaningful bits in the timestamp"},
    {"min_image_transfer_granularity", T_OBJECT_EX, offsetof(vk_q_fly_props, min_image_xfer_grains), 1, "The minimum granularity supported for image transfer operations on this queue family"},
    {NULL},
};

void vk_q_fly_props_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_q_fly_props_dealloc\n");

    vk_q_fly_props *self = (vk_q_fly_props *)self_obj;

    if (self->min_image_xfer_grains != Py_None)
    {
        Py_XDECREF(self->min_image_xfer_grains);
    }

    Py_TYPE((PyObject *)self)->tp_free((PyObject *)self);
}

PyTypeObject vk_q_fly_props_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.queue_family_properties",
    .tp_basicsize = sizeof(vk_q_fly_props),
    .tp_doc = PyDoc_STR("Vulkan Queue Family Properties Docs"),
    .tp_members = vk_q_fly_props_members,
    .tp_dealloc = vk_q_fly_props_dealloc,
};

PyObject *add_vk_q_fly_props_to_module(PyObject *mod)
{
    DEBUG_LOG("adding q_fly_props object\n");

    if (PyType_Ready(&vk_q_fly_props_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready q_fly_props_ci type");

        goto shutdown;
    }

    Py_INCREF(&vk_q_fly_props_type);

    if (PyModule_AddObject(mod, "queue_family_properties", (PyObject *)&vk_q_fly_props_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add q_fly_props type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_q_fly_props_type);

    return NULL;
}
