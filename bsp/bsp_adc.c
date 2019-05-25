/**
 * @file bsp_adc.c
 * @author qiaoqiming
 * @brief 板载adc驱动
 * @version 1.0
 * @date 2019-05-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "bsp_adc.h"
#include "fsl_adc.h"
#include "fsl_power.h"



status_t adc_init(void)
{
    adc_config_t adcConfigStruct;
    adc_conv_seq_config_t adcConvSeqConfigStruct;

    // Configure the power and clock for ADC.
    POWER_DisablePD(kPDRUNCFG_PD_ADC0);     /* Power on the ADC converter. */
    POWER_DisablePD(kPDRUNCFG_PD_VD7_ENA);  /* Power on the analog power supply. */
    POWER_DisablePD(kPDRUNCFG_PD_VREFP_SW); /* Power on the reference voltage source. */
    POWER_DisablePD(kPDRUNCFG_PD_TEMPS);    /* Power on the temperature sensor. */

    // Enable the clock.
    CLOCK_EnableClock(kCLOCK_Adc0); /* SYSCON->AHBCLKCTRL[0] |= SYSCON_AHBCLKCTRL_ADC0_MASK; */


    // Calibration
    if (!ADC_DoSelfCalibration(ADC0))
    {
        return kStatus_Fail;
    }

    /* Configure the converter. */
    adcConfigStruct.clockMode = kADC_ClockSynchronousMode; /* Using sync clock source. */
    adcConfigStruct.clockDividerNumber = 1;                /* The divider for sync clock is 2. */
    adcConfigStruct.resolution = kADC_Resolution12bit;
    adcConfigStruct.enableBypassCalibration = false;
    adcConfigStruct.sampleTimeNumber = 0U;
    ADC_Init(ADC0, &adcConfigStruct);

    /* Use the sensor input to channel 0. */
    ADC_EnableTemperatureSensor(ADC0, true);

    /* Enable channel 0's conversion in Sequence A. */
    adcConvSeqConfigStruct.channelMask = (1U << ADC_CHANNEL_NUM); /* Includes channel 0. */
    adcConvSeqConfigStruct.triggerMask = 0U;
    adcConvSeqConfigStruct.triggerPolarity = kADC_TriggerPolarityNegativeEdge;
    adcConvSeqConfigStruct.enableSingleStep = false;
    adcConvSeqConfigStruct.enableSyncBypass = false;
    adcConvSeqConfigStruct.interruptMode = kADC_InterruptForEachSequence;
    ADC_SetConvSeqAConfig(ADC0, &adcConvSeqConfigStruct);
    ADC_EnableConvSeqA(ADC0, true); /* Enable the conversion sequence A. */

    return kStatus_Success;
}

uint16_t adc_read(uint16_t num)
{
    static adc_result_info_t gAdcResultInfoStruct;

    ADC_DoSoftwareTriggerConvSeqA(ADC0);
    /* Wait for the converter to be done. */
    while (!ADC_GetChannelConversionResult(ADC0, num, &gAdcResultInfoStruct))
    {
    }
    return (gAdcResultInfoStruct.result & 0x0FFF);
}

