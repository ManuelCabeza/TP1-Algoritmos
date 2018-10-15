#ifndef GENERAR_GPX_H
#define GENERAR_GPX_H

#define MAX_LONG_NOMBRE 100

typedef struct {
	char nombre[MAX_LONG_NOMBRE];
	horario_t horario;
} metadata;


typedef enum {INICIAR, INICIAR_ENTER, FINAL, FINAL_ENTER} tipo_tag;

void generar_gpx(gga * ggaptr, metadata * metptr, fecha_t *fecha);

void tag(char * strptr, tipo_tag tipo, size_t indentacion);

#endif
