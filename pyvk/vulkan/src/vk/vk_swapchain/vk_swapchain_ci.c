#include "vk_swapchain_ci.h"
#include "vk_surface.h"
#include "vk_swapchain.h"

#include "log.h"
#include "utils.h"

PyMemberDef vk_swapchain_ci_members[] = {
    {"s_type", T_LONG, offsetof(vk_swapchain_ci, s_type), 0, "Pass the vulkan.STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR"},
    {"p_next", T_OBJECT_EX, offsetof(vk_swapchain_ci, p_next), 0, "TODO: Pass None for now"},
    {"flags", T_UINT, offsetof(vk_swapchain_ci, flags), 0, "Swapchain creation flags"},
    {"surface", T_OBJECT_EX, offsetof(vk_swapchain_ci, surface), 0, "Pass the surface for which the swapchain is to be created"},
    {"min_image_count", T_UINT, offsetof(vk_swapchain_ci, min_image_count), 0, "The minimum number of swapchain images to be created"},
    {"image_format", T_LONG, offsetof(vk_swapchain_ci, image_format), 0, "The format of the swapchain images"},
    {"image_color_space", T_LONG, offsetof(vk_swapchain_ci, image_color_space), 0, "The color space of the swapchain images"},
    {"image_extent", T_OBJECT_EX, offsetof(vk_swapchain_ci, image_extent), 0, "The extent of the swapchain images"},
    {"image_array_layers", T_UINT, offsetof(vk_swapchain_ci, image_array_layers), 0, "The number of array layers in a swapchain image"},
    {"image_usage_flags", T_UINT, offsetof(vk_swapchain_ci, image_usage_flags), 0, "The flags defining the usage of the swapchain images"},
    {"image_sharing_mode", T_LONG, offsetof(vk_swapchain_ci, image_sharing_mode), 0, "The sharing mode for the swapchain images"},
    {"queue_family_indices", T_OBJECT_EX, offsetof(vk_swapchain_ci, queue_family_indices), 0, "The queue families having access to the swapchain images"},
    {"pre_transform", T_LONG, offsetof(vk_swapchain_ci, pre_transform), 0, "The pre transform bit flags of the swapchain"},
    {"composite_alpha", T_LONG, offsetof(vk_swapchain_ci, composite_alpha), 0, "The composite alpha bit flags of the swapchain"},
    {"present_mode", T_LONG, offsetof(vk_swapchain_ci, present_mode), 0, "The presentation mode of the swapchain"},
    {"clipped", T_BOOL, offsetof(vk_swapchain_ci, clipped), 0, "Whether to discard the rendering operations affecting regions of the surface that are not visible"},
    {"old_swapchain", T_OBJECT_EX, offsetof(vk_swapchain_ci, old_swapchain), 0, "Old swapchain if present, which can enable resource re-use"},
    {NULL},
};

void vk_swapchain_ci_dealloc(vk_swapchain_ci *self)
{
    DEBUG_LOG("vk_swapchain_ci_dealloc\n");

    if (self->p_next != Py_None)
    {
        Py_XDECREF(self->p_next);
    }

    if (self->surface != Py_None)
    {
        Py_XDECREF(self->surface);
    }

    if (self->image_extent != Py_None)
    {
        Py_XDECREF(self->image_extent);
    }

    if (self->queue_family_indices != Py_None)
    {
        Py_XDECREF(self->queue_family_indices);
    }

    if (self->old_swapchain != Py_None)
    {
        Py_XDECREF(self->old_swapchain);
    }

    if (self->ci.pQueueFamilyIndices != NULL)
    {
        free(self->ci.pQueueFamilyIndices);
    }

    Py_TYPE((PyObject *)self)->tp_free((PyObject *)self);
}

void init_swapchain_ci_from_obj(vk_swapchain_ci *obj)
{
    DEBUG_LOG("init_swapchain_ci_from_obj\n");

    obj->ci.sType = obj->s_type;
    obj->ci.pNext = NULL;
    obj->ci.flags = obj->flags;
    obj->ci.surface = ((vk_surface *)obj->surface)->surface;
    obj->ci.minImageCount = obj->min_image_count;
    obj->ci.imageFormat = obj->image_format;
    obj->ci.imageColorSpace = obj->image_color_space;

    obj->ci.imageExtent.width = PyLong_FromLong(PyTuple_GetItem(obj->image_extent, 0));
    obj->ci.imageExtent.height = PyLong_FromLong(PyTuple_GetItem(obj->image_extent, 1));

    obj->ci.imageArrayLayers = obj->image_array_layers;
    obj->ci.imageUsage = obj->image_usage_flags;

    obj->ci.imageSharingMode = obj->image_sharing_mode;
    obj->ci.queueFamilyIndexCount = PyList_Size(obj->queue_family_indices);
    get_floats_from_list(obj->queue_family_indices, &obj->ci.pQueueFamilyIndices);

    obj->ci.preTransform = obj->pre_transform;
    obj->ci.compositeAlpha = obj->composite_alpha;
    obj->ci.presentMode = obj->present_mode;
    obj->ci.clipped = obj->clipped;

    if ((vk_swapchain *)obj->old_swapchain != Py_None)
    {
        obj->ci.oldSwapchain = ((vk_swapchain *)obj->old_swapchain)->swapchain;
    }
    else
    {
        obj->ci.oldSwapchain = VK_NULL_HANDLE;
    }
}

int vk_swapchain_ci_init(vk_swapchain_ci *self, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_swapchain_ci_init\n");

    PyObject *p_next = NULL;
    PyObject *surface = NULL;
    PyObject *image_extent = NULL;
    PyObject *q_fly_idx = NULL;
    PyObject *old_swapchain = NULL;

    PyObject *tmp = NULL;

    char *kwlist[] = {"s_type", "p_next", "flags", "surface", "min_image_count", "image_format",
                      "image_color_space", "image_extent", "image_array_layers",
                      "image_usage_flags", "image_sharing_mode", "queue_family_indices",
                      "pre_transform", "composite_alpha", "present_mode", "clipped", "old_swapchain", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|kOIOIkkOIkkOkkkpO", kwlist, &self->s_type, &p_next, &self->flags,
                                &surface, &self->min_image_count, &self->image_format, &self->image_color_space, &image_extent, &self->image_array_layers,
                                &self->image_usage_flags, &self->image_sharing_mode, &q_fly_idx, &self->pre_transform, &self->composite_alpha,
                                &self->present_mode, &self->clipped, &old_swapchain);

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
    DEBUG_LOG("swapchain_ci parsed p_next\n");

    if (surface)
    {
        tmp = self->surface;
        Py_INCREF(surface);
        self->surface = surface;
        Py_XDECREF(tmp);
    }
    else
    {
        self->surface = Py_None;
    }
    DEBUG_LOG("swapchain_ci parsed surface\n");

    if (image_extent)
    {
        tmp = self->image_extent;
        Py_INCREF(image_extent);
        self->image_extent = image_extent;
        Py_XDECREF(tmp);
    }
    else
    {
        self->image_extent = Py_None;
    }
    DEBUG_LOG("swapchain_ci parsed image_extent\n");

    if (q_fly_idx)
    {
        tmp = self->queue_family_indices;
        Py_INCREF(q_fly_idx);
        self->queue_family_indices = q_fly_idx;
        Py_XDECREF(tmp);
    }
    else
    {
        self->queue_family_indices = Py_None;
    }
    DEBUG_LOG("swapchain_ci parsed queue_family_indices\n");

    if (old_swapchain)
    {
        tmp = self->old_swapchain;
        Py_INCREF(old_swapchain);
        self->old_swapchain = old_swapchain;
        Py_XDECREF(tmp);
    }
    else
    {
        self->old_swapchain = Py_None;
    }
    DEBUG_LOG("swapchain_ci parsed old_swapchain\n");

    init_swapchain_ci_from_obj(self);
    if (PyErr_Occurred())
    {
        return -1;
    }

    return 0;
}

PyTypeObject vk_swapchain_ci_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.swapchain_create_info",
    .tp_basicsize = sizeof(vk_swapchain_ci),
    .tp_doc = PyDoc_STR("Vulkan Swapchain Create Info Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_members = vk_swapchain_ci_members,
    .tp_dealloc = vk_swapchain_ci_dealloc,
    .tp_new = PyType_GenericNew,
    .tp_init = vk_swapchain_ci_init,
};

PyObject *add_vk_swapchain_ci_to_module(PyObject *mod)
{
    DEBUG_LOG("adding swapchain_ci object\n");

    if (PyType_Ready(&vk_swapchain_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready swapchain_ci type");

        goto shutdown;
    }

    Py_INCREF(&vk_swapchain_ci_type);

    if (PyModule_AddObject(mod, "swapchain_create_info", (PyObject *)&vk_swapchain_ci_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add swapchain_ci type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_swapchain_ci_type);

    return NULL;
}
