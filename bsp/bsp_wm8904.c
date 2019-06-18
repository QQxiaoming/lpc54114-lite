/**
 * @file bsp_wm8904.c
 * @author qiaoqiming
 * @brief 板载wm8904驱动
 * @version 1.0
 * @date 2019-04-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "bsp_wm8904.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_wm8904.h"
#include "fsl_common.h"
#include "fsl_iocon.h"
#include "fsl_dma.h"
#include "fsl_i2c.h"
#include "fsl_i2s.h"
#include "fsl_i2s_dma.h"
#include "UARTCommandConsole.h"
#include "fsl_codec_adapter.h"

dma_handle_t s_DmaTxHandle;
dma_handle_t s_DmaRxHandle;
static i2s_config_t s_TxConfig;
static i2s_config_t s_RxConfig;
wm8904_config_t codecConfig;
codec_handle_t codecHandle;
const pll_setup_t pllSetup = 
{
	.syspllctrl = SYSCON_SYSPLLCTRL_BANDSEL_MASK | SYSCON_SYSPLLCTRL_SELP(0x1FU) | SYSCON_SYSPLLCTRL_SELI(0x8U),
	.syspllndec = SYSCON_SYSPLLNDEC_NDEC(0x2DU),
	.syspllpdec = SYSCON_SYSPLLPDEC_PDEC(0x42U),
	.syspllssctrl = {SYSCON_SYSPLLSSCTRL0_MDEC(0x34D3U) | SYSCON_SYSPLLSSCTRL0_SEL_EXT_MASK, 0x00000000U},
	.pllRate = 24576000U, /* 16 bits * 2 channels * 48 kHz * 16 */
	.flags = PLL_SETUPFLAG_WAITLOCK
};


wm8904_config_t wm8904Config = {
    .i2cConfig    = {.codecI2CInstance = 4U, .codecI2CSourceClock = 12000000},
    .recordSource = kWM8904_RecordSourceLineInput,
    .recordChannelLeft  = kWM8904_RecordChannelLeft2,
    .recordChannelRight = kWM8904_RecordChannelRight2,
    .playSource         = kWM8904_PlaySourceDAC,
    .slaveAddress       = WM8904_I2C_ADDRESS,
    .protocol           = kWM8904_ProtocolI2S,
    .format             = {.sampleRate = kWM8904_SampleRate48kHz, .bitWidth = kWM8904_BitWidth16},
    .mclk_HZ            = 24576000,
    .master             = false,
};
codec_config_t boardCodecConfig = {.codecDevType = kCODEC_WM8904, .codecDevConfig = &wm8904Config};

status_t wm8904_i2s_init(void)
{
	/* I2C clock */
	CLOCK_AttachClk(kFRO12M_to_FLEXCOMM4);

	/* Initialize PLL clock */
	CLOCK_AttachClk(kFRO12M_to_SYS_PLL);
	CLOCK_SetPLLFreq(&pllSetup);

	/* I2S clocks */
	CLOCK_AttachClk(kSYS_PLL_to_FLEXCOMM6);
	CLOCK_AttachClk(kSYS_PLL_to_FLEXCOMM7);

	/* Attach PLL clock to MCLK for I2S, no divider */
	CLOCK_AttachClk(kSYS_PLL_to_MCLK);
	SYSCON->MCLKDIV = SYSCON_MCLKDIV_DIV(0U);

	/* reset FLEXCOMM for I2C */
	RESET_PeripheralReset(kFC4_RST_SHIFT_RSTn);

	/* reset FLEXCOMM for I2S */
	RESET_PeripheralReset(kFC6_RST_SHIFT_RSTn);
	RESET_PeripheralReset(kFC7_RST_SHIFT_RSTn);

	printfk("Configure WM8904 codec\r\n");
    if (CODEC_Init(&codecHandle, &boardCodecConfig) != kStatus_Success)
    {
        printfk("WM8904_Init failed!\r\n");
		return kStatus_Fail;
    }

	/* SYSCLK=MCLK/MCLKDIV=12000000，采样率44100，位宽16 */
	CODEC_SetFormat(&codecHandle,12000000,44100,16);

	/* Initial volume kept low for hearing safety. */
	/* Adjust it to your needs, 0x0006 for -51 dB, 0x0039 for 0 dB etc. */
    CODEC_SetVolume(&codecHandle, kCODEC_PlayChannelHeadphoneLeft | kCODEC_PlayChannelHeadphoneRight, 0x0006);

	printfk("Configure I2S\r\n");
	I2S_TxGetDefaultConfig(&s_TxConfig);
	/* 采样率44100，位宽16，双声道 */
	s_TxConfig.divider = CLOCK_GetPllOutFreq() / 44100U / 16U / 2U;	
	I2S_RxGetDefaultConfig(&s_RxConfig);
	
	I2S_TxInit(WM8904_I2S_TX, &s_TxConfig);
	I2S_RxInit(WM8904_I2S_RX, &s_RxConfig);

	/* 配置使能IISDMA */
	DMA_EnableChannel(DMA0, WM8904_I2S_DMA_TX);
	DMA_EnableChannel(DMA0, WM8904_I2S_DMA_RX);
	DMA_SetChannelPriority(DMA0, WM8904_I2S_DMA_TX, kDMA_ChannelPriority3);
	DMA_SetChannelPriority(DMA0, WM8904_I2S_DMA_RX, kDMA_ChannelPriority2);
	DMA_CreateHandle(&s_DmaTxHandle, DMA0, WM8904_I2S_DMA_TX);
	DMA_CreateHandle(&s_DmaRxHandle, DMA0, WM8904_I2S_DMA_RX);
    
	return kStatus_Success;
}
