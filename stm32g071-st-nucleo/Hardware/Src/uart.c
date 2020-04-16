#include "config.h"
#include "uart.h"

static UART_HandleTypeDef hlpuart1;
static UART_HandleTypeDef huart1;

int lpuart1_init(void)
{
    /* 初始化串口参数，如波特率、停止位等等 */
    hlpuart1.Instance = LPUART1;
    hlpuart1.Init.BaudRate = 115200;
    hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
    hlpuart1.Init.StopBits = UART_STOPBITS_1;
    hlpuart1.Init.Parity = UART_PARITY_NONE;
    hlpuart1.Init.Mode = UART_MODE_TX_RX;
    hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    hlpuart1.FifoMode = UART_FIFOMODE_DISABLE;

    /* 初始化串口引脚等 */
    if (HAL_UART_Init(&hlpuart1) != HAL_OK)
    {
        while(1);
    }
    if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
    {
        while(1);
    }
    if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
    {
        while(1);
    }
    if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
    {
        while(1);
    }

    return 0;
}

INIT_BOARD_EXPORT(lpuart1_init);

/**
  * @brief This function handles USART3, USART4 and LPUART1 interrupts / LPUART1 wake-up interrupt through EXTI line 28.
  */
void USART3_4_LPUART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_4_LPUART1_IRQn 0 */

  /* USER CODE END USART3_4_LPUART1_IRQn 0 */
  HAL_UART_IRQHandler(&hlpuart1);
  /* USER CODE BEGIN USART3_4_LPUART1_IRQn 1 */

  /* USER CODE END USART3_4_LPUART1_IRQn 1 */
}

void rt_hw_console_output(const char *str)
{
    rt_size_t i = 0, size = 0;
    char a = '\r';

    rt_enter_critical();

    __HAL_UNLOCK(&hlpuart1);

    size = rt_strlen(str);
    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            HAL_UART_Transmit(&hlpuart1, (uint8_t *)&a, 1, 1);
        }
        HAL_UART_Transmit(&hlpuart1, (uint8_t *)(str + i), 1, 1);
    }

    rt_exit_critical();
}

char rt_hw_console_getchar(void)
{
    int ch = -1;

    if (__HAL_UART_GET_FLAG(&hlpuart1, UART_FLAG_RXNE) != RESET)
    {
        ch = hlpuart1.Instance->RDR & 0xff;
    }
    else
    {
        if(__HAL_UART_GET_FLAG(&hlpuart1, UART_FLAG_ORE) != RESET)
        {
            __HAL_UART_CLEAR_OREFLAG(&hlpuart1);
        }
        rt_thread_mdelay(10);
    }
    return ch;
}

int uart1_init(void)
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        while(1);
    }
    if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
    {
        while(1);
    }
    if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
    {
        while(1);
    }
    if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
    {
        while(1);
    }

    return 0;
}

INIT_BOARD_EXPORT(uart1_init);

/**
  * @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
  */
void USART1_IRQHandler(void)
{
    /* USER CODE BEGIN USART1_IRQn 0 */

    /* USER CODE END USART1_IRQn 0 */
    HAL_UART_IRQHandler(&huart1);
    /* USER CODE BEGIN USART1_IRQn 1 */

    /* USER CODE END USART1_IRQn 1 */
}
