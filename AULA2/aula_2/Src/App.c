/*
 * App.c
 *
 *  Created on: 10 de set de 2018
 *      Author: talle
 */
#include "main.h"
#include "stm32f4xx_hal.h"
#include "app.h"

void HAL_SYSTICK_Callback(void)
{
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_SYSTICK_Callback could be implemented in the user file
   */
}

void app_loop(void)
{
uint32_t pin[] = {LED1_Pin, LED2_Pin, LED3_Pin, LED4_Pin};
GPIO_TypeDef *ports[] = { LED1_GPIO_Port, LED2_GPIO_Port, LED3_GPIO_Port, LED4_GPIO_Port};

while(1)
	{

	}
}
