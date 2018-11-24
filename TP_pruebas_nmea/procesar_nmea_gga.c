#include "procesar_nmea_gga.h"

procesar_t procesar_nmea_gga (gps_t * gga_ptr, char * ch_ptr, char * cadena) {

	char c; /*Variable auxiliar para no usar tolower mas de 2 veces.*/
	long suma_verificacion;
	float horario;
	float longitud;
	float latitud;

	/* Se verifica el formato del horario y se carga en la estructura con la proxima funcion*/
	if ((ch_ptr = strchr(cadena, CARACTER_SEPARACION_COMANDO)) != NULL) {
		ch_ptr++;
		if ((horario = strtof(ch_ptr, &ch_ptr)) < 0 || ((* (ch_ptr++)) != CARACTER_SEPARACION_COMANDO)) { 
			return PR_ERR;
		}
	}

	procesar_horario( &(gga_ptr->horario), horario);
	
	if ((latitud = strtof(ch_ptr, &ch_ptr)) < 0 || ((* (ch_ptr++)) != CARACTER_SEPARACION_COMANDO)) { 
		return PR_ERR;
	}

	c = tolower( *(ch_ptr++));
	if ((c != CARACTER_NORTE) && (c != CARACTER_SUR)){ 
		return PR_ERR;
	}

	/* Asigna valor de latitud a partir de formato ddmm.mmm
	 * habiendo verificado previamente que se cumple el formato */
	gga_ptr->latitud = (((int)latitud / 100) + ((latitud - 100 * ((int)latitud / 100)) / 60 )) * (c == CARACTER_SUR ? MULTIPLICADOR_SUR : MULTIPLICADOR_NORTE);
	
	if ((longitud = strtof(++ch_ptr, &ch_ptr)) < 0 || ((* (ch_ptr++)) != CARACTER_SEPARACION_COMANDO)) {
		return PR_ERR;
	}
	c = tolower( * (ch_ptr++));
	if ((c != CARACTER_ESTE) && (c != CARACTER_OESTE)) {
		return PR_ERR;
	}
	/* Asigna valor de longitud a partir de formato dddmm.mmm 
	 * habiendo verificado previamente que se cumple el formato*/
	gga_ptr->longitud = (((int)longitud / 100) + ((longitud - 100 * ((int)longitud / 100)) / 60 )) * (c == CARACTER_OESTE ? MULTIPLICADOR_OESTE : MULTIPLICADOR_ESTE);

	/*Los siguientes if verifican que los datos sean correctos (Que estén
	 * en los rangos necesarios y los carga a la estructura ) */
	if ((gga_ptr->calidad_fix = strtol(++ch_ptr, &ch_ptr, 10)) < MIN_VALOR_FIX || ((* (ch_ptr++)) != CARACTER_SEPARACION_COMANDO) || (gga_ptr->calidad_fix) > MAX_VALOR_FIX) {
		return PR_ERR;
	}
	if ((gga_ptr->cant_satelites = strtof(++ch_ptr, &ch_ptr)) < MIN_VALOR_CANT_SATELITES || ((* (ch_ptr++)) != CARACTER_SEPARACION_COMANDO) || (gga_ptr->cant_satelites > MAX_VALOR_CANT_SATELITES)) {
		return PR_ERR;
	}
	if ((gga_ptr->hdop = strtof(++ch_ptr, &ch_ptr)) < 0 || ((* (ch_ptr++)) != CARACTER_SEPARACION_COMANDO)) {
		return PR_ERR;
	}
	if ((gga_ptr->elevacion = strtof(ch_ptr, &ch_ptr)) < 0 || ((* (ch_ptr++)) != CARACTER_SEPARACION_COMANDO)) {
		return PR_ERR;
	}
	if (tolower(* ch_ptr++) != CARACTER_UNIDAD_METRO) {
		return PR_ERR;
	}
	if ((gga_ptr->sep_geo = strtof(++ch_ptr, &ch_ptr)) < 0 || ((* (ch_ptr++)) != CARACTER_SEPARACION_COMANDO)) {
		return PR_ERR;
	}
	if (tolower(* ch_ptr) != CARACTER_UNIDAD_METRO) {
		return PR_ERR;
	}
	if ((ch_ptr = strrchr(cadena, CARACTER_SUMA_VER)) == NULL) {
		return PR_ERR;
	}
	// Realizo la suma de verificaión
	suma_verificacion = strtol(++ch_ptr, NULL, 16);
	
	ch_ptr = cadena + 1; // Posiciono el puntero para hacer la suma de verificacion.
	
	if (nmea_verificar_suma(ch_ptr) != suma_verificacion) {
		return PR_ERR_SUM_VER;
	}
	return PR_OK;
}

