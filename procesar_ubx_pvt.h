#ifndef PROCESAR_UBX_PVT
#define PROCESAR_UBX_PVT

#include "procesar_ubx.h"

#define LARGO_PAYLOAD_PVT 92
#define MASCARA_VALID 0x0F
#define MASCARA_FLAGS 0x01

procesar_t _procesar_ubx_pvt (FILE **pf_in, gps_t *pvt_ptr);

#endif

