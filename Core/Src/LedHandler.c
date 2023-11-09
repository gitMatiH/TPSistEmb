/*
 * LedHandler.c
 *
 *  Created on: Nov 8, 2023
 *      Author: Matias
 */

#include "main.h"
#define MAX_TIME_MS 125
/* no lo entendí
void LedHandler_Init(led_typedef * ledx, uint8_t num_led)
{
	//led_typedef led[3];
 	//led[num_led].GPIOx = ledx->GPIOx;
 	//led[num_led].Pin = ledx->Pin;
}
*/

void LedHandler(uint8_t* instruccion_ack, bool* flagSecuencia, bool* primeraVez){

	switch(*instruccion_ack){

	case (cmd_led1):
		//prender led 1
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
		break;

	case (cmd_led2):
		//prender led 2
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
		break;

	case (cmd_led3):
		//prender led 3
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);
		break;

	case (cmd_Secuencia):
		if (*flagSecuencia == 0){
			*primeraVez = 1;
			*flagSecuencia = 1;
		}else{
			*primeraVez = 0;
			*flagSecuencia = 0;
		}
		break;

	case (cmd_Apagado):
		*primeraVez = 0;
		*flagSecuencia = 0;//??
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
		break;


	}

}


void LedSequence(int * pEstadoLeds, bool* primeraVez){

	estado_leds estadoLeds = *pEstadoLeds;
	uint32_t t_actual;
	static uint32_t t_evento;

	if (*primeraVez == 1){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
		estadoLeds = PRENDIDO_LED1;
		t_evento = HAL_GetTick();
		t_actual = t_evento;
	}else{t_actual = HAL_GetTick();}

	switch (estadoLeds){

	case PRENDIDO_LED1:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);

		if(t_actual - t_evento > MAX_TIME_MS){
			t_evento = t_actual;
			estadoLeds = PRENDIDO_LED2;
		}
		break;

	case PRENDIDO_LED2:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

		if(t_actual - t_evento > MAX_TIME_MS){
			t_evento = t_actual;
			estadoLeds = PRENDIDO_LED3;
		}
		break;

	case PRENDIDO_LED3:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
		if(t_actual - t_evento > MAX_TIME_MS){
			t_evento = t_actual;
			estadoLeds = APAGADO_LEDS;
		}
		break;

	case APAGADO_LEDS:

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

		if(t_actual - t_evento > MAX_TIME_MS){
			t_evento = t_actual;
			estadoLeds = PRENDIDO_LED1;
		}
		break;
	}

	primeraVez = 0;

}
