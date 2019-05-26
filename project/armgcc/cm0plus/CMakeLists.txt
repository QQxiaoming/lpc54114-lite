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
     -DDEBUG -DDONT_ENABLE_DISABLED_RAMBANKS -D__STARTUP_CLEAR_BSS -DSLAVEBOOT -DNO_CRP -g -Wall -fno-common -ffunction-sections \
     -fdata-sections -ffreestanding -fno-builtin -mthumb -mapcs -std=gnu99 -mcpu=cortex-m0plus -mfloat-abi=soft")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} \
     -DNDEBUG -DDONT_ENABLE_DISABLED_RAMBANKS -D__STARTUP_CLEAR_BSS -DSLAVEBOOT -DNO_CRP -Wall -fno-common -ffunction-sections \
     -fdata-sections -ffreestanding -fno-builtin -mthumb -mapcs -std=gnu99 -mcpu=cortex-m0plus -mfloat-abi=soft")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} \
     -DDEBUG -DCPU_LPC54114J256BD64_cm0plus -DMCMGR_HANDLE_EXCEPTIONS=1 -D__SEMIHOST_HARDFAULT_DISABLE=1 \
     -DMULTICORE_APP=1 -g -O0 -Wall -fno-common -ffunction-sections -fdata-sections -ffreestanding -fno-builtin \
     -mthumb -mapcs -std=gnu99 -mcpu=cortex-m0plus -mfloat-abi=soft -MMD -MP")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} \
     -DNDEBUG -DCPU_LPC54114J256BD64_cm0plus -DMCMGR_HANDLE_EXCEPTIONS=1 -D__SEMIHOST_HARDFAULT_DISABLE=1 \
     -DMULTICORE_APP=1 -Os -Wall -fno-common -ffunction-sections -fdata-sections -ffreestanding -fno-builtin \
     -mthumb -mapcs -std=gnu99 -mcpu=cortex-m0plus -mfloat-abi=soft -MMD -MP")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
     -DDEBUG -DCPU_LPC54114J256BD64_cm0plus -g -O0 -Wall -fno-common -ffunction-sections -fdata-sections \
      -ffreestanding -fno-builtin -mthumb -mapcs -fno-rtti -fno-exceptions -mcpu=cortex-m0plus -mfloat-abi=soft \
      -MMD -MP")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} \
     -DNDEBUG -DCPU_LPC54114J256BD64_cm0plus -Os -Wall -fno-common -ffunction-sections -fdata-sections \
     -ffreestanding -fno-builtin -mthumb -mapcs -fno-rtti -fno-exceptions -mcpu=cortex-m0plus -mfloat-abi=soft \
     -MMD -MP")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} \
     -g --specs=nano.specs --specs=nosys.specs -Wall -fno-common -ffunction-sections -fdata-sections \
     -ffreestanding -fno-builtin -mthumb -mapcs -Xlinker --gc-sections -Xlinker -static -Xlinker -z -Xlinker muldefs \
     -Xlinker -Map=output.map -mcpu=cortex-m0plus -mfloat-abi=soft")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} \
     --specs=nano.specs --specs=nosys.specs -Wall -fno-common -ffunction-sections -fdata-sections -ffreestanding \
     -fno-builtin -mthumb -mapcs -Xlinker --gc-sections -Xlinker -static -Xlinker -z -Xlinker muldefs \
     -Xlinker -Map=output.map -mcpu=cortex-m0plus -mfloat-abi=soft")

include_directories(${ProjDirPath}/../../..)
include_directories(${ProjDirPath}/../../../app)
include_directories(${ProjDirPath}/../../../bsp)
include_directories(${ProjDirPath}/../../../CMSIS/Include)
include_directories(${ProjDirPath}/../../../devices)
include_directories(${ProjDirPath}/../../../devices/LPC54114)
include_directories(${ProjDirPath}/../../../devices/LPC54114/drivers)
include_directories(${ProjDirPath}/../../../middleware/multicore/mcmgr/src)
include_directories(${ProjDirPath}/../../../devices/LPC54114/utilities/str)
include_directories(${ProjDirPath}/../../../devices/LPC54114/utilities/debug_console)
include_directories(${ProjDirPath}/../../../components/uart)
include_directories(${ProjDirPath}/../../../components/serial_manager)
include_directories(${ProjDirPath}/../../../components/lists)

add_executable(core1.elf 
    "${ProjDirPath}/../../../app/main_core1.c"
    "${ProjDirPath}/../../../bsp/bsp_led.c"
    "${ProjDirPath}/../../../bsp/bsp_led.h"
    "${ProjDirPath}/../../../bsp/pin_mux.c"
    "${ProjDirPath}/../../../bsp/pin_mux.h"
    "${ProjDirPath}/../../../bsp/clock_config.c"
    "${ProjDirPath}/../../../bsp/clock_config.h"
    "${ProjDirPath}/../../../middleware/multicore/mcmgr/src/mcmgr_internal_core_api_lpc54114.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_mailbox.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_gpio.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_gpio.c"
    "${ProjDirPath}/../../../middleware/multicore/mcmgr/src/mcmgr.h"
    "${ProjDirPath}/../../../middleware/multicore/mcmgr/src/mcmgr_internal_core_api.h"
    "${ProjDirPath}/../../../middleware/multicore/mcmgr/src/mcmgr.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_iocon.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_common.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_common.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_clock.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_clock.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_power.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_power.c"
    "${ProjDirPath}/../../../devices/LPC54114/fsl_device_registers.h"
    "${ProjDirPath}/../../../devices/LPC54114/LPC54114_cm0plus.h"
    "${ProjDirPath}/../../../devices/LPC54114/LPC54114_cm0plus_features.h"
    "${ProjDirPath}/../../../devices/LPC54114/system_LPC54114_cm0plus.c"
    "${ProjDirPath}/../../../devices/LPC54114/system_LPC54114_cm0plus.h"
    "${ProjDirPath}/../../../devices/LPC54114/gcc/startup_LPC54114_cm0plus.S"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_usart.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_usart.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_flexcomm.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_flexcomm.c"
    "${ProjDirPath}/../../../devices/LPC54114/utilities/str/fsl_str.c"
    "${ProjDirPath}/../../../devices/LPC54114/utilities/str/fsl_str.h"
    "${ProjDirPath}/../../../devices/LPC54114/utilities/debug_console/fsl_debug_console.c"
    "${ProjDirPath}/../../../devices/LPC54114/utilities/debug_console/fsl_debug_console.h"
    "${ProjDirPath}/../../../devices/LPC54114/utilities/debug_console/fsl_debug_console_conf.h"
    "${ProjDirPath}/../../../devices/LPC54114/utilities/fsl_assert.c"
    "${ProjDirPath}/../../../components/uart/uart.h"
    "${ProjDirPath}/../../../components/uart/usart_adapter.c"
    "${ProjDirPath}/../../../components/serial_manager/serial_manager.h"
    "${ProjDirPath}/../../../components/serial_manager/serial_manager.c"
    "${ProjDirPath}/../../../components/serial_manager/serial_port_uart.h"
    "${ProjDirPath}/../../../components/serial_manager/serial_port_uart.c"
    "${ProjDirPath}/../../../components/lists/generic_list.h"
    "${ProjDirPath}/../../../components/lists/generic_list.c"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_reset.h"
    "${ProjDirPath}/../../../devices/LPC54114/drivers/fsl_reset.c"
    "${ProjDirPath}/../../../CMSIS/Include/core_cm0plus.h"
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

set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -T${ProjDirPath}/LPC54114J256_cm0plus_flash.ld -static")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -T${ProjDirPath}/LPC54114J256_cm0plus_flash.ld -static")

TARGET_LINK_LIBRARIES(core1.elf -Wl,--start-group)
target_link_libraries(core1.elf debug m)
target_link_libraries(core1.elf debug c)
target_link_libraries(core1.elf debug gcc)
target_link_libraries(core1.elf debug nosys)
target_link_libraries(core1.elf optimized m)
target_link_libraries(core1.elf optimized c)
target_link_libraries(core1.elf optimized gcc)
target_link_libraries(core1.elf optimized nosys)

link_directories(${ProjDirPath}/../../../devices/LPC54114/gcc)
target_link_libraries(core1.elf debug ${ProjDirPath}/../../../devices/LPC54114/gcc/libpower_cm0.a)

link_directories(${ProjDirPath}/../../../devices/LPC54114/gcc)
target_link_libraries(core1.elf optimized ${ProjDirPath}/../../../devices/LPC54114/gcc/libpower_cm0.a)

TARGET_LINK_LIBRARIES(core1.elf -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET core1.elf POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/core1.elf ${EXECUTABLE_OUTPUT_PATH}/core1_image.bin)
