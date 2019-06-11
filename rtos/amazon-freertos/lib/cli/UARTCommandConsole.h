/**
 * @file UARTCommandConsole.h
 * @author qiaoqiming
 * @brief 
 * @version 1.0
 * @date 2019-06-4
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _UART_COMMAND_CONSOLE_H_
#define _UART_COMMAND_CONSOLE_H_

#include "serial.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#define printfk(fmt, ...)                                                               \
	do                                                                                  \
	{                                                                                   \
		extern const char *const pcEndOfOutputMessage;                                  \
		DbgConsole_Printf("\r\033[K"fmt"%s", ##__VA_ARGS__, pcEndOfOutputMessage + 2);  \
	} while (0)

void vUARTCommandConsoleInit( void );
void vUARTCommandConsoleStart( uint16_t usStackSize, UBaseType_t uxPriority );

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _UART_COMMAND_CONSOLE_H_ */
