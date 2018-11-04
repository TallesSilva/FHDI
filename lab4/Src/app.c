/*
 * app.c
 *
 *  Created on: 17 de set de 2018
 *      Author: Gabriel F. / Talles
 */


#include "main.h"
#include "stm32f4xx_hal.h"
#include "app.h"


uint32_t led=0,i=0, deb = 0;
uint32_t pin[] = {LED1_Pin, LED2_Pin, LED3_Pin,LED4_Pin};
GPIO_TypeDef *ports[] = {LED1_GPIO_Port , LED2_GPIO_Port , LED3_GPIO_Port , LED4_GPIO_Port};
int bot= 0;

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;

void app_loop(void)
{
	__WFI();

}



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0){
	  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1)
	  {
		  if (__HAL_TIM_GET_COUNTER(&htim7) - deb > 100)
		  {
			  bot = bot == 1 ? 0 : 1;
			  deb = __HAL_TIM_GET_COUNTER(&htim7);
		  }
	  }
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{


	if (bot == 0) {
		if (htim == &htim6){

			i++;


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

			}
			else if(bot == 1){

				if (htim == &htim6){

							i++;



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



}


