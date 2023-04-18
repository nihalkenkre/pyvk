#include "vk_dev.h"
#include "vk_q.h"

#include "vk_swapchain_ci.h"
#include "vk_swapchain.h"

#include "vk_cmd_pool_ci.h"
#include "vk_cmd_pool.h"

#include "vk_cmd_buf_ai.h"
#include "vk_cmd_buf.h"

#include "vk_sem_ci.h"
#include "vk_sem.h"

#include "vk_fence_ci.h"
#include "vk_fence.h"

#include "vk_img_ci.h"
#include "vk_img.h"

#include "vk_mem_ai.h"

#include "vk_dev_mem.h"

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

    vk_q *q_obj = PyObject_NEW(vk_q, &vk_q_type);

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

    Py_RETURN_NONE;
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

    vk_cmd_pool *cmd_pool = (vk_cmd_pool *)cmd_pool_obj;

    if (cmd_pool->command_pool != VK_NULL_HANDLE)
    {
        DEBUG_LOG("destroying cmd_pool\n");
        vkDestroyCommandPool(self->device, cmd_pool->command_pool, NULL);
    }

    Py_XDECREF(cmd_pool);

    Py_RETURN_NONE;
}

PyObject *vk_dev_alloc_cmd_bufs(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_alloc_cmd_bufs\n");

    vk_dev *self = (vk_dev *)self_obj;

    PyObject *ai_obj = NULL;
    PyArg_Parse(args, "O", &ai_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_cmd_buf_ai *ai = (vk_cmd_buf_ai *)ai_obj;

    VkCommandBuffer *cmd_bufs = (VkCommandBuffer *)malloc(sizeof(VkCommandBuffer) * ai->ai.commandBufferCount);
    VkResult result = vkAllocateCommandBuffers(self->device, &ai->ai, cmd_bufs);

    if (result != VK_SUCCESS)
    {
        free(cmd_bufs);

        PyObject *return_obj = PyTuple_New(2);
        PyTuple_SetItem(return_obj, 0, Py_None);
        PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

        return return_obj;
    }

    PyObject *cmd_bufs_obj = PyTuple_New(ai->ai.commandBufferCount);

    for (uint32_t cb_idx = 0; cb_idx < ai->ai.commandBufferCount; ++cb_idx)
    {
        vk_cmd_buf *cmd_buf_obj = PyObject_NEW(vk_cmd_buf, &vk_cmd_buf_type);

        cmd_buf_obj->command_buffer = cmd_bufs[cb_idx];
        PyTuple_SetItem(cmd_bufs_obj, cb_idx, (PyObject *)cmd_buf_obj);
    }

    PyObject *return_obj = PyTuple_New(2);
    PyTuple_SetItem(return_obj, 0, cmd_bufs_obj);
    PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

    free(cmd_bufs);

    return return_obj;
}

PyObject *vk_dev_free_cmd_bufs(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_dev_free_cmd_bufs\n");

    PyObject *cmd_pool_obj = NULL;
    PyObject *cmd_bufs_obj = NULL;

    PyObject *tmp = NULL;

    char *kwlist[] = {"command_pool", "command_buffers", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OO", kwlist, &cmd_pool_obj, &cmd_bufs_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_dev *self = (vk_dev *)self_obj;

    uint32_t cmd_buf_count = (uint32_t)PyTuple_Size(cmd_bufs_obj);
    VkCommandBuffer *cmd_bufs = (VkCommandBuffer *)malloc(sizeof(VkCommandBuffer) * cmd_buf_count);

    for (uint32_t cb_idx = 0; cb_idx < cmd_buf_count; ++cb_idx)
    {
        *(cmd_bufs + cb_idx) = ((vk_cmd_buf *)PyTuple_GetItem(cmd_bufs_obj, cb_idx))->command_buffer;
    }

    vkFreeCommandBuffers(self->device, ((vk_cmd_pool *)cmd_pool_obj)->command_pool, cmd_buf_count, cmd_bufs);

    free(cmd_bufs);

    Py_XDECREF(cmd_bufs_obj);

    Py_RETURN_NONE;
}

PyObject *vk_dev_create_sem(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_create_sem\n");

    vk_dev *self = (vk_dev *)self_obj;

    PyObject *ci_obj = NULL;

    PyArg_Parse(args, "O", &ci_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_sem_ci *ci = (vk_sem_ci *)ci_obj;

    vk_sem *sem = PyObject_NEW(vk_sem, &vk_sem_type);

    VkResult result = vkCreateSemaphore(self->device, &ci->ci, NULL, &sem->semaphore);

    PyObject *return_obj = PyTuple_New(2);
    PyTuple_SetItem(return_obj, 0, (PyObject *)sem);
    PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

    return return_obj;
}

PyObject *vk_dev_destroy_sem(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_destroy_sem\n");

    vk_dev *self = (vk_dev *)self_obj;

    PyObject *sem_obj = NULL;

    PyArg_Parse(args, "O", &sem_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_sem *sem = (vk_sem *)sem_obj;

    if (sem->semaphore != VK_NULL_HANDLE)
    {
        DEBUG_LOG("destroying semaphore\n");
        vkDestroySemaphore(self->device, sem->semaphore, NULL);
    }

    Py_XDECREF(sem_obj);

    Py_RETURN_NONE;
}

PyObject *vk_dev_create_fence(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_create_fence\n");

    vk_dev *self = (vk_dev *)self_obj;

    PyObject *ci_obj = NULL;

    PyArg_Parse(args, "O", &ci_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_fence_ci *ci = (vk_fence_ci *)ci_obj;

    vk_fence *fence = PyObject_NEW(vk_fence, &vk_fence_type);

    VkResult result = vkCreateFence(self->device, &ci->ci, NULL, &fence->fence);

    PyObject *return_obj = PyTuple_New(2);
    PyTuple_SetItem(return_obj, 0, (PyObject *)fence);
    PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

    return return_obj;
}

PyObject *vk_dev_destroy_fence(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_destroy_fence\n");

    vk_dev *self = (vk_dev *)self_obj;

    PyObject *fence_obj = NULL;

    PyArg_Parse(args, "O", &fence_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_fence *fence = (vk_fence *)fence_obj;

    if (fence->fence != VK_NULL_HANDLE)
    {
        DEBUG_LOG("destroying fence\n");
        vkDestroyFence(self->device, fence->fence, NULL);
    }

    Py_XDECREF(fence_obj);

    Py_RETURN_NONE;
}

PyObject *vk_dev_create_image(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_create_image\n");

    vk_dev *self = (vk_dev *)self_obj;

    PyObject *ci_obj = NULL;

    PyArg_Parse(args, "O", &ci_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_img_ci *ci = (vk_img_ci *)ci_obj;

    vk_img *image = PyObject_NEW(vk_img, &vk_img_type);

    VkResult result = vkCreateImage(self->device, &ci->ci, NULL, &image->image);

    PyObject *return_obj = PyTuple_New(2);
    PyTuple_SetItem(return_obj, 0, (PyObject *)image);
    PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

    return return_obj;
}

PyObject *vk_dev_destroy_image(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_destroy_image\n");

    vk_dev *self = (vk_dev *)self_obj;

    PyObject *image_obj = NULL;

    PyArg_Parse(args, "O", &image_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_img *image = (vk_img *)image_obj;

    if (image->image != VK_NULL_HANDLE)
    {
        DEBUG_LOG("destroying image\n");
        vkDestroyImage(self->device, image->image, NULL);
    }

    Py_XDECREF(image_obj);

    Py_RETURN_NONE;
}

PyObject *vk_dev_allocate_memory(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_allocate_memory\n");

    vk_dev *self = (vk_dev *)self_obj;

    PyObject *ai_obj = NULL;

    PyArg_Parse(args, "O", &ai_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_mem_ai *ai = (vk_mem_ai *)ai_obj;

    vk_dev_mem *dev_mem = PyObject_NEW(vk_dev_mem, &vk_dev_mem_type);

    VkResult result = vkAllocateMemory(self->device, &ai->ai, NULL, &dev_mem->device_memory);

    PyObject *return_obj = PyTuple_New(2);
    PyTuple_SetItem(return_obj, 0, (PyObject *)dev_mem);
    PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

    return return_obj;
}

PyObject *vk_dev_free_memory(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_free_memory\n");

    vk_dev *dev = (vk_dev *)self_obj;
    PyObject *mem_obj = NULL;

    PyArg_Parse(args, "O", &mem_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_dev_mem *mem = (vk_dev_mem *)mem_obj;

    if (mem->device_memory != VK_NULL_HANDLE)
    {
        DEBUG_LOG("freeing device memory\n");
        vkFreeMemory(dev->device, mem->device_memory, NULL);
    }

    Py_XDECREF(mem_obj);

    Py_RETURN_NONE;
}

PyObject *vk_dev_bind_img_memory(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_dev_bind_img_memory\n");

    vk_dev *self = (vk_dev *)self_obj;

    PyObject *img_obj = NULL;
    PyObject *mem_obj = NULL;

    long offset = 0;

    char *kwlist[] = {"image", "device_memory", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OOk", kwlist, &img_obj, &mem_obj, &offset);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_img *img = (vk_img *)img_obj;
    vk_dev_mem *mem = (vk_dev_mem *)mem_obj;

    VkResult result = vkBindImageMemory(self->device, img->image, mem->device_memory, (VkDeviceSize)offset);

    return PyLong_FromLong(result);
}

PyObject *vk_dev_get_swapchain_images(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_get_swapchain_images\n");

    PyObject *sc_obj = NULL;

    PyArg_Parse(args, "O", &sc_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_dev *self = (vk_dev *)self_obj;
    vk_swapchain *sc = (vk_swapchain *)sc_obj;

    uint32_t image_count = 0;
    VkResult result = vkGetSwapchainImagesKHR(self->device, sc->swapchain, &image_count, NULL);

    if (result != VK_SUCCESS)
    {
        PyObject *return_obj = PyTuple_New(2);

        PyTuple_SetItem(return_obj, 0, Py_None);
        PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

        return return_obj;
    }

    VkImage *images = (VkImage *)PyMem_MALLOC(sizeof(VkImage *) * image_count);
    result = vkGetSwapchainImagesKHR(self->device, sc->swapchain, &image_count, images);

    if (result != VK_SUCCESS)
    {
        PyMem_FREE(images);

        PyObject *return_obj = PyTuple_New(2);

        PyTuple_SetItem(return_obj, 0, Py_None);
        PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

        return return_obj;
    }

    PyObject *imgs_obj = PyTuple_New(image_count);

    for (uint32_t img_idx = 0; img_idx < image_count; ++img_idx)
    {
        vk_img *sc_img = PyObject_NEW(vk_img, &vk_img_type);
        sc_img->image = *(images + img_idx);

        PyTuple_SetItem(imgs_obj, img_idx, (PyObject *)sc_img);
    }

    PyMem_FREE(images);

    PyObject *return_obj = PyTuple_New(2);

    PyTuple_SetItem(return_obj, 0, imgs_obj);
    PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

    return return_obj;
}

PyMethodDef vk_dev_methods[] = {
    {"get_queue", (PyCFunction)vk_dev_get_queue, METH_VARARGS | METH_KEYWORDS, NULL},
    {"create_swapchain", (PyCFunction)vk_dev_create_swapchain, METH_O, NULL},
    {"destroy_swapchain", (PyCFunction)vk_dev_destroy_swapchain, METH_O, NULL},
    {"create_command_pool", (PyCFunction)vk_dev_create_cmd_pool, METH_O, NULL},
    {"destroy_command_pool", (PyCFunction)vk_dev_destroy_cmd_pool, METH_O, NULL},
    {"allocate_command_buffers", (PyCFunction)vk_dev_alloc_cmd_bufs, METH_O, NULL},
    {"free_command_buffers", (PyCFunction)vk_dev_free_cmd_bufs, METH_VARARGS | METH_KEYWORDS, NULL},
    {"create_semaphore", (PyCFunction)vk_dev_create_sem, METH_O, NULL},
    {"destroy_semaphore", (PyCFunction)vk_dev_destroy_sem, METH_O, NULL},
    {"create_fence", (PyCFunction)vk_dev_create_fence, METH_O, NULL},
    {"destroy_fence", (PyCFunction)vk_dev_destroy_fence, METH_O, NULL},
    {"create_image", (PyCFunction)vk_dev_create_image, METH_O, NULL},
    {"destroy_image", (PyCFunction)vk_dev_destroy_image, METH_O, NULL},
    {"allocate_memory", (PyCFunction)vk_dev_allocate_memory, METH_O, NULL},
    {"free_memory", (PyCFunction)vk_dev_free_memory, METH_O, NULL},
    {"bind_image_memory", (PyCFunction)vk_dev_bind_img_memory, METH_VARARGS | METH_KEYWORDS, NULL},
    {"get_swapchain_images", (PyCFunction)vk_dev_get_swapchain_images, METH_O, NULL},
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
