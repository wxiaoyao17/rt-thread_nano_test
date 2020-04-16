#include "config.h"
#include "gpio.h"

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
int MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

    /*Configure GPIO pin : PA5 */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    return 0;
}

INIT_BOARD_EXPORT(MX_GPIO_Init);

void LED_Blink(void)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    rt_thread_mdelay(200);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    rt_thread_mdelay(200);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    rt_thread_mdelay(200);
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    rt_thread_mdelay(200);
}
