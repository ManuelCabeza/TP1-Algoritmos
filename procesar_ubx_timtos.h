#ifndef PROCESAR_UBX_TIMTOS
#define PROCESAR_UBX_TIMTOS

#include "procesar_ubx.h"

#include "main.h"

#define LARGO_PAYLOAD_TIMTOS 56

procesar_t _procesar_ubx_timtos (FILE **pf_in, gps_t *timtos_ptr);

#endif
