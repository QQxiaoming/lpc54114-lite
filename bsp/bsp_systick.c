/**
 * @file bsp_systick.c
 * @author qiaoqiming
 * @brief systick初始化
 * @version 1.0
 * @date 2019-04-16
 */
#include "bsp_systick.h"
#include "fsl_common.h"
#include "clock_config.h"
#include "FreeRTOS.h"

volatile uint32_t dwSysTicks = 0;


#ifndef FSL_RTOS_FREE_RTOS
status_t systick_init(void)
{
    SysTick_Config(SystemCoreClock/1000);
	return kStatus_Success;
}

void SysTick_Handler(void)
{
	dwSysTicks++;
}

#else
status_t systick_init(void)
{
	return kStatus_Success;
}

void vApplicationTickHook(void)
{
	dwSysTicks += (1000/configTICK_RATE_HZ);
}
#endif
