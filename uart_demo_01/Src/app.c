/*
 * app.c
 *
 *  Created on: 15 de out de 2018
 *      Author: Gabriel e Talles
 */
#include <stdint.h>
#include "main.h"
#include "stm32f4xx_hal.h"
#include "app.h"
#include "util_cbuf.h"
#include <string.h>
#include <stdio.h>

#define CB_MAX_SIZE 100

extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim7;

util_cbuf_data_t area[CB_MAX_SIZE];
util_cbuf_t cb;
uint8_t cmd[CB_MAX_SIZE];
uint32_t pos = 0;


void retrieve_command(char *command)
{
	int i = 0;
	while(util_cbuf_get(&cb, &cmd[i++]) != UTIL_CBUF_EMPTY)
		{

		}

}


void mon_rx_interrupt(uint8_t c)
{
	//RECEBER A FRASE INTEIRA, PARA TRATAR
	// este if tira o spaço do meu buffer circular
	if (c == 32)
	{
		 HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,1);
	}

	else if (c =='\n') // antes era else if
	{

		//montar aqui a string recuperando cada caractere
		//caracter armazenado no buffer circular
		//retrieve_command(cmd);
		//chamar a função de tratamento aqui mandando a string

		tratar_comando();
	}
	else if(util_cbuf_put(&cb,c) == UTIL_CBUF_FULL)
	{
		// buffer cheio
	}
}

void custom_uart3_irq(UART_HandleTypeDef *huart)
{
    uint8_t c;
    uint32_t sr;
    USART_TypeDef *h = huart->Instance;

    // lÃª o status register e trata erros atÃ© que desapareÃ§am
    // (o manual manda ler o SR e em seguida DR)
    sr = h->SR;
    while(sr & (UART_FLAG_ORE | UART_FLAG_PE | UART_FLAG_FE | UART_FLAG_NE))
    {
        sr = h->SR;
        c = h->DR;
    }

    if(sr & UART_FLAG_RXNE)
    {
        c = h->DR;
        mon_rx_interrupt(c); // rotina que irÃ¡ receber o byte lido
    }
}
void uart_int_init(void)
{
    // enabling interrupts for errors
    //   (Frame error, noise error, overrun error)
	huart3.Instance->CR3 |= USART_CR3_EIE;
    // enabling interrupt for parity errors and rx
	huart3.Instance->CR1 |= USART_CR1_PEIE | USART_CR1_RXNEIE;

    HAL_NVIC_SetPriority(USART3_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
    HAL_NVIC_ClearPendingIRQ(USART3_IRQn);
}

void app_init(void)
{
	util_cbuf_init(&cb,area,CB_MAX_SIZE);
	uart_int_init();
}

uint8_t bot = 0;
uint32_t deb;

void tratar_comando(void)
{
	uint8_t teste[12]=   {'C','o','d','i','g','o',' ','t','e','s','t','e'};
	uint8_t help[11]=    {'C','o','d','i','g','o',' ','h','e','l','p'};
	uint8_t buton[10] =  {'b','o','t','a','o',' ','h','i','g','h'};
	uint8_t butoff[10] = {'b','o','t','a','o',' ','l','o','w'};
	uint8_t c;
	int i = 0;
	uint8_t vet[10];

	while(util_cbuf_get(&cb,&c) == UTIL_CBUF_OK)
	{
		vet[i]= c;
		i++;
	}

	//RECONHECENDO OS LEDS 1,2,3 E 4
	if ((vet[0] == 'l') & (vet[1]== 'e') & (vet[2] == 'd') & (vet[3]=='1'))
		{
			if((vet[4]=='o') & (vet[5]=='n'))
			{
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,1);
			}
			else if((vet[4]=='o') & (vet[5]=='f') & (vet[6]=='f'))
			{
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,0);
			}
			else
			{	}
		}
		else if ((vet[0] == 'l') & (vet[1]== 'e') & (vet[2] == 'd') & (vet[3]=='2'))
		{
			if((vet[4]=='o') & (vet[5]=='n'))
			{
				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin,1);
			}
			else if((vet[4]=='o') & (vet[5]=='f') & (vet[6]=='f'))
			{
				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin,0);
			}
			else
			{	}
		}
		else if ((vet[0] == 'l') & (vet[1]== 'e') & (vet[2] == 'd') & (vet[3]=='3'))
		{
			if((vet[4]=='o') & (vet[5]=='n'))
			{
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,1);
			}
			else if((vet[4]=='o') & (vet[5]=='f') & (vet[6]=='f'))
			{
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,0);
			}
			else
			{	}
		}
		else if((vet[0] == 'l') & (vet[1]== 'e') & (vet[2] == 'd') & (vet[3]=='4'))
		{
			if((vet[4]=='o') & (vet[5]=='n'))
			{
				HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin,1);
			}
			else if((vet[4]=='o') & (vet[5]=='f') & (vet[6]=='f'))
			{
				HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin,0);
			}
			else
			{	}
		}
		else
		{
			if ((vet[0] == 'h') & (vet[1]== 'e') & (vet[2] == 'l') & (vet[3]=='p'))
			{
				HAL_UART_Transmit(&huart3, help, 11, 200);
			}
			else if((vet[0] == 'b') & (vet[1]== 'u') & (vet[2] == 't'))
			{
				if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1)
				{
					HAL_UART_Transmit(&huart3, buton, 9, 200);
				}
				else
				{
					HAL_UART_Transmit(&huart3, butoff, 9, 200);
				}
			 }
			 else
			 {
				HAL_UART_Transmit(&huart3, teste, 12, 200); // para mandar o help

			 }
		}





}

void app_loop(void)
{
	__WFI();
}


