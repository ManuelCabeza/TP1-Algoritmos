#include "procesar_nmea.h"
#include "main.h"
#include "verificar_argumentos.h"
#include "generar_gpx.h"

procesar_t procesar_nmea(gga_t * ggaptr) {

	char c; /*Variable auxiliar para no usar tolower mas de 2 veces.*/
	char string[MAX_LONG_SEN];
	char * str;

	long suma_verificacion;
	float horario;
	float longitud;
	float latitud;

	if (fgets(string, MAX_LONG_SEN,stdin) == NULL) {
		return PR_FIN;
	}
	str = string;

	if (* str != CARACTER_INICIO_COMANDO) {
		return PR_ERR;
	}

	if ((str = strchr(string, CARACTER_SEPARACION_COMANDO)) != NULL) {
		str++;
		if ((horario = strtof(str, &str)) < 0 || ((* (str++)) != CARACTER_SEPARACION_COMANDO)) { 
			return PR_ERR;
		}
	}

	procesar_horario(ggaptr, horario);

	if ((latitud = strtof(str, &str)) < 0 || ((* (str++)) != CARACTER_SEPARACION_COMANDO)) { 
		return PR_ERR;
	}

	c = tolower( * (str++));
	if ((c != CARACTER_NORTE) && (c != CARACTER_SUR)){ 
		return PR_ERR;
	}

	/* Asigna valor de latitud a partir de formato ddmm.mmm */
	ggaptr->latitud = (((int)latitud / 100) + ((latitud - 100 * ((int)latitud / 100)) / 60 )) * (c == CARACTER_SUR ? -1 : 1);



	if ((longitud = strtof(++str, &str)) < 0 || ((* (str++)) != CARACTER_SEPARACION_COMANDO)) {
		return PR_ERR;
	}
	c = tolower( * (str++));
	if ((c != CARACTER_ESTE) && (c != CARACTER_OESTE)) {
		return PR_ERR;
	}
	/* Asigna valor de longitud a partir de formato dddmm.mmm */
	ggaptr->longitud = (((int)longitud / 100) + ((longitud - 100 * ((int)longitud / 100)) / 60 )) * (c == CARACTER_OESTE ? -1 : 1);

	if ((ggaptr->calidad_fix = strtol(++str, &str, 10)) < MIN_VALOR_FIX || ((* (str++)) != CARACTER_SEPARACION_COMANDO) || (ggaptr->calidad_fix) > MAX_VALOR_FIX) {
		return PR_ERR;
	}
	if ((ggaptr->cant_satelites = strtof(++str, &str)) < MIN_VALOR_CANT_SATELITES || ((* (str++)) != CARACTER_SEPARACION_COMANDO) || (ggaptr->cant_satelites > MAX_VALOR_CANT_SATELITES)) {
		return PR_ERR;
	}
	if ((ggaptr->hdop = strtof(++str, &str)) < 0 || ((* (str++)) != CARACTER_SEPARACION_COMANDO)) {
		return PR_ERR;
	}
	if ((ggaptr->elevacion = strtof(str, &str)) < 0 || ((* (str++)) != CARACTER_SEPARACION_COMANDO)) {
		return PR_ERR;
	}
	if (tolower(* str++) != CARACTER_UNIDAD) {
		return PR_ERR;
	}
	if ((ggaptr->sep_geo = strtof(++str, &str)) < 0 || ((* (str++)) != CARACTER_SEPARACION_COMANDO)) {
		return PR_ERR;
	}
	if (tolower(* str) != CARACTER_UNIDAD) {
		return PR_ERR;
	}
	if ((str = strrchr(string, CARACTER_SUMA_VER)) == NULL) {
		return PR_ERR;
	}
	suma_verificacion = strtol(++str, NULL, 16);

	str = string + 1;

	if (nmea_verificar_suma( str) != suma_verificacion) {
		return PR_ERR;
	}
	return PR_OK;
}




unsigned char nmea_verificar_suma(const char * sentencia) {

	unsigned char suma = 0;

	while ( * sentencia != CARACTER_SUMA_VER) {
		suma ^= *sentencia++;
	}
	return suma;
}

void procesar_horario(gga_t * estructura, float horario) {

	estructura->horario.minuto = (horario - 10000 * (estructura->horario.hora = horario / 10000)) / 100;

	estructura->horario.segundos = horario - 100 * ((int)horario / 100);
}