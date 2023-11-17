/*
 * SendData.h
 *
 *  Created on: Nov 8, 2023
 *      Author: Matias
 */

#ifndef SEND_DATA_H_
#define SEND_DATA_H_

#include "cola.h"
#include <string.h>

#define TX_COLA_MAX_BUFFER	20

extern TColaDato_Typedef buffer_tx[TX_COLA_MAX_BUFFER];
extern Cola_BaseStructTypedef cola_tx;


extern void SendData(UART_HandleTypeDef * huart, Cola_BaseStructTypedef * colaTx);

extern void enviarACola(char* cadena, Cola_BaseStructTypedef* colaTx);

#endif
