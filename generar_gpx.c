#include "generar_gpx.h"
#include "main.h"
#include "verificar_argumentos.h"

#include "procesar_nmea.h"
#include "procesar_ubx.h"
#include "log.h"
#include "lista.h"

void generar_gpx(gps_t *gps_ptr, metadata_t *metadata_ptr, procesar_t (*procesar) (FILE **, gps_t *), FILE *pf_in, FILE *pf_out, FILE *pf_log, int cant_datos, procesar_t *proceso) {
	
	Lista lista;
	size_t i = 0;
	
	if (!gps_ptr || !metadata_ptr || !procesar || !pf_in || !pf_out || !pf_log || !proceso) {
		*proceso = PR_ERR_PTR_NULL;
		return;
	}
	
	if (!lista_crear(&lista)) {
		// Imprimir por log que no se pudo hacer la lista
		//imprimir_msj_log(proceso, pf_log, gps_ptr);
		return;
	}
	
	tag(MSJ_GPX_1, INICIAR_ENTER, INDENTACION_0, pf_out);
	
	tag(MSJ_GPX_2, INICIAR_ENTER, INDENTACION_0, pf_out);

	//Esta sección se ocupa de imprimir todo lo contenido en metadata
	tag(TAG_METADATA, INICIAR_ENTER, INDENTACION_1, pf_out);
	
	tag(TAG_NOMBRE, INICIAR, INDENTACION_2, pf_out);

	fprintf(pf_out, "%s", metadata_ptr->nombre);

	tag(TAG_NOMBRE, FINAL_ENTER, INDENTACION_0, pf_out);

	tag(TAG_TIEMPO, INICIAR, INDENTACION_2, pf_out);
	
	fprintf( pf_out, "%04d-%02d-%02dT%02d:%02d:%02.0fZ", metadata_ptr->fecha.anio, 
		metadata_ptr->fecha.mes, metadata_ptr->fecha.dia, metadata_ptr->horario.hora, 
		metadata_ptr->horario.minuto, metadata_ptr->horario.segundos);
	
	tag(TAG_TIEMPO, FINAL_ENTER, INDENTACION_0, pf_out);
	
	tag(TAG_METADATA, FINAL_ENTER, INDENTACION_1, pf_out);
	
	tag(TAG_TRK, INICIAR_ENTER, INDENTACION_1, pf_out);
	
	tag(TAG_TRKSEG, INICIAR_ENTER, INDENTACION_2, pf_out);
	
	/*A partir de aca se empieza a imprimir cada uno de los trkpt*/
	while (((*proceso = (*procesar)(&pf_in, gps_ptr)) != PR_FIN) && (i < cant_datos)) { 
		// Si se procesar bien se carga en la lista
		printf("PROCESO= %i\n", *proceso);
		if (*proceso == PR_OK) {
			if (!lista_insertar_ultimo(&lista, gps_ptr, &clonar_gps)) {
				// Imprimr error de poner en la lista y hacer free etc (termina el programa no ?)
				return;
			}	
			i++;	
		} else { 
			printf ("El valor de procesar_t %d\n", *proceso);
			imprimir_msj_warn_log(proceso, pf_log, metadata_ptr);
			puts("Imprimir error por log");
		}
	}
	/* Si es PR_FIN es por que la cantidad de datos a leer es mayor o igual a la 
	 * cantidad de datos reales */

	if (*proceso == PR_FIN) {
		cant_datos = i; 
	}
	
	for (i = 0; i < cant_datos; i++) {
		gps_ptr = retornar_dato(&lista, i);
		imprimir_gps_formato_gpx(gps_ptr, pf_out);
	}
	liberar_lista(&lista, &liberar_estructura_gps);
	
	/*Se cierran las tags que se abrieron al comienzo*/
	tag(TAG_TRKSEG, FINAL_ENTER, INDENTACION_2, pf_out);
	
	tag(TAG_TRK, FINAL_ENTER, INDENTACION_1, pf_out);
	
	tag(TAG_GPX, FINAL_ENTER, INDENTACION_0, pf_out);
	
	
}

//saco un nivel de puntero para la impresion Antes. FILE **pf_out
void tag(char *strptr, tipo_tag tipo, size_t indentacion, FILE *pf_out) {
	size_t i;
	for (i = 0; i < (INDENTACION_INICIAL + indentacion) * CANT_CARACTERES_INDENTACION; i++) 
		fputc(CARACTER_INDENTACION, pf_out);
		
	fputc(CARACTER_TAG_INICIO, pf_out);
	
	if ((tipo != INICIAR) && (tipo != INICIAR_ENTER))
		fputc(CARACTER_TAG_FINALIZAR, pf_out);
	
	fprintf(pf_out, "%s", strptr);
	
	fputc(CARACTER_TAG_FINAL, pf_out);

	if ((tipo != INICIAR) && (tipo != FINAL))
		fputc('\n', pf_out);
}

/*Por ahora aca, si lo queres cambiar hacelo sin problema.*/
bool cargar_fecha_por_omision(fecha_t *fecha) {

    time_t tiempo;
    struct tm * fecha_actual;
    tiempo = time(NULL);
    fecha_actual = localtime(&tiempo);

	if(!fecha) {
		return false;
	}
	fecha->dia  = fecha_actual->tm_mday;
	fecha->mes  = (fecha_actual->tm_mon) + AJUSTE_MES;
	fecha->anio = (fecha_actual->tm_year) + ANIO_DE_LINUX;

	return true;
}

bool cargar_hora_por_omision (horario_t *horario) {

	time_t tiempo;
    struct tm *hora;
    tiempo = time(NULL);
    hora = localtime(&tiempo);

	if(!horario) {
		return false;
	}
	horario->segundos = (float)hora -> tm_sec;
	horario->minuto = (hora -> tm_min);
	horario->hora = (hora ->tm_hour);

	return true;
}

void * clonar_gps(void *llegada) {
    gps_t *aux;

    if (!llegada) {
        return NULL;
    }

    aux = (gps_t *)calloc(1, sizeof(gps_t)); // Podria directamente crear el arreglo de estructuras.
    if (aux == NULL) {
        return NULL;
    }
    *aux = *((gps_t *)llegada); //COPIA LAS ESTRUCTURAS ES MAGICO!

    return aux;
}

void liberar_estructura_gps (void *gps_ptr) { 
    free(gps_ptr);
}


// 0 si mal, !0 si bien
void imprimir_gps_formato_gpx(gps_t *gps_ptr, FILE *pf_out) {
	int i;
	
	for (i = 0; i < INDENTACION_3 * CANT_CARACTERES_INDENTACION; i++)
		fputc(CARACTER_INDENTACION, pf_out);
		
	fputc(CARACTER_TAG_INICIO, pf_out);
	
	fprintf(pf_out, "%s %s\"%f\" %s\"%f\"", TAG_TRKPT, TAG_LATITUD, gps_ptr->latitud, TAG_LONGITUD, gps_ptr->longitud);
	
	fputc(CARACTER_TAG_FINAL, pf_out);
	
	fputc('\n', pf_out);

	tag(TAG_ELEVACION, INICIAR, INDENTACION_4, pf_out);
	
	fprintf(pf_out, "%f", gps_ptr->elevacion);
	
	tag(TAG_ELEVACION, FINAL_ENTER, INDENTACION_0, pf_out);

	tag(TAG_TIEMPO, INICIAR, INDENTACION_4, pf_out);

	fprintf(pf_out, "%04d-%02d-%02dT%2i:%2i:%3.3fZ", gps_ptr->fecha.anio, gps_ptr->fecha.mes, gps_ptr->fecha.dia,
		gps_ptr->horario.hora, gps_ptr->horario.minuto, gps_ptr->horario.segundos);
	
	tag(TAG_TIEMPO, FINAL_ENTER, INDENTACION_0, pf_out);
		
	tag(TAG_TRKPT, FINAL_ENTER, INDENTACION_3, pf_out);

}

