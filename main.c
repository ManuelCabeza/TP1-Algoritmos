#include "main.h"
#include "errores.h"
#include "verificar_argumentos.h"
#include "procesar_nmea.h"
#include "generar_gpx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int main(int argc, char *argv[]) {

	gga_t estructura;
	metadata_t datos_usuario;
	status_t st;

	cargar_fecha_por_omision(&(datos_usuario.fecha));
	cargar_nombre_por_omision(datos_usuario.nombre);
	cargar_hora_por_omision(&(datos_usuario.horario));

	st = procesar_argumentos(argc, argv, &datos_usuario);

	if (st == ST_PEDIR_AYUDA) {
		imprimir_ayuda();
		return EXIT_SUCCESS;
	}

	if (st != ST_OK) {
		imprimir_error(st);
		return EXIT_FAILURE;
	}

	generar_gpx(&estructura, &datos_usuario);

	return EXIT_SUCCESS;
}
