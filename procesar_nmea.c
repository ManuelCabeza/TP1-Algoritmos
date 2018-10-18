#include "procesar_nmea.h"
#include "estructuras.h"
#include "verificaciones_main.h"
#include "generar_gpx.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

procesar_t procesar_nmea(gga_t * ggaptr) {

	char c; /*Variable auxiliar para no usar tolower mas de 2 veces.*/
	char string[MAX_LONG_SEN];
	char * strptr;

	long suma_verificacion;
	float horario;
	float longitud;
	float latitud;

	if (fgets(string, MAX_LONG_SEN,stdin) == NULL)
		return PR_FIN;

	strptr = string;

	if (* strptr != CARACTER_INICIO_COMANDO)
		return PR_ERR;


	if ((strptr = strchr(string, CARACTER_SEPARACION_COMANDO)) != NULL) {
		strptr++;
		if ((horario = strtof(strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) { 
			return PR_ERR;
		}
	}

	procesar_horario(ggaptr, horario);

	if ((latitud = strtof(strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) { 
		return PR_ERR;
	}

	c = tolower( * (strptr++));
	if ((c != CARACTER_NORTE) && (c != CARACTER_SUR)){ 
		return PR_ERR;
	}

	/* Asigna valor de latitud a partir de formato ddmm.mmm */
	ggaptr->latitud = (((int)latitud / 100) + ((latitud - 100 * ((int)latitud / 100)) / 60 )) * (c == CARACTER_SUR ? -1 : 1);



	if ((longitud = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO))
		return PR_ERR;

	c = tolower( * (strptr++));
	if ((c != CARACTER_ESTE) && (c != CARACTER_OESTE))
		return PR_ERR;

	/* Asigna valor de longitud a partir de formato dddmm.mmm */
	ggaptr->longitud = (((int)longitud / 100) + ((longitud - 100 * ((int)longitud / 100)) / 60 )) * (c == CARACTER_OESTE ? -1 : 1);

	if ((ggaptr->calidad_fix = strtol(++strptr, &strptr, 10)) < MIN_VALOR_FIX || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO) || (ggaptr->calidad_fix) > MAX_VALOR_FIX)
		return PR_ERR;

	if ((ggaptr->cant_satelites = strtof(++strptr, &strptr)) < MIN_VALOR_CANT_SATELITES || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO) || (ggaptr->cant_satelites > MAX_VALOR_CANT_SATELITES))
		return PR_ERR;

	if ((ggaptr->hdop = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO))
		return PR_ERR;

	if ((ggaptr->elevacion = strtof(strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO))
		return PR_ERR;

	if (tolower(* strptr++) != CARACTER_UNIDAD)
		return PR_ERR;

	if ((ggaptr->sep_geo = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO))
		return PR_ERR;

	if (tolower(* strptr) != CARACTER_UNIDAD)
		return PR_ERR;

	if ((strptr = strrchr(string, CARACTER_SUMA_VER)) == NULL)
		return PR_ERR;

	suma_verificacion = strtol( ++strptr, NULL, 16);

	strptr = string + 1;

	if (nmea_verificar_suma( strptr) != suma_verificacion)
		return PR_ERR;
	
	return PR_OK;
}




unsigned char nmea_verificar_suma(const char * sentencia) {

	unsigned char suma = 0;

	while ( * sentencia != CARACTER_SUMA_VER )
		suma ^= *sentencia++;

	return suma;
}

void procesar_horario(gga_t * estructura, float horario) {

	estructura->horario.minuto = (horario - 10000 * (estructura->horario.hora = horario / 10000)) / 100;

	estructura->horario.segundos = horario - 100 * ((int)horario / 100);
}