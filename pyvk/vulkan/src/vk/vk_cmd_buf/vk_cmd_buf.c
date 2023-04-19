#include "vk_cmd_buf.h"
#include "vk_cmd_buf_bi.h"

#include "vk_img.h"
#include "vk_img_cpy.h"

#include "log.h"

void get_regions_from_list(PyObject *obj, VkImageCopy **regions, uint32_t *regions_count)
{
    DEBUG_LOG("get_regions_from_list\n");

    *regions_count = (uint32_t)PyList_Size(obj);

    for (uint32_t idx = 0; idx < *regions_count; ++idx)
    {
        *(*regions + idx) = ((vk_img_cpy *)PyList_GetItem(obj, idx))->img_cpy;
    }
}

PyObject *vk_cmd_buf_begin(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_cmd_buf_begin\n");

    PyObject *cmd_buf_bi_obj = NULL;

    PyArg_Parse(args, "O", &cmd_buf_bi_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_cmd_buf *self = (vk_cmd_buf *)self_obj;

    VkResult result = vkBeginCommandBuffer(self->command_buffer, &((vk_cmd_buf_bi *)cmd_buf_bi_obj)->bi);

    return PyLong_FromLong(result);
}

PyObject *vk_cmd_buf_cpy_img(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_cmd_buf_cpy_img\n");

    PyObject *src_img_obj = NULL;
    long src_img_layout = 0;
    PyObject *dst_img_obj = NULL;
    long dst_img_layout = 0;
    PyObject *regions_obj = NULL;

    char *kwlist[] = {"src_image", "src_image_layout", "dst_image", "dst_image_layout", "regions", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OkOkO", kwlist, &src_img_layout, &src_img_layout, &dst_img_obj, &dst_img_layout, &regions_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_cmd_buf *self = (vk_cmd_buf *)self_obj;

    uint32_t regions_count = 0;
    VkImageCopy *regions = NULL;

    get_regions_from_list(regions_obj, &regions, &regions_count);

    vkCmdCopyImage(self->command_buffer, ((vk_img *)src_img_obj)->image, src_img_layout,

                   ((vk_img *)dst_img_obj)->image, dst_img_layout, regions_count, regions);

    Py_RETURN_NONE;
}

PyObject *vk_cmd_buf_end(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_cmd_buf_end\n");

    VkResult result = vkEndCommandBuffer(((vk_cmd_buf *)self_obj)->command_buffer);

    return PyLong_FromLong(result);
}

PyMethodDef vk_cmd_buf_methods[] = {
    {"begin", (PyCFunction)vk_cmd_buf_begin, METH_O, NULL},
    {"copy_image", (PyCFunction)vk_cmd_buf_cpy_img, METH_VARARGS | METH_KEYWORDS, NULL},
    {"end", (PyCFunction)vk_cmd_buf_end, METH_NOARGS, NULL},
    {NULL},
};

PyTypeObject vk_cmd_buf_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.command_buffer",
    .tp_basicsize = sizeof(vk_cmd_buf),
    .tp_doc = PyDoc_STR("Vulkan Command Buffer Docs"),
    .tp_methods = vk_cmd_buf_methods,
};

PyObject *add_vk_cmd_buf_to_module(PyObject *mod)
{
    DEBUG_LOG("adding cmd_buf object\n");

    if (PyType_Ready(&vk_cmd_buf_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready cmd_buf type");

        goto shutdown;
    }

    Py_INCREF(&vk_cmd_buf_type);

    if (PyModule_AddObject(mod, "command_buffer", (PyObject *)&vk_cmd_buf_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add cmd_buf type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_cmd_buf_type);

    return NULL;
}