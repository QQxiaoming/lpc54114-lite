/**
 * @file bsp_sdspi.c
 * @author 
 * @brief 
 * @version 0.1
 * @date 2019-04-15
 * 
 * @copyright Copyright (c) 2019
 * 
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


/* SDSPI driver state. */
sdspi_card_t g_card;
sdspi_host_t g_host;
volatile uint32_t dwSysTicks = 0;

/*******************************************************************************
 * Code - SPI interface
 ******************************************************************************/

void spi_init(void)
{
	uint32_t sourceClock;
	spi_master_config_t masterConfig = {0};
		
	/* attach 12 MHz clock to SPI2 */
	CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);
    /* reset FLEXCOMM for SPI */
    RESET_PeripheralReset(kFC2_RST_SHIFT_RSTn);
	
	/* SPI2 pins */
	IOCON_PinMuxSet(IOCON, 0,  3, (IOCON_FUNC2 | IOCON_MODE_PULLUP | IOCON_GPIO_MODE | IOCON_DIGITAL_EN));  /* SPI2_CS - FLASH */
	IOCON_PinMuxSet(IOCON, 0, 10, (IOCON_FUNC1 | IOCON_MODE_PULLUP | IOCON_GPIO_MODE | IOCON_DIGITAL_EN));  /* SPI2_SCK        */
	IOCON_PinMuxSet(IOCON, 0,  8, (IOCON_FUNC1 | IOCON_MODE_PULLUP | IOCON_GPIO_MODE | IOCON_DIGITAL_EN));  /* SPI2_MOSI       */
	IOCON_PinMuxSet(IOCON, 0,  9, (IOCON_FUNC1 | IOCON_MODE_PULLUP | IOCON_GPIO_MODE | IOCON_DIGITAL_EN));  /* SPI2_MISO       */
	
	SPI_MasterGetDefaultConfig(&masterConfig);
	masterConfig.direction = kSPI_MsbFirst;
	masterConfig.polarity = kSPI_ClockPolarityActiveHigh;
	masterConfig.phase = kSPI_ClockPhaseFirstEdge;
	masterConfig.baudRate_Bps = 100000;
	masterConfig.sselNum = (spi_ssel_t)2; // use GPIO as CS is prefer
	SPI_MasterInit(SPI2, &masterConfig, CLOCK_GetFreq(kCLOCK_Flexcomm2));

}

status_t spi_set_frequency(uint32_t frequency)
{
 	uint32_t sourceClock;
	sourceClock = CLOCK_GetFreq(kCLOCK_Flexcomm2);
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
	return SPI_MasterTransferBlocking(SPI2, &xfer);	
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