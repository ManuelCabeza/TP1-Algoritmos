#include "procesar_ubx_timtos.h"

procesar_t _procesar_ubx_timtos (FILE **pf_in, gps_t * timtos_ptr) {
	size_t largo = 0;
	uchar payload[B_MAX_CANT_SENT];
	uchar aux, ck_a = 0, ck_b = 0;
		
	if (!*pf_in || !pf_in || !timtos_ptr) 
		return PR_ERR_PTR_NULL;
	
	if (fread(&aux, U1, 1, *pf_in) != 1)
		return PR_ERR_ARCHIVO;
	largo |= aux;
	
	ck_a += CLASE_TIMTOS;
	ck_b += ck_a;
	
	ck_a += ID_TIMTOS;
	ck_b += ck_a;
	
	ck_a += aux;
	ck_b += ck_a;
	
	if (fread(&aux, U1, 1, *pf_in) != 1)
		return PR_ERR_ARCHIVO;
	largo |= aux << SHIFT_U1;
	
	ck_a += aux;
	ck_b += ck_a;
	
	if (largo != LARGO_PAYLOAD_TIMTOS)
		return PR_ERR_LARGO;
	
	if (fread(payload, U1, LARGO_PAYLOAD_TIMTOS, *pf_in) != LARGO_PAYLOAD_TIMTOS) {
		return PR_ERR_ARCHIVO;
	}
	
	// No se verifica nada, solo se cargan los datos.
	
	timtos_ptr->fecha.anio = u1_to_u2(payload + 8);
	timtos_ptr->fecha.mes = payload[10];
	timtos_ptr->fecha.dia = payload[11];
	
	timtos_ptr->horario.hora = payload[12];
	timtos_ptr->horario.minuto = payload[13];
	timtos_ptr->horario.segundos = payload[14];
	
	// Se ignora todo lo demas
	for (int i = 0; i < LARGO_PAYLOAD_TIMTOS ; i++ ) {
		ck_a += payload[i];
		ck_b += ck_a;
	}
	
	if (fread(payload, U1, 2, *pf_in) != 2) {
		return PR_ERR_ARCHIVO;
	}
	
	if ((ck_a != payload[0 ]) || ck_b != payload[1])
		return PR_ERR_SUM_VER;
	
	return PR_OK;
}
