#ifndef PROCESAR_NMEA_RMC_H
#define PROCESAR_NMEA_RMC_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//estaba en el .h
#include "main.h"
#include "procesar_nmea.h"

#define CARACTER_STATUS_ACTIVO 'a'
#define CARACTER_STATUS_VOID 'v'
#define CARACTER_ESTE 'e'
#define CARACTER_SUR 's'
#define CARACTER_UNIDAD_MAGNETICA 'w'

procesar_t procesar_nmea_rmc(gps_t * zda_ptr, char * ch_ptr, char * cadena);


#endif

