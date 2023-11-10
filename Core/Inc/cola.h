/**
 * \file cola.h
 *
 * \brief Archivo de cabecera de @ref cola.c
 *
 * \details Para implementar una
 *
 * \author Ariel Dalmas Di Giovanni.
 *
 * \details Ver comentarios de @ref cola.c
 *
 * \version 01.
 * <br> *Modificaciones:*
 * \date 09/05/2018
 *
*/

#ifndef COLA_CIRCULAR_H_
#define COLA_CIRCULAR_H_
/*== Include ===========================================================================*/

#define CORTEX_M3
#ifdef CORTEX_M3
	#include "stm32f1xx_hal.h"
#endif



/**	\addtogroup Cola
  * @{
  */

/*== Constantes ========================================================================*/

/*== Tipos de datos ====================================================================*/
/**
  * \brief Tipo de dato del dato a almacenar en memoria (char, uint8_t , uint16_t, etc)
  */
/*
typedef uint16_t TColaDato_Typedef;
*/
typedef uint8_t TColaDato_Typedef;

/**
  * \brief Estructura b�sica para generar una cola.
  */
typedef struct					
{
	TColaDato_Typedef *InicioCola;		/*!< Puntero al inicio de la cola.*/
	TColaDato_Typedef *EntradaCola;		/*!< Puntero a la posici�n de escritura de la cola.*/
	TColaDato_Typedef *SalidaCola;	  	/*!< Puntero a la posici�n de lectura de la cola.*/
	uint16_t CantidadCola;	  	/*!< Cantidad de datos cargados en la cola sin ser leidos.*/
	uint16_t LongitudCola;	  	/*!< Cantidad m�xima de datos posibles de alojar en la cola.*/
}Cola_BaseStructTypedef;

/**
  * \brief Valores de devoluci�n de las funciones.
  */
typedef enum
{
  COLA_COLA_VACIA  = 0x00,	/*!< La cola est� vac�a.*/
  COLA_COLA_LLENA,        	/*!< La cola est� llena.*/
  COLA_OK,					/*!< La operaci�n fue satisfactoria.*/
  COLA_ERROR				/*!< La operaci�n fue err�nea.*/
  
}TColaStatus_Typedef;

/*== Prototipos de funciones publicas ==================================================*/
void Cola_InicializarCola (Cola_BaseStructTypedef *s,TColaDato_Typedef *buf ,uint16_t Long);
void Cola_LimpiarCola (Cola_BaseStructTypedef *s);
TColaDato_Typedef	Cola_CantidadEnCola(Cola_BaseStructTypedef *s);
TColaStatus_Typedef	Cola_AgregarDatoCola (Cola_BaseStructTypedef *s,TColaDato_Typedef dato);
TColaStatus_Typedef	Cola_RetirarDatoCola (Cola_BaseStructTypedef *s,TColaDato_Typedef *dato);
TColaStatus_Typedef Cola_AgregarDatoCola_Multi (Cola_BaseStructTypedef *s, TColaDato_Typedef *dato, uint16_t longitud);
TColaStatus_Typedef	Cola_RetirarDatoCola_Multi (Cola_BaseStructTypedef *s,TColaDato_Typedef *dato,uint16_t cantidad);
/**
  * @}
  */
#endif


