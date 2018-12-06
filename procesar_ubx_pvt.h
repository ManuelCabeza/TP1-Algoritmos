#ifndef PROCESAR_UBX_PVT
#define PROCESAR_UBX_PVT

#include "procesar_ubx.h"

#define LARGO_PAYLOAD_PVT 92
#define MASCARA_VALID 0x0F
#define MASCARA_FLAGS 0x01

procesar_t _procesar_ubx_pvt (FILE **pf_in, gps_t *pvt_ptr);
/*  Recibe un puntero *pf_in a un archivo abierto en formato rb y
 * un ptr a la estructura gps, lee de este un payload y procesa los datos.
 *  Si el procesamiento de todos los datos es correcto devuelve PR_OK
 * en otro caso, devuelve el tipo de error bajo el enumerativo procesar_t.
 *  Carga en la estructura : año, mes, dia, hora, minuto, segundo, 
 * cant_sat, longitud, latitud, sep_geo, elevacion. 
*/
#endif

