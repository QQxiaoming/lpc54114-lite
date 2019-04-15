/*
 * bsp_led.c
 *
 *  Created on: 2018年6月12日
 *      Author: qq_xi
 */
#include "bsp_led.h"

/* 初始化LED引脚 */
void LEDInit(void)
{
    /* 配置使能GPIO0时钟 */
    GPIO_PortInit(GPIO, 0);

    /* 配置LED引脚 */
    LED11_INIT(LOGIC_LED_ON);
    LED10_INIT(LOGIC_LED_ON);
    LED9_INIT(LOGIC_LED_ON);
    LED8_INIT(LOGIC_LED_ON);
    LED7_INIT(LOGIC_LED_OFF);
    LED6_INIT(LOGIC_LED_OFF);
    LED5_INIT(LOGIC_LED_OFF);
    LED4_INIT(LOGIC_LED_OFF);
}
