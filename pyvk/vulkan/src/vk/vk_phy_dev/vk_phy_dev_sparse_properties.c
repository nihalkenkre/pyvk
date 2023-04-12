#include "vk_phy_dev_sparse_properties.h"

#include "log.h"

PyMemberDef vk_phy_dev_sparse_props_members[] = {
    {"residency_standard_2d_block_shape", T_BOOL, offsetof(vk_phy_dev_sparse_props, residency_standard_2d_block_shape), 1, "Residency Standard 2D Block Shape"},
    {"residency_standard_2d_multisample_block_shape", T_BOOL, offsetof(vk_phy_dev_sparse_props, residency_standard_2d_multisample_block_shape), 1, "Residency Standard 2D Multisample Block Shape"},
    {"residency_standard_3d_block_shape", T_BOOL, offsetof(vk_phy_dev_sparse_props, residency_standard_3d_block_shape), 1, "Residency Standard 3D Block Shape"},
    {"residency_aligned_mip_size", T_BOOL, offsetof(vk_phy_dev_sparse_props, residency_aligned_mip_size), 1, "Residency Aligned Mip Size"},
    {"residency_non_resident_strict", T_BOOL, offsetof(vk_phy_dev_sparse_props, residency_non_resident_strict), 1, "Residency Non Resident Strict"},
    {NULL},
};

PyTypeObject vk_phy_dev_sparse_props_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.physical_device_sparse_properties",
    .tp_basicsize = sizeof(vk_phy_dev_sparse_props),
    .tp_doc = PyDoc_STR("Vulkan Physical Device Sparse Properties Docs"),
    .tp_members = vk_phy_dev_sparse_props_members,
};

PyObject *add_vk_phy_dev_sparse_props_to_module(PyObject *mod)
{
    DEBUG_LOG("adding physical_device_sparse_props object\n");

    if (PyType_Ready(&vk_phy_dev_sparse_props_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready phy_dev_sparse_props_type type to module");

        goto shutdown;
    }

    Py_INCREF(&vk_phy_dev_sparse_props_type);

    if (PyModule_AddObject(mod, "physical_device_sparse_properties", (PyObject *)&vk_phy_dev_sparse_props_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add phy_dev_sparse_props_type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_phy_dev_sparse_props_type);

    return NULL;
}