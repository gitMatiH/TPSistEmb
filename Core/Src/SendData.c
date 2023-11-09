/*
 * SendData.c
 *
 *  Created on: Nov 8, 2023
 *      Author: Matias
 */

#include "main.h"


void SendData(UART_HandleTypeDef * huart, Cola_BaseStructTypedef * colaTx){

	uint8_t dato;

	while ( Cola_RetirarDatoCola(colaTx, &dato) != 0x00){
		HAL_UART_Transmit(huart, &dato, 1, 1000);
	}
}

