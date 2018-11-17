#include "procesar_ubx.h"
#include "procesar_ubx_posllh.h"


procesar_ubx_status procesar_ubx (FILE **pf ) {
	uchar aux;
	procesar_ubx_status p_st;
	if (!(*pf) || !pf)
		return PUE_PTRNUL;
	
	while (fread(&aux, U1, 1, *pf) == 1) {
		if (aux == B_SYNC1) {
			if (fread(&aux, U1, 1, *pf) != 1)
				break;
			if (aux == B_SYNC2) {
				return p_st;
			}
		}
	}
	if (!ferror(*pf))
		return PUE_LEC;
	
	if (feof(*pf))
		return PU_FIN;
}

procesar_ubx_status _procesar_ubx (FILE **pf) {
	FILE *pf_aux = *pf; // El puntero aux se usara para la suma de verificacion
	uchar aux;
	
	if (!(*pf) || !pf)
		return PUE_PTRNUL;
		
	if (fread(&aux, U1, 1, *pf) != 1)
		return PUE_LEC;
	
	if (aux != B_CLASE)
		return PUE_CLASE;
	
	if (fread(&aux, U1, 1, *pf) != 1)
		return PUE_LEC;
	
	switch (aux) {
		case ID_TIMTOS :
			return _procesar_ubx_timtos (pf_aux, pf);	
			break;
			
		case ID_POSLLH :
			return _procesar_ubx_posllh (pf_aux, pf);	
			break;
			
		case ID_PVT :
			return _procesar_ubx_pvt (pf_aux, pf);	
			break;
			
		default :
			return PUE_ID;
	}
	
}


bool_t check_sum (uchar ck_a, uchar ck_b, FILE *pf) {
	uchar aux_a = 0, aux_b = 0, c;
	int i;
	
	while (((c = fgetc(pf)) != EOF) && c != ck_a) {
		aux_a += c;
		aux_b += aux_a;
	}
		
	if ((aux_a == ck_a) && (aux_b == ck_b))	
		return VERDADERO;
		
	return FALSO;
}



