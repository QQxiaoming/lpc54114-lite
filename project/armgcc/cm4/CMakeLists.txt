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
     -mthumb -mapcs -std=gnu99 -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} \
     -DNDEBUG -D__STARTUP_CLEAR_BSS -Wall -fno-common -ffunction-sections -fdata-sections -ffreestanding -fno-builtin \
     -mthumb -mapcs -std=gnu99 -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} \
     -DDEBUG -DCORE1_IMAGE_COPY_TO_RAM -DCPU_LPC54114J256BD64_cm4 -DMCMGR_HANDLE_EXCEPTIONS=1 -D__SEMIHOST_HARDFAULT_DISABLE=1 \
     -DMULTICORE_APP=1 -g -O0 -Wall -fno-common -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mthumb \
     -mapcs -std=gnu99 -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -MMD -MP")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} \
     -DNDEBUG -DCORE1_IMAGE_COPY_TO_RAM -DCPU_LPC54114J256BD64_cm4 -DMCMGR_HANDLE_EXCEPTIONS=1 -D__SEMIHOST_HARDFAULT_DISABLE=1 \
     -DMULTICORE_APP=1 -Os -Wall -fno-common -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mthumb \
     -mapcs -std=gnu99 -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -MMD -MP")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
     -DDEBUG -DCPU_LPC54114J256BD64_cm4 -g -O0 -Wall -fno-common -ffunction-sections -fdata-sections -ffreestanding -fno-builtin \
     -mthumb -mapcs -fno-rtti -fno-exceptions -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -MMD -MP")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} \
     -DNDEBUG -DCPU_LPC54114J256BD64_cm4 -Os -Wall -fno-common -ffunction-sections -fdata-sections -ffreestanding -fno-builtin \
     -mthumb -mapcs -fno-rtti -fno-exceptions -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -MMD -MP")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} \
     -g --specs=nano.specs --specs=nosys.specs -Wall -fno-common -ffunction-sections -fdata-sections -ffreestanding -fno-builtin \
     -mthumb -mapcs -Xlinker --gc-sections -Xlinker -static -Xlinker -z -Xlinker muldefs -Xlinker -Map=output.map \
     -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} \
     --specs=nano.specs --specs=nosys.specs -Wall -fno-common -ffunction-sections -fdata-sections -ffreestanding -fno-builtin \
     -mthumb -mapcs -Xlinker --gc-sections -Xlinker -static -Xlinker -z -Xlinker muldefs -Xlinker -Map=output.map \
     -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16")

if(CMAKE_BUILD_TYPE STREQUAL debug)
include_directories(${ProjDirPath}/../cm0plus/debug)
endif(CMAKE_BUILD_TYPE STREQUAL debug)

if(CMAKE_BUILD_TYPE STREQUAL release)
include_directories(${ProjDirPath}/../cm0plus/release)
endif(CMAKE_BUILD_TYPE STREQUAL release)

include_directories(${ProjDirPath}/../../..)
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
include_directories(${ProjDirPath}/../../../middleware/multicore/mcmgr/src)

add_executable(core0.elf 
    "${ProjDirPath}/../../../app/main_core0.c"
    "${ProjDirPath}/../../../app/start_core1.c"
    "${ProjDirPath}/../../../app/start_core1.h"
    "${ProjDirPath}/../../../app/incbin.S"
    "${ProjDirPath}/../../../bsp/bsp_led.c"
    "${ProjDirPath}/../../../bsp/bsp_led.h"
    "${ProjDirPath}/../../../bsp/pin_mux.c"
    "${ProjDirPath}/../../../bsp/pin_mux.h"
    "${ProjDirPath}/../../../bsp/board.c"
    "${ProjDirPath}/../../../bsp/board.h"
    "${ProjDirPath}/../../../bsp/clock_config.c"
    "${ProjDirPath}/../../../bsp/clock_config.h"
    "${ProjDirPath}/../../../middleware/multicore/mcmgr/src/mcmgr.c"
    "${ProjDirPath}/../../../middleware/multicore/mcmgr/src/mcmgr.h"
    "${ProjDirPath}/../../../middleware/multicore/mcmgr/src/mcmgr_internal_core_api.h"
    "${ProjDirPath}/../../../middleware/multicore/mcmgr/src/mcmgr_internal_core_api_lpc54114.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_mailbox.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_iocon.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_reset.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_reset.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_reset.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_reset.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_iocon.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_common.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_common.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_clock.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_clock.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_power.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_power.c"
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
)


set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -T${ProjDirPath}/LPC54114J256_cm4_flash.ld -static")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -T${ProjDirPath}/LPC54114J256_cm4_flash.ld -static")

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
