#ifndef VK_PHY_DEV_MEM_PROPS
#define VK_PHY_DEV_MEM_PROPS

#include <Python.h>
#include <structmember.h>

#include <vulkan/vulkan.h>

typedef struct vk_phy_dev_mem_props
{
    PyObject_HEAD
        PyObject *types;
    PyObject *heaps;

    VkPhysicalDeviceMemoryProperties props;
} vk_phy_dev_mem_props;

PyMemberDef vk_phy_dev_mem_props_members[];
PyTypeObject vk_phy_dev_mem_props_type;

PyObject* add_vk_phy_dev_mem_props_to_module(PyObject* mod);

#endif // VK_PHY_DEV_MEM_PROPS