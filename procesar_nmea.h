#ifndef PROCESAR_NMEA_H
#define PROCESAR_NMEA_H

#include <stdio.h>
#include <string.h>

#include "main.h"
#include "procesar_ubx.h"

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

/*
typedef enum {PR_OK, PR_FIN, PR_ERR_NO_CAR_INI, PR_ERR, PR_ERR_SENT, PR_ERR_SUM_VER,
		      PR_ERR_CAR_STATUS, PR_ERR_HORARIO, PR_ERR_CAR_LATITUD, PR_ERR_LATITUD,
		      PR_ERR_CAR_LONGITUD, PR_ERR_LONGITUD, PR_ERR_CAL_FIX, PR_ERR_CANT_SAT,
		      PR_ERR_ELEVACION, PR_ERR_CAR_METRO, PR_ERR_HDOP, PR_ERR_SEP_GEO, PR_ERR_FECHA,
		      PR_ERR_MES, PR_ERR_ANIO, PR_ERR_DIA, PR_ERR_ZONA_HORARIA } procesar_t;
			  SI NO SIRVEN ELIMINAR ESTE COMENTARIO
*/
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


//MANUU te falto los prototipos de muchas funcones ajjja
void imprimir_estructura (gps_t gps_ptr);

procesar_t procesar_nmea (FILE ** pf, gps_t *gps_ptr);

#endif

