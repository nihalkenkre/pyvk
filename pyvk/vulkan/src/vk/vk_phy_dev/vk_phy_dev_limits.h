#ifndef VK_PHY_DEV_LIMITS
#define VK_PHY_DEV_LIMITS

#include <Python.h>
#include <structmember.h>

#include <stdbool.h>

#include <vulkan/vulkan.h>

typedef struct vk_phy_dev_limits
{
    PyObject_HEAD
        uint32_t max_image_dimension_1d;
    uint32_t max_image_dimension_2d;
    uint32_t max_image_dimension_3d;
    uint32_t max_image_dimension_cube;
    uint32_t max_image_array_layers;

    uint32_t max_texel_buffer_elements;
    uint32_t max_uniform_buffer_range;
    uint32_t max_storage_buffer_range;

    uint32_t max_push_constants_size;

    uint32_t max_memory_allocation_count;
    uint32_t max_sampler_allocation_count;

    VkDeviceSize buffer_image_granularity;
    VkDeviceSize sparse_address_space_size;
    uint32_t max_bound_descriptor_sets;

    uint32_t max_per_stage_descriptor_samplers;
    uint32_t max_per_stage_descriptor_uniform_buffers;
    uint32_t max_per_stage_descriptor_storage_buffers;
    uint32_t max_per_stage_descriptor_sampled_images;
    uint32_t max_per_stage_descriptor_storage_images;
    uint32_t max_per_stage_descriptor_input_attachments;
    uint32_t max_per_stage_resources;

    uint32_t max_descriptor_set_samplers;
    uint32_t max_descriptor_set_uniform_buffers;
    uint32_t max_descriptor_set_uniform_buffers_dynamic;
    uint32_t max_descriptor_set_storage_buffers;
    uint32_t max_descriptor_set_storage_buffers_dynamic;
    uint32_t max_descriptor_set_sampled_images;
    uint32_t max_descriptor_set_storage_images;
    uint32_t max_descriptor_set_input_attachments;

    uint32_t max_vertex_input_attributes;
    uint32_t max_vertex_input_bindings;
    uint32_t max_vertex_input_attribute_offset;
    uint32_t max_vertex_input_binding_stride;
    uint32_t max_vertex_output_components;

    uint32_t max_tessellation_generation_level;
    uint32_t max_tessellation_patch_size;
    uint32_t max_tessellation_control_per_vertex_input_components;
    uint32_t max_tessellation_control_per_vertex_output_components;
    uint32_t max_tessellation_control_per_patch_output_components;
    uint32_t max_tessellation_control_total_output_components;
    uint32_t max_tessellation_evaluation_input_components;
    uint32_t max_tessellation_evaluation_output_components;

    uint32_t max_geometry_shader_invocations;
    uint32_t max_geometry_input_components;
    uint32_t max_geometry_output_components;
    uint32_t max_geometry_output_vertices;
    uint32_t max_geometry_total_output_components;

    uint32_t max_fragment_input_components;
    uint32_t max_fragment_output_attachments;
    uint32_t max_fragment_dual_src_attachments;
    uint32_t max_fragment_combined_output_resources;

    uint32_t max_compute_shared_memory_size;
    PyObject *max_compute_work_group_count;
    uint32_t max_compute_work_group_invocations;
    PyObject *max_compute_work_group_size;

    uint32_t sub_pixel_precision_bits;
    uint32_t sub_texel_precision_bits;

    uint32_t mipmap_precision_bits;

    uint32_t max_draw_indexed_index_value;
    uint32_t max_draw_indirect_count;

    float max_sampler_lod_bias;
    float max_sampler_anisotropy;

    uint32_t max_viewports;
    PyObject *max_viewport_dimensions;

    PyObject *viewport_bounds_range;
    uint32_t viewport_sub_pixel_bits;

    size_t min_memory_map_alignment;
    VkDeviceSize min_texel_buffer_offset_alignment;
    VkDeviceSize min_uniform_buffer_offset_alignment;
    VkDeviceSize min_storage_buffer_offset_alignment;

    int32_t min_texel_offset;
    uint32_t max_texel_offset;
    int32_t min_texel_gather_offset;
    uint32_t max_texel_gather_offset;

    float min_interpolation_offset;
    float max_interpolation_offset;

    uint32_t sub_pixel_interpolation_offset_bits;

    uint32_t max_framebuffer_width;
    uint32_t max_framebuffer_height;
    uint32_t max_framebuffer_layers;

    uint32_t framebuffer_color_sample_counts;
    uint32_t framebuffer_depth_sample_counts;
    uint32_t framebuffer_stencil_sample_counts;
    uint32_t framebuffer_no_attachment_sample_counts;

    uint32_t max_color_attachments;

    uint32_t sampled_image_color_sample_counts;
    uint32_t sampled_image_integer_sample_counts;
    uint32_t sampled_image_depth_sample_counts;
    uint32_t sampled_image_stencil_sample_counts;

    uint32_t storage_image_sample_counts;
    uint32_t max_sample_mask_words;

    bool timestamp_compute_and_graphics;
    float timestamp_period;

    uint32_t max_clip_distances;
    uint32_t max_cull_distances;
    uint32_t max_combined_clip_and_cull_distances;

    uint32_t discrete_queue_properties;

    PyObject *point_size_range;
    PyObject *line_width_range;

    float point_size_granularity;
    float line_width_granularity;

    bool strict_lines;
    bool standard_sample_locations;

    VkDeviceSize optimal_buffer_copy_offset_alignment;
    VkDeviceSize optimal_buffer_copy_row_pitch_alignment;

    VkDeviceSize non_coherent_atom_size;

    VkPhysicalDeviceLimits limits;
} vk_phy_dev_limits;

PyMemberDef vk_phy_dev_limits_members[];
PyTypeObject vk_phy_dev_limits_type;

PyObject *add_vk_phy_dev_limits_to_module(PyObject *mod);

#endif // VK_PHY_DEV_LIMITS