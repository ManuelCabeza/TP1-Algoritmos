#include "main.h"
#include "verificaciones_main.h"
#include "procesar_nmea.h"
#include "generar_gpx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int main(int argc, char *argv[]) {

	gga estructura;
	metadata_t datos_usuario; 
	status_t st;

	cargar_fecha_por_omision(&datos_usuario);
	cargar_nombre_por_omision(&datos_usuario);
	cargar_hora_por_omision(&datos_usuario);

	st = procesar_argumentos(argc, argv, &datos_usuario);
	
	if (st == ST_PEDIR_AYUDA) { 
		imprimir_ayuda();
		return EXIT_FAILURE;
	}

	if (st != ST_OK && st != ST_PEDIR_AYUDA) {  
		imprimir_errores(st);
		return EXIT_FAILURE;
	}

/*	
	printf("nombre: %s\n", datos_usuario.nombre);
	printf("fecha: %d\n", fecha);
	printf("dia: %d\n", datos_usuario.fecha.dia);
	printf("mes: %d\n", datos_usuario.fecha.mes);
	printf("año: %d\n", datos_usuario.fecha.anio);


	partir_fecha(&fecha, &datos_usuario);
	printf("La estructura queda:\n");
	printf("dia: %d\n", datos_usuario.fecha.dia);
	printf("mes: %d\n", datos_usuario.fecha.mes);	
	printf("anio: %d\n", datos_usuario.fecha.anio);
*/	
	generar_gpx(&estructura, &datos_usuario);
/*
	printf("hora: %f\n", datos_usuario.horario.segundos);
	printf("Minuto: %d\n", datos_usuario.horario.minuto);
	printf("dia: %d\n", datos_usuario.horario.hora);
*/
	return EXIT_SUCCESS;
}
//Verifica que los argumentos procesados sean correctos.
status_t procesar_argumentos(int argc, char * argv[], metadata_t * datos_usuario) {

	
	const char * arg_validos[] = { ARG_VALIDO_AYUDA, ARG_VALIDO_AYUDA_V , 
								   ARG_VALIDO_NOMBRE, ARG_VALIDO_NOMBRE_V, 
								   ARG_VALIDO_FECHA, ARG_VALIDO_FECHA_V,
								   ARG_VALIDO_ANIO, ARG_VALIDO_ANIO_V,
								   ARG_VALIDO_MES, ARG_VALIDO_MES_V,
								   ARG_VALIDO_DIA, ARG_VALIDO_DIA_V
						          }; 

	int fecha = 0;
	int i, j;
	status_t estado;
	bool esta_fecha; // La uso como bandera indicadora para ver si esta el argumeto -f o --format
	
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
						if (esta_fecha) // Si fecha estan indicada como true 
							break;
						estado = validar_argumento_anio(argv[i], &(datos_usuario->fecha.anio));
						break;
					case ARG_MES:
						i++;
						if (esta_fecha)
							break;
						estado = validar_argumento_mes(argv[i],  &(datos_usuario->fecha.mes));
						break;
					case ARG_DIA:
						i++;
						if (esta_fecha)
							break;
						estado = validar_argumento_dia(argv[i],  &(datos_usuario->fecha.dia));
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

