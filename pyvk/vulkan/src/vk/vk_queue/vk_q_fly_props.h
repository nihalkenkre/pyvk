#ifndef VK_Q_FLY_PROPS
#define VK_Q_FLY_PROPS

#include <Python.h>

typedef struct vk_q_fly_props
{
    PyObject_HEAD
        uint32_t q_flags;
    uint32_t q_count;
    uint32_t timestamp_valid_bits;
    PyObject *min_image_xfer_grains;
} vk_q_fly_props;

PyTypeObject vk_q_fly_props_type;

PyObject *add_vk_q_fly_props_to_module(PyObject *mod);

#endif