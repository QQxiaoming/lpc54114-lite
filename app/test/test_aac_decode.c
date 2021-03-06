/**
 * @file test_aac_decode.c
 * @author qiaoqiming
 * @brief aac解码测试
 * @version 1.0
 * @date 2019-05-17
 */
#include "aacdec.h"
#include "ff.h"
#include "fsl_debug_console.h"
#include <stdint.h>
#include "UARTCommandConsole.h"


#ifdef AAC_ENABLE_SBR
#define SBR_MUL		2
#else
#define SBR_MUL		1
#endif
#define READBUF_SIZE (2 * AAC_MAINBUF_SIZE * AAC_MAX_NCHANS)

FIL f_aac; 
FIL f_pcm; 
uint8_t aac_buf[READBUF_SIZE];
HAACDecoder aac_decoder;
AACFrameInfo aac_framer;
short pcm_buf[AAC_MAX_NCHANS * AAC_MAX_NSAMPS * SBR_MUL];

void decode_aac(void)
{
    FRESULT f_res;
    unsigned int br;
    int byteleft = 0;
    int offset;
    uint8_t *decode_ptr = aac_buf;
    int ret;

    aac_decoder = AACInitDecoder();
    if(aac_decoder == NULL)
    {
        printfk("init err!\r\n");
        return;
    }

    f_res = f_open(&f_pcm, "4:test.pcm",FA_WRITE | FA_CREATE_ALWAYS);
    f_res = f_open(&f_aac, "4:test128.aac",FA_OPEN_EXISTING | FA_READ);
    if (f_res == FR_OK)
    {
        printfk("open aac file ok!\r\n");
        while(f_size(&f_aac)-f_tell(&f_aac) >= byteleft)
        {
            f_read(&f_aac,aac_buf+byteleft,READBUF_SIZE-byteleft,&br);
            byteleft = READBUF_SIZE;	
            decode_ptr = aac_buf; 

            offset = AACFindSyncWord(aac_buf,byteleft);
            if(offset != -1)
            {
                byteleft -= offset;
                decode_ptr += offset;
                ret = AACDecode(aac_decoder, &decode_ptr, &byteleft, pcm_buf);
                AACGetLastFrameInfo(aac_decoder, &aac_framer);
                if (ret == ERR_AAC_NONE)
                {
                    printfk("once decode,file size is %d\r\n",f_size(&f_aac)-f_tell(&f_aac));
                    f_write(&f_pcm,pcm_buf,(aac_framer.bitsPerSample/8)*aac_framer.outputSamps,&br);
                }
                else
                {
                    printfk("mp3_decord err %d,bad frame!,remove 2byte,detect next\r\n",ret);
				    decode_ptr += 2;
				    byteleft   -= 2;
                }
            }
            else
            {
                decode_ptr += 3800;
				byteleft   -= 3800; 
            }
            
            memmove(aac_buf,decode_ptr,byteleft);
        }

        f_close(&f_aac);
        f_close(&f_pcm);
    }

    AACFreeDecoder(aac_decoder);

    printfk("end\r\n");
}