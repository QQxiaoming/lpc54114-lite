/**
 * @file board.c
 * @author qiaoqiming
 * @brief 板级初始化
 * @version 0.1
 * @date 2019-04-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdint.h>

#include "fsl_common.h"
#include "fsl_debug_console.h"

#include "clock_config.h"
#include "board.h"

/**
 * @brief 初始化调试串口
 * 
 * @return status_t 
 */
status_t BOARD_InitDebugConsole(void)
{
    status_t result;
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);
    RESET_PeripheralReset(BOARD_DEBUG_UART_RST);
    result = DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE,
                             BOARD_DEBUG_UART_CLK_FREQ);
    assert(kStatus_Success == result);
    return result;
}
