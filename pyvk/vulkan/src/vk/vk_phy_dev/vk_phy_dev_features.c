#include "vk_phy_dev_features.h"
#include "log.h"

PyMemberDef vk_phy_dev_features_members[] = {
    {"robust_buffer_access", T_BOOL, offsetof(vk_phy_dev_features, robust_buffer_access), 1, "Robust Buffer Access"},
    {"full_draw_index_uint32", T_BOOL, offsetof(vk_phy_dev_features, full_draw_index_uint32), 1, "Full Draw Index Uint32"},
    {"image_cube_array", T_BOOL, offsetof(vk_phy_dev_features, image_cube_array), 1, "Image Cube Array"},
    {"independent_blend", T_BOOL, offsetof(vk_phy_dev_features, independent_blend), 1, "Independent Blend"},

    {"geometry_shader", T_BOOL, offsetof(vk_phy_dev_features, geometry_shader), 1, "Geometry Shader"},
    {"tessellation_shader", T_BOOL, offsetof(vk_phy_dev_features, tessellation_shader), 1, "Tessellation Shader"},

    {"sample_rate_shading", T_BOOL, offsetof(vk_phy_dev_features, sample_rate_shading), 1, "Sample Rate Shading"},
    {"dual_src_blend", T_BOOL, offsetof(vk_phy_dev_features, dual_src_blend), 1, "Dual Src Blend"},
    {"logic_op", T_BOOL, offsetof(vk_phy_dev_features, logic_op), 1, "Logic Op"},

    {"multi_draw_indirect", T_BOOL, offsetof(vk_phy_dev_features, multi_draw_indirect), 1, "Multi Draw Indirect"},
    {"draw_indirect_first_instance", T_BOOL, offsetof(vk_phy_dev_features, draw_indirect_first_instance), 1, "Draw Indirect First Instance"},

    {"depth_clamp", T_BOOL, offsetof(vk_phy_dev_features, depth_clamp), 1, "Depth Clamp"},
    {"fill_mode_non_solid", T_BOOL, offsetof(vk_phy_dev_features, fill_mode_non_solid), 1, "Fill Mode Non Solid"},
    {"depth_bounds", T_BOOL, offsetof(vk_phy_dev_features, depth_bounds), 1, "Depth Bounds"},
    {"wide_lines", T_BOOL, offsetof(vk_phy_dev_features, wide_lines), 1, "Wide Lines"},
    {"large_points", T_BOOL, offsetof(vk_phy_dev_features, large_points), 1, "Large Points"},
    {"alpha_to_one", T_BOOL, offsetof(vk_phy_dev_features, alpha_to_one), 1, "Alpha To One"},
    {"multi_viewport", T_BOOL, offsetof(vk_phy_dev_features, multi_viewport), 1, "Multi Viewport"},
    {"sampler_anisotropy", T_BOOL, offsetof(vk_phy_dev_features, sampler_anisotropy), 1, "Sampler Anisotropy"},
    
    {"texture_compression_etc2", T_BOOL, offsetof(vk_phy_dev_features, texture_compression_etc2), 1, "Texture Compression ETC2"},
    {"texture_compression_astc_ldr", T_BOOL, offsetof(vk_phy_dev_features, texture_compression_astc_ldr), 1, "Texture Compression ASTC LDR"},
    {"texture_compression_bc", T_BOOL, offsetof(vk_phy_dev_features, texture_compression_bc), 1, "Texture Compression BC"},

    {"occlusion_query_precise", T_BOOL, offsetof(vk_phy_dev_features, occlusion_query_precise), 1, "Occlusion Query Precise"},
    {"pipeline_statistics_query", T_BOOL, offsetof(vk_phy_dev_features, pipeline_statistics_query), 1, "Pipeline Statistics Query"},

    {"vertex_pipeline_stores_and_atomics", T_BOOL, offsetof(vk_phy_dev_features, vertex_pipeline_stores_and_atomics), 1, "Vertex Pipeline Stores and Atomics"},
    {"fragment_stores_and_atomics", T_BOOL, offsetof(vk_phy_dev_features, fragment_stores_and_atomics), 1, "Fragment Stores and Atomics"},

    {"shader_tessellation_and_geometry_point_size", T_BOOL, offsetof(vk_phy_dev_features, shader_tessellation_and_geometry_point_size), 1, "Shader Tessellation and Geometry Point Size"},
    {"shader_image_gather_extended", T_BOOL, offsetof(vk_phy_dev_features, shader_image_gather_extended), 1, "Shader Image Gather Extended"},
    {"shader_storage_image_extended_formats", T_BOOL, offsetof(vk_phy_dev_features, shader_storage_image_extended_formats), 1, "Shader Storage Image Extended Formats"},
    {"shader_storage_image_multisample", T_BOOL, offsetof(vk_phy_dev_features, shader_storage_image_multisample), 1, "Shader Storage Image Multisample"},
    {"shader_storage_image_read_without_format", T_BOOL, offsetof(vk_phy_dev_features, shader_storage_image_read_without_format), 1, "Shader Storage Image Read Without Format"},
    {"shader_storage_image_write_without_format", T_BOOL, offsetof(vk_phy_dev_features, shader_storage_image_write_without_format), 1, "Shader Storage Image Write Without Format"},
    {"shader_uniform_buffer_array_dynamic_indexing", T_BOOL, offsetof(vk_phy_dev_features, shader_uniform_buffer_array_dynamic_indexing), 1, "Shader Uniform Buffer Array Dynamic Indexing"},
    {"shader_sampled_image_array_dynamic_indexing", T_BOOL, offsetof(vk_phy_dev_features, shader_sampled_image_array_dynamic_indexing), 1, "Shader Sample Image Array Dynamic Indexing"},
    {"shader_storage_buffer_array_dynamic_indexing", T_BOOL, offsetof(vk_phy_dev_features, shader_storage_buffer_array_dynamic_indexing), 1, "Shader Storage Buffer Array Dynamic Indexing"},
    {"shader_storage_image_array_dynamic_indexing", T_BOOL, offsetof(vk_phy_dev_features, shader_storage_image_array_dynamic_indexing), 1, "Shader Storage Image Array Dynamic Indexing"},

    {"shader_clip_distance", T_BOOL, offsetof(vk_phy_dev_features, shader_clip_distance), 1, "Shader Clip Distance"},
    {"shader_cull_distance", T_BOOL, offsetof(vk_phy_dev_features, shader_cull_distance), 1, "Shader Cull Distance"},

    {"shader_float_64", T_BOOL, offsetof(vk_phy_dev_features, shader_float_64), 1, "Shader Float64"},
    {"shader_int_64", T_BOOL, offsetof(vk_phy_dev_features, shader_int_64), 1, "Shader Int64"},
    {"shader_int_16", T_BOOL, offsetof(vk_phy_dev_features, shader_int_16), 1, "Shader Int16"},

    {"shader_resource_residency", T_BOOL, offsetof(vk_phy_dev_features, shader_resource_residency), 1, "Shader Resource Residency"},
    {"shader_resource_min_lod", T_BOOL, offsetof(vk_phy_dev_features, shader_resource_min_lod), 1, "Shader Resource Min Lod"},
    {"sparse_binding", T_BOOL, offsetof(vk_phy_dev_features, sparse_binding), 1, "Sparse Binding"},
    {"sparse_residency_buffer", T_BOOL, offsetof(vk_phy_dev_features, sparse_residency_buffer), 1, "Sparse Residency Buffer"},
    {"sparse_residency_image_2d", T_BOOL, offsetof(vk_phy_dev_features, sparse_residency_image_2d), 1, "Sparse Residency Image 2D"},
    {"sparse_residency_image_3d", T_BOOL, offsetof(vk_phy_dev_features, sparse_residency_image_3d), 1, "Sparse Residency Image 3D"},
    {"sparse_residency_2_samples", T_BOOL, offsetof(vk_phy_dev_features, sparse_residency_2_samples), 1, "Sparse Residency 2 Samples"},
    {"sparse_residency_4_samples", T_BOOL, offsetof(vk_phy_dev_features, sparse_residency_4_samples), 1, "Sparse Residency 4 Samples"},
    {"sparse_residency_8_samples", T_BOOL, offsetof(vk_phy_dev_features, sparse_residency_8_samples), 1, "Sparse Residency 8 Samples"},
    {"sparse_residency_16_samples", T_BOOL, offsetof(vk_phy_dev_features, sparse_residency_16_samples), 1, "Sparse Residency 16 Samples"},
    {"sparse_residency_aliased", T_BOOL, offsetof(vk_phy_dev_features, sparse_residency_aliased), 1, "Sparse Residency Aliased"},

    {"variable_multisample_rate", T_BOOL, offsetof(vk_phy_dev_features, variable_multisample_rate), 1, "Variable Multisample Rate"},
    {"inherited_queries", T_BOOL, offsetof(vk_phy_dev_features, inherited_queries), 1, "Inherited Queries"},
    {NULL},
};

PyTypeObject vk_phy_dev_features_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.physical_device_features",
    .tp_basicsize = sizeof(vk_phy_dev_features),
    .tp_doc = PyDoc_STR("Vulkan Physical Device Features"),
    .tp_members = vk_phy_dev_features_members,
};

PyObject *add_vk_phy_dev_features_to_module(PyObject *mod)
{
    DEBUG_LOG("adding physical_device_features object\n");

    if (PyType_Ready(&vk_phy_dev_features_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready phy_dev_limits_type type to module");

        goto shutdown;
    }

    Py_INCREF(&vk_phy_dev_features_type);

    if (PyModule_AddObject(mod, "physical_device_features", (PyObject *)&vk_phy_dev_features_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add phy_dev_features_type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_phy_dev_features_type);

    return NULL;
}