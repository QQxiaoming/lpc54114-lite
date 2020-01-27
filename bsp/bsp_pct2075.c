/**
 * @file bsp_pct2075.c
 * @author qiaoqiming
 * @brief 板载pct2075驱动
 * @version 1.0
 * @date 2019-05-25
 */
#include "bsp_pct2075.h"
#include "fsl_i2c.h"


/**
 * @brief 读取pct2075温度数据
 * 
 * @param data 待返回数据地址
 * @return status_t 状态码
 */
status_t pct2075_i2c_read(float *data)
{
	status_t reVal = kStatus_Fail;
	uint8_t buf[2];

    i2c_master_transfer_t xfer;
    xfer.slaveAddress   = 0x4C;
    xfer.direction      = kI2C_Read;
    xfer.subaddress     = 0x00;
    xfer.subaddressSize = 1;
    xfer.data           = buf;
    xfer.dataSize       = 2;
    xfer.flags          = 0;
    
    reVal = I2C_MasterTransferBlocking(I2C4, &xfer);

    if( (buf[0]&0x80) == 0x00)
    {
        *data = ((float)( ((buf[0]<<8) + buf[1])>>5) * 0.125); 
    }
    else
    {
        *data = 0x800 - (((buf[0]<<8) + buf[1]) >> 5);
        *data = -(((float)(*data)) * 0.125); 
    }

    return reVal;
}

