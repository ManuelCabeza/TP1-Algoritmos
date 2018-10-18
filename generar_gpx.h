#ifndef GENERAR_GPX_H
#define GENERAR_GPX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "verificaciones_main.h"
#include "procesar_nmea.h"
#include "estructuras.h"

#define MSJ_GPX_1 "?xml version=\"1.0\" encoding=\" UTF-8\"?"
#define MSJ_GPX_2 "gpx version=\"1.1\" creator=\"95.11 TP1 - Tracker\" xmlns=\"http://www.topografix.com/GPX/1/1\""
#define CARACTER_TAG_INICIO '<'
#define CARACTER_TAG_FINAL '>'
#define CARACTER_TAG_FINALIZAR '/'
#define CARACTER_INDENTACION '\t'

#define INDENTACION_INICIAL 0
#define INDENTACION_0 0 
#define INDENTACION_1 1
#define INDENTACION_2 2
#define INDENTACION_3 3
#define INDENTACION_4 4

#define TAG_GPX "gpx"
#define TAG_TRK "trk"
#define TAG_TRKSEG "trkseg"
#define TAG_TRKPT "trkpt"
#define TAG_LATITUD "lat="
#define TAG_LONGITUD "lon="
#define TAG_ELEVACION "ele"
#define TAG_TIEMPO "time"
#define TAG_METADATA "metadata"
#define TAG_NOMBRE "name"

typedef enum {INICIAR, INICIAR_ENTER, FINAL, FINAL_ENTER} tipo_tag;

void generar_gpx(gga_t * ggaptr, metadata_t * metptr);
/* El procedimiento imprime el formato tipo GPX por stdout. (
 * Se ocupa de imprimir los valores pertinentes de los argumentos de las estructuras
 * gga_t y metadata_t. Además imprime los tags correspondientes.
 * 
 * Recibe un puntero a la estructura metadata_t y otro a gga_t.
 * No devuelve nada, solamente imprime.
*/

void tag(char * strptr, tipo_tag tipo, size_t indentacion);
/*Imprime un tag con lo que contenga el puntero a char (que se asume que no es NULL) donde el tipo de tag define como se imprime de la forma:
 * INICIAR <"string">
 * INICIAR_ENTER <"string">\n
 * FINAL </"string">
 * FINAL_ENTER </"string">\n
 * 
 * Donde los caracteres '<', '>' y '/' vienen definidos por las macros CARACTER_TAG_INICIO, CARACTER_TAG_FINAL Y CARACTER_TAG_FINALIZAR respectivamente.
 * 
 * La indentación define cuantas veces se imprime el caracter CARACTER_INDENTACION desde INDENTACION_INICIAL , si no se quiere indentar la salida del
 * gpx basta con poner los 5 macros de INDENTACION_i en 0.
 * 
 * El procedimiento recibe la indentación, un enumerativo tipp_tag y un puntero a char que contiene una cadena a imprimir en el tag.
 * No devuelve nada, ya que solamente imprime.
 * 
*/
#endif
