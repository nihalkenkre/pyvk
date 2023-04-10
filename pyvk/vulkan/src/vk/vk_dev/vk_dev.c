#include "vk_dev.h"
#include "vk_queue.h"

#include "vk_swapchain_ci.h"
#include "vk_swapchain.h"

#include "log.h"

void vk_dev_dealloc(PyObject *self)
{
    DEBUG_LOG("vk_dev_dealloc\n");
    Py_TYPE(self)->tp_free(self);
}

PyObject *vk_dev_get_queue(vk_dev *self, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_dev_get_queue\n");

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

    PyObject *q_obj = PyObject_NEW(vk_queue, &vk_queue_type);

    return q_obj;
}

PyObject *vk_dev_create_swapchain(vk_dev *self, PyObject *args)
{
    DEBUG_LOG("vk_dev_create_swapchain\n");

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

PyMethodDef vk_dev_methods[] = {
    {"get_queue", (PyCFunction)vk_dev_get_queue, METH_VARARGS | METH_KEYWORDS, NULL},
    {"create_swapchain", (PyCFunction)vk_dev_create_swapchain, METH_O, NULL},
    {NULL},
};

PyTypeObject vk_dev_type = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "vulkan.device",
    .tp_basicsize = sizeof(vk_dev),
    .tp_doc = PyDoc_STR("Vulkan Device Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_dealloc = vk_dev_dealloc,
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
