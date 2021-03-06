/*
 * app.c
 *
 *  Created on: 2 de set de 2018
 *      Author: talle
 */
#include "main.h"
#include "stm32f4xx_hal.h"
#include "app.h"

void app_loop(void)
{	uint8_t led = 0 ,i = 0, estado = 0, aux_estado = 0;
	uint32_t pin[] = {LED1_Pin, LED2_Pin, LED3_Pin, LED4_Pin};
	GPIO_TypeDef *ports[] = { LED1_GPIO_Port, LED2_GPIO_Port, LED3_GPIO_Port, LED4_GPIO_Port};
	while(1)
		{
		// Leitura Pino
		estado = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
		// Debouncing
		if(estado == 0)
		{
		aux_estado = 0;
		i = 1;
		}
		if(estado == 1)
		{
		  if(aux_estado == 0)
		   {
			aux_estado++ ;
			i = 0;
		   }
		}
		// Avalia estado horario ou anti-horario
		if(i == 0)
			{
			HAL_GPIO_WritePin(ports[led], pin[led], GPIO_PIN_SET);
			HAL_Delay(200);
			HAL_GPIO_WritePin(ports[led], pin[led], GPIO_PIN_RESET);
			HAL_Delay(200);
			if(led == 0)
				{
				led = 4;
				}
			led--;
			}
		else
			{
			HAL_GPIO_WritePin(ports[led], pin[led], GPIO_PIN_SET);
			HAL_Delay(200);
			HAL_GPIO_WritePin(ports[led], pin[led], GPIO_PIN_RESET);
			HAL_Delay(200);
			led++;
			if(led == 4)
				{
				led = 0;
				}
			}
		}
}
