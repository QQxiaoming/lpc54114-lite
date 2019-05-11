#ifndef _BSP_WM8904_H_
#define _BSP_WM8904_H_

#include <stdint.h>
#include "fsl_i2c.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "fsl_dma.h"
#include "fsl_i2s_dma.h"

#define WM8904_I2S_TX  I2S1
#define WM8904_I2S_RX  I2S0

extern dma_handle_t s_DmaTxHandle;
extern dma_handle_t s_DmaRxHandle;

status_t wm8904_i2s_init(void);

#endif /* _BSP_WM8904_H_ */