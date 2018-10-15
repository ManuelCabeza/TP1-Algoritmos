
void generar_gpx(gga * ggaptr, metadata_t * metptr) {
	
	int i;
	procesar_t nmea_aux;

	tag(MSJ_GPX_1, INICIAR_ENTER, INDENTACION_0);
	tag(MSJ_GPX_2, INICIAR_ENTER, INDENTACION_0);
	
	tag(TAG_METADATA, INICIAR_ENTER, INDENTACION_1);
	tag(TAG_NOMBRE, INICIAR, INDENTACION_2);
	printf("%s", metptr->nombre);
	tag(TAG_NOMBRE, FINAL_ENTER, INDENTACION_0);
	tag(TAG_TIEMPO, INICIAR, INDENTACION_2);
	printf("%d-%02d-%dT%02d:%02d:%02.0fZ", metptr->fecha.anio, metptr->fecha.mes, metptr->fecha.dia, metptr->horario.hora, metptr->horario.minuto, metptr->horario.segundos);
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

