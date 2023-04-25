#include "vk_img_view_ci.h"

#include <structmember.h>

#include "log.h"

PyMemberDef vk_img_view_ci_members[] = {
    {"flags", T_LONG, offsetof(vk_img_view_ci, flags), 0, "Creatong flags for the image view"},
    {"image", T_OBJECT_EX, offsetof(vk_img_view_ci, img), 0, "The image to be associated with the image view"},
    {"view_type", T_LONG, offsetof(vk_img_view_ci, view_type), 0, "The type of the image view"},
    {"format", T_LONG, offsetof(vk_img_view_ci, format), 0, "The format of the image view"},
    {"components", T_OBJECT_EX, offsetof(vk_img_view_ci, comps), 0, "Specify the remapping of the color compoents"},
    {"subresource_range", T_OBJECT_EX, offsetof(vk_img_view_ci, sub_re_range), 0, "The subresource range for this image view"},
    {NULL},
};
