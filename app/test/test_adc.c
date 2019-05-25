/**
 * @file test_adc.c
 * @author qiaoqiming
 * @brief adc测试
 * @version 1.0
 * @date 2019-05-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "bsp_adc.h"
#include "fsl_debug_console.h"


/**
 * @brief 粗略延时
 * 
 */
static void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 2000000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}


void test_adc(void)
{
    uint16_t wADCValue = 0;

    for(;;)
    {
        wADCValue = adc_read(ADC_CHANNEL_NUM);
        if(wADCValue != 0xFFFF)
        {
            PRINTF("adc Value is %d\r\n", wADCValue);
        }
        delay();
    }
}