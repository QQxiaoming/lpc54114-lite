/**
 * @file pin_mux.h
 * @author qiaoqiming
 * @brief 板级io管脚功能初始化
 * @version 1.0
 * @date 2019-04-15
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_


#if defined(__cplusplus)
extern "C" {
#endif

void BOARD_InitPins_Core0(void); /* Function assigned for the Cortex-M4F */
void BOARD_InitPins_Core1(void); /* Function assigned for the Cortex-M0P */

#if defined(__cplusplus)
}
#endif


#endif /* _PIN_MUX_H_ */
