/**
 * @file start_core1.c
 * @author qiaoqiming
 * @brief 
 * @version 1.0
 * @date 2019-04-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "fsl_debug_console.h"

#include "board.h"
#include "mcmgr.h"

#include "start_core1.h"

/* Address of RAM, where the image for core1 should be copied */
#define CORE1_BOOT_ADDRESS (void *)0x20010000

#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
extern uint32_t Image$$CORE1_REGION$$Base;
extern uint32_t Image$$CORE1_REGION$$Length;
#define CORE1_IMAGE_START &Image$$CORE1_REGION$$Base
#elif defined(__ICCARM__)
extern unsigned char core1_image_start[];
#define CORE1_IMAGE_START core1_image_start
#elif defined(__GNUC__)
extern const char m0_image_start[];
extern const char *m0_image_end;
extern int m0_image_size;
#define CORE1_IMAGE_START ((void *)m0_image_start)
#define CORE1_IMAGE_SIZE ((void *)m0_image_size)
#endif


static uint32_t get_core1_image_size(void)
{
    uint32_t core1_image_size;
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
    core1_image_size = (uint32_t)&Image$$CORE1_REGION$$Length;
#elif defined(__ICCARM__)
#pragma section = "__sec_core"
    core1_image_size = (uint32_t)__section_end("__sec_core") - (uint32_t)&core1_image_start;
#elif defined(__GNUC__)
    core1_image_size = (uint32_t)m0_image_size;
#endif
    return core1_image_size;
}


void copy_core1_image_to_ram(void)
{
    uint32_t core1_image_size;
    core1_image_size = get_core1_image_size();
    PRINTF("Copy Secondary core image to address: 0x%x, size: %d\r\n", CORE1_BOOT_ADDRESS, core1_image_size);

    /* Copy Secondary core application from FLASH to the target memory. */
    memcpy(CORE1_BOOT_ADDRESS, (void *)CORE1_IMAGE_START, core1_image_size);
}

void start_core1(void)
{
    PRINTF("Starting Secondary core.\r\n");
    /* 启动m0+核，启动参数5传递给m0+核使用 */
    MCMGR_StartCore(kMCMGR_Core1, CORE1_BOOT_ADDRESS, 5, kMCMGR_Start_Synchronous);
    PRINTF("The secondary core application has been started.\r\n");
}
