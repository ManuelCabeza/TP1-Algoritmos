#include "log.h"
#include "verificar_argumentos.h"
#include "main.h"
/*
Forma de imprimir en el LOG
año-mes-dia horas:minutos:segundos [ERROR] mensaje
año-mes-dia horas:minutos:segundos [WARN] mensaje
año-mes-dia horas:minutos:segundos [DEBUG] mensaje
*/
//VER PROCESAR_T EN PROCESAR_UBX.H esta definido
void imprimir_msj_log (status_t estado, FILE *archivo_log, gps_t *datos_satelite /*, procesar_t proceso*/) { 

	const char * msj_error[] = { MSJ_VACIO, MSJ_VACIO,
								MSJ_ERROR_PUNTERO_NULO, MSJ_ERROR_NOMBRE_INVALIDO, 
								MSJ_ERROR_PROTOCOLO,
							    MSJ_ERROR_ARCHIVO_ENTRADA, MSJ_ERROR_ARCHIVO_SALIDA,
								MSJ_ERROR_ARCHIVO_LOG, MSJ_ERROR_CANTIDAD_MSJ,
								MSJ_ERROR_CANT_ARG_INVALIDO,
								MSJ_ERROR_ARG_INVALIDO, MSJ_ERROR_LECTURA
							   }; 
	/*Tiene que tener el mismo orden de status_t para que sea un diccionario*/
/*
	const char * msj_debug[] = { MSJ_VACIO, 

							   };

	const char * msj_warn[] = {
								MSJ_WARN_ID, 
								MSJ_WARN_FIX_INVALIDO,
							   };

*/

	fprintf (archivo_log, "%d-%d-%d %d:%d:%f [ERROR] %s\n", datos_satelite->fecha.anio, 
														    datos_satelite->fecha.mes,
														    datos_satelite->fecha.dia,
														    datos_satelite->horario.hora,
														    datos_satelite->horario.minuto,
														    datos_satelite->horario.segundos,
														    msj_error[estado]
														  );
/*	fprintf (archivo_log, "%d-%d-%d %d:%d:%f [WARN] %s\n", datos_satelite->fecha.anio, 
														    datos_satelite->fecha.mes,
														    datos_satelite->fecha.dia,
														    datos_satelite->horario.hora,
														    datos_satelite->horario.minuto,
														    datos_satelite->horario.segundos,
														    msj_warn[estado]
														  );
	fprintf (archivo_log, "%d-%d-%d %d:%d:%f [DEBUG] %s\n", datos_satelite->fecha.anio, 
														    datos_satelite->fecha.mes,
														    datos_satelite->fecha.dia,
														    datos_satelite->horario.hora,
														    datos_satelite->horario.minuto,
														    datos_satelite->horario.segundos,
														    msj_debug[estado]
														  );
*/	
}


