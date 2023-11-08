/**
 * \file cola.c
 *
 * \brief M�dulo que permite manejar Colas circulares de hasta 65536 bytes de longitud, con
 * con control de cola llena y cola vac�a, (no sobreescribe la cola.)
 *
 * \author Ariel Dalmas Di Giovanni.
 *
 * \date 09/03/2020
 *
 * \details
 * <b> Para definir una cola </b>:
 * 	1. Definir una variable con del tipo @ref Cola_BaseStructTypedef.
 * 	2. Definir un array est�tico de tipo TColaDato_Typedef, de longitud coincidente con la deseada para la cola.
 * 	3. Invocar a "Cola_InicializarCola()" para asignar la variable definida en (1), con el array y la longitud de la cola.
 * 	4. Utilice las funciones Cola_CantidadEnCola(), Cola_AgregarDatoCola() , Cola_RetirarDatoCola(),Cola_RetirarDatoCola_Multi y Cola_AgregarDatoCola_Multi() para operar con la cola.
 *
 * \version 1
 * <br> Modificaciones:
 * -# Se basa en Colas.c, basada en TDAs.
 *
 * \warning Los miembros de la variable de cola del tipo @ref Cola_BaseStructTypedef, no deben
 * accederse de forma directa, deben accederse siempre a trav�s de las funciones del m�dulo.
 *
 */

/*== Librerias==========================================================================*/

/*== Include ===========================================================================*/
#include "cola.h"

/** @addtogroup Drivers
  * @{
  */

/**	@defgroup Cola Cola
  * @brief	Funciones para el manejo de cola de datos. Ver @ref Cola.c.
  * @{
  */

/*== Prototipos de funciones============================================================*/
void Cola_InicializarCola (Cola_BaseStructTypedef *s,TColaDato_Typedef *buf ,uint16_t Long);
void Cola_LimpiarCola	(Cola_BaseStructTypedef *s);
TColaDato_Typedef	Cola_CantidadEnCola(Cola_BaseStructTypedef *s);
TColaStatus_Typedef	Cola_AgregarDatoCola (Cola_BaseStructTypedef *s,TColaDato_Typedef dato);
TColaStatus_Typedef	Cola_RetirarDatoCola (Cola_BaseStructTypedef *s,TColaDato_Typedef *dato);
TColaStatus_Typedef Cola_AgregarDatoCola_Multi (Cola_BaseStructTypedef *s, TColaDato_Typedef *dato, uint16_t longitud);
TColaStatus_Typedef	Cola_RetirarDatoCola_Multi (Cola_BaseStructTypedef *s,TColaDato_Typedef *dato,uint16_t cantidad);

/*== Funciones =========================================================================*/
/**
 * \brief Inicializa la estructura apuntada por s.
 *
 * \param s Puntero a estructura del tipo @ref Cola_BaseStructTypedef
 * \param buf Puntero al buffer de datos.
 * \param Long Longitud m�xima del buffer apuntado por *buf, en bytes.
 *
 * \details Se inicializa la estructura apuntada por s del tipo @ref Cola_BaseStructTypedef,
 * en particular se carga el puntero al buffer y la longitud de la cola.
 *
 */
void Cola_InicializarCola (Cola_BaseStructTypedef *s,TColaDato_Typedef *buf ,uint16_t Long)
{
	s -> LongitudCola 	= Long;
	s->CantidadCola 	= 0;
	s->InicioCola		= buf;
	s->EntradaCola 		= s->InicioCola;
	s->SalidaCola 		= s->InicioCola;
	return;
}

/**
 * \brief Se inicializa la cola apuntada por s, los datos son eliminados.
 * \param s Puntero a estructura del tipo @ref Cola_BaseStructTypedef.
 *
 */
void Cola_LimpiarCola	(Cola_BaseStructTypedef *s)
{
	s->CantidadCola = 0;
	s->EntradaCola	= s->InicioCola;
	s->SalidaCola	= s->InicioCola;
}

/**
 * \brief Retorna la cantidad de datos en la cola que aun no fueron leidos.
 * \param s Puntero a estructura del tipo @ref Cola_BaseStructTypedef.
 * \retval Devuelve la cantidad de datos en la cola.
 */

TColaDato_Typedef	Cola_CantidadEnCola(Cola_BaseStructTypedef *s)
{
    return (s->CantidadCola);
}


/**
  * \brief Agrega un dato en la cola apuntada por s.
  * \param s Puntero a estructura del tipo @ref Cola_BaseStructTypedef
  * \param dato Dato a incorporar a la cola.
  *
  * \return @ref TColaStatus_Typedef.
  * 	- COLA_COLA_LLENA: Si la cola est� llena y no fue posible agregar el dato.
  * 	- COLA_COLA_OK: La operaci�n fue satisfactoria, el dato se agreg� a la cola.
  */

TColaStatus_Typedef	Cola_AgregarDatoCola (Cola_BaseStructTypedef *s,TColaDato_Typedef dato)
{
	if( s->CantidadCola == s->LongitudCola)	// Condici�n de cola llena
	{
		return COLA_COLA_LLENA;
	}
	else
	{
		*(s->EntradaCola) = dato;			// Agrego el dato a la cola en la ubicacion del puntero EntradaCola
		(s->EntradaCola)++;


		if ((s->EntradaCola) == (s->InicioCola + s->LongitudCola))	// Se incrementa el puntero de entrada y se pregunta si lleg� a la �ltima posici�n reservada de memoria
		{
			s->EntradaCola = s->InicioCola;								// Si lleg� al final de la memoria reservada, comienza desde el principio (cola circular)
		}
		s->CantidadCola ++;				// Incremento el contador de datos en la cola
		return COLA_OK;
	}
}


/**
  * \brief Retira un dato en la cola apuntada por s y lo guarda en dato.
  * \param s Puntero a estructura del tipo @ref Cola_BaseStructTypedef.
  * \param dato Puntero al dato le�do.
  *
  * \return @ref TColaStatus_Typedef.
  *  - COLA_OK: Si fue factible retirar el dato.
  *  - COLA_VACIA: Si el no hay datos a retirar.
  */

TColaStatus_Typedef	Cola_RetirarDatoCola (Cola_BaseStructTypedef *s,TColaDato_Typedef *dato)
{
	if(s->CantidadCola)													// Ingresa si hay datos en la cola
	{
		*dato = *(s->SalidaCola);											// Retiro el dato correspondiente a la ubicacion de salidaCola
		(s->SalidaCola)++;

		if ((s->SalidaCola) == (s->InicioCola + s->LongitudCola))	// Verifica que el puntero no est� al final de la cola
		{
			s->SalidaCola = s->InicioCola;								// Si es asi, la inicializa al principio (Cola circular)
		}
		s->CantidadCola --;												// Decremento la cantidad de datos en la cola
		return COLA_OK;
	}
	else
	{
		return COLA_COLA_VACIA;
	}
}

/**
  * \brief Retira una cantidad de datos en la cola apuntada por s y lo guarda en dato.
  * \param s Puntero a estructura del tipo @ref Cola_BaseStructTypedef.
  * \param dato Puntero al array de destino de los datos retirados.
  * \param cantidad Cantidad de datos a retirar.
  *
  * \return @ref TColaStatus_Typedef.
  *  - COLA_OK: Si fue factible retirar los datos.
  *  - COLA_VACIA: Si no hay suficientes datos para retirar.
  */

TColaStatus_Typedef	Cola_RetirarDatoCola_Multi (Cola_BaseStructTypedef *s,TColaDato_Typedef *dato,uint16_t cantidad)
{
	uint16_t i;

	if(s->CantidadCola < cantidad )		/*No hay cantidad suficiente de datos en la cola para retirar.*/
	{
		return COLA_ERROR;
	}

	for( i = 0; i < cantidad  ;i++)
	{
		*(dato++) = *(s->SalidaCola);									// Retiro el dato correspondiente a la ubicacion de salidaCola
		(s->SalidaCola)++;

		if ((s->SalidaCola) == (s->InicioCola + s->LongitudCola))	// Verifica que el puntero no est� al final de la cola
		{
			s->SalidaCola = s->InicioCola;							// Si es asi, la inicializa al principio (Cola circular)
		}
	}
	s->CantidadCola -= cantidad;											// Decremento la cantidad de datos en la cola
	return COLA_OK;

}

/**
  * \brief Agrega varios datos en la cola de una sola vez.
  * \param s Puntero a estructura del tipo @ref Cola_BaseStructTypedef.
  * \param dato Puntero a los datos a agregar.
  * \param longitud Cantidad de datos a agregar a la cola.
  *
  * \return @ref TColaStatus_Typedef.
  *  - COLA_ERROR: Si la no hay espacio para guardar todos los datos detallados en longitud (no se guarda nada).
  *  - COLA_OK: La operaci�n fue satisfactoria.
  *
  */
TColaStatus_Typedef Cola_AgregarDatoCola_Multi (Cola_BaseStructTypedef *s, TColaDato_Typedef *dato, uint16_t longitud)
{
	uint16_t i;

	if((s->CantidadCola + longitud)>s->LongitudCola)	// Condici�n de cola llena
	{
		return COLA_ERROR;
	}
	else
	{
		for( i = 0; i < longitud ;i++)
		{
			*(s->EntradaCola) = dato[i];			// Agrego el dato a la cola en la ubicacion del puntero EntradaCola
			(s->EntradaCola)++;

			if ((s->EntradaCola) == (s->InicioCola + s->LongitudCola))	// Se incrementa el puntero de entrada y se pregunta si lleg� a la �ltima posici�n reservada de memoria
			{
				s->EntradaCola = s->InicioCola;								// Si lleg� al final de la memoria reservada, comienza desde el principio (cola circular)
			}
		}

		s->CantidadCola+=longitud;				// Incremento el contador de datos en la cola
		return COLA_OK;
	}
}


/**
  * @}
  */
/**
  * @}
  */
