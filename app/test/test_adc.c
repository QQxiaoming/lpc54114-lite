/**
 * @file test_adc.c
 * @author qiaoqiming
 * @brief adc测试
 * @version 1.0
 * @date 2019-05-25
 */
#include "bsp_adc.h"
#include "fsl_debug_console.h"
#include "UARTCommandConsole.h"


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


/**
 * @brief adc示例
 * 
 */
void test_adc(void)
{
    uint16_t wADCValue = 0;

    for(;;)
    {
        /* 触发并读取一次adc数据 */
        wADCValue = adc_read(ADC_CHANNEL_NUM);
        if(wADCValue != 0xFFFF)
        {
            /* 打印adc值 */
            printfk("adc Value is %d\r\n", wADCValue);
        }
        delay();
    }
}