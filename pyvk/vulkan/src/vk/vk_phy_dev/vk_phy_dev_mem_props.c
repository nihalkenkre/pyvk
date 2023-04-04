#include "vk_phy_dev_mem_props.h"

PyMemberDef vk_phy_dev_mem_props_members[] = {
    {"types", T_OBJECT_EX, offsetof(vk_phy_dev_mem_props, types), 1, "List of memory types of the physical device"},
    {"heaps", T_OBJECT_EX, offsetof(vk_phy_dev_mem_props, heaps), 1, "List of memory heaps of the physical device"},
    {NULL},
};

void vk_phy_dev_mem_props_dealloc(PyObject *self)
{
    DEBUG_LOG("vk_phy_dev_mem_props_dealloc\n");
    
    Py_XDECREF(((vk_phy_dev_mem_props*)self)->types);
    Py_XDECREF(((vk_phy_dev_mem_props*)self)->heaps);

    Py_TYPE(self)->tp_free(self);
}

PyTypeObject vk_phy_dev_mem_props_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.physical_device_memory_properties",
    .tp_basicsize = sizeof(vk_phy_dev_mem_props),
    .tp_doc = PyDoc_STR("Vulkan Physical Device Memory Properties Docs"),
    .tp_members = vk_phy_dev_mem_props_members,
    .tp_dealloc = vk_phy_dev_mem_props_dealloc,
};

PyObject *add_vk_phy_dev_mem_props_to_module(PyObject *mod)
{
    DEBUG_LOG("adding physical_device_memory_properties object\n");

    if (PyType_Ready(&vk_phy_dev_mem_props_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready phy_dev_mem_props_type type to module");

        goto shutdown;
    }

    Py_INCREF(&vk_phy_dev_mem_props_type);

    if (PyModule_AddObject(mod, "physical_device_memory_properties", (PyObject *)&vk_phy_dev_mem_props_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add phy_dev_mem_props_type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_phy_dev_mem_props_type);

    return NULL;
}