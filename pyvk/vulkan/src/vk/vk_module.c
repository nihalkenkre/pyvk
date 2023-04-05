#include <Python.h>
#include <structmember.h>

#include <Windows.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>

#include "log.h"

#include "vk_instance/vk_app_info.h"
#include "vk_instance/vk_instance_ci.h"
#include "vk_instance/vk_instance.h"
#include "vk_mem/vk_mem_type.h"
#include "vk_mem/vk_mem_heap.h"
#include "vk_phy_dev/vk_phy_dev_mem_props.h"
#include "vk_phy_dev/vk_phy_dev_limits.h"
#include "vk_phy_dev/vk_phy_dev_features.h"
#include "vk_phy_dev/vk_phy_dev_sparse_properties.h"
#include "vk_phy_dev/vk_phy_dev_props.h"
#include "vk_phy_dev/vk_phy_dev.h"
#include "vk_surface/vk_surface.h"
#include "vk_surface/vk_surface_ci.h"
#include "vk_dev/vk_dev_q_ci.h"
#include "vk_dev/vk_dev_ci.h"
#include "vk_dev/vk_dev.h"
#include "vk_swapchain/vk_swapchain_ci.h"
#include "vk_swapchain/vk_swapchain.h"

PyObject *vk_create_instance(PyObject *self, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_create_instance\n");

    PyObject *instance_ci_obj = NULL;

    PyArg_Parse(args, "O", &instance_ci_obj);
    if (PyErr_Occurred())
    {
        goto shutdown;
    }

    vk_instance_ci *ci_obj = (vk_instance_ci *)instance_ci_obj;

    vk_instance *inst = PyObject_New(vk_instance, &vk_instance_type);
    VkResult result = vkCreateInstance(&ci_obj->ci, NULL, &inst->instance);

    PyObject *return_obj = PyTuple_New(2);
    PyTuple_SetItem(return_obj, 0, (PyObject *)inst);
    PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

    return return_obj;

shutdown:

    return NULL;
}

PyObject *vk_destroy_instance(PyObject *self, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_destroy_instance\n");

    PyObject *inst;
    PyArg_Parse(args, "O", &inst);

    if (PyErr_Occurred())
    {
        return NULL;
    }

    if (PyObject_TypeCheck(inst, &vk_instance_type) == 0)
    {
        PyErr_SetString(PyExc_TypeError, "Please pass object of type vulkan.instance");
        return NULL;
    }

    if (((vk_instance *)inst)->instance != VK_NULL_HANDLE)
    {
        DEBUG_LOG("destroying instance\n");
        vkDestroyInstance(((vk_instance *)inst)->instance, NULL);
    }

    Py_XDECREF(inst);

    return Py_None;
}

PyObject *add_structure_types_enums_to_module(PyObject *mod)
{
    if (PyModule_AddIntConstant(mod, "STRUCTURE_TYPE_APPLICATION_INFO", VK_STRUCTURE_TYPE_APPLICATION_INFO) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add STRUCTURE_TYPE_APPLICATION_INFO to module");
        return NULL;
    }

    if (PyModule_AddIntConstant(mod, "STRUCTURE_TYPE_INSTANCE_CREATE_INFO", VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add STRUCTURE_TYPE_INSTANCE_CREATE_INFO to module");
        return NULL;
    }

    if (PyModule_AddIntConstant(mod, "STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR", VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR to module");
        return NULL;
    }

    if (PyModule_AddIntConstant(mod, "STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO", VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO to module");
        return NULL;
    }

    if (PyModule_AddIntConstant(mod, "STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO", VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO to module");
        return NULL;
    }

    return mod;
}

PyObject *add_surface_enums_to_module(PyObject *mod)
{
    if (PyModule_AddStringConstant(mod, "KHR_SURFACE_EXTENSION_NAME", VK_KHR_SURFACE_EXTENSION_NAME) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add KHR_SURFACE_EXTENSION_NAME to module");
        return NULL;
    }

    if (PyModule_AddStringConstant(mod, "KHR_WIN32_SURFACE_EXTENSION_NAME", VK_KHR_WIN32_SURFACE_EXTENSION_NAME) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add KHR_WIN32_SURFACE_EXTENSION_NAME to module");
        return NULL;
    }

    return mod;
}

PyObject *add_creation_flags_to_module(PyObject *mod)
{
    if (PyModule_AddIntConstant(mod, "SWAPCHAIN_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR", 0x00000001) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add SWAPCHAIN_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR to module");
        return NULL;
    }

    if (PyModule_AddIntConstant(mod, "SWAPCHAIN_CREATE_PROTECTED_BIT_KHR", 0x00000002) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add SWAPCHAIN_CREATE_PROTECTED_BIT_KHR to module");
        return NULL;
    }

    if (PyModule_AddIntConstant(mod, "SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR", 0x00000004) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add SWAPCHAIN_CREATE_MUTABLE_FORMAT_BIT_KHR to module");
        return NULL;
    }

    if (PyModule_AddIntConstant(mod, "SWAPCHAIN_CREATE_DEFERRED_MEMORY_ALLOCATION_BIT_EXT", 0x00000008) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add SWAPCHAIN_CREATE_DEFERRED_MEMORY_ALLOCATION_BIT_EXT to module");
        return NULL;
    }

    if (PyModule_AddStringConstant(mod, "KHR_SWAPCHAIN_EXTENSION_NAME", VK_KHR_SWAPCHAIN_EXTENSION_NAME) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add KHR_SWAPCHAIN_EXTENSION_NAME to module");
        return NULL;
    }
    return mod;
}

PyObject *add_phy_dev_enums_to_module(PyObject *mod)
{
    if (PyModule_AddIntConstant(mod, "PHYSICAL_DEVICE_TYPE_OTHER", VK_PHYSICAL_DEVICE_TYPE_OTHER) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add PHYSICAL_DEVICE_TYPE_OTHER to module");
        return NULL;
    }

    if (PyModule_AddIntConstant(mod, "PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU", VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU to module");
        return NULL;
    }

    if (PyModule_AddIntConstant(mod, "PHYSICAL_DEVICE_TYPE_DISCRETE_GPU", VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add PHYSICAL_DEVICE_TYPE_DISCRETE_GPU to module");
        return NULL;
    }

    if (PyModule_AddIntConstant(mod, "PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU", VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU to module");
        return NULL;
    }

    if (PyModule_AddIntConstant(mod, "PHYSICAL_DEVICE_TYPE_CPU", VK_PHYSICAL_DEVICE_TYPE_CPU) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add PHYSICAL_DEVICE_TYPE_CPU to module");
        return NULL;
    }
}

PyObject *add_error_enums_to_module(PyObject *mod)
{
    if (PyModule_AddIntConstant(mod, "SUCCESS", VK_SUCCESS) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add SUCCESS to module");
        return NULL;
    }

    if (PyModule_AddIntConstant(mod, "ERROR_OUT_OF_HOST_MEMORY", VK_ERROR_OUT_OF_HOST_MEMORY) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add ERROR_OUT_OF_HOST_MEMORY to module");
        return NULL;
    }

    if (PyModule_AddIntConstant(mod, "ERROR_OUT_OF_DEVICE_MEMORY", VK_ERROR_OUT_OF_DEVICE_MEMORY) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add ERROR_OUT_OF_DEVICE_MEMORY to module");
        return NULL;
    }

    if (PyModule_AddIntConstant(mod, "ERROR_INITIALIZATION_FAILED", VK_ERROR_INITIALIZATION_FAILED) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add ERROR_INITIALIZATION_FAILED to module");
        return NULL;
    }

    if (PyModule_AddIntConstant(mod, "ERROR_LAYER_NOT_PRESENT", VK_ERROR_LAYER_NOT_PRESENT) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add ERROR_LAYER_NOT_PRESENT to module");
        return NULL;
    }

    if (PyModule_AddIntConstant(mod, "ERROR_EXTENSION_NOT_PRESENT", VK_ERROR_EXTENSION_NOT_PRESENT) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add ERROR_EXTENSION_NOT_PRESENT to module");
        return NULL;
    }

    if (PyModule_AddIntConstant(mod, "ERROR_INCOMPATIBLE_DRIVER", VK_ERROR_INCOMPATIBLE_DRIVER) == -1)
    {
        PyErr_SetString(PyExc_SystemError, "Could not add ERROR_INCOMPATIBLE_DRIVER to module");
        return NULL;
    }
}

PyObject *add_enums_to_module(PyObject *mod)
{
    mod = add_structure_types_enums_to_module(mod);
    if (mod == NULL)
    {
        return NULL;
    }

    mod = add_surface_enums_to_module(mod);
    if (mod == NULL)
    {
        return NULL;
    }

    mod = add_creation_flags_to_module(mod);
    if (mod == NULL)
    {
        return NULL;
    }

    mod = add_error_enums_to_module(mod);
    if (mod == NULL)
    {
        return NULL;
    }

    mod = add_phy_dev_enums_to_module(mod);
    if (mod == NULL)
    {
        return NULL;
    }

    return mod;
}

static PyMethodDef vk_module_methods[] = {
    {"create_instance", (PyCFunction)vk_create_instance, METH_O, NULL},
    {"destroy_instance", (PyCFunction)vk_destroy_instance, METH_O, NULL},
    {NULL},
};

static struct PyModuleDef vk_module = {
    PyModuleDef_HEAD_INIT,
    .m_name = "vulkan",
    .m_doc = "Vulkan bindings from CPython",
    .m_size = -1,
    .m_methods = vk_module_methods,
};

PyMODINIT_FUNC PyInit_vulkan(void)
{
    PyObject *mod = PyModule_Create(&vk_module);

    DEBUG_LOG("creating module\n");

    if (mod == NULL)
    {
        PyErr_SetString(PyExc_TypeError, "Could not create vulkan module");
        return NULL;
    }

    mod = add_vk_app_info_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_instance_ci_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_instance_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_mem_type_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_mem_heap_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_phy_dev_features_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_phy_dev_limits_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_phy_dev_sparse_props_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_phy_dev_props_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_phy_dev_mem_props_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_phy_dev_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_surface_ci_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_surface_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_dev_q_ci_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_dev_ci_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_dev_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_swapchain_ci_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_swapchain_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    /*mod = add_enums_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }*/

    return mod;

shutdown:
    Py_XDECREF(mod);

    return NULL;
}