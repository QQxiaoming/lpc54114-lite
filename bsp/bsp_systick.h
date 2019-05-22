/**
 * @file bsp_systick.h
 * @author qiaoqiming
 * @brief systick初始化
 * @version 1.0
 * @date 2019-04-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _BSP_SYSTICK_H_
#define _BSP_SYSTICK_H_

#include <stdint.h>
#include "fsl_common.h"

extern volatile uint32_t dwSysTicks;

status_t systick_init(void);
#endif /* _BSP_SYSTICK_H_ */
