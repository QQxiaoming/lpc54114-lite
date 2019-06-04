/**
 * @file test_fatfs.c
 * @author qiaoqiming
 * @brief 文件系统测试
 * @version 1.0
 * @date 2019-05-22
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <string.h>
#include <stdio.h>
#include "ff.h"
#include "diskio.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"

extern const TCHAR driverNumberBuffer[3U];
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

    printfk("*************** 设备信息获取 ***************\r\n");
    /* 获取设备信息和空簇大小 */
    f_res = f_getfree("4:", &fre_clust, &pfs);

    /* 计算得到总的扇区个数和空扇区个数 */
    tot_sect = (pfs->n_fatent - 2) * pfs->csize;
    fre_sect = fre_clust * pfs->csize;

    /* 打印信息(4096 字节/扇区) */
    printfk(">设备总空间：%d KB。\r\n>可用空间：  %d KB。\r\n", tot_sect * 4, fre_sect * 4);

    printfk("******** 文件定位和格式化写入功能测试 ********\r\n");
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
                printfk(">文件内容：\r\n%s\r\n", readbuffer);
            }
        }
        f_close(&file);

        printfk("\r\n********** 目录创建和重命名功能测试 **********\r\n");
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
        printfk("!! 打开文件失败：%d\r\n", f_res);
        printfk("!! 或许需要再次运行“FatFs移植与读写测试”工程\r\n");
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
        printfk("readme.txt文件信息：\r\n");
        printfk(">文件大小: %d(字节)\r\n", finfo.fsize);
        printfk(">时间戳: %u/%02u/%02u, %02u:%02u\r\n",
               (finfo.fdate >> 9) + 1980, finfo.fdate >> 5 & 15, finfo.fdate & 31, finfo.ftime >> 11, finfo.ftime >> 5 & 63);
        printfk(">属性: %c%c%c%c%c\r\n\r\n",
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
                printfk("%s/%s\r\n", path, fn); //输出文件名
                                             /* 可以在这里提取特定格式的文件路径 */
            }                                //else
        }                                    //for
    }
    return res;
}


void test_fatfs(void)
{
    // TODO: 以下测试函数稳定性存在问题
    printfk("*************** FatFs多项功能测试 **************\r\n");
    miscellaneous();

    printfk("*************** 文件信息获取测试 **************\r\n");
    file_check();

    printfk("***************** 文件扫描测试 ****************\r\n");
    strcpy(fpath, driverNumberBuffer);
    scan_files(fpath);
}
