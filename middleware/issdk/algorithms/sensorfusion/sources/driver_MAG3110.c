/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*! \file driver_MAG3110.c
    \brief Provides init() and read() functions for the MAG3110 magnetometer.
*/

#include "board.h"                      // generated by Kinetis Expert.  Long term - merge sensor_board.h into this file
#include "sensor_fusion.h"              // Sensor fusion structures and types
#include "sensor_drv.h"
#include "sensor_io_i2c.h"              // Required for registerreadlist_t / registerwritelist_t declarations
#include "drivers.h"                    // Device specific drivers supplied by NXP (can be replaced with user drivers)
#include "mag3110.h"
#define MAG3110_COUNTSPERUT 10						// fixed range for MAG3110 magnetometer

#if F_USING_MAG

// Command definition to read the WHO_AM_I value.
const registerreadlist_t    MAG3110_WHO_AM_I_READ[] =
{
    { .readFrom = MAG3110_WHO_AM_I, .numBytes = 1 }, __END_READ_DATA__
};

// Command definition to read the number of entries in the accel FIFO.
const registerreadlist_t    MAG3110_DR_STATUS_READ[] =
{
    { .readFrom = MAG3110_DR_STATUS, .numBytes = 1 }, __END_READ_DATA__
};

// Command definition to read the converted result
registerreadlist_t          MAG3110_DATA_READ[] =
{
    { .readFrom = MAG3110_OUT_X_MSB, .numBytes = 6 }, __END_READ_DATA__
};

// Each entry in a RegisterWriteList is composed of: register address, value to write, bit-mask to apply to write (0 enables)
const registerwritelist_t   MAG3110_Initialization[] =
{
    // write 0000 0000 = 0x00 to CTRL_REG1 to place MAG3110 into standby
    // [7-1] = 0000 000
    // [0]: AC=0 for standby
    { MAG3110_CTRL_REG1, 0x00, 0x00 },

    // write 1001 0000 = 0x90 to CTRL_REG2
    // [7]: AUTO_MRST_EN=1: enable degaussing
    // [6]: unused=0
    // [5]: RAW=0: normal mode
    // [4]: Mag_RST=1: enable a single degauss
    // [3-0]: unused=0
    { MAG3110_CTRL_REG2, 0x90, 0x00 },

    // write 000X X001 to CTRL_REG1 to set ODR and take MAG3110 out of standby
    // [7-5]: DR=000 for 1280Hz ADC (to give best noise performance)
    // [4-3]: OS=11 for 10Hz ODR giving 0x19
    // [4-3]: OS=10 for 20Hz ODR giving 0x11
    // [4-3]: OS=01 for 40Hz ODR giving 0x09
    // [4-3]: OS=00 for 80Hz ODR giving 0x01
    // [2]: FT=0 for normal reads
    // [1]: TM=0 to not trigger immediate measurement
    // [0]: AC=1 for active mode
#if (MAG_ODR_HZ <= 10) // select 10Hz ODR
    { MAG3110_CTRL_REG1, 0x19, 0x00 },
#elif (MAG_ODR_HZ <= 30) // select 20Hz ODR (to give lower noise with standard 25Hz build)
    { MAG3110_CTRL_REG1, 0x11, 0x00 },
#elif (MAG_ODR_HZ <= 40) // select 40Hz ODR
    { MAG3110_CTRL_REG1, 0x09, 0x00 },
#else // select 80Hz ODR
    { MAG3110_CTRL_REG1, 0x01, 0x00 },
#endif
     __END_WRITE_DATA__
};

// All sensor drivers and initialization functions have the same prototype.
// sfg is a pointer to the master "global" sensor fusion structure.
// sensor = pointer to linked list element used by the sensor fusion subsystem to specify required sensors
//#pragma optimize=no_scheduling
int8_t MAG3110_Init(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg)
{
    int32_t status;
    uint8_t reg;
    status = Register_I2C_Read(sensor->bus_driver, &sensor->deviceInfo, sensor->addr, MAG3110_WHO_AM_I, 1, &reg);
    if (status==SENSOR_ERROR_NONE) {
        sfg->Mag.iWhoAmI = reg;
        if (reg!=MAG3110_WHOAMI_VALUE) {
             return(SENSOR_ERROR_INIT);
        }
    } else {
        // iWhoAmI will return default value of zero
        // return with error
        return(SENSOR_ERROR_INIT);
    }

    // Configure and start the MAG3110 sensor.  This does multiple register writes
    // (see MAG3110_Initialization definition above)
    status = Sensor_I2C_Write(sensor->bus_driver, &sensor->deviceInfo, sensor->addr, MAG3110_Initialization );

    // Stash some needed constants in the SF data structure for this sensor
    sfg->Mag.iCountsPeruT = MAG3110_COUNTSPERUT;
    sfg->Mag.fCountsPeruT = (float)MAG3110_COUNTSPERUT; // IAR optimized this out without the #pragma before the function
    sfg->Mag.fuTPerCount = 1.0F / MAG3110_COUNTSPERUT;  // IAR optimized this out without the #pragma before the function

    sensor->isInitialized = F_USING_MAG;        // IAR optimized this out without the #pragma before the function
    sfg->Mag.isEnabled = true;                  // IAR optimized this out without the #pragma before the function

    return (status);
}

int8_t MAG3110_Read(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg)
{
    uint8_t                     I2C_Buffer[6];  // I2C read buffer
    int8_t                      status;         // I2C transaction status
    int16_t                     sample[3];      // Reconstructed sample

    if(sensor->isInitialized != F_USING_MAG)
    {
        return SENSOR_ERROR_INIT;
    }

    status =  Sensor_I2C_Read(sensor->bus_driver, &sensor->deviceInfo, sensor->addr, MAG3110_DATA_READ, I2C_Buffer );
    sample[CHX] = (I2C_Buffer[0] << 8) | I2C_Buffer[1];
    sample[CHY] = (I2C_Buffer[2] << 8) | I2C_Buffer[3];
    sample[CHZ] = (I2C_Buffer[4] << 8) | I2C_Buffer[5];
    if (status==SENSOR_ERROR_NONE) {
        conditionSample(sample);  // truncate negative values to -32767
        sample[CHZ] = -sample[CHZ];  // +Z should point up (MAG3110 Z positive is down)
        addToFifo((union FifoSensor*) &(sfg->Mag), MAG_FIFO_SIZE, sample);
    }

    return (status);
}


// Each entry in a RegisterWriteList is composed of: register address, value to write, bit-mask to apply to write (0 enables)
const registerwritelist_t   MAG3110_IDLE[] =
{
  // Set ACTIVE = 0
  { MAG3110_CTRL_REG1, 0x00, 0x00 },
    __END_WRITE_DATA__
};

// MAG3110_Idle places the sensor into STANDBY mode (wakeup time = 25ms at ODR = 80Hz)
int8_t MAG3110_Idle(struct PhysicalSensor *sensor, SensorFusionGlobals *sfg)
{
    int32_t     status;
    if(sensor->isInitialized == F_USING_MAG) {
        status = Sensor_I2C_Write(sensor->bus_driver, &sensor->deviceInfo, sensor->addr, MAG3110_IDLE );
        sensor->isInitialized = 0;
        sfg->Mag.isEnabled = false;
    } else {
      return SENSOR_ERROR_INIT;
    }
    return status;
}

#endif
