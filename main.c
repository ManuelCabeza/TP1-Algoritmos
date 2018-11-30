#include "main.h"
#include "verificar_argumentos.h"
#include "errores.h"
#include "generar_gpx.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void cerrar_archivos(FILE *pf_in, FILE *pf_out, FILE *pf_log);


int main(int argc, char *argv[]) {

	/*metadata_t datos_usuario;*/
	status_t st;
	FILE *pf_in;
	gps_t gps;
	metadata_t metadata;
	/*
    FILE *pf_in = stdin;
    FILE *pf_out = stdout; //Abro como archivo de escritura
    FILE *pf_log = stderr; //idem aca
	*/
	/*	cargar_nombre_por_omision(datos_usuario.nombre);*/

	//st = procesar_argumentos(argc, argv, &pf_in, &pf_out, &pf_log/*, &datos_usuario*/);
	pf_in = fopen( "prueba_zda.txt", "rt");
	
	generar_gpx(&gps, &metadata, &procesar_nmea, pf_in, stdout, stderr);
	/*
	if (st == ST_PEDIR_AYUDA) {
		//imprimir_ayuda(pf_out); //ACA el argumento de pf_out no estaba inicializado. COMO SOLUCIONARLO?		
		cerrar_archivos(pf_in, pf_out, pf_log);
		return EXIT_SUCCESS;
	}
	
	
	if (st != ST_OK) {
		//imprimir_msj_log(st, pf_log);
		cerrar_archivos(pf_in, pf_out, pf_log);
		return EXIT_FAILURE;
	}

	cerrar_archivos(pf_in, pf_out, pf_log);
	*/
	return EXIT_SUCCESS;
}


void cerrar_archivos(FILE *pf_in, FILE *pf_out, FILE *pf_log) {

	if (pf_in != stdin && pf_in != NULL) {
		fclose(pf_in);
	}
	if (pf_out != stdout && pf_out != NULL) {
		fclose(pf_out);
	}
	if (pf_log != stderr && pf_log != NULL) {
		fclose(pf_log);
	}

}
