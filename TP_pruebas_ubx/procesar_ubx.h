#ifndef PROCESAR_UBX
#define PROCESAR_UBX

#include <stdio.h>

#define B_MAX_CANT_SENT 100 
#define B_SYNC1 0xB5
#define B_SYNC2 0x62
#define B_CLASE 0x01
#define ID_TIMTOS 8888
#define ID_POSLLH 0x02
#define ID_PVT 0x07

#define SHIFT_U1 8;
//Formatos de tamaños definidos para protocolo ubx
#define U1 sizeof(unsigned char)
/*#define U2 sizeof(unsigned short)
#define U4 sizeof(unsigned long)
#define I1 sizeof(signed char)
#define I2 sizeof(signed short)
#define I4 sizeof(signed long)
#define X1 sizeof(unsigned char)*/

// PUE == Procesar Ubx Error, El error PUE_LEC equivale a error de archivo corrupto
typedef enum {PU_OK, PU_FIN, PUE_LEC, PUE_PTRNUL, PUE_CLASE, PUE_ID, PUE_LARGO, PUE_CKSUM_B, PUE_CKSUM_A,
	          PUE_VALID_FLAGS, PUE_VALID_FIX } procesar_ubx_status;

typedef unsigned char uchar;


procesar_ubx_status procesar_ubx (FILE **pf_in, gps_t * ubx_ptr);

procesar_ubx_status _procesar_ubx (FILE **pf_in, gps_t * ubx_ptr);

void check_sum (uchar payload[], size_t long_payload, uchar * ck_a, uchar * ck_b);

#endif
