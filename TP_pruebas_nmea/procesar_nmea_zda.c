#include "procesar_nmea_zda.h"
/* Sentencia tipo
 * $GPZDA,hhmmss.sss,dd,mm,yyyy,xx,xx*cc
*/
procesar_t procesar_nmea_zda(gps_t * zda_ptr, char * ch_ptr, char * cadena) {
	
	long suma_verificacion;
	float horario;
	
	if ((ch_ptr = strchr(cadena, CARACTER_SEPARACION_COMANDO)) != NULL) {
		ch_ptr++;
		if ((horario = strtof(ch_ptr, &ch_ptr)) < 0 || ((* (ch_ptr++)) != CARACTER_SEPARACION_COMANDO)) { 
			return PR_ERR;
		}
	} // horario = hhmmss.sss
	procesar_horario(&(zda_ptr->horario), horario);
	
	zda_ptr->fecha.dia = strtol(ch_ptr, &ch_ptr, 10);
	if (*(ch_ptr++) != CARACTER_SEPARACION_COMANDO)
		return PR_ERR; // Ver que tipo de error es ==???

	zda_ptr->fecha.mes = strtol(ch_ptr, &ch_ptr, 10); 
	if (*(ch_ptr++) != CARACTER_SEPARACION_COMANDO)
		return PR_ERR; // Ver que tipo de error es ==???

	
	zda_ptr->fecha.anio = strtol(ch_ptr, &ch_ptr, 10); // aux es yyyy
	if (*(ch_ptr++) != CARACTER_SEPARACION_COMANDO)
		return PR_ERR; // Ver que tipo de error es ==???
	
	strtol(ch_ptr, &ch_ptr, 10); // aux es xx (1)
	if (*(ch_ptr++) != CARACTER_SEPARACION_COMANDO)
		return PR_ERR;
	
	strtol(ch_ptr, &ch_ptr, 10); // aux es xx (2)
	if (*ch_ptr != CARACTER_SEPARACION_COMANDO)
		return PR_ERR;
	
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

