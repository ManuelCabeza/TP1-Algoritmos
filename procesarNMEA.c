/* Las líneas de tipo NMEA son de la forma
 * 
 *  $GPGGA,hhmmss.sss,ddmm.mmm,S(o N),ddmm.mmm, E(o W), Calidad del fix, Cantidad de satélites, HDop, elevación, Unidad, SepGeo, Unidad, *camposnulos*, *SV
 * 
 * hhmmss.sss horario del fix;
 * ddmm.mmm la primera es latitud, la seguna longitud
 * S multiplica por -1 latitud
 * W multiplica por -1 longitud
 * Calidad del fix numero del 0 al 8 discreto
 * Cantidad de satélites, número del 0 a 12 discreto
 * HDop debe ser 1.0 ? Preguntar a Pato .. Rta Debe ser numero
 * Elevación debe ser 0.0 ? Preguntar a Pato .. Rta Debe ser numero
 * Unidad Las dos deben ser M
 * Suma de verificacion 
 */
 
//#include "verificacionesprocesarNMEA.h"

#define MAX_LONG_SEN 85
#define CANT_ARGUMENTOS 14
#define MAX_VALOR_FIX 8
#define MIN_VALOR_FIX 0
#define MAX_VALOR_CANT_SATELITES 12
#define MIN_VALOR_CANT_SATELITES 0
#define CARACTER_NORTE 'n'
#define CARACTER_SUR   's'
#define CARACTER_ESTE  'e'
#define CARACTER_OESTE 'w'
#define CARACTER_UNIDAD 'm'
#define CARACTER_INICIO_COMANDO '$' 
#define CARACTER_SEPARACION_COMANDO ',' 

typedef enum {PR_FIN, PR_OK, PR_ERR} procesar_t;


procesar_t procesarNMEA() {
	
	char c; //Variable auxiliar para no usar tolower mas de 2 veces.
	char string[MAX_LONG_SEN]; // Max longitud de un string posible
	char * strptr;
	
	
	int calfix, cantsat;
	
	float horario, HDoP, elvacion, sepgeo;
	float longitud;
	float latitud;
	
	if (fgets(string, MAX_LONG_SEN,stdin) == NULL) 
		return PR_FIN;
	
	strptr = string;
	if (* strptr != CARACTER_INICIO_COMANDO) {
		puts("Caracter incorrecto");
		return PR_ERR;
	}
	
	if ((strptr = strchr(string, CARACTER_SEPARACION_COMANDO)) != NULL) {
		strptr++;
		if ((horario = strtof(strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) {
			puts("Tiene horario invalido");
			return PR_ERR;
		}
	}
	
	printf("|%c %c %c|\n", *(strptr - 1), *strptr, *(strptr + 1));
	
	if ((longitud = strtof(strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) {
			puts("Tiene longitud invalida");
			return PR_ERR;
	}
	
	printf("|%c %c %c|\n", *(strptr - 1), *strptr, *(strptr + 1));
	
	c = tolower( * (strptr++));
	if ((c != CARACTER_NORTE) && (c != CARACTER_SUR)){
		puts("Tiene norte sur mal");
		return PR_ERR;
	}
	
	printf("|%c %c %c|\n", *(strptr - 1), *strptr, *(strptr + 1));
	
	if ((latitud = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) {
			puts("Tiene latitud invalida");
			return PR_ERR;
	}
	
	printf("|%c %c %c|\n", *(strptr - 1), *strptr, *(strptr + 1));
	
	c = tolower( * (strptr++));
	if ((c != CARACTER_ESTE) && (c != CARACTER_OESTE)){
		puts("Tiene oeste este mal");
		return PR_ERR;
	}
	strptr++;
	printf("|%c %c %c|\n", *(strptr - 1), *strptr, *(strptr + 1));

	if ((calfix = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) {
			puts("Tiene calfix invalida");
			return PR_ERR;
	}	
	
	printf("|%c %c %c|\n", *(strptr - 1), *strptr, *(strptr + 1));
	
	if ((cantsat = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) {
			puts("Tiene cansat invalida");
			return PR_ERR;
	}
	
	printf("|%c %c %c|\n", *(strptr - 1), *strptr, *(strptr + 1));
	
	if ((HDoP = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) {
			puts("Tiene HDoP invalida");
			return PR_ERR;
	}
	
	printf("|%c %c %c|\n", *(strptr - 1), *strptr, *(strptr + 1));
	
	if ((elvacion = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) {
			puts("Tiene elevacion invalida");
			return PR_ERR;
	}
	
	printf("|%c %c %c|\n", *(strptr - 1), *strptr, *(strptr + 1));
	
	if (tolower(* strptr++) != CARACTER_UNIDAD){
		puts("Tiene unidad 1 mal");
		return PR_ERR;
	}
	
	printf("|%c %c %c|\n", *(strptr - 1), *strptr, *(strptr + 1));
	
	if ((sepgeo = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) {
			puts("Tiene sepgeo invalida");
			return PR_ERR;
	}

	printf("|%c %c %c|\n", *(strptr - 1), *strptr, *(strptr + 1));

	if (tolower(* strptr) != CARACTER_UNIDAD){
		puts("Tiene unidad 2 mal");
		return PR_ERR;
	}
	
	
	puts("Esta bien");
		
	return PR_OK;
}
