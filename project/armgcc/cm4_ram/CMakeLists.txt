INCLUDE(CMakeForceCompiler)

# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

# THE VERSION NUMBER
SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 0)

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

 
# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})


SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} \
     -DDEBUG -D__STARTUP_CLEAR_BSS -g -Wall -fno-common -ffunction-sections -fdata-sections -ffreestanding -fno-builtin \
     -mthumb -mapcs -Wa,-mimplicit-it=thumb -std=gnu99 -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} \
     -DNDEBUG -D__STARTUP_CLEAR_BSS -Wall -fno-common -ffunction-sections -fdata-sections -ffreestanding -fno-builtin \
     -mthumb -mapcs -Wa,-mimplicit-it=thumb -std=gnu99 -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} \
     -DDEBUG -DCPU_LPC54114J256BD64_cm4 -DMCMGR_HANDLE_EXCEPTIONS=1 -D__SEMIHOST_HARDFAULT_DISABLE=1 \
     -DMULTICORE_APP=1 -DSERIAL_PORT_TYPE_UART=1 -DFSL_RTOS_FREE_RTOS -DDEBUG_CONSOLE_TRANSFER_NON_BLOCKING -g -O0 -Wall -fno-common -ffunction-sections \
     -fdata-sections -ffreestanding -fno-builtin -mthumb -mapcs -std=gnu99 -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -MMD -MP")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} \
     -DNDEBUG -DCPU_LPC54114J256BD64_cm4 -DMCMGR_HANDLE_EXCEPTIONS=1 -D__SEMIHOST_HARDFAULT_DISABLE=1 \
     -DMULTICORE_APP=1 -DSERIAL_PORT_TYPE_UART=1 -DFSL_RTOS_FREE_RTOS -DDEBUG_CONSOLE_TRANSFER_NON_BLOCKING -Os -Wall -fno-common -ffunction-sections \
     -fdata-sections -ffreestanding -fno-builtin -mthumb -mapcs -std=gnu99 -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -MMD -MP")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
     -DDEBUG -DCPU_LPC54114J256BD64_cm4 -DSERIAL_PORT_TYPE_UART=1 -g -O0 -Wall -fno-common -ffunction-sections -fdata-sections -ffreestanding -fno-builtin \
     -mthumb -mapcs -fno-rtti -fno-exceptions -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -MMD -MP")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} \
     -DNDEBUG -DCPU_LPC54114J256BD64_cm4 -DSERIAL_PORT_TYPE_UART=1 -Os -Wall -fno-common -ffunction-sections -fdata-sections -ffreestanding -fno-builtin \
     -mthumb -mapcs -fno-rtti -fno-exceptions -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -MMD -MP")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} \
     -g --specs=nano.specs --specs=nosys.specs -Wall -fno-common -ffunction-sections -fdata-sections -ffreestanding -fno-builtin \
     -mthumb -mapcs -Xlinker --gc-sections -Xlinker -static -Xlinker -z -Xlinker muldefs -Xlinker -Map=output.map \
     -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} \
     --specs=nano.specs --specs=nosys.specs -Wall -fno-common -ffunction-sections -fdata-sections -ffreestanding -fno-builtin \
     -mthumb -mapcs -Xlinker --gc-sections -Xlinker -static -Xlinker -z -Xlinker muldefs -Xlinker -Map=output.map \
     -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16")

include_directories(${ProjDirPath}/../../..)
include_directories(${ProjDirPath}/../../../app/test)
include_directories(${ProjDirPath}/../../../app)
include_directories(${ProjDirPath}/../../../bsp)
include_directories(${ProjDirPath}/../../../CMSIS/Include)
include_directories(${ProjDirPath}/../../../devices)
include_directories(${ProjDirPath}/../../../devices/LPC54114)
include_directories(${ProjDirPath}/../../../devices/LPC54114/drivers)
include_directories(${ProjDirPath}/../../../devices/LPC54114/utilities/str)
include_directories(${ProjDirPath}/../../../devices/LPC54114/utilities/debug_console)
include_directories(${ProjDirPath}/../../../components/uart)
include_directories(${ProjDirPath}/../../../components/serial_manager)
include_directories(${ProjDirPath}/../../../components/lists)
include_directories(${ProjDirPath}/../../../components/sdmmc/sdmmc_2.1.1/inc)
include_directories(${ProjDirPath}/../../../components/mx25r_flash)
include_directories(${ProjDirPath}/../../../components/codec)
include_directories(${ProjDirPath}/../../../components/codec/port)
include_directories(${ProjDirPath}/../../../components/codec/wm8904)
include_directories(${ProjDirPath}/../../../components/codec/i2c)
include_directories(${ProjDirPath}/../../../components/i2c)
include_directories(${ProjDirPath}/../../../middleware/fatfs/source)
include_directories(${ProjDirPath}/../../../middleware/fatfs/source/fsl_sdspi_disk)
include_directories(${ProjDirPath}/../../../middleware/multicore/mcmgr/src)
include_directories(${ProjDirPath}/../../../middleware/mp3lib/mp3pub)
include_directories(${ProjDirPath}/../../../middleware/mp3lib/real)
include_directories(${ProjDirPath}/../../../middleware/aaclib/aacpub)
include_directories(${ProjDirPath}/../../../middleware/aaclib/real)
include_directories(${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/portable/GCC/ARM_CM4F)
include_directories(${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/include)
include_directories(${ProjDirPath}/../../../rtos/amazon-freertos/cli)
include_directories(${ProjDirPath}/../../../rtos/amazon-freertos/cli/port)

add_executable(core0.elf 
    "${ProjDirPath}/../../../app/test/test_cli.c"
    "${ProjDirPath}/../../../app/test/test_audio_play.c"
    "${ProjDirPath}/../../../app/test/test_mp3_decode.c"
    "${ProjDirPath}/../../../app/test/test_aac_decode.c"
    "${ProjDirPath}/../../../app/test/test_fatfs.c"
    "${ProjDirPath}/../../../app/test/test_pct2075.c"
    "${ProjDirPath}/../../../app/test/test_adc.c"
    "${ProjDirPath}/../../../app/test/test_wm8904.c"
    "${ProjDirPath}/../../../app/main_core0.c"
    "${ProjDirPath}/../../../app/FreeRTOSConfig.h"
    "${ProjDirPath}/../../../bsp/bsp_led.c"
    "${ProjDirPath}/../../../bsp/bsp_led.h"
    "${ProjDirPath}/../../../bsp/bsp_dmic.c"
    "${ProjDirPath}/../../../bsp/bsp_dmic.h"
    "${ProjDirPath}/../../../bsp/bsp_systick.c"
    "${ProjDirPath}/../../../bsp/bsp_systick.h"
    "${ProjDirPath}/../../../bsp/bsp_pct2075.c"
    "${ProjDirPath}/../../../bsp/bsp_pct2075.h"
    "${ProjDirPath}/../../../bsp/bsp_adc.c"
    "${ProjDirPath}/../../../bsp/bsp_adc.h"
    "${ProjDirPath}/../../../bsp/bsp_flash.c"
    "${ProjDirPath}/../../../bsp/bsp_flash.h"
    "${ProjDirPath}/../../../bsp/bsp_wm8904.c"
    "${ProjDirPath}/../../../bsp/bsp_wm8904.h"
    "${ProjDirPath}/../../../bsp/bsp_sdspi.c"
    "${ProjDirPath}/../../../bsp/bsp_sdspi.h"
    "${ProjDirPath}/../../../bsp/bsp_key.c"
    "${ProjDirPath}/../../../bsp/bsp_key.h"
    "${ProjDirPath}/../../../bsp/pin_mux.c"
    "${ProjDirPath}/../../../bsp/pin_mux.h"
    "${ProjDirPath}/../../../bsp/clock_config.c"
    "${ProjDirPath}/../../../bsp/clock_config.h"
    "${ProjDirPath}/../../../middleware/fatfs/source/ffunicode.c"
    "${ProjDirPath}/../../../middleware/fatfs/source/ffsystem.c"
    "${ProjDirPath}/../../../middleware/fatfs/source/ff.h"
    "${ProjDirPath}/../../../middleware/fatfs/source/ff.c"
    "${ProjDirPath}/../../../middleware/fatfs/source/diskio.h"
    "${ProjDirPath}/../../../middleware/fatfs/source/diskio.c"
    "${ProjDirPath}/../../../middleware/fatfs/source/fsl_sdspi_disk/fsl_sdspi_disk.c"
    "${ProjDirPath}/../../../middleware/fatfs/source/fsl_sdspi_disk/fsl_sdspi_disk.h"
    "${ProjDirPath}/../../../middleware/multicore/mcmgr/src/mcmgr.c"
    "${ProjDirPath}/../../../middleware/multicore/mcmgr/src/mcmgr.h"
    "${ProjDirPath}/../../../middleware/multicore/mcmgr/src/mcmgr_internal_core_api.h"
    "${ProjDirPath}/../../../middleware/multicore/mcmgr/src/mcmgr_internal_core_api_lpc54114.c"
    "${ProjDirPath}/../../../middleware/mp3lib/mp3dec.c"
    "${ProjDirPath}/../../../middleware/mp3lib/mp3play.c"
    "${ProjDirPath}/../../../middleware/mp3lib/mp3tabs.c"
    "${ProjDirPath}/../../../middleware/mp3lib/real/armgcc/asmmisc.S"
    "${ProjDirPath}/../../../middleware/mp3lib/real/armgcc/asmpoly_thumb2.S"
    "${ProjDirPath}/../../../middleware/mp3lib/real/bitstream.c"
    "${ProjDirPath}/../../../middleware/mp3lib/real/buffers.c"
    "${ProjDirPath}/../../../middleware/mp3lib/real/dct32.c"
    "${ProjDirPath}/../../../middleware/mp3lib/real/dequant.c"
    "${ProjDirPath}/../../../middleware/mp3lib/real/dqchan.c"
    "${ProjDirPath}/../../../middleware/mp3lib/real/huffman.c"
    "${ProjDirPath}/../../../middleware/mp3lib/real/hufftabs.c"
    "${ProjDirPath}/../../../middleware/mp3lib/real/imdct.c"
    "${ProjDirPath}/../../../middleware/mp3lib/real/polyphase.c"
    "${ProjDirPath}/../../../middleware/mp3lib/real/scalfact.c"
    "${ProjDirPath}/../../../middleware/mp3lib/real/stproc.c"
    "${ProjDirPath}/../../../middleware/mp3lib/real/subband.c"
    "${ProjDirPath}/../../../middleware/mp3lib/real/trigtabs.c"
    "${ProjDirPath}/../../../middleware/aaclib/aacdec.c"
    "${ProjDirPath}/../../../middleware/aaclib/aactabs.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/armgcc/sbrcov.S"
    "${ProjDirPath}/../../../middleware/aaclib/real/armgcc/sbrqmfak.S"
    "${ProjDirPath}/../../../middleware/aaclib/real/armgcc/sbrqmfsk.S"
    "${ProjDirPath}/../../../middleware/aaclib/real/bitstream.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/buffers.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/dct4.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/decelmnt.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/dequant.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/fft.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/filefmt.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/huffman.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/hufftabs.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/imdct.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/noiseless.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/pns.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/sbr.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/sbrfft.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/sbrfreq.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/sbrhfadj.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/sbrhfgen.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/sbrhuff.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/sbrimdct.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/sbrmath.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/sbrqmf.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/sbrside.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/sbrtabs.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/stproc.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/tns.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/trigtabs_fltgen.c"
    "${ProjDirPath}/../../../middleware/aaclib/real/trigtabs.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_mailbox.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_iocon.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_reset.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_reset.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_common.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_common.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_clock.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_clock.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_power.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_power.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_dmic.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_dmic.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_spi.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_spi.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_spi_dma.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_spi_dma.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_i2c.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_i2c.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_i2s.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_i2s.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_i2s_dma.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_i2s_dma.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_dma.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_dma.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_adc.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_adc.c"
    "${ProjDirPath}/../../../devices/LPC54114/fsl_device_registers.h"
    "${ProjDirPath}/../../../devices/LPC54114/LPC54114_cm4.h"
    "${ProjDirPath}/../../../devices/LPC54114/LPC54114_cm4_features.h"
    "${ProjDirPath}/../../../devices/LPC54114/system_LPC54114_cm4.c"
    "${ProjDirPath}/../../../devices/LPC54114/system_LPC54114_cm4.h"
    "${ProjDirPath}/../../../devices/LPC54114/gcc/startup_LPC54114_cm4.S"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_usart.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_usart.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_flexcomm.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_flexcomm.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_gpio.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_gpio.c"
    "${ProjDirPath}/../../../devices/LPC54114/utilities/fsl_assert.c"
    "${ProjDirPath}/../../../devices/LPC54114/utilities/str/fsl_str.c"
    "${ProjDirPath}/../../../devices/LPC54114/utilities/str/fsl_str.h"
    "${ProjDirPath}/../../../devices/LPC54114/utilities/fsl_sbrk.c"
    "${ProjDirPath}/../../../devices/LPC54114/utilities/debug_console/fsl_debug_console.c"
    "${ProjDirPath}/../../../devices/LPC54114/utilities/debug_console/fsl_debug_console.h"
    "${ProjDirPath}/../../../devices/LPC54114/utilities/debug_console/fsl_debug_console_conf.h"
    "${ProjDirPath}/../../../components/uart/uart.h"
    "${ProjDirPath}/../../../components/uart/usart_adapter.c"
    "${ProjDirPath}/../../../components/serial_manager/serial_manager.h"
    "${ProjDirPath}/../../../components/serial_manager/serial_manager.c"
    "${ProjDirPath}/../../../components/serial_manager/serial_port_uart.h"
    "${ProjDirPath}/../../../components/serial_manager/serial_port_uart.c"
    "${ProjDirPath}/../../../components/lists/generic_list.h"
    "${ProjDirPath}/../../../components/lists/generic_list.c"
    "${ProjDirPath}/../../../components/sdmmc/sdmmc_2.1.1/src/fsl_sdspi.c"
    "${ProjDirPath}/../../../components/sdmmc/sdmmc_2.1.1/inc/fsl_sdspi.h"
    "${ProjDirPath}/../../../components/mx25r_flash/mx25r_flash.c"
    "${ProjDirPath}/../../../components/mx25r_flash/mx25r_flash.h"
    "${ProjDirPath}/../../../components/codec/fsl_codec_common.c"
    "${ProjDirPath}/../../../components/codec/fsl_codec_common.h"
    "${ProjDirPath}/../../../components/codec/port/fsl_codec_adapter.h"
    "${ProjDirPath}/../../../components/codec/port/wm8904/fsl_codec_adapter.c"
    "${ProjDirPath}/../../../components/codec/wm8904/fsl_wm8904.c"
    "${ProjDirPath}/../../../components/codec/wm8904/fsl_wm8904.h"
    "${ProjDirPath}/../../../components/codec/i2c/fsl_codec_i2c.c"
    "${ProjDirPath}/../../../components/codec/i2c/fsl_codec_i2c.h"
    "${ProjDirPath}/../../../components/i2c/flexcomm_i2c_adapter.c"
    "${ProjDirPath}/../../../components/i2c/i2c.h"
    "${ProjDirPath}/../../../CMSIS/Include/core_cm4.h"
    "${ProjDirPath}/../../../CMSIS/Include/cmsis_armcc.h"
    "${ProjDirPath}/../../../CMSIS/Include/cmsis_armclang.h"
    "${ProjDirPath}/../../../CMSIS/Include/cmsis_gcc.h"
    "${ProjDirPath}/../../../CMSIS/Include/cmsis_compiler.h"
    "${ProjDirPath}/../../../CMSIS/Include/cmsis_version.h"
    "${ProjDirPath}/../../../CMSIS/Include/mpu_armv7.h"
    "${ProjDirPath}/../../../CMSIS/Include/core_armv8mbl.h"
    "${ProjDirPath}/../../../CMSIS/Include/core_armv8mml.h"
    "${ProjDirPath}/../../../CMSIS/Include/arm_common_tables.h"
    "${ProjDirPath}/../../../CMSIS/Include/arm_const_structs.h"
    "${ProjDirPath}/../../../CMSIS/Include/arm_math.h"
    "${ProjDirPath}/../../../CMSIS/Include/cmsis_iccarm.h"
    "${ProjDirPath}/../../../CMSIS/Include/mpu_armv8.h"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/portable/MemMang/heap_4.c"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/include/event_groups.h"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/include/FreeRTOS.h"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/include/message_buffer.h"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/include/queue.h"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/include/semphr.h"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/include/stream_buffer.h"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/include/task.h"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/include/timers.h"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/include/freertos_tasks_c_additions.h"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/event_groups.c"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/list.c"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/queue.c"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/stream_buffer.c"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/tasks.c"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/timers.c"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/portable/GCC/ARM_CM4F/port.c"
    "${ProjDirPath}/../../../rtos/amazon-freertos/freertos_kernel/portable/GCC/ARM_CM4F/portmacro.h"
    "${ProjDirPath}/../../../rtos/amazon-freertos/cli/FreeRTOS_CLI.c"
    "${ProjDirPath}/../../../rtos/amazon-freertos/cli/FreeRTOS_CLI.h"
    "${ProjDirPath}/../../../rtos/amazon-freertos/cli/UARTCommandConsole.c"
    "${ProjDirPath}/../../../rtos/amazon-freertos/cli/UARTCommandConsole.h"
    "${ProjDirPath}/../../../rtos/amazon-freertos/cli/port/serial.c"
    "${ProjDirPath}/../../../rtos/amazon-freertos/cli/port/serial.h"
)


set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -T${ProjDirPath}/LPC54114J256_cm4_ram.ld -static")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -T${ProjDirPath}/LPC54114J256_cm4_ram.ld -static")

TARGET_LINK_LIBRARIES(core0.elf -Wl,--start-group)
target_link_libraries(core0.elf debug m)
target_link_libraries(core0.elf debug c)
target_link_libraries(core0.elf debug gcc)
target_link_libraries(core0.elf debug nosys)
target_link_libraries(core0.elf optimized m)
target_link_libraries(core0.elf optimized c)
target_link_libraries(core0.elf optimized gcc)
target_link_libraries(core0.elf optimized nosys)

link_directories(${ProjDirPath}/../../../devices/LPC54114/gcc)
target_link_libraries(core0.elf debug ${ProjDirPath}/../../../devices/LPC54114/gcc/libpower_cm4_hardabi.a)

link_directories(${ProjDirPath}/../../../devices/LPC54114/gcc)
target_link_libraries(core0.elf optimized ${ProjDirPath}/../../../devices/LPC54114/gcc/libpower_cm4_hardabi.a)

TARGET_LINK_LIBRARIES(core0.elf -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET core0.elf POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/core0.elf ${EXECUTABLE_OUTPUT_PATH}/core0_image.bin)
