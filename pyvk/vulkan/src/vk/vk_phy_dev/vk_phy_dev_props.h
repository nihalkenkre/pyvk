#ifndef VK_PHY_DEV_PROPS
#define VK_PHY_DEV_PROPS

#include <Python.h>
#include <structmember.h>

#include <vulkan/vulkan.h>

typedef struct vk_phy_dev_props
{
    PyObject_HEAD
    uint32_t api_version;
    uint32_t driver_version;
    uint32_t vendor_id;
    uint32_t device_id;
    uint32_t device_type;
    PyObject* device_name;
    PyObject* pipeline_cache_uuid;
    PyObject* limits;
    PyObject* sparse_properties;

    VkPhysicalDeviceProperties props;
} vk_phy_dev_props;

PyTypeObject vk_phy_dev_props_type;

PyObject* add_vk_phy_dev_props_to_module(PyObject* mod);

#endif // VK_PHY_DEV_PROPS  