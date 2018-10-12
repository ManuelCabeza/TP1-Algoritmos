/* Las líneas de tipo NMEA son de la forma
 * 
 *  $GPGGA,hhmmss.sss,ddmm.mmm,S(o N),dddmm.mmm, E(o W), Calidad del fix, Cantidad de satélites, HDop, elevación, Unidad, SepGeo, Unidad, *camposnulos*, *SV
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
#define CARACTER_SUMA_VER '*'

typedef enum {PR_FIN, PR_OK, PR_ERR} procesar_t;

typedef struct {
	float horario;
	float latitud;
	float longitud;
	int calidad_fix;
	int cant_satelites;
	float hdop;
	float elevacion;
	float sep_geo;
} gga;

unsigned char nmea_verificar_suma(const char * sentencia);

//La funcion devuelve...
procesar_t procesarNMEA(gga * ggaptr) {
	
	char c; //Variable auxiliar para no usar tolower mas de 2 veces.
	char string[MAX_LONG_SEN]; // Max longitud de un string posible
	char * strptr;
	
	long suma_verificacion;
	float horario;
	float longitud;
	float latitud;
	
	if (fgets(string, MAX_LONG_SEN,stdin) == NULL) 
		return PR_FIN;
	
	strptr = string;
	
	//Verifica que comienze con el caracter necesario
	if (* strptr != CARACTER_INICIO_COMANDO)  
		return PR_ERR;
	
	
	if ((strptr = strchr(string, CARACTER_SEPARACION_COMANDO)) != NULL) {
		strptr++;
		if ((horario = strtof(strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) { //Verifica que el primer argumento sea un numero (float) positivo
			return PR_ERR;
		}
	}
		
	if ((latitud = strtof(strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) { //Verifica que el segundo argumento sea un numero (float) positivo
		return PR_ERR;
	}
	
	c = tolower( * (strptr++));
	if ((c != CARACTER_NORTE) && (c != CARACTER_SUR)){ //Verifica que el tercer argumento sea uno de dos chars
		return PR_ERR;
	}
	
	ggaptr->latitud = ((int)latitud / 100) + ((latitud - 100 * ((int)latitud / 100)) / 60 ) * (c == CARACTER_SUR ? -1 : 1);
	printf("%f\n", ((latitud - 100 * ((int)latitud / 100)) / 60 ));
	//Verifica que el cuarto argumento sea un numero(float) positivo
	if ((longitud = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) 
		return PR_ERR;
	
	c = tolower( * (strptr++));
	if ((c != CARACTER_ESTE) && (c != CARACTER_OESTE)) //Verifica que el quinto argumento sea uno de dos chars
		return PR_ERR;
		
	ggaptr->longitud = ((int)longitud / 1000) + ((longitud - 1000 * ((int)longitud / 1000)) / 60 ) * (c == CARACTER_OESTE ? -1 : 1); 
	
	//Verifica que el sexto argumento sea un numero entero entre 0 y 8
	if ((ggaptr->calidad_fix = strtol(++strptr, &strptr, 10)) < MIN_VALOR_FIX || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO) || (ggaptr->calidad_fix) > MAX_VALOR_FIX) 
		return PR_ERR;
	
	//Verifica que el septimo argumento sea un numero entero entre 0 y 12
	if ((ggaptr->cant_satelites = strtof(++strptr, &strptr)) < MIN_VALOR_CANT_SATELITES || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO) || (ggaptr->cant_satelites > MAX_VALOR_CANT_SATELITES))  
		return PR_ERR;
			
	//Verifica que el octavo argumento sea un numero(float) positivo y lo guarda
	if ((ggaptr->hdop = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO))
		return PR_ERR;
			
	//Verifica que el noveno argumento sea un numero(float) positivo y lo guarda
	if ((ggaptr->elevacion = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) 
		return PR_ERR;
	
	//Verifica que el decimo argumento sea un caracter en especifico	
	if (tolower(* strptr++) != CARACTER_UNIDAD) 
		return PR_ERR;
	
	//Verifica que el undecimo argumento sea un numero(float) positivo y lo guarda
	if ((ggaptr->sep_geo = strtof(++strptr, &strptr)) < 0 || ((* (strptr++)) != CARACTER_SEPARACION_COMANDO)) 
		return PR_ERR;
	
	//Verifica que el duodecimo argumento sea un caracter en especifico
	if (tolower(* strptr) != CARACTER_UNIDAD)
		return PR_ERR;
	
	//Verifica que este el caracter que da inicio a la suma de verificacion
	if ((strptr = strrchr(string, CARACTER_SUMA_VER)) == NULL)
		return PR_ERR;
	
	suma_verificacion = strtol( ++strptr, NULL, 16);
	
	strptr = string + 1;	
	
	//Verifica la suma de verificacion (Valga la redundancia)
	if (nmea_verificar_suma( strptr) != suma_verificacion)
		return PR_ERR;
	
	puts("Esta bien");
		
	return PR_OK;
}

//Funcion que recibe una sentencia y calcula la XOR de todos los bytes hasta llegar a un caracter de corte
unsigned char nmea_verificar_suma(const char * sentencia) {
	
	unsigned char suma = 0;
	
	while ( * sentencia != CARACTER_SUMA_VER )
		suma ^= *sentencia++;
		
	return suma;
}
