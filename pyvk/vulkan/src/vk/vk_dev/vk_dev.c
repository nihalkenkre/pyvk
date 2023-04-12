#include "vk_dev.h"
#include "vk_queue.h"

#include "vk_swapchain_ci.h"
#include "vk_swapchain.h"

#include "vk_cmd_pool_ci.h"
#include "vk_cmd_pool.h"

#include "log.h"

PyObject *vk_dev_get_queue(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_dev_get_queue\n");

    vk_dev *self = (vk_dev *)self_obj;

    uint32_t q_flx_idx = 0;
    uint32_t q_idx = 0;

    char *kwlist[] = {"queue_family_index", "queue_index", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|II", kwlist, &q_flx_idx, &q_idx);

    if (PyErr_Occurred())
    {
        return NULL;
    }

    VkQueue q;
    vkGetDeviceQueue(self->device, q_flx_idx, q_idx, &q);

    vk_queue *q_obj = PyObject_NEW(vk_queue, &vk_queue_type);

    return (PyObject *)q_obj;
}

PyObject *vk_dev_create_swapchain(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_create_swapchain\n");

    vk_dev *self = (vk_dev *)self_obj;

    PyObject *sc_ci = NULL;

    PyArg_Parse(args, "O", &sc_ci);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_swapchain_ci *ci_obj = (vk_swapchain_ci *)sc_ci;
    vk_swapchain *sc = PyObject_NEW(vk_swapchain, &vk_swapchain_type);

    VkResult result = vkCreateSwapchainKHR(self->device, &ci_obj->ci, NULL, &sc->swapchain);

    PyObject *return_obj = PyTuple_New(2);
    PyTuple_SetItem(return_obj, 0, (PyObject *)sc);
    PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

    return return_obj;
}

PyObject *vk_dev_destroy_swapchain(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_destroy_swapchain\n");

    vk_dev *self = (vk_dev *)self_obj;

    PyObject *swapchain = NULL;
    PyArg_Parse(args, "O", &swapchain);

    if (PyErr_Occurred())
    {
        return NULL;
    }

    if (((vk_swapchain *)swapchain)->swapchain != VK_NULL_HANDLE)
    {
        DEBUG_LOG("destroying swapchain\n");
        vkDestroySwapchainKHR(self->device, ((vk_swapchain *)swapchain)->swapchain, NULL);
    }

    Py_XDECREF(swapchain);

    return Py_None;
}

PyObject *vk_dev_create_cmd_pool(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_create_cmd_pool\n");

    vk_dev *self = (vk_dev *)self_obj;

    PyObject *cmd_pool_ci_obj = NULL;

    PyArg_Parse(args, "O", &cmd_pool_ci_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_cmd_pool_ci *ci_obj = (vk_cmd_pool_ci *)cmd_pool_ci_obj;
    vk_cmd_pool *cmd_pool = PyObject_NEW(vk_cmd_pool, &vk_cmd_pool_type);

    VkResult result = vkCreateCommandPool(self->device, &ci_obj->ci, NULL, &cmd_pool->command_pool);

    PyObject *return_obj = PyTuple_New(2);
    PyTuple_SetItem(return_obj, 0, (PyObject *)cmd_pool);
    PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

    return return_obj;
}

PyObject *vk_dev_destroy_cmd_pool(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_destroy_cmd_pool\n");

    vk_dev *self = (vk_dev *)self_obj;

    PyObject *cmd_pool_obj = NULL;
    PyArg_Parse(args, "O", &cmd_pool_obj);

    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_cmd_pool* cmd_pool = (vk_cmd_pool*) cmd_pool_obj;

    if (cmd_pool->command_pool != VK_NULL_HANDLE)
    {
        DEBUG_LOG("destroying cmd_pool\n");
        vkDestroyCommandPool(self->device, cmd_pool->command_pool, NULL);
    }

    Py_XDECREF(cmd_pool);

    return Py_None;
}

PyMethodDef vk_dev_methods[] = {
    {"get_queue", (PyCFunction)vk_dev_get_queue, METH_VARARGS | METH_KEYWORDS, NULL},
    {"create_swapchain", (PyCFunction)vk_dev_create_swapchain, METH_O, NULL},
    {"destroy_swapchain", (PyCFunction)vk_dev_destroy_swapchain, METH_O, NULL},
    {"create_command_pool", (PyCFunction)vk_dev_create_cmd_pool, METH_O, NULL},
    {"destroy_command_pool", (PyCFunction)vk_dev_destroy_cmd_pool, METH_O, NULL},
    {NULL},
};

PyTypeObject vk_dev_type = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "vulkan.device",
    .tp_basicsize = sizeof(vk_dev),
    .tp_doc = PyDoc_STR("Vulkan Device Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_methods = vk_dev_methods,
};

PyObject *add_vk_dev_to_module(PyObject *mod)
{
    DEBUG_LOG("adding device object\n");

    if (PyType_Ready(&vk_dev_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready dev type to module");
        goto shutdown;
    }

    Py_INCREF(&vk_dev_type);

    if (PyModule_AddObject(mod, "device", (PyObject *)&vk_dev_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add dev type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_dev_type);

    return NULL;
}
