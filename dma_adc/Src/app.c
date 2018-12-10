/*
 * app.c
 *
 *  Created on: Dec 03, 2018
 *      Author: Gabriel e Tales
 */

#include "app.h"
#include "main.h"
#include "stm32f4xx_hal.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim2;
uint16_t v[3];
float mme[3] = {0};
uint16_t media_inteira[3] = {0};
float ant[3] = {0};


void app_init(void){
	HAL_TIM_Base_Start(&htim2);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)v ,3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_15,GPIO_PIN_RESET);
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	static uint32_t i = 0;
	static uint32_t n = 0;
	i++;
	for(n=0 ; n < 3 ; n++){
		mme[n] = 0.875*ant[n] + 0.125*v[n];
		ant[n] = mme[n];
		media_inteira[n] = (uint16_t) mme[n]/10;
	}
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1, media_inteira[0]);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2, media_inteira[1]);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3, media_inteira[2]);
	if(i >= 10){
		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_15);
		i = 0;
	}


}
