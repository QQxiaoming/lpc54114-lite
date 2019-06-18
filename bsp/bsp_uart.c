/**
 * @file bsp_uart.c
 * @author qiaoqiming
 * @brief 串口初始化
 * @version 1.0
 * @date 2019-04-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdint.h>

#include "fsl_common.h"
#include "fsl_debug_console.h"

#include "clock_config.h"
#include "bsp_uart.h"

/**
 * @brief 初始化调试串口
 * 
 * @return status_t 
 */
status_t debug_console_init(void)
{
    status_t result;
    
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM0);
    RESET_PeripheralReset(kFC0_RST_SHIFT_RSTn);
    result = DbgConsole_Init(0U, 115200, kSerialPort_Uart,CLOCK_GetFreq(kCLOCK_Flexcomm0));

    return result;
}
