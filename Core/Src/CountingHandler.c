/*
 * CountingHandler.c
 *
 *  Created on: Nov 8, 2023
 *      Author: Matias
 */

#include "CountingHandler.h"
#include "cola.h"
#include "SendData.h"

void CountingHandler_init(uint16_t *pulseCount, bool *flagPulso){
	*pulseCount = 0;
	*flagPulso = 0;
}

void CountingHandler(uint16_t *pulseCount){

	unsigned char byte;

	/*
	pulsecount = 0;	// aunque esto hace una condicion de carrera (podria perderse un pulsecount si justo entre 13 y 14 tieene estimulo)
					// tambien, si lo saco, podría quedar "enganchado", por la condicion de que es global y se podría justo
					// "enganchar" a agregar un pulso por ciclo. entonces no saldría de la condicion
	*
	*/ // Interprete mal!!!!

	byte = (uint8_t)*pulseCount;
	enviarACola(&byte,&cola_tx);
	byte = (uint8_t)((uint16_t)*pulseCount>>8);
	enviarACola(&byte,&cola_tx);

	flagPulso = 0;

}

