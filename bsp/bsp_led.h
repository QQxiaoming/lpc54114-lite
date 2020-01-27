/**
 * @file bsp_led.h
 * @author qiaoqiming
 * @brief 板载led驱动
 * @version 1.0
 * @date 2018-06-12
 */
#ifndef SRC_BSP_LED_H_
#define SRC_BSP_LED_H_

#include "fsl_gpio.h"
#include "fsl_common.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/* 板载LED引脚定义 */
#define BOARD_LED11_GPIO      GPIO
#define BOARD_LED11_GPIO_PORT 0U
#define BOARD_LED11_GPIO_PIN  15U

#define BOARD_LED10_GPIO      GPIO
#define BOARD_LED10_GPIO_PORT 0U
#define BOARD_LED10_GPIO_PIN  19U

#define BOARD_LED9_GPIO       GPIO
#define BOARD_LED9_GPIO_PORT  0U
#define BOARD_LED9_GPIO_PIN   21U

#define BOARD_LED8_GPIO       GPIO
#define BOARD_LED8_GPIO_PORT  0U
#define BOARD_LED8_GPIO_PIN   22U

#define BOARD_LED7_GPIO       GPIO
#define BOARD_LED7_GPIO_PORT  0U
#define BOARD_LED7_GPIO_PIN   25U

#define BOARD_LED6_GPIO       GPIO
#define BOARD_LED6_GPIO_PORT  0U
#define BOARD_LED6_GPIO_PIN   26U

#define BOARD_LED5_GPIO       GPIO
#define BOARD_LED5_GPIO_PORT  0U
#define BOARD_LED5_GPIO_PIN   29U

#define BOARD_LED4_GPIO       GPIO
#define BOARD_LED4_GPIO_PORT  0U
#define BOARD_LED4_GPIO_PIN   30U


/* 采用宏控制LED */
/* 定义开关选项 */
#define LOGIC_LED_ON 0U
#define LOGIC_LED_OFF 1U

/* LED11 */
#define LED11_INIT(output)   GPIO_PinInit(BOARD_LED11_GPIO, BOARD_LED11_GPIO_PORT, BOARD_LED11_GPIO_PIN, \
                                            &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)})
#define LED11_OFF()          GPIO_PortClear(BOARD_LED11_GPIO, BOARD_LED11_GPIO_PORT, \
                                            1U << BOARD_LED11_GPIO_PIN)
#define LED11_ON()           GPIO_PortSet(BOARD_LED11_GPIO, BOARD_LED11_GPIO_PORT, \
                                            1U << BOARD_LED11_GPIO_PIN)
#define LED11_TOGGLE()       GPIO_PortToggle(BOARD_LED11_GPIO, BOARD_LED11_GPIO_PORT, \
                                            1U << BOARD_LED11_GPIO_PIN)

/* LED10 */
#define LED10_INIT(output)   GPIO_PinInit(BOARD_LED10_GPIO, BOARD_LED10_GPIO_PORT, BOARD_LED10_GPIO_PIN, \
                                            &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)})
#define LED10_OFF()          GPIO_PortClear(BOARD_LED10_GPIO, BOARD_LED10_GPIO_PORT, \
                                            1U << BOARD_LED10_GPIO_PIN)
#define LED10_ON()           GPIO_PortSet(BOARD_LED10_GPIO, BOARD_LED10_GPIO_PORT, \
                                            1U << BOARD_LED10_GPIO_PIN)
#define LED10_TOGGLE()       GPIO_PortToggle(BOARD_LED10_GPIO, BOARD_LED10_GPIO_PORT, \
                                            1U << BOARD_LED10_GPIO_PIN)

/* LE9 */
#define LED9_INIT(output)    GPIO_PinInit(BOARD_LED9_GPIO, BOARD_LED9_GPIO_PORT, BOARD_LED9_GPIO_PIN, \
                                            &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)})
#define LED9_OFF()           GPIO_PortClear(BOARD_LED9_GPIO, BOARD_LED9_GPIO_PORT, \
                                            1U << BOARD_LED9_GPIO_PIN)
#define LED9_ON()            GPIO_PortSet(BOARD_LED9_GPIO, BOARD_LED9_GPIO_PORT, \
                                            1U << BOARD_LED9_GPIO_PIN)
#define LED9_TOGGLE()        GPIO_PortToggle(BOARD_LED9_GPIO, BOARD_LED9_GPIO_PORT, \
                                            1U << BOARD_LED9_GPIO_PIN)

/* LE8 */
#define LED8_INIT(output)    GPIO_PinInit(BOARD_LED8_GPIO, BOARD_LED8_GPIO_PORT, BOARD_LED8_GPIO_PIN, \
                                            &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)})
#define LED8_ON()            GPIO_PortClear(BOARD_LED8_GPIO, BOARD_LED8_GPIO_PORT, \
                                            1U << BOARD_LED8_GPIO_PIN)
#define LED8_OFF()           GPIO_PortSet(BOARD_LED8_GPIO, BOARD_LED8_GPIO_PORT, \
                                            1U << BOARD_LED8_GPIO_PIN)
#define LED8_TOGGLE()        GPIO_PortToggle(BOARD_LED8_GPIO, BOARD_LED8_GPIO_PORT, \
                                            1U << BOARD_LED8_GPIO_PIN)

/* LE7 */
#define LED7_INIT(output)    GPIO_PinInit(BOARD_LED7_GPIO, BOARD_LED7_GPIO_PORT, BOARD_LED7_GPIO_PIN, \
                                            &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)})
#define LED7_ON()            GPIO_PortClear(BOARD_LED7_GPIO, BOARD_LED7_GPIO_PORT, \
                                            1U << BOARD_LED7_GPIO_PIN)
#define LED7_OFF()           GPIO_PortSet(BOARD_LED7_GPIO, BOARD_LED7_GPIO_PORT, \
                                            1U << BOARD_LED7_GPIO_PIN)
#define LED7_TOGGLE()        GPIO_PortToggle(BOARD_LED7_GPIO, BOARD_LED7_GPIO_PORT, \
                                            1U << BOARD_LED7_GPIO_PIN)

/* LE6 */
#define LED6_INIT(output)    GPIO_PinInit(BOARD_LED6_GPIO, BOARD_LED6_GPIO_PORT, BOARD_LED6_GPIO_PIN, \
                                            &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)})
#define LED6_ON()            GPIO_PortClear(BOARD_LED6_GPIO, BOARD_LED6_GPIO_PORT, \
                                            1U << BOARD_LED6_GPIO_PIN)
#define LED6_OFF()           GPIO_PortSet(BOARD_LED6_GPIO, BOARD_LED6_GPIO_PORT, \
                                            1U << BOARD_LED6_GPIO_PIN)
#define LED6_TOGGLE()        GPIO_PortToggle(BOARD_LED6_GPIO, BOARD_LED6_GPIO_PORT, \
                                            1U << BOARD_LED6_GPIO_PIN)

/* LE5 */
#define LED5_INIT(output)    GPIO_PinInit(BOARD_LED5_GPIO, BOARD_LED5_GPIO_PORT, BOARD_LED5_GPIO_PIN, \
                                            &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)})
#define LED5_ON()            GPIO_PortClear(BOARD_LED5_GPIO, BOARD_LED5_GPIO_PORT, \
                                            1U << BOARD_LED5_GPIO_PIN)
#define LED5_OFF()           GPIO_PortSet(BOARD_LED5_GPIO, BOARD_LED5_GPIO_PORT, \
                                            1U << BOARD_LED5_GPIO_PIN)
#define LED5_TOGGLE()        GPIO_PortToggle(BOARD_LED5_GPIO, BOARD_LED5_GPIO_PORT, \
                                            1U << BOARD_LED5_GPIO_PIN)

/* LED4 */
#define LED4_INIT(output)    GPIO_PinInit(BOARD_LED4_GPIO, BOARD_LED4_GPIO_PORT, BOARD_LED4_GPIO_PIN, \
                                            &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)})
#define LED4_ON()            GPIO_PortClear(BOARD_LED4_GPIO, BOARD_LED4_GPIO_PORT, \
                                            1U << BOARD_LED4_GPIO_PIN)
#define LED4_OFF()           GPIO_PortSet(BOARD_LED4_GPIO, BOARD_LED4_GPIO_PORT, \
                                            1U << BOARD_LED4_GPIO_PIN)
#define LED4_TOGGLE()        GPIO_PortToggle(BOARD_LED4_GPIO, BOARD_LED4_GPIO_PORT, \
                                            1U << BOARD_LED4_GPIO_PIN)

status_t LEDInit(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* SRC_BSP_LED_H_ */
