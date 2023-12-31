
#include "main.h"
#include "ProcessRxMsg.h"


void ProcessRxMsg(UART_HandleTypeDef * huart1, uint8_t * rx_data, Cola_BaseStructTypedef * colaRx, Cola_BaseStructTypedef * colaTx, uint8_t *instruccion_ack, int* pEstadoActual){

	int estadoActual = *pEstadoActual;
	uint8_t instruccion;
	uint8_t dato;
	/*static*/ uint32_t tiempoRecepcionActual, tiempoRecepcion0;



	// recepcionDatosFlag
	// maquina de estado:
	// en realidad desacolar(cola) = caracter
	// estadoActual depende de caracter

	switch(estadoActual){
		case OCIOSO:

				if (Cola_RetirarDatoCola (colaRx,&dato) != 0x00){
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

			if (Cola_RetirarDatoCola (colaRx,&dato) != 0x00){

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

			if (Cola_RetirarDatoCola (colaRx, &dato) != 0x00){
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
					tiempoRecepcion0 = HAL_GetTick();
					instruccion = 0;
					estadoActual = CARACTER_VALIDO_1;
				//dato no esperado inválido
				}else{
					enviarACola(MSG_ERROR,colaTx);
					instruccion = 0;
					estadoActual = OCIOSO;
				}
			}

			*pEstadoActual = estadoActual;
			//devuelve (por referencia) 1, 2, 3 S o O.
	}

}

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
