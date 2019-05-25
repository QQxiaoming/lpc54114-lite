/**
 * @file main_core0.c
 * @author qiaoqiming
 * @brief M4核主函数
 * @version 1.0
 * @date 2019-04-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_debug_console.h"

#include "mcmgr.h"
#include "ff.h"
#include "diskio.h"

#include "board.h"
#include "bsp_led.h"
#include "bsp_dmic.h"
#include "bsp_flash.h"
#include "bsp_wm8904.h"
#include "bsp_systick.h"
#include "bsp_pct2075.h"
#include "bsp_adc.h"
#include "pin_mux.h"

#include "start_core1.h"

#include "test.h"


/**
 * @brief 系统初始化钩子函数
 * 
 */
void SystemInitHook(void)
{
    NVIC_SetPriorityGrouping(4);

    /* 初始化多核管理器系统，完成后才可调用MCMGR_Init */
    MCMGR_EarlyInit();
}


/**
 * @brief 主函数
 * 
 * @return int 
 */
int main(void)
{
    /* 初始化MCMGR（多核管理系统） */
    MCMGR_Init();

    /* 初始化时钟 */
    BOARD_BootClockFROHF96M();
    systick_init();

    /* 配置引脚功能*/
    BOARD_InitPins_Core0();
    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);
    
    /* 初始化debug串口 */
    BOARD_InitDebugConsole();
    PRINTF("Debug Console Init Successful!\r\n");

#ifdef CORE1_IMAGE_COPY_TO_RAM
    /* 拷贝从核数据到从核启动ram,使用MCUXpresso IDE不需要拷贝 */
    copy_core1_image_to_ram();
#endif

    /* 初始化LED */
    LEDInit();
    LED7_ON();
    
    /* 使能DMA */
    DMA_Init(DMA0);
    NVIC_SetPriority(DMA0_IRQn, 2);

    /* adc 初始化 */
    adc_init();

    /* flash 初始化 */
    spiflash_init();

    /* dmic初始化 */
    dmic_init();

    /* codec初始化 */
    wm8904_i2s_init();

#ifdef CORE1_IMAGE_COPY_TO_RAM
	/* 启动m0核心 */
	start_core1();
#endif

    /* 播放任务创建 */
    audio_play_init();

    vTaskStartScheduler();
    for (;;);
}
