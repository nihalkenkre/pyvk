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
#include "vk_surface/vk_surface_caps_khr.h"
#include "vk_surface/vk_surface_fmt_khr.h"
#include "vk_dev/vk_dev_q_ci.h"
#include "vk_dev/vk_dev_ci.h"
#include "vk_dev/vk_dev.h"
#include "vk_queue/vk_q_fly_props.h"
#include "vk_queue/vk_queue.h"
#include "vk_swapchain/vk_swapchain_ci.h"
#include "vk_swapchain/vk_swapchain.h"
#include "vk_cmd_pool/vk_cmd_pool_ci.h"
#include "vk_cmd_pool/vk_cmd_pool.h"
#include "vk_cmd_buf/vk_cmd_buf_ai.h"
#include "vk_cmd_buf/vk_cmd_buf.h"
#include "vk_sem/vk_sem_ci.h"
#include "vk_sem/vk_sem.h"

PyObject *vk_create_instance(PyObject *self, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_create_instance\n");

    PyObject *instance_ci_obj = NULL;

    PyArg_Parse(args, "O", &instance_ci_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_instance_ci *ci_obj = (vk_instance_ci *)instance_ci_obj;

    vk_instance *inst = PyObject_New(vk_instance, &vk_instance_type);
    VkResult result = vkCreateInstance(&ci_obj->ci, NULL, &inst->instance);

    PyObject *return_obj = PyTuple_New(2);
    PyTuple_SetItem(return_obj, 0, (PyObject *)inst);
    PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

    return return_obj;
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

    if (((vk_instance *)inst)->instance != VK_NULL_HANDLE)
    {
        DEBUG_LOG("destroying instance\n");
        vkDestroyInstance(((vk_instance *)inst)->instance, NULL);
    }

    Py_XDECREF(inst);

    return Py_None;
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

    mod = add_vk_surface_caps_khr_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_surface_fmt_khr_to_module(mod);

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

    mod = add_vk_queue_to_module(mod);

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

    mod = add_vk_q_fly_props_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_cmd_pool_ci_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_cmd_pool_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_cmd_buf_ai_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_cmd_buf_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_sem_ci_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    mod = add_vk_sem_to_module(mod);

    if (mod == NULL)
    {
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(mod);

    return NULL;
}