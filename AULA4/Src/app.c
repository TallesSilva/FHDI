/*
 * app.c
 *
 *  Created on: 17 de set de 2018
 *      Author: Gabriel F. /Tales
 */


#include "main.h"
#include "stm32f4xx_hal.h"
#include "app.h"

uint32_t led=0,i=0;
uint32_t pin[] = {LED1_Pin, LED2_Pin, LED3_Pin,LED4_Pin};
GPIO_TypeDef *ports[] = {LED1_GPIO_Port , LED2_GPIO_Port , LED3_GPIO_Port , LED4_GPIO_Port};
int bot= 0;

void app_loop(void)
{
	__WFI();

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /*codigo;*/

	static int t =0;

			if (HAL_GetTick() - t > 50) {

				bot = bot == 1 ? 0 : 1;
			}
}

void HAL_SYSTICK_Callback(void)
{


	i++;
	if (bot == 0) {
				if(i == 50){

					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_SET);

				}

				if(i == 100){

					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);

				}

				if(i == 150){

					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);

				}

				if(i == 200){

					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
					i = 0;

				}

			}
			else if(bot == 1){

				if(i == 50){

					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15,GPIO_PIN_SET);

				}

				if(i == 100){

					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);

				}

				if(i == 150){

					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);

				}

				if(i == 200){

					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
					i = 0;

				}
			}



}


