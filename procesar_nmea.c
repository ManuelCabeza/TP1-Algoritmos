#include "procesar_nmea.h"

#include <stdio.h>
#include <string.h>

#include "procesar_nmea_zda.h"
#include "procesar_nmea_gga.h"
#include "procesar_nmea_rmc.h"

procesar_t procesar_nmea (FILE **pf, gps_t *gps_ptr) { 
	
	char cadena[MAX_LONG_SENTENCIA];
	char * ch_ptr;
	
	
	if (!(fgets(cadena, MAX_LONG_SENTENCIA, *pf))) { 
		return PR_FIN; //Ver si esta bien esto
	}
	ch_ptr = cadena;
	
	if (* ch_ptr != CARACTER_INICIO_COMANDO) {
		return PR_ERR_NO_CAR_INI;
	}
	ch_ptr += 3; // Muevo el puntero para que apunte a la primer 'x' de "$GPxxx,"
	
	// Verifico que tipo de sentencia es.
	if (!strncmp(ch_ptr, SENT_GGA, LONG_SENT_GGA)) {
		return procesar_nmea_gga(gps_ptr, ch_ptr, cadena);
	}
	else if (!strncmp(ch_ptr, SENT_ZDA, LONG_SENT_ZDA)) {
		return procesar_nmea_zda(gps_ptr, ch_ptr, cadena);
	}
	else if (!strncmp(ch_ptr, SENT_RMC, LONG_SENT_RMC)) {
		return procesar_nmea_rmc(gps_ptr, ch_ptr, cadena);
	}
	return PR_ERR_SENT;
}


unsigned char nmea_verificar_suma(const char *sentencia) {

	unsigned char suma = 0;

	while ( * sentencia != CARACTER_SUMA_VER) {
		suma ^= *sentencia++;
	}
	return suma;
}

void procesar_horario (horario_t *horario_ptr, float horario) {

	horario_ptr->minuto = (horario - 10000 * (horario_ptr->hora = horario / 10000)) / 100;
	horario_ptr->segundos = horario - 100 * ((int)horario / 100);
}

void procesar_fecha (fecha_t *fecha_ptr, long fecha) {
	
	fecha_ptr->mes = fecha / 100 - 100 * (fecha_ptr->dia = fecha / 10000);
	fecha_ptr->anio = 2000 + (fecha % 100);
}

