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
#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_debug_console.h"

#include "mcmgr.h"

#include "board.h"
#include "bsp_led.h"
#include "pin_mux.h"

#include "start_core1.h"


/**
 * @brief 粗略延时
 * 
 */
void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 1000000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}


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
 * @brief 主函数
 * 
 * @return int 
 */
int main(void)
{
    /* 初始化MCMGR（多核管理系统） */
    MCMGR_Init();

    /* 初始化时钟 */
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM0);

    /* 配置引脚功能*/
    BOARD_InitPins_Core0();

    BOARD_BootClockFROHF48M();
    BOARD_InitDebugConsole();

    PRINTF("Debug Console Init Successful!\r\n");

#ifdef CORE1_IMAGE_COPY_TO_RAM
    /* 拷贝从核数据到从核启动ram,使用MCUXpresso IDE不需要拷贝 */
	copy_core1_image_to_ram();
#endif

#if 0
	/* 启动m0核心 */
	start_core1();
    
    while (1)
    {
    }
#else

    /* 初始化LED */
	LEDInit();
	LED4_ON();

	PRINTF("LED Init Successful!\r\n");
	while (1)
	{
		/* 延时一段时间 */
		delay();
		PRINTF("LED!\r\n");
	}
#endif
}
