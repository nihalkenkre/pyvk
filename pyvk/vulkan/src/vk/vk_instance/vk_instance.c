#include "vk_surface.h"
#include "vk_surface_ci.h"
#include "vk_phy_dev.h"
#include "vk_instance.h"
#include "log.h"

#include <Windows.h>
#include <vulkan/vulkan_win32.h>

PyObject *vk_instance_get_phy_devs(PyObject *self)
{
    vk_instance *inst = (vk_instance *)self;

    uint32_t phy_dev_count = 0;

    VkResult result = vkEnumeratePhysicalDevices(inst->instance, &phy_dev_count, NULL);
    if (result != VK_SUCCESS)
    {
        goto shutdown;
    }
    VkPhysicalDevice *phy_devs = (VkPhysicalDevice *)malloc(sizeof(VkPhysicalDevice) * phy_dev_count);

    result = vkEnumeratePhysicalDevices(inst->instance, &phy_dev_count, phy_devs);
    if (result != VK_SUCCESS)
    {
        goto shutdown;
    }

    PyObject *phy_dev_list = PyList_New(phy_dev_count);

    for (uint32_t phy_dev_idx = 0; phy_dev_idx < phy_dev_count; ++phy_dev_idx)
    {
        vk_phy_dev *phy_dev = PyObject_New(vk_phy_dev, &vk_phy_dev_type);
        phy_dev->phy_dev = phy_devs[phy_dev_idx];

        PyList_SetItem(phy_dev_list, phy_dev_idx, (PyObject *)phy_dev);
    }

    free(phy_devs);
    {
        PyObject *return_obj = PyTuple_New(2);
        PyTuple_SetItem(return_obj, 0, phy_dev_list);
        PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

        return return_obj;
    }

shutdown:
    free(phy_devs);
    {
        PyObject *return_obj = PyTuple_New(2);
        PyTuple_SetItem(return_obj, 0, Py_None);
        PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

        return return_obj;
    }
}

PyObject *vk_instance_create_surface(PyObject *self, PyObject *args)
{
    DEBUG_LOG("vk_instance_create_surface\n");

    PyObject *surface_ci_obj = NULL;

    PyArg_Parse(args, "O", &surface_ci_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_surface_ci *ci_obj = (vk_surface_ci *)surface_ci_obj;

    vk_surface *surf = PyObject_NEW(vk_surface, &vk_surface_type);
    VkResult result = vkCreateWin32SurfaceKHR(((vk_instance *)self)->instance, &ci_obj->ci, NULL, &surf->surface);

    PyObject *return_obj = PyTuple_New(2);
    PyTuple_SetItem(return_obj, 0, (PyObject *)surf);
    PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

    return return_obj;
}

PyObject *vk_instance_destroy_surface(PyObject *self, PyObject *args)
{
    PyObject *surf;
    PyArg_Parse(args, "O", &surf);

    if (PyErr_Occurred())
    {
        return NULL;
    }

    if (((vk_surface *)surf)->surface != VK_NULL_HANDLE)
    {
        DEBUG_LOG("destroying surface\n");
        vkDestroySurfaceKHR(((vk_instance *)self)->instance, ((vk_surface *)surf)->surface, NULL);
    }

    Py_XDECREF(surf);

    return Py_None;
}

PyMethodDef vk_instance_methods[] = {
    {"get_physical_devices", (PyCFunction)vk_instance_get_phy_devs, METH_NOARGS, NULL},
    {"create_surface", (PyCFunction)vk_instance_create_surface, METH_O, NULL},
    {"destroy_surface", (PyCFunction)vk_instance_destroy_surface, METH_O, NULL},
    {NULL},
};

PyTypeObject vk_instance_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.instance",
    .tp_basicsize = sizeof(vk_instance),
    .tp_doc = PyDoc_STR("Vulkan Instance Docs"),
    .tp_methods = vk_instance_methods,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
};

PyObject *add_vk_instance_to_module(PyObject *mod)
{
    DEBUG_LOG("adding instance object\n");

    if (PyType_Ready(&vk_instance_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready instance type");

        goto shutdown;
    }

    Py_INCREF(&vk_instance_type);

    if (PyModule_AddObject(mod, "instance", (PyObject *)&vk_instance_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add instance type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_instance_type);

    return NULL;
}