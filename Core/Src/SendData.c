/*
 * SendData.c
 *
 *  Created on: Nov 8, 2023
 *      Author: Matias
 */

#include "main.h"
#include "SendData.h"


void SendData(UART_HandleTypeDef * huart, Cola_BaseStructTypedef * colaTx){

	uint8_t dato;
	HAL_StatusTypeDef estados;

	while ( Cola_RetirarDatoCola(colaTx, &dato) != 0x00){
		// esto es bloqueante usar IT, tamanio cola 10
		estados = HAL_UART_Transmit(huart, &dato, 1, 10);
		//usar este
		estados = HAL_UART_Transmit_IT(huart, &dato, 1, 10);
	}
}

