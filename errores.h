#ifndef ERRORES_H
#define ERRORES_H

#include <stdio.h>
#include <stdlib.h>

#include "verificar_argumentos.h"
/*
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
*/
/*
para los debug
 #define MSJ_DEBUG_BUSCANDO_SINCRONISMO "buscando los 2 bytes de sincronismo" 
 #define MSJ_DEBUG_ID "detecta un determinado ID"

 recolectó un mensaje, 
 cargó un mensaje en la lista, 
 imprimió un mensaje, etc.


*/

/*
WARN
No se reconoce un ID 
Un mensaje contiene un ﬁx inválido
Se descarta un mensaje por lista llena, etc. 

*/


/*
void imprimir_msj_log(status_t estado, FILE *archivo_log, gps_t *datos_satelite);
*/
/* Dependiendo del estado que reciba, imprime el correspondiente mensaje en el
archivo log. Los mensajes pueden ser: 
ERROR: Son errores graves que ocurren durante la ejecució
DEBUG: Son mensajes de información sobre lo que está haciendo el programa. 
WARN: Son avisos que ocurren durante la ejecucion 
Por defecto, la impresion sale por stderr. */

#endif
