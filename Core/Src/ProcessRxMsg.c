
#include "ProcessRxMsg.h"

typedef enum{
	OCIOSO = 0,
	CARACTER_VALIDO_1 = 1,
	CARACTER_VALIDO_2 = 2,
}enum_proceso;

//alternativa a static
enum_proceso estadoActual;
uint8_t flag;

void SetFlag(uint8_t value)
{
	flag = value;
}

uint8_t GetFlag(void)
{
	return flag;
}

TColaDato_Typedef buffer_rx[RX_COLA_MAX_BUFFER];
Cola_BaseStructTypedef cola_rx;

void ProcessRxMsg_Init(void){
	estadoActual = OCIOSO;
	Cola_InicializarCola(&cola_rx, buffer_rx, RX_COLA_MAX_BUFFER);

}


void ProcessRxMsg(UART_HandleTypeDef * huart1, uint8_t * rx_data, Cola_BaseStructTypedef * colaTx, uint8_t *instruccion_ack){

	uint8_t instruccion;
	uint8_t dato;
	uint32_t tiempoRecepcionActual, tiempoRecepcion0, tiempoRecepcion1, tiempoRecepcion2;



	// recepcionDatosFlag
	// maquina de estado:
	// en realidad desacolar(cola) = caracter
	// estadoActual depende de caracter

	switch(estadoActual){
		case OCIOSO:

				if (Cola_RetirarDatoCola (&cola_rx,&dato) != 0x00){
					//dato esperado
					if (dato == 1 || dato == 2 || dato == 3 || dato == 'S' || dato == 'O'){
						tiempoRecepcion0 = HAL_GetTick();
						instruccion = dato;
						estadoActual = CARACTER_VALIDO_1;
					//dato inválido
					}else{
						instruccion = 0;
						enviarACola(MSG_ERROR,colaTx);
					}
				}
				break;

		case CARACTER_VALIDO_1:

			if (Cola_RetirarDatoCola (&cola_rx,&dato) != 0x00){

				//dato esperado
				tiempoRecepcionActual = HAL_GetTick();
				if (dato == 0x0D) {
					//a tiempo
					if(tiempoRecepcionActual - tiempoRecepcion0 < TMAX){
						estadoActual = CARACTER_VALIDO_2;
					//tarde
					}else{
						enviarACola(MSG_TIMEOUT,colaTx);
						instruccion = 0;
						estadoActual = OCIOSO;
					}
				//dato no esperado pero valido para secuencia
				}else if(dato == 1 || dato == 2 || dato == 3 || dato == 'S' || dato == 'O'){
					enviarACola(MSG_ERROR,colaTx);
					tiempoRecepcion0 = HAL_GetTick();
					instruccion = dato;
					estadoActual = CARACTER_VALIDO_1;
				//dato no esperado inválido
				}else{
					enviarACola(MSG_ERROR,colaTx);
					instruccion = 0;
					estadoActual = OCIOSO;
				}
			}
			break;

		case CARACTER_VALIDO_2:

			if (Cola_RetirarDatoCola (&cola_rx, &dato) != 0x00){
				tiempoRecepcionActual = HAL_GetTick();
				//dato esperado
				if (dato == 0x0A){
					//a tiempo
					if(tiempoRecepcionActual - tiempoRecepcion0 < TMAX){
						enviarACola(MSG_OK,colaTx);
						*instruccion_ack = instruccion;
						estadoActual = OCIOSO;
					//tarde
					}else{
						enviarACola(MSG_TIMEOUT,colaTx);
						instruccion = 0;
						estadoActual = OCIOSO;
					}
				//dato no esperado pero valido para secuencia
				}else if(dato == 1 || dato == 2 || dato == 3 || dato == 'S' || dato == 'O'){
					enviarACola(MSG_ERROR,colaTx);
					tiempoRecepcion1 = HAL_GetTick();
					instruccion = 0;
					estadoActual = CARACTER_VALIDO_1;
				//dato no esperado inválido
				}else{
					enviarACola(MSG_ERROR,colaTx);
					instruccion = 0;
					estadoActual = OCIOSO;
				}
			}

			//devuelve (por referencia) 1, 2, 3 S o O.
	}

}

//pasar esta funcion a send data, poner aca el include senddata.c
//poner en senddata la cola de tx y el buffer (perteneciente a la cola)


void enviarACola(char* cadena, Cola_BaseStructTypedef* colaTx){
//encapsular en enviarACola(MSG_ERROR,cola_tx);
//tal vez que sea bloqueante (que no lo pueda interrumpir otro proceso de llenado de cola)
	int i;
	int longitud = strlen(cadena);
	unsigned char bytes[longitud]; // Arreglo de bytes (8 bits cada uno)
	strncpy((char *)bytes, cadena, longitud);	// la cadena es descompuesta en bytes
												// y metida al array "bytes"
	for (i = 0; i<longitud; i++){
		Cola_AgregarDatoCola (colaTx, bytes[i]);
	}
}
