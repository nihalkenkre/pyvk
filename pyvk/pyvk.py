import pyvk.vulkan as vk

from enum import Enum


class StructureType(Enum):
    APPLICATION_INFO = 0
    INSTANCE_CREATE_INFO = 1
    WIN32_SURFACE_CREATE_INFO_KHR = 1000009000


class ExtensionNames(Enum):
    KHR_SURFACE_EXTENSION_NAME = 'VK_KHR_surface'
    KHR_WIN32_SURFACE_EXTENSION_NAME = 'VK_KHR_win32_surface'


class InstanceCreateFlagBits(Enum):
    NONE = 0x00000000
    INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR = 0x00000001


class Result(Enum):
    SUCCESS = 0
    ERROR_OUT_OF_HOST_MEMORY = -1
    ERROR_OUT_OF_DEVICE_MEMORY = -2
    ERROR_INITIALIZATION_FAILED = -3
    ERROR_LAYER_NOT_PRESENT = -6
    ERROR_EXTENSION_NOT_PRESENT = -7
    ERROR_INCOMPATIBLE_DRIVER = -9


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


class Win32SurfaceCreateFlagsKHR(Enum):
    NONE = 0x00000000


class ApplicationInfo(vk.application_info):
    def __new__(cls, s_type=StructureType, p_next=None,
                app_name='', app_ver=(1, 0, 0, 0),
                engine_name='', engine_ver=(1, 0, 0, 0), api_ver=(1, 0, 0, 0)):

        if not isinstance(s_type, StructureType):
            raise TypeError(
                'Please pass a value from the pyvk.StructureType enum for s_type')

        if p_next is not None:
            raise TypeError('Please pass p_next as None')

        if not isinstance(app_ver, tuple):
            raise TypeError(
                'Please pass a tuple (variant, major, minor, patch) or None for default (1, 0, 0, 0) for app_ver')
        else:
            if not isinstance(app_ver[0], int):
                raise TypeError(
                    'Please pass an integer value for variant in app_ver')
            if not isinstance(app_ver[1], int):
                raise TypeError(
                    'Please pass an integer value for major in app_ver')
            if not isinstance(app_ver[2], int):
                raise TypeError(
                    'Please pass an integer value for minor in app_ver')
            if not isinstance(app_ver[3], int):
                raise TypeError(
                    'Please pass an integer value for patch in app_ver')

        if not isinstance(engine_ver, tuple):
            raise TypeError(
                'Please pass a tuple (variant, major, minor, patch) or None for default (1, 0, 0, 0) for engine_ver')
        else:
            if not isinstance(engine_ver[0], int):
                raise TypeError(
                    'Please pass an integer value for variant in engine_ver')
            if not isinstance(engine_ver[1], int):
                raise TypeError(
                    'Please pass an integer value for major in engine_ver')
            if not isinstance(engine_ver[2], int):
                raise TypeError(
                    'Please pass an integer value for minor in engine_ver')
            if not isinstance(engine_ver[3], int):
                raise TypeError(
                    'Please pass an integer value for patch in engine_ver')

        if not isinstance(api_ver, tuple):
            raise TypeError(
                'Please pass a tuple (variant, major, minor, patch) or None for default (1, 0, 0, 0) for api_ver')
        else:
            if not isinstance(api_ver[0], int):
                raise TypeError(
                    'Please pass an integer value for variant for api_ver')
            if not isinstance(api_ver[1], int):
                raise TypeError(
                    'Please pass an integer value for major for api_ver')
            if not isinstance(api_ver[2], int):
                raise TypeError(
                    'Please pass an integer value for minor for api_ver')
            if not isinstance(api_ver[3], int):
                raise TypeError(
                    'Please pass an integer value for patch for api_ver')

        return super(ApplicationInfo, cls).__new__(cls, s_type, p_next,
                                                   app_name, app_ver, engine_name,
                                                   engine_ver, api_ver)

    def __init__(self, s_type=StructureType, p_next=None,
                 app_name='', app_ver=(1, 0, 0, 0),
                 engine_name='', engine_ver=(1, 0, 0, 0), api_ver=(1, 0, 0, 0)):
        super(ApplicationInfo, self).__init__(s_type.value, p_next, app_name, app_ver,
                                              engine_name, engine_ver, api_ver)


class InstanceCreateInfo(vk.instance_create_info):
    def __new__(cls, s_type=StructureType, p_next=None,
                flags=InstanceCreateFlagBits, app_info=None, enabled_layers=[], enabled_extensions=[]):

        if not isinstance(s_type, StructureType):
            raise TypeError(
                'Please pass a value from the pyvk.StructureType enum class for s_type')

        if not isinstance(enabled_layers, list):
            raise TypeError(
                'Please pass a list of layer names for enabled_layers')

        for layer in enabled_layers:
            if not isinstance(layer, str):
                raise TypeError('Please pass a str as layer name')

        if not isinstance(enabled_extensions, list):
            raise TypeError(
                'Please pass a list of extension names for enabled_extensions')

        for extension in enabled_extensions:
            if not isinstance(extension, str):
                raise TypeError('Please pass a str as extension name')

        return super(InstanceCreateInfo, cls).__new__(cls, s_type, p_next,
                                                      flags, app_info,
                                                      enabled_layers, enabled_extensions)

    def __init__(self, s_type=StructureType, p_next=None,
                 flags=InstanceCreateFlagBits, app_info=None,
                 enabled_layers=[], enabled_extensions=[]):

        super(InstanceCreateInfo, self).__init__(s_type.value, p_next,
                                                 flags.value, app_info,
                                                 enabled_layers, enabled_extensions)


class Win32SurfaceCreateInfo(vk.surface_create_info):
    def __new__(cls, s_type=StructureType, p_next=None,
                flags=Win32SurfaceCreateFlagsKHR, h_wnd=int):
        if not isinstance(s_type, StructureType):
            raise TypeError(
                'Please pass a value from the pyvk.StructureType enum class for s_type')

        if p_next is not None:
            raise TypeError('Please pass None for p_next')

        if not isinstance(h_wnd, int):
            raise TypeError('Please pass object of type int/long for h_wnd')

        return super(Win32SurfaceCreateInfo, cls).__new__(cls, s_type, p_next, flags, h_wnd)

    def __init__(self, s_type=StructureType, p_next=None,
                 flags=Win32SurfaceCreateFlagsKHR, h_wnd=int):

        super(Win32SurfaceCreateInfo, self).__init__(s_type.value, p_next,
                                                     flags.value, h_wnd)


class Instance(object):
    def __init__(self, i=vk.instance):
        if not isinstance(i, vk.instance):
            raise TypeError('Please pass an object of type vulkan.instance')

        self._i = i

    def get_physical_devices(self):
        pds, result = self._i.get_physical_devices()

        ret_pds = [PhysicalDevice(pd) for pd in pds]

        for r in Result:
            if result == r.value:
                return ret_pds, r

    def create_surface(self, surface_create_info=Win32SurfaceCreateInfo):
        if not isinstance(surface_create_info, Win32SurfaceCreateInfo):
            raise TypeError(
                'Please pass an object of type vulkan.surface_create_info')

        s, result = self._i.create_surface(surface_create_info)
        for r in Result:
            if result == r.value:
                return s, r

    def destroy_surface(self, surface=vk.surface):
        if not isinstance(surface, vk.surface):
            raise TypeError('Please pass an object of type vulkan.surface')

        self._i.destroy_surface(surface)


class PhysicalDevice(object):
    def __init__(self, pd=vk.physical_device):
        if not isinstance(pd, vk.physical_device):
            raise TypeError(
                'Please pass an object of type vulkan.physical_device')

        self._pd = pd

    def get_features(self):
        return self._pd.get_features()

    def get_properties(self):
        return self._pd.get_properties()

    def get_memory_properties(self):
        return self._pd.get_memory_properties()

    def get_surface_capabilities_khr(self, surface=vk.surface):
        if not isinstance(surface, vk.surface):
            raise TypeError('Please pass an object of type vulkan.surface')

        caps, result = self._pd.get_surface_capabilities_khr(surface)

        for r in Result:
            if result == r.value:
                return caps, r


def create_instance(instance_create_info=InstanceCreateInfo):
    if not isinstance(instance_create_info, InstanceCreateInfo):
        raise TypeError(
            'Please pass an object of type pyvk.InstanceCreateInfo')

    i, result = vk.create_instance(instance_create_info)

    for r in Result:
        if result == r.value:
            return Instance(i), r


def destroy_instance(instance=Instance):
    if not isinstance(instance, Instance):
        raise TypeError('Please pass an object type pyvk.Instance')

    vk.destroy_instance(instance._i)

# THIS IS LEFT HERE AS A REFERENCE FOR FUTURE
# class MemoryHeap(object):
#     def __init__(self, mh=vk.memory_heap):
#         if not isinstance(mh, vk.memory_heap):
#             raise TypeError('Please pass an object of type vulkan.memory_heap')

#         self._mh = mh

#         for a in dir(mh):
#             if not a.startswith('__'):
#                 setattr(self, a, getattr(mh, a))
