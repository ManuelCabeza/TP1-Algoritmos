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

#define MAX_CANT_ARG 6 //num del enum arg_t
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
//Ultima linea no poner contrabarra

#define CANT_MIN_PALABRA 9 //validar nombre

#define MSJ_ERROR_PREFIJO "Error"

#define MSJ_ERROR_PUNTERO_NULO "Puntero nulo."
#define MSJ_ERROR_FECHA_INVALIDA "La fecha ingresada es invalida."
#define MSJ_ERROR_NOMBRE_INVALIDO "El nombre ingresado es invalido."
#define MSJ_ERROR_SEGUNDO_INVALIDO "El segundo ingresado es invalido."
#define MSJ_ERROR_MINUTO_INVALIDO "El minuto ingresado es invalido."
#define MSJ_ERROR_HORA_INVALIDA "La hora ingresada es invalida. "




typedef enum { ARG_AYUDA = 0, ARG_NOMBRE, ARG_FECHA, ARG_ANIO, ARG_MES, ARG_DIA } arg_t;


typedef enum estados {ST_OK, ST_ERROR_PUNTERO_NULO, ST_ERROR_FECHA_INVALIDA, ST_PEDIR_AYUDA,
                        ST_ERROR_NOMBRE_INVALIDO, ST_ERROR_SEGUNDO_INVALIDO, ST_ERROR_MINUTO_INVALIDO,
                        ST_ERROR_HORA_INVALIDA} status_t;  
// NO ME GUSTA QUE AYUDA ESTE ACA

status_t procesar_argumentos(int argc, char *argv[], char *nombre, int *fecha);

status_t validar_argumento_nombre(char *argv_nombre, char *nombre);
status_t validar_argumento_fecha(char *argv_fecha, int *fecha);

void imprimir_ayuda();
void imprimir_errores(status_t estado);
#endif 


// solo van en el .h si otras funciones necesitan esas variables.
//Caso contratario va en el .c