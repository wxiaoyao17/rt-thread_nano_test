#ifndef __UART_H__
#define __UART_H__

/* 实现 1：初始化串口 */
int uart_init(void);
/* 实现 2：输出一个字符，系统函数，函数名不可更改 */
void rt_hw_console_output(const char *str);
/* 实现 3：finsh 获取一个字符，系统函数，函数名不可更改 */
char rt_hw_console_getchar(void);

#endif // !__UART_H__
