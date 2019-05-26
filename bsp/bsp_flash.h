/**
 * @file bsp_flash.h
 * @author qiaoqiming
 * @brief 板载flash驱动
 * @version 1.0
 * @date 2019-04-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _BSP_FLASH_H_
#define _BSP_FLASH_H_

#include <stdint.h>
#include "fsl_common.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

status_t spiflash_init(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BSP_FLASH_H_ */

