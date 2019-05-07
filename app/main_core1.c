/**
 * @file main_core1.c
 * @author qiaoqiming
 * @brief M0+核主函数
 * @version 1.0
 * @date 2019-04-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "fsl_common.h"
#include "fsl_gpio.h"

#include "mcmgr.h"

#include "board.h"
#include "bsp_led.h"
#include "pin_mux.h"


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
    /* Initialize MCMGR - low level multicore management library. Call this
       function as close to the reset entry as possible to allow CoreUp event
       triggering. The SystemInitHook() weak function overloading is used in this
       application. */
    MCMGR_EarlyInit();
}


/**
 * @brief 主函数
 * 
 * @return int 
 */
int main(void)
{
    mcmgr_status_t status;
    uint32_t startupData, i;

    /* 初始化MCMGR（多核管理系统） */
    MCMGR_Init();

    /* 获取启动数据这里是5，注意：这个函数只在m0+核上使用 */
    do
    {
        status = MCMGR_GetStartupData(&startupData);
    } while (status != kStatus_MCMGR_Success);

    /* 延时一定的时间，这里使用获取到的启动参数 */
    for (i = 0; i < startupData; i++)
	{
        delay();
	}

    while (1)
    {
    	LED11_TOGGLE();

		/* 延时一段时间 */
		delay();
    }
}
