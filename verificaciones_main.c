#include "verificaciones_main.h"
#include "generar_gpx.h"
#include "procesar_nmea.h"
#include "estructuras.h"
#include "errores.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


status_t procesar_argumentos(int argc, char * argv[], metadata_t * datos_usuario) {

	const char * arg_validos[] = { ARG_VALIDO_AYUDA, ARG_VALIDO_AYUDA_V ,
								   ARG_VALIDO_NOMBRE, ARG_VALIDO_NOMBRE_V,
								   ARG_VALIDO_FECHA, ARG_VALIDO_FECHA_V,
								   ARG_VALIDO_ANIO, ARG_VALIDO_ANIO_V,
								   ARG_VALIDO_MES, ARG_VALIDO_MES_V,
								   ARG_VALIDO_DIA, ARG_VALIDO_DIA_V
						          };

	int fecha = 0;
	int mes = 0;
	int anio = 0;
	int dia = 0;

	int i, j;
	status_t estado;
	bool esta_fecha = false;
	// La uso como bandera indicadora para ver si esta el argumeto -f o --format

	if (!argv|| !datos_usuario)
		return ST_ERROR_PUNTERO_NULO;

	for (i = 1; i < argc; i++) {
		for (j = 0; j < MAX_CANT_ARG; j++) {
			if (strcmp(argv[i], arg_validos[j]) == 0) {
				j = j / 2;
				switch (j) {
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
						estado = validar_argumento_fecha(argv[i], &fecha, datos_usuario);
						break;
					case ARG_ANIO:
						i++;
						if (esta_fecha)
							break;
						estado = validar_argumento_anio(argv[i], &anio, datos_usuario);
						break;
					case ARG_MES:
						i++;
						if (esta_fecha)
							break;
						estado = validar_argumento_mes(argv[i], &mes, datos_usuario);
						break;
					case ARG_DIA:
						i++;
						if (esta_fecha)
							break;
						estado = validar_argumento_dia(argv[i], &dia, datos_usuario);
						break;
				}
				if (estado != ST_OK)
					return estado;

			}
		}
	}

	return ST_OK;
}


bool convertir_a_numero_entero(char *cadena, int *resultado) {

	char *perr = NULL;

	if (!cadena|| !resultado)
		return false;

	*resultado = strtol(cadena, &perr, 10);

	if (*perr != '\0')
		return false;

	return true;
}

status_t validar_argumento_nombre(char *argv_nombre, char *nombre) {

	if (!argv_nombre|| !nombre)
		return ST_ERROR_PUNTERO_NULO;

	strcpy(nombre, argv_nombre);
	return ST_OK;

}

status_t validar_argumento_fecha(char *argv_fecha, int *fecha, metadata_t *datos_usuario) {
//validar mes y dia. y 30 de febrero no es una fecha

	if(!argv_fecha || !fecha || !datos_usuario)
		return ST_ERROR_PUNTERO_NULO;

	if (!convertir_a_numero_entero(argv_fecha, fecha))
		return ST_ERROR_MES_INVALIDO;

	if (*fecha < CANT_MIN_FECHA)
		return ST_ERROR_FECHA_INVALIDA;

	partir_fecha(fecha, datos_usuario);

	if (datos_usuario->fecha.dia < CANT_MIN_DIA || datos_usuario->fecha.dia > CANT_MAX_DIA)
		return ST_ERROR_DIA_INVALIDO;
	if (datos_usuario->fecha.mes < CANT_MIN_MES || datos_usuario->fecha.mes > CANT_MAX_MES)
		return ST_ERROR_MES_INVALIDO;
	if (datos_usuario->fecha.anio < CANT_MIN_ANIO || datos_usuario->fecha.anio > CANT_MAX_ANIO)
		return ST_ERROR_ANIO_INVALIDO;

	return ST_OK;
}

status_t validar_argumento_mes(char *argv_mes, int * mes, metadata_t *datos_usuario) {


	if(!argv_mes || !mes || !datos_usuario)
		return ST_ERROR_PUNTERO_NULO;

	if (!convertir_a_numero_entero(argv_mes, mes))
		return ST_ERROR_MES_INVALIDO;

	if (*mes < CANT_MIN_MES || *mes > CANT_MAX_MES)
		return ST_ERROR_MES_INVALIDO;

	datos_usuario->fecha.mes = * mes;

	return ST_OK;
}

status_t validar_argumento_anio(char *argv_anio, int *anio, metadata_t *datos_usuario) {

	
	if(!argv_anio || !anio || !datos_usuario)
		return ST_ERROR_PUNTERO_NULO;

	if (!convertir_a_numero_entero(argv_anio, anio))
		return ST_ERROR_ANIO_INVALIDO;

	if (*anio < CANT_MIN_ANIO || *anio > CANT_MAX_ANIO)
		return ST_ERROR_ANIO_INVALIDO;

	datos_usuario->fecha.anio = *anio;

	return ST_OK;
}

status_t validar_argumento_dia(char *argv_dia, int *dia, metadata_t *datos_usuario) {
	
	if(!argv_dia || !dia || !datos_usuario)
		return ST_ERROR_PUNTERO_NULO;

	if (!convertir_a_numero_entero(argv_dia, dia))
		return ST_ERROR_DIA_INVALIDO;

	if (*dia < CANT_MIN_DIA || *dia > CANT_MAX_DIA)
		return ST_ERROR_DIA_INVALIDO;

	datos_usuario->fecha.dia = *dia;

	return ST_OK;

}

/*Recibe a fecha:aaaammdd y carga a la estructura año = aaaa, mes = mm y dia = dd */
status_t partir_fecha(int *fecha, metadata_t *datos_usuario) {

	if (!fecha || !datos_usuario)
		return ST_ERROR_PUNTERO_NULO;

	datos_usuario->fecha.anio = *fecha / 10000;
	datos_usuario->fecha.mes = (*fecha % 10000) / 100;
	datos_usuario->fecha.dia = (*fecha % 10000) % 100;

	return ST_OK;

}

bool cargar_fecha_por_omision (metadata_t * datos_usuario) {

    time_t tiempo;
    struct tm * fecha_actual;
    tiempo = time(NULL);
    fecha_actual = localtime(&tiempo);

	if(!(datos_usuario))
		return false;

	datos_usuario->fecha.dia  = fecha_actual->tm_mday;
	datos_usuario->fecha.mes  = (fecha_actual->tm_mon) + AJUSTE_DE_NUM;
	datos_usuario->fecha.anio = (fecha_actual->tm_year) + ANIO_DE_LINUX;

	return true;
}

bool cargar_nombre_por_omision(metadata_t *datos_usuario) {

	if (!datos_usuario)
		return false;

	strcpy(datos_usuario->nombre, NOMBRE_POR_OMISION);

	return true;
}

bool cargar_hora_por_omision (metadata_t * datos_usuario) {

	time_t tiempo;
    struct tm *hora;
    tiempo = time(NULL);
    hora = localtime(&tiempo);

	if(!datos_usuario)
		return false;

	datos_usuario -> horario.segundos = (float)hora -> tm_sec;
	datos_usuario -> horario.minuto = (hora -> tm_min) + AJUSTE_DE_NUM;
	datos_usuario -> horario.hora = (hora ->tm_hour) + AJUSTE_DE_NUM;

	return true;
}

void imprimir_ayuda() {

	printf("%s\n", MSJ_IMPRIMIR_AYUDA);
}