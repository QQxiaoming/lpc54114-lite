/**
 * @file test_mp3_decode.c
 * @author qiaoqiming
 * @brief mp3解码测试
 * @version 1.0
 * @date 2019-05-17
 */
#include "mp3dec.h"
#include "ff.h"
#include "fsl_debug_console.h"
#include <stdint.h>
#include "UARTCommandConsole.h"


FIL f_mp3; 
FIL f_pcm; 
uint8_t mp3_buf[4000];
HMP3Decoder mp3_decoder;
MP3FrameInfo mp3_framer;
short pcm_buf[2304];


/**
 * @brief 读取sd卡内的MP3文件并解码成pcm文件保存在sd卡内的测试示例
 * 
 */
void decode_mp3(void)
{
    FRESULT f_res;
    unsigned int br;
    int byteleft = 0;
    int offset;
    uint8_t *decode_ptr = mp3_buf;
    int ret;

    /* 初始化MP3解码器 */
    mp3_decoder = MP3InitDecoder();
    if(mp3_decoder == NULL)
    {
        printfk("init err!\r\n");
        return;
    }

    /* 打开mp3文件以及待输出的pcm文件 */
    f_res = f_open(&f_pcm, "4:test.pcm",FA_WRITE | FA_CREATE_ALWAYS);
    f_res = f_open(&f_mp3, "4:test128.mp3",FA_OPEN_EXISTING | FA_READ);
    if (f_res == FR_OK)
    {
        printfk("open mp3 file ok!\r\n");
        /* 循环解码mp3直到文件全部读取完成 */
        while(f_size(&f_mp3)-f_tell(&f_mp3) >= byteleft)
        {
            /* 第一次读取4000字节，循环之后补齐4000字节 */
            f_read(&f_mp3,mp3_buf+byteleft,4000-byteleft,&br);
            byteleft = 4000;	
            decode_ptr = mp3_buf; 
            
            /* 查找MP3流的帧头同步字偏移 */
            offset = MP3FindSyncWord(mp3_buf,byteleft);
            if(offset != -1)
            {
                byteleft -= offset;
                decode_ptr += offset;

                /* 成功读取后开始解码一帧 */
                ret = MP3Decode(mp3_decoder,&decode_ptr,&byteleft,pcm_buf,0);
                MP3GetLastFrameInfo(mp3_decoder, &mp3_framer);

                /* 确认解码结果的正确性 */
                if(ret == ERR_MP3_NONE && mp3_framer.samprate == 44100)
                {
                    printfk("once decode,file size is %d\r\n",f_size(&f_mp3)-f_tell(&f_mp3));
                    /* 写入文件系统 */
                    f_write(&f_pcm,pcm_buf,2304*sizeof(short),&br);
                }
                else
                {
                    /* 解码出错则跳过该同步字 */
                    printfk("mp3_decord err %d,bad frame!,remove 2byte,detect next\r\n",ret);
				    decode_ptr += 2;
				    byteleft   -= 2;
                }
            }
            else
            {
                /* 未能找到同步字则跳过这一包数据 */
                decode_ptr += 3998;
				byteleft   -= 3998; 
            }

            /* 未使用的数据移动到buf头部继续下一帧解码 */
            memmove(mp3_buf,decode_ptr,byteleft);
        }

        /* 完成后关闭文件 */
        f_close(&f_mp3);
        f_close(&f_pcm);
    }

    /* 释放MP3解码器 */
    MP3FreeDecoder(mp3_decoder);

    printfk("end\r\n");
}