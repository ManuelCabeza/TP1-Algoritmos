#ifndef PROCESAR_UBX_POSLLH
#define PROCESAR_UBX_POSLLH

#include <stdio.h>

#include "procesar_ubx.h"


#define LARGO_PAYLOAD_POSLLH 28

procesar_t _procesar_ubx_posllh (FILE **pf_in, gps_t *pos_ptr);
/*  Recibe un puntero *pf_in a un archivo abierto en formato rb y
 * un ptr a la estructura gps, lee de este un payload y procesa los datos.
 *  Si el procesamiento de todos los datos es correcto devuelve PR_OK
 * en otro caso, devuelve el tipo de error bajo el enumerativo procesar_t.
 *  Carga en la estructura :  latitud, longitud, sep_geo y elevacion.
*/
#endif
