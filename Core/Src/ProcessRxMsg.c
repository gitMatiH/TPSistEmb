
#include "ProcessRxMsg.h"


typedef enum{
	OCIOSO = 0,
	CARACTER_VALIDO_1 = 1,
	CARACTER_VALIDO_2 = 2,
}enum_proceso;



enum_proceso estadoActual;

uint32_t tiempoRecepcion0;
uint8_t validar_dato;

TColaDato_Typedef buffer_rx[RX_COLA_MAX_BUFFER];
Cola_BaseStructTypedef cola_rx;

void ProcessRxMsg_Init(void){
	estadoActual = OCIOSO;
	Cola_InicializarCola(&cola_rx, buffer_rx, RX_COLA_MAX_BUFFER);

}


void ProcessRxMsg(UART_HandleTypeDef * huart1, uint8_t * rx_data, Cola_BaseStructTypedef * colaTx, uint8_t *instruccion_ok){

	uint8_t dato;
	//uint8_t static validar_dato;
	uint32_t tiempoRecepcionActual;
	//uint32_t static tiempoRecepcion0;

	switch(estadoActual){
	case OCIOSO:

		if (Cola_RetirarDatoCola (&cola_rx,&dato) != COLA_COLA_VACIA){
			//dato esperado
			if (dato == L1 || dato == L2 || dato == L3 || dato == S || dato == O){
				tiempoRecepcion0 = HAL_GetTick();
				validar_dato = dato;
				//*instruccion_ok = dato;
				estadoActual = CARACTER_VALIDO_1;
			//dato inválido
			}else{
				*instruccion_ok = 0;
				enviarACola(MSG_ERROR,colaTx);
			}
		}
		break;

	case CARACTER_VALIDO_1:

		if (Cola_RetirarDatoCola (&cola_rx,&dato) != COLA_COLA_VACIA){

			//dato esperado
			if (dato == CR){
				tiempoRecepcionActual = HAL_GetTick();
				if (dato == COLA_COLA_VACIA) {
					//a tiempo
					if(tiempoRecepcionActual - tiempoRecepcion0 < TMAX){
						estadoActual = CARACTER_VALIDO_2;
					//tarde
					}else{
						enviarACola(MSG_TIMEOUT,colaTx);
						*instruccion_ok = 0;
						estadoActual = OCIOSO;
					}
				}
			//dato no esperado inválido
			}else{
				enviarACola(MSG_ERROR,colaTx);
				*instruccion_ok = 0;
				estadoActual = OCIOSO;
			}

		}
		break;

	case CARACTER_VALIDO_2:

		if (Cola_RetirarDatoCola (&cola_rx, &dato) != COLA_COLA_VACIA){
			tiempoRecepcionActual = HAL_GetTick();
			//dato esperado
			if (dato == LF){
				//a tiempo
				if(tiempoRecepcionActual - tiempoRecepcion0 < TMAX){
					*instruccion_ok = validar_dato;
					enviarACola(MSG_OK,colaTx);
					estadoActual = OCIOSO;
				//tarde
				}else{
					enviarACola(MSG_TIMEOUT,colaTx);
					instruccion_ok = 0;
					estadoActual = OCIOSO;
				}
			//dato no esperado inválido
			}else{
				enviarACola(MSG_ERROR,colaTx);
				instruccion_ok = 0;
				estadoActual = OCIOSO;
			}
		}
	}
}

/*$12340D0A
 * $SizePAyload
 * $GPRMC,12.3,fggggg,,*ODOA
 * $>GPRMC,,,,*/
