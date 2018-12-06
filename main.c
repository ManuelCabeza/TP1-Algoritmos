#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "procesar_nmea.h"
#include "verificar_argumentos.h"
#include "log.h"
#include "procesar_ubx.h"
#include "generar_gpx.h"

int main(int argc, char *argv[]) {

	metadata_t datos_usuario;
	status_t st;
	gps_t gps;
	procesar_t proceso = PR_OK;
	protocolo_t protocolo = PROTOCOLO_AUTO; //VER ESTO
	int longitud_lista = rand();
	
    FILE *entrada = stdin;
    FILE *salida = stdout; 
    FILE *archivo_log = stderr; 

	cargar_fecha_por_omision(&(datos_usuario.fecha));
	cargar_hora_por_omision(&(datos_usuario.horario));
	cargar_nombre_por_omision(datos_usuario.nombre);

	inicializar_estructura(&gps);

	//printf("Cantidad aleatoria: %d\n", longitud_lista);

	st = procesar_argumentos(argc, argv, &entrada, &salida, &archivo_log, &datos_usuario, &protocolo, &longitud_lista);

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
	
	if (protocolo == PROTOCOLO_NMEA) { 
		generar_gpx(&gps, &datos_usuario, &procesar_nmea, entrada, salida, archivo_log, longitud_lista, &proceso);
	}
	if (protocolo == PROTOCOLO_UBX) {
		generar_gpx(&gps, &datos_usuario, &procesar_ubx, entrada, salida, archivo_log, longitud_lista, &proceso);
	}

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
