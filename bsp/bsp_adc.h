/**
 * @file bsp_adc.h
 * @author qiaoqiming
 * @brief 板载adc驱动
 * @version 1.0
 * @date 2019-05-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _BSP_ADC_H_
#define _BSP_ADC_H_

#include "fsl_common.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

#define ADC_NUM            1
#define ADC_CHANNEL_NUM    3

status_t adc_init(void);
uint16_t adc_read(uint16_t num);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BSP_ADC_H_ */