/*
 * LedHandler.h
 *
 *  Created on: Nov 8, 2023
 *      Author: Matias
 */
#include "main.h"

#ifndef LED_HANDLER_H_
#define LED_HANDLER_H_

/*
#define LED1 0
#define LED2 1
#define LED3 2
*/

/* No lo entendi
typedef struct estructuraLed{
	GPIO_TypeDef *GPIOx;
	uint32_t Pin;
} led_typedef;
*/

typedef enum{
	cmd_led1='1',
	cmd_led2='2',
	cmd_led3='3',
	cmd_Secuencia='S',
	cmd_Apagado='O'
}cmd_typedef;

typedef enum{
	PRENDIDO_LED1 = 0,
	PRENDIDO_LED2 = 1,
	PRENDIDO_LED3 = 2,
	APAGADO_LEDS = 3
}estado_leds;



extern void LedHandler(uint8_t* instruccion_ack, bool* flagSecuencia, bool* primeraVez);

//extern void LedHandler_Init(led_typedef * , uint8_t);

extern void LedSequence(int * pestado_leds,  bool* primeraVez);

#endif
