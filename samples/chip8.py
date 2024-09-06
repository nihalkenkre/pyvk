from PySide6.QtWidgets import QApplication, QMainWindow, QWidget, QFileDialog
from PySide6.QtGui import QAction
from PySide6.QtCore import Signal, Slot, QTimer, QObject, QFile, QByteArray

import numpy as np
import copy

import sys
from pyvk import pyvk as vk


'''
The signal - slot mechanism is used as much as possible. 

Each function has a signal associated with it, which is emitted just before the function returns.

So any dependant functionality is connected to the signal. 

The signal-slot connection between objects are handled by the class of which those objects are members/attributes, creating
a kind of loose hierarchy.

'''


class Display(QWidget):
    '''
    Handles the drawing of pixel data onto the "screen", using the vulkan interface.
    '''

    def __init__(self):
        QWidget.__init__(self)
        self.setFixedSize(64*10, 32*10)

        self.is_window_closed = False

        self.init_vulkan()

    @Slot(np.ndarray)
    def update(self, display_buffer):
        '''
        Parameter:
        display_buffer (numpy.ndarray) : the 64 x 32 bit binary data of which pixel in the display is 1(on) or 0(off).

        The next image index is obtained from the swapchain.
        Pipeline barriers are setup for the image data to be blitted from the source image
        to the swapchain image.

        *Our display is 640 x 320. So the display buffer is blitted into the presentation engine, with the scaling,
        filtering etc taken care of by the vulkan vkCmdBlitImage command.*
        '''

        if self.is_window_closed:
            return

        self.d.update_host_mapped_data(data=display_buffer, mem_id=self.mem_id)

        img_index, result = self.d.acquire_next_image(
            swapchain=self.swapchain, semaphore=self.img_acquire_sem)
        if result != vk.Result.SUCCESS:
            raise SystemError(f'Acquiring image failed with {result.name}')

        self.sc_img_to_dst = vk.ImageMemoryBarrier(src_access_mask=vk.AccessFlagBits.NONE,
                                                   dst_access_mask=vk.AccessFlagBits.TRANSFER_WRITE_BIT,
                                                   old_layout=vk.ImageLayout.UNDEFINED,
                                                   new_layout=vk.ImageLayout.TRANSFER_DST_OPTIMAL,
                                                   image=self.sc_imgs[img_index],
                                                   subresource_range=self.isr)
        self.img_to_src = vk.ImageMemoryBarrier(src_access_mask=vk.AccessFlagBits.NONE,
                                                dst_access_mask=vk.AccessFlagBits.TRANSFER_READ_BIT,
                                                old_layout=vk.ImageLayout.GENERAL,
                                                new_layout=vk.ImageLayout.TRANSFER_SRC_OPTIMAL,
                                                image=self.image,
                                                subresource_range=self.isr)
        self.sc_img_to_present = vk.ImageMemoryBarrier(src_access_mask=vk.AccessFlagBits.TRANSFER_WRITE_BIT,
                                                       dst_access_mask=vk.AccessFlagBits.NONE,
                                                       old_layout=vk.ImageLayout.TRANSFER_DST_OPTIMAL,
                                                       new_layout=vk.ImageLayout.PRESENT_SRC_KHR,
                                                       image=self.sc_imgs[img_index],
                                                       subresource_range=self.isr)

        self.isl = vk.ImageSubresourceLayers()

        result = self.cmd_bufs[0].begin(self.cbbi)
        if result != vk.Result.SUCCESS:
            raise SystemError(
                f'Begin command buffer failed with {result.name}')

        self.cmd_bufs[0].pipeline_barrier(src_stage_mask=vk.PipelineStageFlagBits.HOST_BIT,
                                          dst_stage_mask=vk.PipelineStageFlagBits.TRANSFER_BIT,
                                          image_memory_barriers=[self.img_to_src])

        self.cmd_bufs[0].pipeline_barrier(src_stage_mask=vk.PipelineStageFlagBits.TOP_OF_PIPE_BIT,
                                          dst_stage_mask=vk.PipelineStageFlagBits.TRANSFER_BIT,
                                          image_memory_barriers=[self.sc_img_to_dst])

        src_offsets = [(0, 0, 0), (64, 32, 1)]
        dst_offsets = [(0, 0, 0), (self.caps.current_extent[0],
                                   self.caps.current_extent[1], 1)]

        self.img_blit = vk.ImageBlit(src_subresource=self.isl, src_offsets=src_offsets,
                                     dst_subresource=self.isl, dst_offsets=dst_offsets)

        self.cmd_bufs[0].blit_image(src_image=self.image, src_image_layout=vk.ImageLayout.TRANSFER_SRC_OPTIMAL,
                                    dst_image=self.sc_imgs[img_index], dst_image_layout=vk.ImageLayout.TRANSFER_DST_OPTIMAL,
                                    regions=[self.img_blit])
        self.cmd_bufs[0].pipeline_barrier(src_stage_mask=vk.PipelineStageFlagBits.TRANSFER_BIT,
                                          dst_stage_mask=vk.PipelineStageFlagBits.BOTTOM_OF_PIPE_BIT,
                                          image_memory_barriers=[self.sc_img_to_present])
        self.cmd_bufs[0].pipeline_barrier(src_stage_mask=vk.PipelineStageFlagBits.TRANSFER_BIT,
                                          dst_stage_mask=vk.PipelineStageFlagBits.BOTTOM_OF_PIPE_BIT,
                                          image_memory_barriers=[self.img_to_gen])
        result = self.cmd_bufs[0].end()
        if result != vk.Result.SUCCESS:
            raise SystemError(
                f'Ending command buffer failed with {result.name}')

        si = vk.SubmitInfo(wait_semaphores=[self.img_acquire_sem],
                           command_buffers=self.cmd_bufs,
                           signal_semaphores=[self.signal_present_sem])
        result = self.q.submit(submit_infos=[si])
        if result != vk.Result.SUCCESS:
            raise SystemError(f'Queue submit failed with {result.name}')

        pi = vk.PresentInfo(wait_semaphores=[self.signal_present_sem],
                            swapchains=[self.swapchain],
                            image_indices=[img_index])

        result = self.q.present(pi)
        if result != vk.Result.SUCCESS:
            raise SystemError(f'Presenting image failed with {result.name}')

        result = self.q.wait_idle()
        if result != vk.Result.SUCCESS:
            raise SystemError(f'Wait Idle failed with {result.name}')

    def init_vulkan(self):
        '''
        Initialize vulkan 'boilerplate' code. Device, swapchain, command buffers, synchronization objects, source image.
        The source image named 'image' is the staging image, in which the 'display buffer' is copied to, and then blitted
        into the swapchain image.
        '''
        engine_ver = (1, 0, 0, 1)
        app_info = vk.ApplicationInfo(p_next=None,
                                      app_name="Chip8", app_ver=(1, 0, 0, 0), engine_ver=engine_ver,
                                      engine_name="Chip8")

        instance_ci = vk.InstanceCreateInfo(p_next=None,
                                            flags=0, app_info=app_info,
                                            enabled_extensions=[
                                                vk.InstanceExtensionNames.KHR_SURFACE_EXTENSION_NAME,
                                                vk.InstanceExtensionNames.KHR_WIN32_SURFACE_EXTENSION_NAME
                                            ])
        self.i, result = vk.create_instance(instance_ci)
        if result != vk.Result.SUCCESS:
            raise SystemError(f'Instance creation failed with {result.name}')

        phy_devs, result = self.i.get_physical_devices()
        if result != vk.Result.SUCCESS:
            raise SystemError(
                f'Getting physical devices failed with {result.name}')

        h_wnd = self.winId()

        sci = vk.Win32SurfaceCreateInfo(p_next=None,
                                        h_wnd=h_wnd)
        self.s, result = self.i.create_surface(sci)

        if result != vk.Result.SUCCESS:
            raise SystemError(
                f'Surface creation failed with error {result.name}')

        self.pd = phy_devs[0]

        dev_props = self.pd.get_properties()
        mem_props = self.pd.get_memory_properties()
        pdf = self.pd.get_features()

        pms, result = self.pd.get_surface_present_modes_khr(self.s)

        if result != vk.Result.SUCCESS:
            raise SystemError(
                f'Getting present modes failed with {result.name}')

        fmts, result = self.pd.get_surface_formats_khr(self.s)

        if result != vk.Result.SUCCESS:
            raise SystemError(f'Getting formats failed with {result.name}')

        self.caps, result = self.pd.get_surface_capabilities_khr(self.s)

        if result != vk.Result.SUCCESS:
            raise SystemError(
                f'Getting surface capabilities failed with {result.name}')

        dqci = vk.DeviceQueueCreateInfo(
            queue_family_index=0, queue_count=1, priorities=[1.0])
        dci = vk.DeviceCreateInfo(queue_create_infos=[dqci],
                                  enabled_extensions=[
            vk.DeviceExtensionNames.SWAPCHAIN_EXTENSION_NAME],
            enabled_features=pdf)
        self.d, result = self.pd.create_device(dci)

        if result != vk.Result.SUCCESS:
            raise SystemError(
                f'Device creation failed with error {result.name}')
        cpci = vk.CommandPoolCreateInfo(
            flags=vk.CommandPoolCreateFlagBits.RESET_COMMAND_BUFFER_BIT)
        self.cmd_pool, result = self.d.create_command_pool(cpci)

        if result != vk.Result.SUCCESS:
            raise SystemError(
                f'Command Pool creationg failed with {result.name}')
        cmd_buf_ai = vk.CommandBufferAllocateInfo(self.cmd_pool)
        self.cmd_bufs, result = self.d.allocate_command_buffers(cmd_buf_ai)

        if result != vk.Result.SUCCESS:
            raise SystemError(
                f'Command Buffer creation failed with {result.name}')

        fci = vk.FenceCreateInfo()
        self.fence, result = self.d.create_fence(fci)

        if result != vk.Result.SUCCESS:
            raise SystemError(f'Fence creation failed with {result.name}')

        sci = vk.SemaphoreCreateInfo()
        self.img_acquire_sem, result = self.d.create_semaphore(sci)

        if result != vk.Result.SUCCESS:
            raise SystemError(f'Semaphore creation failed with {result.name}')

        self.signal_present_sem, result = self.d.create_semaphore(sci)

        if result != vk.Result.SUCCESS:
            raise SystemError(f'Semaphore creation failed with {result.name}')

        self.cpy_complete_sem, result = self.d.create_semaphore(sci)
        if result != vk.Result.SUCCESS:
            raise SystemError(f'Semaphore creation failed with {result.name}')

        ici = vk.ImageCreateInfo(p_next=None, format=fmts[0].format,
                                 usage=vk.ImageUsageFlagBits.TRANSFER_SRC_BIT,
                                 extent=(64, 32, 1),
                                 tiling=vk.ImageTiling.LINEAR, queue_family_indices=[])

        self.image, result = self.d.create_image(ici)

        if result != vk.Result.SUCCESS:
            raise SystemError(
                f'Image creation failed with {result.name} on device {dev_props.device_name}')

        mem_req = self.d.get_image_memory_requirements(self.image)

        mem_type_idx = 0
        req_types = vk.MemoryPropertyFlagBits.HOST_VISIBLE_BIT.value

        for i in range(len(mem_props.types)):
            if (mem_req.memory_type_bits * (1 << i)) and (req_types & mem_props.types[i].property_flags):
                mem_type_idx = i
                break

        mai = vk.MemoryAllocateInfo(
            allocation_size=mem_req.size, memory_type_index=mem_type_idx)

        self.memory, result = self.d.allocate_memory(mai)

        if result != vk.Result.SUCCESS:
            raise SystemError(f'Allocating memory failed with {result.name}')

        result = self.d.bind_image_memory(image=self.image, memory=self.memory)

        if result != vk.Result.SUCCESS:
            raise SystemError(
                f'Binding image memory failed with {result.name}')

        scci = vk.SwapchainCreateInfoKHR(surface=self.s, min_image_count=self.caps.min_image_count,
                                         image_format=fmts[0].format, image_color_space=fmts[0].color_space,
                                         image_extent=self.caps.current_extent, image_usage_flags=self.caps.supported_usage_flags,
                                         image_sharing_mode=vk.SharingMode.EXCLUSIVE, pre_transform=self.caps.current_transform)

        self.swapchain, result = self.d.create_swapchain(scci)

        if result != vk.Result.SUCCESS:
            raise SystemError(f'Swapchain creation failed with {result.name}')

        self.sc_imgs, result = self.d.get_swapchain_images(self.swapchain)

        if result != vk.Result.SUCCESS:
            raise SystemError(
                f'Getting swapchain images failed with {result.name}')

        self.isr = vk.ImageSubresourceRange()
        self.q = self.d.get_queue()

        self.cbbi = vk.CommandBufferBeginInfo()

        self.img_to_gen = vk.ImageMemoryBarrier(src_access_mask=vk.AccessFlagBits.NONE,
                                                dst_access_mask=vk.AccessFlagBits.NONE,
                                                old_layout=vk.ImageLayout.UNDEFINED,
                                                new_layout=vk.ImageLayout.GENERAL,
                                                image=self.image,
                                                subresource_range=self.isr)

        result = self.cmd_bufs[0].begin(self.cbbi)
        if result != vk.Result.SUCCESS:
            raise SystemError(
                f'Begin command buffer failed with {result.name}')

        self.cmd_bufs[0].pipeline_barrier(src_stage_mask=vk.PipelineStageFlagBits.TOP_OF_PIPE_BIT,
                                          dst_stage_mask=vk.PipelineStageFlagBits.HOST_BIT,
                                          image_memory_barriers=[
                                              self.img_to_gen])

        result = self.cmd_bufs[0].end()
        if result != vk.Result.SUCCESS:
            raise SystemError(
                f'End command buffer failed with {result.name}')

        si = vk.SubmitInfo(command_buffers=self.cmd_bufs)

        result = self.q.submit(submit_infos=[si], fence=self.fence)
        if result != vk.Result.SUCCESS:
            raise SystemError(
                f'Submit fence failed with {result.name}')

        result = self.d.wait_for_fences([self.fence])
        if result != vk.Result.SUCCESS:
            raise SystemError(
                f'Wait for fence failed with {result.name}')

        result = self.d.reset_fences(fences=[self.fence])
        if result != vk.Result.SUCCESS:
            raise SystemError(f'Reset fences failed with {result.name}')


        # The memory is left mapped until the end of the application since it is updated regularly during opcode execution.

        self.mem_id, result = self.d.map_memory(self.memory, size=mem_req.size)
        if result != vk.Result.SUCCESS:
            raise SystemError(
                f'Map memory failed with {result.name}')

    def shutdown(self):
        self.is_window_closed = True
        self.shutdown_vulkan()

    def shutdown_vulkan(self):
        # for sc_iv in self.sc_ivs:
        #     self.d.destroy_image_view(sc_iv)

        self.d.unmap_memory(self.memory)
        self.d.destroy_swapchain(self.swapchain)
        self.d.free_memory(self.memory)
        self.d.destroy_image(self.image)
        self.d.destroy_semaphore(self.cpy_complete_sem)
        self.d.destroy_semaphore(self.signal_present_sem)
        self.d.destroy_semaphore(self.img_acquire_sem)
        self.d.destroy_fence(self.fence)
        self.d.free_command_buffers(self.cmd_pool, self.cmd_bufs)
        self.d.destroy_command_pool(self.cmd_pool)
        self.pd.destroy_device(self.d)
        self.i.destroy_surface(self.s)
        vk.destroy_instance(self.i)


class CPU(QObject):
    '''
    Reads the Chip8 ROM file, sets/resets memory, registers, and cpu timer.
    '''
    
    finished_receive_file_name = Signal()
    finished_reset = Signal()
    finished_file_read = Signal((QByteArray))
    finished_load_data_into_memory = Signal()
    finished_execute = Signal((np.ndarray))

    def __init__(self):
        super(CPU, self).__init__()
        self.timer = QTimer(self)
        self.file_name = ''

        self.timer.timeout.connect(self.exec_next_opcode)

        self.finished_receive_file_name.connect(self.reset_mem_and_regs)
        self.finished_reset.connect(self.read_file)
        self.finished_file_read.connect(self.load_data_into_memory)
        self.finished_load_data_into_memory.connect(self.start_timer)

    @Slot()
    def start_timer(self):
        if self.timer.isActive():
            self.timer.stop()

        self.timer.start(16)

    @Slot()
    def reset_mem_and_regs(self):
        self.memory = [0] * 4096

        self.pc = 512
        self.sp = -1

        self.I = 0
        self.V = [0] * 16
        self.stack = []

        self.delay_timer = 0
        self.sound_timer = 0

        self.display_buffer = np.asarray(
            np.random.rand(64, 32) * 0, dtype='uint8')

        self.init_sprite_sheet()
        self.finished_reset.emit()

    def init_sprite_sheet(self):
        '''
            The sprites used are stored in the memory within the 512 mark as 2 byte data.
            The following are bytes values for the hexadecimal digits.
        '''
        # 0
        self.memory[0] = 0xF0
        self.memory[1] = 0x90
        self.memory[2] = 0x90
        self.memory[3] = 0x90
        self.memory[4] = 0xF0

        # 1
        self.memory[5] = 0x20
        self.memory[6] = 0x60
        self.memory[7] = 0x20
        self.memory[8] = 0x20
        self.memory[9] = 0x70

        # 2
        self.memory[10] = 0xF0
        self.memory[11] = 0x10
        self.memory[12] = 0xF0
        self.memory[13] = 0x80
        self.memory[14] = 0xF0

        # 3
        self.memory[15] = 0xF0
        self.memory[16] = 0x10
        self.memory[17] = 0xF0
        self.memory[18] = 0x10
        self.memory[19] = 0xF0

        # 4
        self.memory[20] = 0x90
        self.memory[21] = 0x90
        self.memory[22] = 0xF0
        self.memory[23] = 0x10
        self.memory[24] = 0x10

        # 5
        self.memory[25] = 0xF0
        self.memory[26] = 0x80
        self.memory[27] = 0xF0
        self.memory[28] = 0x10
        self.memory[29] = 0xF0

        # 6
        self.memory[30] = 0xF0
        self.memory[31] = 0x80
        self.memory[32] = 0xF0
        self.memory[33] = 0x90
        self.memory[34] = 0xF0

        # 7
        self.memory[35] = 0xF0
        self.memory[36] = 0x10
        self.memory[37] = 0x20
        self.memory[38] = 0x40
        self.memory[39] = 0x40

        # 8
        self.memory[40] = 0xF0
        self.memory[41] = 0x90
        self.memory[42] = 0xF0
        self.memory[43] = 0xF9
        self.memory[44] = 0xF0

        # 9
        self.memory[45] = 0xF0
        self.memory[46] = 0x90
        self.memory[47] = 0xF0
        self.memory[48] = 0x10
        self.memory[49] = 0xF0

        # A
        self.memory[50] = 0xF0
        self.memory[51] = 0x90
        self.memory[52] = 0xF0
        self.memory[53] = 0x90
        self.memory[54] = 0x90

        # B
        self.memory[55] = 0xE0
        self.memory[56] = 0x90
        self.memory[57] = 0xF0
        self.memory[58] = 0x10
        self.memory[59] = 0xE0

        # C
        self.memory[60] = 0xF0
        self.memory[61] = 0x80
        self.memory[62] = 0x80
        self.memory[63] = 0x80
        self.memory[64] = 0xF0

        # D
        self.memory[65] = 0xE0
        self.memory[66] = 0x90
        self.memory[67] = 0x90
        self.memory[68] = 0x90
        self.memory[69] = 0xE0

        # E
        self.memory[70] = 0xF0
        self.memory[71] = 0x80
        self.memory[72] = 0xF0
        self.memory[73] = 0x80
        self.memory[74] = 0xF0

        # F
        self.memory[75] = 0xF0
        self.memory[76] = 0x80
        self.memory[77] = 0xF0
        self.memory[78] = 0x80
        self.memory[79] = 0x80

    @Slot(str)
    def receive_file_name(self, file_name):
        self.file_name = file_name

        self.finished_receive_file_name.emit()

    @Slot(str)
    def read_file(self):
        rom_file = QFile(self.file_name)

        if rom_file.open(QFile.OpenModeFlag.ReadOnly):
            rom_data = rom_file.readAll()
            self.finished_file_read.emit(rom_data)
        else:
            raise IOError(f'Could not open {self.file_name}')

    @Slot(QByteArray)
    def load_data_into_memory(self, rom_data):
        '''
        The program for the system are loaded from memory location 0x200 which is 512 in decimal.
        The first 512 bytes were reserved for the interpreter itself.
        '''
        for i in range(512, 512 + len(rom_data)):
            self.memory[i] = int.from_bytes(rom_data[i - 512])

        self.finished_load_data_into_memory.emit()

    @Slot()
    def exec_next_opcode(self):
        '''
        Get the 4-byte opcode from the memory.
        Isolate the first byte, on which the operation of the opcode is based on.
        Perform the operation
        '''

        opcode = self.memory[self.pc] << 8 | self.memory[self.pc + 1]

        first = opcode >> 12

        if first == 0x0:
            if opcode == 0x00E0:
                self.display_buffer.fill(0)

                self.pc += 2
                self.finished_execute.emit(self.display_buffer)

            elif opcode == 0x00EE:
                self.pc = self.stack.pop()
                self.sp -= 1

        elif first == 0x1:
            location = opcode & 0x0FFF

            self.pc = location

        elif first == 0x2:
            location = opcode & 0x0FFF

            self.stack.append(self.pc + 2)
            self.sp += 1

            self.pc = location

        elif first == 0x3:
            x = (opcode & 0x0F00) >> 8
            kk = opcode & 0x00FF

            if self.V[x] == kk:
                self.pc += 2

            self.pc += 2

        elif first == 0x4:
            x = (opcode & 0x0F00) >> 8
            kk = opcode & 0x00FF

            if self.V[x] != kk:
                self.pc += 2

            self.pc += 2

        elif first == 0x5:
            x = (opcode & 0x0F00) >> 8
            y = (opcode & 0x00F0) >> 4

            if (self.V[x] == self.V[y]):
                self.pc += 2

            self.pc += 2

        elif first == 0x6:
            x = (opcode & 0x0F00) >> 8
            kk = opcode & 0x00FF

            self.V[x] = kk

            self.pc += 2

        elif first == 0x7:
            x = (opcode & 0x0F00) >> 8
            kk = opcode & 0x00FF

            self.V[x] = (self.V[x] + kk) & 0x00FF

            self.pc += 2

        elif first == 0x8:
            mode = opcode & 0x000F

            x = (opcode & 0x0F00) >> 8
            y = (opcode & 0x00F0) >> 4

            if mode == 0x0:
                self.V[x] = self.V[y] & 0x00FF
            elif mode == 0x1:
                self.V[x] = (self.V[x] | self.V[y]) & 0x00FF
            elif mode == 0x2:
                self.V[x] = (self.V[x] & self.V[y]) & 0x00FF
            elif mode == 0x3:
                self.V[x] = (self.V[x] ^ self.V[y]) & 0x00FF
            elif mode == 0x4:
                tmp = (self.V[x] + self.V[y])
                self.V[0xF] = 1 if tmp > 255 else 0
                self.V[x] = tmp & 0x00FF
            elif mode == 0x5:
                self.V[0xF] = 1 if self.V[x] > self.V[y] else 0
                self.V[x] = (self.V[x] - self.V[y]) & 0x00FF
            elif mode == 0x6:
                self.V[0xF] = self.V[x] & 0x1
                self.V[x] = (self.V[x] >> 1) & 0x00FF
            elif mode == 0x7:
                self.V[0xF] = 1 if (self.V[y] > self.V[x]) else 0
                self.V[x] = (self.V[y] - self.V[x]) & 0x00FF
            elif mode == 0xE:
                self.V[0xF] = (self.V[x] & 0x80) >> 7
                self.V[x] = (self.V[x] << 1) & 0x00FF

            self.pc += 2

        elif first == 0x9:
            x = (opcode & 0x0F00) >> 8
            y = (opcode & 0x00F0) >> 4

            if self.V[x] != self.V[y]:
                self.pc += 2

            self.pc += 2

        elif first == 0xA:
            location = opcode & 0x0FFF

            self.I = location & 0xFFFF

            self.pc += 2

        elif first == 0xB:
            location = (opcode & 0x0FFF) + self.V[0]

            self.pc += 2

        elif first == 0xC:
            x = (opcode & 0x0F00) >> 8
            kk = opcode & 0x00FF

            self.V[x] = (np.random.randint(low=0, high=256) & kk) & 0x00FF

            self.pc += 2

        elif first == 0xD:
            xx = (opcode & 0x0F00) >> 8
            yy = (opcode & 0x00F0) >> 4
            nn = opcode & 0x000F

            y = self.V[yy] & 31

            self.V[0xF] = 0

            for n in range(nn):
                row = self.memory[self.I + n]

                x = self.V[xx] & 63

                for p in range(8):
                    if x > 63:
                        continue

                    row_pixel = (((128) >> p) & row) >> (7 - p)

                    if ((row_pixel == 1) and (self.display_buffer[x][y] == 255)):
                        self.display_buffer[x][y] = 0
                        self.V[0xF] = 1

                    elif ((row_pixel == 1) and (self.display_buffer[x][y] == 0)):
                        self.display_buffer[x][y] = 255

                    x += 1

                y += 1

                if y > 31:
                    break

            self.pc += 2

            self.finished_execute.emit(self.display_buffer)

        elif first == 0xE:
            x = (opcode & 0x0F00) >> 8

            mode = opcode & 0x00FF

            if mode == 0x9E:
                ...
            elif mode == 0xA1:
                ...

        elif first == 0xF:
            x = opcode & 0x0F00 >> 8

            mode = opcode & 0x00FF

            if mode == 0x07:
                self.V[x] = self.delay_timer
            elif mode == 0x0A:
                ...
            elif mode == 0x15:
                self.delay_timer = self.V[x]
            elif mode == 0x18:
                self.sound_timer = self.V[x]
            elif mode == 0x1E:
                tmp = (self.I + self.V[x])
                if tmp > 0x0FFF:
                    self.V[0xF] = 1

                self.I = tmp & 0x0FFF
            elif mode == 0x29:
                ...
            elif mode == 0x33:
                vx_str = str(self.V[x])

                for i in range(len(vx_str)):
                    self.memory[self.I + i] = int(vx_str[i])

            elif mode == 0x55:
                for i in range(0, x):
                    self.memory[self.I + i] = (self.V[i]) & 0x00FF
            elif mode == 0x65:
                for i in range(0, x):
                    self.V[i] = (self.memory[self.I + i]) & 0x00FF

            self.pc += 2


class Window(QMainWindow):
    '''
    Setup parts of the application. 
    Handle the input events - keyboard and mouse events.
    '''

    got_file_name = Signal((str))

    def __init__(self):
        super(Window, self).__init__()

        self.setWindowTitle("Chip 8")
        self.menu = self.menuBar()
        self.file_menu = self.menu.addMenu("File")

        file_open_action = QAction("Open", self)
        file_open_action.triggered.connect(self.get_file_name)
        self.file_menu.addAction(file_open_action)

        self.file_menu.addSeparator()

        self.file_menu.addAction("Exit")

        self.cpu = CPU()
        self.display = Display()

        self.got_file_name.connect(self.cpu.receive_file_name)
        self.cpu.finished_execute.connect(self.display.update)

        self.setCentralWidget(self.display)

    @ Slot()
    def get_file_name(self):
        file_name, ext = QFileDialog.getOpenFileName(
            self, "Select Chip8 ROM", "", "*.ch8", "*.ch8")

        if file_name == '':
            return

        if not QFile.exists(file_name):
            raise FileNotFoundError(f'{file_name} not found')

        self.got_file_name.emit(file_name)

    def keyPressEvent(self, event):
        event.accept()
        print(event.text())

    def closeEvent(self, event):
        self.display.shutdown()
        return super().closeEvent(event)


class Chip8(QApplication):
    '''
    Application level details and functionality
    '''

    def __init__(self, argv):
        super(Chip8, self).__init__(argv)


if __name__ == '__main__':
    print('Hello')

    chip8 = Chip8(sys.argv)

    window = Window()
    window.show()

    chip8.exec()

    print('Bye')