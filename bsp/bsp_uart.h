/**
 * @file bsp_uart.h
 * @author qiaoqiming
 * @brief 串口初始化
 * @version 1.0
 * @date 2019-04-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#include "fsl_common.h"
#include "serial.h"


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */


status_t debug_console_init(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BSP_UART_H_ */
