#include "procesar_ubx.h"
#include "procesar_ubx_posllh.c"
#include "procesar_ubx_timtos.c"
#include "procesar_ubx_pvt.c"


procesar_ubx_status procesar_ubx (FILE **pf_in, gps_t * ubx_ptr) {
	uchar aux;
	
	if (!(*pf_in) || !pf_in)
		return PUE_PTRNUL;
	
	while (fread(&aux, U1, 1, *pf_in) == 1) {
		if (aux == B_SYNC1) {
			if (fread(&aux, U1, 1, *pf_in) != 1)
				break;
			if (aux == B_SYNC2) {
				return _procesar_ubx(pf_in, ubx_ptr);
			}
		}
	}
	if (!ferror(*pf_in))
		return PUE_LEC;
	
	if (feof(*pf_in))
		return PU_FIN;
}

procesar_ubx_status _procesar_ubx (FILE **pf_in, gps_t * ubx_ptr) {
	uchar aux;
	
	if (!(*pf_in) || !pf_in)
		return PUE_PTRNUL;
		
	if (fread(&aux, U1, 1, *pf_in) != 1)
		return PUE_LEC;
	
	if (aux != B_CLASE)
		return PUE_CLASE;
	
	if (fread(&aux, U1, 1, *pf_in) != 1)
		return PUE_LEC;
	
	switch (aux) {
		case ID_TIMTOS :
			return _procesar_ubx_timtos (pf_in, ubx_ptr);	
			break;
			
		case ID_POSLLH :
			return _procesar_ubx_posllh (pf_in, ubx_ptr);	
			break;
			
		case ID_PVT :
			return _procesar_ubx_pvt (pf_in, ubx_ptr);	
			break;
			
		default :
			return PUE_ID;
	}
}

// Hace el ChkSum a lo largo de todo el Payload, aparte
// afuera de la funcion hay que agregarle la clase y Id.
void check_sum (uchar payload[], size_t long_payload, uchar * ck_a, uchar * ck_b) {
	int i;
	
	*ck_a = *ck_b = 0;
	for (i = 0; i < long_payload; i++ ) {
		*ck_a += payload[i];
		*ck_b += *ck_a;
		
	}
}

signed long u1_to_i4 (uchar *u1) {
	signed long i4 = 0;
	
	i4 |= *u1;
	i4 <<= SHIFT_U1;
	i4 |= *(u1 + 1);
	i4 <<= SHIFT_U1;
	i4 |= *(u1 + 2);
	i4 <<= SHIFT_U1;
	i4 |= *(u1 + 3);
	
	return i4;
}

unsigned short u1_to_u2 (uchar *u1) {
	unsigned short u2 = 0;
	
	u2 |= *u1;
	u2 <<= SHIFT_U1;
	u2 |= *(u1 + 1);
	u2 <<= SHIFT_U1;
	
	return u2;
}
