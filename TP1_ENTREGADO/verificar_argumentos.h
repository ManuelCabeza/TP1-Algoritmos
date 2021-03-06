#ifndef VALIDACIONES_MAIN_H
#define VALIDACIONES_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "main.h"

#define ARG_VALIDO_AYUDA "-h"
#define ARG_VALIDO_AYUDA_V "--help"
#define ARG_VALIDO_NOMBRE "-n"
#define ARG_VALIDO_NOMBRE_V "--name"
#define ARG_VALIDO_FECHA "-f" 
#define ARG_VALIDO_FECHA_V "--format"
#define ARG_VALIDO_ANIO "-Y"
#define ARG_VALIDO_ANIO_V "--year"
#define ARG_VALIDO_MES "-m"
#define ARG_VALIDO_MES_V "--month"
#define ARG_VALIDO_DIA "-d"
#define ARG_VALIDO_DIA_V "--day"

#define MAX_CANT_ARG_VALIDOS 12 

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


#define CANT_MAX_FECHA 99991231
#define CANT_MIN_FECHA 0
#define CANT_MAX_MES 12 
#define CANT_MIN_MES 1
#define CANT_MAX_ANIO 9999
#define CANT_MIN_ANIO 0
#define CANT_MAX_DIA 31
#define CANT_MIN_DIA 1

#define CANT_MAX 100
#define NOMBRE_POR_OMISION "ARSAT-15"

#define AJUSTE_DE_NUM 1
#define ANIO_DE_LINUX 1900

typedef enum {ARG_AYUDA = 0, ARG_NOMBRE, ARG_FECHA, ARG_ANIO, ARG_MES, ARG_DIA, ARG_INVALIDO} arg_t;

typedef enum estados {ST_OK, ST_PEDIR_AYUDA, ST_ERROR_PUNTERO_NULO,  
					  ST_ERROR_FECHA_INVALIDA, ST_ERROR_NOMBRE_INVALIDO, 
					  ST_ERROR_DIA_INVALIDO, ST_ERROR_MES_INVALIDO,
                      ST_ERROR_ANIO_INVALIDO, ST_ERROR_CANT_ARG_INVALIDO,
					  ST_ERROR_ARG_INVALIDO} status_t;  
					  

/*
  * Recibe una cadena que corresponde al argumento ingresado por línea de 
  * comando. Si recibe un argumento válido, devuelve qué tipo de argumento es. 
  * Caso contrario, devuelve un ARG_INVALIDO.
  */
arg_t validar_arg(char *arg);

/* Verifica que los argumentos que se ingresan por linea de comando sean validos.
 * En caso de que sean validos, los almacena en la estructura datos_usuario.
 * Caso contrario, devuelve un estado de error que corresponda.  
 * 
 * Recibe un arreglo de cadenas argv, la cantidad de cadenas que haya en argv es argc,
 * y un puntero a una estructura datos_usuario donde se guardaran los resultados.
 * 
 * Devuelve un ST_AYUDA en caso de que se haya ingresado el argumento -h o --help
 * ST_ERROR_* en caso que algun argumento no sea valido
 * ST_OK si todos los argumentos son validos y sus contenidos tambien 
 */
status_t procesar_argumentos(int argc, char *argv[], metadata_t *datos_usuario);

/* Convierte cualquier cadena que se le pase a un numero entero en base 10.
 * Si se puede convertir la cadena, lo guarda en resultado y devuelve true.
 * Caso contrario, devuelve un false y la funcion no hace nada. 
 */
bool convertir_a_numero_entero(char *cadena, int *resultado); 

/* Verifica que el argumento ingresado por linea de comando argv_nombre sea 
 * valido. Si el argumento es valido, se guarda en el campo nombre de la 
 * estructura. 
 * Caso contrario, devuelve un estado de error, y la funcion no hace nada.
 */
status_t validar_argumento_nombre(char *argv_nombre, char *nombre);

/* Verifica que el argumento fecha ingresado por linea de comando sea valido.
 * En caso que sea valido, lo almacena en el campo de la estructura 
 * datos_usuario. Caso contrario, devuelve un estado de error correspondiente.
 * 
 * Recibe una cadena argv y un puntero a una estructura donde se guardaran
 * todos los datos. 
 */
status_t validar_argumento_fecha(char *argv_fecha, fecha_t *fecha);

/* Se espera que fecha sea de la forma yyyymmdd ingresada por linea de comando,
 * y la parte de forma tal que quede año = yyyy , mes = mm, dia = dd
 * cargada correctamente en el campo de la estructura datos_usuario.
 * Caso contrario, devuelve un estado de error correspondiente. 
*/
status_t partir_fecha(int fecha_actual, fecha_t *fecha);

/* Las siguientes tres funciones siguen la misma idea:
 * Verifica que el argumento ingresado por linea de comando sea valido. 
 * Y en caso de serlo, lo guarda al campo de fecha la estructura.
 * Caso contrario, devuelve un estado de error correspondiente.
 * 
 * Recibe un arreglo de cadenas argv correspondiente y un puntero a una
 * estructura donde se guarda dicho valor si es correcto.
*/
status_t validar_argumento_mes(char *argv_mes, int *mes);
status_t validar_argumento_anio(char *argv_anio, int *anio);
status_t validar_argumento_dia(char *argv_dia, int *dia);

/* Imprime la ayuda por stdout. */
void imprimir_ayuda(void);

/* Inicializa al campo fecha de la estructura con la fecha actual del sistema. 
 * Si recibe un puntero nulo, entonces devuelve false.
 * Caso contrario, devuelve true. 
 */
bool cargar_fecha_por_omision (fecha_t * fecha);

/* Inicializa al campo nombre de la estructura con un nombre por defecto. 
 * Si recibe un puntero nulo, entonces devuelve false.
 * Caso contrario, devuelve true. 
 */
bool cargar_nombre_por_omision(char *nombre);

/* Inicializa al campo horario de la estructura con la hora actual del sistema. 
 * Si recibe un puntero nulo, entonces devuelve false.
 * Caso contrario, devuelve true. 
 */
bool cargar_hora_por_omision (horario_t *horario);

#endif 