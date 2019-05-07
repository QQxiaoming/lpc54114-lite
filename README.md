# 玩转LPC54114



### 0.开发环境说明

LPC54114系列是NXP推出的双核MCU，包括一个M4主核和一个M0+从核。lpc54114-lite是其推出的一款开发板，本人作为学习打算研究这块板子的相关资源和官方SDK包。

目前MCU开发一般使用MDK或者IAR，但其为收费软件这里不做考虑，NXP官方推出免费的IDE——MCUXpresso很优秀，但为了熟悉更多底层内容，这里就不使用任何IDE，直接在linux平台使用gcc开发。好在[NXP官网](https://mcuxpresso.nxp.com/zh/dashboard#)开发包下载提供了GCC ARM Embedded的SDK包，这里使用了2.5.0这个版本的SDK。我们可以较为简单的构建编译环境，可以看到SDK内存在大量示例工程，使用CMAKE构建工程，但其不能直接匹配lpc54114-lite开发版，由此我在SDK的基础上删去了board相关内容，添加自己的app、bsp、project来开发，同样使用CMAKE作为构建器，为了方便调试，这里添加了GDB调试脚步，同时为了方便起见，使用insight做为GDB前端，insight需要自行编译使用，具体可参考我的博客。

### 1.BSP开发

