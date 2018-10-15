#ifndef VALIDACIONES_MAIN_H
#define VALIDACIONES_MAIN_H

//No se me ocurren nombres de variables mas representativos.
#define ARG_VALIDO_AYUDA "-h"
#define ARG_VALIDO_AYUDA_V "--help"
#define ARG_VALIDO_NOMBRE "-n"
#define ARG_VALIDO_NOMBRE_V "--name"
#define ARG_VALIDO_FECHA "-f" //Si no se indica fecha se toma la del sistema
#define ARG_VALIDO_FECHA_V "--format"
#define ARG_VALIDO_ANIO "-Y"
#define ARG_VALIDO_ANIO_V "--year"
#define ARG_VALIDO_MES "-m"
#define ARG_VALIDO_MES_V "--month"
#define ARG_VALIDO_DIA "-d"
#define ARG_VALIDO_DIA_V "--day"

#define MAX_CANT_ARG 12 

#define MSJ_IMPRIMIR_AYUDA "Argumentos que tiene que recibir el programa:\n\n" \
							"-h , --help\n" \
							"		Muestra la ayuda\n" \
							"-n , --name\n" \
							"		Indica al metadato nombre(name)\n" \
							"-f , --format\n" \
							"		Indica la fecha. Debe ser una secuencia de 8 digitos\n" \
							"		que indiquen el año(la centuria), el mes y el dia,\n" \
							" 		por ejemplo 20181120 que indica el 20 noviembre de 2018\n" \
							"-Y , --year\n" \
							"		Indica el año. El año debe ser una secuencia de 4 digitos\n" \
							"		que indiquen el año con centuria. Por ejemplo: 2018\n" \
							"		indica el año 2018\n" \
							"-m , --month\n" \
							"		Indica el mes. El mes debe ser una secuencia de 1 ó 2 dígitos\n" \
							"		que indiquen el mes. Por ejemplo, 11 indica el mes noviembre.\n" \
							"-d , --day\n" \
							"		Indica el día. día debe ser una secuencia de 1 ó 2 dígitos\n" \
							"		que indiquen el día. Por ejemplo, 20 indica el día veinte.\n\n" \
							"Si no se indica la fecha, se debe tomar la del sistema.\n" \


#define CANT_MIN_FECHA 999999999 //NO ME GUSTA ESTO
#define CANT_MIN_MES 1
#define CANT_MAX_MES 12
#define CANT_MAX_ANIO 9999
#define CANT_MIN_ANIO 0
#define CANT_MAX_DIA 31
#define CANT_MIN_DIA 0

#define MSJ_ERROR_PREFIJO "Error"
#define MSJ_ERROR_PUNTERO_NULO "Puntero nulo."
#define MSJ_ERROR_FECHA_INVALIDA "La fecha ingresada es invalida."
#define MSJ_ERROR_NOMBRE_INVALIDO "El nombre ingresado es invalido."
#define MSJ_ERROR_DIA_INVALIDO "El dia ingresado es invalido."
#define MSJ_ERROR_MES_INVALIDO "El mes ingresado es invalido."
#define MSJ_ERROR_ANIO_INVALIDA "El año ingresado es invalido. "
#define MSJ_ERROR_SEGUNDOS_INVALIDO "El segundo ingresado es invalido. "
#define MSJ_ERROR_MINUTO_INVALIDO "El minuto ingresado es invalido. "
#define MSJ_ERROR_HORA_INVALIDA "La hora ingresada es invalida. "

#define CANT_MAX 150
#define NOMBRE_POR_OMISION "jiji"

typedef enum {ARG_AYUDA = 0, ARG_NOMBRE, ARG_FECHA, ARG_ANIO, ARG_MES, ARG_DIA} arg_t;


typedef enum estados {ST_OK, ST_ERROR_PUNTERO_NULO, ST_ERROR_FECHA_INVALIDA, ST_PEDIR_AYUDA,
                        ST_ERROR_NOMBRE_INVALIDO, ST_ERROR_DIA_INVALIDO, ST_ERROR_MES_INVALIDO,
                        ST_ERROR_ANIO_INVALIDO,/* ST_ERROR_MINUTOS_INVALIDO, ST_ERROR_SEGUNDOS_INVALIDO,
						ST_ERROR_HORA_INVALIDA*/} status_t;  
// NO ME GUSTA QUE AYUDA ESTE ACA
/* Esta se define de vardad qaca
typedef struct {
	int dia;
	int mes;
	int anio;
} fecha_t;
*/ 
 

bool convertir_a_numero_entero(char *cadena, int *resultado);
//char *nombre;
status_t procesar_argumentos(int argc, char *argv[], metadata *datos_usuario, int *fecha);

status_t validar_argumento_nombre(char *argv_nombre, char *nombre);
status_t validar_argumento_fecha(char *argv_fecha, int *fecha);
status_t validar_argumento_mes(char *argv_mes, int *mes);
status_t validar_argumento_anio(char *argv_anio, int *anio);
status_t validar_argumento_dia(char *argv_dia, int *dia);

status_t partir_fecha(int *fecha, int *dia, int *mes, int *anio);

void imprimir_ayuda();
void imprimir_errores(status_t estado);

status_t cargar_fecha_por_omision (metadata * datos_usuario);
status_t cargar_nombre_por_omision(metadata *datos_usuario);


#endif 


// solo van en el .h si otras funciones necesitan esas variables.
//Caso contratario va en el .c
