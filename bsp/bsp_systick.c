/**
 * @file bsp_systick.c
 * @author 
 * @brief 
 * @version 0.1
 * @date 2019-04-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "bsp_systick.h"
#include "fsl_common.h"
#include "clock_config.h"

volatile uint32_t dwSysTicks = 0;


#ifndef FSL_RTOS_FREE_RTOS
void systick_init(void)
{
    SysTick_Config(SystemCoreClock/1000);
}

void SysTick_Handler(void)
{
	dwSysTicks++;
}

#else
void systick_init(void)
{
}

void vApplicationTickHook(void)
{
	dwSysTicks++;
}
#endif