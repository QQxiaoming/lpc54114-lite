/**
 * @file test_mp3_decode.c
 * @author qiaoqiming
 * @brief mp3解码测试
 * @version 1.0
 * @date 2019-05-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "mp3dec.h"
#include "ff.h"
#include "fsl_debug_console.h"
#include <stdint.h>


FIL f_mp3; 
FIL f_pcm; 
uint8_t mp3_buf[4000];
HMP3Decoder mp3_decoder;
MP3FrameInfo mp3_framer;
short pcm_buf[2304];

void decode_mp3(void)
{
    FRESULT f_res;
    unsigned int br;
    int byteleft = 0;
    int offset;
    uint8_t *decode_ptr = mp3_buf;
    int ret;

    mp3_decoder = MP3InitDecoder();
    if(mp3_decoder == NULL)
    {
        printfk("init err!\r\n");
        return;
    }

    f_res = f_open(&f_pcm, "4:test.pcm",FA_WRITE | FA_CREATE_ALWAYS);
    f_res = f_open(&f_mp3, "4:test128.mp3",FA_OPEN_EXISTING | FA_READ);
    if (f_res == FR_OK)
    {
        printfk("open mp3 file ok!\r\n");
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
                ret = MP3Decode(mp3_decoder,&decode_ptr,&byteleft,pcm_buf,0);
                MP3GetLastFrameInfo(mp3_decoder, &mp3_framer);
                if(ret == ERR_MP3_NONE && mp3_framer.samprate == 44100)
                {
                    printfk("once decode,file size is %d\r\n",f_size(&f_mp3)-f_tell(&f_mp3));
                    f_write(&f_pcm,pcm_buf,2304*sizeof(short),&br);
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

            memmove(mp3_buf,decode_ptr,byteleft);
        }
        f_close(&f_mp3);
        f_close(&f_pcm);
    }

    MP3FreeDecoder(mp3_decoder);

    printfk("end\r\n");
}