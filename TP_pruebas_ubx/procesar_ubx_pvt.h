#ifndef PROCESAR_UBX_PVT
#define PROCESAR_UBX_PVT

#include "procesar_ubx.h"

#define LARGO_PAYLOAD_PVT 92

procesar_ubx_status _procesar_ubx_pvt (FILE **pf_in, gps_t * pvt_ptr);


#endif

