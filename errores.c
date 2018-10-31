#include <stdio.h>
#include "errores.h"
#include "verificar_argumentos.h"


void imprimir_error(status_t estado) {

	const char * msj_error[] = { MSJ_VACIO, MSJ_VACIO,
								MSJ_ERROR_PUNTERO_NULO, MSJ_ERROR_FECHA_INVALIDA,
							    MSJ_ERROR_NOMBRE_INVALIDO, MSJ_ERROR_DIA_INVALIDO,
								MSJ_ERROR_MES_INVALIDO, MSJ_ERROR_ANIO_INVALIDA,
								MSJ_ERROR_CANT_ARG_INVALIDO, MSJ_ERROR_ARG_INVALIDO
							   };


	fprintf(stderr, "%s : %s\n", MSJ_ERROR_PREFIJO, msj_error[estado]);
}

