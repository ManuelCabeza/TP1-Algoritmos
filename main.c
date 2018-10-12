#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "verificaciones_main.h"


//No se me ocurren nombres de variables mas representativos.

#define ARG_VALIDO_AYUDA "-h"
#define ARG_VALIDO_AYUDA_V "--help"
#define ARG_VALIDO_NOMBRE "-n"
#define ARG_VALIDO_NOMBRE_V "--name"
#define ARG_VALIDO_FECHA "-f" //Si no se indica fecha se toma la del sistema
#define ARG_VALIDO_FECHA_V "--format"
#define ARG_VALIDO_ANIO "-Y"
#define ARG_VALIDO_ANIO_V "--year"
#define ARG_VALIDO_MES "-m"
#define ARG_VALIDO_MES_V "--month"
#define ARG_VALIDO_DIA "-d"
#define ARG_VALIDO_DIA_V "--day"

#define MAX_CANT_ARG 12 //num del enum arg_t
#define MSJ_IMPRIMIR_AYUDA "Ayuda"


int main(int argc, char *argv[]) {

	char nombre[100] = {0};
	int fecha;
	//Va en la estructura

	status_t st;

	
	st = procesar_argumentos(argc, argv, nombre, &fecha);
	
	if (st == ST_PEDIR_AYUDA)
		imprimir_ayuda(ST_PEDIR_AYUDA);

	//VER COMO ANALIZAR LOS DISTINTOS ERRORES
	if (st != ST_OK && st != ST_PEDIR_AYUDA) {  
		fprintf(stderr, "%s\n", MSJ_ERROR_PREFIJO);
		return EXIT_FAILURE;
	}


	
	//llamar a funcion en procesarNMEA
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
	char *perr = NULL;

	if (nombre == NULL|| !argv||!nombre|| !fecha)
		return ST_ERROR_PUNTERO_NULO;
	
	//Aca pongo parametros por omision, para cuando tenga la estructura
	//hacerlo en una funcion aparte que se llame cargar_argumentos_por_omision;
	strcpy(nombre, "tu mama");
	*fecha = 20181011;
	


	for (i = 1; i < argc ; i++) {
		for (j = 0; j < MAX_CANT_ARG; j++) {
			if (!strcmp(argv[i], arg_validos[j]))
				//ACA EL SWITCH
				break; //Ya encontre lo que buscaba ya que j es el argumento
		}
	}

	switch(j) {
		case ARG_AYUDA:ARG_AYUDA_V: //LE DIGO AL MAIN QUE ME LLEGO UNA AYUDA
			return ST_PEDIR_AYUDA;
			break;
		case ARG_NOMBRE: ARG_NOMBRE_V:
			//Guarda el nombre en la estructura.
			i++;
			strcpy(nombre, argv[i]);
			return ST_OK; //Tengo que verificar que todos esten bien CUIDADO!
			break;
		case ARG_FECHA: ARG_FECHA_V:
			i++; 
			*fecha = strtol(argv[i],&perr,10);
			if (*perr != '\0' || *fecha < 0)
				return ST_ERROR_FECHA_INVALIDA;
			return ST_OK;
			break;
		case ARG_ANIO: ARG_ANIO_V:
			break;
		case ARG_MES: ARG_MES_V:
			break;
		case ARG_DIA: ARG_DIA_V:
			break;

	}

	return ST_OK;

}

void imprimir_ayuda() {
	printf("%s\n", MSJ_IMPRIMIR_AYUDA);
}
