#include "procesar_ubx_posllh.h"


procesar_t _procesar_ubx_posllh (FILE **pf_in, gps_t *pos_ptr)  {
	size_t largo = 0;
	uchar payload[B_MAX_CANT_SENT];
	uchar aux, ck_a = 0, ck_b = 0;
	
	if (!pf_in || !*pf_in || !pos_ptr) 
		return PR_ERR_PTR_NULL;
	
	if (fread(&aux, U1, 1, *pf_in) != 1)
		return PR_ERR_ARCHIVO;
	largo |= aux;
	
	ck_a += CLASE_POSLLH;
	ck_b += ck_a;
	
	ck_a += ID_POSLLH;
	ck_b += ck_a;
	
	ck_a += aux;
	ck_b += ck_a;
	
	if (fread(&aux, U1, 1, *pf_in) != 1)
		return PR_ERR_ARCHIVO;
		
	largo |= aux << SHIFT_U1;
	ck_a += aux;
	ck_b += ck_a;
	
	if (largo != LARGO_PAYLOAD_POSLLH)
		return PR_ERR_LARGO;
	
	if (fread(payload, U1, LARGO_PAYLOAD_POSLLH, *pf_in) != LARGO_PAYLOAD_POSLLH)
		return PR_ERR_ARCHIVO;
	
	pos_ptr->longitud = (float) u1_to_i4(payload + 4);
	pos_ptr->latitud = (float) u1_to_i4(payload + 8);
	pos_ptr->sep_geo = (float) u1_to_i4(payload + 12);
	pos_ptr->elevacion = (float) u1_to_i4(payload + 16);

	for (int i = 0; i < LARGO_PAYLOAD_POSLLH ; i++ ) {
		ck_a += payload[i];
		ck_b += ck_a;
	}
	
	if (fread(payload, U1, 2, *pf_in) != 2) {
		return PR_ERR_ARCHIVO;
	}
	
	if ((ck_a != payload[0]) || ck_b != payload[1])
		return PR_ERR_SUM_VER;
	
	return PR_OK;
}
