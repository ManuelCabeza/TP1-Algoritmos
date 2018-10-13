#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "verificaciones_main.h"

status_t validar_argumento_nombre(char *argv_nombre, char *nombre) {

	if (argv_nombre == NULL || nombre == NULL)
		return ST_ERROR_PUNTERO_NULO;
	
	strcpy(nombre, argv_nombre);
	return ST_OK;
	
}

status_t validar_argumento_fecha(char *argv_fecha, int *fecha) {

	char *perr = NULL;
	int cant;

	if (argv_fecha == NULL || fecha == NULL)
		return ST_ERROR_PUNTERO_NULO;
	
	cant = strlen(argv_fecha);
    printf("cant es %d\n", cant);
	if ( (cant + 1) != CANT_MIN_PALABRA)
		return ST_ERROR_FECHA_INVALIDA;
	
	*fecha = strtol(argv_fecha, &perr, 10);

	if (*perr != '\0' || *fecha < 0)
		return ST_ERROR_FECHA_INVALIDA;
	
	return ST_OK;
}

//validar_argumento_mes
//validar_argumento_anio
//validar_argumento_dia