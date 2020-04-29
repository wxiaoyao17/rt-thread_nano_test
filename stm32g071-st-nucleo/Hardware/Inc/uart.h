#ifndef __UART_H__
#define __UART_H__

#define USART1_RX_BUF_SIZE 64

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart1;

extern rt_sem_t uart1_recv_sem;
extern rt_mq_t uart1_recv_mq;

extern uint8_t g_USART1_RxBuf[USART1_RX_BUF_SIZE]; // 串口接收缓冲区
extern uint16_t g_USART1_RecPos;                   // 存放当前串口接收数据存放的位置

/* 实现 1：初始化串口 */
int MX_USART2_UART_Init(void);
void USART2_IRQHandler(void);
/* 实现 2：输出一个字符，系统函数，函数名不可更改 */
void rt_hw_console_output(const char *str);
/* 实现 3：finsh 获取一个字符，系统函数，函数名不可更改 */
char rt_hw_console_getchar(void);

int MX_USART1_UART_Init(void);
void USART1_IRQHandler(void);

#endif // !__UART_H__
