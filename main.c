#include "main.h"
#include "procesar_nmea.h"
#include "verificar_argumentos.h"
#include "log.h"
#include "generar_gpx.h"
//#include "lista.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {

	metadata_t datos_usuario;
	status_t st;
	gps_t gps;
	procesar_t proceso = PR_OK;
	int numero_random = 10;
	
    FILE *entrada = stdin;
    FILE *salida = stdout; 
    FILE *archivo_log = stderr; 

	cargar_fecha_por_omision(&(datos_usuario.fecha));
	cargar_hora_por_omision(&(datos_usuario.horario));
	cargar_nombre_por_omision(datos_usuario.nombre);

	st = procesar_argumentos(argc, argv, &entrada, &salida, &archivo_log, &datos_usuario);

	if (st == ST_PEDIR_AYUDA) {
		imprimir_ayuda(stdout); // ver si tambien lo quiere por salida 		
		cerrar_archivos(entrada, salida, archivo_log);
		return EXIT_SUCCESS;
	}	

	if (st != ST_OK) {
		imprimir_msj_errores_log(&st, archivo_log, &datos_usuario);
		cerrar_archivos(entrada, salida, archivo_log);
		return EXIT_FAILURE;
	}

	generar_gpx(&gps, &datos_usuario, &procesar_ubx, entrada, salida, archivo_log, numero_random, &proceso);
//	if (proceso != PR_OK) {
//		imprimir_msj_warn_log(&proceso, archivo_log, &gps);
//	}


	cerrar_archivos(entrada, salida, archivo_log);
	
	return EXIT_SUCCESS;
}

void cerrar_archivos(FILE *entrada, FILE *salida, FILE *archivo_log) {

	if (entrada != stdin && entrada != NULL) {
		fclose(entrada);
	}
	if (salida != stdout && salida != NULL) {
		fclose(salida);
	}
	if (archivo_log != stderr && archivo_log != NULL) {
		fclose(archivo_log);
	}

}
