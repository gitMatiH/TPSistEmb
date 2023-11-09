/*
 * ProcessRxMsg.h
 *
 *  Created on: Nov 7, 2023
 *      Author: Matias
 */
#include "main.h"


#ifndef PROCESS_RX_MSG_H_
#define PROCESS_RX_MSG_H_


#define MSG_ERROR "Error\n"
#define MSG_TIMEOUT "Timeout\n"
#define MSG_OK "OK\n"

#define TMAX (uint32_t)1000

extern enum{
	OCIOSO = 0,
	CARACTER_VALIDO_1 = 1,
	CARACTER_VALIDO_2 = 2,
}enum_proceso;

extern void ProcessRxMsg(UART_HandleTypeDef *, uint8_t *, Cola_BaseStructTypedef *, Cola_BaseStructTypedef *, uint8_t *instruccion, int * estadoActual);

extern void enviarACola(char*, Cola_BaseStructTypedef*);

#endif
