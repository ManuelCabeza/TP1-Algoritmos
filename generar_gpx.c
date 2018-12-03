#include "generar_gpx.h"
#include "main.h"
#include "verificar_argumentos.h"

/* Esto hay que ver si se puede perto estaria bueno si se puede hacer algo asi
* Que solo se incluya el .c que se va a usar y no el otro, pero no se si se puede
* creo que no*/
#include "procesar_nmea.h"
#include "procesar_ubx.h"
//#include "procesar_ubx.c"
#include "lista.h"

void generar_gpx(gps_t *gps_ptr, metadata_t *metadata_ptr, procesar_t (*procesar) (FILE **, gps_t *), FILE *pf_in, FILE *pf_out, FILE *pf_log, int cant_datos) {
	
	procesar_t aux_p;
	Lista lista;
	size_t i = 0;
	
	if (!lista_crear(&lista)) {
		// Imprimir por log que no se pudo hacer la lista
		return;
	}
	if (!tag(MSJ_GPX_1, INICIAR_ENTER, INDENTACION_0, &pf_out)) { //NO SE, LE AGREGUE EL & PORQUE HABIA PROBLEMA 
	//CON LOS NIVELES DE PUNTERO. NO SE SI ESTA BIEN ESO. O HAY QUE SACARLE UN NIVEL AL PROTOTIPO
		imprimir_error_pf_out(&pf_log);
		return;
	}
	if (!tag(MSJ_GPX_2, INICIAR_ENTER, INDENTACION_0, &pf_out)) {
		imprimir_error_pf_out(&pf_log);
		return;
	}
	//Esta sección se ocupa de imprimir todo lo contenido en metadata
	if (!tag(TAG_METADATA, INICIAR_ENTER, INDENTACION_1, &pf_out)) {
		imprimir_error_pf_out(&pf_log);
		return;
	}	
	if (!tag(TAG_NOMBRE, INICIAR, INDENTACION_2, &pf_out)) {
		imprimir_error_pf_out(&pf_log);
		return;
	}
	if (fprintf(pf_out, "%s", metadata_ptr->nombre) < 0) {
		imprimir_error_pf_out(&pf_log);
		return;
	}
	if (!tag(TAG_NOMBRE, FINAL_ENTER, INDENTACION_0, &pf_out)) {
		imprimir_error_pf_out(&pf_log);
		return;
	}
	if (!tag(TAG_TIEMPO, INICIAR, INDENTACION_2, &pf_out)) {
		imprimir_error_pf_out(&pf_log);
		return;
	}
	
	if (fprintf( pf_out, "%04d-%02d-%02dT%02d:%02d:%02.0fZ", metadata_ptr->fecha.anio, metadata_ptr->fecha.mes, metadata_ptr->fecha.dia,
		metadata_ptr->horario.hora, metadata_ptr->horario.minuto, metadata_ptr->horario.segundos) < 0) {
		imprimir_error_pf_out(&pf_log);
		return;
	}
	
	if (!tag(TAG_TIEMPO, FINAL_ENTER, INDENTACION_0, &pf_out)) {
		imprimir_error_pf_out(&pf_log);
		return;
	}
	if (!tag(TAG_METADATA, FINAL_ENTER, INDENTACION_1, &pf_out)) {
		imprimir_error_pf_out(&pf_log);
		return;
	}
	if (!tag(TAG_TRK, INICIAR_ENTER, INDENTACION_1, &pf_out)) {
		imprimir_error_pf_out(&pf_log);
		return;
	}
	if (!tag(TAG_TRKSEG, INICIAR_ENTER, INDENTACION_2, &pf_out)) {
		imprimir_error_pf_out(&pf_log);
		return;
	}
	/*A partir de aca se empieza a imprimir cada uno de los trkpt*/
	while (((aux_p = (*procesar)(&pf_in, gps_ptr)) != PR_FIN) && (i < cant_datos)) { //Me salta error valgrind DE QUE ?
		// Si se procesar bien se carga en la lista
		if (aux_p == PR_OK) {
			puts("Esta bien");
			if (!lista_insertar_ultimo(&lista, gps_ptr, &clonar_gps)) {
				// Imprimr error de poner en la lista y hacer free etc (termina el programa no ?)
				return;
			}		
		} else { 
			puts("Imprimir error por log");
			// Imprmir el error por log o stderr
		}
		i++;		
	}
	/* Si es PR_FIN es por que la cantidad de datos a leer es mayor o igual a la 
	 * cantidad de datos reales */
	if (aux_p == PR_FIN) {
		cant_datos = cantidad_datos(&lista); 
	}
	i = 0;
	while (i < cant_datos) {
		gps_ptr = retornar_dato(&lista, i);
		if (!imprimir_gps_formato_gpx(gps_ptr, &pf_out)) {
			imprimir_error_pf_out(&pf_log);
			return;
		}
	}
	/*Se cierran las tags que se abrieron al comienzo*/
	if (!tag(TAG_TRKSEG, FINAL_ENTER, INDENTACION_2, &pf_out)) {
		imprimir_error_pf_out(&pf_log);
		return;
	}
	if (!tag(TAG_TRK, FINAL_ENTER, INDENTACION_1, &pf_out)) {
		imprimir_error_pf_out(&pf_log);
		return;
	}
	if (!tag(TAG_GPX, FINAL_ENTER, INDENTACION_0, &pf_out)) {
		imprimir_error_pf_out(&pf_log);
		return;
	}
	liberar_lista(&lista, &liberar_estructura_gps);
	
}

bool tag(char *strptr, tipo_tag tipo, size_t indentacion, FILE ** pf_out) {
	size_t i;
	for (i = 0; i < (INDENTACION_INICIAL + indentacion) * CANT_CARACTERES_INDENTACION; i++) { 
		if (fputc(CARACTER_INDENTACION, *pf_out) != CARACTER_INDENTACION)
			return false;
	}
	if (fputc(CARACTER_TAG_INICIO, *pf_out) != CARACTER_TAG_INICIO)
			return false;
	
	if ((tipo != INICIAR) && (tipo != INICIAR_ENTER)) { 
		if (fputc(CARACTER_TAG_FINALIZAR, *pf_out) != CARACTER_TAG_FINALIZAR)
			return false;
	}
	
	if (fprintf(*pf_out, "%s", strptr) < 0)
		return false;
	
	if (fputc(CARACTER_TAG_FINAL, *pf_out) != CARACTER_TAG_FINAL)
		return false;

	if ((tipo != INICIAR) && (tipo != FINAL)) { 
		if (fputc('\n', *pf_out) != '\n')
			return false;
	}
	return true;
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
	fecha->mes  = (fecha_actual->tm_mon) + AJUSTE_DE_NUM;
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
	horario->minuto = (hora -> tm_min) + AJUSTE_DE_NUM;
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
	//Si solo queda con una estructura, entonces hacer directamente free
	// ??? 
    /*if (!gps_ptr) {
        return NULL;
    }*/ //Esta demas esa vaidacidon me parece se puede free(NULL)
    free(gps_ptr);
}
// 0 si mal, !0 si bien
bool imprimir_gps_formato_gpx(gps_t *gps_ptr, FILE **pf_out) {
	int i;
	
	for (i = 0; i < INDENTACION_3 * CANT_CARACTERES_INDENTACION; i++)	{
		if (fputc(CARACTER_INDENTACION, *pf_out) != CARACTER_INDENTACION)
			return false;
	}
	if (fputc(CARACTER_TAG_INICIO, *pf_out) != CARACTER_TAG_INICIO)
			return false;
	
	if (fprintf(*pf_out, "%s %s\"%f\" %s\"%f\"", TAG_TRKPT, TAG_LATITUD, gps_ptr->latitud, TAG_LONGITUD, gps_ptr->longitud) < 0)
		return false;
	
	if (fputc(CARACTER_TAG_FINAL, *pf_out) != CARACTER_TAG_FINAL)
			return false;
	if (fputc('\n', *pf_out) != '\n')
			return false;

	if (!tag(TAG_ELEVACION, INICIAR, INDENTACION_4, pf_out))
		return false;
	
	if (fprintf(*pf_out, "%f", gps_ptr->elevacion) < 0)
		return false;
	
	if (!tag(TAG_ELEVACION, FINAL_ENTER, INDENTACION_0, pf_out))
		return false;

	if (!tag(TAG_TIEMPO, INICIAR, INDENTACION_4, pf_out))
		return false;
	
	if (fprintf(*pf_out, "%04d-%02d-%02dT%2i:%2i:%3.3fZ", gps_ptr->fecha.anio, gps_ptr->fecha.mes, gps_ptr->fecha.dia,
		gps_ptr->horario.hora, gps_ptr->horario.minuto, gps_ptr->horario.segundos) < 0)
			return false;
	
	if (!tag(TAG_TIEMPO, FINAL_ENTER, INDENTACION_0, pf_out))
		return false;
		
	if (!tag(TAG_TRKPT, FINAL_ENTER, INDENTACION_3, pf_out))	
		return false;
	return true;
}

void imprimir_error_pf_out(FILE **pf_log) {
	
	fprintf (*pf_log, "[%s] %s\n", "ERROR", "No se pudo escribir en la salida");
	return;
}
/*
void imprimir_estructura (gps_t gps) {
	printf("°°\nHora: %i, Minuto: %i, Segundo: %f\n", gps.horario.hora, gps.horario.minuto, gps.horario.segundos );
	printf("Año: %i, Mes: %i, Día: %i\n", gps.fecha.anio, gps.fecha.mes, gps.fecha.dia);
	printf("Latitud: %f\n", gps.latitud);
	printf("Longitud: %f\n", gps.longitud);
	printf("Elevacion: %f\n", gps.elevacion);
	printf("SepGeo: %f\n", gps.sep_geo);
	printf("HDop: %f\n", gps.hdop);
	printf("Calidad Fix: %i\n", gps.calidad_fix);
	printf("Cantidad satelites: %i\n°°\n", gps.cant_satelites);
}

void inicializar_estructura (gps_t *gps_ptr) {
	gps_ptr->horario.hora = gps_ptr->horario.minuto = gps_ptr->horario.segundos = 10;
	gps_ptr->fecha.anio = gps_ptr->fecha.mes = gps_ptr->fecha.dia = 10;
	gps_ptr->latitud = 10;
	gps_ptr->longitud = 10;
	gps_ptr->sep_geo = 10;
	gps_ptr->hdop = 10;
	gps_ptr->elevacion = 10;
	gps_ptr->calidad_fix = 10;
	gps_ptr->cant_satelites = 10;
}
*/
