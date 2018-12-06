#ifndef PROCESAR_UBX_TIMTOS
#define PROCESAR_UBX_TIMTOS

#include <stdio.h>

#include "procesar_ubx.h"

#define LARGO_PAYLOAD_TIMTOS 56

procesar_t _procesar_ubx_timtos (FILE **pf_in, gps_t *timtos_ptr);
/*  Recibe un puntero *pf_in a un archivo abierto en formato rb y
 * un ptr a la estructura gps, lee de este un payload y procesa los datos.
 *  Si el procesamiento de todos los datos es correcto devuelve PR_OK
 * en otro caso, devuelve el tipo de error bajo el enumerativo procesar_t.
 *  Carga en la estructura :  año, mes, dia, minuto, segundo y hora.
*/
#endif
