/**
 * @file bsp_wm8904.h
 * @author qiaoqiming
 * @brief 板载wm8904驱动
 * @version 1.0
 * @date 2019-04-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _BSP_WM8904_H_
#define _BSP_WM8904_H_

#include <stdint.h>
#include "fsl_i2c.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "fsl_dma.h"
#include "fsl_i2s_dma.h"
#include "fsl_wm8904.h"


#define WM8904_I2C         I2C4
#define WM8904_I2S_TX      I2S1
#define WM8904_I2S_RX      I2S0
#define WM8904_I2S_DMA_TX  15
#define WM8904_I2S_DMA_RX  12

extern dma_handle_t s_DmaTxHandle;
extern dma_handle_t s_DmaRxHandle;
extern codec_handle_t codecHandle;

status_t wm8904_i2s_init(void);

#endif /* _BSP_WM8904_H_ */