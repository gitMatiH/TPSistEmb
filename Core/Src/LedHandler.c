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
	if(GetFlag()==0)
	{
		return;
	}
	switch(*instruccion_ok){

	case cmd_led1:
		//cambiar estado led 1
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
	    *instruccion_ok = 0;
		break;

	case cmd_led2:
		//cambiar estado led 2
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
		*instruccion_ok = 0;
		break;

	case cmd_led3:
		//cambiar estado led 3
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);
		*instruccion_ok = 0;
		break;

	case cmd_Secuencia:
		if (GetFlag()==0){
			//*primeraVez = 1;
			//bool primeraVez;	// capaz nos lo podemos ahorrar... no hace falta por el ledsequence_init
			//tiempo_inicial = HAL_GetTick();	//reemplaza a toda la estructura de tiempo inic asoc a flagprimeravez
			// va en LedSequence_init()
			//puedo usar ese para leer el tiempo inicial "seed
			LedSequence_init();
			//*flagSecuencia = 1;
			SetFlag(1);
			//puedo usar ese para leer el tiempo inicial "seed
		}else{
			//*primeraVez = 0;//ESTE ES IMPORTANTE, PARA CUANDO RETORNE LA SECUENCIA SEGUN FLAG
			//ya no hace falta apagar primera vez pq ya no existe
			//*flagSecuencia = 0;
			SetFlag(0);
		}
		*instruccion_ok = 0;
		break;

	case cmd_Apagado:
		//*primeraVez = 0;
		// ya no hace falta
		//*flagSecuencia = 0;// es reemplazado por setflag
		SetFlag(0);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
		*instruccion_ok = 0;
		break;

	default:
		// apagar todos los leds??? no, es para agarrar una instruccion no indizada
		*instruccion_ok = 0;
		break;

	}

}

void LedSequence_init(void){

	tiempo_inicial = HAL_GetTick();

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

	estadoLeds = PRENDIDO_LED1;

	return;
}

void LedSequence(void){

	uint32_t t_actual;

	t_actual = HAL_GetTick();

	switch (estadoLeds){

	case PRENDIDO_LED1:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);

		if(t_actual - tiempo_inicial > MAX_TIME_MS){
			tiempo_inicial = t_actual;
			estadoLeds = PRENDIDO_LED2;
		}
		break;

	case PRENDIDO_LED2:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

		if(t_actual - tiempo_inicial > MAX_TIME_MS){
			tiempo_inicial = t_actual;
			estadoLeds = PRENDIDO_LED3;
		}
		break;

	case PRENDIDO_LED3:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
		if(t_actual - tiempo_inicial > MAX_TIME_MS){
			tiempo_inicial = t_actual;
			estadoLeds = APAGADO_LEDS;
		}
		break;

	case APAGADO_LEDS:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

		if(t_actual - tiempo_inicial > MAX_TIME_MS){
			tiempo_inicial = t_actual;
			estadoLeds = PRENDIDO_LED1;
		}
		break;
	}
	//no, no hace falta esto
	//primera vez hecha
	//SetFlag(0);
}
