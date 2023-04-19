#include "vk_cmd_buf_bi.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_cmd_buf_bi_members[] = {
    {"flags", T_LONG, offsetof(vk_cmd_buf_bi, flags), 0, "Bitmask of flags specifying usage behaviour for the command buffer"},
    {NULL},
};

void init_cmd_buf_bi_from_obj(PyObject* obj_obj)
{
    DEBUG_LOG("init_cmd_buf_bi_from_obj\n");

    vk_cmd_buf_bi* obj = (vk_cmd_buf_bi*) obj_obj;

    obj->bi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    obj->bi.pNext = NULL;
    obj->bi.flags = obj->flags;
    obj->bi.pInheritanceInfo = NULL;
}

int vk_cmd_buf_bi_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_cmd_buf_bi_init\n");

    vk_cmd_buf_bi *self = (vk_cmd_buf_bi *)self_obj;

    char *kwlist[] = {"flags", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|k", kwlist, &self->flags);
    if (PyErr_Occurred())
    {
        return -1;
    }

    init_cmd_buf_bi_from_obj(self_obj);

    return 0;
}

PyTypeObject vk_cmd_buf_bi_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.command_buffer_begin_info",
    .tp_basicsize = sizeof(vk_cmd_buf_bi),
    .tp_doc = PyDoc_STR("Vulkan Command Buffer Begin Info"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_members = vk_cmd_buf_bi_members,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_cmd_buf_bi_init,
};

PyObject *add_vk_cmd_buf_bi_to_module(PyObject *mod)
{
    DEBUG_LOG("adding cmd_buf_bi object\n");

    if (PyType_Ready(&vk_cmd_buf_bi_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready cmd_buf_bi type");
        goto shutdown;
    }

    Py_INCREF(&vk_cmd_buf_bi_type);

    if (PyModule_AddObject(mod, "command_buffer_begin_info", (PyObject *)&vk_cmd_buf_bi_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add cmd_buf_bi type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_cmd_buf_bi_type);

    return NULL;
}