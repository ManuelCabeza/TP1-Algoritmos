#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool convertir_a_numero_entero(char *cadena, int *resultado) {

	char *perr = NULL;

	if (cadena == NULL || resultado == NULL)
		return false;
	
	*resultado = strtol(cadena, &perr, 10);

	if (*perr != '\0') 
		return false;

	return true;
}

status_t validar_argumento_nombre(char *argv_nombre, char *nombre) {

	if (argv_nombre == NULL || nombre == NULL)
		return ST_ERROR_PUNTERO_NULO;
	
	strcpy(nombre, argv_nombre);
	return ST_OK;
	
}

status_t validar_argumento_fecha(char *argv_fecha, int *fecha) { 
//ANALIZAR COMO VALIDAR LOS MES Y DIA EN FECAH
//validar mes y dia. y 30 de febrero no es una fecha
	if (!convertir_a_numero_entero(argv_fecha, fecha))
		return ST_ERROR_MES_INVALIDO;

	if (*fecha < 0) 
		return ST_ERROR_FECHA_INVALIDA;
	
	return ST_OK;
}

status_t validar_argumento_mes(char *argv_mes, int *mes) {
	
	if (!convertir_a_numero_entero(argv_mes, mes))
		return ST_ERROR_MES_INVALIDO;

	if (*mes < CANT_MIN_MES || *mes > CANT_MAX_MES) 
		return ST_ERROR_MES_INVALIDO;

	return ST_OK;	
}

status_t validar_argumento_anio(char *argv_anio, int *anio) {
//cuesta mas trabajo usar strlen para leer una cantidad de una cadena y despues ver si eso esta bien.
	
	if (!convertir_a_numero_entero(argv_anio, anio))
		return ST_ERROR_ANIO_INVALIDO;

	if (*anio > CANT_MIN_ANIO || *anio < CANT_MAX_ANIO)
		return ST_ERROR_ANIO_INVALIDO;

	return ST_OK;
}

status_t validar_argumento_dia(char *argv_dia, int *dia) {

	if (!convertir_a_numero_entero(argv_dia, dia))
		return ST_ERROR_DIA_INVALIDO;

	if (*dia > CANT_MIN_DIA || *dia < CANT_MAX_DIA)
		return ST_ERROR_DIA_INVALIDO;

	return ST_OK;

}

//NOMBRE DUDOSO, PROPENSO A CAMBIO
status_t partir_fecha(int *fecha, int *dia, int *mes, int *anio) {

	if (!fecha || !dia || !mes || !anio)
		return ST_ERROR_PUNTERO_NULO;

	*anio = *fecha / 10000;
	*mes = (*fecha % 10000) / 100; //ver que sea del 1 al 12
	*dia = (*fecha % 10000) % 100; // ver que sea del 0 al 31

	printf("fecha %d\n", *fecha);
	printf("año : %d\n", *anio);
	printf("mes : %d\n", *mes);
	printf("Dia : %d\n", *dia);

	return ST_OK;
	
}

status_t cargar_fecha_por_omision (metadata * datos_usuario) {
    
    time_t tiempo; 
    struct tm * fecha_actual; 
    tiempo = time(NULL); 
    fecha_actual = localtime(&tiempo);
	
	/* Validar algo ??
	if(!())
		return ST_ERROR_PUNTERO_NULO;
	*/
	datos_usuario->fecha.dia  = fecha_actual->tm_mday;
	datos_usuario->fecha.mes  = fecha_actual->tm_mon;
	datos_usuario->fecha.anio = fecha_actual->tm_year; //VER PORQUE me da desde 1900

	return ST_OK;
}

status_t cargar_nombre_por_omision(metadata *datos_usuario) {

	if (!datos_usuario)
		return ST_ERROR_PUNTERO_NULO;

	strcpy(datos_usuario->nombre, NOMBRE_POR_OMISION); //VER QUE NOMBRE PONER


	return ST_OK;
}

bool cargar_hora_por_omision (horario_t *horario) {
    
	time_t tiempo; 
    struct tm *hora; 
    tiempo = time(NULL); 
    hora = localtime(&tiempo);

	if(!horario)
		return false;

	horario -> segundos = hora -> tm_sec;
	horario -> minuto = (hora -> tm_min) + 1;
	horario -> hora = (hora ->tm_hour) + 1;

	return true;
}
