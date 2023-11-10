/*
 * ProcessRxMsg.h
 *
 *  Created on: Nov 7, 2023
 *      Author: Matias
 */
#include "main.h"


#ifndef PROCESS_RX_MSG_H_
#define PROCESS_RX_MSG_H_

#define RX_COLA_MAX_BUFFER	6
#define MSG_ERROR "Error\n"
#define MSG_TIMEOUT "Timeout\n"
#define MSG_OK "OK\n"

#define TMAX (uint32_t)1000

extern void ProcessRxMsg_Init(void);

extern void ProcessRxMsg(UART_HandleTypeDef *, uint8_t *, Cola_BaseStructTypedef *, uint8_t *instruccion);

extern void enviarACola(char*, Cola_BaseStructTypedef*);
extern void SetFlag(uint8_t value);
extern uint8_t GetFlag(void);

extern TColaDato_Typedef buffer_rx[RX_COLA_MAX_BUFFER];
extern Cola_BaseStructTypedef cola_rx;

#endif
