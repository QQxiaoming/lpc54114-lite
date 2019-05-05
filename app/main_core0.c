/**
 * @file main_core0.c
 * @author qiaoqiming
 * @brief 
 * @version 0.1
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
#include "pin_mux.h"

#include "start_core1.h"

static FATFS g_fileSystem; /* File system object */
const TCHAR driverNumberBuffer[3U] = {SDSPIDISK + '0', ':', '/'};

/**
 * @brief 系统初始化钩子函数
 * 
 */
void SystemInitHook(void)
{
    /* 初始化多核管理器系统，完成后才可调用MCMGR_Init */
    MCMGR_EarlyInit();
}


/**
 * @brief 测试任务
 * 
 * @param pvParameters 
 */
static void hello_task(void *pvParameters)
{
    for (;;)
    {
        PRINTF("Hello world.\r\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
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
    BOARD_BootClockFROHF48M();

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

    /* spisd文件系统初始化 */
    f_mount(&g_fileSystem, driverNumberBuffer, 1);

    /* flash 初始化 */
    spiflash_init();

    /* dmic初始化 */
    dmic_init();

    /* codec初始化 */
    wm8904_i2s_init();


    if (xTaskCreate(hello_task, "Hello_task", configMINIMAL_STACK_SIZE + 10, NULL, 3, NULL) != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1);
    }

#ifdef CORE1_IMAGE_COPY_TO_RAM
	/* 启动m0核心 */
	//start_core1();
#endif

    vTaskStartScheduler();
    for (;;);
}