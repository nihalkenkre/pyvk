import pyvk.vulkan as vk

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
    INCOMPLETE = 5
    ERROR_OUT_OF_HOST_MEMORY = -1
    ERROR_OUT_OF_DEVICE_MEMORY = -2
    ERROR_INITIALIZATION_FAILED = -3
    ERROR_DEVICE_LOST = -4
    ERROR_LAYER_NOT_PRESENT = -6
    ERROR_EXTENSION_NOT_PRESENT = -7
    ERROR_FEATURE_NOT_PRESENT = -8
    ERROR_INCOMPATIBLE_DRIVER = -9
    ERROR_TOO_MANY_OBJECTS = -10
    ERROR_UNKNOWN = -13
    ERROR_SURFACE_LOST_KHR = -1000000000
    ERROR_NATIVE_WINDOW_IN_USE_KHR = -1000000001
    ERROR_COMPRESSION_EXHAUSTED_EXT = -1000338000


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
    VK_IMAGE_USAGE_TRANSFER_SRC_BIT = 0x00000001
    VK_IMAGE_USAGE_TRANSFER_DST_BIT = 0x00000002
    VK_IMAGE_USAGE_SAMPLED_BIT = 0x00000004
    VK_IMAGE_USAGE_STORAGE_BIT = 0x00000008
    VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT = 0x00000010
    VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT = 0x00000020
    VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT = 0x00000040
    VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT = 0x00000080
    VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR = 0x00000400
    VK_IMAGE_USAGE_VIDEO_DECODE_SRC_BIT_KHR = 0x00000800
    VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR = 0x00001000
    VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT = 0x00000200
    VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR = 0x00000100
# ifdef VK_ENABLE_BETA_EXTENSIONS
    VK_IMAGE_USAGE_VIDEO_ENCODE_DST_BIT_KHR = 0x00002000
# endif
# ifdef VK_ENABLE_BETA_EXTENSIONS
    VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR = 0x00004000
# endif
# ifdef VK_ENABLE_BETA_EXTENSIONS
    VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR = 0x00008000
# endif
    VK_IMAGE_USAGE_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT = 0x00080000
    VK_IMAGE_USAGE_INVOCATION_MASK_BIT_HUAWEI = 0x00040000
    VK_IMAGE_USAGE_SAMPLE_WEIGHT_BIT_QCOM = 0x00100000
    VK_IMAGE_USAGE_SAMPLE_BLOCK_MATCH_BIT_QCOM = 0x00200000
    VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV = VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR


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


class ApplicationInfo(vk.application_info):
    def __init__(self, p_next=None,
                 app_name='', app_ver=(1, 0, 0, 0),
                 engine_name='', engine_ver=(1, 0, 0, 0), api_ver=(1, 0, 0, 0)):
        super(ApplicationInfo, self).__init__(p_next=p_next, app_name=app_name, app_ver=app_ver,
                                              engine_name=engine_name, engine_ver=engine_ver, api_ver=api_ver)


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

        super(InstanceCreateInfo, self).__init__(p_next,
                                                 flags.value, app_info,
                                                 enabled_layers=enabled_layers_str,
                                                 enabled_extensions=enabled_extensions_str)


class Win32SurfaceCreateInfo(vk.surface_create_info):
    def __init__(self, p_next=None,
                 flags=Win32SurfaceCreateFlagsKHR.NONE, h_wnd=int):

        super(Win32SurfaceCreateInfo, self).__init__(p_next,
                                                     flags.value, h_wnd)


class Instance(object):
    def __init__(self, i=vk.instance):
        self._i = i

    def get_physical_devices(self):
        pds, result = self._i.get_physical_devices()

        ret_pds = [PhysicalDevice(pd) for pd in pds]

        for r in Result:
            if result == r.value:
                return ret_pds, r

    def create_surface(self, surface_create_info=Win32SurfaceCreateInfo):
        s, result = self._i.create_surface(surface_create_info)
        for r in Result:
            if result == r.value:
                return s, r

    def destroy_surface(self, surface=vk.surface):
        self._i.destroy_surface(surface)


class DeviceQueueCreateInfo(vk.device_queue_create_info):
    def __init__(self, p_next=None,
                 flags=DeviceQueueCreateFlagBits.NONE, q_family_index=int,
                 q_count=1, priorities=[]):

        super(DeviceQueueCreateInfo, self).__init__(p_next, flags.value, q_family_index,
                                                    q_count, priorities)


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
                 surface=vk.surface, min_image_count=1, image_format=Format, image_color_space=ColorSpace,
                 image_extent=None, image_array_layers=1, image_usage_flags=ImageUsageFlagBits, image_sharing_mode=SharingMode,
                 queue_family_indices=[
                 ], pre_transform=SurfaceTransformFlagBits, composite_alpha=CompositeAlphFlagBitsKHR,
                 present_mode=PresentModeKHR, clipped=True, old_swapchain=vk.swapchain):

        if image_extent is not None:
            if len(image_extent) != 2:
                raise ValueError(
                    'Please pass a tuple of size 2 for image_extent in pyvk.SwapchainCreateInfo')

        flags_value = flags.value if isinstance(
            flags, SwapchainCreateFlagBitsKHR) else flags
        image_format_value = image_format.value if isinstance(
            image_format, Format) else image_format
        image_color_space_value = image_color_space.value if isinstance(
            image_color_space, ColorSpace) else image_color_space
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
                                                     image_usage_flags, image_sharing_mode_value, queue_family_indices, pre_transform_value,
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


class Device(object):
    def __init__(self, device=vk.device):
        self._d = device

    def get_queue(self, queue_family_index=0, queue_index=0):
        return self._d.get_queue(queue_family_index=queue_family_index, queue_index=queue_index)

    def create_swapchain(self, swapchain_create_info=SwapchainCreateInfoKHR):
        sc, result = self._d.create_swapchain(swapchain_create_info)

        for r in Result:
            if result == r.value:
                return sc, r

    def destroy_swapchain(self, swapchain=vk.swapchain):
        self._d.destroy_swapchain(swapchain)

    def create_command_pool(self, comamnd_pool_create_info=CommandPoolCreateInfo):
        cp, result = self._d.create_command_pool(comamnd_pool_create_info)

        for r in Result:
            if result == r.value:
                return cp, r

    def destroy_command_pool(self, command_pool=vk.command_pool):
        self._d.destroy_command_pool(command_pool)

    def allocate_command_buffers(self, command_buffer_allocate_info=CommandBufferAllocateInfo):
        cmd_bufs, result = self._d.allocate_command_buffers(
            command_buffer_allocate_info)

        for r in Result:
            if result == r.value:
                return cmd_bufs, r

    def free_command_buffers(self, command_pool=vk.command_pool, command_buffers=()):
        self._d.free_command_buffers(command_pool, command_buffers)

    def create_semaphore(self, semaphore_create_info=SemaphoreCreateInfo):
        sem, result = self._d.create_semaphore(semaphore_create_info)

        for r in Result:
            if result == r.value:
                return sem, r

    def destroy_semaphore(self, semaphore=vk.semaphore):
        self._d.destroy_semaphore(semaphore)


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

    def get_surface_formats_khr(self, surface=vk.surface):
        formats, result = self._pd.get_surface_formats_khr(surface)

        for r in Result:
            if result == r.value:
                return formats, r

    def get_surface_present_modes_khr(self, surface=vk.surface):
        present_modes, result = self._pd.get_surface_present_modes_khr(surface)

        for r in Result:
            if result == r.value:
                return present_modes, r

    def get_queue_family_properties(self):
        return self._pd.get_queue_family_properties()

    def create_device(self, device_create_info=vk.device_create_info):
        device, result = self._pd.create_device(device_create_info)

        for r in Result:
            if result == r.value:
                return Device(device), r

    def destroy_device(self, device=Device):
        self._pd.destroy_device(device._d)


def create_instance(instance_create_info=InstanceCreateInfo):
    i, result = vk.create_instance(instance_create_info)

    for r in Result:
        if result == r.value:
            return Instance(i), r


def destroy_instance(instance=Instance):
    vk.destroy_instance(instance._i)

# THIS IS LEFT HERE AS A REFERENCE FOR FUTURE
# class MemoryHeap(object):
#     def __init__(self, mh=vk.memory_heap):
#         self._mh = mh

#         for a in dir(mh):
#             if not a.startswith('__'):
#                 setattr(self, a, getattr(mh, a))
