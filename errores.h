#ifndef ERRORES_H
#define ERRORES_H

#include <stdio.h>
#include <stdlib.h>

#include "verificar_argumentos.h"

#define MSJ_ERROR_PREFIJO "Error"
#define MSJ_VACIO ""
#define MSJ_ERROR_PUNTERO_NULO "Puntero nulo."
#define MSJ_ERROR_NOMBRE_INVALIDO "El nombre ingresado es invalido." //lo voy a eliminar!
#define MSJ_ERROR_PROTOCOLO "El protocolo ingresado es invalido."
#define MSJ_ERROR_ARCHIVO_ENTRADA "El archivo de entrada es invalido." //Tengo que deci que no existe?
#define MSJ_ERROR_ARCHIVO_SALIDA "El archivo de salida es invalido."
#define MSJ_ERROR_ARCHIVO_LOG "El archivo log es invalido."
#define MSJ_ERROR_CANTIDAD_MSJ "La cantidad de mensajes no es valido."
#define MSJ_ERROR_CANTIDAD_ARGUMENTOS_INVALIDOS "La cantidad de argumentos ingresados es invalido."

#define MSJ_ERROR_ARG_INVALIDO "El argumento ingresado es invalido, pruebe ingresando el comando -h para obtener ayuda." 

#define MSJ_ERROR_LECTURA "No se pudo leer el archivo"
/* Dependiendo del estado que reciba, imprime el correspondiente mensaje de error. */


void imprimir_msj_log(status_t estado, FILE *archivo_log);

#endif