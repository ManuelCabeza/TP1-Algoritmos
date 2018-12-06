#ifndef PROCESAR_NMEA_H
#define PROCESAR_NMEA_H

#include <stdio.h>

#include "main.h"

#define MAX_LONG_SENTENCIA 95

#define SENT_GGA "GGA"
#define LONG_SENT_GGA 3
#define SENT_ZDA "ZDA"
#define LONG_SENT_ZDA 3
#define SENT_RMC "RMC"
#define LONG_SENT_RMC 3

#define CARACTER_SEPARACION_COMANDO ','
#define CARACTER_SUMA_VER '*'
#define CARACTER_INICIO_COMANDO '$' 

#ifndef PROCESAR
#define PROCESAR
typedef enum { PR_OK = 0, PR_FIN, PR_ERR_NO_CAR_INI, PR_ERR, PR_ERR_SENT, 
			   PR_ERR_CAR_STATUS, PR_ERR_HORARIO, PR_ERR_CAR_LATITUD, 
			   PR_ERR_LATITUD, PR_ERR_CAR_LONGITUD, PR_ERR_LONGITUD, 
			   PR_ERR_CAL_FIX, PR_ERR_CANT_SAT, PR_ERR_ELEVACION, 
			   PR_ERR_CAR_METRO, PR_ERR_HDOP, PR_ERR_SEP_GEO, PR_ERR_FECHA,
		       PR_ERR_MES, PR_ERR_ANIO, PR_ERR_DIA, PR_ERR_ZONA_HORARIA,
			   PR_ERR_ARCHIVO, PR_ERR_PTR_NULL, PR_ERR_CLASE, 
			   PR_ERR_ID, PR_ERR_LARGO, PR_ERR_SUM_VER, PR_ERR_VALID_FLAGS, 
			   PR_ERR_VALID_FIX, PUE_NOT, PR_DEBUG, PR_ERR_SEG, PR_ERR_MIN 
			   } procesar_t;

#endif
void procesar_fecha (fecha_t *fecha_ptr, long fecha);
/* Carga la estructura con formato ddmmyy de la forma
 * fecha.dia dd
 * fecha.mes mm
 * fecha.anio 20yy
*/

void procesar_horario(horario_t *horario_str, float horario);
/* Carga la estructura con un horario de formato hhmmss.sss (o mas s), recibe 
 * un puntero a la estructura del tipo horario_t y un horario a convertir. 
 * Carga la estructura con :
 * horario.hora = hh
 * horario.minuto = mm
 * horario.segundo = ss.sss
*/

unsigned char nmea_verificar_suma(const char *sentencia);
/* Recibe una sentencia y calcula la XOR de todos los bytes hasta llegar a
 * un caracter de corte que se define por la macro CARACTER_SUMA_VER.
 * 
 * Recibe un puntero al comienzo de la sentencia a calcular
 * Devuelve la suma XOR
*/

procesar_t procesar_nmea (FILE ** pf, gps_t *gps_ptr);
/* Recibe un doble ptr a un archivo abierto en modo lectura rt y un ptr a 
 * la estructura gps.
 * Si no se encuentra el caracter de incio de comando o una sentencia 
 * valida, devuelve el tipo de error procesar_t correspondiente, sino
 * dependiendo de la sentencia lo que devuelvan las funciones
 * procesar_nmea_gga, procesar_nmea_rmc o procesar_nmea_zda.
 * Ademas si no hay nada mas que leer devuelve PR_FIN
*/

#endif

