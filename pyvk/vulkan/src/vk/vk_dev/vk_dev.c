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

#include "vk_img_view_ci.h"
#include "vk_img_view.h"

#include "vk_mem_ai.h"
#include "vk_dev_mem.h"
#include "vk_mem_req.h"

#include "log.h"

#include <object.h>

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
    q_obj->queue = q;

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
        if (cmd_bufs != NULL)
        {
            free(cmd_bufs);
        }

        PyObject *return_obj = PyTuple_New(2);
        PyTuple_SetItem(return_obj, 0, Py_None);
        PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

        return return_obj;
    }

    PyObject *cmd_bufs_obj = PyList_New(ai->ai.commandBufferCount);

    for (uint32_t cb_idx = 0; cb_idx < ai->ai.commandBufferCount; ++cb_idx)
    {
        vk_cmd_buf *cmd_buf_obj = PyObject_NEW(vk_cmd_buf, &vk_cmd_buf_type);

        cmd_buf_obj->command_buffer = cmd_bufs[cb_idx];
        PyList_SetItem(cmd_bufs_obj, cb_idx, (PyObject *)cmd_buf_obj);
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

    uint32_t cmd_buf_count = (uint32_t)PyList_Size(cmd_bufs_obj);
    VkCommandBuffer *cmd_bufs = (VkCommandBuffer *)malloc(sizeof(VkCommandBuffer) * cmd_buf_count);

    for (uint32_t cb_idx = 0; cb_idx < cmd_buf_count; ++cb_idx)
    {
        cmd_bufs[cb_idx] = ((vk_cmd_buf *)PyList_GetItem(cmd_bufs_obj, cb_idx))->command_buffer;
    }

    vkFreeCommandBuffers(self->device, ((vk_cmd_pool *)cmd_pool_obj)->command_pool, cmd_buf_count, cmd_bufs);

    if (cmd_bufs != NULL)
    {
        free(cmd_bufs);
    }

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
void get_fences_from_list(PyObject *obj, VkFence **fences, uint32_t *fences_count)
{
    DEBUG_LOG("get_fence_from_list\n");

    *fences_count = (uint32_t)PyList_Size(obj);
    *fences = (VkFence *)malloc(sizeof(VkFence) * *fences_count);

    for (uint32_t idx = 0; idx < *fences_count; ++idx)
    {
        *(*fences + idx) = ((vk_fence *)PyList_GetItem(obj, idx))->fence;
    }
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

PyObject *vk_dev_reset_fences(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_reset_fences\n");

    PyObject *fences_obj = NULL;

    PyArg_Parse(args, "O", &fences_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_dev *self = (vk_dev *)self_obj;

    VkFence *fences = NULL;
    uint32_t fences_count = 0;
    get_fences_from_list(fences_obj, &fences, &fences_count);

    VkResult result = vkResetFences(self->device, fences_count, fences);

    if (fences != NULL)
    {
        free((void *)fences);
    }

    return PyLong_FromLong(result);
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

PyObject *vk_dev_create_image_view(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_create_image_view\n");

    vk_dev *self = (vk_dev *)self_obj;

    PyObject *ci_obj = NULL;

    PyArg_Parse(args, "O", &ci_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_img_view_ci *ci = (vk_img_view_ci *)ci_obj;
    vk_img_view *image_view = PyObject_NEW(vk_img_view, &vk_img_view_type);

    VkResult result = vkCreateImageView(self->device, &ci->ci, NULL, &image_view->image_view);

    PyObject *return_obj = PyTuple_New(2);
    PyTuple_SetItem(return_obj, 0, (PyObject *)image_view);
    PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

    return return_obj;
}

PyObject *vk_dev_destroy_image_view(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_destroy_image_view\n");

    vk_dev *self = (vk_dev *)self_obj;

    PyObject *image_view_obj = NULL;

    PyArg_Parse(args, "O", &image_view_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_img_view *image_view = (vk_img_view *)image_view_obj;

    if (image_view->image_view != VK_NULL_HANDLE)
    {
        DEBUG_LOG("destroying image_view\n");
        vkDestroyImageView(self->device, image_view->image_view, NULL);
    }

    Py_XDECREF(image_view_obj);

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

    char *kwlist[] = {"image", "device_memory", "offset", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OOk", kwlist, &img_obj, &mem_obj, &offset);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_img *img = (vk_img *)img_obj;
    vk_dev_mem *mem = (vk_dev_mem *)mem_obj;

    VkResult result = vkBindImageMemory(self->device, img->image, mem->device_memory, (VkDeviceSize)offset);
    ;

    return PyLong_FromLong(result);
}

PyObject *vk_dev_get_img_mem_req(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_get_img_mem_req\n");

    vk_dev *self = (vk_dev *)self_obj;

    PyObject *img_obj = NULL;

    PyArg_Parse(args, "O", &img_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_img *img = (vk_img *)img_obj;

    VkMemoryRequirements mem_req;
    vkGetImageMemoryRequirements(self->device, img->image, &mem_req);

    vk_mem_req *mr_obj = (vk_mem_req *)PyObject_NEW(vk_mem_req, &vk_mem_req_type);
    mr_obj->size = (unsigned long)mem_req.size;
    mr_obj->alignment = (unsigned long)mem_req.alignment;
    mr_obj->mem_type_bits = mem_req.memoryTypeBits;

    return (PyObject *)mr_obj;
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

    VkImage *images = (VkImage *)malloc(sizeof(VkImage *) * image_count);
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

    if (images != NULL)
    {
        free(images);
    }

    PyObject *return_obj = PyTuple_New(2);

    PyTuple_SetItem(return_obj, 0, imgs_obj);
    PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

    return return_obj;
}

PyObject *vk_dev_acquire_next_image(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_dev_acquire_next_image\n");

    PyObject *sc_obj = NULL;
    unsigned long timeout = 0;
    PyObject *sem_obj = NULL;
    PyObject *fence_obj = NULL;

    char *kwlist[] = {"swapchain", "timeout", "wait_semaphore", "fence", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OKOO", kwlist, &sc_obj, &timeout, &sem_obj, &fence_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_dev *self = (vk_dev *)self_obj;
    vk_swapchain *sc = (vk_swapchain *)sc_obj;
    vk_sem *sem = (vk_sem *)sem_obj;
    vk_fence *fence = (vk_fence *)fence_obj;

    uint32_t image_index = 0;
    VkResult result = vkAcquireNextImageKHR(self->device, sc->swapchain, timeout, sem->semaphore, fence->fence, &image_index);

    PyObject *return_obj = PyTuple_New(2);
    PyTuple_SetItem(return_obj, 0, PyLong_FromLong(image_index));
    PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

    return return_obj;
}

PyObject *vk_dev_wait_for_fences(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_dev_wait_for_fences\n");

    PyObject *fences_obj = NULL;
    bool wait_for_all = false;
    long timeout = 0;

    char *kwlist[] = {"fences", "wait_for_all", "timeout", NULL};
    PyArg_ParseTupleAndKeywords(args, kwds, "|Opk", kwlist, &fences_obj, &wait_for_all, &timeout);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    VkFence *fences = NULL;
    uint32_t fences_count = 0;
    get_fences_from_list(fences_obj, &fences, &fences_count);

    vk_dev *self = (vk_dev *)self_obj;
    VkResult result = vkWaitForFences(self->device, fences_count, fences, wait_for_all, timeout);

    if (fences != NULL)
    {
        free((void *)fences);
    }

    return PyLong_FromLong(result);
}

PyObject *vk_dev_map_memory(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_dev_map_memory\n");

    PyObject *dev_mem_obj = NULL;
    unsigned long offset = 0;
    unsigned long size = 0;
    uint32_t flags = 0;

    char *kwlist[] = {"memory", "offset", "size", "flags", NULL};

    PyArg_ParseTupleAndKeywords(args, kwds, "|OKKI", kwlist, &dev_mem_obj, &offset, &size, &flags);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_dev *self = (vk_dev *)self_obj;

    ++self->mapped_datas_count;
    if (self->mapped_datas == NULL)
    {
        self->mapped_datas = (void **)malloc(sizeof(void *) * self->mapped_datas_count);
    }
    else
    {
        self->mapped_datas = (void **)realloc(self->mapped_datas, sizeof(void *) * self->mapped_datas_count);
    }

    if (self->mapped_data_sizes == NULL)
    {
        self->mapped_data_sizes = (uint32_t *)malloc(sizeof(uint32_t) * self->mapped_datas_count);
    }
    else
    {
        self->mapped_data_sizes = (uint32_t *)realloc(self->mapped_data_sizes, sizeof(uint32_t) * self->mapped_datas_count);
    }

    uint32_t mapped_data_id = self->mapped_datas_count - 1;

    VkResult result = vkMapMemory(self->device, ((vk_dev_mem *)dev_mem_obj)->device_memory, offset, size, flags, &self->mapped_datas[mapped_data_id]);
    self->mapped_data_sizes[mapped_data_id] = size;

    PyObject *return_obj = PyTuple_New(2);

    PyTuple_SetItem(return_obj, 0, PyLong_FromLong(mapped_data_id));
    PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

    return return_obj;
}

PyObject *vk_dev_update_host_mapped_data(PyObject *self_obj, PyObject *args, PyObject *kwds)
{
    DEBUG_LOG("vk_dev_update_host_mapped_mem\n");

    PyObject *data_obj = NULL;
    const char *data = NULL;
    uint32_t mem_id = 0;

    char *kwlist[] = {"data", "mem_id", NULL};
    PyArg_ParseTupleAndKeywords(args, kwds, "|SI", kwlist, &data_obj, &mem_id);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vk_dev *self = (vk_dev *)self_obj;

    /*
    int is_bytes = PyBytes_Check(data_obj);
    printf("is_bytes: %d\n", is_bytes);

    if (is_bytes == 1)
    {
        char *data = NULL;
        Py_ssize_t size = 0;
        if (PyBytes_AsStringAndSize(data_obj, &data, &size) < 0)
        {
            return NULL;
        }

        for (uint32_t idx = 0; idx < size; ++idx)
        {
            printf("%x %d\n", data[idx], (unsigned char)data[idx]);
        }

        printf("end of data\n");
    }
    */
    int is_buffer = PyObject_CheckBuffer(data_obj);
    // printf("is_buffer: %d\n", is_buffer);

    if (is_buffer == 1)
    {
        Py_buffer buffer;
        PyObject_GetBuffer(data_obj, &buffer, 0);

        unsigned char *buff = (unsigned char *)malloc(sizeof(unsigned char) * 640 * 320 * 4);

        uint32_t idx = 0;
        for (uint32_t y = 0; y < 320; ++y)
        {
            for (uint32_t x = 0; x < 640; ++x)
            {
                buff[x + (y * 640 * 4)] = 255;     //((unsigned char *)buffer.buf)[idx];
                buff[x + (y * 640 * 4) + 1] = 0; //((unsigned char *)buffer.buf)[idx];
                buff[x + (y * 640 * 4) + 2] = 0; //((unsigned char *)buffer.buf)[idx];
                buff[x + (y * 640 * 4) + 3] = 255; //((unsigned char *)buffer.buf)[idx];

                ++idx;
            }
        }
        printf("idx: %u\n", idx);
        printf("size: %u\n", self->mapped_data_sizes[mem_id]);

        memcpy(self->mapped_datas[mem_id], buff, self->mapped_data_sizes[mem_id]);

        if (buff != NULL)
        {
            free(buff);
        }

        PyBuffer_Release(&buffer);
    }

    Py_RETURN_NONE;
}

PyObject *vk_dev_unmap_memory(PyObject *self_obj, PyObject *args)
{
    DEBUG_LOG("vk_dev_unmap_memory\n");

    PyObject *dev_mem_obj = NULL;

    PyArg_Parse(args, "O", &dev_mem_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    vkUnmapMemory(((vk_dev *)self_obj)->device, ((vk_dev_mem *)dev_mem_obj)->device_memory);

    Py_RETURN_NONE;
}

void vk_dev_dealloc(PyObject *self_obj)
{
    DEBUG_LOG("vk_dev_dealloc\n");

    vk_dev *self = (vk_dev *)self_obj;

    if (self->mapped_datas != NULL)
    {
        free(self->mapped_datas);
    }

    if (self->mapped_data_sizes != NULL)
    {
        free(self->mapped_data_sizes);
    }

    Py_TYPE(self_obj)->tp_free(self_obj);
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
    {"reset_fences", (PyCFunction)vk_dev_reset_fences, METH_O, NULL},
    {"destroy_fence", (PyCFunction)vk_dev_destroy_fence, METH_O, NULL},
    {"create_image", (PyCFunction)vk_dev_create_image, METH_O, NULL},
    {"destroy_image", (PyCFunction)vk_dev_destroy_image, METH_O, NULL},
    {"create_image_view", (PyCFunction)vk_dev_create_image_view, METH_O, NULL},
    {"destroy_image_view", (PyCFunction)vk_dev_destroy_image_view, METH_O, NULL},
    {"allocate_memory", (PyCFunction)vk_dev_allocate_memory, METH_O, NULL},
    {"free_memory", (PyCFunction)vk_dev_free_memory, METH_O, NULL},
    {"get_image_memory_requirements", (PyCFunction)vk_dev_get_img_mem_req, METH_O, NULL},
    {"bind_image_memory", (PyCFunction)vk_dev_bind_img_memory, METH_VARARGS | METH_KEYWORDS, NULL},
    {"get_swapchain_images", (PyCFunction)vk_dev_get_swapchain_images, METH_O, NULL},
    {"acquire_next_image", (PyCFunction)vk_dev_acquire_next_image, METH_VARARGS | METH_KEYWORDS, NULL},
    {"wait_for_fences", (PyCFunction)vk_dev_wait_for_fences, METH_VARARGS | METH_KEYWORDS, NULL},
    {"map_memory", (PyCFunction)vk_dev_map_memory, METH_VARARGS | METH_KEYWORDS, NULL},
    {"update_host_mapped_data", (PyCFunction)vk_dev_update_host_mapped_data, METH_VARARGS | METH_KEYWORDS, NULL},
    {"unmap_memory", (PyCFunction)vk_dev_unmap_memory, METH_O, NULL},
    {NULL},
};

PyTypeObject vk_dev_type = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "vulkan.device",
    .tp_basicsize = sizeof(vk_dev),
    .tp_doc = PyDoc_STR("Vulkan Device Docs"),
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_methods = vk_dev_methods,
    .tp_dealloc = vk_dev_dealloc,
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
