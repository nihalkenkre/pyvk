#include "vk_dev_q_ci.h"

#include "log.h"

PyMemberDef vk_dev_q_ci_members[] = {
    {"s_type", T_UINT, offsetof(vk_dev_q_ci, s_type), 0, "Pass the vulkan.STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO"},
    {"p_next", T_OBJECT_EX, offsetof(vk_dev_q_ci, p_next), 0, "TODO: Pass None for now"},
    {"flags", T_UINT, offsetof(vk_dev_q_ci, flags), 0, "Device Queue Create Info Creation Flags"},
    {"queue_family_index", T_UINT, offsetof(vk_dev_q_ci, q_fly_idx), 0, "The queue family index"},
    {"queue_count", T_UINT, offsetof(vk_dev_q_ci, q_count), 0, "The number of queues to be created"},
    {"priorities", T_OBJECT_EX, offsetof(vk_dev_q_ci, priorities), 0, "List of priorities for the queues"},
    {NULL},
};

void vk_dev_q_ci_free(vk_dev_q_ci *self)
{
    DEBUG_LOG("vk_dev_q_ci_free\n");

    if (self->ci.pQueuePriorities)
    {
        free(self->ci.pQueuePriorities);
    }
}

void vk_dev_q_ci_dealloc(vk_dev_q_ci *self)
{
    DEBUG_LOG("vk_dev_q_ci_dealloc\n");

    if (self->p_next != Py_None)
    {
        Py_XDECREF(self->p_next);
    }

    if (self->priorities != Py_None)
    {
        Py_XDECREF(self->priorities);
    }

    Py_TYPE((PyObject *)self)->tp_free((PyObject *)self);
}

void init_dev_q_ci_from_obj(vk_dev_q_ci *obj)
{
    DEBUG_LOG("init_dev_q_ci_from_obj\n");

    obj->ci.sType = obj->s_type;
    obj->ci.pNext = NULL;
    obj->ci.flags = obj->flags;
    obj->ci.queueFamilyIndex = obj->q_fly_idx;
    obj->ci.queueCount = obj->q_count;

    get_floats_from_list(obj->priorities, &obj->ci.pQueuePriorities);
}

int vk_dev_q_ci_init(vk_dev_q_ci *self, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_dev_q_ci_init\n");

    PyObject *p_next = NULL;
    PyObject *priorities = NULL;
    PyObject *tmp = NULL;

    char *kwlist[] = {"s_type", "p_next", "flags", "queue_family_index", "queue_count", "priorities", NULL};
    PyArg_ParseTupleAndKeywords(args, kwds, "|IOIIIO", kwlist, &self->s_type, &p_next, &self->flags, &self->q_fly_idx, &self->q_count, &priorities);
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
    DEBUG_LOG("dev_q_ci parsed p_next\n");

    if (priorities)
    {
        tmp = self->priorities;
        Py_INCREF(priorities);
        self->priorities = priorities;
        Py_XDECREF(tmp);
    }
    else
    {
        self->priorities = Py_None;
    }
    DEBUG_LOG("dev_q_ci parsed priorities\n");

    if (PyList_Check(self->priorities) == 0 && !Py_IsNone(self->priorities))
    {
        PyErr_SetString(PyExc_TypeError, "Please pass a a list of floating point values between 0.0 and 1.0");
        return -1;
    }
    else if (PyList_Check(self->priorities) == 1)
    {
        Py_ssize_t count = PyList_Size(self->priorities);

        for (Py_ssize_t c_idx = 0; c_idx < count; ++c_idx)
        {
            if (PyFloat_Check(PyList_GetItem(self->priorities, c_idx)) == 0)
            {
                char buff[1024];
                sprintf(buff, "Index %d: Please pass a floating point value between 0.0 and 1.0\n", c_idx);

                PyErr_SetString(PyExc_TypeError, buff);

                return -1;
            }
        }
    }

    init_dev_q_ci_from_obj(self);
    if (PyErr_Occurred())
    {
        return -1;
    }

    return 0;
}

PyTypeObject vk_dev_q_ci_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.device_queue_create_info",
    .tp_basicsize = sizeof(vk_dev_q_ci),
    .tp_doc = PyDoc_STR("Vulkan Device Queue Create Info Docs"),
    .tp_members = vk_dev_q_ci_members,
    .tp_dealloc = vk_dev_q_ci_dealloc,
    .tp_free = vk_dev_q_ci_free,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_dev_q_ci_init,
};

PyObject *add_vk_dev_q_ci_to_module(PyObject *mod)
{
    DEBUG_LOG("adding dev_q_ci object\n");

    if (PyType_Ready(&vk_dev_q_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready dev_q_ci type");
        goto shutdown;
    }

    Py_INCREF(&vk_dev_q_ci_type);

    if (PyModule_AddObject(mod, "device_queue_create_info", (PyObject *)&vk_dev_q_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add dev_q_ci type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_dev_q_ci_type);

    return NULL;
}