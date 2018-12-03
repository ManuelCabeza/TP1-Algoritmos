#ifndef PROCESAR_NMEA_ZDA_H
#define PROCESAR_NMEA_ZDA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "procesar_nmea.h"

/* Carga en la estructura el horario y la fecha
*/
procesar_t procesar_nmea_zda(gps_t *zda_ptr, char *ch_ptr, char *cadena);


#endif
