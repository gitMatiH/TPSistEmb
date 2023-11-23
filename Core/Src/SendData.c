/*
 * SendData.c
 *
 *  Created on: Nov 8, 2023
 *      Author: Matias
 */

#include "SendData.h"

TColaDato_Typedef buffer_tx[TX_COLA_MAX_BUFFER];
Cola_BaseStructTypedef cola_tx;

TColaDato_Typedef bufferOut[TX_COLA_MAX_BUFFER];

void SendData(UART_HandleTypeDef * huart, Cola_BaseStructTypedef * colaTx){

	uint8_t dato;
	uint8_t i;
	uint8_t cantidad = Cola_CantidadEnCola(colaTx);
	if (cantidad>0){
		for(i=0;i<cantidad;i++){
				Cola_RetirarDatoCola(colaTx, &dato);
				bufferOut[i] = dato;

			}
		HAL_UART_Transmit_IT(huart, &(bufferOut[0]), cantidad);
	}
}


void enviarACola(char* cadena, Cola_BaseStructTypedef* colaTx){
	uint8_t i;
	uint8_t longitud = strlen(cadena);
	if (longitud > 0){
		for (i = 0; i<longitud; i++){
			Cola_AgregarDatoCola (colaTx, cadena[i]);
		}
	}
}
