#include "generar_gpx.h"
#include "verificar_argumentos.h"
#include "main.h"
/* Esto hay que ver si se puede perto estaria bueno si se puede hacer algo asi
* Que solo se incluya el .c que se va a usar y no el otro, pero no se si se puede
* creo que no*/
#include "procesar_nmea.h"
//#include "procesar_ubx.c"


void generar_gpx(gps_t * gps_ptr, metadata_t * metptr, procesar_t (* procesar) (FILE **, gps_t *), FILE * pf_in, FILE * pf_out, FILE * pf_log ) {

	int i;
	procesar_t aux_p;
	/*Imprime las dos líneas por stdout, siempre las mismas*/
	tag(MSJ_GPX_1, INICIAR_ENTER, INDENTACION_0);
	tag(MSJ_GPX_2, INICIAR_ENTER, INDENTACION_0);

	/*Esta sección se ocupa de imprimir todo lo contenido en metadata*/
	tag(TAG_METADATA, INICIAR_ENTER, INDENTACION_1);
	tag(TAG_NOMBRE, INICIAR, INDENTACION_2);
	printf("%s", metptr->nombre);
	tag(TAG_NOMBRE, FINAL_ENTER, INDENTACION_0);
	tag(TAG_TIEMPO, INICIAR, INDENTACION_2);
	printf("%04d-%02d-%02dT%02d:%02d:%02.0fZ", metptr->fecha.anio, metptr->fecha.mes, metptr->fecha.dia, metptr->horario.hora, metptr->horario.minuto, metptr->horario.segundos);
	tag(TAG_TIEMPO, FINAL_ENTER, INDENTACION_0);
	tag(TAG_METADATA, FINAL_ENTER, INDENTACION_1);

	tag(TAG_TRK, INICIAR_ENTER, INDENTACION_1);
	tag(TAG_TRKSEG, INICIAR_ENTER, INDENTACION_2);
	/*A partir de aca se empieza a imprimir cada uno de los trkpt*/
	while ((aux_p = (* procesar)(&pf_in, gps_ptr)) != PR_FIN) {
		// Si se procesar bien se imprimie y se carga en la lista
		if (aux_p == PR_OK) {

			for (i = 0; i < INDENTACION_3 * CANT_CARACTERES_INDENTACION; i++)	{
				putchar(CARACTER_INDENTACION);
			}
			putchar(CARACTER_TAG_INICIO);
			printf("%s %s\"%f\" %s\"%f\"", TAG_TRKPT, TAG_LATITUD, gps_ptr->latitud, TAG_LONGITUD, gps_ptr->longitud);
			putchar(CARACTER_TAG_FINAL);
			putchar('\n');

			tag(TAG_ELEVACION, INICIAR, INDENTACION_4);
			printf("%f", gps_ptr->elevacion);
			tag(TAG_ELEVACION, FINAL_ENTER, INDENTACION_0);

			tag(TAG_TIEMPO, INICIAR, INDENTACION_4);
			printf("%04d-%02d-%02dT%2i:%2i:%3.3fZ", metptr->fecha.anio, metptr->fecha.mes, metptr->fecha.dia, gps_ptr->horario.hora, gps_ptr->horario.minuto, gps_ptr->horario.segundos);

			tag(TAG_TIEMPO, FINAL_ENTER, INDENTACION_0);

			tag(TAG_TRKPT, FINAL_ENTER, INDENTACION_3);
			// CARGAR EN LA LISTA
		} else { // Si no esat bien se imprime el error por el archivo de log o stderr
			
		}		
		
	}
	/*Se cierran las tags que se abrieron al comienzo*/
	tag(TAG_TRKSEG, FINAL_ENTER, INDENTACION_2);
	tag(TAG_TRK, FINAL_ENTER, INDENTACION_1);
	tag(TAG_GPX, FINAL_ENTER, INDENTACION_0);

}

void tag(char * strptr, tipo_tag tipo, size_t indentacion) {

	size_t i;
	for (i = 0; i < (INDENTACION_INICIAL + indentacion) * CANT_CARACTERES_INDENTACION; i++) { 
			putchar(CARACTER_INDENTACION);
	}
	putchar(CARACTER_TAG_INICIO);

	if ((tipo != INICIAR) && (tipo != INICIAR_ENTER)) { 
		putchar(CARACTER_TAG_FINALIZAR);
	}
	printf("%s", strptr);
	putchar(CARACTER_TAG_FINAL);

	if ((tipo != INICIAR) && (tipo != FINAL)) { 
		putchar('\n');
	}
}
