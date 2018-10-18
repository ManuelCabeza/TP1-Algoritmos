#include "main.h"
#include "errores.h"
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

	generar_gpx(&estructura, &datos_usuario);


	return EXIT_SUCCESS;
}





