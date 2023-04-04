import pyvk.vulkan as vk

from enum import Enum

class StructureType(Enum):
    APPLICATION_INFO = 0
    INSTANCE_CREATE_INFO = 1


class ExtensionNames(Enum):
    KHR_SURFACE_EXTENSION_NAME = 'VK_KHR_surface'
    KHR_WIN32_SURFACE_EXTENSION_NAME = "VK_KHR_win32_surface" 


class InstanceCreateFlagBits(Enum):
    NULL = 0x00000000
    INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR = 0x00000001


class ApplicationInfo(vk.application_info):
    def __new__(cls, s_type=StructureType, p_next=None, 
                app_name='', app_ver=(1, 0, 0, 0), 
                engine_name='', engine_ver=(1, 0, 0, 0), api_ver=(1, 0, 0, 0)):

        if not isinstance(s_type, StructureType):
            raise TypeError("Please pass a value from the pyvk.StructureType enum for s_type")

        if p_next is not None:
            raise TypeError("Please pass p_next as None")
        
        if not isinstance(app_ver, tuple):
            raise TypeError("Please pass a tuple (variant, major, minor, patch) or None for default (1, 0, 0, 0) for app_ver")
        else:
            if not isinstance(app_ver[0], int):
                raise TypeError("Please pass an integer value for variant in app_ver")
            if not isinstance(app_ver[1], int):
                raise TypeError("Please pass an integer value for major in app_ver")
            if not isinstance(app_ver[2], int):
                raise TypeError("Please pass an integer value for minor in app_ver")
            if not isinstance(app_ver[3], int):
                raise TypeError("Please pass an integer value for patch in app_ver")

        if not isinstance(engine_ver, tuple):
            raise TypeError("Please pass a tuple (variant, major, minor, patch) or None for default (1, 0, 0, 0) for engine_ver")
        else:
            if not isinstance(engine_ver[0], int):
                raise TypeError("Please pass an integer value for variant in engine_ver")
            if not isinstance(engine_ver[1], int):
                raise TypeError("Please pass an integer value for major in engine_ver")
            if not isinstance(engine_ver[2], int):
                raise TypeError("Please pass an integer value for minor in engine_ver")
            if not isinstance(engine_ver[3], int):
                raise TypeError("Please pass an integer value for patch in engine_ver")

        if not isinstance(api_ver, tuple):
            raise TypeError("Please pass a tuple (variant, major, minor, patch) or None for default (1, 0, 0, 0) for api_ver")
        else:
            if not isinstance(api_ver[0], int):
                raise TypeError("Please pass an integer value for variant for api_ver")
            if not isinstance(api_ver[1], int):
                raise TypeError("Please pass an integer value for major for api_ver")
            if not isinstance(api_ver[2], int):
                raise TypeError("Please pass an integer value for minor for api_ver")
            if not isinstance(api_ver[3], int):
                raise TypeError("Please pass an integer value for patch for api_ver")

        return super(ApplicationInfo, cls).__new__(cls)

    def __init__(self, s_type=StructureType, p_next=None, 
                app_name='', app_ver=(1, 0, 0, 0), 
                engine_name='', engine_ver=(1, 0, 0, 0), api_ver=(1, 0, 0, 0)):
        super(ApplicationInfo, self).__init__(s_type.value, p_next, app_name, app_ver,
                                              engine_name, engine_ver, api_ver)


class InstanceCreateInfo(vk.instance_create_info):
    def __new__(cls, s_type=StructureType, p_next=None,
                flags=InstanceCreateFlagBits, app_info=None, enabled_layers=[], enabled_extensions=[]):

        if not isinstance(s_type, StructureType):
            raise TypeError("Please pass a value from the pyvk.StructureType enum class")
    
        if not isinstance(enabled_layers, list):
            raise TypeError("Please pass a list of layer names")

        if not isinstance(enabled_extensions, list):
            raise TypeError("Please pass a list of extension names")

        return super(InstanceCreateInfo, cls).__new__(cls, s_type=s_type.value)
    
    def __init__(self,s_type=StructureType, p_next=None,
                flags=InstanceCreateFlagBits, app_info=None, enabled_layers=[], enabled_extensions=[]):
        super(InstanceCreateInfo, self).__init__(s_type.value, p_next, flags.value, app_info, enabled_layers, enabled_extensions)