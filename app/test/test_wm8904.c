/**
 * @file test_wm8904.c
 * @author qiaoqiming
 * @brief 测试wm8904
 * @version 1.0
 * @date 2019-05-13
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "bsp_wm8904.h"
#include "fsl_common.h"
#include "fsl_dma.h"
#include "fsl_i2s_dma.h"
#include "compile.h"

/**
 * @brief 正弦波
 */
__ALIGN_BEGIN uint8_t g_Music[] __ALIGN_END = {
    0x00U, 0x00U, 0x00U, 0x00U, 0x71U, 0x07U, 0x71U, 0x07U, 0xDCU, 0x0EU, 0xDCU, 0x0EU, 0x39U, 0x16U, 0x39U, 0x16U,
    0x84U, 0x1DU, 0x84U, 0x1DU, 0xB5U, 0x24U, 0xB5U, 0x24U, 0xC6U, 0x2BU, 0xC6U, 0x2BU, 0xB2U, 0x32U, 0xB2U, 0x32U,
    0x71U, 0x39U, 0x71U, 0x39U, 0xFFU, 0x3FU, 0xFFU, 0x3FU, 0x55U, 0x46U, 0x55U, 0x46U, 0x6FU, 0x4CU, 0x6FU, 0x4CU,
    0x46U, 0x52U, 0x46U, 0x52U, 0xD6U, 0x57U, 0xD6U, 0x57U, 0x19U, 0x5DU, 0x19U, 0x5DU, 0x0CU, 0x62U, 0x0CU, 0x62U,
    0xABU, 0x66U, 0xABU, 0x66U, 0xF0U, 0x6AU, 0xF0U, 0x6AU, 0xD9U, 0x6EU, 0xD9U, 0x6EU, 0x61U, 0x72U, 0x61U, 0x72U,
    0x87U, 0x75U, 0x87U, 0x75U, 0x46U, 0x78U, 0x46U, 0x78U, 0x9EU, 0x7AU, 0x9EU, 0x7AU, 0x8BU, 0x7CU, 0x8BU, 0x7CU,
    0x0DU, 0x7EU, 0x0DU, 0x7EU, 0x21U, 0x7FU, 0x21U, 0x7FU, 0xC7U, 0x7FU, 0xC7U, 0x7FU, 0xFEU, 0x7FU, 0xFEU, 0x7FU,
    0xC7U, 0x7FU, 0xC7U, 0x7FU, 0x21U, 0x7FU, 0x21U, 0x7FU, 0x0DU, 0x7EU, 0x0DU, 0x7EU, 0x8BU, 0x7CU, 0x8BU, 0x7CU,
    0x9EU, 0x7AU, 0x9EU, 0x7AU, 0x46U, 0x78U, 0x46U, 0x78U, 0x87U, 0x75U, 0x87U, 0x75U, 0x61U, 0x72U, 0x61U, 0x72U,
    0xD9U, 0x6EU, 0xD9U, 0x6EU, 0xF0U, 0x6AU, 0xF0U, 0x6AU, 0xABU, 0x66U, 0xABU, 0x66U, 0x0CU, 0x62U, 0x0CU, 0x62U,
    0x19U, 0x5DU, 0x19U, 0x5DU, 0xD6U, 0x57U, 0xD6U, 0x57U, 0x46U, 0x52U, 0x46U, 0x52U, 0x6FU, 0x4CU, 0x6FU, 0x4CU,
    0x55U, 0x46U, 0x55U, 0x46U, 0xFFU, 0x3FU, 0xFFU, 0x3FU, 0x71U, 0x39U, 0x71U, 0x39U, 0xB2U, 0x32U, 0xB2U, 0x32U,
    0xC6U, 0x2BU, 0xC6U, 0x2BU, 0xB5U, 0x24U, 0xB5U, 0x24U, 0x84U, 0x1DU, 0x84U, 0x1DU, 0x39U, 0x16U, 0x39U, 0x16U,
    0xDCU, 0x0EU, 0xDCU, 0x0EU, 0x71U, 0x07U, 0x71U, 0x07U, 0x00U, 0x00U, 0x00U, 0x00U, 0x8FU, 0xF8U, 0x8FU, 0xF8U,
    0x24U, 0xF1U, 0x24U, 0xF1U, 0xC7U, 0xE9U, 0xC7U, 0xE9U, 0x7CU, 0xE2U, 0x7CU, 0xE2U, 0x4BU, 0xDBU, 0x4BU, 0xDBU,
    0x3AU, 0xD4U, 0x3AU, 0xD4U, 0x4EU, 0xCDU, 0x4EU, 0xCDU, 0x8FU, 0xC6U, 0x8FU, 0xC6U, 0x01U, 0xC0U, 0x01U, 0xC0U,
    0xABU, 0xB9U, 0xABU, 0xB9U, 0x91U, 0xB3U, 0x91U, 0xB3U, 0xBAU, 0xADU, 0xBAU, 0xADU, 0x2AU, 0xA8U, 0x2AU, 0xA8U,
    0xE7U, 0xA2U, 0xE7U, 0xA2U, 0xF4U, 0x9DU, 0xF4U, 0x9DU, 0x55U, 0x99U, 0x55U, 0x99U, 0x10U, 0x95U, 0x10U, 0x95U,
    0x27U, 0x91U, 0x27U, 0x91U, 0x9FU, 0x8DU, 0x9FU, 0x8DU, 0x79U, 0x8AU, 0x79U, 0x8AU, 0xBAU, 0x87U, 0xBAU, 0x87U,
    0x62U, 0x85U, 0x62U, 0x85U, 0x75U, 0x83U, 0x75U, 0x83U, 0xF3U, 0x81U, 0xF3U, 0x81U, 0xDFU, 0x80U, 0xDFU, 0x80U,
    0x39U, 0x80U, 0x39U, 0x80U, 0x02U, 0x80U, 0x02U, 0x80U, 0x39U, 0x80U, 0x39U, 0x80U, 0xDFU, 0x80U, 0xDFU, 0x80U,
    0xF3U, 0x81U, 0xF3U, 0x81U, 0x75U, 0x83U, 0x75U, 0x83U, 0x62U, 0x85U, 0x62U, 0x85U, 0xBAU, 0x87U, 0xBAU, 0x87U,
    0x79U, 0x8AU, 0x79U, 0x8AU, 0x9FU, 0x8DU, 0x9FU, 0x8DU, 0x27U, 0x91U, 0x27U, 0x91U, 0x10U, 0x95U, 0x10U, 0x95U,
    0x55U, 0x99U, 0x55U, 0x99U, 0xF4U, 0x9DU, 0xF4U, 0x9DU, 0xE7U, 0xA2U, 0xE7U, 0xA2U, 0x2AU, 0xA8U, 0x2AU, 0xA8U,
    0xBAU, 0xADU, 0xBAU, 0xADU, 0x91U, 0xB3U, 0x91U, 0xB3U, 0xABU, 0xB9U, 0xABU, 0xB9U, 0x01U, 0xC0U, 0x01U, 0xC0U,
    0x8FU, 0xC6U, 0x8FU, 0xC6U, 0x4EU, 0xCDU, 0x4EU, 0xCDU, 0x3AU, 0xD4U, 0x3AU, 0xD4U, 0x4BU, 0xDBU, 0x4BU, 0xDBU,
    0x7CU, 0xE2U, 0x7CU, 0xE2U, 0xC7U, 0xE9U, 0xC7U, 0xE9U, 0x24U, 0xF1U, 0x24U, 0xF1U, 0x8FU, 0xF8U, 0x8FU, 0xF8U,
};

__ALIGN_BEGIN static uint8_t s_Buffer[400] __ALIGN_END; /* 100 samples => time about 2 ms */
static i2s_transfer_t s_TxTransfer;
static i2s_transfer_t s_RxTransfer;
static i2s_dma_handle_t s_TxHandle;
static i2s_dma_handle_t s_RxHandle;

static void TxCallback(I2S_Type *base, i2s_dma_handle_t *handle, status_t completionStatus, void *userData)
{
    /* Enqueue the same original buffer all over again */
    i2s_transfer_t *transfer = (i2s_transfer_t *)userData;
    I2S_TxTransferSendDMA(base, handle, *transfer);
}

static void RxCallback(I2S_Type *base, i2s_dma_handle_t *handle, status_t completionStatus, void *userData)
{
    /* Enqueue the same original buffer all over again */
    i2s_transfer_t *transfer = (i2s_transfer_t *)userData;
    I2S_RxTransferReceiveDMA(base, handle, *transfer);
}


void StartSoundPlayback(void)
{
    printfk("Setup looping playback of sine wave\r\n");

    s_TxTransfer.data = &g_Music[0];
    s_TxTransfer.dataSize = sizeof(g_Music);

    I2S_TxTransferCreateHandleDMA(WM8904_I2S_TX, &s_TxHandle, &s_DmaTxHandle, TxCallback, (void *)&s_TxTransfer);
    /* need to queue two transmit buffers so when the first one
     * finishes transfer, the other immediatelly starts */
    I2S_TxTransferSendDMA(WM8904_I2S_TX, &s_TxHandle, s_TxTransfer);
    I2S_TxTransferSendDMA(WM8904_I2S_TX, &s_TxHandle, s_TxTransfer);
}

void StartDigitalLoopback(void)
{
    printfk("Setup digital loopback\r\n");

    s_TxTransfer.data = &s_Buffer[0];
    s_TxTransfer.dataSize = sizeof(s_Buffer);

    s_RxTransfer.data = &s_Buffer[0];
    s_RxTransfer.dataSize = sizeof(s_Buffer);

    I2S_TxTransferCreateHandleDMA(WM8904_I2S_TX, &s_TxHandle, &s_DmaTxHandle, TxCallback, (void *)&s_TxTransfer);
    I2S_RxTransferCreateHandleDMA(WM8904_I2S_RX, &s_RxHandle, &s_DmaRxHandle, RxCallback, (void *)&s_RxTransfer);

    /* need to queue two receive buffers so when the first one is filled,
     * the other is immediatelly starts to be filled */
    I2S_RxTransferReceiveDMA(WM8904_I2S_RX, &s_RxHandle, s_RxTransfer);
    I2S_RxTransferReceiveDMA(WM8904_I2S_RX, &s_RxHandle, s_RxTransfer);

    /* need to queue two transmit buffers so when the first one
     * finishes transfer, the other immediatelly starts */
    I2S_TxTransferSendDMA(WM8904_I2S_TX, &s_TxHandle, s_TxTransfer);
    I2S_TxTransferSendDMA(WM8904_I2S_TX, &s_TxHandle, s_TxTransfer);
}
