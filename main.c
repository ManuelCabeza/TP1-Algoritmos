#include "main.h"
#include "verificar_argumentos.h"
#include "errores.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void cerrar_archivos(FILE *entrada, FILE *salida, FILE *archivo_log);


int main(int argc, char *argv[]) {

	/*metadata_t datos_usuario;*/
	status_t st;
	 
    FILE *entrada = stdin;
    FILE *salida = stdout; //Abro como archivo de escritura
    FILE *archivo_log = stderr; //idem aca

/*	cargar_nombre_por_omision(datos_usuario.nombre);*/

	st = procesar_argumentos(argc, argv, &entrada, &salida, &archivo_log/*, &datos_usuario*/);

	if (st == ST_PEDIR_AYUDA) {
		imprimir_ayuda(salida); //ACA el argumento de salida no estaba inicializado. COMO SOLUCIONARLO?		
		cerrar_archivos(entrada, salida, archivo_log);
		return EXIT_SUCCESS;
	}

	if (st != ST_OK) {
		imprimir_msj_log(st, archivo_log);
		cerrar_archivos(entrada, salida, archivo_log);
		return EXIT_FAILURE;
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
