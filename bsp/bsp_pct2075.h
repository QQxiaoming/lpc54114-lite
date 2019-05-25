/**
 * @file bsp_pct2075.h
 * @author qiaoqiming
 * @brief 板载pct2075驱动
 * @version 1.0
 * @date 2019-05-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef _BSP_PCT2075_H_
#define _BSP_PCT2075_H_

#include "fsl_common.h"

status_t pct2075_i2c_read(float *data);

#endif /* _BSP_PCT2075_H_ */
