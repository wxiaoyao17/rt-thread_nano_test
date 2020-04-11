#include "config.h"
#include "uart.h"

static UART_HandleTypeDef UartHandle;

int uart_init(void)
{
    /* 初始化串口参数，如波特率、停止位等等 */
    // UartHandle.Instance = USART1;
    // UartHandle.Init.BaudRate   = 115200;
    // UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    // UartHandle.Init.Mode       = UART_MODE_TX_RX;
    // UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
    // UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    // UartHandle.Init.StopBits   = UART_STOPBITS_1;
    // UartHandle.Init.Parity     = UART_PARITY_NONE;
    UartHandle.Instance = LPUART1;
    UartHandle.Init.BaudRate = 115200;
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits = UART_STOPBITS_1;
    UartHandle.Init.Parity = UART_PARITY_NONE;
    UartHandle.Init.Mode = UART_MODE_TX_RX;
    UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UartHandle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    UartHandle.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    UartHandle.FifoMode = UART_FIFOMODE_DISABLE;

    /* 初始化串口引脚等 */
    if (HAL_UART_Init(&UartHandle) != HAL_OK)
    {
        while(1);
    }

    return 0;
}
INIT_BOARD_EXPORT(uart_init);

void rt_hw_console_output(const char *str)
{
    rt_size_t i = 0, size = 0;
    char a = '\r';

    rt_enter_critical();

    __HAL_UNLOCK(&UartHandle);

    size = rt_strlen(str);
    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            HAL_UART_Transmit(&UartHandle, (uint8_t *)&a, 1, 1);
        }
        HAL_UART_Transmit(&UartHandle, (uint8_t *)(str + i), 1, 1);
    }

    rt_exit_critical();
}

char rt_hw_console_getchar(void)
{
    int ch = -1;

    if (__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_RXNE) != RESET)
    {
        ch = UartHandle.Instance->RDR & 0xff;
    }
    else
    {
        if(__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_ORE) != RESET)
        {
            __HAL_UART_CLEAR_OREFLAG(&UartHandle);
        }
        rt_thread_mdelay(10);
    }
    return ch;
}