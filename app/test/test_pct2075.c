/**
 * @file test_pct2075..c
 * @author qiaoqiming
 * @brief pct2075传感器测试
 * @version 1.0
 * @date 2019-05-25
 */
#include "bsp_pct2075.h"
#include "fsl_debug_console.h"
#include "assert.h"
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
 * @brief pct2075温湿度传感测试示例
 * 
 */
void test_pct2075(void)
{
    status_t result = kStatus_Fail;
    volatile float fPCTValue;

    (void)result;
    
    for(;;)
    {
        /* 通过i2c读取pct2075温度数据 */
        result = pct2075_i2c_read((float *)&fPCTValue);
        assert(result == kStatus_Success);
        /* 根据结果计算温湿度并计算 */
        if(fPCTValue>=0)
        {
            printfk("Temperature Value is +%d.%d oC.\r\n", (int)(fPCTValue*100)/100, (int)(fPCTValue*100)%100);
        }
        else
        {
            printfk("Temperature Value is -%d.%d oC.\r\n", (int)((0-fPCTValue)*100)/100, (int)((0-fPCTValue)*100)%100);
        }
        delay();
    }
}