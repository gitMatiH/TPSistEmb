/*
 * LedHandler.h
 *
 *  Created on: Nov 8, 2023
 *      Author: Matias
 */
//#include "main.h"

#ifndef LED_HANDLER_H_
#define LED_HANDLER_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f1xx_hal.h"
#include <ProcessRxMsg.h>

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



extern void LedHandler(uint8_t* instruccion_ok);

//extern void LedHandler_Init(led_typedef * , uint8_t);

extern void LedSequence(void);

extern void SetFlag(uint8_t value);
extern uint8_t GetFlag(void);

#endif
