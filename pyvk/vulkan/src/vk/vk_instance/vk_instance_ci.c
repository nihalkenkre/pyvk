#include "vk_instance_ci.h"
#include "vk_app_info.h"

#include "log.h"
#include "utils.h"

PyMemberDef vk_instance_ci_members[] = {
    {"p_next", T_OBJECT_EX, offsetof(vk_instance_ci, p_next), 0, "TODO: Pass None for now"},
    {"flags", T_UINT, offsetof(vk_instance_ci, flags), 0, "Instance Creation Flags"},
    {"app_info", T_OBJECT_EX, offsetof(vk_instance_ci, app_info), 0, "Application Info object"},
    {"enabled_layers", T_OBJECT_EX, offsetof(vk_instance_ci, enabled_layers), 0, "List of layer names to be enabled"},
    {"enabled_extensions", T_OBJECT_EX, offsetof(vk_instance_ci, enabled_extensions), 0, "List of extension names to be enabled"},
    {NULL},
};

void vk_instance_ci_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_instance_ci_dealloc\n");

    vk_instance_ci *self = (vk_instance_ci *)self_obj;

    if (self->ci.ppEnabledLayerNames)
    {
        for (uint32_t l_idx = 0; l_idx < self->ci.enabledLayerCount; ++l_idx)
        {
            if (strcmp(self->ci.ppEnabledLayerNames[l_idx], "") != 0)
            {
                free(self->ci.ppEnabledLayerNames[l_idx]);
            }
        }

        free(self->ci.ppEnabledLayerNames);
    }

    if (self->ci.ppEnabledExtensionNames)
    {
        for (uint32_t e_idx = 0; e_idx < self->ci.enabledExtensionCount; ++e_idx)
        {
            if (strcmp(self->ci.ppEnabledExtensionNames[e_idx], "") != 0)
            {
                free(self->ci.ppEnabledExtensionNames[e_idx]);
            }
        }

        free(self->ci.ppEnabledExtensionNames);
    }

    if (self->p_next != Py_None)
    {
        Py_XDECREF(self->p_next);
    }

    if (self->app_info != Py_None)
    {
        Py_XDECREF(self->app_info);
    }

    if (self->enabled_layers != Py_None)
    {
        Py_XDECREF(self->enabled_layers);
    }

    if (self->enabled_extensions != Py_None)
    {
        Py_XDECREF(self->enabled_extensions);
    }

    Py_TYPE((PyObject *)self)->tp_free((PyObject *)self);
}

void init_instance_ci_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_instance_ci_from_obj\n");

    vk_instance_ci *obj = (vk_instance_ci *)obj_obj;

    obj->ci.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    obj->ci.pNext = NULL;
    obj->ci.flags = obj->flags;
    obj->ci.pApplicationInfo = &((vk_app_info *)obj->app_info)->app_info;

    char **layer_names = NULL;
    uint32_t layer_count = 0;
    get_names_from_list(obj->enabled_layers, &layer_names, &layer_count);

    obj->ci.enabledLayerCount = layer_count;
    obj->ci.ppEnabledLayerNames = layer_names;

    char **extension_names = NULL;
    uint32_t extension_count = 0;
    get_names_from_list(obj->enabled_extensions, &extension_names, &extension_count);

    obj->ci.enabledExtensionCount = extension_count;
    obj->ci.ppEnabledExtensionNames = extension_names;
}

int vk_instance_ci_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_instance_ci_init\n");

    vk_instance_ci *self = (vk_instance_ci *)self_obj;

    PyObject *p_next = NULL;
    PyObject *app_info = NULL;
    PyObject *enabled_layers = NULL;
    PyObject *enabled_extensions = NULL;

    PyObject *tmp = NULL;

    char *kwlist[] = { "p_next", "flags", "app_info", "enabled_layers", "enabled_extensions", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OIOOO", kwlist, &p_next, &self->flags, &app_info,
                                &enabled_layers, &enabled_extensions);
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
    DEBUG_LOG("instance_ci parsed p_next\n");

    if (app_info)
    {
        tmp = self->app_info;
        Py_INCREF(app_info);
        self->app_info = app_info;
        Py_XDECREF(tmp);
    }
    else
    {
        self->app_info = Py_None;
    }
    DEBUG_LOG("instance_ci parsed app_info\n");

    if (enabled_layers)
    {
        tmp = self->enabled_layers;
        Py_INCREF(enabled_layers);
        self->enabled_layers = enabled_layers;
        Py_XDECREF(tmp);
    }
    else
    {
        self->enabled_layers = Py_None;
    }

    DEBUG_LOG("instance_ci parsed enabled_layers\n");

    if (enabled_extensions)
    {
        tmp = self->enabled_extensions;
        Py_INCREF(enabled_extensions);
        self->enabled_extensions = enabled_extensions;
        Py_XDECREF(tmp);
    }
    else
    {
        self->enabled_extensions = Py_None;
    }
    DEBUG_LOG("instance_ci parsed enabled_extensions\n");

    init_instance_ci_from_obj(self_obj);
    if (PyErr_Occurred())
    {
        return -1;
    }

    return 0;
}

PyTypeObject vk_instance_ci_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.instance_create_info",
    .tp_basicsize = sizeof(vk_instance_ci),
    .tp_doc = PyDoc_STR("Vulkan Instance Create Info Docs"),
    .tp_members = vk_instance_ci_members,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = vk_instance_ci_dealloc,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_instance_ci_init,
};

PyObject *add_vk_instance_ci_to_module(PyObject *mod)
{
    DEBUG_LOG("adding instance_ci object\n");

    if (PyType_Ready(&vk_instance_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready instance_ci type");

        goto shutdown;
    }

    Py_INCREF(&vk_instance_ci_type);

    if (PyModule_AddObject(mod, "instance_create_info", (PyObject *)&vk_instance_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add instance_ci type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_instance_ci_type);

    return NULL;
}