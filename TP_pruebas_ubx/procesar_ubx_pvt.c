#include "procesar_ubx_pvt.h"


procesar_ubx_status _procesar_ubx_pvt (FILE **pf_in, gps_t * pvt_ptr)  {
	size_t largo = 0;
	uchar payload[B_MAX_CANT_SENT];
	uchar  aux, ck_a, ck_b;
	
	if (!*pf_in || !pf_in || !pvt_ptr) 
		return PUE_PTRNUL;
	
	if (fread(&aux, U1, 1, *pf_in) != 1)
		return PUE_LEC;
	largo |= aux;
	if (fread(&aux, U1, 1, *pf_in) != 1)
		return PUE_LEC;
	largo = (largo<<SHIFT_U1) | aux;
	
	if (largo != LARGO_PAYLOAD_PVT)
		return PUE_LARGO;
	                                       // El mas dos esta para cargar el Check sum !
	if (fread(payload, U1, LARGO_PAYLOAD_PVT + 2, *pf_in) != LARGO_PAYLOAD_PVT + 2) {
		return PUE_LEC;
	}
	
	// Se cargan los datos.
	// Solo se verifican los flags 
	pvt_ptr->fecha.anio = u1_to_u2(payload + 4);
	pvt_ptr->fecha.mes = payload[6];
	pvt_ptr->fecha.dia = payload[7];
	
	pvt_ptr->horario.hora = payload[8];
	pvt_ptr->horario.minuto = payload[9];
	pvt_ptr->horario.segundos = payload[10];
	
	// Aux = validity flags;
	aux = payload[11];
	// Se verifica que esten las ultimas 4 en 1,
	if (aux | 0x0F)
		return PUE_VALID_FLAGS;
	
	aux = payload[21];
	
	if (aux | 0x01)
		return PUE_VALID_FIX;
	
	pvt_ptr->cant_satelites = payload[23];
	
	pvt_ptr->longitud = (float) u1_to_i4(payload + 24);
	pvt_ptr->latitud = (float) u1_to_i4(payload + 28);
	pvt_ptr->sep_geo = (float) u1_to_i4(payload + 32);
	pvt_ptr->elevacion = (float) u1_to_i4(payload + 36);
	
	check_sum(payload, LARGO_PAYLOAD_PVT, &ck_a, &ck_b);
	
	ck_a += B_CLASE;
	ck_b += ck_a;
	
	ck_a += ID_PVT;
	ck_b += ck_a;
	
	if (ck_a != payload[LARGO_PAYLOAD_PVT + 1])
		return PUE_CKSUM_A;
	if (ck_b != payload[LARGO_PAYLOAD_PVT + 2])
		return PUE_CKSUM_B;
	
	return PU_OK;
}

