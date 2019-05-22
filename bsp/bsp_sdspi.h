/**
 * @file bsp_sdspi.h
 * @author qiaoqiming
 * @brief 板载spisd卡驱动
 * @version 1.0
 * @date 2019-04-15
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _BSP_SDSPI_H_
#define _BSP_SDSPI_H_

#include "fsl_sdspi.h"
#include "fsl_common.h"

extern sdspi_card_t g_card;
extern sdspi_host_t g_host;

/*************************************************************************************************
 * API - SPI interface
 ************************************************************************************************/
/*!
 * @brief Initializes the SPI.
 */
void spi_init(void);

/*!
 * @brief Sets the SPI bus frequency.
 *
 * @param frequency The frequency to set.
 * @retval kStatus_Success Success.
 * @retval kStatus_Fail Failed.
 */
status_t spi_set_frequency(uint32_t frequency);

/*!
 * @brief Transfers data over SPI bus in full-duplex way.
 *
 * @param in The buffer to save the data to be sent.
 * @param out The buffer to save the data to be read.
 * @param size The transfer data size.
 * @return The status of the function DSPI_MasterTransferPolling().
 */
status_t spi_exchange(uint8_t *in, uint8_t *out, uint32_t size);

/*!
 * @brief Initializes the timer to generator 1ms interrupt used to get current time in milliseconds.
 */
void timer_init(void);

/*!
 * @brief Gets current time in milliseconds.
 *
 * @return Current time in milliseconds.
 */
uint32_t timer_get_current_milliseconds(void);

/*!
 * @brief Initializes the host descriptor.
 */
void sdspi_host_init(void);

#endif /* _BSP_SDSPI_H_ */
