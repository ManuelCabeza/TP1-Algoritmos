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
 * HDop debe ser 1.0 ? Preguntar a Pato
 * Elevación debe ser 0.0 ? Preguntar a Pato
 * Unidad Las dos deben ser M
 * Suma de verificacion 
 */
 
#include "verificacionesprocesarNMEA.h"

#define MAX_LONG_SEN 250
#define CARACTER_SEPARACION_COM "," //COM de COMANDOS
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


bool procesarNMEA() {
	
	int i = 1;
	char sentencia[MAX_LONG_SEN]; // Max longitud de un string posible
	//char * sentenciaptr; //por ahora no se usa fecha 10/10
	char * argumentos[CANT_ARGUMENTOS]; //En cada casilla de argumentos hay un puntero que apunta a su argumento. HASTA ANTES DE LOS CAMPOS NULOS
	
	fgets(sentencia, MAX_LONG_SEN,stdin);
	
	argumentos[0] = strtok(sentencia, CARACTER_SEPARACION_COM);
	
	while (argumentos[i] != NULL) {
		argumentos[i] = strtok(NULL, CARACTER_SEPARACION_COM);
		i++;
	}
	
	for (i = 0; i < CANT_ARGUMENTOS - 1; i++)
		printf("%s\n", argumentos[i]);
	
	
	if (verificarprimerchar(argumentos[0]) != true)
		return false;
	
	if (verificarnumeroconpunto(argumentos[1]) != true) //Para la hora
		return false;
	
	if (verificarnumeroconpunto(argumentos[2]) != true) //Para la latitud
		return false;
	
	//cargarlatitud(argumentos[2], estructura ??); HAY QUE CARGAR TODOS
	
	if (verificarchar(argumentos[3], CARACTER_NORTE, CARACTER_SUR) != true)
		return false;
	
	if (verificarnumeroconpunto(argumentos[4]) != true) //Para la longitud
		return false;
	
	if (verificarchar(argumentos[5], CARACTER_OESTE, CARACTER_ESTE) != true)
		return false;
	
	if(verificarintervalo(argumentos[6], MIN_VALOR_FIX, MAX_VALOR_FIX) != true)  //Verifica el valor del Fix
		return false;
	
	if(verificarintervalo(argumentos[7], MIN_VALOR_CANT_SATELITES, MAX_VALOR_CANT_SATELITES) != true) { //Verifica el valor del Fix
		puts("MAl intervalo2"); //Esto esta mal preguntar como hacer al grupo
		return false;
	}
	if(verificarcharunidad(argumentos[10], CARACTER_UNIDAD) != true) {
		puts("MALUNIDAD");
		return false;
	}
	if(verificarcharunidad(argumentos[12], CARACTER_UNIDAD) != true) {
		puts("MALUNIDAD");
		return false;
	}
		
		
		
		
	puts("Bueno");
	return true;
}
