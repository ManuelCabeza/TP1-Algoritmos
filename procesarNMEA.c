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
#define CARACTER_INICIO_SUMA_VER '*'

typedef enum {PR_FIN, PR_OK, PR_ERR} procesar_t;

unsigned char nmea_verificar_suma(const char * sentencia);

procesar_t procesarNMEA() {
	
	char c; //Variable auxiliar para no usar tolower mas de 2 veces.
	char string[MAX_LONG_SEN]; // Max longitud de un string posible
	char * strptr;
	unsigned char sumaux;
	
	int calfix, cantsat;
	
	float horario, HDoP, elvacion, sepgeo;
	float longitud;
	float latitud;
	
	if (fgets(string, MAX_LONG_SEN,stdin) == NULL) 
		return PR_FIN;
	
	strptr = string;
	if (* strptr != CARACTER_INICIO_COMANDO) {
		return PR_ERR;
	}
	
	if ((strptr = strchr(string, CARACTER_SEPARACION_COMANDO)) != NULL) {
		strptr++;
		if ((horario = strtof(strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) {
			return PR_ERR;
		}
	}
		
	if ((longitud = strtof(strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) {
			return PR_ERR;
	}
	
	c = tolower( * (strptr++));
	if ((c != CARACTER_NORTE) && (c != CARACTER_SUR)){
		return PR_ERR;
	}
	
	
	if ((latitud = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) {
			return PR_ERR;
	}
	
	
	c = tolower( * (strptr++));
	if ((c != CARACTER_ESTE) && (c != CARACTER_OESTE)){
		return PR_ERR;
	}
	strptr++;
	
	if ((calfix = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) {
			return PR_ERR;
	}	
		
	if ((cantsat = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) {
			return PR_ERR;
	}
		
	if ((HDoP = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) {
			return PR_ERR;
	}
		
	if ((elvacion = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) {
			return PR_ERR;
	}
		
	if (tolower(* strptr++) != CARACTER_UNIDAD){
		return PR_ERR;
	}
		
	if ((sepgeo = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) {
			return PR_ERR;
	}

	if (tolower(* strptr) != CARACTER_UNIDAD){
		return PR_ERR;
	}
	
	if ((strptr = strrchr(string, CARACTER_INICIO_SUMA_VER)) == NULL)
		return PR_ERR;
		
	strptr = string + 1;
	sumaux = nmea_verificar_suma( strptr);
	printf("%u %c %i \n", sumaux, sumaux, sumaux);
	
	puts("Esta bien");
		
	return PR_OK;
}

unsigned char nmea_verificar_suma(const char * sentencia) {
	
	unsigned char suma = 0;
	
	while ( * sentencia != '*' )
		suma ^= *sentencia++;
		
	return suma;
}
