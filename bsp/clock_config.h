/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _CLOCK_CONFIG_H_
#define _CLOCK_CONFIG_H_

#include "fsl_common.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

#define BOARD_XTAL0_CLK_HZ                         12000000U  /*!< Board xtal0 frequency in Hz */
#define BOARD_XTAL32K_CLK_HZ                       32768U     /*!< Board xtal32K frequency in Hz */

#define BOARD_BOOTCLOCKFRO12M_CORE_CLOCK           12000000U  /*!< Core clock frequency: 12000000Hz */
void BOARD_BootClockFRO12M(void);

#define BOARD_BOOTCLOCKFROHF48M_CORE_CLOCK         48000000U  /*!< Core clock frequency: 48000000Hz */
void BOARD_BootClockFROHF48M(void);

#define BOARD_BOOTCLOCKFROHF96M_CORE_CLOCK         96000000U  /*!< Core clock frequency: 96000000Hz */
void BOARD_BootClockFROHF96M(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* _CLOCK_CONFIG_H_ */

