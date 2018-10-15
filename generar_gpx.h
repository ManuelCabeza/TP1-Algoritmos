#ifndef GENERAR_GPX_H
#define GENERAR_GPX_H


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
