/**
 * @file bsp_dmic.c
 * @author qiaoqiming
 * @brief dmic驱动
 * @version 1.0
 * @date 2019-04-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdbool.h>
#include "fsl_common.h"
#include "fsl_iocon.h"
#include "fsl_dmic.h"
#include "bsp_led.h"
#include "fsl_debug_console.h"
#include "bsp_uart.h"


#define FIFO_DEPTH 15U


/*!
* @brief Call back for DMIC0 Interrupt
*/
void DMIC0_Callback(void)
{
    /* In this example this interrupt is disabled */
}

/*!
* @brief Call back for DMIC0 HWVAD Interrupt
*/
void DMIC0_HWVAD_Callback(void)
{
    volatile int i;

    /* reset hwvad internal interrupt */
    DMIC_CtrlClrIntrHwvad(DMIC0, true);
	//printfk("Just woke up\r\n");
    /* wait for HWVAD to settle */
    for (i = 0; i <= 500U; i++)
    {
			
    }
    /*HWVAD Normal operation */
    DMIC_CtrlClrIntrHwvad(DMIC0, false);
}

status_t dmic_init(void)
{
	uint32_t i = 0;
	dmic_channel_config_t dmic_channel_cfg;
	
	/* DMIC uses 12MHz FRO clock */
    CLOCK_AttachClk(kFRO12M_to_DMIC);
	/*12MHz divided by 15 = 800KHz PDM clock */
	CLOCK_SetClkDiv(kCLOCK_DivDmicClk, 14, false);
	dmic_channel_cfg.divhfclk = kDMIC_PdmDiv1;
	dmic_channel_cfg.osr = 25U;
	dmic_channel_cfg.gainshft = 3U;
	dmic_channel_cfg.preac2coef = kDMIC_CompValueZero;
	dmic_channel_cfg.preac4coef = kDMIC_CompValueZero;
	dmic_channel_cfg.dc_cut_level = kDMIC_DcCut155;
	dmic_channel_cfg.post_dc_gain_reduce = 0U;
	dmic_channel_cfg.saturate16bit = true;
	dmic_channel_cfg.sample_rate = kDMIC_PhyFullSpeed;
	DMIC_Init(DMIC0);
	
	DMIC_ConfigIO(DMIC0, kDMIC_PdmStereo);
	DMIC_Use2fs(DMIC0, true);
	DMIC_SetOperationMode(DMIC0, kDMIC_OperationModeInterrupt);
	DMIC_ConfigChannel(DMIC0, kDMIC_Channel0, kDMIC_Left, &dmic_channel_cfg);
	DMIC_ConfigChannel(DMIC0, kDMIC_Channel1, kDMIC_Right, &dmic_channel_cfg);
	DMIC_FifoChannel(DMIC0, kDMIC_Channel0, FIFO_DEPTH, true, true);
	DMIC_FifoChannel(DMIC0, kDMIC_Channel1, FIFO_DEPTH, true, true);
	
	/*Gain of the noise estimator */
	DMIC_SetGainNoiseEstHwvad(DMIC0, 0x02U);
	/*Gain of the signal estimator */
	DMIC_SetGainSignalEstHwvad(DMIC0, 0x01U);
	/* 00 = first filter by-pass, 01 = hpf_shifter=1, 10 = hpf_shifter=4 */
	DMIC_SetFilterCtrlHwvad(DMIC0, 0x01U);
	/*input right-shift of (GAIN x 2 -10) bits (from -10bits (0000) to +14bits (1100)) */
	DMIC_SetInputGainHwvad(DMIC0, 0x04U);
	DisableDeepSleepIRQ(HWVAD0_IRQn);
	DMIC_HwvadEnableIntCallback(DMIC0, DMIC0_HWVAD_Callback);
	DMIC_EnableChannnel(DMIC0, (DMIC_CHANEN_EN_CH0(1) | DMIC_CHANEN_EN_CH1(1)));
	/* reset hwvad internal interrupt */
	DMIC_CtrlClrIntrHwvad(DMIC0, true);
	/* To clear first spurious interrupt */
	for (i = 0; i < 0xFFFFU; i++)
	{
	}
	/*HWVAD Normal operation */
	NVIC_SetPriority(HWVAD0_IRQn, 2);
	DMIC_CtrlClrIntrHwvad(DMIC0, false);
	NVIC_ClearPendingIRQ(HWVAD0_IRQn);
	EnableDeepSleepIRQ(HWVAD0_IRQn);

	return kStatus_Success;
}
