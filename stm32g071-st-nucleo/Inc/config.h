#ifndef __CONFIG_H__
#define __CONFIG_H__

//无符号类型的定义
#define uchar unsigned char
#define uint unsigned int

#define uint8 unsigned char
#define uint16 unsigned short int
#define uint32 unsigned int

//全局宏定义
#define CPU_INT_DISABLE()  {__set_PRIMASK(1);} //关闭中断
#define CPU_INT_ENABLE()   {__set_PRIMASK(0);}  //打开中断

//全局类型定义
typedef enum{FALSE = 0, TRUE = !FALSE}BOOL;

//-------------------------------------
#ifdef MAIN_CONFIG  //头文件被多个C调用时，避免变量冲突问题
    #define EXT
#else
    #define EXT extern
#endif

//RTOS相关头文件包含
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <rthw.h>
#include <rtthread.h>
#include "stm32g0xx_hal.h"

#include "gpio.h"
#include "uart.h"
#include "task.h"

#endif // !__CONFIG_H__
