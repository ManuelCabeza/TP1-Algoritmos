#define MAX_LONG_NOMBRE 100

typedef struct {
	char nombre[MAX_LONG_NOMBRE];
	// VER TIME.H para el tiempo
} metadata;


typedef enum {INICIAR, INICIAR_ENTER, FINAL, FINAL_ENTER} tipo_tag;

void generar_gpx(gga * ggaptr, metadata * metptr);

void tag(char * strptr, tipo_tag tipo, size_t indentacion);

