#include "vk_cmd_buf_ai.h"
#include "vk_cmd_pool.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_cmd_buf_ai_members[] = {
    {"command_pool", T_OBJECT_EX, offsetof(vk_cmd_buf_ai, cmd_pool), 0, "The command pool to allocated the command buffer in"},
    {"level", T_ULONG, offsetof(vk_cmd_buf_ai, level), 0, "The level of the command buffers"},
    {"command_buffer_count", T_UINT, offsetof(vk_cmd_buf_ai, cmd_buf_count), 0, "The number of command buffers to be allocated"},
    {NULL},
};

void vk_cmd_buf_ai_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_cmd_buf_ai_dealloc\n");

    vk_cmd_buf_ai *self = (vk_cmd_buf_ai *)self_obj;

    if (self->cmd_pool != Py_None)
    {
        Py_XDECREF(self->cmd_pool);
    }

    Py_TYPE(self_obj)->tp_free(self_obj);
}

void init_cmd_buf_ai_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_cmd_buf_ai_from_obj\n");

    vk_cmd_buf_ai *obj = (vk_cmd_buf_ai *)obj_obj;

    obj->ai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    obj->ai.pNext = NULL;
    obj->ai.level = obj->level;
    obj->ai.commandBufferCount = obj->cmd_buf_count;
    obj->ai.commandPool = ((vk_cmd_pool*)obj->cmd_pool)->command_pool;
}

int vk_cmd_buf_ai_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_cmd_buf_ai_init\n");

    vk_cmd_buf_ai *self = (vk_cmd_buf_ai *)self_obj;

    PyObject *cmd_pool = NULL;

    PyObject *tmp = NULL;

    char *kwlist[] = {"command_pool", "level", "command_buffer_count", NULL};
    PyArg_ParseTupleAndKeywords(args, kwds, "|OKI", kwlist, &cmd_pool, &self->level, &self->cmd_buf_count);
    if (PyErr_Occurred())
    {
        return -1;
    }

    if (cmd_pool)
    {
        tmp = self->cmd_pool;
        Py_INCREF(cmd_pool);
        self->cmd_pool = cmd_pool;
        Py_XDECREF(tmp);
    }
    else
    {
        self->cmd_pool = Py_None;
    }
    DEBUG_LOG("cmd_buf_ai parsed command_pool\n");

    init_cmd_buf_ai_from_obj(self_obj);

    return 0;
}

PyTypeObject vk_cmd_buf_ai_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.command_buffer_allocate_info",
    .tp_basicsize = sizeof(vk_cmd_buf_ai),
    .tp_doc = PyDoc_STR("Vulkan Command Buffer Allocate Info Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_members = vk_cmd_buf_ai_members,
    .tp_dealloc = vk_cmd_buf_ai_dealloc,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_cmd_buf_ai_init,
};

PyObject *add_vk_cmd_buf_ai_to_module(PyObject *mod)
{
    DEBUG_LOG("adding cmd_buf_ai object\n");

    if (PyType_Ready(&vk_cmd_buf_ai_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready cmd_buf_ai type");
        goto shutdown;
    }

    Py_INCREF(&vk_cmd_buf_ai_type);

    if (PyModule_AddObject(mod, "command_buffer_allocate_info", (PyObject *)&vk_cmd_buf_ai_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add cmd_buf_ai type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_cmd_buf_ai_type);

    return NULL;
}