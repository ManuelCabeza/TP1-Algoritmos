#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "verificaciones_main.h"

bool convertir_a_numero_entero(char *cadena, int *resultado) {

	char *perr = NULL;

	if (cadena == NULL || resultado == NULL)
		return false;
	
	*resultado = strtol(cadena, &perr, 10);

	if (*perr != '\0') 
		return false;

	return true;
}

status_t validar_argumento_nombre(char *argv_nombre, char *nombre) {
//Nombre puede aceptar numeros? onda nombre123 como los mails
//valido que si me ponen nombre -123435?
	if (argv_nombre == NULL || nombre == NULL)
		return ST_ERROR_PUNTERO_NULO;
	
	strcpy(nombre, argv_nombre);
	return ST_OK;
	
}

status_t validar_argumento_fecha(char *argv_fecha, int *fecha) { //ANALIZAR COMO VALIDAR LOS MES Y DIA EN FECAH
//validar mes y dia. y 30 de febrero no es una fecha
	if (!convertir_a_numero_entero(char *argv_fecha, int *fecha))
		return ST_ERROR_MES_INVALIDO;

	if (*fecha < 0) 
		return ST_ERROR_FECHA_INVALIDA;
	
	return ST_OK;
}

status_t validar_argumento_mes(char *argv_mes, int *mes) {
	
	if (!convertir_a_numero_entero(char *argv_mes, int *mes))
		return ST_ERROR_MES_INVALIDO;

	if (*mes < CANT_MIN_MES || *mes > CANT_MAX_MES) 
		return ST_ERROR_MES_INVALIDO;

	return ST_OK;	
}
status_t validar_argumento_anio(char *argv_anio, int *anio) {
//cuesta mas trabajo usar strlen para leer una cantidad de una cadena y despues ver si eso esta bien.
	if (!convertir_a_numero_entero(char *argv_anio, int *anio))
		return ST_ERROR_ANIO_INVALIDO;

	if (*anio > CANT_MIN_ANIO || *anio < CANT_MAX_ANIO)
		return ST_ERROR_ANIO_INVALIDO;

	return ST_OK;
}
status_t validar_argumento_dia(char *argv_dia, int *dia) {

	if (!convertir_a_numero_entero(char *argv_dia, int *dia))
		return ST_ERROR_DIA_INVALIDO;

	if (*dia > CANT_MIN_DIA || *dia < CANT_MAX_DIA)
		return ST_ERROR_DIA_INVALIDO;

	return ST_OK;

}

