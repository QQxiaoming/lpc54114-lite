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


#define I2S_DMA_TX  15
#define I2S_DMA_RX  12

#define BOARD_CODEC_I2C_BASEADDR   I2C4
#define BOARD_CODEC_I2C_CLOCK_FREQ 12000000

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



void BOARD_I2C_Init(I2C_Type *base, uint32_t clkSrc_Hz)
{
    i2c_master_config_t i2cConfig = {0};

    I2C_MasterGetDefaultConfig(&i2cConfig);
    I2C_MasterInit(base, &i2cConfig, clkSrc_Hz);
}

status_t BOARD_I2C_Send(I2C_Type *base,
                        uint8_t deviceAddress,
                        uint32_t subAddress,
                        uint8_t subaddressSize,
                        uint8_t *txBuff,
                        uint8_t txBuffSize)
{
    i2c_master_transfer_t masterXfer;

    /* Prepare transfer structure. */
    masterXfer.slaveAddress = deviceAddress;
    masterXfer.direction = kI2C_Write;
    masterXfer.subaddress = subAddress;
    masterXfer.subaddressSize = subaddressSize;
    masterXfer.data = txBuff;
    masterXfer.dataSize = txBuffSize;
    masterXfer.flags = kI2C_TransferDefaultFlag;

    return I2C_MasterTransferBlocking(base, &masterXfer);
}

status_t BOARD_I2C_Receive(I2C_Type *base,
                           uint8_t deviceAddress,
                           uint32_t subAddress,
                           uint8_t subaddressSize,
                           uint8_t *rxBuff,
                           uint8_t rxBuffSize)
{
    i2c_master_transfer_t masterXfer;

    /* Prepare transfer structure. */
    masterXfer.slaveAddress = deviceAddress;
    masterXfer.subaddress = subAddress;
    masterXfer.subaddressSize = subaddressSize;
    masterXfer.data = rxBuff;
    masterXfer.dataSize = rxBuffSize;
    masterXfer.direction = kI2C_Read;
    masterXfer.flags = kI2C_TransferDefaultFlag;

    return I2C_MasterTransferBlocking(base, &masterXfer);
}

void BOARD_Codec_I2C_Init(void)
{
    BOARD_I2C_Init(BOARD_CODEC_I2C_BASEADDR, BOARD_CODEC_I2C_CLOCK_FREQ);
}

status_t BOARD_Codec_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize)
{
    return BOARD_I2C_Send(BOARD_CODEC_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, (uint8_t *)txBuff,
                          txBuffSize);
}

status_t BOARD_Codec_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize)
{
    return BOARD_I2C_Receive(BOARD_CODEC_I2C_BASEADDR, deviceAddress, subAddress, subAddressSize, rxBuff, rxBuffSize);
}

codec_config_t boardCodecConfig = 
{
	.I2C_SendFunc = BOARD_Codec_I2C_Send,
	.I2C_ReceiveFunc = BOARD_Codec_I2C_Receive,
	.op.Init = WM8904_Init,
	.op.Deinit = WM8904_Deinit,
	.op.SetFormat = WM8904_SetAudioFormat
};

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
	
	
	PRINTF("Configure I2C\r\n");
    BOARD_Codec_I2C_Init();

	PRINTF("Configure WM8904 codec\r\n");
	/*
	 * enableMaster = true;
	 * baudRate_Bps = 100000U;
	 * enableTimeout = false;
	 */
	WM8904_GetDefaultConfig(&codecConfig);
	codecConfig.mclk_HZ = 12000000;
	boardCodecConfig.codecConfig = (void *)&codecConfig;

    if (CODEC_Init(&codecHandle, &boardCodecConfig) != kStatus_Success)
    {
        PRINTF("WM8904_Init failed!\r\n");
		return kStatus_Fail;
    }

	/* SYSCLK=MCLK/MCLKDIV=12000000，采样率44100，位宽16 */
	WM8904_SetAudioFormat(&codecHandle,12000000,44100,16);

	/* Initial volume kept low for hearing safety. */
	/* Adjust it to your needs, 0x0006 for -51 dB, 0x0039 for 0 dB etc. */
	WM8904_SetVolume(&codecHandle, 0x0006, 0x0006);
	
	PRINTF("Configure I2S\r\n");
	I2S_TxGetDefaultConfig(&s_TxConfig);
	/* 采样率44100，位宽16，双声道 */
	s_TxConfig.divider = CLOCK_GetPllOutFreq() / 44100U / 16U / 2U;	
	I2S_RxGetDefaultConfig(&s_RxConfig);
	
	I2S_TxInit(WM8904_I2S_TX, &s_TxConfig);
	I2S_RxInit(WM8904_I2S_RX, &s_RxConfig);

	/* 配置使能IISDMA */
	DMA_EnableChannel(DMA0, I2S_DMA_TX);
	DMA_EnableChannel(DMA0, I2S_DMA_RX);
	DMA_SetChannelPriority(DMA0, I2S_DMA_TX, kDMA_ChannelPriority3);
	DMA_SetChannelPriority(DMA0, I2S_DMA_RX, kDMA_ChannelPriority2);
	DMA_CreateHandle(&s_DmaTxHandle, DMA0, I2S_DMA_TX);
	DMA_CreateHandle(&s_DmaRxHandle, DMA0, I2S_DMA_RX);
    
	return kStatus_Success;
}
