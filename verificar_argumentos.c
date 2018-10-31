#include "verificar_argumentos.h"
#include "generar_gpx.h"
#include "procesar_nmea.h"
#include "main.h"
#include "errores.h"

#define MAX_CANT_ARG 10

status_t procesar_argumentos(int argc, char * argv[], metadata_t * datos_usuario) {

	int i;
	status_t estado;
	bool esta_fecha = false;  
	/* La uso como bandera indicadora para ver si esta el argumeto -f o --format */
	arg_t argumento;

	if (!argv || !datos_usuario) { 
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
				i++;
				estado = validar_argumento_nombre(argv[i], datos_usuario->nombre);
				break;
			case ARG_FECHA:
				esta_fecha = true;
				i++;
				estado = validar_argumento_fecha(argv[i], &(datos_usuario->fecha));
				break;
			case ARG_ANIO:
				i++;
				if (esta_fecha) { 
					break;
				}
				estado = validar_argumento_anio(argv[i], &(datos_usuario->fecha).anio);
				break;
			case ARG_MES:
				i++;
				if (esta_fecha) {
					break;
				}
				estado = validar_argumento_mes(argv[i], &(datos_usuario->fecha).mes);
				break;
			case ARG_DIA:
				i++;
				if (esta_fecha) { 
					break;
				}
				estado = validar_argumento_dia(argv[i], &(datos_usuario->fecha).dia);
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

	const char * arg_validos[] = { ARG_VALIDO_AYUDA, ARG_VALIDO_AYUDA_V ,
								   ARG_VALIDO_NOMBRE, ARG_VALIDO_NOMBRE_V,
								   ARG_VALIDO_FECHA, ARG_VALIDO_FECHA_V,
								   ARG_VALIDO_ANIO, ARG_VALIDO_ANIO_V,
								   ARG_VALIDO_MES, ARG_VALIDO_MES_V,
								   ARG_VALIDO_DIA, ARG_VALIDO_DIA_V
						          };

	size_t i;
	
	for (i = 0; i < MAX_CANT_ARG_VALIDOS; i++) {
		if (strcmp(arg, arg_validos[i]) == 0) {
			i = i / 2;
			return i;
		}
	}
	
	return ARG_INVALIDO;
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

status_t validar_argumento_fecha(char *argv_fecha, fecha_t *fecha) {

	int fecha_por_comando;
	
	if(!argv_fecha || !fecha) {
		return ST_ERROR_PUNTERO_NULO;
	}
	if (!convertir_a_numero_entero(argv_fecha, &fecha_por_comando)) {
		return ST_ERROR_FECHA_INVALIDA;
	}
	if (fecha_por_comando < CANT_MIN_FECHA) {
		return ST_ERROR_FECHA_INVALIDA;
	}
	partir_fecha(fecha_por_comando, fecha);

	if (fecha->dia < CANT_MIN_DIA || fecha->dia > CANT_MAX_DIA) {
		return ST_ERROR_DIA_INVALIDO;
	}
	if (fecha->mes < CANT_MIN_MES || fecha->mes > CANT_MAX_MES) {
		return ST_ERROR_MES_INVALIDO;
	}	
	if (fecha->anio < CANT_MIN_ANIO || fecha->anio > CANT_MAX_ANIO) {
		return ST_ERROR_ANIO_INVALIDO;
	}
	return ST_OK;
}

status_t validar_argumento_mes(char *argv_mes, int * mes) {

	if(!argv_mes || !mes) {
		return ST_ERROR_PUNTERO_NULO;
	}
	if (!convertir_a_numero_entero(argv_mes, mes)) {
		return ST_ERROR_MES_INVALIDO;
	}
	if (*mes < CANT_MIN_MES || *mes > CANT_MAX_MES) {
		return ST_ERROR_MES_INVALIDO;
	}

	return ST_OK;
}

status_t validar_argumento_anio(char *argv_anio, int *anio) {

	if(!argv_anio || !anio) {
		return ST_ERROR_PUNTERO_NULO;
	}
	if (!convertir_a_numero_entero(argv_anio, anio)) {
		return ST_ERROR_ANIO_INVALIDO;
	}
	if (*anio < CANT_MIN_ANIO || *anio > CANT_MAX_ANIO) {
		return ST_ERROR_ANIO_INVALIDO;
	}

	return ST_OK;
}

status_t validar_argumento_dia(char *argv_dia, int *dia) {
	
	if(!argv_dia || !dia) {
		return ST_ERROR_PUNTERO_NULO;
	}
	if (!convertir_a_numero_entero(argv_dia, dia)) {
		return ST_ERROR_DIA_INVALIDO;
	}
	if (*dia < CANT_MIN_DIA || *dia > CANT_MAX_DIA) {
		return ST_ERROR_DIA_INVALIDO;
	}

	return ST_OK;
}

/*Recibe a fecha:aaaammdd y carga a la estructura año = aaaa, mes = mm y dia = dd */
status_t partir_fecha(int fecha_actual, fecha_t *fecha) {

	if (!fecha) {
		return ST_ERROR_PUNTERO_NULO;
	}
	fecha->anio = fecha_actual / 10000;
	fecha->mes = (fecha_actual % 10000) / 100;
	fecha->dia = (fecha_actual % 10000) % 100;

	return ST_OK;
}

bool cargar_fecha_por_omision(fecha_t *fecha) {

    time_t tiempo;
    struct tm * fecha_actual;
    tiempo = time(NULL);
    fecha_actual = localtime(&tiempo);

	if(!fecha) {
		return false;
	}
	fecha->dia  = fecha_actual->tm_mday;
	fecha->mes  = (fecha_actual->tm_mon) + AJUSTE_DE_NUM;
	fecha->anio = (fecha_actual->tm_year) + ANIO_DE_LINUX;

	return true;
}

bool cargar_nombre_por_omision(char *nombre) {

	size_t largo;

	if (!nombre) {
		return false;
	}
	largo = (strlen(nombre) + 1); /* Mas el '\0' */

	if (largo > CANT_MAX) {
		return ST_ERROR_NOMBRE_INVALIDO;
	}
	strcpy(nombre, NOMBRE_POR_OMISION);

	return true;
}

bool cargar_hora_por_omision (horario_t *horario) {

	time_t tiempo;
    struct tm *hora;
    tiempo = time(NULL);
    hora = localtime(&tiempo);

	if(!horario) {
		return false;
	}
	horario->segundos = (float)hora -> tm_sec;
	horario->minuto = (hora -> tm_min) + AJUSTE_DE_NUM;
	horario->hora = (hora ->tm_hour);

	return true;
}

void imprimir_ayuda(void) {

	printf("%s\n", MSJ_IMPRIMIR_AYUDA);
}