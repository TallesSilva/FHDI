/*
 * app.c
 *
 *  Created on: 17 de set de 2018
 *      Author: Gabriel F. / Talles
 */


#include "main.h"
#include "stm32f4xx_hal.h"
#include "app.h"


extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim7;
extern uint32_t bot, deb;
void app_loop(void)
{
	__WFI();
}



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0){
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1)
		{
			if ( __HAL_TIM_GET_COUNTER(&htim7) - deb < 200)
			{
				deb = __HAL_TIM_GET_COUNTER(&htim7);
				if(bot == 0){
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0);
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 0);
					bot++;
				}
				else if(bot == 1){
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 1249);
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 1249);
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 1249);
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 1249);
					bot++;
				}
				else if(bot == 2){
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 2499);
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 2499);
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 2499);
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 2499);
					bot++;
				}
				else if(bot == 3){
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 3750);
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 3750);
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 3750);
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 3750);
					bot++;
				}
				else if(bot == 4){
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 4999);
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 4999);
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 4999);
					__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 4999);
					bot=0;
				}
			}
			else if(( __HAL_TIM_GET_COUNTER(&htim7) - deb > 1000) & ( __HAL_TIM_GET_COUNTER(&htim7) - deb <= 2000)){
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 0);
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0);
				__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 0);
			}
		}
	}
}

