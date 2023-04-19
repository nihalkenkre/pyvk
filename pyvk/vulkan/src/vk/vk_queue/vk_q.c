#include "vk_q.h"
#include "vk_q_si.h"
#include "vk_fence.h"

#include "log.h"

void get_si_from_obj(PyObject *obj, VkSubmitInfo **infos, uint32_t *infos_count)
{
    DEBUG_LOG("get_si_from_obj\n");

    *infos_count = (uint32_t)PyList_Size(obj);
    *infos = (VkSubmitInfo *)malloc(sizeof(VkSubmitInfo) * *infos_count);

    for (uint32_t idx = 0; idx < *infos_count; ++idx)
    {
        *(*infos + idx) = ((vk_q_si *)PyList_GetItem(obj, idx))->si;
    }
}

PyObject *vk_q_submit(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_q_submit\n");

    PyObject *submit_infos_obj = NULL;
    PyObject *fence_obj = NULL;

    char *kwlist[] = {"submit_infos", "fence", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OO", kwlist, &submit_infos_obj, &fence_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }
    VkSubmitInfo *submit_infos = NULL;
    uint32_t submit_info_count = 0;

    get_si_from_obj((vk_q_si *)submit_infos_obj, &submit_infos, &submit_info_count);

    VkResult result = vkQueueSubmit(((vk_q *)self_obj)->queue, submit_info_count, submit_infos, ((vk_fence *)fence_obj)->fence);

    if(submit_infos)
    {
        free(submit_infos);
    }

    return PyLong_FromLong(result);
}

PyMethodDef vk_q_methods[] = {
    {"submit", (PyCFunction)vk_q_submit, METH_VARARGS | METH_KEYWORDS, NULL},
    {NULL},
};

PyTypeObject vk_q_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.q",
    .tp_basicsize = sizeof(vk_q),
    .tp_doc = PyDoc_STR("Vulkan Queue Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_methods = vk_q_methods,
};

PyObject *add_vk_q_to_module(PyObject *mod)
{
    DEBUG_LOG("adding queue object\n");

    if (PyType_Ready(&vk_q_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready q type");

        goto shutdown;
    }

    Py_INCREF(&vk_q_type);

    if (PyModule_AddObject(mod, "queue", (PyObject *)&vk_q_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add q type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_q_type);

    return NULL;
}