#ifndef GENERAR_GPX_H
#define GENERAR_GPX_H


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


/* Esta se define de vardad aca
#define MAX_LONG_NOMBRE 100

typedef struct {
	char nombre[MAX_LONG_NOMBRE];
	horario_t horario;
	fecha_t fecha;
} metadata;
*/

typedef enum {INICIAR, INICIAR_ENTER, FINAL, FINAL_ENTER} tipo_tag;

void generar_gpx(gga * ggaptr, metadata * metptr);

void tag(char * strptr, tipo_tag tipo, size_t indentacion);

#endif
