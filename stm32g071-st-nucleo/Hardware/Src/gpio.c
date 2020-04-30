#include "config.h"
#include "gpio.h"

uint8_t PC13_flag = 0;

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
int MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : USER_BUTTON_Pin */
    GPIO_InitStruct.Pin = USER_BUTTON_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(USER_BUTTON_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : LED_Pin */
    GPIO_InitStruct.Pin = LED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

    return 0;
}

INIT_BOARD_EXPORT(MX_GPIO_Init);

/**
  * @brief This function handles EXTI line 4 to 15 interrupts.
  */
void EXTI4_15_IRQHandler(void)
{
    /* USER CODE BEGIN EXTI4_15_IRQn 0 */

    /* USER CODE END EXTI4_15_IRQn 0 */
    HAL_GPIO_EXTI_IRQHandler(USER_BUTTON_Pin);
    /* USER CODE BEGIN EXTI4_15_IRQn 1 */

    /* USER CODE END EXTI4_15_IRQn 1 */
}

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
    PC13_flag++;
    if ((PC13_flag & 0x01) == 0x01)
    {
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
    }
}

void LED_Blink(void)
{
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    rt_thread_mdelay(200);
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    rt_thread_mdelay(200);
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    rt_thread_mdelay(200);
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    rt_thread_mdelay(200);
}
