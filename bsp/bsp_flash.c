/**
 * @file bsp_flash.c
 * @author qiaoqiming
 * @brief 板载flash驱动
 * @version 1.0
 * @date 2019-04-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "bsp_flash.h"
#include "mx25r_flash.h"
#include "fsl_common.h"
#include "fsl_iocon.h"
#include "fsl_spi.h"
#include "fsl_clock.h"

struct mx25r_instance mx25r;

int flash_transfer_cb(void *transfer_prv, uint8_t *tx_data, uint8_t *rx_data, size_t dataSize, bool eof)
{
//	  SPI_FLASH_CS0();
    spi_transfer_t xfer = {0};
    xfer.txData = tx_data;
    xfer.rxData = rx_data;
    xfer.dataSize = dataSize;
    /* terminate frame */
    if (eof)
    {
        xfer.configFlags |= kSPI_FrameAssert;
    }
    SPI_MasterTransferBlocking((SPI_Type *)transfer_prv, &xfer);
//		SPI_FLASH_CS1();
    return 0;
}

status_t spiflash_init(void)
{
	spi_master_config_t masterConfig = {0};
	struct mx25r_rdid_result gIDResult;
		
	/* attach 12 MHz clock to SPI2 */
	CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);
    /* reset FLEXCOMM for SPI */
    RESET_PeripheralReset(kFC2_RST_SHIFT_RSTn);
	

	SPI_MasterGetDefaultConfig(&masterConfig);
	masterConfig.direction = kSPI_MsbFirst;
	masterConfig.polarity = kSPI_ClockPolarityActiveHigh;
	masterConfig.phase = kSPI_ClockPhaseFirstEdge;
	masterConfig.baudRate_Bps = 100000;
	masterConfig.sselNum = kSPI_Ssel3; // use GPIO as CS is prefer
	SPI_MasterInit(SPI2, &masterConfig, CLOCK_GetFlexCommClkFreq(2));

    mx25r_init(&mx25r, flash_transfer_cb, SPI2);
	mx25r_cmd_rdid(&mx25r, &gIDResult);
	
	if( (gIDResult.manufacturer == 0x51) && (gIDResult.device[0] == 0x40) && (gIDResult.device[1] == 0x15) )
	{
		return kStatus_Success;
	}
	else
	{
		return kStatus_Fail;
	}
}
