
#define CHAR_INICIO_COMANDO '$' 

//Verifica que el char de inicio de comando sea el correcto
bool verificarprimerchar(char sentencia[]) {

	if (sentencia[0] != CHAR_INICIO_COMANDO)
		return false;
	return true;
}

//Verifica que halla solamente numeros en la sentencia, no se proteje de que haya mas de un punto !
//HARDCODEO !!!!!!! ??
bool verificarnumeroconpunto(char sentencia[]) {
	
	int longitud = strlen(sentencia);
	int i;
	
	for (i = 0; i < longitud; i++) 
		if ((isdigit((int)sentencia[i]) == 0) && sentencia[i] != '.')
			return false;
		
	return true;
}

//Verifica que haya solamente 1 caracter en el array y que sea char1 o char2.
//CHAR1 y CHAR2 DEBEN ESTAR EN MINUSCULA
bool verificarchar(char sentencia[], char caracter1, char caracter2) {
	
	if (strlen(sentencia) != 1) 
		return false;
		
	sentencia[0] = tolower(sentencia[0]);
	
	if (sentencia[0] != caracter1 && sentencia[0] != caracter2) 
		return false;

	return true;
}

//Revisa que contenga 1 caracter numerico y que sea un numero discreto del min al max
bool verificarintervalo(char sentencia[], int minimo, int maximo) {
	
	if (strlen(sentencia) != 1 || (isdigit(sentencia[0]) == 0)) 
		return false;
	
	int i = atoi(sentencia);
	
	if(i < minimo || i > maximo) 
		return false;
	
	return true;
}

//Revisa que recibe un solo caracter y que es el mismo que char1.
//CHAR1 DEBE SER MINUSCULA
bool verificarcharunidad(char sentencia[], char caracter) {
	
	if (strlen(sentencia) != 1 || tolower(sentencia[0]) != caracter)
		return false;
	
	return true;
}





