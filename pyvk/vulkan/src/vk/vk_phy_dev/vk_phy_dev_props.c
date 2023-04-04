#include "vk_phy_dev_props.h"
#include "log.h"

PyMemberDef vk_phy_dev_props_members[] = {
    {"api_version", T_UINT, offsetof(vk_phy_dev_props, api_version), 1, "API version of the physical device"},
    {"driver_version", T_UINT, offsetof(vk_phy_dev_props, driver_version), 1, "Driver version of the physical device"},
    {"vendor_id", T_UINT, offsetof(vk_phy_dev_props, vendor_id), 1, "Vendor ID of the physical device"},
    {"device_id", T_UINT, offsetof(vk_phy_dev_props, device_id), 1, "Device ID of the physical device"},
    {"device_type", T_UINT, offsetof(vk_phy_dev_props, device_type), 1, "Device Type of the physical device"},
    {"device_name", T_OBJECT_EX, offsetof(vk_phy_dev_props, device_name), 1, "Device Name of the physical device"},
    {"pipeline_cache_uuid", T_OBJECT_EX, offsetof(vk_phy_dev_props, pipeline_cache_uuid), 1, "Pipeline Cache UUID array of the physical device"},
    {"limits", T_OBJECT_EX, offsetof(vk_phy_dev_props, limits), 1, "Limits of the physical device"},
    {"sparse_properties", T_OBJECT_EX, offsetof(vk_phy_dev_props, sparse_properties), 1, "Sparse properties of the physical device"},
    {NULL},
};

void vk_phy_dev_props_dealloc(PyObject *self)
{
    DEBUG_LOG("vk_phy_dev_props_dealloc\n");

    Py_XDECREF(((vk_phy_dev_props *)self)->device_name);
    Py_XDECREF(((vk_phy_dev_props *)self)->pipeline_cache_uuid);
    Py_XDECREF(((vk_phy_dev_props *)self)->limits);
    Py_XDECREF(((vk_phy_dev_props *)self)->sparse_properties);

    Py_TYPE(self)->tp_free(self);
}

PyTypeObject vk_phy_dev_props_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.physical_device_properties",
    .tp_basicsize = sizeof(vk_phy_dev_props),
    .tp_doc = PyDoc_STR("Vulkan Physical Device Properties Docs"),
    .tp_members = vk_phy_dev_props_members,
    .tp_dealloc = vk_phy_dev_props_dealloc,
};

PyObject *add_vk_phy_dev_props_to_module(PyObject *mod)
{
    DEBUG_LOG("adding physical_device properties object\n");

    if (PyType_Ready(&vk_phy_dev_props_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready phy_dev_props_type type to module");

        goto shutdown;
    }

    Py_INCREF(&vk_phy_dev_props_type);

    if (PyModule_AddObject(mod, "physical_device_properties", (PyObject *)&vk_phy_dev_props_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add phy_dev_props_type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_phy_dev_props_type);

    return NULL;
}