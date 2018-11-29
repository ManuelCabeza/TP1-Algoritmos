#include "procesar_ubx_timtos.h"

procesar_ubx_status _procesar_ubx_timtos (FILE **pf_in, gps_t * timtos_ptr) {
	size_t largo = 0;
	uchar payload[B_MAX_CANT_SENT];
	uchar aux, ck_a, ck_b;
		
	if (!*pf_in || !pf_in || !timtos_ptr) 
		return PUE_PTRNUL;
	
	
	if (fread(&aux, U1, 1, *pf_in) != 1)
		return PUE_LEC;
	largo |= aux;
	if (fread(&aux, U1, 1, *pf_in) != 1)
		return PUE_LEC;
	largo = (largo<<SHIFT_U1) | aux;
	
	if (largo != LARGO_PAYLOAD_TIMTOS)
		return PUE_LARGO;
	                                       // El mas dos esta para cargar el Check sum !
	if (fread(payload, U1, LARGO_PAYLOAD_TIMTOS + 2, *pf_in) != LARGO_PAYLOAD_TIMTOS + 2) {
		return PUE_LEC;
	}
	
	// No se verifica nada, solo se cargan los datos.
	
	timtos_ptr->fecha.anio = u1_to_u2(payload + 8);
	timtos_ptr->fecha.mes = payload[10];
	timtos_ptr->fecha.dia = payload[11];
	
	timtos_ptr->horario.hora = payload[12];
	timtos_ptr->horario.minuto = payload[13];
	timtos_ptr->horario.segundos = payload[14];
	
	// Se ignora todo lo demas	
	
	check_sum(payload, LARGO_PAYLOAD_TIMTOS, &ck_a, &ck_b);
	
	ck_a += B_CLASE;
	ck_b += ck_a;
	
	ck_a += ID_TIMTOS;
	ck_b += ck_a;
	
	if (ck_a != payload[LARGO_PAYLOAD_TIMTOS + 1])
		return PUE_CKSUM_A;
	if (ck_b != payload[LARGO_PAYLOAD_TIMTOS + 2])
		return PUE_CKSUM_B;
	
	return PU_OK;
}
