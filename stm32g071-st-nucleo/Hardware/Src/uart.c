#include "config.h"
#include "uart.h"

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart1;

rt_sem_t uart1_recv_sem;
rt_mq_t uart1_recv_mq;

uint8 g_USART1_RxBuf[USART1_RX_BUF_SIZE]; // 串口接收缓冲区
uint16 g_USART1_RecPos = 0;               // 存放当前串口接收数据存放的位置
uint8_t recvByte = 0;

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
int MX_USART2_UART_Init(void)
{

    /* USER CODE BEGIN USART2_Init 0 */

    /* USER CODE END USART2_Init 0 */

    /* USER CODE BEGIN USART2_Init 1 */

    /* USER CODE END USART2_Init 1 */
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        while(1);
    }
    if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
    {
        while(1);
    }
    if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
    {
        while(1);
    }
    if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
    {
        while(1);
    }
    /* USER CODE BEGIN USART2_Init 2 */
    return 0;
    /* USER CODE END USART2_Init 2 */
}

INIT_BOARD_EXPORT(MX_USART2_UART_Init);

/**
  * @brief This function handles USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26.
  */
void USART2_IRQHandler(void)
{
    /* USER CODE BEGIN USART2_IRQn 0 */

    /* USER CODE END USART2_IRQn 0 */
    HAL_UART_IRQHandler(&huart2);
    /* USER CODE BEGIN USART2_IRQn 1 */

    /* USER CODE END USART2_IRQn 1 */
}

void rt_hw_console_output(const char *str)
{
    rt_size_t i = 0, size = 0;
    char a = '\r';

    rt_enter_critical();

    __HAL_UNLOCK(&huart2);

    size = rt_strlen(str);
    for (i = 0; i < size; i++)
    {
        if (*(str + i) == '\n')
        {
            HAL_UART_Transmit(&huart2, (uint8_t *)&a, 1, 1);
        }
        HAL_UART_Transmit(&huart2, (uint8_t *)(str + i), 1, 1);
    }

    rt_exit_critical();
}

char rt_hw_console_getchar(void)
{
    int ch = -1;

    if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE) != RESET)
    {
        ch = huart2.Instance->RDR & 0xff;
    }
    else
    {
        if(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_ORE) != RESET)
        {
            __HAL_UART_CLEAR_OREFLAG(&huart2);
        }
        rt_thread_mdelay(10);
    }
    return ch;
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
int MX_USART1_UART_Init(void)
{

    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */
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
    /* USER CODE BEGIN USART1_Init 2 */
    // HAL_UART_Receive_IT(&huart1, (uint8_t *)g_USART1_RxBuf, USART1_RX_BUF_SIZE);
    // HAL_UART_Receive_IT(&huart1, &recvByte, 1);
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);

    return 0;
    /* USER CODE END USART1_Init 2 */
}

INIT_BOARD_EXPORT(MX_USART1_UART_Init);

/**
  * @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
  */
void USART1_IRQHandler(void)
{
    /* USER CODE BEGIN USART1_IRQn 0 */
    // USART1_IRQHandler_Callback(&huart1);

    int8_t ret;

    // if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET)
    if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) && __HAL_UART_GET_IT_SOURCE(&huart1, UART_IT_RXNE))
    {
        if (HAL_UART_Receive(&huart1, &recvByte, 1, 10) == HAL_OK)
        // if (HAL_UART_Receive_IT(&huart1, &recvByte, 1) == HAL_OK)
        {
            g_USART1_RxBuf[g_USART1_RecPos++] = recvByte;
        }
        // HAL_UART_RxCpltCallback(&huart1);
    }
    // if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET)
    if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) && __HAL_UART_GET_IT_SOURCE(&huart1, UART_IT_IDLE))
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart1);
        g_USART1_RxBuf[g_USART1_RecPos] = '\0';
#if 0 // 信号量方式
        ret = rt_sem_release(uart1_recv_sem);
        if (RT_EOK != ret)
        {
            rt_kprintf("semaphore send error: %d\n", ret);
        }
#else // 信息队列方式
        ret = rt_mq_send(uart1_recv_mq, g_USART1_RxBuf, sizeof(g_USART1_RxBuf));
        if (RT_EOK != ret)
        {
            rt_kprintf("message send error: %d\n", ret);
        }
#endif
        g_USART1_RecPos = 0;
    }

    /* USER CODE END USART1_IRQn 0 */
    HAL_UART_IRQHandler(&huart1);
    /* USER CODE BEGIN USART1_IRQn 1 */
    // __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
    /* USER CODE END USART1_IRQn 1 */
}

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}
