import pyvk.vulkan as vk

import sys

from enum import Enum


class InstanceLayerNames(Enum):
    pass


class InstanceExtensionNames(Enum):
    KHR_SURFACE_EXTENSION_NAME = 'VK_KHR_surface'
    KHR_WIN32_SURFACE_EXTENSION_NAME = 'VK_KHR_win32_surface'


class DeviceLayerNames(Enum):
    pass


class DeviceExtensionNames(Enum):
    SWAPCHAIN_EXTENSION_NAME = 'VK_KHR_swapchain'


class InstanceCreateFlagBits(Enum):
    NONE = 0x00000000
    INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR = 0x00000001


class Result(Enum):
    SUCCESS = 0
    NOT_READY = 1
    TIMEOUT = 2
    INCOMPLETE = 5
    SUBOPTIMAL_KHR = 1000001003
    ERROR_OUT_OF_HOST_MEMORY = -1
    ERROR_OUT_OF_DEVICE_MEMORY = -2
    ERROR_INITIALIZATION_FAILED = -3
    ERROR_DEVICE_LOST = -4
    ERROR_MEMORY_MAP_FAILED = -5
    ERROR_LAYER_NOT_PRESENT = -6
    ERROR_EXTENSION_NOT_PRESENT = -7
    ERROR_FEATURE_NOT_PRESENT = -8
    ERROR_INCOMPATIBLE_DRIVER = -9
    ERROR_TOO_MANY_OBJECTS = -10
    ERROR_FORMAT_NOT_SUPPORTED = -11
    ERROR_UNKNOWN = -13
    ERROR_SURFACE_LOST_KHR = -1000000000
    ERROR_NATIVE_WINDOW_IN_USE_KHR = -1000000001
    ERROR_OUT_OF_DATE_KHR = -1000001004
    ERROR_VALIDATION_FAILED_EXT = -1000011001
    ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT = -1000255000
    ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS = -1000257000
    ERROR_COMPRESSION_EXHAUSTED_EXT = -1000338000
    ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS_KHR = ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS


class MemoryPropertyFlagBits(Enum):
    DEVICE_LOCAL_BIT = 0x00000001
    HOST_VISIBLE_BIT = 0x00000002
    HOST_COHERENT_BIT = 0x00000004
    HOST_CACHED_BIT = 0x00000008
    LAZILY_ALLOCATED_BIT = 0x00000010
    PROTECTED_BIT = 0x00000020
    DEVICE_COHERENT_BIT_AMD = 0x00000040
    DEVICE_UNCACHED_BIT_AMD = 0x00000080
    RDMA_CAPABLE_BIT_NV = 0x00000100


class MemoryHeapFlagBits(Enum):
    DEVICE_LOCAL_BIT = 0x00000001
    MULTI_INSTANCE_BIT = 0x00000002
    MULTI_INSTANCE_BIT_KHR = MULTI_INSTANCE_BIT


class SampleCountFlagBits(Enum):
    COUNT_1_BIT = 0x00000001
    COUNT_2_BIT = 0x00000002
    COUNT_4_BIT = 0x00000004
    COUNT_8_BIT = 0x00000008
    COUNT_16_BIT = 0x00000010
    COUNT_32_BIT = 0x00000020
    COUNT_64_BIT = 0x00000040


class SurfaceTransformFlagBits(Enum):
    IDENTITY_BIT_KHR = 0x00000001
    ROTATE_90_BIT_KHR = 0x00000002
    ROTATE_180_BIT_KHR = 0x00000004
    ROTATE_270_BIT_KHR = 0x00000008
    HORIZONTAL_MIRROR_BIT_KHR = 0x00000010
    HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR = 0x00000020
    HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR = 0x00000040
    HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR = 0x00000080
    INHERIT_BIT_KHR = 0x00000100


class CompositeAlphFlagBitsKHR(Enum):
    OPAQUE_BIT_KHR = 0x00000001
    PRE_MULTIPLIED_BIT_KHR = 0x00000002
    POST_MULTIPLIED_BIT_KHR = 0x00000004
    INHERIT_BIT_KHR = 0x00000008


class ImageUsageFlagBits(Enum):
    NONE = 0x00000000
    TRANSFER_SRC_BIT = 0x00000001
    TRANSFER_DST_BIT = 0x00000002
    SAMPLED_BIT = 0x00000004
    STORAGE_BIT = 0x00000008
    COLOR_ATTACHMENT_BIT = 0x00000010
    DEPTH_STENCIL_ATTACHMENT_BIT = 0x00000020
    TRANSIENT_ATTACHMENT_BIT = 0x00000040
    INPUT_ATTACHMENT_BIT = 0x00000080
    VIDEO_DECODE_DST_BIT_KHR = 0x00000400
    VIDEO_DECODE_SRC_BIT_KHR = 0x00000800
    VIDEO_DECODE_DPB_BIT_KHR = 0x00001000
    FRAGMENT_DENSITY_MAP_BIT_EXT = 0x00000200
    FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR = 0x00000100
    VIDEO_ENCODE_DST_BIT_KHR = 0x00002000
    VIDEO_ENCODE_SRC_BIT_KHR = 0x00004000
    VIDEO_ENCODE_DPB_BIT_KHR = 0x00008000
    ATTACHMENT_FEEDBACK_LOOP_BIT_EXT = 0x00080000
    INVOCATION_MASK_BIT_HUAWEI = 0x00040000
    SAMPLE_WEIGHT_BIT_QCOM = 0x00100000
    SAMPLE_BLOCK_MATCH_BIT_QCOM = 0x00200000
    SHADING_RATE_IMAGE_BIT_NV = FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR


class FormatFeatureFlagBits(Enum):
    SAMPLED_IMAGE_BIT = 0x00000001
    STORAGE_IMAGE_BIT = 0x00000002
    STORAGE_IMAGE_ATOMIC_BIT = 0x00000004
    UNIFORM_TEXEL_BUFFER_BIT = 0x00000008
    STORAGE_TEXEL_BUFFER_BIT = 0x00000010
    STORAGE_TEXEL_BUFFER_ATOMIC_BIT = 0x00000020
    VERTEX_BUFFER_BIT = 0x00000040
    COLOR_ATTACHMENT_BIT = 0x00000080
    COLOR_ATTACHMENT_BLEND_BIT = 0x00000100
    DEPTH_STENCIL_ATTACHMENT_BIT = 0x00000200
    BLIT_SRC_BIT = 0x00000400
    BLIT_DST_BIT = 0x00000800
    SAMPLED_IMAGE_FILTER_LINEAR_BIT = 0x00001000
    TRANSFER_SRC_BIT = 0x00004000
    TRANSFER_DST_BIT = 0x00008000
    MIDPOINT_CHROMA_SAMPLES_BIT = 0x00020000
    SAMPLED_IMAGE_YCBCR_CONVERSION_LINEAR_FILTER_BIT = 0x00040000
    SAMPLED_IMAGE_YCBCR_CONVERSION_SEPARATE_RECONSTRUCTION_FILTER_BIT = 0x00080000
    SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_BIT = 0x00100000
    SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_FORCEABLE_BIT = 0x00200000
    DISJOINT_BIT = 0x00400000
    COSITED_CHROMA_SAMPLES_BIT = 0x00800000
    SAMPLED_IMAGE_FILTER_MINMAX_BIT = 0x00010000
    VIDEO_DECODE_OUTPUT_BIT_KHR = 0x02000000
    VIDEO_DECODE_DPB_BIT_KHR = 0x04000000
    ACCELERATION_STRUCTURE_VERTEX_BUFFER_BIT_KHR = 0x20000000
    SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT = 0x00002000
    FRAGMENT_DENSITY_MAP_BIT_EXT = 0x01000000
    FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR = 0x40000000
    VIDEO_ENCODE_INPUT_BIT_KHR = 0x08000000
    VIDEO_ENCODE_DPB_BIT_KHR = 0x10000000
    SAMPLED_IMAGE_FILTER_CUBIC_BIT_IMG = SAMPLED_IMAGE_FILTER_CUBIC_BIT_EXT
    TRANSFER_SRC_BIT_KHR = TRANSFER_SRC_BIT
    TRANSFER_DST_BIT_KHR = TRANSFER_DST_BIT
    SAMPLED_IMAGE_FILTER_MINMAX_BIT_EXT = SAMPLED_IMAGE_FILTER_MINMAX_BIT
    MIDPOINT_CHROMA_SAMPLES_BIT_KHR = MIDPOINT_CHROMA_SAMPLES_BIT
    SAMPLED_IMAGE_YCBCR_CONVERSION_LINEAR_FILTER_BIT_KHR = SAMPLED_IMAGE_YCBCR_CONVERSION_LINEAR_FILTER_BIT
    SAMPLED_IMAGE_YCBCR_CONVERSION_SEPARATE_RECONSTRUCTION_FILTER_BIT_KHR = SAMPLED_IMAGE_YCBCR_CONVERSION_SEPARATE_RECONSTRUCTION_FILTER_BIT
    SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_BIT_KHR = SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_BIT
    SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_FORCEABLE_BIT_KHR = SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_FORCEABLE_BIT
    DISJOINT_BIT_KHR = DISJOINT_BIT
    COSITED_CHROMA_SAMPLES_BIT_KHR = COSITED_CHROMA_SAMPLES_BIT


class Format(Enum):
    UNDEFINED = 0
    R4G4_UNORM_PACK8 = 1
    R4G4B4A4_UNORM_PACK16 = 2
    B4G4R4A4_UNORM_PACK16 = 3
    R5G6B5_UNORM_PACK16 = 4
    B5G6R5_UNORM_PACK16 = 5
    R5G5B5A1_UNORM_PACK16 = 6
    B5G5R5A1_UNORM_PACK16 = 7
    A1R5G5B5_UNORM_PACK16 = 8
    R8_UNORM = 9
    R8_SNORM = 10
    R8_USCALED = 11
    R8_SSCALED = 12
    R8_UINT = 13
    R8_SINT = 14
    R8_SRGB = 15
    R8G8_UNORM = 16
    R8G8_SNORM = 17
    R8G8_USCALED = 18
    R8G8_SSCALED = 19
    R8G8_UINT = 20
    R8G8_SINT = 21
    R8G8_SRGB = 22
    R8G8B8_UNORM = 23
    R8G8B8_SNORM = 24
    R8G8B8_USCALED = 25
    R8G8B8_SSCALED = 26
    R8G8B8_UINT = 27
    R8G8B8_SINT = 28
    R8G8B8_SRGB = 29
    B8G8R8_UNORM = 30
    B8G8R8_SNORM = 31
    B8G8R8_USCALED = 32
    B8G8R8_SSCALED = 33
    B8G8R8_UINT = 34
    B8G8R8_SINT = 35
    B8G8R8_SRGB = 36
    R8G8B8A8_UNORM = 37
    R8G8B8A8_SNORM = 38
    R8G8B8A8_USCALED = 39
    R8G8B8A8_SSCALED = 40
    R8G8B8A8_UINT = 41
    R8G8B8A8_SINT = 42
    R8G8B8A8_SRGB = 43
    B8G8R8A8_UNORM = 44
    B8G8R8A8_SNORM = 45
    B8G8R8A8_USCALED = 46
    B8G8R8A8_SSCALED = 47
    B8G8R8A8_UINT = 48
    B8G8R8A8_SINT = 49
    B8G8R8A8_SRGB = 50
    A8B8G8R8_UNORM_PACK32 = 51
    A8B8G8R8_SNORM_PACK32 = 52
    A8B8G8R8_USCALED_PACK32 = 53
    A8B8G8R8_SSCALED_PACK32 = 54
    A8B8G8R8_UINT_PACK32 = 55
    A8B8G8R8_SINT_PACK32 = 56
    A8B8G8R8_SRGB_PACK32 = 57
    A2R10G10B10_UNORM_PACK32 = 58
    A2R10G10B10_SNORM_PACK32 = 59
    A2R10G10B10_USCALED_PACK32 = 60
    A2R10G10B10_SSCALED_PACK32 = 61
    A2R10G10B10_UINT_PACK32 = 62
    A2R10G10B10_SINT_PACK32 = 63
    A2B10G10R10_UNORM_PACK32 = 64
    A2B10G10R10_SNORM_PACK32 = 65
    A2B10G10R10_USCALED_PACK32 = 66
    A2B10G10R10_SSCALED_PACK32 = 67
    A2B10G10R10_UINT_PACK32 = 68
    A2B10G10R10_SINT_PACK32 = 69
    R16_UNORM = 70
    R16_SNORM = 71
    R16_USCALED = 72
    R16_SSCALED = 73
    R16_UINT = 74
    R16_SINT = 75
    R16_SFLOAT = 76
    R16G16_UNORM = 77
    R16G16_SNORM = 78
    R16G16_USCALED = 79
    R16G16_SSCALED = 80
    R16G16_UINT = 81
    R16G16_SINT = 82
    R16G16_SFLOAT = 83
    R16G16B16_UNORM = 84
    R16G16B16_SNORM = 85
    R16G16B16_USCALED = 86
    R16G16B16_SSCALED = 87
    R16G16B16_UINT = 88
    R16G16B16_SINT = 89
    R16G16B16_SFLOAT = 90
    R16G16B16A16_UNORM = 91
    R16G16B16A16_SNORM = 92
    R16G16B16A16_USCALED = 93
    R16G16B16A16_SSCALED = 94
    R16G16B16A16_UINT = 95
    R16G16B16A16_SINT = 96
    R16G16B16A16_SFLOAT = 97
    R32_UINT = 98
    R32_SINT = 99
    R32_SFLOAT = 100
    R32G32_UINT = 101
    R32G32_SINT = 102
    R32G32_SFLOAT = 103
    R32G32B32_UINT = 104
    R32G32B32_SINT = 105
    R32G32B32_SFLOAT = 106
    R32G32B32A32_UINT = 107
    R32G32B32A32_SINT = 108
    R32G32B32A32_SFLOAT = 109
    R64_UINT = 110
    R64_SINT = 111
    R64_SFLOAT = 112
    R64G64_UINT = 113
    R64G64_SINT = 114
    R64G64_SFLOAT = 115
    R64G64B64_UINT = 116
    R64G64B64_SINT = 117
    R64G64B64_SFLOAT = 118
    R64G64B64A64_UINT = 119
    R64G64B64A64_SINT = 120
    R64G64B64A64_SFLOAT = 121
    B10G11R11_UFLOAT_PACK32 = 122
    E5B9G9R9_UFLOAT_PACK32 = 123
    D16_UNORM = 124
    X8_D24_UNORM_PACK32 = 125
    D32_SFLOAT = 126
    S8_UINT = 127
    D16_UNORM_S8_UINT = 128
    D24_UNORM_S8_UINT = 129
    D32_SFLOAT_S8_UINT = 130
    BC1_RGB_UNORM_BLOCK = 131
    BC1_RGB_SRGB_BLOCK = 132
    BC1_RGBA_UNORM_BLOCK = 133
    BC1_RGBA_SRGB_BLOCK = 134
    BC2_UNORM_BLOCK = 135
    BC2_SRGB_BLOCK = 136
    BC3_UNORM_BLOCK = 137
    BC3_SRGB_BLOCK = 138
    BC4_UNORM_BLOCK = 139
    BC4_SNORM_BLOCK = 140
    BC5_UNORM_BLOCK = 141
    BC5_SNORM_BLOCK = 142
    BC6H_UFLOAT_BLOCK = 143
    BC6H_SFLOAT_BLOCK = 144
    BC7_UNORM_BLOCK = 145
    BC7_SRGB_BLOCK = 146
    ETC2_R8G8B8_UNORM_BLOCK = 147
    ETC2_R8G8B8_SRGB_BLOCK = 148
    ETC2_R8G8B8A1_UNORM_BLOCK = 149
    ETC2_R8G8B8A1_SRGB_BLOCK = 150
    ETC2_R8G8B8A8_UNORM_BLOCK = 151
    ETC2_R8G8B8A8_SRGB_BLOCK = 152
    EAC_R11_UNORM_BLOCK = 153
    EAC_R11_SNORM_BLOCK = 154
    EAC_R11G11_UNORM_BLOCK = 155
    EAC_R11G11_SNORM_BLOCK = 156
    ASTC_4x4_UNORM_BLOCK = 157
    ASTC_4x4_SRGB_BLOCK = 158
    ASTC_5x4_UNORM_BLOCK = 159
    ASTC_5x4_SRGB_BLOCK = 160
    ASTC_5x5_UNORM_BLOCK = 161
    ASTC_5x5_SRGB_BLOCK = 162
    ASTC_6x5_UNORM_BLOCK = 163
    ASTC_6x5_SRGB_BLOCK = 164
    ASTC_6x6_UNORM_BLOCK = 165
    ASTC_6x6_SRGB_BLOCK = 166
    ASTC_8x5_UNORM_BLOCK = 167
    ASTC_8x5_SRGB_BLOCK = 168
    ASTC_8x6_UNORM_BLOCK = 169
    ASTC_8x6_SRGB_BLOCK = 170
    ASTC_8x8_UNORM_BLOCK = 171
    ASTC_8x8_SRGB_BLOCK = 172
    ASTC_10x5_UNORM_BLOCK = 173
    ASTC_10x5_SRGB_BLOCK = 174
    ASTC_10x6_UNORM_BLOCK = 175
    ASTC_10x6_SRGB_BLOCK = 176
    ASTC_10x8_UNORM_BLOCK = 177
    ASTC_10x8_SRGB_BLOCK = 178
    ASTC_10x10_UNORM_BLOCK = 179
    ASTC_10x10_SRGB_BLOCK = 180
    ASTC_12x10_UNORM_BLOCK = 181
    ASTC_12x10_SRGB_BLOCK = 182
    ASTC_12x12_UNORM_BLOCK = 183
    ASTC_12x12_SRGB_BLOCK = 184
    G8B8G8R8_422_UNORM = 1000156000
    B8G8R8G8_422_UNORM = 1000156001
    G8_B8_R8_3PLANE_420_UNORM = 1000156002
    G8_B8R8_2PLANE_420_UNORM = 1000156003
    G8_B8_R8_3PLANE_422_UNORM = 1000156004
    G8_B8R8_2PLANE_422_UNORM = 1000156005
    G8_B8_R8_3PLANE_444_UNORM = 1000156006
    R10X6_UNORM_PACK16 = 1000156007
    R10X6G10X6_UNORM_2PACK16 = 1000156008
    R10X6G10X6B10X6A10X6_UNORM_4PACK16 = 1000156009
    G10X6B10X6G10X6R10X6_422_UNORM_4PACK16 = 1000156010
    B10X6G10X6R10X6G10X6_422_UNORM_4PACK16 = 1000156011
    G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16 = 1000156012
    G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16 = 1000156013
    G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16 = 1000156014
    G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16 = 1000156015
    G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16 = 1000156016
    R12X4_UNORM_PACK16 = 1000156017
    R12X4G12X4_UNORM_2PACK16 = 1000156018
    R12X4G12X4B12X4A12X4_UNORM_4PACK16 = 1000156019
    G12X4B12X4G12X4R12X4_422_UNORM_4PACK16 = 1000156020
    B12X4G12X4R12X4G12X4_422_UNORM_4PACK16 = 1000156021
    G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16 = 1000156022
    G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16 = 1000156023
    G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16 = 1000156024
    G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16 = 1000156025
    G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16 = 1000156026
    G16B16G16R16_422_UNORM = 1000156027
    B16G16R16G16_422_UNORM = 1000156028
    G16_B16_R16_3PLANE_420_UNORM = 1000156029
    G16_B16R16_2PLANE_420_UNORM = 1000156030
    G16_B16_R16_3PLANE_422_UNORM = 1000156031
    G16_B16R16_2PLANE_422_UNORM = 1000156032
    G16_B16_R16_3PLANE_444_UNORM = 1000156033
    G8_B8R8_2PLANE_444_UNORM = 1000330000
    G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16 = 1000330001
    G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16 = 1000330002
    G16_B16R16_2PLANE_444_UNORM = 1000330003
    A4R4G4B4_UNORM_PACK16 = 1000340000
    A4B4G4R4_UNORM_PACK16 = 1000340001
    ASTC_4x4_SFLOAT_BLOCK = 1000066000
    ASTC_5x4_SFLOAT_BLOCK = 1000066001
    ASTC_5x5_SFLOAT_BLOCK = 1000066002
    ASTC_6x5_SFLOAT_BLOCK = 1000066003
    ASTC_6x6_SFLOAT_BLOCK = 1000066004
    ASTC_8x5_SFLOAT_BLOCK = 1000066005
    ASTC_8x6_SFLOAT_BLOCK = 1000066006
    ASTC_8x8_SFLOAT_BLOCK = 1000066007
    ASTC_10x5_SFLOAT_BLOCK = 1000066008
    ASTC_10x6_SFLOAT_BLOCK = 1000066009
    ASTC_10x8_SFLOAT_BLOCK = 1000066010
    ASTC_10x10_SFLOAT_BLOCK = 1000066011
    ASTC_12x10_SFLOAT_BLOCK = 1000066012
    ASTC_12x12_SFLOAT_BLOCK = 1000066013
    PVRTC1_2BPP_UNORM_BLOCK_IMG = 1000054000
    PVRTC1_4BPP_UNORM_BLOCK_IMG = 1000054001
    PVRTC2_2BPP_UNORM_BLOCK_IMG = 1000054002
    PVRTC2_4BPP_UNORM_BLOCK_IMG = 1000054003
    PVRTC1_2BPP_SRGB_BLOCK_IMG = 1000054004
    PVRTC1_4BPP_SRGB_BLOCK_IMG = 1000054005
    PVRTC2_2BPP_SRGB_BLOCK_IMG = 1000054006
    PVRTC2_4BPP_SRGB_BLOCK_IMG = 1000054007
    R16G16_S10_5_NV = 1000464000
    ASTC_4x4_SFLOAT_BLOCK_EXT = ASTC_4x4_SFLOAT_BLOCK
    ASTC_5x4_SFLOAT_BLOCK_EXT = ASTC_5x4_SFLOAT_BLOCK
    ASTC_5x5_SFLOAT_BLOCK_EXT = ASTC_5x5_SFLOAT_BLOCK
    ASTC_6x5_SFLOAT_BLOCK_EXT = ASTC_6x5_SFLOAT_BLOCK
    ASTC_6x6_SFLOAT_BLOCK_EXT = ASTC_6x6_SFLOAT_BLOCK
    ASTC_8x5_SFLOAT_BLOCK_EXT = ASTC_8x5_SFLOAT_BLOCK
    ASTC_8x6_SFLOAT_BLOCK_EXT = ASTC_8x6_SFLOAT_BLOCK
    ASTC_8x8_SFLOAT_BLOCK_EXT = ASTC_8x8_SFLOAT_BLOCK
    ASTC_10x5_SFLOAT_BLOCK_EXT = ASTC_10x5_SFLOAT_BLOCK
    ASTC_10x6_SFLOAT_BLOCK_EXT = ASTC_10x6_SFLOAT_BLOCK
    ASTC_10x8_SFLOAT_BLOCK_EXT = ASTC_10x8_SFLOAT_BLOCK
    ASTC_10x10_SFLOAT_BLOCK_EXT = ASTC_10x10_SFLOAT_BLOCK
    ASTC_12x10_SFLOAT_BLOCK_EXT = ASTC_12x10_SFLOAT_BLOCK
    ASTC_12x12_SFLOAT_BLOCK_EXT = ASTC_12x12_SFLOAT_BLOCK
    G8B8G8R8_422_UNORM_KHR = G8B8G8R8_422_UNORM
    B8G8R8G8_422_UNORM_KHR = B8G8R8G8_422_UNORM
    G8_B8_R8_3PLANE_420_UNORM_KHR = G8_B8_R8_3PLANE_420_UNORM
    G8_B8R8_2PLANE_420_UNORM_KHR = G8_B8R8_2PLANE_420_UNORM
    G8_B8_R8_3PLANE_422_UNORM_KHR = G8_B8_R8_3PLANE_422_UNORM
    G8_B8R8_2PLANE_422_UNORM_KHR = G8_B8R8_2PLANE_422_UNORM
    G8_B8_R8_3PLANE_444_UNORM_KHR = G8_B8_R8_3PLANE_444_UNORM
    R10X6_UNORM_PACK16_KHR = R10X6_UNORM_PACK16
    R10X6G10X6_UNORM_2PACK16_KHR = R10X6G10X6_UNORM_2PACK16
    R10X6G10X6B10X6A10X6_UNORM_4PACK16_KHR = R10X6G10X6B10X6A10X6_UNORM_4PACK16
    G10X6B10X6G10X6R10X6_422_UNORM_4PACK16_KHR = G10X6B10X6G10X6R10X6_422_UNORM_4PACK16
    B10X6G10X6R10X6G10X6_422_UNORM_4PACK16_KHR = B10X6G10X6R10X6G10X6_422_UNORM_4PACK16
    G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16_KHR = G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16
    G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16_KHR = G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16
    G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16_KHR = G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16
    G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16_KHR = G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16
    G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16_KHR = G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16
    R12X4_UNORM_PACK16_KHR = R12X4_UNORM_PACK16
    R12X4G12X4_UNORM_2PACK16_KHR = R12X4G12X4_UNORM_2PACK16
    R12X4G12X4B12X4A12X4_UNORM_4PACK16_KHR = R12X4G12X4B12X4A12X4_UNORM_4PACK16
    G12X4B12X4G12X4R12X4_422_UNORM_4PACK16_KHR = G12X4B12X4G12X4R12X4_422_UNORM_4PACK16
    B12X4G12X4R12X4G12X4_422_UNORM_4PACK16_KHR = B12X4G12X4R12X4G12X4_422_UNORM_4PACK16
    G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16_KHR = G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16
    G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16_KHR = G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16
    G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16_KHR = G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16
    G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16_KHR = G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16
    G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16_KHR = G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16
    G16B16G16R16_422_UNORM_KHR = G16B16G16R16_422_UNORM
    B16G16R16G16_422_UNORM_KHR = B16G16R16G16_422_UNORM
    G16_B16_R16_3PLANE_420_UNORM_KHR = G16_B16_R16_3PLANE_420_UNORM
    G16_B16R16_2PLANE_420_UNORM_KHR = G16_B16R16_2PLANE_420_UNORM
    G16_B16_R16_3PLANE_422_UNORM_KHR = G16_B16_R16_3PLANE_422_UNORM
    G16_B16R16_2PLANE_422_UNORM_KHR = G16_B16R16_2PLANE_422_UNORM
    G16_B16_R16_3PLANE_444_UNORM_KHR = G16_B16_R16_3PLANE_444_UNORM
    G8_B8R8_2PLANE_444_UNORM_EXT = G8_B8R8_2PLANE_444_UNORM
    G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16_EXT = G10X6_B10X6R10X6_2PLANE_444_UNORM_3PACK16
    G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16_EXT = G12X4_B12X4R12X4_2PLANE_444_UNORM_3PACK16
    G16_B16R16_2PLANE_444_UNORM_EXT = G16_B16R16_2PLANE_444_UNORM
    A4R4G4B4_UNORM_PACK16_EXT = A4R4G4B4_UNORM_PACK16
    A4B4G4R4_UNORM_PACK16_EXT = A4B4G4R4_UNORM_PACK16


class ColorSpace(Enum):
    SRGB_NONLINEAR_KHR = 0
    DISPLAY_P3_NONLINEAR_EXT = 1000104001
    EXTENDED_SRGB_LINEAR_EXT = 1000104002
    DISPLAY_P3_LINEAR_EXT = 1000104003
    DCI_P3_NONLINEAR_EXT = 1000104004
    BT709_LINEAR_EXT = 1000104005
    BT709_NONLINEAR_EXT = 1000104006
    BT2020_LINEAR_EXT = 1000104007
    HDR10_ST2084_EXT = 1000104008
    DOLBYVISION_EXT = 1000104009
    HDR10_HLG_EXT = 1000104010
    ADOBERGB_LINEAR_EXT = 1000104011
    ADOBERGB_NONLINEAR_EXT = 1000104012
    PASS_THROUGH_EXT = 1000104013
    EXTENDED_SRGB_NONLINEAR_EXT = 1000104014
    DISPLAY_NATIVE_AMD = 1000213000
    DCI_P3_LINEAR_EXT = DISPLAY_P3_LINEAR_EXT


class PresentModeKHR(Enum):
    IMMEDIATE_KHR = 0
    MAILBOX_KHR = 1
    FIFO_KHR = 2
    FIFO_RELAXED_KHR = 3
    SHARED_DEMAND_REFRESH_KHR = 1000111000
    SHARED_CONTINUOUS_REFRESH_KHR = 1000111001


class QueueFlagBits(Enum):
    GRAPHICS_BIT = 0x00000001
    COMPUTE_BIT = 0x00000002
    TRANSFER_BIT = 0x00000004
    SPARSE_BINDING_BIT = 0x00000008
    PROTECTED_BIT = 0x00000010
    VIDEO_DECODE_BIT_KHR = 0x00000020
    VIDEO_ENCODE_BIT_KHR = 0x00000040
    OPTICAL_FLOW_BIT_NV = 0x00000100


class DeviceQueueCreateFlagBits(Enum):
    NONE = 0x00000000
    PROTECTED_BIT = 0x00000001


class Win32SurfaceCreateFlagsKHR(Enum):
    NONE = 0x00000000


class DeviceCreateFlags(Enum):
    NONE = 0x00000000


class SemaphoreCreateFlags(Enum):
    NONE = 0x00000000


class FenceCreateFlagBits(Enum):
    NONE = 0x00000000
    SIGNALED_BIT = 0x00000001


class SharingMode(Enum):
    EXCLUSIVE = 0
    CONCURRENT = 1


class SwapchainCreateFlagBitsKHR(Enum):
    NONE = 0x00000000
    SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR = 0x00000001
    PROTECTED_BIT_KHR = 0x00000002
    MUTABLE_FORMAT_BIT_KHR = 0x00000004
    DEFERRED_MEMORY_ALLOCATION_BIT_EXT = 0x00000008


class CommandPoolCreateFlagBits(Enum):
    NONE = 0x00000000
    TRANSIENT_BIT = 0x00000001
    RESET_COMMAND_BUFFER_BIT = 0x00000002
    PROTECTED_BIT = 0x00000004


class CommandBufferLevel(Enum):
    PRIMARY = 0
    SECONDARY = 1


class ImageCreateFlagBits(Enum):
    NONE = 0x00000000
    SPARSE_BINDING_BIT = 0x00000001
    SPARSE_RESIDENCY_BIT = 0x00000002
    SPARSE_ALIASED_BIT = 0x00000004
    MUTABLE_FORMAT_BIT = 0x00000008
    CUBE_COMPATIBLE_BIT = 0x00000010
    ALIAS_BIT = 0x00000400
    SPLIT_INSTANCE_BIND_REGIONS_BIT = 0x00000040
    TWO_2D_ARRAY_COMPATIBLE_BIT = 0x00000020
    BLOCK_TEXEL_VIEW_COMPATIBLE_BIT = 0x00000080
    EXTENDED_USAGE_BIT = 0x00000100
    PROTECTED_BIT = 0x00000800
    DISJOINT_BIT = 0x00000200
    CORNER_SAMPLED_BIT_NV = 0x00002000
    SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT = 0x00001000
    SUBSAMPLED_BIT_EXT = 0x00004000
    DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT = 0x00010000
    MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_BIT_EXT = 0x00040000
    TWO_2D_VIEW_COMPATIBLE_BIT_EXT = 0x00020000
    FRAGMENT_DENSITY_MAP_OFFSET_BIT_QCOM = 0x00008000
    SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR = SPLIT_INSTANCE_BIND_REGIONS_BIT
    TWO_2D_ARRAY_COMPATIBLE_BIT_KHR = TWO_2D_ARRAY_COMPATIBLE_BIT
    BLOCK_TEXEL_VIEW_COMPATIBLE_BIT_KHR = BLOCK_TEXEL_VIEW_COMPATIBLE_BIT
    EXTENDED_USAGE_BIT_KHR = EXTENDED_USAGE_BIT
    DISJOINT_BIT_KHR = DISJOINT_BIT
    ALIAS_BIT_KHR = ALIAS_BIT


class ImageType(Enum):
    ONE_1D = 0
    TWO_2D = 1
    THREE_3D = 2


class ImageViewType(Enum):
    ONE_1D = 0
    TWO_2D = 1
    THREE_3D = 2
    CUBE = 3
    ONE_1D_ARRAY = 4
    TWO_2D_ARRAY = 5
    CUBE_ARRAY = 6


class ImageTiling(Enum):
    OPTIMAL = 0
    LINEAR = 1
    DRM_FORMAT_MODIFIER_EXT = 1000158000


class ImageLayout(Enum):
    UNDEFINED = 0
    GENERAL = 1
    COLOR_ATTACHMENT_OPTIMAL = 2
    DEPTH_STENCIL_ATTACHMENT_OPTIMAL = 3
    DEPTH_STENCIL_READ_ONLY_OPTIMAL = 4
    SHADER_READ_ONLY_OPTIMAL = 5
    TRANSFER_SRC_OPTIMAL = 6
    TRANSFER_DST_OPTIMAL = 7
    PREINITIALIZED = 8
    DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL = 1000117000
    DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL = 1000117001
    DEPTH_ATTACHMENT_OPTIMAL = 1000241000
    DEPTH_READ_ONLY_OPTIMAL = 1000241001
    STENCIL_ATTACHMENT_OPTIMAL = 1000241002
    STENCIL_READ_ONLY_OPTIMAL = 1000241003
    READ_ONLY_OPTIMAL = 1000314000
    ATTACHMENT_OPTIMAL = 1000314001
    PRESENT_SRC_KHR = 1000001002
    VIDEO_DECODE_DST_KHR = 1000024000
    VIDEO_DECODE_SRC_KHR = 1000024001
    VIDEO_DECODE_DPB_KHR = 1000024002
    SHARED_PRESENT_KHR = 1000111000
    FRAGMENT_DENSITY_MAP_OPTIMAL_EXT = 1000218000
    FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR = 1000164003
    VIDEO_ENCODE_DST_KHR = 1000299000
    VIDEO_ENCODE_SRC_KHR = 1000299001
    VIDEO_ENCODE_DPB_KHR = 1000299002
    ATTACHMENT_FEEDBACK_LOOP_OPTIMAL_EXT = 1000339000
    DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL_KHR = DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL
    DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL_KHR = DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL
    SHADING_RATE_OPTIMAL_NV = FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR
    DEPTH_ATTACHMENT_OPTIMAL_KHR = DEPTH_ATTACHMENT_OPTIMAL
    DEPTH_READ_ONLY_OPTIMAL_KHR = DEPTH_READ_ONLY_OPTIMAL
    STENCIL_ATTACHMENT_OPTIMAL_KHR = STENCIL_ATTACHMENT_OPTIMAL
    STENCIL_READ_ONLY_OPTIMAL_KHR = STENCIL_READ_ONLY_OPTIMAL
    READ_ONLY_OPTIMAL_KHR = READ_ONLY_OPTIMAL
    ATTACHMENT_OPTIMAL_KHR = ATTACHMENT_OPTIMAL


class ImageAspectFlagBits(Enum):
    COLOR_BIT = 0x00000001
    DEPTH_BIT = 0x00000002
    STENCIL_BIT = 0x00000004
    METADATA_BIT = 0x00000008
    PLANE_0_BIT = 0x00000010
    PLANE_1_BIT = 0x00000020
    PLANE_2_BIT = 0x00000040
    NONE = 0
    MEMORY_PLANE_0_BIT_EXT = 0x00000080
    MEMORY_PLANE_1_BIT_EXT = 0x00000100
    MEMORY_PLANE_2_BIT_EXT = 0x00000200
    MEMORY_PLANE_3_BIT_EXT = 0x00000400
    PLANE_0_BIT_KHR = PLANE_0_BIT
    PLANE_1_BIT_KHR = PLANE_1_BIT
    PLANE_2_BIT_KHR = PLANE_2_BIT
    NONE_KHR = NONE


class AccessFlagBits(Enum):
    INDIRECT_COMMAND_READ_BIT = 0x00000001
    INDEX_READ_BIT = 0x00000002
    VERTEX_ATTRIBUTE_READ_BIT = 0x00000004
    UNIFORM_READ_BIT = 0x00000008
    INPUT_ATTACHMENT_READ_BIT = 0x00000010
    SHADER_READ_BIT = 0x00000020
    SHADER_WRITE_BIT = 0x00000040
    COLOR_ATTACHMENT_READ_BIT = 0x00000080
    COLOR_ATTACHMENT_WRITE_BIT = 0x00000100
    DEPTH_STENCIL_ATTACHMENT_READ_BIT = 0x00000200
    DEPTH_STENCIL_ATTACHMENT_WRITE_BIT = 0x00000400
    TRANSFER_READ_BIT = 0x00000800
    TRANSFER_WRITE_BIT = 0x00001000
    HOST_READ_BIT = 0x00002000
    HOST_WRITE_BIT = 0x00004000
    MEMORY_READ_BIT = 0x00008000
    MEMORY_WRITE_BIT = 0x00010000
    NONE = 0
    TRANSFORM_FEEDBACK_WRITE_BIT_EXT = 0x02000000
    TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT = 0x04000000
    TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT_EXT = 0x08000000
    CONDITIONAL_RENDERING_READ_BIT_EXT = 0x00100000
    COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT = 0x00080000
    ACCELERATION_STRUCTURE_READ_BIT_KHR = 0x00200000
    ACCELERATION_STRUCTURE_WRITE_BIT_KHR = 0x00400000
    FRAGMENT_DENSITY_MAP_READ_BIT_EXT = 0x01000000
    FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT_KHR = 0x00800000
    COMMAND_PREPROCESS_READ_BIT_NV = 0x00020000
    COMMAND_PREPROCESS_WRITE_BIT_NV = 0x00040000
    SHADING_RATE_IMAGE_READ_BIT_NV = FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT_KHR
    ACCELERATION_STRUCTURE_READ_BIT_NV = ACCELERATION_STRUCTURE_READ_BIT_KHR
    ACCELERATION_STRUCTURE_WRITE_BIT_NV = ACCELERATION_STRUCTURE_WRITE_BIT_KHR
    NONE_KHR = NONE


class CommandBufferUsageFlagBits(Enum):
    NONE = 0x00000000
    ONE_TIME_SUBMIT_BIT = 0x00000001
    RENDER_PASS_CONTINUE_BIT = 0x00000002
    SIMULTANEOUS_USE_BIT = 0x00000004


class PipelineStageFlagBits(Enum):
    TOP_OF_PIPE_BIT = 0x00000001
    DRAW_INDIRECT_BIT = 0x00000002
    VERTEX_INPUT_BIT = 0x00000004
    VERTEX_SHADER_BIT = 0x00000008
    TESSELLATION_CONTROL_SHADER_BIT = 0x00000010
    TESSELLATION_EVALUATION_SHADER_BIT = 0x00000020
    GEOMETRY_SHADER_BIT = 0x00000040
    FRAGMENT_SHADER_BIT = 0x00000080
    EARLY_FRAGMENT_TESTS_BIT = 0x00000100
    LATE_FRAGMENT_TESTS_BIT = 0x00000200
    COLOR_ATTACHMENT_OUTPUT_BIT = 0x00000400
    COMPUTE_SHADER_BIT = 0x00000800
    TRANSFER_BIT = 0x00001000
    BOTTOM_OF_PIPE_BIT = 0x00002000
    HOST_BIT = 0x00004000
    ALL_GRAPHICS_BIT = 0x00008000
    ALL_COMMANDS_BIT = 0x00010000
    NONE = 0
    TRANSFORM_FEEDBACK_BIT_EXT = 0x01000000
    CONDITIONAL_RENDERING_BIT_EXT = 0x00040000
    ACCELERATION_STRUCTURE_BUILD_BIT_KHR = 0x02000000
    RAY_TRACING_SHADER_BIT_KHR = 0x00200000
    FRAGMENT_DENSITY_PROCESS_BIT_EXT = 0x00800000
    FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR = 0x00400000
    COMMAND_PREPROCESS_BIT_NV = 0x00020000
    TASK_SHADER_BIT_EXT = 0x00080000
    MESH_SHADER_BIT_EXT = 0x00100000
    SHADING_RATE_IMAGE_BIT_NV = FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR
    RAY_TRACING_SHADER_BIT_NV = RAY_TRACING_SHADER_BIT_KHR
    ACCELERATION_STRUCTURE_BUILD_BIT_NV = ACCELERATION_STRUCTURE_BUILD_BIT_KHR
    TASK_SHADER_BIT_NV = TASK_SHADER_BIT_EXT
    MESH_SHADER_BIT_NV = MESH_SHADER_BIT_EXT
    NONE_KHR = NONE


class DependencyFlagBits(Enum):
    BY_REGION_BIT = 0x00000001
    DEVICE_GROUP_BIT = 0x00000004
    VIEW_LOCAL_BIT = 0x00000002
    FEEDBACK_LOOP_BIT_EXT = 0x00000008
    VIEW_LOCAL_BIT_KHR = VIEW_LOCAL_BIT
    DEVICE_GROUP_BIT_KHR = DEVICE_GROUP_BIT


class ComponentSwizzle(Enum):
    IDENTITY = 0
    ZERO = 1
    ONE = 2
    R = 3
    G = 4
    B = 5
    A = 6


class ImageViewCreateFlagBits(Enum):
    NONE = 0x00000000
    FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT = 0x00000001
    DESCRIPTOR_BUFFER_CAPTURE_REPLAY_BIT_EXT = 0x00000004
    FRAGMENT_DENSITY_MAP_DEFERRED_BIT_EXT = 0x00000002


class Filter(Enum):
    NEAREST = 0
    LINEAR = 1
    CUBIC_EXT = 1000015000
    CUBIC_IMG = CUBIC_EXT


class ApplicationInfo(vk.application_info):
    def __init__(self, p_next=None,
                 app_name='', app_ver=(1, 0, 0, 0),
                 engine_name='', engine_ver=(1, 0, 0, 0)):
        super(ApplicationInfo, self).__init__(p_next=p_next, app_name=app_name, app_ver=app_ver,
                                              engine_name=engine_name, engine_ver=engine_ver)


class InstanceCreateInfo(vk.instance_create_info):
    def __init__(self, p_next=None,
                 flags=InstanceCreateFlagBits.NONE, app_info=None,
                 enabled_layers=[], enabled_extensions=[]):

        enabled_layers_str = []

        for layer in enabled_layers:
            enabled_layers_str.append(layer.value)

        enabled_extensions_str = []

        for ext in enabled_extensions:
            enabled_extensions_str.append(ext.value)

        flags_value = flags.value if isinstance(flags, InstanceCreateFlagBits) else flags

        super(InstanceCreateInfo, self).__init__(p_next,
                                                 flags_value, app_info,
                                                 enabled_layers=enabled_layers_str,
                                                 enabled_extensions=enabled_extensions_str)


class Win32SurfaceCreateInfo(vk.surface_create_info):
    def __init__(self, p_next=None,
                 flags=Win32SurfaceCreateFlagsKHR.NONE, h_wnd=int):

        flags_value = flags.value if isinstance(flags, Win32SurfaceCreateFlagsKHR) else flags

        super(Win32SurfaceCreateInfo, self).__init__(p_next,
                                                     flags_value, h_wnd)


class Instance(object):
    def __init__(self, i=vk.instance):
        self._i = i

    def get_physical_devices(self):
        pds, result = self._i.get_physical_devices()

        ret_pds = [PhysicalDevice(pd) for pd in pds]

        for r in Result:
            if result == r.value:
                return ret_pds, r

        return ret_pds, result

    def create_surface(self, surface_create_info=Win32SurfaceCreateInfo):
        s, result = self._i.create_surface(surface_create_info)
        for r in Result:
            if result == r.value:
                return s, r

        return s, result

    def destroy_surface(self, surface=vk.surface):
        self._i.destroy_surface(surface)


class DeviceQueueCreateInfo(vk.device_queue_create_info):
    def __init__(self, p_next=None,
                 flags=DeviceQueueCreateFlagBits.NONE, queue_family_index=0,
                 queue_count=1, priorities=[1.0]):

        super(DeviceQueueCreateInfo, self).__init__(p_next, flags.value, queue_family_index,
                                                    queue_count, priorities)


class DeviceCreateInfo(vk.device_create_info):
    def __init__(self, p_next=None,
                 flags=DeviceCreateFlags.NONE, queue_create_infos=[],
                 enabled_layers=[], enabled_extensions=[],
                 enabled_features=vk.physical_device_features):

        enabled_layers_str = []

        for layer in enabled_layers:
            enabled_layers_str.append(layer.value)

        enabled_extensions_str = []

        for ext in enabled_extensions:
            enabled_extensions_str.append(ext.value)

        super(DeviceCreateInfo, self).__init__(p_next, flags.value,
                                               queue_create_infos, enabled_layers=enabled_layers_str,
                                               enabled_extensions=enabled_extensions_str,
                                               enabled_features=enabled_features)


class SwapchainCreateInfoKHR(vk.swapchain_create_info):
    def __init__(self, p_next=None, flags=SwapchainCreateFlagBitsKHR.NONE,
                 surface=vk.surface, min_image_count=1, image_format=Format.UNDEFINED, image_color_space=ColorSpace.SRGB_NONLINEAR_KHR,
                 image_extent=(0, 0), image_array_layers=1, image_usage_flags=ImageUsageFlagBits.NONE, image_sharing_mode=SharingMode.EXCLUSIVE,
                 queue_family_indices=[0], pre_transform=SurfaceTransformFlagBits.IDENTITY_BIT_KHR, composite_alpha=CompositeAlphFlagBitsKHR.OPAQUE_BIT_KHR,
                 present_mode=PresentModeKHR.IMMEDIATE_KHR, clipped=True, old_swapchain=vk.swapchain):

        if len(image_extent) != 2:
                raise ValueError(
                    'Please pass a tuple of size 2 for image_extent in pyvk.SwapchainCreateInfo')

        flags_value = flags.value if isinstance(
            flags, SwapchainCreateFlagBitsKHR) else flags
        image_format_value = image_format.value if isinstance(
            image_format, Format) else image_format
        image_color_space_value = image_color_space.value if isinstance(
            image_color_space, ColorSpace) else image_color_space
        image_usage_flags_value = image_usage_flags.value if isinstance(
            image_usage_flags, ImageUsageFlagBits) else image_usage_flags
        image_sharing_mode_value = image_sharing_mode.value if isinstance(
            image_sharing_mode, SharingMode) else image_sharing_mode
        pre_transform_value = pre_transform.value if isinstance(
            pre_transform, SurfaceTransformFlagBits) else pre_transform
        composite_alpha_value = composite_alpha.value if isinstance(
            composite_alpha, CompositeAlphFlagBitsKHR) else composite_alpha
        present_mode_value = present_mode.value if isinstance(
            present_mode, PresentModeKHR) else present_mode

        super(SwapchainCreateInfoKHR, self).__init__(p_next, flags_value, surface, min_image_count,
                                                     image_format_value, image_color_space_value, image_extent, image_array_layers,
                                                     image_usage_flags_value, image_sharing_mode_value, queue_family_indices, pre_transform_value,
                                                     composite_alpha_value, present_mode_value, clipped, old_swapchain)


class CommandPoolCreateInfo(vk.command_pool_create_info):
    def __init__(self, p_next=None, flags=CommandPoolCreateFlagBits.NONE,
                 queue_family_index=0):

        flags_value = flags.value if isinstance(
            flags, CommandPoolCreateFlagBits) else flags

        super(CommandPoolCreateInfo, self).__init__(
            p_next, flags_value, queue_family_index)


class CommandBufferAllocateInfo(vk.command_buffer_allocate_info):
    def __init__(self, command_pool=vk.command_pool, level=CommandBufferLevel.PRIMARY, command_buffer_count=1):
        level_value = level.value if isinstance(
            level, CommandBufferLevel) else level

        super(CommandBufferAllocateInfo, self).__init__(
            command_pool, level_value, command_buffer_count)


class SemaphoreCreateInfo(vk.semaphore_create_info):
    def __init__(self, p_next=None, flags=SemaphoreCreateFlags.NONE):
        flags_value = flags.value if isinstance(
            flags, SemaphoreCreateFlags) else flags

        super(SemaphoreCreateInfo, self).__init__(p_next, flags_value)


class FenceCreateInfo(vk.fence_create_info):
    def __init__(self, p_next=None, flags=FenceCreateFlagBits.NONE):

        flags_value = flags.value if isinstance(
            flags, FenceCreateFlagBits) else flags

        super(FenceCreateInfo, self).__init__(p_next, flags_value)


class ImageSubresourceLayers(vk.image_subresource_layers):
    def __init__(self, aspect_mask=ImageAspectFlagBits.COLOR_BIT, mip_level=0, 
                 base_array_layer=0, layer_count=1):

        aspect_mask_value = aspect_mask.value if isinstance(
            aspect_mask, ImageAspectFlagBits) else aspect_mask
        super(ImageSubresourceLayers, self).__init__(aspect_mask_value, mip_level, 
                                                     base_array_layer, layer_count)


class ImageSubresourceRange(vk.image_subresource_range):
    def __init__(self, aspect_mask=ImageAspectFlagBits.COLOR_BIT, base_mip_level=0, 
                 level_count=1, base_array_layer=0, layer_count=1):

        aspect_mask_value = aspect_mask.value if isinstance(
            aspect_mask, ImageAspectFlagBits) else aspect_mask

        super(ImageSubresourceRange, self).__init__(aspect_mask_value, base_mip_level, 
                                                    level_count, base_array_layer, layer_count)


class ImageMemoryBarrier(vk.image_memory_barrier):
    def __init__(self, p_next=None, src_access_mask=AccessFlagBits.NONE, dst_access_mask=AccessFlagBits.NONE,
                 old_layout=ImageLayout.UNDEFINED, new_layout=ImageLayout.UNDEFINED, src_queue_family_index=0,
                 dst_queue_family_index=0, image=vk.image, subresource_range=ImageSubresourceRange):
        
        src_access_mask_value = src_access_mask.value if isinstance(src_access_mask, AccessFlagBits) else src_access_mask
        dst_access_mask_value = dst_access_mask.value if isinstance(dst_access_mask, AccessFlagBits) else dst_access_mask
        old_layout_value = old_layout.value if isinstance(old_layout, ImageLayout) else old_layout
        new_layout_value = new_layout.value if isinstance(new_layout, ImageLayout) else new_layout

        super(ImageMemoryBarrier, self).__init__(p_next, src_access_mask_value, dst_access_mask_value, old_layout_value, 
                                                new_layout_value, src_queue_family_index, dst_queue_family_index, image, 
                                                subresource_range)



class ImageCreateInfo(vk.image_create_info):
    def __init__(self, p_next=None, flags=ImageCreateFlagBits.NONE, image_type=ImageType.TWO_2D,
                 format=Format.UNDEFINED, extent=(0, 0, 0), mip_levels=1, array_layers=1, 
                 samples=SampleCountFlagBits.COUNT_1_BIT, tiling=ImageTiling.OPTIMAL, 
                 usage=ImageUsageFlagBits.NONE, sharing_mode=SharingMode.EXCLUSIVE,
                 queue_family_indices=[0], initial_layout=ImageLayout.UNDEFINED):

        flags_value = flags.value if isinstance(
            flags, ImageCreateFlagBits) else flags
        image_type_value = image_type.value if isinstance(
            image_type, ImageType) else image_type
        format_value = format.value if isinstance(format, Format) else format
        samples_value = samples.value if isinstance(
            samples, SampleCountFlagBits) else samples
        tiling_value = tiling.value if isinstance(
            tiling, ImageTiling) else tiling
        usage_value = usage.value if isinstance(
            usage, ImageUsageFlagBits) else usage
        sharing_mode_value = sharing_mode.value if isinstance(
            sharing_mode, SharingMode) else sharing_mode
        initial_layout_value = initial_layout.value if isinstance(
            initial_layout, ImageLayout) else initial_layout

        if len(extent) != 3:
            raise ValueError(
                'Please pass a tuple with 3 values for extent in pyvk.ImageCreateInfo')

        super(ImageCreateInfo, self).__init__(p_next, flags_value, image_type_value, 
                                              format_value, extent, mip_levels, array_layers, 
                                              samples_value, tiling_value, usage_value, 
                                              sharing_mode_value, queue_family_indices,
                                              initial_layout_value)


class ComponentMapping(vk.component_mapping):
    def __init__(self, r=0, g=0, b=0, a=0):
        super(ComponentMapping, self).__init__(r, g, b, a)


class ImageViewCreateInfo(vk.image_view_create_info):
    def __init__(self, flags=ImageViewCreateFlagBits.NONE, image=vk.image, view_type=ImageViewType.TWO_2D, 
                 format=Format, components=vk.component_mapping, subresource_range=vk.image_subresource_range):
        
        flags_value = flags.value if isinstance(flags, ImageViewCreateFlagBits) else flags
        view_type_value = view_type.value if isinstance(view_type, ImageViewType) else view_type
        format_value = format.value if isinstance(format, Format) else format

        super(ImageViewCreateInfo, self).__init__(flags_value, image, view_type_value, format_value, 
                                                  components, subresource_range)


class ImageCopy(vk.image_copy):
    def __init__(self, src_subresource_layers=vk.image_subresource_layers, src_offset=(0, 0, 0),
                 dst_subresource_layers=vk.image_subresource_layers, dst_offset=(0, 0, 0), extent=(0, 0, 0)):
        
        if len(src_offset) != 3:
            raise TypeError('Please pass a tuple of length 3 for src_offset in pyvk.ImageCopyr')

        if len(dst_offset) != 3:
            raise TypeError('Please pass a tuple of length 3 for dst_offset in pyvk.ImageCopy')

        if len(extent) != 3:
            raise TypeError('Please pass a tuple of length 3 for extent in pyvk.ImageCopy')

        super(ImageCopy, self).__init__(src_subresource_layers, src_offset, dst_subresource_layers,
                                         dst_offset, extent)

class ImageBlit(vk.image_blit):
    def __init__(self, src_subresrouce=vk.image_subresource_layers, src_offsets=[],
                 dst_subresource=vk.image_subresource_layers, dst_offsets=[]):

        if len(src_offsets) != 2:
            raise ValueError('Please pass a list of 2 tuples of 3 values each for src_offsets in vk.ImageBlit')

        if len(dst_offsets) != 2:
            raise ValueError('Please pass a list of 2 tuples of 3 values each for dst_offsets in vk.ImageBlit')

        super(ImageBlit, self).__init__(src_subresrouce, dst_offsets, dst_subresource, dst_offsets)


class MemoryAllocateInfo(vk.memory_allocate_info):
    def __init__(self, p_next=None, allocation_size=1, memory_type_index=int):

        if allocation_size < 1:
            raise ValueError('Please pass a positive value for allocation_size in pyvk.MemoryAllocateInfo')

        super(MemoryAllocateInfo, self).__init__(p_next, allocation_size, memory_type_index)


class SubmitInfo(vk.submit_info):
    def __init__(self, p_next=None, wait_semaphores=[], wait_dst_stage_masks=[], 
                 command_buffers=[], signal_semaphores=[]):

        wait_dst_stage_masks = [msk.value for msk in wait_dst_stage_masks]
        command_buffers = [cmd_buf._cb for cmd_buf in command_buffers]

        super(SubmitInfo, self).__init__(p_next, wait_semaphores, wait_dst_stage_masks, 
                                         command_buffers, signal_semaphores)
        

class CommandBufferBeginInfo(vk.command_buffer_begin_info):
    def __init__(self, flags=CommandBufferUsageFlagBits.NONE):
        
        flags_value = flags.value if isinstance(flags, CommandBufferUsageFlagBits) else flags

        super(CommandBufferBeginInfo, self).__init__(flags_value)


class PresentInfo(vk.present_info):
    def __init__(self, wait_semaphores=[], swapchains=[], image_indices=[]):
        super(PresentInfo, self).__init__(wait_semaphores, swapchains, image_indices)

    
class Device(object):
    def __init__(self, device=vk.device):
        self._d = device

    def get_queue(self, queue_family_index=0, queue_index=0):
        return Queue(self._d.get_queue(queue_family_index=queue_family_index, queue_index=queue_index))

    def create_swapchain(self, swapchain_create_info=SwapchainCreateInfoKHR):
        sc, result = self._d.create_swapchain(swapchain_create_info)

        for r in Result:
            if result == r.value:
                return sc, r

        return sc, result

    def get_swapchain_images(self, swapchain=vk.swapchain):
        imgs, result = self._d.get_swapchain_images(swapchain)

        for r in Result:
            if result == r.value:
                return imgs, r
            
        return imgs, result

    def destroy_swapchain(self, swapchain=vk.swapchain):
        self._d.destroy_swapchain(swapchain)

    def create_command_pool(self, comamnd_pool_create_info=CommandPoolCreateInfo):
        cp, result = self._d.create_command_pool(comamnd_pool_create_info)

        for r in Result:
            if result == r.value:
                return cp, r

        return cp, result

    def destroy_command_pool(self, command_pool=vk.command_pool):
        self._d.destroy_command_pool(command_pool)

    def allocate_command_buffers(self, command_buffer_allocate_info=CommandBufferAllocateInfo):
        cmd_bufs, result = self._d.allocate_command_buffers(
            command_buffer_allocate_info)

        cmd_bufs = [CommandBuffer(cb) for cb in cmd_bufs]

        for r in Result:
            if result == r.value:
                return cmd_bufs, r

        return cmd_bufs, result

    def free_command_buffers(self, command_pool=vk.command_pool, command_buffers=[]):
        command_buffers = [cmd_buf._cb for cmd_buf in command_buffers]

        self._d.free_command_buffers(command_pool, command_buffers)

    def create_semaphore(self, semaphore_create_info=SemaphoreCreateInfo):
        sem, result = self._d.create_semaphore(semaphore_create_info)

        for r in Result:
            if result == r.value:
                return sem, r

        return sem, result

    def destroy_semaphore(self, semaphore=vk.semaphore):
        self._d.destroy_semaphore(semaphore)

    def create_fence(self, fence_create_info=FenceCreateInfo):
        fence, result = self._d.create_fence(fence_create_info)

        for r in Result:
            if result == r.value:
                return fence, r

        return fence, result

    def reset_fences(self, fences=[]):
        result = self._d.reset_fences(fences)

        for r in Result:
            if result == r.value:
                return r

        return result

    def destroy_fence(self, fence=vk.fence):
        self._d.destroy_fence(fence)

    def create_image(self, image_create_info=ImageCreateInfo):
        image, result = self._d.create_image(image_create_info)

        for r in Result:
            if result == r.value:
                return image, r

        return image, result

    def destroy_image(self, image=vk.image):
        self._d.destroy_image(image)

    def create_image_view(self, image_view_create_info=ImageViewCreateInfo):
        image_view, result = self._d.create_image_view(image_view_create_info)

        for r in Result:
            if result == r.value:
                return image_view, r

        return image_view, result

    def destroy_image_view(self, image_view=vk.image_view):
        self._d.destroy_image_view(image_view)
        
    def get_image_memory_requirements(self, image=vk.image):
        return self._d.get_image_memory_requirements(image)

    def allocate_memory(self, memory_allocate_info=MemoryAllocateInfo):
        m, result = self._d.allocate_memory(memory_allocate_info)

        for r in Result:
            if result == r.value:
                return m, r

        return m, result

    def map_memory(self, memory=vk.device_memory, offset=0, size=1, flags=0):
        if size == 0:
            raise ValueError("Please pass a positive value for size in pyvk.Device.map_memory") 

        mem_id, result = self._d.map_memory(memory, offset, size, flags)

        for r in Result:
            if result == r.value:
                return mem_id, r
            
        return mem_id, result

    def update_host_mapped_data(self, data=None, mem_id=0):
        self._d.update_host_mapped_data(data, mem_id)

    def unmap_memory(self, memory=vk.device_memory):
        self._d.unmap_memory(memory)
    
    def free_memory(self, memory=vk.device_memory):
        self._d.free_memory(memory)


    def bind_image_memory(self, image=vk.image, memory=vk.device_memory, offset=0):
        
        if offset < 0:
            raise ValueError('Please pass a positive value for offset in pyvk.Device.bind_image_memory')

        result = self._d.bind_image_memory(image, memory, offset)

        for r in Result:
            if result == r.value:
                return r

        return result

    def acquire_next_image(self, swapchain=vk.swapchain, timeout=sys.maxsize, semaphore=vk.semaphore, fence=vk.fence):
        image_index, result = self._d.acquire_next_image(swapchain, timeout, semaphore, fence)

        for r in Result:
            if r.value == result:
                return image_index, r
            
        return image_index, result

    def wait_for_fences(self, fences=[], wait_for_all=True, timeout=sys.maxsize):
        result = self._d.wait_for_fences(fences=fences, wait_for_all=wait_for_all, timeout=timeout)

        for r in Result:
            if r.value == result:
                return r

        return result


class PhysicalDevice(object):
    def __init__(self, pd=vk.physical_device):
        self._pd = pd

    def get_features(self):
        return self._pd.get_features()

    def get_properties(self):
        return self._pd.get_properties()

    def get_memory_properties(self):
        return self._pd.get_memory_properties()

    def get_surface_capabilities_khr(self, surface=vk.surface):
        caps, result = self._pd.get_surface_capabilities_khr(surface)

        for r in Result:
            if result == r.value:
                return caps, r

        return caps, result

    def get_surface_formats_khr(self, surface=vk.surface):
        formats, result = self._pd.get_surface_formats_khr(surface)

        for r in Result:
            if result == r.value:
                return formats, r

        return formats, result

    def get_surface_present_modes_khr(self, surface=vk.surface):
        present_modes, result = self._pd.get_surface_present_modes_khr(surface)

        for r in Result:
            if result == r.value:
                return present_modes, r

        return present_modes, result

    def get_queue_family_properties(self):
        return self._pd.get_queue_family_properties()

    def create_device(self, device_create_info=vk.device_create_info):
        device, result = self._pd.create_device(device_create_info)

        for r in Result:
            if result == r.value:
                return Device(device), r

        return Device(device), result

    def destroy_device(self, device=Device):
        self._pd.destroy_device(device._d)


class CommandBuffer(object):
    def __init__(self, command_buffer):
        self._cb = command_buffer

    def begin(self, command_buffer_begin_info=CommandBufferBeginInfo):
        result = self._cb.begin(command_buffer_begin_info)

        for r in Result:
            if result == r.value:
                return r

        return result

    def pipeline_barrier(self, src_stage_mask=PipelineStageFlagBits.NONE, 
                        dst_stage_mask=PipelineStageFlagBits.NONE, 
                        dependency_flags=DependencyFlagBits.DEVICE_GROUP_BIT, 
                        memory_barriers=[], 
                        buffer_memory_barriers=[],
                        image_memory_barriers=[]):

        src_stage_mask_value = src_stage_mask.value if isinstance(src_stage_mask, PipelineStageFlagBits) else src_stage_mask
        dst_stage_mask_value = dst_stage_mask.value if isinstance(dst_stage_mask, PipelineStageFlagBits) else dst_stage_mask
        dependency_flags_value = dependency_flags.value if isinstance(dependency_flags, DependencyFlagBits) else dependency_flags

        self._cb.pipeline_barrier(src_stage_mask_value, dst_stage_mask_value, dependency_flags_value, memory_barriers,
                                  buffer_memory_barriers, image_memory_barriers)                        

    def copy_image(self, src_image=vk.image, src_image_layout=ImageLayout, dst_image=vk.image, dst_image_layout=ImageLayout, regions=[]):
        src_image_layout_value = src_image_layout.value if isinstance(src_image_layout, ImageLayout) else src_image_layout
        dst_image_layout_value = dst_image_layout.value if isinstance(dst_image_layout, ImageLayout) else dst_image_layout

        self._cb.copy_image(src_image, src_image_layout_value, dst_image, dst_image_layout_value, regions)

    def blit_image(self, src_image=vk.image, src_image_layout=ImageLayout.UNDEFINED, 
                   dst_image=vk.image, dst_image_layout=ImageLayout.UNDEFINED,
                   regions=[], filter=Filter.NEAREST):

        src_image_layout_value = src_image_layout.value if isinstance(src_image_layout, ImageLayout) else src_image_layout
        dst_image_layout_value = dst_image_layout.value if isinstance(dst_image_layout, ImageLayout) else dst_image_layout
        filter_value = filter.value if isinstance(filter, Filter) else filter

        self._cb.blit_image(src_image, src_image_layout_value, dst_image, dst_image_layout_value, regions, filter_value)

    def end(self):
        result = self._cb.end() 

        for r in Result:
            if result == r.value:
                return r
            
        return result


class Queue(object):
    def __init__(self, queue):
        self._q = queue

    def submit(self, submit_infos=list[SubmitInfo], fence=vk.fence):
        result = self._q.submit(submit_infos, fence)

        for r in Result:
            if r.value == result:
                return r
            
        return result

    def wait_idle(self):
        result = self._q.wait_idle()
        
        for r in Result:
            if r.value == result:
                return r
            
        return result

    def present(self, present_info=PresentInfo):
        result = self._q.present(present_info)

        for r in Result:
            if r.value == result:
                return r
        
        return result


def create_instance(instance_create_info=InstanceCreateInfo):
    i, result = vk.create_instance(instance_create_info)

    for r in Result:
        if result == r.value:
            return Instance(i), r

    return Instance(i), result


def destroy_instance(instance=Instance):
    vk.destroy_instance(instance._i)

# THIS IS LEFT HERE AS A REFERENCE FOR FUTURE
# class MemoryHeap(object):
#     def __init__(self, mh=vk.memory_heap):
#         self._mh = mh

#         for a in dir(mh):
#             if not a.startswith('__'):
#                 setattr(self, a, getattr(mh, a))
