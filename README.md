# PyVK

Python bindings for the Vulkan C libraries.

This consists of two parts.
1. The C - Extension which exposes the Vulkan structures and functions to Python.
2. A python file which defines the enums, provided wrapper classes around the C-extension classes, does value checking on the inputs to the classes  and is imported by the client scripts.

## C - Extension

This is a CPython extension. Vulkan structures are provided as classes and their members as class attributes. 

Structures which have members like the following
```
VkStruct {
    ...

    VkAnotherStruct* anotherStructPtr;
    uint32_t anotherStructPtrCount;

    ...
}
```
are provided as a list in the python classes.
```
class Struct {
    anotherStruct = []
}
```

The C code can easily get the necessary data from list to pass to the raw Vulkan structure.

`VkExtent2D` and friends are to be passed as `tuple`s. e.g. `VkExtent2D` will be passed as `(width, height)` etc.

Most functions are provided as part of classes they operate on. 

e.g.
```
vkGetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, ...... );

//

vkCreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, ...... );
```

are provided as part of the `PhysicalDevice` class, and `Device` class respectively as 

```
class PhysicalDevice(vk.physical_device):
    ...

    def get_surface_formatsi_khr(self, surface=vk.surface):
        ...
```

and

```
class Device(vk.device):
    ...

    def create_fence(self, fence_create_info=FenceCreateInfo):
        ...
```

Raw vulkan C functions which have an `'out'` parameter, and return a `VkResult`, are implemented to return a `tuple(out, Result)` as seen below in the `create_instance` example.

Raw vulkan C functions which do not have an `'out'` parameter, and return a `VkResult`, are implemented to return a `result`.

Raw vulkan C functions which do not have an `'out'` parameter, and do not return a `VkResult`, are implemented to return `None`.

## Python code

The enums are provided as class enums.

e.g.
```
typedef enum VkResult {
    VK_SUCCESS = 0,
    VK_NOT_READY = 1,
    
    ...

    VK_ERROR_OUT_OF_HOST_MEMORY = -1,
    VK_ERROR_OUT_OF_DEVICE_MEMORY = -2,
    ...

};
```

is provided as 
```
class Result(Enum):
    SUCCESS = 0
    NOT_READY = 1

    ...

    ERROR_OUT_OF_HOST_MEMORY = -1
    ERROR_OUT_OF_DEVICE_MEMORY = -2

    ...
```
There are wrapper classes created for the `**CreateInfo` structures. These classes create the `**CreateInfo` objects which can be used in Python. 

They provide acceptable default values. They do value checks when called by the client program and pass on the values to the C extension function.

There are wrapper classes created for objects that have functionality attached to them.
e.g.
```
class Device(vk.device):
    ...

    def create_fence(self, fence_create_info=FenceCreateInfo):
        ...
```


The python code is imported into the client application via

`from pyvk import pyvk as vk`

and from there vulkan structs (classes in Python) are accessed by
```
app_info = vk.ApplicationInfo(p_next=None,
                              app_name="Chip8", app_ver=(1, 0, 0, 0), 
                              engine_ver=engine_ver, engine_name="Chip8")

instance_ci = vk.InstanceCreateInfo(p_next=None,
                                    flags=0, app_info=app_info,
                                    enabled_extensions=[
                                        vk.InstanceExtensionNames.KHR_SURFACE_EXTENSION_NAME,
                                        vk.InstanceExtensionNames.KHR_WIN32_SURFACE_EXTENSION_NAME
                                    ])
self.i, result = vk.create_instance(instance_ci)                                    
```

and the enums are accessed by

```
result = some_operation(...)

if result != vk.Result.SUCCESS:
    raise SystemError(f'Some operation did not succeed')
```

Please refer to my [Chip8 Interpreter](https://gist.github.com/nihalkenkre/790cd416d87f08d2cdc7a04a8c00a671) built using `PySide6` for the GUI and `pyvk` for drawing.

## Disclaimer
This extension/package only wraps around the vulkan class and functions that were required to get the [Chip8 Interpreter](https://gist.github.com/nihalkenkre/790cd416d87f08d2cdc7a04a8c00a671) working.

## Current Implementation

Structures, functions and enums around the following operations have been implemented thus far.
1. Creating/destroying a Vulkan instance.
2. Getting physical devices. Getting device properties, memory properties.
3. Creating/destroying a surface.
4. Creating/destroying a logical device.
5. Creating/destroying a command pool.
6. Allocating/freeing command buffers.
7. Creating/destroying a swapchain.
8. Creating/destroying an image.
9. Creating/destroying an image view.
10. Beginning/ending command buffers.
11. Transitioning image layouts.
12. Issuing Image Copy, Image Blit operations.
13. Issuing Pipeline Barriers.
14. Queue Submissing and Presentation.

## TO-DO:
1. Implement the `setAttr` and `getAttr` C extension function. For now the attributes in the classes can be set only by passing them to the `init` function. 
2. The rest of the Vulkan API.

## CONTRIBUTIONS
Awaiting your feedback, inputs, tips, pull requests on everything as this develops further.