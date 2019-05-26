/**
 * @file bsp_key.h
 * @author qiaoqiming
 * @brief 按键初始化
 * @version 1.0
 * @date 2019-05-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "fsl_common.h"
#include "fsl_gpio.h"



#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */


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



#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BSP_KEY_H_ */
