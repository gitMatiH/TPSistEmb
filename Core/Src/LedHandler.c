/*
 * LedHandler.c
 *
 *  Created on: Nov 8, 2023
 *      Author: Matias
 */



#include "LedHandler.h"

#define MAX_TIME_MS (uint32_t)125

uint32_t tiempo_inicial;

estado_leds estadoLeds;

uint8_t flag;

void SetFlag(uint8_t value)
{
	flag = value;
}

uint8_t GetFlag(void)
{
	return flag;
}


void LedSequence_init(void);


void LedHandler(uint8_t* instruccion_ok){

	switch(*instruccion_ok){

	case idle:

		break;

	case cmd_led1:
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
	    *instruccion_ok = 0;
		break;

	case cmd_led2:
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
		*instruccion_ok = 0;
		break;

	case cmd_led3:
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);
		*instruccion_ok = 0;
		break;

	case cmd_Secuencia:
		if (GetFlag()==0){
			LedSequence_init();
			SetFlag(1);
		}else{
			SetFlag(0);
		}
		*instruccion_ok = 0;
		break;

	case cmd_Apagado:
		SetFlag(0);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, LED_ESTADO_INACTIVO);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, LED_ESTADO_INACTIVO);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, LED_ESTADO_INACTIVO);
		*instruccion_ok = 0;
		break;

	default:
		//es para agarrar una instruccion no indizada
		SetFlag(0);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, LED_ESTADO_INACTIVO);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, LED_ESTADO_INACTIVO);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, LED_ESTADO_INACTIVO);
		*instruccion_ok = 0;
		break;

	}

}

void LedSequence_init(void){

	tiempo_inicial = HAL_GetTick();

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, LED_ESTADO_INACTIVO);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, LED_ESTADO_INACTIVO);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, LED_ESTADO_INACTIVO);

	estadoLeds = PRENDIDO_LED1;

	return;
}

void LedSequence(void){

	uint32_t t_actual;

	t_actual = HAL_GetTick();

	switch (estadoLeds){

	case PRENDIDO_LED1:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, LED_ESTADO_ACTIVO);

		if(t_actual - tiempo_inicial > MAX_TIME_MS){
			tiempo_inicial = t_actual;
			estadoLeds = PRENDIDO_LED2;
		}
		break;

	case PRENDIDO_LED2:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, LED_ESTADO_ACTIVO);

		if(t_actual - tiempo_inicial > MAX_TIME_MS){
			tiempo_inicial = t_actual;
			estadoLeds = PRENDIDO_LED3;
		}
		break;

	case PRENDIDO_LED3:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, LED_ESTADO_ACTIVO);
		if(t_actual - tiempo_inicial > MAX_TIME_MS){
			tiempo_inicial = t_actual;
			estadoLeds = APAGADO_LEDS;
		}
		break;

	case APAGADO_LEDS:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, LED_ESTADO_INACTIVO);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, LED_ESTADO_INACTIVO);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, LED_ESTADO_INACTIVO);

		if(t_actual - tiempo_inicial > MAX_TIME_MS){
			tiempo_inicial = t_actual;
			estadoLeds = PRENDIDO_LED1;
		}
		break;
	}
}
