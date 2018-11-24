#ifndef PROCESAR_UBX
#define PROCESAR_UBX

#include <stdio.h>


#define B_SYNC1 0xB5
#define B_SYNC2 0x62
#define B_CLASE 0x01
#define ID_TIMTOS 8888
#define ID_POSLLH 0x02
#define ID_PVT 0x07

//Formatos de tamaños definidos para protocolo ubx
#define U1 sizeof(unsigned char)
#define U2 sizeof(unsigned short)
#define U4 sizeof(unsigned long)
#define I1 sizeof(signed char)
#define I2 sizeof(signed short)
#define I4 sizeof(signed long)
#define X1 sizeof(unsigned char)

// PUE == Procesar Ubx Error
typedef enum {PU_OK, PU_FIN, PUE_LEC, PUE_PTRNUL, PUE_CLASE, PUE_ID, PUE_LARGO, PUE_CKSUM} procesar_ubx_status;
typedef enum {FALSO = 0, VERDADERO = 1} bool_t;
typedef unsigned char uchar;


procesar_ubx_status procesar_ubx (FILE **pf);

procesar_ubx_status _procesar_ubx (FILE **pf);

bool_t check_sum (uchar ck_a, uchar ck_b, FILE *pf);

#endif
