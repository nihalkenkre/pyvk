#ifndef VK_PHY_DEV_SPARSE_PROPERTIES
#define VK_PHY_DEV_SPARSE_PROPERTIES

#include <Python.h>
#include <structmember.h>

#include <stdbool.h>

#include <vulkan/vulkan.h>

typedef struct vk_phy_dev_sparse_props
{
    PyObject_HEAD 
    bool residency_standard_2d_block_shape;
    bool residency_standard_2d_multisample_block_shape;
    bool residency_standard_3d_block_shape;
    bool residency_aligned_mip_size;
    bool residency_non_resident_strict;

    VkPhysicalDeviceSparseProperties props;
} vk_phy_dev_sparse_props;

PyMemberDef vk_phy_dev_sparse_props_members[];
PyTypeObject vk_phy_dev_sparse_props_type;

PyObject* add_vk_phy_dev_sparse_props_to_module(PyObject* mod);

#endif // VK_PHY_DEV_SPARSE_PROPERTIES