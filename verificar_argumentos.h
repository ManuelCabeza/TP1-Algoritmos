#ifndef VALIDACIONES_MAIN_H
#define VALIDACIONES_MAIN_H

#include <stdio.h>
#include <stdbool.h>

#include "procesar_ubx.h"

#define ARG_VALIDO_AYUDA "-h"
#define ARG_VALIDO_AYUDA_V "--help"
#define ARG_VALIDO_NOMBRE "-n"
#define ARG_VALIDO_NOMBRE_V "--name"
#define ARG_VALIDO_PROTOCOLO "-p" 
#define ARG_VALIDO_PROTOCOLO_V "--protocolo"
#define ARG_VALIDO_ARCHIVO_ENTRADA "-i"
#define ARG_VALIDO_ARCHIVO_ENTRADA_V "--infile"
#define ARG_VALIDO_ARCHIVO_SALIDA "-o"
#define ARG_VALIDO_ARCHIVO_SALIDA_V "--outfile"
#define ARG_VALIDO_ARCHIVO_LOG "-l"
#define ARG_VALIDO_ARCHIVO_LOG_V "--logfile"
#define ARG_VALIDO_CANT_MENSAJE "-m"
#define ARG_VALIDO_CANT_MENSAJE_V "--maxlen"

#define MAX_CANT_ARG_VALIDOS 14 

#define MAX_CANT_ARG 14 

#define MSJ_IMPRIMIR_AYUDA "Argumentos que tiene que recibir el programa:\n\n" \
							"-h , --help\n" \
							"		Muestra la ayuda\n" \
							"-n , --name\n" \
							"		Indica al metadato nombre(name)\n" \
							"-p , --protocol \n" \
							"		Indica el protocolo a leer. protocolo puede tomar \n" \
							"		los valores nmea, ubx o auto. En la tercera opcion,\n" \
							" 		el protocolo debe ser detectado por la aplicacion en\n" \
							"		en funcion de los mensajes que lee\n "\
							"-i , --infile \n" \
							"		Indica el nombre del archivo a utilizar como entrada de datos.\n" \
							"		Si no quiere que sea por archivo, ingrese \"-\".\n" \
							"		\n" \
							"-o , --outfile \n" \
							"		Indica el nombre del archivo a utilizar para el archivo gpx.\n" \
							"		Para indicar la impresion de datos en stdout, se ingresa \"-\".\n" \
							"-l , --logfile \n" \
							"		Indica el nombre del archivo a utilizar para el archivo log.\n" \
							"		Para indicar la impresion de logs en stderr, se ingresa \"-\".\n" \
							"-m , --maxlen \n" \
							"		Indica la máxima cantidad de mensajes que se pueden .\n" \
							"		almacenar en una lista.\n\n" \


#define B_SYNC1 0xB5 
#define B_SYNC2 0x62 

#define CANT_MAX 100
#define NOMBRE_POR_OMISION "ARSAT-15"

#define ARG_PROTOCOLO_NMEA "nmea"
#define ARG_PROTOCOLO_UBX "ubx"
#define ARG_PROTOCOLO_AUTO "auto" /*Debe ser detectado por la aplicacion*/

#define CANT_MAX_CARACTERES_SINCRONISMO 2
#define POS_INICIAL_CARACTER_SINCRONISMO 0
#define POS_FINAL_CARACTER_SINCRONISMO 1

#define CARACTER_PESO '$' 

#define ARCHIVO_ENTRADA_STDIN "-"
#define ARCHIVO_SALIDA_STDOUT "-"
#define ARCHIVO_LOG_STDERR "-"

typedef enum {ARG_AYUDA = 0, ARG_NOMBRE, ARG_PROTOCOLO, ARG_ARCHIVO_ENTRADA, 
			  ARG_ARCHIVO_SALIDA, ARG_ARCHIVO_LOG, ARG_CANT_MENSAJES, 
			  ARG_INVALIDO} arg_t;

typedef enum estados {ST_OK, ST_PEDIR_AYUDA, ST_ERROR_PUNTERO_NULO,  
					  ST_ERROR_NOMBRE_INVALIDO, ST_ERROR_PROTOCOLO_INVALIDO,
					  ST_ERROR_ARCHIVO_ENTRADA_INVALIDO, ST_ERROR_ARCHIVO_SALIDA_INVALIDO,
					  ST_ERROR_ARCHIVO_LOGS_INVALIDO, ST_ERROR_CANT_MENSAJES_INVALIDOS,
					  ST_ERROR_CANT_ARG_INVALIDO, ST_ERROR_ARG_INVALIDO, 
					  ST_ERROR_LECTURA, ST_ERROR_LISTA_CREAR, ST_ERROR_LISTA_CARGAR} status_t;  

typedef enum {PROTOCOLO_NMEA, PROTOCOLO_UBX, PROTOCOLO_AUTO, PROTOCOLO_INVALIDO} protocolo_t;


arg_t validar_arg(char *arg);
/* Recibe una cadena que corresponde al argumento ingresado por línea de 
 * comando. Si recibe un argumento válido, devuelve qué tipo de argumento es. 
 * Caso contrario, devuelve un ARG_INVALIDO.
 */

status_t procesar_argumentos(int argc, char *argv[], FILE **entrada, FILE **salida, FILE **archivo_log, metadata_t *datos_usuario, protocolo_t *protocolo, int *longitud_lista);
/* Verifica que los argumentos que se ingresan por linea de comando sean validos.
 * En caso de que sean validos, los almacena en la estructura datos_usuario.
 * Caso contrario, devuelve un estado de error que corresponda.  
 * 
 * Recibe la cantidad, argc, de cadenas que haya en argv, un arreglo de cadenas
 * argv, puntero al archivo de entrada donde se van leyendo los datos, y unos 
 * puntero a los archivos de salida e archivo_log donde se van imprimiendo el
 * formato gpx e imprimeindo los mensajes de errores, warn o debug en el log,
 * un puntero a una estructura datos_usuario donde se guardaran los resultados
 * un puntero a protocolo_t, donde aclara que tipo de protocolo es y por ultimo
 * un puntero a longitud de la listJASKJANSKJDANSDKJNASKDJASDAKSND
 * Devuelve un ST_AYUDA en caso de que se haya ingresado el argumento -h o --help
 * ST_ERROR_* en caso que algun argumento no sea valido
 * ST_OK si todos los argumentos son validos y sus contenidos tambien. 
 */

status_t validar_argumento_nombre(char *argv_nombre, char *nombre);
/* Verifica que el argumento ingresado por linea de comando argv_nombre sea 
 * valido. Si el argumento es valido, se guarda en el campo nombre de la 
 * estructura. 
 * Caso contrario, devuelve un estado de error, y la funcion no hace nada.
 */

void imprimir_ayuda(FILE *salida);
/* Imprime la ayuda por stdout. */

bool cargar_nombre_por_omision(char *nombre);
/* Inicializa al campo nombre de la estructura con un nombre por defecto. 
 * Si recibe un puntero nulo, devuelve false. Caso contrario, devuelve true.
 */

status_t validar_argumento_protocolo(char *argv_protocolo, protocolo_t *protocolo);
/* Verifica que el argumento ingresado por linea de comando argv_protocolo sea
 * valido (Puede ser: nmea, ubx, auto: Lo define el programa). 
 * Recibe como primer parametro un puntero a una cadena donde se indica el 
 * protocolo y un puntero a protocolo_t donde guarda el protocolo encontrado.
 * Devuelve ST_OK si encontro alguno de los protocolo validos, 
 * ST_ERROR_PROTOCOLO_INVALIDO si no encontro ningun protocolo, y 
 * ST_ERROR_PUNTERO_NULO si se ingresa como parametro de funcion un pntero nulo.
 */

status_t identificar_protocolo_auto(char *arg_archivo_entrada, protocolo_t *protocolo);
/* Verifica que el argumento ingresado por linea de comando sea auto, entonces
 * el programa se encarga de determinar que protocolo es. 
 * Recibe un puntero al nombre del archivo de entrada y un puntero al protocolo.
 * Devuelve ST_ERROR_PUNTERO_NULO si se ingresa un puntero nulo como parametro
 * de la funcion, ST_ERROR_PROTOCOLO_INVALIDO cuando se pasa un protocolo invalido,
 * ST_ERROR_ARCHIVO_ENTRADA_INVALIDO cuando no se puede abrir el archivo, 
 * ST_ERROR_LECTURA cuando no se puede leer el archivo de entrada y ST_OK
 * cuando identifico un protocolo valido.
 */

FILE * abrir_archivo_entrada(char *arg_archivo_entrada, protocolo_t *protocolo, status_t *estado);
/* Abre el archivo de entrada que se pasa por argumento de linea de comando. 
 * Dependiendo de que protocolo, lo abre en diferentes modos. Si se pasa el 
 * argumento "-" se reciben los datos por stdin.
 * Recibe un puntero al nombre del archivo de entrada, un puntero indicando
 * el protocolo, un puntero a un estado para informar las validaciones.
 * Devuelve NULL en caso de algun error o el archivo abierto en modo "rt" si
 * el protocolo es NMEA, "rb" si el protocolo es UBX.
 */

FILE * abrir_archivo_salida (char *arg_archivo_salida, status_t *estado);
/* Abre el archivo de salida que se pasa por argumento de linea de comando. 
 * Si se pasa el argumento "-", se imprimen los datos en formato gpx por stdout.
 * Recibe un puntero al nombre del archivo de salida y un puntero indicando
 * un estado para informar las validaciones.
 * Devuelve NULL en caso de algun error o el archivo abierto en modo "rw". 
 */

FILE * abrir_archivo_log (char *arg_archivo_log, status_t *estado);
/* Abre el archivo log que se pasa por argumento de linea de comando. 
 * Si se pasa el argumento "-", se imprimen los mensajes por stderr.
 * Recibe un puntero al nombre del archivo log y un puntero indicando
 * un estado para informar las validaciones.
 * Devuelve NULL en caso de algun error o el archivo abierto en modo "rw".
 * Donde se imprimen los mensajes de errores, warning y debug. 
 */

bool convertir_a_numero_entero(char *cadena, int *resultado); 
/* Convierte cualquier cadena que se le pase a un numero entero en base 10.
 * Si se puede convertir la cadena, lo guarda en resultado y devuelve true.
 * Caso contrario, devuelve un false y la funcion no hace nada. 
 */

status_t validar_argumento_cant_msj(char *arg_cant_msj, int *cant_msj);
/* Verifica que el argumento cantidad de mensajes sea valido.
 * Recibe un puntero al argumento y un puntero al numero de cant_msj.
 * Devuelve ST_OK cuando el argumento sea valido, 
 * ST_ERROR_CANT_MENSAJES_INVALIDO cuando es invalido, 
 * ST_ERROR_PUNTERO_NULO cuando algun parametro de la funcion es un puntero nulo.
 */

#endif 