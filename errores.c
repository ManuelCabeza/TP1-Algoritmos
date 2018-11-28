#include "errores.h"
#include "verificar_argumentos.h"

/*
Forma de imprimir en el LOG

año-mes-dia horas:minutos:segundos [ERROR] mensaje
año-mes-dia horas:minutos:segundos [WARN] mensaje
año-mes-dia horas:minutos:segundos [DEBUG] mensaje
*/

//LOGS es lo mismo para ver stdout


//PARA MODIFICAR UNA ESTRUCTURA NO HACE FALTA PASAR DOS NIVELES DE PUNTERO
void imprimir_errores_log (status_t *estado, FILE *archivo_log) { //Pasa una estructura

	const char * msj_error[] = { MSJ_VACIO, MSJ_VACIO,
								MSJ_ERROR_PUNTERO_NULO, MSJ_ERROR_NOMBRE_INVALIDO, 
								MSJ_ERROR_PROTOCOLO,
							    MSJ_ERROR_ARCHIVO_ENTRADA, MSJ_ERROR_ARCHIVO_SALIDA,
								MSJ_ERROR_ARCHIVO_LOG, MSJ_ERROR_CANTIDAD_MSJ,
								MSJ_ERROR_ARG_INVALIDO, MSJ_ERROR_LECTURA
							   }; 
/*Tiene que tener el mismo orden de status_t para que sea un diccionario*/

	if (archivo_log == stderr) { 
	fprintf(stderr, "%s : %s\n", MSJ_ERROR_PREFIJO, msj_error[*estado]);
	}

	fprintf(archivo_log, "%s : %s\n", MSJ_ERROR_PREFIJO, msj_error[*estado]);

}

/*
status_t procesar_logs(logs_t *log, file **archivo_log, //las estructuras ) {

    fprintf(stdout, "%d%d\n", 7, 34) // o nombre del archivo
}

*/

