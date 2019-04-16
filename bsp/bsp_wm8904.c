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
//#include "music.h"

#define I2S_TX  I2S1
#define I2S_RX  I2S0

#define I2S_DMA_TX  15
#define I2S_DMA_RX  12

#define BOARD_CODEC_I2C_BASEADDR I2C4
#define BOARD_CODEC_I2C_CLOCK_FREQ 12000000

static dma_handle_t s_DmaTxHandle;
static dma_handle_t s_DmaRxHandle;
static i2s_config_t s_TxConfig;
static i2s_config_t s_RxConfig;


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

wm8904_config_t codecConfig;
codec_config_t codecHandle = {.I2C_SendFunc = BOARD_Codec_I2C_Send,
                                   .I2C_ReceiveFunc = BOARD_Codec_I2C_Receive,
                                   .op.Init = WM8904_Init,
                                   .op.Deinit = WM8904_Deinit,
                                   .op.SetFormat = WM8904_SetAudioFormat};


const pll_setup_t pllSetup = {
		.syspllctrl = SYSCON_SYSPLLCTRL_BANDSEL_MASK | SYSCON_SYSPLLCTRL_SELP(0x1FU) | SYSCON_SYSPLLCTRL_SELI(0x8U),
		.syspllndec = SYSCON_SYSPLLNDEC_NDEC(0x2DU),
		.syspllpdec = SYSCON_SYSPLLPDEC_PDEC(0x42U),
		.syspllssctrl = {SYSCON_SYSPLLSSCTRL0_MDEC(0x34D3U) | SYSCON_SYSPLLSSCTRL0_SEL_EXT_MASK, 0x00000000U},
		.pllRate = 24576000U, /* 16 bits * 2 channels * 48 kHz * 16 */
		.flags = PLL_SETUPFLAG_WAITLOCK};



uint8_t wm8904_i2s_init(void)
{
    // we need initial i2c here, but we initial the right i2c at pct2075 already
	
	/* Initialize PLL clock */
	CLOCK_AttachClk(kFRO12M_to_SYS_PLL);
	CLOCK_SetPLLFreq(&pllSetup);

	CLOCK_AttachClk(kSYS_PLL_to_FLEXCOMM6);
	CLOCK_AttachClk(kSYS_PLL_to_FLEXCOMM7);
	/* Attach PLL clock to MCLK for I2S, no divider */
	CLOCK_AttachClk(kSYS_PLL_to_MCLK);
	SYSCON->MCLKDIV = SYSCON_MCLKDIV_DIV(0U);
	/* reset FLEXCOMM for I2S */
	RESET_PeripheralReset(kFC6_RST_SHIFT_RSTn);
	RESET_PeripheralReset(kFC7_RST_SHIFT_RSTn);
	
	/* I2S */
    // Flexcomm 6 I2S Rx
	IOCON_PinMuxSet(IOCON, 0, 5, IOCON_FUNC1 | IOCON_DIGITAL_EN); /* Flexcomm 6 / SDA */
	IOCON_PinMuxSet(IOCON, 0, 6, IOCON_FUNC1 | IOCON_DIGITAL_EN); /* Flexcomm 6 / WS */
	IOCON_PinMuxSet(IOCON, 0, 7, IOCON_FUNC1 | IOCON_DIGITAL_EN); /* Flexcomm 6 / SCK */
    // Flexcomm 7 I2S Tx
	IOCON_PinMuxSet(IOCON, 1, 12, IOCON_FUNC4 | IOCON_DIGITAL_EN); /* Flexcomm 7 / SCK */
	IOCON_PinMuxSet(IOCON, 1, 13, IOCON_FUNC4 | IOCON_DIGITAL_EN);  /* Flexcomm 7 / SDA */
	IOCON_PinMuxSet(IOCON, 1, 14, IOCON_FUNC4 | IOCON_DIGITAL_EN);  /* Flexcomm 7 / WS */

	/* MCLK output for I2S */
	IOCON_PinMuxSet(IOCON, 1, 17, IOCON_FUNC4 | IOCON_MODE_INACT | IOCON_DIGITAL_EN);
	SYSCON->MCLKIO = 1U;
	/*
	 * enableMaster = true;
	 * baudRate_Bps = 100000U;
	 * enableTimeout = false;
	 */
	WM8904_GetDefaultConfig(&codecConfig);

	if (WM8904_Init((codec_handle_t *)&codecHandle, &codecConfig) != kStatus_Success)
	{
		PRINTF("WM8904_Init failed!\r\n");
	}
	else
	{
	}
	/* Initial volume kept low for hearing safety. */
	/* Adjust it to your needs, 0x0006 for -51 dB, 0x0039 for 0 dB etc. */
	WM8904_SetVolume((codec_handle_t *)&codecHandle, 0x0006, 0x0006);
	
	I2S_TxGetDefaultConfig(&s_TxConfig);
	s_TxConfig.divider = CLOCK_GetPllOutFreq() / 48000U / 16U / 2U;	
	I2S_RxGetDefaultConfig(&s_RxConfig);
	
	I2S_TxInit(I2S_TX, &s_TxConfig);
	I2S_RxInit(I2S_RX, &s_RxConfig);
	
	DMA_Init(DMA0);

	DMA_EnableChannel(DMA0, I2S_DMA_TX);
	DMA_EnableChannel(DMA0, I2S_DMA_RX);
	DMA_SetChannelPriority(DMA0, I2S_DMA_TX, kDMA_ChannelPriority3);
	DMA_SetChannelPriority(DMA0, I2S_DMA_RX, kDMA_ChannelPriority2);
	DMA_CreateHandle(&s_DmaTxHandle, DMA0, I2S_DMA_TX);
	DMA_CreateHandle(&s_DmaRxHandle, DMA0, I2S_DMA_RX);
    
    /*
	if (true)
	{
		StartSoundPlayback();
	}
	else
	{
		StartDigitalLoopback();
	}*/
    return 0;
}
