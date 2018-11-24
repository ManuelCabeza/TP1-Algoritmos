#ifndef PROCESAR_UBX_TIMTOS
#define PROCESAR_UBX_TIMTOS

#include "procesar_ubx.h"

#define LARGO_PAYLOAD_TIMTOS 8888

procesar_ubx_status _procesar_ubx_timtos (FILE *pf_aux, FILE **pf);

#endif
