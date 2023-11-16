/*
 * SendData.c
 *
 *  Created on: Nov 8, 2023
 *      Author: Matias
 */

#include "SendData.h"

TColaDato_Typedef buffer_tx[TX_COLA_MAX_BUFFER];
Cola_BaseStructTypedef cola_tx;


void SendData(UART_HandleTypeDef * huart, Cola_BaseStructTypedef * colaTx){

	uint8_t dato;
	HAL_StatusTypeDef estados;

	while ( Cola_RetirarDatoCola(colaTx, &dato) != 0x00){
		estados = HAL_UART_Transmit_IT(huart, &dato, 1);
	}
}

//pasar esta funcion a send data, poner aca el include senddata.c (.h)
//poner en senddata la cola de tx y el buffer (perteneciente a la cola)


void enviarACola(char* cadena, Cola_BaseStructTypedef* colaTx){
//encapsular en enviarACola(MSG_ERROR,cola_tx);
//tal vez que sea bloqueante (que no lo pueda interrumpir otro proceso de llenado de cola)
	int i;
	int longitud = strlen(cadena);
	unsigned char bytes[longitud]; // Arreglo de bytes (8 bits cada uno)
	strncpy(bytes,cadena, longitud);	// la cadena es descompuesta en bytes
												// y metida al array "bytes"
	for (i = 0; i<longitud; i++){
		Cola_AgregarDatoCola (colaTx, bytes[i]);
	}
}
