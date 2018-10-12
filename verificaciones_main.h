#ifndef VALIDACIONES_MAIN_H
#define VALIDACIONES_MAIN_H

#define MSJ_ERROR_PREFIJO "Error"

typedef enum { ARG_AYUDA = 0, ARG_AYUDA_V, ARG_NOMBRE, ARG_NOMBRE_V, ARG_FECHA, ARG_FECHA_V,
               ARG_ANIO, ARG_ANIO_V, ARG_MES, ARG_MES_V, ARG_DIA, ARG_DIA_V
              } arg_t;


typedef enum estados {ST_OK, ST_ERROR_PUNTERO_NULO, ST_ERROR_FECHA_INVALIDA, ST_PEDIR_AYUDA} status_t;  
// NO ME GUSTA QUE AYUDA ESTE ACA

status_t procesar_argumentos(int argc, char *argv[], char *nombre, int *fecha);

void imprimir_ayuda();


#endif 


// solo van en el .h si otras funciones necesitan esas variables.
//Caso contratario va en el .c