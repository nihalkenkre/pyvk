#include "vk_phy_dev_limits.h"
#include "log.h"

PyMemberDef vk_phy_dev_limits_members[] = {
    {"max_image_dimension_1d", T_UINT, offsetof(vk_phy_dev_limits, max_image_dimension_1d), 1, "Max Image Dimension 1D"},
    {"max_image_dimension_2d", T_UINT, offsetof(vk_phy_dev_limits, max_image_dimension_2d), 1, "Max Image Dimension 2D"},
    {"max_image_dimension_3d", T_UINT, offsetof(vk_phy_dev_limits, max_image_dimension_3d), 1, "Max Image Dimension 3D"},
    {"max_image_dimension_cube", T_UINT, offsetof(vk_phy_dev_limits, max_image_dimension_cube), 1, "Max Image Dimension Cube"},
    {"max_image_array_layers", T_UINT, offsetof(vk_phy_dev_limits, max_image_array_layers), 1, "Max Image Array Layers"},
    {"max_texel_buffer_elements", T_UINT, offsetof(vk_phy_dev_limits, max_texel_buffer_elements), 1, "Max Image Texel Buffer Elemens"},

    {"max_uniform_buffer_range", T_UINT, offsetof(vk_phy_dev_limits, max_uniform_buffer_range), 1, "Max Uniform Buffer Range"},
    {"max_storage_buffer_range", T_UINT, offsetof(vk_phy_dev_limits, max_storage_buffer_range), 1, "Max Storage Buffer Range"},
    {"max_push_constants_size", T_UINT, offsetof(vk_phy_dev_limits, max_push_constants_size), 1, "Max Push Constants Size"},
    {"max_memory_allocation_count", T_UINT, offsetof(vk_phy_dev_limits, max_memory_allocation_count), 1, "Max Memory Allocation Count"},
    {"max_sampler_allocation_count", T_UINT, offsetof(vk_phy_dev_limits, max_sampler_allocation_count), 1, "Max Sampler Allocation Count"},
    {"buffer_image_granularity", T_LONG, offsetof(vk_phy_dev_limits, buffer_image_granularity), 1, "Buffer Image Granularity"},
    {"sparse_address_space_size", T_LONG, offsetof(vk_phy_dev_limits, sparse_address_space_size), 1, "Sparse Address Space Size"},
    {"max_bound_descriptor_sets", T_UINT, offsetof(vk_phy_dev_limits, max_bound_descriptor_sets), 1, "Max Bound Descriptor Sets"},

    {"max_per_stage_descriptor_samplers", T_UINT, offsetof(vk_phy_dev_limits, max_per_stage_descriptor_samplers), 1, "Max Per Stage Descriptor Samplers"},
    {"max_per_stage_descriptor_uniform_buffers", T_UINT, offsetof(vk_phy_dev_limits, max_per_stage_descriptor_uniform_buffers), 1, "Max Per Stage Descriptor Uniform Buffers"},
    {"max_per_stage_descriptor_storage_buffers", T_UINT, offsetof(vk_phy_dev_limits, max_per_stage_descriptor_storage_buffers), 1, "Max Per Stage Descriptor Storage Buffers"},
    {"max_per_stage_descriptor_sampled_images", T_UINT, offsetof(vk_phy_dev_limits, max_per_stage_descriptor_sampled_images), 1, "Max Per Stage Descriptor Sampled Images"},
    {"max_per_stage_descriptor_storage_images", T_UINT, offsetof(vk_phy_dev_limits, max_per_stage_descriptor_storage_images), 1, "Max Per Stage Descriptor Storage Images"},
    {"max_per_stage_descriptor_input_attachments", T_UINT, offsetof(vk_phy_dev_limits, max_per_stage_descriptor_input_attachments), 1, "Max Per Stage Descriptor Input Attachments"},
    {"max_per_stage_resources", T_UINT, offsetof(vk_phy_dev_limits, max_per_stage_resources), 1, "Max Per Stage Resources"},

    {"max_descriptor_set_samplers", T_UINT, offsetof(vk_phy_dev_limits, max_descriptor_set_samplers), 1, "Max Descriptor Set Samplers"},
    {"max_descriptor_set_uniform_buffers", T_UINT, offsetof(vk_phy_dev_limits, max_descriptor_set_uniform_buffers), 1, "Max Descriptor Set Uniform Buffers"},
    {"max_descriptor_set_uniform_buffers_dynamic", T_UINT, offsetof(vk_phy_dev_limits, max_descriptor_set_uniform_buffers_dynamic), 1, "Max Descriptor Set Uniform Buffers Dynamic"},
    {"max_descriptor_set_storage_buffers", T_UINT, offsetof(vk_phy_dev_limits, max_descriptor_set_storage_buffers), 1, "Max Descriptor Set Storage Buffers"},
    {"max_descriptor_set_storage_buffers_dynamic", T_UINT, offsetof(vk_phy_dev_limits, max_descriptor_set_storage_buffers_dynamic), 1, "Max Descriptor Set Storage Buffers Dynamic"},
    {"max_descriptor_set_sampled_images", T_UINT, offsetof(vk_phy_dev_limits, max_descriptor_set_sampled_images), 1, "Max Descriptor Set Sampled Images"},
    {"max_descriptor_set_storage_images", T_UINT, offsetof(vk_phy_dev_limits, max_descriptor_set_storage_images), 1, "Max Descriptor Set Storage Images"},
    {"max_descriptor_set_input_attachemnts", T_UINT, offsetof(vk_phy_dev_limits, max_descriptor_set_input_attachments), 1, "Max Descriptor Set Input Attachments"},

    {"max_vertex_input_attributes", T_UINT, offsetof(vk_phy_dev_limits, max_vertex_input_attributes), 1, "Max Vertex Input Attributes"},
    {"max_vertex_input_bindings", T_UINT, offsetof(vk_phy_dev_limits, max_vertex_input_bindings), 1, "Max Vertex Input Bindings"},
    {"max_vertex_input_attribute_offset", T_UINT, offsetof(vk_phy_dev_limits, max_vertex_input_attribute_offset), 1, "Max Vertex Input Attribute Offset"},
    {"max_vertex_input_binding_stride", T_UINT, offsetof(vk_phy_dev_limits, max_vertex_input_binding_stride), 1, "Max Vertex Input Binding Stride"},
    {"max_vertex_output_components", T_UINT, offsetof(vk_phy_dev_limits, max_vertex_output_components), 1, "Max Vertex Output Components"},

    {"max_tessellation_generation_level", T_UINT, offsetof(vk_phy_dev_limits, max_tessellation_generation_level), 1, "Max Tessellation Generation Level"},
    {"max_tessellation_patch_size", T_UINT, offsetof(vk_phy_dev_limits, max_tessellation_patch_size), 1, "Max Tessellation Patch Size"},
    {"max_tessellation_control_per_vertex_input_components", T_UINT, offsetof(vk_phy_dev_limits, max_tessellation_control_per_vertex_input_components), 1, "Max Tessellation Control Per Vertex Input Components"},
    {"max_tessellation_control_per_vertex_output_components", T_UINT, offsetof(vk_phy_dev_limits, max_tessellation_control_per_vertex_output_components), 1, "Max Tessellation Control Per Vertex Ouput Components"},
    {"max_tessellation_control_per_patch_output_components", T_UINT, offsetof(vk_phy_dev_limits, max_tessellation_control_per_patch_output_components), 1, "Max Tessellation Control Per Patch Ouput Components"},
    {"max_tessellation_control_total_output_components", T_UINT, offsetof(vk_phy_dev_limits, max_tessellation_control_total_output_components), 1, "Max Tessellation Control Total Ouput Components"},
    {"max_tessellation_evaluation_input_components", T_UINT, offsetof(vk_phy_dev_limits, max_tessellation_evaluation_input_components), 1, "Max Tessellation Evaluation Input Components"},
    {"max_tessellation_evaluation_output_components", T_UINT, offsetof(vk_phy_dev_limits, max_tessellation_evaluation_output_components), 1, "Max Tessellation Evaluation Output Components"},

    {"max_geometry_shader_invocations", T_UINT, offsetof(vk_phy_dev_limits, max_geometry_shader_invocations), 1, "Max Geometry Shader Invocations"},
    {"max_geometry_input_components", T_UINT, offsetof(vk_phy_dev_limits, max_geometry_input_components), 1, "Max Geometry Input Components"},
    {"max_geometry_output_components", T_UINT, offsetof(vk_phy_dev_limits, max_geometry_output_components), 1, "Max Geometry Output Components"},
    {"max_geometry_output_vertices", T_UINT, offsetof(vk_phy_dev_limits, max_geometry_output_vertices), 1, "Max Geometry Output Vertices"},
    {"max_geometry_total_output_components", T_UINT, offsetof(vk_phy_dev_limits, max_geometry_total_output_components), 1, "Max Geometry Total Output Components"},

    {"max_fragment_input_components", T_UINT, offsetof(vk_phy_dev_limits, max_fragment_input_components), 1, "Max Fragment Input Components"},
    {"max_fragment_output_attachments", T_UINT, offsetof(vk_phy_dev_limits, max_fragment_output_attachments), 1, "Max Fragment Output Attachments"},
    {"max_fragment_dual_src_attachments", T_UINT, offsetof(vk_phy_dev_limits, max_fragment_dual_src_attachments), 1, "Max Fragment Dual Src Attachments"},
    {"max_fragment_combined_output_resources", T_UINT, offsetof(vk_phy_dev_limits, max_fragment_combined_output_resources), 1, "Max Fragment Combined Output Resources"},

    {"max_compute_shared_memory_size", T_UINT, offsetof(vk_phy_dev_limits, max_compute_shared_memory_size), 1, "Max Compute Shared Memory Size"},
    {"max_compute_work_group_count", T_OBJECT_EX, offsetof(vk_phy_dev_limits, max_compute_work_group_count), 1, "Max Compute Work Group Count"},
    {"max_compute_work_group_invocations", T_UINT, offsetof(vk_phy_dev_limits, max_compute_work_group_invocations), 1, "Max Compute Work Group Invocations"},
    {"max_compute_work_group_size", T_OBJECT_EX, offsetof(vk_phy_dev_limits, max_compute_work_group_size), 1, "Max Compute Work Group Size"},

    {"sub_pixel_precision_bits", T_UINT, offsetof(vk_phy_dev_limits, sub_pixel_precision_bits), 1, "Sub Pixel Precision Bits"},
    {"sub_texel_precision_bits", T_UINT, offsetof(vk_phy_dev_limits, sub_texel_precision_bits), 1, "Sub Texel Precision Bits"},

    {"mipmap_precision_bits", T_UINT, offsetof(vk_phy_dev_limits, mipmap_precision_bits), 1, "Mipmap Precision Bits"},

    {"max_draw_indexed_index_value", T_UINT, offsetof(vk_phy_dev_limits, max_draw_indexed_index_value), 1, "Max Draw Indexed Index Value"},
    {"max_draw_indirect_count", T_UINT, offsetof(vk_phy_dev_limits, max_draw_indirect_count), 1, "Max Draw Indirect Count"},

    {"max_sampler_lod_bias", T_FLOAT, offsetof(vk_phy_dev_limits, max_sampler_lod_bias), 1, "Max Sampler LOD Bias"},
    {"max_sampler_anisotropy", T_FLOAT, offsetof(vk_phy_dev_limits, max_sampler_anisotropy), 1, "Max Sampler Anisotropy"},

    {"max_viewports", T_UINT, offsetof(vk_phy_dev_limits, max_viewports), 1, "Max Viewports"},
    {"max_viewport_dimensions", T_OBJECT_EX, offsetof(vk_phy_dev_limits, max_viewport_dimensions), 1, "Max Viewport Dimensions"},

    {"viewport_bounds_range", T_OBJECT_EX, offsetof(vk_phy_dev_limits, viewport_bounds_range), 1, "Viewport bound range"},
    {"viewport_sub_pixel_bits", T_OBJECT_EX, offsetof(vk_phy_dev_limits, viewport_sub_pixel_bits), 1, "Viewport Sub Pixel Bits"},

    {"min_memory_map_alignment", T_ULONGLONG, offsetof(vk_phy_dev_limits, min_memory_map_alignment), 1, "Min Memory Map Alignment"},
    {"min_texel_buffer_offset_alignment", T_LONG, offsetof(vk_phy_dev_limits, min_texel_buffer_offset_alignment), 1, "Min Texel Buffer Offset Alignment"},
    {"min_uniform_buffer_offset_alignment", T_LONG, offsetof(vk_phy_dev_limits, min_uniform_buffer_offset_alignment), 1, "Min Uniform Buffer Offset Alignment"},
    {"min_storage_buffer_offset_alignment", T_LONG, offsetof(vk_phy_dev_limits, min_storage_buffer_offset_alignment), 1, "Min Storage Buffer Offset Alignment"},

    {"min_texel_offset", T_INT, offsetof(vk_phy_dev_limits, min_texel_offset), 1, "Min Texel Offset"},
    {"max_texel_offset", T_UINT, offsetof(vk_phy_dev_limits, max_texel_offset), 1, "Max Texel Offset"},
    {"min_texel_gather_offset", T_INT, offsetof(vk_phy_dev_limits, min_texel_gather_offset), 1, "Min Texel Gather Offset"},
    {"max_texel_gather_offset", T_UINT, offsetof(vk_phy_dev_limits, max_texel_gather_offset), 1, "Max Texel Gather Offset"},

    {"min_interpolation_offset", T_FLOAT, offsetof(vk_phy_dev_limits, min_interpolation_offset), 1, "Min Interpolation Offset"},
    {"max_interpolation_offset", T_FLOAT, offsetof(vk_phy_dev_limits, max_interpolation_offset), 1, "Max Interpolation Offset"},

    {"sub_pixel_interpolation_offset_bits", T_UINT, offsetof(vk_phy_dev_limits, sub_pixel_interpolation_offset_bits), 1, "Sub Pixel Interpolation Offset Bits"},

    {"max_framebuffer_width", T_UINT, offsetof(vk_phy_dev_limits, max_framebuffer_width), 1, "Max Framebuffer Width"},
    {"max_framebuffer_height", T_UINT, offsetof(vk_phy_dev_limits, max_framebuffer_height), 1, "Max Framebuffer Height"},
    {"max_framebuffer_layers", T_UINT, offsetof(vk_phy_dev_limits, max_framebuffer_layers), 1, "Max Framebuffer Layers"},

    {"framebuffer_color_sample_counts", T_UINT, offsetof(vk_phy_dev_limits, framebuffer_color_sample_counts), 1, "Framebuffer Color Sample Counts"},
    {"framebuffer_depth_sample_counts", T_UINT, offsetof(vk_phy_dev_limits, framebuffer_depth_sample_counts), 1, "Framebuffer Depth Sample Counts"},
    {"framebuffer_stencil_sample_counts", T_UINT, offsetof(vk_phy_dev_limits, framebuffer_stencil_sample_counts), 1, "Framebuffer Stencil Sample Counts"},
    {"framebuffer_no_attachment_sample_counts", T_UINT, offsetof(vk_phy_dev_limits, framebuffer_no_attachment_sample_counts), 1, "Framebuffer No Attachment Sample Counts"},

    {"max_color_attachments", T_UINT, offsetof(vk_phy_dev_limits, max_color_attachments), 1, "Max Color Attachments"},

    {"sampled_image_color_sample_counts", T_UINT, offsetof(vk_phy_dev_limits, sampled_image_color_sample_counts), 1, "Sampled Image Color Sample Counts"},
    {"sampled_image_integer_sample_counts", T_UINT, offsetof(vk_phy_dev_limits, sampled_image_integer_sample_counts), 1, "Sampled Image Integer Sample Counts"},
    {"sampled_image_depth_sample_counts", T_UINT, offsetof(vk_phy_dev_limits, sampled_image_depth_sample_counts), 1, "Sampled Image Depth Sample Counts"},
    {"sampled_image_stencil_sample_counts", T_UINT, offsetof(vk_phy_dev_limits, sampled_image_stencil_sample_counts), 1, "Sampled Image Stencil Sample Counts"},

    {"storage_image_sample_counts", T_UINT, offsetof(vk_phy_dev_limits, storage_image_sample_counts), 1, "Storage Image Sample Counts"},
    {"max_sample_mask_words", T_UINT, offsetof(vk_phy_dev_limits, max_sample_mask_words), 1, "Max Sample Mask Words"},

    {"timestamp_compute_and_graphics", T_BOOL, offsetof(vk_phy_dev_limits, timestamp_compute_and_graphics), 1, "Timestamp Compute and Graphics"},
    {"timestamp_period", T_BOOL, offsetof(vk_phy_dev_limits, timestamp_period), 1, "Timestamp Period"},

    {"max_clip_distances", T_UINT, offsetof(vk_phy_dev_limits, max_clip_distances), 1, "Max Clip Distances"},
    {"max_cull_distances", T_UINT, offsetof(vk_phy_dev_limits, max_cull_distances), 1, "Max Cull Distances"},
    {"max_combined_clip_and_cull_distances", T_UINT, offsetof(vk_phy_dev_limits, max_combined_clip_and_cull_distances), 1, "Max Combined Clip and Cull Distances"},

    {"discrete_queue_properties", T_UINT, offsetof(vk_phy_dev_limits, discrete_queue_properties), 1, "Discrete Queue Properties"},

    {"point_size_range", T_OBJECT_EX, offsetof(vk_phy_dev_limits, point_size_range), 1, "Point Size Range"},
    {"line_width_range", T_OBJECT_EX, offsetof(vk_phy_dev_limits, line_width_range), 1, "Line Width Range"},

    {"point_size_granularity", T_FLOAT, offsetof(vk_phy_dev_limits, point_size_granularity), 1, "Point Size Granularity"},
    {"line_width_granularity", T_FLOAT, offsetof(vk_phy_dev_limits, line_width_granularity), 1, "Line Width Granularity"},

    {"strict_lines", T_BOOL, offsetof(vk_phy_dev_limits, strict_lines), 1, "Strict Lines"},
    {"standard_sample_locations", T_BOOL, offsetof(vk_phy_dev_limits, standard_sample_locations), 1, "Standard Sample Locations"},

    {"optimal_buffer_copy_offset_alignment", T_LONG, offsetof(vk_phy_dev_limits, optimal_buffer_copy_offset_alignment), 1, "Optimal Buffer Copy Offset Alignment"},
    {"optimal_buffer_copy_row_pitch_alignment", T_LONG, offsetof(vk_phy_dev_limits, optimal_buffer_copy_row_pitch_alignment), 1, "Optimal Buffer Copy Row Pitch Alignment"},

    {"non_coherent_atom_size", T_LONG, offsetof(vk_phy_dev_limits, non_coherent_atom_size), 1, "Non Coherent Atom Size"},

    {NULL},
};

void vk_phy_dev_limits_dealloc(PyObject *self)
{
    DEBUG_LOG("vk_phy_dev_limits_dealloc\n");

    Py_XDECREF(((vk_phy_dev_limits*)self)->max_compute_work_group_count);
    Py_XDECREF(((vk_phy_dev_limits*)self)->max_compute_work_group_size);
    Py_XDECREF(((vk_phy_dev_limits*)self)->max_viewport_dimensions);
    Py_XDECREF(((vk_phy_dev_limits*)self)->viewport_bounds_range);
    Py_XDECREF(((vk_phy_dev_limits*)self)->point_size_range);
    Py_XDECREF(((vk_phy_dev_limits*)self)->line_width_range);

    Py_TYPE(self)->tp_free(self);
}

PyTypeObject vk_phy_dev_limits_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.physical_device_limits",
    .tp_basicsize = sizeof(vk_phy_dev_limits),
    .tp_doc = PyDoc_STR("Vulkan Physical Device Limits Docs"),
    .tp_members = vk_phy_dev_limits_members,
    .tp_dealloc = vk_phy_dev_limits_dealloc,
};

PyObject *add_vk_phy_dev_limits_to_module(PyObject *mod)
{
    DEBUG_LOG("adding physical_device_limits object\n");

    if (PyType_Ready(&vk_phy_dev_limits_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready phy_dev_limits_type type to module");

        goto shutdown;
    }

    Py_INCREF(&vk_phy_dev_limits_type);

    if (PyModule_AddObject(mod, "physical_device_limits", (PyObject *)&vk_phy_dev_limits_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add phy_dev_limits_type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_phy_dev_limits_type);

    return NULL;
}
