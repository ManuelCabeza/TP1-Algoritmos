#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "procesar_nmea.h"
#include "generar_gpx.h"
#include "verificaciones_main.h"

#include "procesar_nmea.c"
#include "generar_gpx.c" // Ya se que no van estos pero sino no compila

int main(int argc, char *argv[]) {

	char nombre[100] = {0};
	int fecha;
	int mes;
	int anio;
	int dia;
	//Va en la gpx

	gga estructura;
	metadata datosusuario;
	status_t st;
	st = procesar_argumentos(argc, argv, nombre, &fecha, &mes, &anio, &dia);
	
	if (st == ST_PEDIR_AYUDA) { 
		imprimir_ayuda();
		return EXIT_FAILURE;
	}

	//VER COMO ANALIZAR LOS DISTINTOS ERRORES
	if (st != ST_OK && st != ST_PEDIR_AYUDA) {  
		imprimir_errores(st);
		return EXIT_FAILURE;
	}

	printf("%s\n", nombre);
	printf("%d\n", fecha);
	printf("%d\n", mes);
	printf("%d\n", anio);
	printf("%d\n", dia);
	
	generar_gpx(&estructura, &datosusuario);
	//llamar a funcion en procesarNMEA
	return EXIT_SUCCESS;
}
//Verifica que los argumentos procesados sean correctos.
status_t procesar_argumentos(int argc, char *argv[], char *nombre, int *fecha, int *mes, int *anio, int *dia) {

	const char *arg_validos[] = { ARG_VALIDO_AYUDA, ARG_VALIDO_AYUDA_V , 
								  ARG_VALIDO_NOMBRE, ARG_VALIDO_NOMBRE_V, 
								  ARG_VALIDO_FECHA, ARG_VALIDO_FECHA_V,
								  ARG_VALIDO_ANIO, ARG_VALIDO_ANIO_V,
								  ARG_VALIDO_MES, ARG_VALIDO_MES_V,
								  ARG_VALIDO_DIA, ARG_VALIDO_DIA_V
								}; 

	int i, j;
	status_t estado;

	if (!argv|| !nombre|| !fecha || !mes)
		return ST_ERROR_PUNTERO_NULO;
	
	//Aca pongo parametros por omision, para procesargpx
	//hacerlo en una funcion aparte que se llame cargar_argumentos_por_omision;
	strcpy(nombre, "tu mama");
	*fecha = 20181011;
	*mes = 10; 
	*anio = 2018;
	*dia = 23;

	for (i = 1; i < argc; i++) { //Despues hacer que cuando encuentre ayuda el resto lo corte
		for (j = 0; j < MAX_CANT_ARG; j++) { 
			if (strcmp(argv[i], arg_validos[j]) == 0) {
				j = j/2;
				switch (j) {
					case ARG_AYUDA: 
						return ST_PEDIR_AYUDA;
						break;
					case ARG_NOMBRE:
						//Guarda el nombre en la GPX
						i++;
						estado = validar_argumento_nombre(argv[i], nombre);
						//Tengo que verificar que todos esten bien CUIDADO
						break;
					case ARG_FECHA:
						i++; 
						estado = validar_argumento_fecha(argv[i], fecha);
						break;
					case ARG_ANIO:
						i++;
						estado = validar_argumento_anio(argv[i], anio);
						break;
					case ARG_MES:
						i++;
						estado = validar_argumento_mes(argv[i], mes);
						break;
					case ARG_DIA:
						i++;
						estado = validar_argumento_dia(argv[i], dia);
						break;
				}
				if (estado != ST_OK)
					return estado;
			} 
		}
	}

	return ST_OK;
}

void imprimir_ayuda() {
	printf("%s\n", MSJ_IMPRIMIR_AYUDA);
}


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
	}

}
