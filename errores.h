#ifndef ERRORES_H
#define ERRORES_H

#include "verificar_argumentos.h"

#define MSJ_ERROR_PREFIJO "Error"
#define MSJ_ERROR_PUNTERO_NULO "Puntero nulo."
#define MSJ_ERROR_FECHA_INVALIDA "La fecha ingresada es invalida."
#define MSJ_ERROR_NOMBRE_INVALIDO "El nombre ingresado es invalido."
#define MSJ_ERROR_DIA_INVALIDO "El dia ingresado es invalido."
#define MSJ_ERROR_MES_INVALIDO "El mes ingresado es invalido."
#define MSJ_ERROR_ANIO_INVALIDA "El año ingresado es invalido. "
#define MSJ_ERROR_CANT_ARG_INVALIDO "La cantidad de argumentos ingresados no es valida. "
#define MSJ_ERROR_ARG_INVALIDO "El argumento ingresado es invalido. "


/* Dependiendo del estado que reciba, imprime el correspondiente mensaje de error. */
void imprimir_error(status_t estado);



#endif