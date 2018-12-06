#include "log.h"

#include <stdio.h>

#include "verificar_argumentos.h"


void imprimir_msj_errores_log (status_t *mensaje, FILE *archivo_log, metadata_t *datos_usuario) { 

	const char * msj_error[] = { MSJ_VACIO, MSJ_VACIO,
								MSJ_ERROR_PUNTERO_NULO, MSJ_ERROR_NOMBRE_INVALIDO, 
								MSJ_ERROR_PROTOCOLO,
							    MSJ_ERROR_ARCHIVO_ENTRADA, MSJ_ERROR_ARCHIVO_SALIDA,
								MSJ_ERROR_ARCHIVO_LOG, MSJ_ERROR_CANTIDAD_MSJ,
								MSJ_ERROR_CANT_ARG_INVALIDO,
								MSJ_ERROR_ARG_INVALIDO, MSJ_ERROR_LECTURA,
								MSJ_ERROR_LISTA_CREAR, MSJ_ERROR_LISTA_CARGAR
							   }; 
	/*Tiene que tener el mismo orden de status_t para que sea un diccionario*/
	fprintf (archivo_log, "%04d-%02d-%02d %02d:%02d:%.0f [%s] %s\n", 
													datos_usuario->fecha.anio, 
													datos_usuario->fecha.mes,
													datos_usuario->fecha.dia,
													datos_usuario->horario.hora,
													datos_usuario->horario.minuto,
													datos_usuario->horario.segundos,
													MSJ_ERROR_TIPO,
													msj_error[*mensaje]
													);
}

void imprimir_msj_warn_log (procesar_t *mensaje, FILE *archivo_log, metadata_t *datos_usuario) { 

	const char * msj_warn[] = { MSJ_VACIO, MSJ_FIN, MSJ_WARN_CARACTER_NO_INICIAL,
								MSJ_ERROR, MSJ_WARN_SENTENCIA_INVALIDA, 
								MSJ_WARN_CARACTER_ESTADO, MSJ_WARN_HORARIO, 
								MSJ_WARN_CARACTER_LATITUD, MSJ_WARN_LATITUD,
								MSJ_WARN_CARACTER_LONGITUD, MSJ_WARN_LONGITUD,
								MSJ_WARN_FIX_INVALIDO, MSJ_WARN_CANT_SATELITES, 
								MSJ_WARN_ELEVACION, MSJ_WARN_CARACTER_METRO,
								MSJ_WARN_HDOP, MSJ_WARN_SEPARACION_GEOGRAFICA, MSJ_WARN_FECHA,
								MSJ_WARN_MES, MSJ_WARN_ANIO, MSJ_WARN_DIA, MSJ_WARN_ZONA_HORARIA,
								MSJ_WARN_ARCHIVO, MSJ_WARN_PTR_NULL, MSJ_WARN_CLASE, 
								MSJ_WARN_ID, MSJ_WARN_LARGO, MSJ_WARN_SUMA_VERIFICACION, MSJ_WARN_VAL_FLAGS,
								MSJ_WARN_VAL_FIX, MSJ_VACIO, MSJ_VACIO, MSJ_WARN_SEGUNDO, MSJ_WARN_MINUTO
							   };

		fprintf (archivo_log, "%04d-%02d-%02d %02d:%02d:%.0f [%s] %s\n", 
													datos_usuario->fecha.anio, 
													datos_usuario->fecha.mes,
													datos_usuario->fecha.dia,
													datos_usuario->horario.hora,
													datos_usuario->horario.minuto,
													datos_usuario->horario.segundos,
													MSJ_WARN_TIPO,
													msj_warn[*mensaje]
													);
}


/*	
void imprimir_msj_debug_log (status_t *mensaje, FILE *archivo_log, metadata_t *datos_usuario) { 

	const char * msj_debug[] = { MSJ_VACIO, 
							   };
	
	fprintf (archivo_log, "%04d-%02d-%02d %02d:%02d:%f [DEBUG] %s\n", datos_usuario->fecha.anio, 
														    datos_usuario->fecha.mes,
														    datos_usuario->fecha.dia,
														    datos_usuario->horario.hora,
														    datos_usuario->horario.minuto,
														    datos_usuario->horario.segundos,
														    msj_debug[estado]
														  );
*/	



