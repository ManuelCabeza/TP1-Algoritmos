#ifndef PROCESAR_NMEA_RMC_H
#define PROCESAR_NMEA_RMC_H

#include "procesar_nmea.h"

#define CARACTER_STATUS_ACTIVO 'a'
#define CARACTER_STATUS_VOID 'v'
#define CARACTER_ESTE 'e'
#define CARACTER_SUR 's'
#define CARACTER_UNIDAD_MAGNETICA 'w'

procesar_t procesar_nmea_rmc(gps_t *zda_ptr, char *ch_ptr, char *cadena);
/* Recibe la estructura a cargar, la cadena de caracteres leida
 * del archivo de entrada y un puntero con el cual recorrer la
 * cadena para hacer las verificaciones y conversiones.
 * De este tipo de sentencia se verifica que todos los campos sean válidos,
 * y que cumplan con las condiciones necesarias (además del checksum final).
 *  Mientras se leen y verifican los mismos se va cargando la estructura 
 * *gga_ptr con la fecha (mes, dia y año), horario, la latitud, la longitud. 
 * Dependiendo si pudo cargar correctamente la estructura devuelve PR_OK o
 *  en otro caso el tipo de error correspondiente. */

#endif

