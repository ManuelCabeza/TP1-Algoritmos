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

#define CANT_MAX 150

void generar_gpx(gga * ggaptr, metadata * metptr) {
	
//TEMPORALMENTE VA A ESTAR ESTO	
    char aux[CANT_MAX];
    time_t tiempo;
    struct tm *fecha; 
    tiempo = time(NULL); 
    fecha = localtime(&tiempo);


	int i;
	procesar_t nmea_aux;

	tag(MSJ_GPX_1, INICIAR_ENTER, INDENTACION_0);
	tag(MSJ_GPX_2, INICIAR_ENTER, INDENTACION_0);
	
	tag(TAG_METADATA, INICIAR_ENTER, INDENTACION_1);
	tag(TAG_NOMBRE, INICIAR, INDENTACION_2);
	printf("%s", metptr->nombre);
	tag(TAG_NOMBRE, FINAL_ENTER, INDENTACION_0);
	tag(TAG_TIEMPO, INICIAR, INDENTACION_2);


	//ANALIZAR CCON PROFUNDIDAD
	strftime(aux,CANT_MAX,"%Y-%m-%dT%H:%M:%SZ", fecha);
    //printf("%s", aux);
	printf("%d-%02d-%dT%2i:%2i:%3.3fZ", metptr->fecha.anio, metptr->fecha.mes, metptr->fecha.dia, ggaptr->horario.hora, ggaptr->horario.minuto, ggaptr->horario.segundos);
	//printf("%s", metptr->nombre); //ACA TENGO QUE PONER EL TIEMPO
	
	
	tag(TAG_TIEMPO, FINAL_ENTER, INDENTACION_0);
	tag(TAG_METADATA, FINAL_ENTER, INDENTACION_1);
	
	tag(TAG_TRK, INICIAR_ENTER, INDENTACION_1);
	tag(TAG_TRKSEG, INICIAR_ENTER, INDENTACION_2);
	
	while ((nmea_aux = procesar_nmea(ggaptr)) != PR_FIN) {
		if (nmea_aux != PR_ERR) {
			
			for (i = 0; i < INDENTACION_3; i++)
				putchar(CARACTER_INDENTACION);
				
			putchar(CARACTER_TAG_INICIO);
			printf("%s %s\"%f\" %s\"%f\"", TAG_TRKPT, TAG_LATITUD, ggaptr->latitud, TAG_LONGITUD, ggaptr->longitud);
			putchar(CARACTER_TAG_FINAL);
			putchar('\n');
			
			tag(TAG_ELEVACION, INICIAR, INDENTACION_4);
			printf("%f", ggaptr->elevacion);
			tag(TAG_ELEVACION, FINAL_ENTER, INDENTACION_0);
			
			tag(TAG_TIEMPO, INICIAR, INDENTACION_4);
			// Analizar como imprimir por defecto si fecha esta o no. (- f)
			//ahora pienso como si no estuviera
			printf("%d-%02d-%dT%2i:%2i:%3.3fZ", metptr->fecha.anio, metptr->fecha.mes, metptr->fecha.dia, ggaptr->horario.hora, ggaptr->horario.minuto, ggaptr->horario.segundos);
			
			tag(TAG_TIEMPO, FINAL_ENTER, INDENTACION_0);
			
			tag(TAG_TRKPT, FINAL_ENTER, INDENTACION_3);
		}
	}
	
	tag(TAG_TRKSEG, FINAL_ENTER, INDENTACION_2);
	tag(TAG_TRK, FINAL_ENTER, INDENTACION_1);
	tag(TAG_GPX, FINAL_ENTER, INDENTACION_0);
	
}


// Imprime una tag, la empieza si recibe un uno y la termina con un 0;
void tag(char * strptr, tipo_tag tipo, size_t indentacion) {
	
	size_t i;
	
	for (i = 0; i < INDENTACION_INICIAL + indentacion; i++)
			putchar(CARACTER_INDENTACION);
			
	putchar(CARACTER_TAG_INICIO);
	
	if ((tipo != INICIAR) && (tipo != INICIAR_ENTER))
		putchar(CARACTER_TAG_FINALIZAR);
			
	printf("%s", strptr);
	putchar(CARACTER_TAG_FINAL);
	
	if ((tipo != INICIAR) && (tipo != FINAL))
		putchar('\n');
}

