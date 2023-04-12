#ifndef VK_PHY_DEV
#define VK_PHY_DEV

#include <Python.h>
#include <vulkan/vulkan.h>

#include "vk_phy_dev_mem_props.h"

typedef struct vk_phy_dev
{
    PyObject_HEAD
        VkPhysicalDevice phy_dev;
} vk_phy_dev;

PyTypeObject vk_phy_dev_type;

PyObject *add_vk_phy_dev_to_module(PyObject *mod);

#endif // VK_PHY_DEV