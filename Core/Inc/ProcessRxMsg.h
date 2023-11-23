/*
 * ProcessRxMsg.h
 *
 *  Created on: Nov 7, 2023
 *      Author: Matias
 */


#ifndef PROCESS_RX_MSG_H_
#define PROCESS_RX_MSG_H_

//#include <stdint.h>
#include <cola.h>

typedef enum{
	L1 = '1',
	L2 = '2',
	L3 = '3',
	S = 'S',
	O = 'O',
	CR = 0x0D,
	LF = 0x0A
}comandos;

#define RX_COLA_MAX_BUFFER	6
#define MSG_ERROR "Error\n"
#define MSG_TIMEOUT "Timeout\n"
#define MSG_OK "OK\n"

#define TMAX (uint32_t)1000

extern void ProcessRxMsg_Init(void);

extern void ProcessRxMsg(UART_HandleTypeDef *, uint8_t *, Cola_BaseStructTypedef *, uint8_t *instruccion);

extern void enviarACola(char*, Cola_BaseStructTypedef*);


/*https://www.scaler.com/topics/c-extern/
	It is important to note that the C extern keyword is
	used to only declare a variable and not define a variable.
	The C extern keyword is used to declare global variables
	mostly in the header files that will be used in other
	files of a long program.
*/
extern TColaDato_Typedef buffer_rx[RX_COLA_MAX_BUFFER];
extern Cola_BaseStructTypedef cola_rx;

#endif
