from setuptools import setup
from setuptools import Extension

import os

vulkan_sdk = os.environ['VULKAN_SDK']

setup(
    ext_modules=[
        Extension(
            name='pyvk.vulkan',
            sources=[
                './pyvk/vulkan/src/vk/vk_module.c',
                './pyvk/vulkan/src/vk/vk_instance/vk_instance.c',
                './pyvk/vulkan/src/vk/vk_instance/vk_instance_ci.c',
                './pyvk/vulkan/src/vk/vk_instance/vk_app_info.c',
                './pyvk/vulkan/src/vk/vk_phy_dev/vk_phy_dev.c',
                './pyvk/vulkan/src/vk/vk_phy_dev/vk_phy_dev_mem_props.c',
                './pyvk/vulkan/src/vk/vk_phy_dev/vk_phy_dev_props.c',
                './pyvk/vulkan/src/vk/vk_phy_dev/vk_phy_dev_limits.c',
                './pyvk/vulkan/src/vk/vk_phy_dev/vk_phy_dev_features.c',
                './pyvk/vulkan/src/vk/vk_phy_dev/vk_phy_dev_sparse_properties.c',
                './pyvk/vulkan/src/vk/vk_mem/vk_mem_req.c',
                './pyvk/vulkan/src/vk/vk_mem/vk_mem_type.c',
                './pyvk/vulkan/src/vk/vk_mem/vk_mem_heap.c',
                './pyvk/vulkan/src/vk/vk_mem/vk_mem_ai.c',
                './pyvk/vulkan/src/vk/vk_dev/vk_dev_mem.c',
                './pyvk/vulkan/src/vk/vk_dev/vk_dev_q_ci.c',
                './pyvk/vulkan/src/vk/vk_dev/vk_dev_ci.c',
                './pyvk/vulkan/src/vk/vk_dev/vk_dev.c',
                './pyvk/vulkan/src/vk/vk_surface/vk_surface_caps_khr.c',
                './pyvk/vulkan/src/vk/vk_surface/vk_surface_fmt_khr.c',
                './pyvk/vulkan/src/vk/vk_surface/vk_surface_ci.c',
                './pyvk/vulkan/src/vk/vk_surface/vk_surface.c',
                './pyvk/vulkan/src/vk/vk_swapchain/vk_swapchain_ci.c',
                './pyvk/vulkan/src/vk/vk_swapchain/vk_swapchain.c',
                './pyvk/vulkan/src/vk/vk_queue/vk_q.c',
                './pyvk/vulkan/src/vk/vk_queue/vk_q_fly_props.c',
                './pyvk/vulkan/src/vk/vk_queue/vk_q_si.c',
                './pyvk/vulkan/src/vk/vk_queue/vk_q_pi.c',
                './pyvk/vulkan/src/vk/vk_cmd_pool/vk_cmd_pool_ci.c',
                './pyvk/vulkan/src/vk/vk_cmd_pool/vk_cmd_pool.c',
                './pyvk/vulkan/src/vk/vk_cmd_buf/vk_cmd_buf_ai.c',
                './pyvk/vulkan/src/vk/vk_cmd_buf/vk_cmd_buf_bi.c',
                './pyvk/vulkan/src/vk/vk_cmd_buf/vk_cmd_buf.c',
                './pyvk/vulkan/src/vk/vk_sem/vk_sem_ci.c',
                './pyvk/vulkan/src/vk/vk_sem/vk_sem.c',
                './pyvk/vulkan/src/vk/vk_fence/vk_fence_ci.c',
                './pyvk/vulkan/src/vk/vk_fence/vk_fence.c',
                './pyvk/vulkan/src/vk/vk_img/vk_img_mem_bar.c',
                './pyvk/vulkan/src/vk/vk_img/vk_img_cpy.c',
                './pyvk/vulkan/src/vk/vk_img/vk_img_srl.c',
                './pyvk/vulkan/src/vk/vk_img/vk_img_srr.c',
                './pyvk/vulkan/src/vk/vk_img/vk_img_ci.c',
                './pyvk/vulkan/src/vk/vk_img/vk_img.c',
                './pyvk/vulkan/src/utils/log.c',
                './pyvk/vulkan/src/utils/utils.c',
            ],
            include_dirs=[
                './pyvk/vulkan/src/vk',
                './pyvk/vulkan/src/vk/vk_instance',
                './pyvk/vulkan/src/vk/vk_phy_dev',
                './pyvk/vulkan/src/vk/vk_dev',
                './pyvk/vulkan/src/vk/vk_mem',
                './pyvk/vulkan/src/vk/vk_surface',
                './pyvk/vulkan/src/vk/vk_swapchain',
                './pyvk/vulkan/src/vk/vk_queue',
                './pyvk/vulkan/src/vk/vk_cmd_pool',
                './pyvk/vulkan/src/vk/vk_cmd_buf',
                './pyvk/vulkan/src/vk/vk_sem',
                './pyvk/vulkan/src/vk/vk_fence',
                './pyvk/vulkan/src/vk/vk_img',
                './pyvk/vulkan/src/utils',
                os.path.join(vulkan_sdk, 'Include'),
            ],
            library_dirs=[
                os.path.join(vulkan_sdk, 'Lib'),
            ],
            libraries=[
                'vulkan-1'
            ],
            define_macros=[
                ('WIN32_LEAN_AND_MEAN', None),
                ('PY_SSIZE_T_CLEAN', None),
                ('DEBUG', None),
            ],
        )
    ]
)
