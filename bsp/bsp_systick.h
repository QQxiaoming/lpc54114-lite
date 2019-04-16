/**
 * @file bsp_systick.h
 * @author 
 * @brief 
 * @version 0.1
 * @date 2019-04-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _BSP_SYSTICK_H_
#define _BSP_SYSTICK_H_

#include <stdint.h>

extern volatile uint32_t dwSysTicks;

void systick_init(void);
#endif /* _BSP_SYSTICK_H_ */
