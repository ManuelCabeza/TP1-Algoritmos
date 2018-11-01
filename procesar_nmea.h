#ifndef PROCESAR_NMEA_H
#define PROCESAR_NMEA_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "verificar_argumentos.h"
#include "main.h"

#define MAX_LONG_SEN 90
#define CANT_ARGUMENTOS 14
#define MAX_VALOR_FIX 8
#define MIN_VALOR_FIX 0
#define MAX_VALOR_CANT_SATELITES 12
#define MIN_VALOR_CANT_SATELITES 0

#define CARACTER_NORTE 'n'
#define CARACTER_SUR   's'
#define CARACTER_ESTE  'e'
#define CARACTER_OESTE 'w'
#define CARACTER_UNIDAD 'm'
#define CARACTER_INICIO_COMANDO '$' 
#define CARACTER_SEPARACION_COMANDO ','
#define CARACTER_SUMA_VER '*'

#define MULTIPLICADOR_ESTE  1
#define MULTIPLICADOR_OESTE -1
#define MULTIPLICADOR_SUR  -1
#define MULTIPLICADOR_NORTE  1


typedef enum {INVALIDO, GPS, DGPS, PPS, RTK, FRTK, ESTIMADA, MANUAL, SIMULACION} cal_fix;

typedef struct {
	horario_t horario;
	float latitud;
	float longitud;
	cal_fix calidad_fix;
	int cant_satelites;
	float hdop;
	float elevacion;
	float sep_geo;
} gga_t;

typedef enum {PR_OK, PR_ERR, PR_FIN} procesar_t;

/* Carga la estructura con un horario de formato hhmmss.sss (o mas s), recibe 
 * un puntero a la estructura del tipo horario_t y un horario a convertir. 
 * Carga la estructura con :
 * horario.hora = hh
 * horario.minuto = mm
 * horario.segundo = ss.sss
*/
void procesar_horario(horario_t * horario_str, float horario);

/* Recibe una sentencia y calcula la XOR de todos los bytes hasta llegar a
 * un caracter de corte que se define por la macro CARACTER_SUMA_VER.
 * 
 * Recibe un puntero al comienzo de la sentencia a calcular
 * Devuelve la suma XOR
*/
unsigned char nmea_verificar_suma(const char * sentencia);

/* Procesa una línea de stdin (hasta \n) hasta MAX_LONG_SEN. Una vez que se 
 * verifica un dato y es correcto, se carga en la estructura gga_t, 
 * hasta que se acabe la sentencia o halla alguno incorrecto.
 * 
 * Recibe un puntero a la estructura del tipo gga_t
 * 
 * La funcion devuelve:
 * PR_FIN si no hay nada mas que leer en el archivo
 * PR_ERR si el formato de cualquier argument de una linea de datos no esta bien
 * PR_OK si el dato de una linea fue procesado correctamente. */
procesar_t procesar_nmea(gga_t * ggaptr);

#endif 