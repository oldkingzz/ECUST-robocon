/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
void led_ini(void)
{
		__HAL_RCC_GPIOF_CLK_ENABLE(); //hand here!
		GPIO_InitTypeDef GPIO_InitStruct;
	  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;//led0 led1
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	  
}
