
#include "bsp_flash.h"
#include "mx25r_flash.h"
#include "fsl_common.h"
#include "fsl_iocon.h"
#include "fsl_spi.h"

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

uint8_t spiflash_init(void)
{
	spi_master_config_t masterConfig = {0};
	struct mx25r_rdid_result gIDResult;
		
	/* attach 12 MHz clock to SPI2 */
	CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);
    /* reset FLEXCOMM for SPI */
    RESET_PeripheralReset(kFC2_RST_SHIFT_RSTn);
	
	/* SPI2 pins */
	IOCON_PinMuxSet(IOCON, 0,  2, (IOCON_FUNC2 | IOCON_MODE_PULLUP | IOCON_GPIO_MODE | IOCON_DIGITAL_EN));  /* SPI2_CS - FLASH */
	IOCON_PinMuxSet(IOCON, 0, 10, (IOCON_FUNC1 | IOCON_MODE_PULLUP | IOCON_GPIO_MODE | IOCON_DIGITAL_EN));  /* SPI2_SCK        */
	IOCON_PinMuxSet(IOCON, 0,  8, (IOCON_FUNC1 | IOCON_MODE_PULLUP | IOCON_GPIO_MODE | IOCON_DIGITAL_EN));  /* SPI2_MOSI       */
	IOCON_PinMuxSet(IOCON, 0,  9, (IOCON_FUNC1 | IOCON_MODE_PULLUP | IOCON_GPIO_MODE | IOCON_DIGITAL_EN));  /* SPI2_MISO       */
	
	SPI_MasterGetDefaultConfig(&masterConfig);
	masterConfig.direction = kSPI_MsbFirst;
	masterConfig.polarity = kSPI_ClockPolarityActiveHigh;
	masterConfig.phase = kSPI_ClockPhaseFirstEdge;
	masterConfig.baudRate_Bps = 100000;
	masterConfig.sselNum = (spi_ssel_t)3; // use GPIO as CS is prefer
	SPI_MasterInit(SPI2, &masterConfig, CLOCK_GetFreq(kCLOCK_Flexcomm2));

    mx25r_init(&mx25r, flash_transfer_cb, SPI2);
	mx25r_cmd_rdid(&mx25r, &gIDResult);
	
	if( (gIDResult.manufacturer == 0x51) && (gIDResult.device[0] == 0x40) && (gIDResult.device[1] == 0x15) )
	{
		return 1;
	}
	return 0;
}