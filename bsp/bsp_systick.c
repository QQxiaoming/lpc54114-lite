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


void vApplicationTickHook(void)
{
	dwSysTicks++;
}
/*
void systick_init(void)
{
    SysTick_Config(SystemCoreClock/1000);
}
*/