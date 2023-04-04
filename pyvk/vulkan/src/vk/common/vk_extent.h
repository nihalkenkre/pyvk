#ifndef VK_EXTENT
#define VK_EXTENT

typedef struct vk_extent
{
    PyObject_HEAD
        uint32_t width;
    uint32_t height;
} vk_extent;

PyObject* add_vk_extent_to_module(PyObject* mod);

PyTypeObject vk_extent_type;

#endif