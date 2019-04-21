/**
 * @file main_core0.c
 * @author qiaoqiming
 * @brief 
 * @version 0.1
 * @date 2019-04-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <string.h>
#include <stdio.h>
#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_debug_console.h"

#include "mcmgr.h"
#include "ff.h"
#include "diskio.h"

#include "board.h"
#include "bsp_led.h"
#include "bsp_dmic.h"
#include "bsp_flash.h"
#include "bsp_systick.h"
#include "bsp_wm8904.h"
#include "pin_mux.h"

#include "start_core1.h"

static FATFS g_fileSystem; /* File system object */
const TCHAR driverNumberBuffer[3U] = {SDSPIDISK + '0', ':', '/'};
FIL file;             /* 文件对象 */
FRESULT f_res;        /* 文件操作结果 */
UINT fnum;            /* 文件成功读写数量 */
char fpath[100];      /* 保存当前扫描路径 */
char readbuffer[512]; /*  */

/* FatFs多项功能测试 */
static FRESULT miscellaneous(void)
{
    DIR dir;
    FATFS *pfs;
    DWORD fre_clust, fre_sect, tot_sect;

    PRINTF("*************** 设备信息获取 ***************\r\n");
    /* 获取设备信息和空簇大小 */
    f_res = f_getfree("4:", &fre_clust, &pfs);

    /* 计算得到总的扇区个数和空扇区个数 */
    tot_sect = (pfs->n_fatent - 2) * pfs->csize;
    fre_sect = fre_clust * pfs->csize;

    /* 打印信息(4096 字节/扇区) */
    PRINTF(">设备总空间：%d KB。\r\n>可用空间：  %d KB。\r\n", tot_sect * 4, fre_sect * 4);

    PRINTF("******** 文件定位和格式化写入功能测试 ********\r\n");
    f_res = f_open(&file, "4:readme.TXT",
                   FA_OPEN_EXISTING | FA_WRITE | FA_READ);
    if (f_res == FR_OK)
    {
        /*  文件定位 */
        f_res = f_lseek(&file, f_size(&file) - 1);
        if (f_res == FR_OK)
        {
            /* 格式化写入，参数格式类似printf函数 */
            f_printf(&file, "在原来文件新添加一行内容\r\n");
            f_printf(&file, ">设备总空间：%d KB。\r\n>可用空间： %d KB。\r\n", tot_sect * 4, fre_sect * 4);
            /*  文件定位到文件起始位置 */
            f_res = f_lseek(&file, 0);
            /* 读取文件所有内容到缓存区 */
            f_res = f_read(&file, readbuffer, f_size(&file), &fnum);
            if (f_res == FR_OK)
            {
                PRINTF(">文件内容：\r\n%s\r\n", readbuffer);
            }
        }
        f_close(&file);

        PRINTF("\r\n********** 目录创建和重命名功能测试 **********\r\n");
        /* 尝试打开目录 */
        f_res = f_opendir(&dir, "4:TestDir");
        if (f_res != FR_OK)
        {
            /* 打开目录失败，就创建目录 */
            f_res = f_mkdir("4:TestDir");
        }
        else
        {
            /* 如果目录已经存在，关闭它 */
            f_res = f_closedir(&dir);
            /* 删除文件 */
            f_unlink("4:TestDir/testdir.txt");
        }
        if (f_res == FR_OK)
        {
            /* 重命名并移动文件 */
            f_res = f_rename("4:FatFs读写测试文件.txt", "4:TestDir/testdir.txt");
        }
    }
    else
    {
        PRINTF("!! 打开文件失败：%d\r\n", f_res);
        PRINTF("!! 或许需要再次运行“FatFs移植与读写测试”工程\r\n");
    }
    return f_res;
}

/**
  * 文件信息获取
  */
static FRESULT file_check(void)
{
    static FILINFO finfo;
    /* 获取文件信息 */
    f_res = f_stat("4:readme.TXT", &finfo);
    if (f_res == FR_OK)
    {
        PRINTF("readme.txt文件信息：\r\n");
        PRINTF(">文件大小: %d(字节)\r\n", finfo.fsize);
        PRINTF(">时间戳: %u/%02u/%02u, %02u:%02u\r\n",
               (finfo.fdate >> 9) + 1980, finfo.fdate >> 5 & 15, finfo.fdate & 31, finfo.ftime >> 11, finfo.ftime >> 5 & 63);
        PRINTF(">属性: %c%c%c%c%c\r\n\r\n",
               (finfo.fattrib & AM_DIR) ? 'D' : '-',  // 是一个目录
               (finfo.fattrib & AM_RDO) ? 'R' : '-',  // 只读文件
               (finfo.fattrib & AM_HID) ? 'H' : '-',  // 隐藏文件
               (finfo.fattrib & AM_SYS) ? 'S' : '-',  // 系统文件
               (finfo.fattrib & AM_ARC) ? 'A' : '-'); // 档案文件
    }
    return f_res;
}

/**
  * @brief  scan_files 递归扫描FatFs内的文件
  * @param  path:初始扫描路径
  * @retval result:文件系统的返回值
  */
static FRESULT scan_files(char *path)
{
    FRESULT res; //部分在递归过程被修改的变量，不用全局变量
    FILINFO fno;
    DIR dir;
    int i;
    char *fn; // 文件名

#if FF_USE_LFN
    /* 长文件名支持 */
    /* 简体中文需要2个字节保存一个“字”*/
    static char lfn[_MAX_LFN * 2 + 1];
    fno.lfname = lfn;
    fno.lfsize = sizeof(lfn);
#endif
    //打开目录
    res = f_opendir(&dir, path);
    if (res == FR_OK)
    {
        i = strlen(path);
        for (;;)
        {
            //读取目录下的内容，再读会自动读下一个文件
            res = f_readdir(&dir, &fno);
            //为空时表示所有项目读取完毕，跳出
            if (res != FR_OK || fno.fname[0] == 0)
                break;
#if FF_USE_LFN
            fn = *fno.lfname ? fno.lfname : fno.fname;
#else
            fn = fno.fname;
#endif
            //点表示当前目录，跳过
            if (*fn == '.')
                continue;
            //目录，递归读取
            if (fno.fattrib & AM_DIR)
            {
                //合成完整目录名
                sprintf(&path[i], "/%s", fn);
                //递归遍历
                res = scan_files(path);
                path[i] = 0;
                //打开失败，跳出循环
                if (res != FR_OK)
                    break;
            }
            else
            {
                PRINTF("%s/%s\r\n", path, fn); //输出文件名
                                             /* 可以在这里提取特定格式的文件路径 */
            }                                //else
        }                                    //for
    }
    return res;
}

/**
 * @brief 粗略延时
 * 
 */
void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 1000000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

/**
 * @brief 系统初始化钩子函数
 * 
 */
void SystemInitHook(void)
{
    /* 初始化多核管理器系统，完成后才可调用MCMGR_Init */
    MCMGR_EarlyInit();
}

/**
 * @brief 主函数
 * 
 * @return int 
 */
int main(void)
{
    /* 初始化MCMGR（多核管理系统） */
    MCMGR_Init();

    /* 初始化时钟 */
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM0);

    /* 初始化systick */
    systick_init();

    /* 配置引脚功能*/
    BOARD_InitPins_Core0();
    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);
    
    BOARD_BootClockFROHF48M();
    BOARD_InitDebugConsole();

    PRINTF("Debug Console Init Successful!\r\n");

#ifdef CORE1_IMAGE_COPY_TO_RAM
    /* 拷贝从核数据到从核启动ram,使用MCUXpresso IDE不需要拷贝 */
    copy_core1_image_to_ram();
#endif

#if 0
	/* 启动m0核心 */
	start_core1();
    
    while (1)
    {
    }
#else

    /* 初始化LED */
    LEDInit();
    LED4_ON();
    PRINTF("LED Init Successful!\r\n");


    PRINTF("****** 这是一个基于SD卡的FatFS文件系统功能使用 ******\r\n");
    /* 文件系统初始化 */
    f_res = f_mount(&g_fileSystem, driverNumberBuffer, 1);
    if (f_res != FR_OK)
    {
        PRINTF("！！SD卡挂载文件系统失败。\r\n");
        while (1);
    }
    else
    {
        PRINTF(">SD卡文件系统挂载成功，可以进行测试。\r\n");
    }
    /* FatFs多项功能测试 */
    f_res = miscellaneous();

    PRINTF("*************** 文件信息获取测试 **************\r\n");
    f_res = file_check();

    PRINTF("***************** 文件扫描测试 ****************\r\n");
    strcpy(fpath, driverNumberBuffer);
    scan_files(fpath);

    PRINTF("**************** flash 初始化 ****************\r\n");
    /* flash 初始化 */
    spiflash_init();

    /* dmic初始化 */
    dmic_init();

    /* codec初始化 */
    wm8904_i2s_init();

    
    while (1)
    {
        /* 延时一段时间 */
        delay();
        PRINTF("LED!\r\n");
    }
#endif
}
