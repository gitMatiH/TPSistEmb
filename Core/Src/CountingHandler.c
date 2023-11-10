/*
 * CountingHandler.c
 *
 *  Created on: Nov 8, 2023
 *      Author: Matias
 */

#include "CountingHandler.h"
#include "SendData.h"

void CountingHandler(uint16_t* pulseCount, uint16_t* contador, UART_HandleTypeDef * huart, Cola_BaseStructTypedef * colaTx){

	int i, pc;
	pc = *pulseCount;
	*pulseCount = 0;	// asi si lo interrumpe la callback puede seguir contando y no se crea condicion de carrera en el for

	for(i=0; i<pc; i++){
		*contador = *contador +1;
		//¿Como le agregamos un uint16??
		//Cola_AgregarDatoCola(huart, dato)
		byte = (uint8_t) dato;
		tx
		byte = (uint8_t)((uint16_t)dato>>8)
	}

}
