#ifndef PROCESAR_UBX_POSLLH
#define PROCESAR_UBX_POSLLH

#include "procesar_ubx.h"

#define LARGO_PAYLOAD_POSLLH 28

procesar_ubx_status _procesar_ubx_posllh (FILE *pf_aux, FILE **pf);


#endif
