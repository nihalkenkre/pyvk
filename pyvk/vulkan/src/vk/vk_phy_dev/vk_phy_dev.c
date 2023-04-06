#include "vk_phy_dev.h"
#include "vk_mem_type.h"
#include "vk_mem_heap.h"
#include "vk_phy_dev_features.h"
#include "vk_phy_dev_props.h"
#include "vk_phy_dev_mem_props.h"
#include "vk_phy_dev_limits.h"
#include "vk_phy_dev_sparse_properties.h"
#include "vk_dev_ci.h"
#include "vk_dev.h"
#include "vk_surface.h"
#include "vk_surface_caps_khr.h"

#include "log.h"

PyObject *create_phy_dev_limits_obj(const VkPhysicalDeviceLimits *limits)
{
    vk_phy_dev_limits *limits_obj = PyObject_NEW(vk_phy_dev_limits, &vk_phy_dev_limits_type);

    limits_obj->max_image_dimension_1d = limits->maxImageDimension1D;
    limits_obj->max_image_dimension_2d = limits->maxImageDimension2D;
    limits_obj->max_image_dimension_3d = limits->maxImageDimension3D;
    limits_obj->max_image_dimension_cube = limits->maxImageDimensionCube;
    limits_obj->max_image_array_layers = limits->maxImageArrayLayers;

    limits_obj->max_texel_buffer_elements = limits->maxTexelBufferElements;
    limits_obj->max_uniform_buffer_range = limits->maxUniformBufferRange;
    limits_obj->max_storage_buffer_range = limits->maxStorageBufferRange;

    limits_obj->max_push_constants_size = limits->maxPushConstantsSize;

    limits_obj->max_memory_allocation_count = limits->maxMemoryAllocationCount;
    limits_obj->max_sampler_allocation_count = limits->maxSamplerAllocationCount;

    limits_obj->buffer_image_granularity = limits->bufferImageGranularity;
    limits_obj->sparse_address_space_size = limits->sparseAddressSpaceSize;
    limits_obj->max_bound_descriptor_sets = limits->maxBoundDescriptorSets;

    limits_obj->max_per_stage_descriptor_samplers = limits->maxPerStageDescriptorSamplers;
    limits_obj->max_per_stage_descriptor_uniform_buffers = limits->maxPerStageDescriptorUniformBuffers;
    limits_obj->max_per_stage_descriptor_storage_buffers = limits->maxPerStageDescriptorStorageBuffers;
    limits_obj->max_per_stage_descriptor_sampled_images = limits->maxPerStageDescriptorSampledImages;
    limits_obj->max_per_stage_descriptor_storage_images = limits->maxPerStageDescriptorStorageImages;
    limits_obj->max_per_stage_descriptor_input_attachments = limits->maxPerStageDescriptorInputAttachments;
    limits_obj->max_per_stage_resources = limits->maxPerStageResources;

    limits_obj->max_descriptor_set_samplers = limits->maxDescriptorSetSamplers;
    limits_obj->max_descriptor_set_uniform_buffers = limits->maxDescriptorSetUniformBuffers;
    limits_obj->max_descriptor_set_uniform_buffers_dynamic = limits->maxDescriptorSetUniformBuffersDynamic;
    limits_obj->max_descriptor_set_storage_buffers = limits->maxDescriptorSetStorageBuffers;
    limits_obj->max_descriptor_set_storage_buffers_dynamic = limits->maxDescriptorSetStorageBuffersDynamic;
    limits_obj->max_descriptor_set_sampled_images = limits->maxDescriptorSetSampledImages;
    limits_obj->max_descriptor_set_input_attachments = limits->maxDescriptorSetInputAttachments;

    limits_obj->max_vertex_input_attributes = limits->maxVertexInputAttributes;
    limits_obj->max_vertex_input_bindings = limits->maxVertexInputBindings;
    limits_obj->max_vertex_input_attribute_offset = limits->maxVertexInputAttributeOffset;
    limits_obj->max_vertex_input_binding_stride = limits->maxVertexInputBindingStride;
    limits_obj->max_vertex_output_components = limits->maxVertexOutputComponents;

    limits_obj->max_tessellation_generation_level = limits->maxTessellationGenerationLevel;
    limits_obj->max_tessellation_patch_size = limits->maxTessellationPatchSize;
    limits_obj->max_tessellation_control_per_vertex_input_components = limits->maxTessellationControlPerVertexInputComponents;
    limits_obj->max_tessellation_control_per_vertex_output_components = limits->maxTessellationControlPerVertexOutputComponents;
    limits_obj->max_tessellation_control_per_patch_output_components = limits->maxTessellationControlPerPatchOutputComponents;
    limits_obj->max_tessellation_control_total_output_components = limits->maxTessellationControlTotalOutputComponents;
    limits_obj->max_tessellation_evaluation_input_components = limits->maxTessellationEvaluationInputComponents;
    limits_obj->max_tessellation_evaluation_output_components = limits->maxTessellationEvaluationOutputComponents;

    limits_obj->max_geometry_shader_invocations = limits->maxGeometryShaderInvocations;
    limits_obj->max_geometry_input_components = limits->maxGeometryInputComponents;
    limits_obj->max_geometry_output_components = limits->maxGeometryOutputComponents;
    limits_obj->max_geometry_total_output_components = limits->maxGeometryTotalOutputComponents;

    limits_obj->max_fragment_input_components = limits->maxFragmentInputComponents;
    limits_obj->max_fragment_output_attachments = limits->maxFragmentOutputAttachments;
    limits_obj->max_fragment_dual_src_attachments = limits->maxFragmentDualSrcAttachments;
    limits_obj->max_fragment_combined_output_resources = limits->maxFragmentCombinedOutputResources;

    limits_obj->max_compute_shared_memory_size = limits->maxComputeSharedMemorySize;

    PyObject *work_group_count_obj = PyTuple_New(3);
    PyTuple_SetItem(work_group_count_obj, 0, PyLong_FromLong(limits->maxComputeWorkGroupCount[0]));
    PyTuple_SetItem(work_group_count_obj, 1, PyLong_FromLong(limits->maxComputeWorkGroupCount[1]));
    PyTuple_SetItem(work_group_count_obj, 2, PyLong_FromLong(limits->maxComputeWorkGroupCount[2]));
    limits_obj->max_compute_work_group_count = work_group_count_obj;

    limits_obj->max_compute_work_group_invocations = limits->maxComputeWorkGroupInvocations;

    PyObject *work_group_size_obj = PyTuple_New(3);
    PyTuple_SetItem(work_group_size_obj, 0, PyLong_FromLong(limits->maxComputeWorkGroupSize[0]));
    PyTuple_SetItem(work_group_size_obj, 1, PyLong_FromLong(limits->maxComputeWorkGroupSize[1]));
    PyTuple_SetItem(work_group_size_obj, 2, PyLong_FromLong(limits->maxComputeWorkGroupSize[2]));
    limits_obj->max_compute_work_group_size = work_group_size_obj;

    limits_obj->sub_pixel_precision_bits = limits->subPixelPrecisionBits;
    limits_obj->sub_texel_precision_bits = limits->subTexelPrecisionBits;

    limits_obj->mipmap_precision_bits = limits->mipmapPrecisionBits;

    limits_obj->max_draw_indexed_index_value = limits->maxDrawIndexedIndexValue;
    limits_obj->max_draw_indirect_count = limits->maxDrawIndirectCount;

    limits_obj->max_sampler_lod_bias = limits->maxSamplerLodBias;
    limits_obj->max_sampler_anisotropy = limits->maxSamplerAnisotropy;

    limits_obj->max_viewports = limits->maxViewports;

    PyObject *max_dimensions_obj = PyTuple_New(2);
    PyTuple_SetItem(max_dimensions_obj, 0, PyLong_FromLong(limits->maxViewportDimensions[0]));
    PyTuple_SetItem(max_dimensions_obj, 1, PyLong_FromLong(limits->maxViewportDimensions[1]));
    limits_obj->max_viewport_dimensions = max_dimensions_obj;

    PyObject *bounds_range_obj = PyTuple_New(2);
    PyTuple_SetItem(bounds_range_obj, 0, PyFloat_FromDouble(limits->viewportBoundsRange[0]));
    PyTuple_SetItem(bounds_range_obj, 1, PyFloat_FromDouble(limits->viewportBoundsRange[1]));
    limits_obj->viewport_bounds_range = bounds_range_obj;

    limits_obj->viewport_sub_pixel_bits = limits->viewportSubPixelBits;

    limits_obj->min_memory_map_alignment = limits->minMemoryMapAlignment;

    limits_obj->min_texel_buffer_offset_alignment = limits->minTexelBufferOffsetAlignment;
    limits_obj->min_uniform_buffer_offset_alignment = limits->minUniformBufferOffsetAlignment;
    limits_obj->min_storage_buffer_offset_alignment = limits->minStorageBufferOffsetAlignment;

    limits_obj->min_texel_offset = limits->minTexelOffset;
    limits_obj->max_texel_offset = limits->maxTexelOffset;
    limits_obj->min_texel_gather_offset = limits->minTexelGatherOffset;
    limits_obj->max_texel_gather_offset = limits->maxTexelGatherOffset;

    limits_obj->min_interpolation_offset = limits->minInterpolationOffset;
    limits_obj->max_interpolation_offset = limits->maxInterpolationOffset;

    limits_obj->sub_pixel_interpolation_offset_bits = limits->subPixelInterpolationOffsetBits;

    limits_obj->max_framebuffer_width = limits->maxFramebufferWidth;
    limits_obj->max_framebuffer_height = limits->maxFramebufferHeight;
    limits_obj->max_framebuffer_layers = limits->maxFramebufferLayers;

    limits_obj->framebuffer_color_sample_counts = limits->framebufferColorSampleCounts;
    limits_obj->framebuffer_depth_sample_counts = limits->framebufferDepthSampleCounts;
    limits_obj->framebuffer_stencil_sample_counts = limits->framebufferStencilSampleCounts;
    limits_obj->framebuffer_no_attachment_sample_counts = limits->framebufferNoAttachmentsSampleCounts;

    limits_obj->max_color_attachments = limits->maxColorAttachments;

    limits_obj->sampled_image_color_sample_counts = limits->sampledImageColorSampleCounts;
    limits_obj->sampled_image_integer_sample_counts = limits->sampledImageIntegerSampleCounts;
    limits_obj->sampled_image_depth_sample_counts = limits->sampledImageDepthSampleCounts;
    limits_obj->sampled_image_stencil_sample_counts = limits->sampledImageStencilSampleCounts;

    limits_obj->storage_image_sample_counts = limits->storageImageSampleCounts;
    limits_obj->max_sample_mask_words = limits->maxSampleMaskWords;

    limits_obj->timestamp_compute_and_graphics = limits->timestampComputeAndGraphics;
    limits_obj->timestamp_period = limits->timestampPeriod;

    limits_obj->max_clip_distances = limits->maxClipDistances;
    limits_obj->max_cull_distances = limits->maxCullDistances;
    limits_obj->max_combined_clip_and_cull_distances = limits->maxCombinedClipAndCullDistances;

    limits_obj->discrete_queue_properties = limits->discreteQueuePriorities;

    PyObject *point_size_range_obj = PyTuple_New(2);
    PyTuple_SetItem(point_size_range_obj, 0, PyFloat_FromDouble(limits->pointSizeRange[0]));
    PyTuple_SetItem(point_size_range_obj, 1, PyFloat_FromDouble(limits->pointSizeRange[1]));
    limits_obj->point_size_range = point_size_range_obj;

    PyObject *line_width_range_obj = PyTuple_New(2);
    PyTuple_SetItem(line_width_range_obj, 0, PyFloat_FromDouble(limits->lineWidthRange[0]));
    PyTuple_SetItem(line_width_range_obj, 1, PyFloat_FromDouble(limits->lineWidthRange[1]));
    limits_obj->line_width_range = line_width_range_obj;

    limits_obj->point_size_granularity = limits->pointSizeGranularity;
    limits_obj->line_width_granularity = limits->lineWidthGranularity;

    limits_obj->strict_lines = limits->strictLines;
    limits_obj->standard_sample_locations = limits->standardSampleLocations;

    limits_obj->optimal_buffer_copy_offset_alignment = limits->optimalBufferCopyOffsetAlignment;
    limits_obj->optimal_buffer_copy_row_pitch_alignment = limits->optimalBufferCopyRowPitchAlignment;

    limits_obj->non_coherent_atom_size = limits->nonCoherentAtomSize;

    limits_obj->limits = *limits;

    return (PyObject *)limits_obj;
}

PyObject *create_phy_dev_sparse_props_obj(const VkPhysicalDeviceSparseProperties *sparse_props)
{
    vk_phy_dev_sparse_props *sparse_props_obj = PyObject_NEW(vk_phy_dev_sparse_props, &vk_phy_dev_sparse_props_type);

    sparse_props_obj->residency_standard_2d_block_shape = sparse_props->residencyStandard2DBlockShape;
    sparse_props_obj->residency_standard_2d_multisample_block_shape = sparse_props->residencyStandard2DMultisampleBlockShape;
    sparse_props_obj->residency_standard_3d_block_shape = sparse_props->residencyStandard3DBlockShape;
    sparse_props_obj->residency_aligned_mip_size = sparse_props->residencyAlignedMipSize;
    sparse_props_obj->residency_non_resident_strict = sparse_props->residencyNonResidentStrict;

    sparse_props_obj->props = *sparse_props;

    return (PyObject *)sparse_props_obj;
}

PyObject *create_phy_dev_features_obj(const VkPhysicalDeviceFeatures *features)
{
    vk_phy_dev_features *features_obj = PyObject_NEW(vk_phy_dev_features, &vk_phy_dev_features_type);

    features_obj->robust_buffer_access = features->robustBufferAccess;
    features_obj->full_draw_index_uint32 = features->fullDrawIndexUint32;
    features_obj->image_cube_array = features->imageCubeArray;
    features_obj->independent_blend = features->independentBlend;

    features_obj->geometry_shader = features->geometryShader;
    features_obj->tessellation_shader = features->tessellationShader;

    features_obj->sample_rate_shading = features->sampleRateShading;
    features_obj->dual_src_blend = features->dualSrcBlend;
    features_obj->logic_op = features->logicOp;

    features_obj->multi_draw_indirect = features->multiDrawIndirect;
    features_obj->draw_indirect_first_instance = features->drawIndirectFirstInstance;
    features_obj->depth_clamp = features->depthClamp;
    features_obj->fill_mode_non_solid = features->fillModeNonSolid;
    features_obj->depth_bounds = features->depthBounds;
    features_obj->wide_lines = features->wideLines;
    features_obj->large_points = features->largePoints;
    features_obj->alpha_to_one = features->alphaToOne;
    features_obj->multi_viewport = features->multiViewport;
    features_obj->sampler_anisotropy = features->samplerAnisotropy;

    features_obj->texture_compression_etc2 = features->textureCompressionETC2;
    features_obj->texture_compression_astc_ldr = features->textureCompressionASTC_LDR;
    features_obj->texture_compression_bc = features->textureCompressionBC;

    features_obj->occlusion_query_precise = features->occlusionQueryPrecise;
    features_obj->pipeline_statistics_query = features->pipelineStatisticsQuery;

    features_obj->vertex_pipeline_stores_and_atomics = features->vertexPipelineStoresAndAtomics;
    features_obj->fragment_stores_and_atomics = features->fragmentStoresAndAtomics;

    features_obj->shader_tessellation_and_geometry_point_size = features->shaderTessellationAndGeometryPointSize;
    features_obj->shader_image_gather_extended = features->shaderImageGatherExtended;
    features_obj->shader_storage_image_extended_formats = features->shaderStorageImageExtendedFormats;
    features_obj->shader_storage_image_multisample = features->shaderStorageImageMultisample;
    features_obj->shader_storage_image_read_without_format = features->shaderStorageImageReadWithoutFormat;
    features_obj->shader_storage_image_write_without_format = features->shaderStorageImageWriteWithoutFormat;
    features_obj->shader_uniform_buffer_array_dynamic_indexing = features->shaderUniformBufferArrayDynamicIndexing;
    features_obj->shader_sampled_image_array_dynamic_indexing = features->shaderSampledImageArrayDynamicIndexing;
    features_obj->shader_storage_buffer_array_dynamic_indexing = features->shaderStorageBufferArrayDynamicIndexing;
    features_obj->shader_storage_image_array_dynamic_indexing = features->shaderStorageImageArrayDynamicIndexing;

    features_obj->shader_clip_distance = features->shaderClipDistance;
    features_obj->shader_cull_distance = features->shaderCullDistance;

    features_obj->shader_resource_residency = features->shaderResourceResidency;
    features_obj->shader_resource_min_lod = features->shaderResourceMinLod;

    features_obj->sparse_binding = features->sparseBinding;
    features_obj->sparse_residency_buffer = features->sparseResidencyBuffer;
    features_obj->sparse_residency_image_2d = features->sparseResidencyImage2D;
    features_obj->sparse_residency_image_3d = features->sparseResidencyImage3D;
    features_obj->sparse_residency_2_samples = features->sparseResidency2Samples;
    features_obj->sparse_residency_4_samples = features->sparseResidency4Samples;
    features_obj->sparse_residency_8_samples = features->sparseResidency8Samples;
    features_obj->sparse_residency_16_samples = features->sparseResidency16Samples;
    features_obj->sparse_residency_aliased = features->sparseResidencyAliased;

    features_obj->variable_multisample_rate = features->variableMultisampleRate;
    features_obj->inherited_queries = features->inheritedQueries;

    features_obj->features = *features;

    return (PyObject *)features_obj;
}

PyObject *create_phy_dev_surf_caps_khr_obj(const VkSurfaceCapabilitiesKHR *caps)
{
    vk_surface_caps_khr *caps_obj = PyObject_NEW(vk_surface_caps_khr, &vk_surface_caps_khr_type);

    caps_obj->min_image_count = caps->minImageCount;
    caps_obj->max_image_count = caps->maxImageCount;

    PyObject* cur_ext_obj = PyTuple_New(2);
    PyTuple_SetItem(cur_ext_obj, 0, PyLong_FromLong(caps->currentExtent.width));
    PyTuple_SetItem(cur_ext_obj, 1, PyLong_FromLong(caps->currentExtent.height));

    caps_obj->current_extent = cur_ext_obj;

    PyObject* min_ext_obj = PyTuple_New(2);
    PyTuple_SetItem(min_ext_obj, 0, PyLong_FromLong(caps->minImageExtent.width));
    PyTuple_SetItem(min_ext_obj, 1, PyLong_FromLong(caps->minImageExtent.height));

    caps_obj->min_image_extent = min_ext_obj;

    PyObject* max_ext_obj = PyTuple_New(2);
    PyTuple_SetItem(max_ext_obj, 0, PyLong_FromLong(caps->maxImageExtent.width));
    PyTuple_SetItem(max_ext_obj, 1, PyLong_FromLong(caps->maxImageExtent.height));

    caps_obj->max_image_extent = max_ext_obj;

    caps_obj->max_image_array_layers = caps->maxImageArrayLayers;
    caps_obj->supported_transforms = caps->supportedTransforms;
    caps_obj->current_transform = caps->currentTransform;
    caps_obj->supported_composite_alpha = caps->supportedCompositeAlpha;
    caps_obj->supported_usage_flags = caps->supportedUsageFlags;

    caps_obj->caps = *caps;
    
    return (PyObject *)caps_obj;
}

PyObject *vk_phy_dev_get_features(PyObject *self)
{
    DEBUG_LOG("vk_phy_dev_get_features\n");

    vk_phy_dev *phy_dev_obj = (vk_phy_dev *)self;

    VkPhysicalDeviceFeatures features;
    vkGetPhysicalDeviceFeatures(phy_dev_obj->phy_dev, &features);

    return create_phy_dev_features_obj(&features);
}

PyObject *vk_phy_dev_get_props(PyObject *self, PyObject *args)
{
    DEBUG_LOG("vk_phy_dev_get_props\n");

    VkPhysicalDeviceProperties dev_props;
    vkGetPhysicalDeviceProperties(((vk_phy_dev *)self)->phy_dev, &dev_props);

    vk_phy_dev_props *dev_props_obj = PyObject_NEW(vk_phy_dev_props, &vk_phy_dev_props_type);
    dev_props_obj->api_version = dev_props.apiVersion;
    dev_props_obj->driver_version = dev_props.driverVersion;
    dev_props_obj->vendor_id = dev_props.vendorID;
    dev_props_obj->device_id = dev_props.deviceID;
    dev_props_obj->device_type = dev_props.deviceType;
    dev_props_obj->device_name = PyUnicode_FromFormat("%s", dev_props.deviceName);

    PyObject *pipeline_cache_uuid_obj = PyList_New(VK_UUID_SIZE);

    for (uint32_t pc_uuid_idx = 0; pc_uuid_idx < VK_UUID_SIZE; ++pc_uuid_idx)
    {
        PyList_SetItem(pipeline_cache_uuid_obj, pc_uuid_idx, PyLong_FromLong(dev_props.pipelineCacheUUID[pc_uuid_idx]));
    }

    dev_props_obj->pipeline_cache_uuid = pipeline_cache_uuid_obj;
    dev_props_obj->limits = create_phy_dev_limits_obj(&dev_props.limits);
    dev_props_obj->sparse_properties = create_phy_dev_sparse_props_obj(&dev_props.sparseProperties);

    dev_props_obj->props = dev_props;

    return (PyObject *)dev_props_obj;
}

PyObject *vk_phy_dev_get_mem_props(PyObject *self, PyObject *args)
{
    DEBUG_LOG("vk_phy_dev_get_mem_props\n");

    VkPhysicalDeviceMemoryProperties mem_props;
    vkGetPhysicalDeviceMemoryProperties(((vk_phy_dev *)self)->phy_dev, &mem_props);

    PyObject *mem_types_list = PyList_New(mem_props.memoryTypeCount);

    for (uint32_t mem_type_idx = 0; mem_type_idx < mem_props.memoryTypeCount; ++mem_type_idx)
    {
        vk_mem_type *mem_type = PyObject_NEW(vk_mem_type, &vk_mem_type_type);
        mem_type->heap_index = mem_props.memoryTypes[mem_type_idx].heapIndex;
        mem_type->property_flags = mem_props.memoryTypes[mem_type_idx].propertyFlags;

        PyList_SetItem(mem_types_list, mem_type_idx, (PyObject *)mem_type);
    }

    PyObject *mem_heaps_list = PyList_New(mem_props.memoryHeapCount);

    for (uint32_t mem_heap_idx = 0; mem_heap_idx < mem_props.memoryHeapCount; ++mem_heap_idx)
    {
        vk_mem_heap *mem_heap = PyObject_NEW(vk_mem_heap, &vk_mem_heap_type);
        mem_heap->size = mem_props.memoryHeaps[mem_heap_idx].size;
        mem_heap->flags = mem_props.memoryHeaps[mem_heap_idx].flags;

        PyList_SetItem(mem_heaps_list, mem_heap_idx, (PyObject *)mem_heap);
    }

    vk_phy_dev_mem_props *mem_props_obj = PyObject_NEW(vk_phy_dev_mem_props, &vk_phy_dev_mem_props_type);
    mem_props_obj->types = mem_types_list;
    mem_props_obj->heaps = mem_heaps_list;
    mem_props_obj->props = mem_props;

    return (PyObject *)mem_props_obj;
}

PyObject *vk_phy_dev_get_surface_caps_khr(PyObject *self, PyObject *args)
{
    DEBUG_LOG("vk_phy_dev_get_surface_caps_khr\n");

    PyObject *surf_obj = NULL;

    PyArg_Parse(args, "O", &surf_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    VkSurfaceCapabilitiesKHR caps;
    VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(((vk_phy_dev *)self)->phy_dev, ((vk_surface *)surf_obj)->surface, &caps);

    PyObject *surface_caps_obj = create_phy_dev_surf_caps_khr_obj(&caps);

    PyObject *return_obj = PyTuple_New(2);
    PyTuple_SetItem(return_obj, 0, surface_caps_obj);
    PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

    return return_obj;
}

PyObject *vk_phy_dev_create_dev(vk_phy_dev *self, PyObject *args)
{
    DEBUG_LOG("vk_phy_dev_create_dev\n");

    PyObject *dev_ci_obj = NULL;

    PyArg_Parse(args, "O", &dev_ci_obj);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    if (PyObject_TypeCheck(dev_ci_obj, &vk_dev_ci_type) == 0)
    {
        PyErr_SetString(PyExc_TypeError, "Please pass object of vulkan.device_create_info");
        goto shutdown;
    }

    vk_dev_ci *ci_obj = (vk_dev_ci *)dev_ci_obj;

    vk_dev *dev = PyObject_NEW(vk_dev, &vk_dev_type);

    VkResult result = vkCreateDevice(((vk_phy_dev *)self)->phy_dev, &ci_obj->ci, NULL, &dev->device);

    PyObject *return_obj = PyTuple_New(2);
    PyTuple_SetItem(return_obj, 0, (PyObject *)dev);
    PyTuple_SetItem(return_obj, 1, PyLong_FromLong(result));

    return return_obj;

shutdown:
    return NULL;
}

PyObject *vk_phy_dev_destroy_dev(PyObject *self, PyObject *args)
{
    DEBUG_LOG("vk_phy_dev_destroy_dev\n");
    PyObject *dev = NULL;

    PyArg_Parse(args, "O", &dev);
    if (PyErr_Occurred())
    {
        return NULL;
    }

    if (PyObject_TypeCheck(dev, &vk_dev_type) == 0)
    {
        PyErr_SetString(PyExc_TypeError, "Please pass object of vulkan.device");
    }

    if (((vk_dev *)dev)->device != VK_NULL_HANDLE)
    {
        DEBUG_LOG("destroying device\n");
        vkDestroyDevice(((vk_dev *)dev)->device, NULL);
    }

    Py_XDECREF(dev);

    return Py_None;
}

void vk_phy_dev_dealloc(PyObject *self)
{
    DEBUG_LOG("vk_phy_dev_dealloc\n");
    Py_TYPE(self)->tp_free(self);
}

PyMethodDef vk_phy_dev_methods[] = {
    {"get_features", (PyCFunction)vk_phy_dev_get_features, METH_NOARGS, NULL},
    {"get_properties", (PyCFunction)vk_phy_dev_get_props, METH_NOARGS, NULL},
    {"get_memory_properties", (PyCFunction)vk_phy_dev_get_mem_props, METH_NOARGS, NULL},
    {"get_surface_capabilities_khr", (PyCFunction)vk_phy_dev_get_surface_caps_khr, METH_O, NULL},
    {"create_device", (PyCFunction)vk_phy_dev_create_dev, METH_O, NULL},
    {"destroy_device", (PyCFunction)vk_phy_dev_destroy_dev, METH_O, NULL},
    {NULL},
};

PyTypeObject vk_phy_dev_type = {
    PyVarObject_HEAD_INIT(NULL, 0)
        .tp_name = "vulkan.physical_device",
    .tp_basicsize = sizeof(vk_phy_dev),
    .tp_doc = PyDoc_STR("Vulkan Physical Device Docs"),
    .tp_methods = vk_phy_dev_methods,
    .tp_dealloc = vk_phy_dev_dealloc,
};

PyObject *add_vk_phy_dev_to_module(PyObject *mod)
{
    DEBUG_LOG("adding physical device object\n");

    if (PyType_Ready(&vk_phy_dev_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not ready physical_device type");

        goto shutdown;
    }

    Py_INCREF(&vk_phy_dev_type);

    if (PyModule_AddObject(mod, "physical_device", (PyObject *)&vk_phy_dev_type) < 0)
    {
        PyErr_SetString(PyExc_TypeError, "Could not add physical_device type to module");
        goto shutdown;
    }

    return mod;

shutdown:
    Py_XDECREF(&vk_phy_dev_type);

    return NULL;
}