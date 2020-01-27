/**
 * @file bsp_sdspi.c
 * @author qiaoqiming
 * @brief 板载spisd卡驱动
 * @version 1.0
 * @date 2019-04-15
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "fsl_spi.h"
#include "fsl_sdspi.h"
#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "fsl_iocon.h"
#include "fsl_gpio.h"
#include "fsl_spi.h"
#include "bsp_sdspi.h"
#include "bsp_systick.h"
#include "fsl_spi_dma.h"
#include "fsl_clock.h"

/* SDSPI driver state. */
sdspi_card_t g_card;
sdspi_host_t g_host;

#define SPI2_DMA_TX   5
#define SPI2_DMA_RX   4
spi_dma_handle_t spi_dma_handle;
dma_handle_t spi2_TxHandle;
dma_handle_t spi2_RxHandle;
volatile bool isTransferCompleted = false;

/*******************************************************************************
 * Code - SPI interface
 ******************************************************************************/
static void SPI2_Callback(SPI_Type *base, spi_dma_handle_t *handle, status_t status, void *userData)
{
    if (status == kStatus_Success)
    {
        isTransferCompleted = true;
    }
}

void spi_init(void)
{
	spi_master_config_t masterConfig = {0};
		
	/* attach 12 MHz clock to SPI2 */
	CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);
    /* reset FLEXCOMM for SPI */
    RESET_PeripheralReset(kFC2_RST_SHIFT_RSTn);
	
	/* SPI init */
	SPI_MasterGetDefaultConfig(&masterConfig);
	masterConfig.direction = kSPI_MsbFirst;
	masterConfig.polarity = kSPI_ClockPolarityActiveHigh;
	masterConfig.phase = kSPI_ClockPhaseFirstEdge;
	masterConfig.baudRate_Bps = 100000;
	masterConfig.sselNum = kSPI_Ssel2; // use GPIO as CS is prefer
	SPI_MasterInit(SPI2, &masterConfig, CLOCK_GetFlexCommClkFreq(2));

    /* 配置使能SPI2DMA*/
    DMA_EnableChannel(DMA0, SPI2_DMA_TX);
    DMA_EnableChannel(DMA0, SPI2_DMA_RX);
    DMA_SetChannelPriority(DMA0, SPI2_DMA_TX, kDMA_ChannelPriority3);
    DMA_SetChannelPriority(DMA0, SPI2_DMA_RX, kDMA_ChannelPriority2);
    DMA_CreateHandle(&spi2_TxHandle, DMA0, SPI2_DMA_TX);
    DMA_CreateHandle(&spi2_RxHandle, DMA0, SPI2_DMA_RX);

	SPI_MasterTransferCreateHandleDMA(SPI2, &spi_dma_handle, SPI2_Callback, NULL, &spi2_TxHandle,
                                      &spi2_RxHandle);

}

status_t spi_set_frequency(uint32_t frequency)
{
 	uint32_t sourceClock;
	sourceClock = CLOCK_GetFlexCommClkFreq(2);
	/* If returns 0, indicates failed. */
	return 	SPI_MasterSetBaud(SPI2, frequency, sourceClock);
	return kStatus_Fail;
}

status_t spi_exchange(uint8_t *in, uint8_t *out, uint32_t size)
{
	spi_transfer_t 	xfer;

	/* SPI master start transfer */
	xfer.txData 		= in;
	xfer.rxData 		= out;
	xfer.dataSize		= size;
	xfer.configFlags	= kSPI_FrameAssert;

	SPI_MasterTransferDMA(SPI2, &spi_dma_handle, &xfer);

	while (!isTransferCompleted);
	isTransferCompleted = false;

	return kStatus_Success;
}

void timer_init(void)
{

}

uint32_t timer_get_current_milliseconds(void)
{
    return dwSysTicks;
}

void sdspi_host_init(void)
{
    /* Initializes timer to make host's callback function "timer_get_current_milliseconds" workable. */
    timer_init();

    /* Saves host state and callback. */
    g_host.busBaudRate = 500000;
    g_host.setFrequency = spi_set_frequency;
    g_host.exchange = spi_exchange;
    g_host.getCurrentMilliseconds = timer_get_current_milliseconds;

    /* Saves card state. */
    g_card.host = &g_host;
}
