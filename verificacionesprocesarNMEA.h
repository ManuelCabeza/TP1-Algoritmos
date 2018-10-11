#include "verificacionesprocesarNMEA.c"

bool verificarprimerchar(char sentencia[]);
bool verificanumeroconpunto(char sentencia[]);
bool verificarchar(char sentencia[], char caracter1, char caracter2);
bool verificarcharunidad(char sentencia[], char caracter);
bool verificarintervalo(char sentencia[], int minimo, int maximo);

