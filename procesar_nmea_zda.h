#ifndef PROCESAR_NMEA_ZDA_H
#define PROCESAR_NMEA_ZDA_H

#include "procesar_nmea.h"


procesar_t procesar_nmea_zda(gps_t *zda_ptr, char *ch_ptr, char *cadena);
/* Recibe la estructura a cargar, la cadena de caracteres
 * leida del archivo de entrada y un puntero con el cual recorrer
 * la cadena para hacer las verificaciones y conversiones. 
 * De este tipo de sentencia se verifica que todos los campos sean
 * válidos, y que cumplan con las condiciones necesarias (además del checksum final).
 * Mientras se leen y verifican los mismos se va cargando la estructura
 * *gga_ptr con la fecha (mes, dia y año) y el horario.
 *  Dependiendo si pudo cargar correctamente la estructura devuelve PR_OK
 *  o en otro caso el tipo de error correspondiente. */

#endif
