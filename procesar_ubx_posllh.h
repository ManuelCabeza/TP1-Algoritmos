#ifndef PROCESAR_UBX_POSLLH
#define PROCESAR_UBX_POSLLH

#include "procesar_ubx.h"


#include "main.h"

#define LARGO_PAYLOAD_POSLLH 28

procesar_t _procesar_ubx_posllh (FILE **pf_in, gps_t *pos_ptr);

#endif
