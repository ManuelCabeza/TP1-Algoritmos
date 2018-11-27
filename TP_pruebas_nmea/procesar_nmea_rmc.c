#include "procesar_nmea_rmc.h"
/* $GPRMC,hhmmss.sss,A,ddmm.mmm,S,dddmmm.mmm,E,dddddd.d,ddd.d,ddmmyy,ddd.d,W*cc
 * _variaciones_   V   lat    N    long    W 
 * 
*/

procesar_t procesar_nmea_rmc(gps_t * zda_ptr, char * ch_ptr, char * cadena) {
	
	long suma_verificacion;
	long fecha;
	float horario;
	float longitud, latitud;
	char c;
	
	
	if ((ch_ptr = strchr(cadena, CARACTER_SEPARACION_COMANDO)) != NULL) {
		ch_ptr++;
		if ((horario = strtof(ch_ptr, &ch_ptr)) < 0 || ((* (ch_ptr++)) != CARACTER_SEPARACION_COMANDO)) { 
			return PR_ERR;
		}
	}
	procesar_horario(&(zda_ptr->horario), horario);
	
	c = tolower( *(ch_ptr++));
	if ((c != CARACTER_STATUS_VOID) && (c != CARACTER_STATUS_ACTIVO))
		return PR_ERR_CAR_STATUS;
	
	// Latitud ddmm.mmm
	if ((latitud = strtof(ch_ptr++, &ch_ptr)) < 0 || ((* (ch_ptr++)) != CARACTER_SEPARACION_COMANDO)) { 
		return PR_ERR;
	}
	
	c = tolower( *(ch_ptr++));
	if ((c != CARACTER_NORTE) && (c != CARACTER_SUR)){ 
		return PR_ERR;
	}
	
	zda_ptr->latitud = (((int)latitud / 100) + ((latitud - 100 * ((int)latitud / 100)) / 60 )) * (c == CARACTER_SUR ? MULTIPLICADOR_SUR : MULTIPLICADOR_NORTE);

	// Longitud dddmm.mmm
	if ((longitud = strtof(ch_ptr++, &ch_ptr)) < 0 || ((* (ch_ptr++)) != CARACTER_SEPARACION_COMANDO)) { 
		return PR_ERR;
	}
	
	c = tolower( *(ch_ptr++));
	if ((c != CARACTER_ESTE) && (c != CARACTER_OESTE)){ 
		return PR_ERR;
	}
	
	zda_ptr->longitud = (((int)longitud / 100) + ((longitud - 100 * ((int)longitud / 100)) / 60 )) * (c == CARACTER_OESTE ? MULTIPLICADOR_OESTE : MULTIPLICADOR_ESTE);
	
	strtof(++ch_ptr, &ch_ptr); // La velocidad no se verifica o se carga
	if ((*ch_ptr) != CARACTER_SEPARACION_COMANDO) { 
		return PR_ERR;
	}
	
	strtof(++ch_ptr, &ch_ptr); // La velocidad no se verifica o se carga
	if (*(ch_ptr) != CARACTER_SEPARACION_COMANDO) { 
		return PR_ERR;
	}
	
	fecha = strtol(++ch_ptr, &ch_ptr, 10);
	
	procesar_fecha(&(zda_ptr->fecha), fecha);
	
	if (*(ch_ptr) != CARACTER_SEPARACION_COMANDO) { 
		return PR_ERR;
	}
	
	strtol(++ch_ptr, &ch_ptr, 10); // La desviación magnetica no se verifica
	if (*(ch_ptr) != CARACTER_SEPARACION_COMANDO) { 
		return PR_ERR;
	}
	// Solo se verfica que la unidad magnetica sea 'w'
	c = tolower(*(++ch_ptr)); 
	if (c != CARACTER_UNIDAD_MAGNETICA)
		return PR_ERR;
	
	
	if (!(ch_ptr = strrchr(cadena, CARACTER_SUMA_VER))) {
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