#include "procesar_ubx_posllh.h"


procesar_ubx_status _procesar_ubx_posllh (FILE **pf_in, gps_t * pos_ptr)  {
	size_t largo = 0;
	uchar payload[B_MAX_CANT_SENT];
	uchar aux, ck_a, ck_b;
	
	if (!pf_in || !*pf_in || !pos_ptr) 
		return PUE_PTRNUL;
	
	if (fread(&aux, U1, 1, *pf_in) != 1)
		return PUE_LEC;
	largo |= aux;
	largo <<= SHIFT_U1;
	
	if (fread(&aux, U1, 1, *pf_in) != 1)
		return PUE_LEC;
		
	largo |= aux;
	
	if (largo != LARGO_PAYLOAD_POSLLH)
		return PUE_LARGO;
	
	if (fread(payload, U1, LARGO_PAYLOAD_POSLLH + 2, *pf_in) != LARGO_PAYLOAD_POSLLH + 2)
		return PUE_LEC;
	
	pos_ptr->longitud = (float) u1_to_i4(payload + 4);
	pos_ptr->latitud = (float) u1_to_i4(payload + 8);
	pos_ptr->sep_geo = (float) u1_to_i4(payload + 12);
	pos_ptr->elevacion = (float) u1_to_i4(payload + 16);

	check_sum(payload, LARGO_PAYLOAD_POSLLH, &ck_a, &ck_b);
	
	ck_a += B_CLASE;
	ck_b += ck_a;
	
	ck_a += ID_POSLLH;
	ck_b += ck_a;
	
	if (ck_a != payload[LARGO_PAYLOAD_POSLLH + 1])
		return PUE_CKSUM_A;
	if (ck_b != payload[LARGO_PAYLOAD_POSLLH + 2])
		return PUE_CKSUM_B;
	
	return PU_OK;
}
