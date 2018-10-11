#include "verificacionesprocesarNMEA.h"

#define MAX_LONG_SEN 250

void procesarNMEA() {
	
	char sentencia[MAX_LONG_SEN]; // Max longitud de un string posible
	char * sentenciaptr; //por ahora no se usa 10/10
	
	fgets(sentencia, MAX_LONG_SEN,stdin);
	
	verificarargumentos(sentencia);
	
}

