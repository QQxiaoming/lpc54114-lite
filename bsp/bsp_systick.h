/**
 * @file bsp_systick.h
 * @author qiaoqiming
 * @brief systick初始化
 * @version 1.0
 * @date 2019-04-16
 */
#ifndef _BSP_SYSTICK_H_
#define _BSP_SYSTICK_H_

#include <stdint.h>
#include "fsl_common.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

extern volatile uint32_t dwSysTicks;

status_t systick_init(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BSP_SYSTICK_H_ */
