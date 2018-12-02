#ifndef PROCESAR_NMEA_GGA_H
#define PROCESAR_NMEA_GGA_H

#include "procesar_nmea.h"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_VALOR_FIX 8
#define MIN_VALOR_FIX 0
#define MAX_VALOR_CANT_SATELITES 12
#define MIN_VALOR_CANT_SATELITES 0

#define CARACTER_NORTE 'n'
#define CARACTER_SUR   's'
#define CARACTER_ESTE  'e'
#define CARACTER_OESTE 'w'
#define CARACTER_UNIDAD_METRO 'm'

#define MULTIPLICADOR_ESTE  1
#define MULTIPLICADOR_OESTE -1
#define MULTIPLICADOR_SUR  -1
#define MULTIPLICADOR_NORTE  1

procesar_t procesar_nmea_gga(gps_t *ggaptr, char *str, char *cadena);
//Esta definicion esta vieja
/* Procesa una línea de stdin (hasta \n) hasta MAX_LONG_SEN. Una vez que se 
 * verifica un dato y es correcto, se carga en la estructura gga_t, 
 * hasta que se acabe la sentencia o halla alguno incorrecto.
 * 
 * Recibe un puntero a la estructura del tipo gga_t
 * 
 * La funcion devuelve:
 * PR_FIN si no hay nada mas que leer en el archivo
 * PR_ERR si el formato de cualquier argument de una linea de datos no esta bien
 * PR_OK si el dato de una linea fue procesado correctamente. 
 */

#endif 
