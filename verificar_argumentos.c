#include "verificar_argumentos.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "procesar_ubx.h"
//#include "log.h"


status_t procesar_argumentos(int argc, char *argv[], FILE **entrada, FILE **salida, FILE **archivo_log, metadata_t *datos_usuario, protocolo_t *protocolo, int *longitud_lista) {

	int i;
	status_t estado;
	arg_t argumento;

	if (!argv || !entrada || !salida || !archivo_log || !datos_usuario || !protocolo || !longitud_lista) {  
		return ST_ERROR_PUNTERO_NULO;
	}

	if (argc > MAX_CANT_ARG) {
		return ST_ERROR_CANT_ARG_INVALIDO;
	}

	for (i = 1; i < argc; i++) {
		argumento = validar_arg(argv[i]);
		switch (argumento) { 
			case ARG_AYUDA:
				return ST_PEDIR_AYUDA;
				break;
			case ARG_NOMBRE:
				++i;
				estado = validar_argumento_nombre(argv[i], datos_usuario->nombre);
				break;
			case ARG_PROTOCOLO:
				++i;
				estado = validar_argumento_protocolo(argv[i], protocolo); 
				break;
			case ARG_ARCHIVO_ENTRADA:
				++i;
				*entrada = abrir_archivo_entrada(argv[i], protocolo, &estado); 
				if (*entrada == NULL) {
					return ST_ERROR_ARCHIVO_ENTRADA_INVALIDO;
				}
				break;
			case ARG_ARCHIVO_SALIDA:
				++i;
				*salida = abrir_archivo_salida(argv[i], &estado);
				if (*salida == NULL) {
					return ST_ERROR_ARCHIVO_SALIDA_INVALIDO;
				}
				break;
			case ARG_ARCHIVO_LOG:
				++i;
				*archivo_log = abrir_archivo_log(argv[i], &estado);
				if (*archivo_log == NULL) {
					*archivo_log = stderr; /*Para informar que error se cometio*/
					return ST_ERROR_ARCHIVO_LOGS_INVALIDO;
				}
				break;
			case ARG_CANT_MENSAJES:
				++i;
				estado = validar_argumento_cant_msj(argv[i], longitud_lista);
				break;
			case ARG_INVALIDO: 
				return ST_ERROR_ARG_INVALIDO;
				break;
		}

		if (estado != ST_OK) {
			return estado;
		}

	}

	return ST_OK;
}

arg_t validar_arg(char *arg) {

	const char * arg_validos[] = { ARG_VALIDO_AYUDA, ARG_VALIDO_AYUDA_V, ARG_VALIDO_NOMBRE, ARG_VALIDO_NOMBRE_V,
								   ARG_VALIDO_PROTOCOLO, ARG_VALIDO_PROTOCOLO_V, ARG_VALIDO_ARCHIVO_ENTRADA, 
								   ARG_VALIDO_ARCHIVO_ENTRADA_V, ARG_VALIDO_ARCHIVO_SALIDA, 
								   ARG_VALIDO_ARCHIVO_SALIDA_V, ARG_VALIDO_ARCHIVO_LOG,
								   ARG_VALIDO_ARCHIVO_LOG_V, ARG_VALIDO_CANT_MENSAJE, ARG_VALIDO_CANT_MENSAJE_V 
						         };

	size_t i;
	
	for (i = 0; i < MAX_CANT_ARG_VALIDOS; i++) {
		if (strcmp(arg, arg_validos[i]) == 0) {
			/* El  i / 2 es para hacer compatible arg_validos con el enumerativo arg_t*/
			i = i / 2;
			return i;
		}
	}
	
	return ARG_INVALIDO;
}

status_t validar_argumento_protocolo(char *argv_protocolo, protocolo_t *protocolo) {

	if (!argv_protocolo || !protocolo) {
		return ST_ERROR_PUNTERO_NULO;
	}	

    if (strcmp(argv_protocolo, ARG_PROTOCOLO_NMEA) == 0) {
        *protocolo = PROTOCOLO_NMEA; 
        return ST_OK;
    }
    else if (strcmp(argv_protocolo, ARG_PROTOCOLO_UBX) == 0) { 
        *protocolo = PROTOCOLO_UBX;
        return ST_OK;
    }
    if (strcmp(argv_protocolo, ARG_PROTOCOLO_AUTO) == 0) { 
        *protocolo = PROTOCOLO_AUTO;
        return ST_OK;
    }

	*protocolo = PROTOCOLO_INVALIDO;
    return ST_ERROR_PROTOCOLO_INVALIDO;
}


status_t identificar_protocolo_auto(char *arg_archivo_entrada, protocolo_t *protocolo) { 

    uchar aux = 0;
    FILE *entrada;

	if (!arg_archivo_entrada || !protocolo) {
		return ST_ERROR_PUNTERO_NULO;
	}

	if (*protocolo == PROTOCOLO_INVALIDO) {
		return ST_ERROR_PROTOCOLO_INVALIDO;	
	}
	
    entrada = fopen(arg_archivo_entrada, "rb");
    if (entrada == NULL) {
        return ST_ERROR_ARCHIVO_ENTRADA_INVALIDO; 
    }
    
	while (fread(&aux, sizeof(uchar), 1, entrada) == 1) { 
		if (aux == CARACTER_PESO) {
			*protocolo = PROTOCOLO_NMEA;
			fclose(entrada);
            return ST_OK;
		}
		if (aux == B_SYNC1) {
			if (fread(&aux, sizeof(uchar), 1, entrada) != 1) {
				fclose(entrada);
				return ST_ERROR_ARCHIVO_ENTRADA_INVALIDO;
			}
			if (aux == B_SYNC2) {
				*protocolo = PROTOCOLO_UBX;
				fclose(entrada);
				return ST_OK;
			}
		}
    }
	
	fclose(entrada);
    return ST_ERROR_ARCHIVO_ENTRADA_INVALIDO;
}

FILE * abrir_archivo_entrada(char *arg_archivo_entrada, protocolo_t *protocolo, status_t *estado) {
    
	if (!arg_archivo_entrada || !protocolo || !estado) {
		*estado = ST_ERROR_PUNTERO_NULO;
		return NULL;
	}
	if (*protocolo == PROTOCOLO_INVALIDO) { 
		*estado = ST_ERROR_PROTOCOLO_INVALIDO;
		return NULL;
	}
	if (strcmp(arg_archivo_entrada, ARCHIVO_ENTRADA_STDIN) == 0) {
		*estado = ST_OK;
        return stdin;
    }

    if (*protocolo == PROTOCOLO_AUTO) {
        *estado = identificar_protocolo_auto(arg_archivo_entrada, protocolo);
        if (*estado != ST_OK) {
            return NULL;
        }
    }
	/*Si no me dice nada uso la aplicacion automatico */ 
    if (*protocolo == PROTOCOLO_UBX) {
		*estado = ST_OK;        
		return fopen(arg_archivo_entrada, "rb");
    }
    if (*protocolo == PROTOCOLO_NMEA) {
        *estado = ST_OK;
		return fopen(arg_archivo_entrada, "rt");
    }

	*estado = ST_ERROR_ARCHIVO_ENTRADA_INVALIDO;
    return NULL;
}

FILE * abrir_archivo_salida (char *arg_archivo_salida, status_t *estado) {

	if (!arg_archivo_salida|| !estado) {
		*estado = ST_ERROR_PUNTERO_NULO;
		return NULL;
	}

	if(strcmp(arg_archivo_salida, ARCHIVO_SALIDA_STDOUT) == 0) {
		*estado = ST_OK;
		return stdout;
	}
	*estado = ST_OK;
	return fopen(arg_archivo_salida, "wt");
}

FILE * abrir_archivo_log (char *arg_archivo_log, status_t *estado) {

	if (!arg_archivo_log || !estado) {
		*estado = ST_ERROR_PUNTERO_NULO;
		return NULL;
	}
	if (strcmp(arg_archivo_log, ARCHIVO_LOG_STDERR) == 0) {
		*estado = ST_OK;
		return stderr;
	}

	*estado = ST_OK; 

	return fopen(arg_archivo_log, "wt");
}

status_t validar_argumento_nombre(char *argv_nombre, char *nombre) {

	size_t largo;
	if (!argv_nombre|| !nombre) { 
		return ST_ERROR_PUNTERO_NULO;
	}

	largo = (strlen(argv_nombre) + 1); /* Mas el '\0' */

	if (largo > CANT_MAX) {
		return ST_ERROR_NOMBRE_INVALIDO;
	}
	strcpy(nombre, argv_nombre);

	return ST_OK;
}

bool cargar_nombre_por_omision(char *nombre) {

	if (!nombre) {
		return false;
	}
	strcpy(nombre, NOMBRE_POR_OMISION);

	return true;
}

status_t validar_argumento_cant_msj(char *arg_cant_msj, int *cant_msj) {

	if (!arg_cant_msj || !cant_msj) {
		return ST_ERROR_PUNTERO_NULO;
	}
	if(!convertir_a_numero_entero(arg_cant_msj, cant_msj)) {
		return ST_ERROR_CANT_MENSAJES_INVALIDOS;
	}
	if (*cant_msj < 0) {
		return ST_ERROR_CANT_MENSAJES_INVALIDOS;
	}

	return ST_OK;
}

bool convertir_a_numero_entero(char *cadena, int *resultado) {

	char *perr = NULL;

	if (!cadena|| !resultado) { 
		return false;
	}
	*resultado = strtol(cadena, &perr, 10);

	if (*perr != '\0') { 
		return false;
	}
	return true;
}

void imprimir_ayuda(FILE *salida) {

	fprintf(salida, "%s\n", MSJ_IMPRIMIR_AYUDA);

}
