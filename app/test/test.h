/**
 * @file test.h
 * @author qiaoqiming
 * @brief 测试代码声明文件
 * @version 1.0
 * @date 2019-05-13
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _TEST_H_
#define _TEST_H_

#if defined(__cplusplus)
"C" {
#endif /* __cplusplus */

void test_fatfs(void);
void test_pct2075(void);
void test_adc(void);
void decode_aac(void);
void decode_mp3(void);
void StartSoundPlayback(void);
void StartDigitalLoopback(void);

void audio_play_init(void);
void vUARTCommandConsoleInit( void );
void vRegisterCLICommands( void );
void vUARTCommandConsoleStart( uint16_t usStackSize, UBaseType_t uxPriority );

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _TEST_H_ */
