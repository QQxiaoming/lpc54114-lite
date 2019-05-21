#include <stdint.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "ff.h"
#include "diskio.h"
#include "bsp_wm8904.h"
#include "fsl_debug_console.h"
#include "mp3dec.h"

#if defined(__GNUC__) /* GNU Compiler */
#ifndef __ALIGN_END
#define __ALIGN_END __attribute__((aligned(4)))
#endif
#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN
#endif
#else
#ifndef __ALIGN_END
#define __ALIGN_END
#endif
#ifndef __ALIGN_BEGIN
#if defined(__CC_ARM) || defined(__ARMCC_VERSION) /* ARM Compiler */
#define __ALIGN_BEGIN __attribute__((aligned(4)))
#elif defined(__ICCARM__) /* IAR Compiler */
#define __ALIGN_BEGIN
#endif
#endif
#endif

#define OUT_SIZE (4608)
#define BUFF_MAX 3

static FATFS g_fileSystem; /* File system object */
const TCHAR driverNumberBuffer[3U] = {SDSPIDISK + '0', ':', '/'};
static QueueHandle_t audio_data_addr = NULL;
static i2s_transfer_t audio_transfer;
static i2s_dma_handle_t audio_dma_handle;
__ALIGN_BEGIN static uint8_t audio_voice_buff[OUT_SIZE] __ALIGN_END;
FIL f_mp3; 
FIL f_pcm; 
uint8_t mp3_buf[4000];
HMP3Decoder mp3_decoder;
MP3FrameInfo mp3_framer;
short pcm_buf[BUFF_MAX][OUT_SIZE/2];

/**
 * @brief 播放数据读取任务
 * 
 * @param pvParameters 
 */
static void audio_data_reader(void *pvParameters)
{
    FRESULT f_res;
    unsigned int br;
    int byteleft = 0;
    int offset;
    uint8_t *decode_ptr = mp3_buf;
    int ret;
    int buf_count = 0;
    short *curr_buf = pcm_buf[buf_count];
    uint32_t buff_addr = (uint32_t)curr_buf;

    /* spisd文件系统初始化 */
    f_mount(&g_fileSystem, driverNumberBuffer, 1);

    mp3_decoder = MP3InitDecoder();
    if(mp3_decoder == NULL)
    {
        PRINTF("init err!\r\n");
        return;
    }

    f_res = f_open(&f_mp3, "4:test128.mp3",FA_OPEN_EXISTING | FA_READ);
    //f_res = f_open(&f_pcm, "4:test.pcm",FA_WRITE | FA_CREATE_ALWAYS);
    if (f_res == FR_OK)
    {
        PRINTF("open mp3 file ok!\r\n");
        while(f_size(&f_mp3)-f_tell(&f_mp3) >= byteleft)
        {
            f_read(&f_mp3,mp3_buf+byteleft,4000-byteleft,&br);

            byteleft = 4000;	
            decode_ptr = mp3_buf; 
            
            offset = MP3FindSyncWord(mp3_buf,byteleft);
            if(offset != -1)
            {
                byteleft -= offset;
                decode_ptr += offset;
                while(uxQueueMessagesWaiting(audio_data_addr) == BUFF_MAX)
                {
                    vTaskDelay(2);
                }
                ret = MP3Decode(mp3_decoder,&decode_ptr,&byteleft,curr_buf,0);
                MP3GetLastFrameInfo(mp3_decoder, &mp3_framer);
                if(ret == ERR_MP3_NONE && mp3_framer.samprate == 44100)
                {
                    //PRINTF("once decode,file size is %d\r\n",f_size(&f_mp3)-f_tell(&f_mp3));

                    xQueueSend(audio_data_addr,&buff_addr,portMAX_DELAY);
                    buf_count++;
                    if(buf_count >= BUFF_MAX)
                    {
                        buf_count = 0;
                    }
                    curr_buf = pcm_buf[buf_count];
                    buff_addr = (uint32_t)curr_buf;
                    //f_write(&f_pcm,pcm_buf,2304*sizeof(short),&br);
                }
                else
                {
                    PRINTF("mp3_decord err %d,bad frame!,remove 2byte,detect next\r\n",ret);
				    decode_ptr += 2;
				    byteleft   -= 2;
                }
            }
            else
            {
                decode_ptr += 3800;
				byteleft   -= 3800; 
            }

            memmove(mp3_buf,decode_ptr,byteleft);
        }
        f_close(&f_mp3);
        f_close(&f_pcm);
    }

    MP3FreeDecoder(mp3_decoder);

    PRINTF("end\r\n");
    
    I2S_TransferAbortDMA(WM8904_I2S_TX,&audio_dma_handle);
    
    vTaskDelete(NULL);
}

static void audio_callback(I2S_Type *base, i2s_dma_handle_t *handle, status_t completionStatus, void *userData)
{
    static bool is_mute = false;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint32_t data_addr;

    if(xQueuePeekFromISR(audio_data_addr, &data_addr) == pdTRUE)
    {
        if(is_mute)
        {
            WM8904_SetMute(&codecHandle,false,false);
            is_mute = false;
        }

        memcpy(audio_voice_buff,(void *)data_addr,OUT_SIZE);
        xQueueReceiveFromISR(audio_data_addr, &data_addr,&xHigherPriorityTaskWoken);

        audio_transfer.data = &audio_voice_buff[0];
        audio_transfer.dataSize = sizeof(audio_voice_buff);
        I2S_TxTransferSendDMA(base, handle, audio_transfer);
    }
    else
    {
        if(!is_mute)
        {
            WM8904_SetMute(&codecHandle,true,true);
            is_mute = true;
        }
        PRINTF("peek err\r\n");
        I2S_TxTransferSendDMA(base, handle, *(i2s_transfer_t *)userData);
    }
}


/**
 * @brief 播放数据读取任务
 * 
 * @param pvParameters 
 */
static void audio_play_voice(void *pvParameters)
{
    uint32_t data_addr;

    vTaskDelay(pdMS_TO_TICKS(1000*2));

    xQueuePeek(audio_data_addr, &data_addr, portMAX_DELAY);
    memcpy(audio_voice_buff,(void *)data_addr,OUT_SIZE);
    xQueueReceive(audio_data_addr, &data_addr, 0);

    audio_transfer.data = &audio_voice_buff[0];
    audio_transfer.dataSize = sizeof(audio_voice_buff)/2;

    I2S_TxTransferCreateHandleDMA(WM8904_I2S_TX, &audio_dma_handle, &s_DmaTxHandle, audio_callback, (void *)&audio_transfer);
    I2S_TxTransferSendDMA(WM8904_I2S_TX, &audio_dma_handle, audio_transfer);

    audio_transfer.data = &audio_voice_buff[2304];
    audio_transfer.dataSize = sizeof(audio_voice_buff)/2;
    I2S_TxTransferSendDMA(WM8904_I2S_TX, &audio_dma_handle, audio_transfer);

    vTaskDelete(NULL);
}


void audio_play_init(void)
{
    audio_data_addr = xQueueCreate(BUFF_MAX, sizeof(uint32_t));
    xTaskCreate(audio_data_reader, "audio_data_reader", 512, NULL, 3, NULL);
    xTaskCreate(audio_play_voice, "audio_play_voice", 512, NULL, 3, NULL);
}