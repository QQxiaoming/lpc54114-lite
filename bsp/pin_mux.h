/**
 * @brief 
 * 
 */
#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_


#if defined(__cplusplus)
extern "C" {
#endif

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
  kPIN_MUX_DirectionInput = 0U,         /* Input direction */
  kPIN_MUX_DirectionOutput = 1U,        /* Output direction */
  kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;


/* FC0_RXD_SDA_MOSI (number 31), U18[4]/TO_MUX_P0_0-ISP_RX */
#define BOARD_INITPINS_CORE0_DEBUG_UART_RX_PERIPHERAL                  FLEXCOMM0   /*!< Device name: FLEXCOMM0 */
#define BOARD_INITPINS_CORE0_DEBUG_UART_RX_SIGNAL                   RXD_SDA_MOSI   /*!< FLEXCOMM0 signal: RXD_SDA_MOSI */
#define BOARD_INITPINS_CORE0_DEBUG_UART_RX_PIN_NAME             FC0_RXD_SDA_MOSI   /*!< Pin name */
#define BOARD_INITPINS_CORE0_DEBUG_UART_RX_LABEL     "U18[4]/TO_MUX_P0_0-ISP_RX"   /*!< Label */
#define BOARD_INITPINS_CORE0_DEBUG_UART_RX_NAME                  "DEBUG_UART_RX"   /*!< Identifier name */

/* FC0_TXD_SCL_MISO (number 32), U6[4]/U22[3]/P0_1-ISP_TX */
#define BOARD_INITPINS_CORE0_DEBUG_UART_TX_PERIPHERAL                  FLEXCOMM0   /*!< Device name: FLEXCOMM0 */
#define BOARD_INITPINS_CORE0_DEBUG_UART_TX_SIGNAL                   TXD_SCL_MISO   /*!< FLEXCOMM0 signal: TXD_SCL_MISO */
#define BOARD_INITPINS_CORE0_DEBUG_UART_TX_PIN_NAME             FC0_TXD_SCL_MISO   /*!< Pin name */
#define BOARD_INITPINS_CORE0_DEBUG_UART_TX_LABEL      "U6[4]/U22[3]/P0_1-ISP_TX"   /*!< Label */
#define BOARD_INITPINS_CORE0_DEBUG_UART_TX_NAME                  "DEBUG_UART_TX"   /*!< Identifier name */


void BOARD_InitPins_Core0(void); /* Function assigned for the Cortex-M4F */
void BOARD_InitPins_Core1(void); /* Function assigned for the Cortex-M0P */

#if defined(__cplusplus)
}
#endif


#endif /* _PIN_MUX_H_ */
