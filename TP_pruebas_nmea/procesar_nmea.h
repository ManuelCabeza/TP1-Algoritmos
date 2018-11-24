#ifndef PROCESAR_NMEA_H
#define PROCESAR_NMEA_H

#include <stdio.h>
#include <string.h>

//BORRAR ESTO
typedef struct {
	int dia;
	int mes;
	int anio;
} fecha_t;
 
typedef struct {
	int hora;
	int minuto;
	float segundos;
} horario_t;
// HASTA ACA

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

typedef enum {INVALIDO, GPS, DGPS, PPS, RTK, FRTK, ESTIMADA, MANUAL, SIMULACION} cal_fix;

typedef struct {
	fecha_t fecha;
	horario_t horario;
	float latitud;
	float longitud;
	cal_fix calidad_fix;
	int cant_satelites;
	float hdop;
	float elevacion;
	float sep_geo;
} gps_t;

typedef enum {PR_OK, PR_FIN, PR_ERR_NO_CAR_INI, PR_ERR, PR_ERR_SENT, PR_ERR_SUM_VER,
		      PR_ERR_CAR_STATUS } procesar_t;

void procesar_fecha (fecha_t * fecha_ptr, long fecha);
/* Carga la estructura con formato ddmmyy de la forma
 * fecha.dia dd
 * fecha.mes mm
 * fecha.anio 20yy
*/

void procesar_horario(horario_t * horario_str, float horario);
/* Carga la estructura con un horario de formato hhmmss.sss (o mas s), recibe 
 * un puntero a la estructura del tipo horario_t y un horario a convertir. 
 * Carga la estructura con :
 * horario.hora = hh
 * horario.minuto = mm
 * horario.segundo = ss.sss
*/

unsigned char nmea_verificar_suma(const char * sentencia);
/* Recibe una sentencia y calcula la XOR de todos los bytes hasta llegar a
 * un caracter de corte que se define por la macro CARACTER_SUMA_VER.
 * 
 * Recibe un puntero al comienzo de la sentencia a calcular
 * Devuelve la suma XOR
*/

#endif

