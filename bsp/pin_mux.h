/**
 * @brief 
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
