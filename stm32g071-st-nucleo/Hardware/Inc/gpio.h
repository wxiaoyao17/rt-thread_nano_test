#ifndef __GPIO_H__
#define __GPIO_H__

#define USER_BUTTON_Pin GPIO_PIN_13
#define USER_BUTTON_GPIO_Port GPIOC
#define USER_BUTTON_EXTI_IRQn EXTI4_15_IRQn
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOA

int MX_GPIO_Init(void);
void LED_Blink(void);

#endif // !__GPIO_H__
