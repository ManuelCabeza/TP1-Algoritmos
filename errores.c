#include <stdio.h>
#include "errores.h"
#include "verificaciones_main.h"

void imprimir_errores(status_t estado) {

	switch (estado) {
		case ST_OK:
			break;
		case ST_ERROR_PUNTERO_NULO:
			fprintf(stderr, "%s : %s\n", MSJ_ERROR_PREFIJO, MSJ_ERROR_PUNTERO_NULO);
			break;
		case ST_ERROR_FECHA_INVALIDA:
			fprintf(stderr, "%s : %s\n", MSJ_ERROR_PREFIJO, MSJ_ERROR_FECHA_INVALIDA);
			break;
		case ST_ERROR_NOMBRE_INVALIDO:
			fprintf(stderr, "%s : %s\n", MSJ_ERROR_PREFIJO, MSJ_ERROR_NOMBRE_INVALIDO);
			break;
		case ST_ERROR_DIA_INVALIDO:
			fprintf(stderr, "%s : %s\n", MSJ_ERROR_PREFIJO, MSJ_ERROR_DIA_INVALIDO);
			break;
		case ST_ERROR_MES_INVALIDO:
			fprintf(stderr, "%s : %s\n", MSJ_ERROR_PREFIJO, MSJ_ERROR_MES_INVALIDO);
			break;
		case ST_ERROR_ANIO_INVALIDO:
			fprintf(stderr, "%s : %s\n", MSJ_ERROR_PREFIJO, MSJ_ERROR_ANIO_INVALIDA);
			break;
		case ST_PEDIR_AYUDA:
			break;
		case ST_ERROR_ARG_INVALIDO:
			fprintf(stderr, "%s : %s\n", MSJ_ERROR_PREFIJO, MSJ_ERROR_ARG_INVALIDO);
			break;
	}

}