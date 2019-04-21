/**
 * @file pin_mux.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-04-15
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "fsl_common.h"
#include "fsl_iocon.h"
#include "pin_mux.h"


#define PORT0_IDX 0u
#define PORT1_IDX 1u

#define PIN0_IDX 0u
#define PIN1_IDX 1u                   
#define PIN2_IDX 2u
#define PIN3_IDX 3u
#define PIN4_IDX 4u 
#define PIN5_IDX 5u 
#define PIN6_IDX 6u 
#define PIN7_IDX 7u 
#define PIN8_IDX 8u 
#define PIN9_IDX 9u 
#define PIN10_IDX 10u 
#define PIN11_IDX 11u 
#define PIN12_IDX 12u 
#define PIN13_IDX 13u 
#define PIN14_IDX 14u 
#define PIN15_IDX 15u 
#define PIN16_IDX 16u 
#define PIN17_IDX 17u 
#define PIN18_IDX 18u 
#define PIN19_IDX 19u 
#define PIN20_IDX 20u 
#define PIN21_IDX 21u 
#define PIN22_IDX 22u 
#define PIN23_IDX 23u 
#define PIN24_IDX 24u 
#define PIN25_IDX 25u 
#define PIN26_IDX 26u 
#define PIN27_IDX 27u 
#define PIN28_IDX 28u 
#define PIN29_IDX 29u 
#define PIN30_IDX 30u 
#define PIN31_IDX 31u 


/**
 * @brief Function assigned for the Cortex-M4F
 * 
 */
void BOARD_InitPins_Core0(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);

    /* Flexcomm Interface 0: USART RXD */ /* UART_RX - debug */
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN0_IDX, IOCON_FUNC1 | IOCON_DIGITAL_EN | IOCON_INPFILT_OFF);
    /* Flexcomm Interface 0: USART TXD */ /* UART_TX - debug */
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN1_IDX, IOCON_FUNC1 | IOCON_DIGITAL_EN | IOCON_INPFILT_OFF);

    /* Flexcomm Interface 3: SPI SSEL3 */ /* SPI_CS - FLASH */
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN2_IDX, IOCON_FUNC2 | IOCON_MODE_PULLUP | IOCON_GPIO_MODE | IOCON_DIGITAL_EN);
    /* Flexcomm Interface 2: SPI SSEL2 */ /* SPI_CS - TF */
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN3_IDX, IOCON_FUNC2 | IOCON_MODE_PULLUP | IOCON_GPIO_MODE | IOCON_DIGITAL_EN);

    /* Flexcomm Interface 6: I2S data */ /* I2S_RXD - wm8904 */
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN5_IDX, IOCON_FUNC1 | IOCON_DIGITAL_EN);
    /* Flexcomm Interface 6: I2S WS */ 
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN6_IDX, IOCON_FUNC1 | IOCON_DIGITAL_EN);
    /* Flexcomm Interface 6: I2S clock */ 
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN7_IDX, IOCON_FUNC1 | IOCON_DIGITAL_EN);

    /* Flexcomm Interface 2: SPI MOSI */ /* SPI_MOSI - FLASH/TF */
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN8_IDX, IOCON_FUNC1 | IOCON_MODE_PULLUP | IOCON_GPIO_MODE | IOCON_DIGITAL_EN);
    /* Flexcomm Interface 2: SPI MISO */ /* SPI_MISO - FLASH/TF */
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN9_IDX, IOCON_FUNC1 | IOCON_MODE_PULLUP | IOCON_GPIO_MODE | IOCON_DIGITAL_EN);
    /* Flexcomm Interface 2: SPI clock */ /* SPI_SCK - FLASH/TF */
    IOCON_PinMuxSet(IOCON, PORT0_IDX, PIN10_IDX, IOCON_FUNC1 | IOCON_MODE_PULLUP | IOCON_GPIO_MODE | IOCON_DIGITAL_EN);

    /* Flexcomm Interface 4: I2C SCL */ /* I2C_SCLK - wm8904 */
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN1_IDX, IOCON_FUNC5 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN | IOCON_INPFILT_OFF);
    /* Flexcomm Interface 4: I2C SDA */ /* I2C_SDA - wm8904 */    
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN2_IDX, IOCON_FUNC5 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN | IOCON_INPFILT_OFF);

    /* Flexcomm Interface 7: I2S clock */ /* I2S_BCLK - wm8904 */
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN12_IDX, IOCON_FUNC4 | IOCON_DIGITAL_EN);
    /* Flexcomm Interface 7: I2S DATA */ /* I2S_TXD - wm8904 */
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN13_IDX, IOCON_FUNC4 | IOCON_DIGITAL_EN);
    /* Flexcomm Interface 7: I2S WS */ /* I2S_LRCLK - wm8904 */
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN14_IDX, IOCON_FUNC4 | IOCON_DIGITAL_EN);

    /* PDM0_CLK  */ /* CLK - SPH0641LM4H */
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN15_IDX, IOCON_FUNC1 | IOCON_DIGITAL_EN);
    /* PDM0_DATA  */ /* Dout - SPH0641LM4H */    
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN16_IDX, IOCON_FUNC1 | IOCON_DIGITAL_EN);

    /* MCLK */ /* I2S_MCLK - wm8904 */
    IOCON_PinMuxSet(IOCON, PORT1_IDX, PIN17_IDX, IOCON_FUNC4 | IOCON_MODE_INACT | IOCON_DIGITAL_EN);
    SYSCON->MCLKIO = 1U;
}

/**
 * @brief Function assigned for the Cortex-M0P
 * 
 */
void BOARD_InitPins_Core1(void)
{
}
