/**
 * @file bsp_uart.c
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
"C" {
#endif /* __cplusplus */

#define printfk(fmt, args...)                                         \
	do                                                                \
	{                                                                 \
		extern const char *const pcEndOfOutputMessage;                \
		int index = strlen(pcEndOfOutputMessage) - 11;                \
		for (int i = index; i > 0; i--)                               \
		{                                                             \
			DbgConsole_Putchar('\b');                                 \
		}                                                             \
		for (int i = index; i > 0; i--)                               \
		{                                                             \
			DbgConsole_Putchar(' ');                                  \
		}                                                             \
		for (int i = index; i > 0; i--)                               \
		{                                                             \
			DbgConsole_Putchar('\b');                                 \
		}                                                             \
		DbgConsole_Printf(fmt, ##args);                               \
		DbgConsole_Printf(pcEndOfOutputMessage + 2); \
	} while (0)

void vUARTCommandConsoleInit( void );
void vUARTCommandConsoleStart( uint16_t usStackSize, UBaseType_t uxPriority );

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _UART_COMMAND_CONSOLE_H_ */
