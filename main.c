#include "main.h"
#include "verificar_argumentos.h"
#include "errores.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {

	/*metadata_t datos_usuario;*/
	status_t st;
	 
    FILE *entrada;
    FILE *salida; //Abro como archivo de escritura
    FILE *archivo_log; //idem aca

/*	cargar_nombre_por_omision(datos_usuario.nombre);*/

	st = procesar_argumentos(argc, argv, entrada, salida, archivo_log/*, &datos_usuario*/);

	if (st == ST_PEDIR_AYUDA) {
		imprimir_ayuda();
		return EXIT_SUCCESS;
	}

	if (st != ST_OK) {
		imprimir_errores_log(&st,archivo_log);
		return EXIT_FAILURE;
	}

//Para cerrar cada archivo hacer de la misma forma. Ver si crear un funcion para eso. 
	if (entrada != stdin) {
		fclose(entrada);
	}


	return EXIT_SUCCESS;
}