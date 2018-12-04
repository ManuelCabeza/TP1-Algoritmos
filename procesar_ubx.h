#ifndef PROCESAR_UBX
#define PROCESAR_UBX

#include <stdio.h>
#include "main.h"

#define B_MAX_CANT_SENT 100 
#define B_SYNC1 0xB5
#define B_SYNC2 0x62
#define CLASE_PVT 0x01
#define CLASE_POSLLH 0x01
#define CLASE_TIMTOS 0x0D
#define ID_TIMTOS 0x12
#define ID_POSLLH 0x02
#define ID_PVT 0x07

#define SHIFT_U1 8
//Formatos de tamaños definidos para protocolo ubx
#define U1 sizeof(unsigned char)
#define U2 sizeof(unsigned short)
//#define U4 sizeof(unsigned long)
//#define I1 sizeof(signed char)
//#define I2 sizeof(signed short)
#define I4 sizeof(signed long)
//#define X1 sizeof(unsigned char)


typedef enum { PR_OK = 0, PR_FIN, PR_ERR_NO_CAR_INI, PR_ERR, PR_ERR_SENT, 
			   PR_ERR_CAR_STATUS, PR_ERR_HORARIO, PR_ERR_CAR_LATITUD, 
			   PR_ERR_LATITUD, PR_ERR_CAR_LONGITUD, PR_ERR_LONGITUD, 
			   PR_ERR_CAL_FIX, PR_ERR_CANT_SAT, PR_ERR_ELEVACION, 
			   PR_ERR_CAR_METRO, PR_ERR_HDOP, PR_ERR_SEP_GEO, PR_ERR_FECHA,
		       PR_ERR_MES, PR_ERR_ANIO, PR_ERR_DIA, PR_ERR_ZONA_HORARIA,
			   PR_ERR_ARCHIVO, PR_ERR_PTR_NULL, PR_ERR_CLASE, 
			   PR_ERR_ID, PR_ERR_LARGO, PR_ERR_SUM_VER, PR_ERR_VALID_FLAGS, 
			   PR_ERR_VALID_FIX, PUE_NOT, PR_DEBUG /* Lo agregue por un warnign que habia*/ } procesar_t;

typedef unsigned char uchar;

signed long u1_to_i4 (uchar *u1);

unsigned short u1_to_u2 (uchar *u1);

procesar_t procesar_ubx (FILE **pf_in, gps_t *ubx_ptr);

procesar_t _procesar_ubx (FILE **pf_in, gps_t *ubx_ptr);

void check_sum (uchar payload[], size_t long_payload, uchar *ck_a, uchar *ck_b);

#endif
