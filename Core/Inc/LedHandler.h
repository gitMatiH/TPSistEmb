/*
 * LedHandler.h
 *
 *  Created on: Nov 8, 2023
 *      Author: Matias
 */
#include "main.h"

#ifndef LED_HANDLER_H_
#define LED_HANDLER_H_

#define LED1 0
#define LED2 1
#define LED3 2

typedef struct estructuraLed{
	GPIO_TypeDef *GPIOx;
	uint32_t Pin;
} led_typedef;






extern void LedHandler();

extern void LedHandler_Init(led_typedef * , uint8_t);

extern void LedSequence();

#endif
