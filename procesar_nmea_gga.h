#ifndef PROCESAR_NMEA_GGA_H
#define PROCESAR_NMEA_GGA_H

#include <stdio.h>

#include "procesar_nmea.h"

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
/* Recibe la estructura a cargar, la cadena de caracteres leida del archivo de entrada
 * y un puntero con el cual recorrer la cadena para hacer las verificaciones y conversiones. 
 *  De este tipo de sentencia se verifica que todos los campos sean válidos, y
 * que cumplan con las condiciones necesarias (además del checksum final). 
 * Mientras se leen y verifican los mismos se va cargando la estructura *gga_ptr con la 
 * latitud, longitud, cal_fix, horario, cant_satelites, Hdop, elevación y sep_geo.
 *  Dependiendo si pudo cargar correctamente la estructura devuelve PR_OK o
 * en otro caso el tipo de error correspondiente del enumerativo procesar_t.
*/
#endif 
