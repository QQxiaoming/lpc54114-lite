/**
 * @file bsp_adc.c
 * @author qiaoqiming
 * @brief 板载adc驱动
 * @version 1.0
 * @date 2019-05-25
 */
#include "bsp_adc.h"
#include "fsl_adc.h"
#include "fsl_power.h"


/**
 * @brief 初始化adc0
 * 
 * @return status_t 状态码
 */
status_t adc_init(void)
{
    adc_config_t adcConfigStruct;
    adc_conv_seq_config_t adcConvSeqConfigStruct;

    /* 配置ADC的电源和时钟 */
    POWER_DisablePD(kPDRUNCFG_PD_ADC0);     /* Power on the ADC converter. */
    POWER_DisablePD(kPDRUNCFG_PD_VD7_ENA);  /* Power on the analog power supply. */
    POWER_DisablePD(kPDRUNCFG_PD_VREFP_SW); /* Power on the reference voltage source. */
    POWER_DisablePD(kPDRUNCFG_PD_TEMPS);    /* Power on the temperature sensor. */

    /* 启用时钟 */
    CLOCK_EnableClock(kCLOCK_Adc0); /* SYSCON->AHBCLKCTRL[0] |= SYSCON_AHBCLKCTRL_ADC0_MASK; */


    /* 校准 */
    if (!ADC_DoSelfCalibration(ADC0))
    {
        return kStatus_Fail;
    }

    /* 配置adc */
    adcConfigStruct.clockMode = kADC_ClockSynchronousMode; /* 使用 sync clock */
    adcConfigStruct.clockDividerNumber = 1;                /* 2分频 */
    adcConfigStruct.resolution = kADC_Resolution12bit;     /* 12bit */
    adcConfigStruct.enableBypassCalibration = false;
    adcConfigStruct.sampleTimeNumber = 0U;
    ADC_Init(ADC0, &adcConfigStruct);

    /* 使能内部温度传感器数据到adc0 */
    ADC_EnableTemperatureSensor(ADC0, true);

    /* 配置通道3并使能 */
    adcConvSeqConfigStruct.channelMask = (1U << ADC_CHANNEL_NUM); /* Includes channel 0. */
    adcConvSeqConfigStruct.triggerMask = 0U;
    adcConvSeqConfigStruct.triggerPolarity = kADC_TriggerPolarityNegativeEdge;
    adcConvSeqConfigStruct.enableSingleStep = false;
    adcConvSeqConfigStruct.enableSyncBypass = false;
    adcConvSeqConfigStruct.interruptMode = kADC_InterruptForEachSequence;
    ADC_SetConvSeqAConfig(ADC0, &adcConvSeqConfigStruct);
    ADC_EnableConvSeqA(ADC0, true);

    return kStatus_Success;
}


/**
 * @brief 查询方式读取adc数据
 * 
 * @param num 目标通道号
 * @return uint16_t 数据值
 */
uint16_t adc_read(uint16_t num)
{
    static adc_result_info_t gAdcResultInfoStruct;

    /* 触发adc转换 */
    ADC_DoSoftwareTriggerConvSeqA(ADC0);
    /* 查询等待转换完成并读出数据 */
    while (!ADC_GetChannelConversionResult(ADC0, num, &gAdcResultInfoStruct))
    {
    }
    return (gAdcResultInfoStruct.result & 0x0FFF);
}
