#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "verificaciones_main.h"

int main(int argc, char *argv[]) {

	char nombre[100] = {0};
	int fecha;
	//Va en la gpx
	
	gga estructura;
	metadata datosusuario;
	status_t st;
	st = procesar_argumentos(argc, argv, nombre, &fecha);
	
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

	generar_gpx(&estructura, &datosusuario);

	return EXIT_SUCCESS;
}
//Verifica que los argumentos procesados sean correctos.
status_t procesar_argumentos(int argc, char *argv[], char *nombre, int *fecha) {

	const char *arg_validos[] = { ARG_VALIDO_AYUDA, ARG_VALIDO_AYUDA_V , 
								  ARG_VALIDO_NOMBRE, ARG_VALIDO_NOMBRE_V, 
								  ARG_VALIDO_FECHA, ARG_VALIDO_FECHA_V,
								  ARG_VALIDO_ANIO, ARG_VALIDO_ANIO_V,
								  ARG_VALIDO_MES, ARG_VALIDO_MES_V,
								  ARG_VALIDO_DIA, ARG_VALIDO_DIA_V
								}; 

	int i, j;
	//char *perr = NULL;

	if (nombre == NULL|| !argv|| !nombre|| !fecha)
		return ST_ERROR_PUNTERO_NULO;
	
	//Aca pongo parametros por omision, para procesargpx
	//hacerlo en una funcion aparte que se llame cargar_argumentos_por_omision;
	strcpy(nombre, "tu mama");
	*fecha = 20181011;

	for (i = 1; i < argc ; i++) {
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
						//validar_argumento_nombre(argv[i], nombre);
						//Tengo que verificar que todos esten bien CUIDADO
						break;
					case ARG_FECHA:
						i++; 
						//validar_argumento_fecha(argv[i], fecha);
						break;
					case ARG_ANIO:
						break;
					case ARG_MES:
						break;
					case ARG_DIA:
						break;
				}

			} 
				//break; //Ya encontre lo que buscaba ya que j es el argumento
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

		case ST_ERROR_SEGUNDO_INVALIDO:
			fprintf(stderr, "%s : %s\n", MSJ_ERROR_PREFIJO, MSJ_ERROR_SEGUNDO_INVALIDO);
			break;
		case ST_ERROR_MINUTO_INVALIDO:
			fprintf(stderr, "%s : %s\n", MSJ_ERROR_PREFIJO, MSJ_ERROR_MINUTO_INVALIDO);
			break;
		case ST_ERROR_HORA_INVALIDA:
			fprintf(stderr, "%s : %s\n", MSJ_ERROR_PREFIJO, MSJ_ERROR_HORA_INVALIDA);
			break;
			
		case ST_PEDIR_AYUDA:
			break;

	}

}
