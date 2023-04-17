#include "vk_dev_q_ci.h"
#include "vk_dev_ci.h"
#include "vk_phy_dev_features.h"

#include "log.h"
#include "utils.h"

PyMemberDef vk_dev_ci_members[] = {
    {"p_next", T_OBJECT_EX, offsetof(vk_dev_ci, p_next), 0, "TODO: Pass None for now"},
    {"flags", T_UINT, offsetof(vk_dev_ci, flags), 0, "Device Create Info Creation Flags"},
    {"queue_create_infos", T_OBJECT_EX, offsetof(vk_dev_ci, queue_create_infos), 0, "List of vulkan.device_queue_create_info objects"},
    {"enabled_layers", T_OBJECT_EX, offsetof(vk_dev_ci, enabled_layers), 0, "List of names of the layers to be enabled"},
    {"enabled_extensions", T_OBJECT_EX, offsetof(vk_dev_ci, enabled_extensions), 0, "List of names of the extensions to be enabled"},
    {"enabled_features", T_OBJECT_EX, offsetof(vk_dev_ci, enabled_features), 0, "Pass a vulkan.physical_device_features object"},
    {NULL},
};

void vk_dev_ci_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_dev_ci_dealloc\n");

    vk_dev_ci *self = (vk_dev_ci *)self_obj;

    if (self->ci.ppEnabledLayerNames)
    {
        for (uint32_t l_idx = 0; l_idx < self->ci.enabledLayerCount; ++l_idx)
        {
            if (strcmp(self->ci.ppEnabledLayerNames[l_idx], "") != 0)
            {
                free((void *)self->ci.ppEnabledLayerNames[l_idx]);
            }
        }

        free((void *)self->ci.ppEnabledLayerNames);
    }

    if (self->ci.ppEnabledExtensionNames)
    {
        for (uint32_t e_idx = 0; e_idx < self->ci.enabledExtensionCount; ++e_idx)
        {
            if (strcmp(self->ci.ppEnabledExtensionNames[e_idx], "") != 0)
            {
                free((void *)self->ci.ppEnabledExtensionNames[e_idx]);
            }
        }

        free((void *)self->ci.ppEnabledExtensionNames);
    }

    if (self->p_next != Py_None)
    {
        Py_XDECREF(self->p_next);
    }

    if (self->queue_create_infos != Py_None)
    {
        Py_XDECREF(self->queue_create_infos);
    }

    if (self->enabled_layers != Py_None)
    {
        Py_XDECREF(self->enabled_layers);
    }

    if (self->enabled_extensions != Py_None)
    {
        Py_XDECREF(self->enabled_extensions);
    }

    if (self->enabled_features != Py_None)
    {
        Py_XDECREF(self->enabled_features);
    }

    Py_TYPE((PyObject *)self)->tp_free((PyObject *)self);
}

void get_queue_cis_from_list(PyObject *obj, VkDeviceQueueCreateInfo **q_cis, uint32_t *q_ci_count)
{
    DEBUG_LOG("get_queue_cis_from_obj\n");

    *q_ci_count = (uint32_t)PyList_Size(obj);

    *q_cis = (VkDeviceQueueCreateInfo *)malloc(sizeof(VkDeviceQueueCreateInfo) * *q_ci_count);

    for (Py_ssize_t idx = 0; idx < *q_ci_count; ++idx)
    {
        *(*q_cis + idx) = ((vk_dev_q_ci *)PyList_GetItem(obj, idx))->ci;
    }
}

void init_device_ci_from_obj(PyObject *obj_obj)
{
    DEBUG_LOG("init_device_ci_from_obj\n");

    vk_dev_ci *obj = (vk_dev_ci *)obj_obj;

    obj->ci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    obj->ci.pNext = NULL;
    obj->ci.flags = obj->flags;

    VkDeviceQueueCreateInfo *q_cis = NULL;
    uint32_t q_ci_count = 0;
    get_queue_cis_from_list(obj->queue_create_infos, &q_cis, &q_ci_count);

    obj->ci.pQueueCreateInfos = q_cis;
    obj->ci.queueCreateInfoCount = q_ci_count;

    char **layers_names = NULL;
    uint32_t layer_count = 0;
    get_names_from_list(obj->enabled_layers, &layers_names, &layer_count);

    obj->ci.ppEnabledLayerNames = layers_names;
    obj->ci.enabledLayerCount = layer_count;

    char **extension_names = NULL;
    uint32_t extension_count = 0;
    get_names_from_list(obj->enabled_extensions, &extension_names, &extension_count);

    obj->ci.ppEnabledExtensionNames = extension_names;
    obj->ci.enabledExtensionCount = extension_count;

    obj->ci.pEnabledFeatures = &((vk_phy_dev_features *)obj->enabled_features)->features;
}

int vk_dev_ci_init(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_dev_ci_init\n");

    vk_dev_ci *self = (vk_dev_ci *)self_obj;

    PyObject *p_next = NULL;
    PyObject *queue_create_infos = NULL;
    PyObject *enabled_layers = NULL;
    PyObject *enabled_extensions = NULL;
    PyObject *enabled_features = NULL;

    PyObject *tmp = NULL;

    char *kwlist[] = {"p_next", "flags", "queue_create_infos", "enabled_layers", "enabled_extensions", "enabled_features", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OIOOOO", kwlist, &p_next, &self->flags, &queue_create_infos, &enabled_layers, &enabled_extensions, &enabled_features);
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
    DEBUG_LOG("dev_ci parsed p_next\n");

    if (queue_create_infos)
    {
        tmp = self->queue_create_infos;
        Py_INCREF(queue_create_infos);
        self->queue_create_infos = queue_create_infos;
        Py_XDECREF(tmp);
    }
    else
    {
        self->queue_create_infos = Py_None;
    }

    DEBUG_LOG("dev_ci parsed queue_create_infos\n");

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
    DEBUG_LOG("dev_ci parsed enabled_layers\n");

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

    DEBUG_LOG("dev_ci parsed enabled_extensions\n");

    if (enabled_features)
    {
        tmp = self->enabled_features;
        Py_INCREF(enabled_features);
        self->enabled_features = enabled_features;
        Py_XDECREF(tmp);
    }
    else
    {
        self->enabled_features = Py_None;
    }
    DEBUG_LOG("dev_ci parsed enabled_features\n");

    init_device_ci_from_obj(self_obj);

    return 0;
}

PyTypeObject vk_dev_ci_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.device_create_info",
    .tp_basicsize = sizeof(vk_dev_ci),
    .tp_doc = PyDoc_STR("Vulkan Device Create Info Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_members = vk_dev_ci_members,
    .tp_dealloc = vk_dev_ci_dealloc,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_dev_ci_init,
};

PyObject *add_vk_dev_ci_to_module(PyObject *mod)
{
    DEBUG_LOG("adding dev_ci object\n");

    if (PyType_Ready(&vk_dev_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready dev_ci type");

        goto shutdown;
    }

    Py_INCREF(&vk_dev_ci_type);

    if (PyModule_AddObject(mod, "device_create_info", (PyObject *)&vk_dev_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add dev_ci type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_dev_ci_type);

    return NULL;
}