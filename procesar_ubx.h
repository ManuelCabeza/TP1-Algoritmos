#ifndef PROCESAR_UBX
#define PROCESAR_UBX

#include <stdio.h>

#include "main.h"

#define B_MAX_CANT_SENT 100 
#define B_SYNC1 0xB5
#define B_SYNC2 0x62
#define CLASE_PVT 0x01
#define CLASE_POSLLH 0x01
#define CLASE_TIMTOS 0x0D
#define ID_TIMTOS 0x12
#define ID_POSLLH 0x02
#define ID_PVT 0x07

#define SHIFT_U1 8
//Formatos de tamaños definidos para protocolo ubx
#define U1 sizeof(unsigned char)
#define U2 sizeof(unsigned short)
#define I4 sizeof(signed long)


#define RANGO_DIA_MIN 1
#define RANGO_DIA_MAX 31
#define RANGO_MES_MIN 1
#define RANGO_MES_MAX 12

#define RANGO_HORA_MIN 1
#define RANGO_HORA_MAX 24
#define RANGO_MINUTO_MIN 0
#define RANGO_MINUTO_MAX 60
#define RANGO_SEGUNDO_MIN 0
#define RANGO_SEGUNDO_MAX 60


#ifndef PROCESAR
#define PROCESAR
typedef enum { PR_OK = 0, PR_FIN, PR_ERR_NO_CAR_INI, PR_ERR, PR_ERR_SENT, 
			   PR_ERR_CAR_STATUS, PR_ERR_HORARIO, PR_ERR_CAR_LATITUD, 
			   PR_ERR_LATITUD, PR_ERR_CAR_LONGITUD, PR_ERR_LONGITUD, 
			   PR_ERR_CAL_FIX, PR_ERR_CANT_SAT, PR_ERR_ELEVACION, 
			   PR_ERR_CAR_METRO, PR_ERR_HDOP, PR_ERR_SEP_GEO, PR_ERR_FECHA,
		       PR_ERR_MES, PR_ERR_ANIO, PR_ERR_DIA, PR_ERR_ZONA_HORARIA,
			   PR_ERR_ARCHIVO, PR_ERR_PTR_NULL, PR_ERR_CLASE, 
			   PR_ERR_ID, PR_ERR_LARGO, PR_ERR_SUM_VER, PR_ERR_VALID_FLAGS, 
			   PR_ERR_VALID_FIX, PUE_NOT, PR_DEBUG, PR_ERR_SEG, PR_ERR_MIN 
			   } procesar_t;
#endif

typedef unsigned char uchar;

signed long u1_to_i4 (uchar *u1);
/*Función de conversión que permite cambiar de un conjunto de 4 uchar 
 *a un signed long. Devuelve el signed long y recibe un puntero a la
 * primer posición de los 4 uchar.
 *   !!Al usar esta función se debe tener precacución ya que funciona
 * para realizar conversiones sobre un arreglo donde ya se verifico que
 * a donde apunten las 4 posiciones de u1 son válidas. Podría causar un
 * error si no se usa adecuadamente.
*/

unsigned short u1_to_u2 (uchar *u1);
/*Función de conversión que permite cambiar de un conjunto de 4 uchar 
 *a un unsigned short. Devuelve el unsigned short y recibe un puntero a la
 * primer posición de los 2 uchar.
 *   !!Al usar esta función se debe tener precacución ya que funciona
 * para realizar conversiones sobre un arreglo donde ya se verifico que
 * a donde apunten las 2 posiciones de u1 son válidas. Podría causar un
 * error si no se usa adecuadamente.
*/


procesar_t procesar_ubx (FILE **pf_in, gps_t *ubx_ptr);
/* La función busca en *pf_in el par de caracteres de sincronismo
 * definidos por las macros B_SYNC1 y B_SYNC2.
 *   Si no los encuentra o hay un error devuelve el determinado tipo
 * procesar_t, si lo logra devuelve lo que de _procesar_ubx
 * (funciona como una función de wrapper para la misma).
*/

procesar_t _procesar_ubx (FILE **pf_in, gps_t *ubx_ptr);
/* Lee a partir de *pf_in los byte de clase e id una vez leidos los
 * de sincronismo en procesar_ubx. Una vez que se distingue el id
 * se llama a la funcion de procesamiento correspondiente.
 * Duevuelve PR_OK si se proceso correctamente la linea y el tipo de 
 * error en el enumerativo procesar_t si hay un error.
*/

void check_sum (uchar payload[], size_t long_payload, uchar *ck_a, uchar *ck_b);
/* Raliza el algoritmo de check sum para todo el payload y devuelve sus valores por interfaz.
 * Se debe previamente, realizar el ch_sum de los bytes de clase e id
 * fuera de la funcion.
*/

void inicializar_estructura (gps_t *gps_ptr);
/* Inicializa todos los campos de la estructura en 0.
*/

#endif
