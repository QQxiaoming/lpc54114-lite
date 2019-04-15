/**
 * @file board.h
 * @author qiaoqiming
 * @brief 
 * @version 0.1
 * @date 2019-04-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#include "fsl_common.h"
#include "fsl_gpio.h"

#include "clock_config.h"


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief 板级名称 */
#define BOARD_NAME "LPCXPRESSO54114"


/*! @brief 调试串口配置 */
#define BOARD_DEBUG_SPI_CLK_FREQ   12000000

#define BOARD_DEBUG_UART_BAUDRATE           115200
#define BOARD_DEBUG_UART_TYPE               kSerialPort_Uart
#define BOARD_DEBUG_UART_BASEADDR           (uint32_t) USART0
#define BOARD_DEBUG_UART_INSTANCE           0U
#define BOARD_DEBUG_UART_CLK_FREQ           CLOCK_GetFreq(kCLOCK_Flexcomm0)
#define BOARD_DEBUG_UART_CLK_ATTACH         kFRO12M_to_FLEXCOMM0
#define BOARD_DEBUG_UART_RST                kFC0_RST_SHIFT_RSTn
#define BOARD_UART_IRQ                      FLEXCOMM0_IRQn
#define BOARD_UART_IRQ_HANDLER              FLEXCOMM0_IRQHandler

#define BOARD_DEBUG_UART_BAUDRATE_CORE1     115200
#define BOARD_DEBUG_UART_TYPE_CORE1         kSerialPort_Uart
#define BOARD_DEBUG_UART_BASEADDR_CORE1     (uint32_t) USART2
#define BOARD_DEBUG_UART_INSTANCE_CORE1     2U
#define BOARD_DEBUG_UART_CLK_FREQ_CORE1     CLOCK_GetFreq(kCLOCK_Flexcomm2)
#define BOARD_DEBUG_UART_CLK_ATTACH_CORE1   kFRO12M_to_FLEXCOMM2
#define BOARD_DEBUG_UART_RST_CORE1          kFC2_RST_SHIFT_RSTn
#define BOARD_UART_IRQ_CORE1                FLEXCOMM2_IRQn
#define BOARD_UART_IRQ_HANDLER_CORE1        FLEXCOMM2_IRQHandler


/* 按键引脚定义 */
#define BOARD_SW1_GPIO      GPIO
#define BOARD_SW1_GPIO_PORT 1U
#define BOARD_SW1_GPIO_PIN  8U
#define BOARD_SW1_NAME      "SW1"


#define BOARD_SW2_GPIO      GPIO
#define BOARD_SW2_GPIO_PORT 1U
#define BOARD_SW2_GPIO_PIN  9U
#define BOARD_SW2_NAME      "SW2"


#define BOARD_SW3_GPIO      GPIO
#define BOARD_SW3_GPIO_PORT 1U
#define BOARD_SW3_GPIO_PIN  10U
#define BOARD_SW3_NAME      "SW3"

#define BOARD_SW4_GPIO      GPIO
#define BOARD_SW4_GPIO_PORT 1U
#define BOARD_SW4_GPIO_PIN  11U
#define BOARD_SW4_NAME      "SW4"



#define BOARD_SW4_IRQ               PIN_INT1_IRQn
#define BOARD_SW4_IRQ_HANDLER       PIN_INT1_IRQHandler
#define BOARD_SW4_GPIO_PININT_INDEX 11

#define BOARD_ARDUINO_INT_IRQ       (GINT0_IRQn)
#define BOARD_ARDUINO_I2C_IRQ       (FLEXCOMM4_IRQn)
#define BOARD_ARDUINO_I2C_INDEX     (4)

#define BOARD_CODEC_I2C_BASEADDR    I2C4
#define BOARD_CODEC_I2C_CLOCK_FREQ  12000000



/*******************************************************************************
 * API
 ******************************************************************************/

status_t BOARD_InitDebugConsole(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
