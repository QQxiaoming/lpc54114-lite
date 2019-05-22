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


extern void decode_aac(void);
extern void decode_mp3(void);
extern void test_fatfs(void);
extern void StartSoundPlayback(void);
extern void StartDigitalLoopback(void);

extern void audio_play_init(void);

#endif /* _TEST_H_ */
