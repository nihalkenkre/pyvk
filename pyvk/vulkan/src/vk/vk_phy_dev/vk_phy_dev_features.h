#ifndef VK_PHY_DEV_FEATURES
#define VK_PHY_DEV_FEATURES

#include <Python.h>
#include <structmember.h>

#include <stdbool.h>

#include <vulkan/vulkan.h>

typedef struct vk_phy_dev_features
{
    PyObject_HEAD bool robust_buffer_access;
    bool full_draw_index_uint32;
    bool image_cube_array;
    bool independent_blend;

    bool geometry_shader;
    bool tessellation_shader;

    bool sample_rate_shading;
    bool dual_src_blend;
    bool logic_op;

    bool multi_draw_indirect;
    bool draw_indirect_first_instance;

    bool depth_clamp;
    bool fill_mode_non_solid;
    bool depth_bounds;
    bool wide_lines;
    bool large_points;
    bool alpha_to_one;
    bool multi_viewport;
    bool sampler_anisotropy;

    bool texture_compression_etc2;
    bool texture_compression_astc_ldr;
    bool texture_compression_bc;

    bool occlusion_query_precise;
    bool pipeline_statistics_query;

    bool vertex_pipeline_stores_and_atomics;
    bool fragment_stores_and_atomics;

    bool shader_tessellation_and_geometry_point_size;
    bool shader_image_gather_extended;
    bool shader_storage_image_extended_formats;
    bool shader_storage_image_multisample;
    bool shader_storage_image_read_without_format;
    bool shader_storage_image_write_without_format;
    bool shader_uniform_buffer_array_dynamic_indexing;
    bool shader_sampled_image_array_dynamic_indexing;
    bool shader_storage_buffer_array_dynamic_indexing;
    bool shader_storage_image_array_dynamic_indexing;

    bool shader_clip_distance;
    bool shader_cull_distance;

    bool shader_float_64;
    bool shader_int_64;
    bool shader_int_16;

    bool shader_resource_residency;
    bool shader_resource_min_lod;

    bool sparse_binding;
    bool sparse_residency_buffer;
    bool sparse_residency_image_2d;
    bool sparse_residency_image_3d;
    bool sparse_residency_2_samples;
    bool sparse_residency_4_samples;
    bool sparse_residency_8_samples;
    bool sparse_residency_16_samples;
    bool sparse_residency_aliased;

    bool variable_multisample_rate;
    bool inherited_queries;

    VkPhysicalDeviceFeatures features;
} vk_phy_dev_features;

PyTypeObject vk_phy_dev_features_type;

PyObject *add_vk_phy_dev_features_to_module(PyObject *mod);

#endif // VK_PHY_DEV_FEATURES