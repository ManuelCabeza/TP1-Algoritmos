#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>

#include "verificar_argumentos.h"

#define MSJ_VACIO ""
#define MSJ_ERROR_PUNTERO_NULO "Puntero nulo."
#define MSJ_ERROR_NOMBRE_INVALIDO "El nombre ingresado es invalido." //lo voy a eliminar!
#define MSJ_ERROR_PROTOCOLO "El protocolo ingresado es invalido."
#define MSJ_ERROR_ARCHIVO_ENTRADA "El archivo de entrada es invalido." 
#define MSJ_ERROR_ARCHIVO_SALIDA "El archivo de salida es invalido."
#define MSJ_ERROR_ARCHIVO_LOG "El archivo log es invalido."
#define MSJ_ERROR_CANTIDAD_MSJ "La cantidad de mensajes no es valido."
#define MSJ_ERROR_CANT_ARG_INVALIDO "La cantidad de argumentos ingresados es invalido."
#define MSJ_ERROR_ARG_INVALIDO "El argumento ingresado es invalido, pruebe ingresando el comando -h para obtener ayuda." 
#define MSJ_ERROR_LECTURA "No se pudo leer el archivo"

/*
para los debug
#define MSJ_DEBUG_BUSCANDO_SINCRONISMO "Buscando los 2 bytes de sincronismo." 
#define MSJ_DEBUG_ID "Se detecta un determinado ID."
#define MSJ_DEBUG_RECOLECTO_MSJ "Se recolectò un mensaje."
#define MSJ_DEBUG_CARGO_MSJ "Se cargó un mensaje en la lista."
#define MSJ_DEBUG_IMPRIMIO_MSJ "Se imprimió un mensaje."
etc.
*/

/*
WARN
#define MSJ_WARN_ID "No se reconoce un ID"
#define MSJ_WARN_FIX_INVALIDO "Un mensaje contiene un ﬁx inválido"
#define MSJ_WARN_LISTA_LLENA "Se descarta un mensaje por lista llena."
etc. 
*/

void imprimir_msj_log(status_t estado, FILE *archivo_log, gps_t *datos_satelite);
/* Dependiendo del estado que reciba, imprime el correspondiente mensaje en el
 * archivo log. Los mensajes pueden ser: 
 * ERROR: Son errores graves que ocurren durante la ejecució
 * DEBUG: Son mensajes de información sobre lo que está haciendo el programa. 
 * WARN: Son avisos que ocurren durante la ejecucion 
 * Por defecto, la impresion sale por stderr. 
 * Recibe un estado, un puntero al archivo log y la estrustura datos_satelite,
 * donde se imprime la hora y fecha de cuando ocurren los mensajes.
*/

#endif