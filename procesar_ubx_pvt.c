#include "procesar_ubx_pvt.h"

#include <stdio.h>

procesar_t _procesar_ubx_pvt (FILE **pf_in, gps_t *pvt_ptr) {

	size_t largo = 0;
	uchar payload[B_MAX_CANT_SENT];
	uchar  aux, ck_a = 0, ck_b = 0;
	
	ck_a += CLASE_PVT;
	ck_b += ck_a;
	
	ck_a += ID_PVT;
	ck_b += ck_a;
	
	if (!*pf_in || !pf_in || !pvt_ptr) { 
		return PR_ERR_PTR_NULL;
	}

	if (fread(&aux, U1, 1, *pf_in) != 1) { 
		return PR_ERR_ARCHIVO;
	}
	largo |= aux;
	ck_a += aux;
	ck_b += ck_a;

	if (fread(&aux, U1, 1, *pf_in) != 1) { 
		return PR_ERR_ARCHIVO;
	}
	ck_a += aux;
	ck_b += ck_a;
	
	largo |= aux << SHIFT_U1;
		
	if (largo != LARGO_PAYLOAD_PVT) { 
		return PR_ERR_LARGO;
	}                                     
	if (fread(payload, U1, LARGO_PAYLOAD_PVT, *pf_in) != LARGO_PAYLOAD_PVT) {
		return PR_ERR_ARCHIVO;
	}
	
	// Se cargan los datos. Solo se verifican losbyte valid y flags
	pvt_ptr->fecha.anio = u1_to_u2(payload + 4);
	
	if (((pvt_ptr->fecha.mes = payload[6]) < RANGO_MES_MIN) && (pvt_ptr->fecha.mes > RANGO_MES_MAX)) { 
		return PR_ERR_MES;
	}	
	if (((pvt_ptr->fecha.dia = payload[7]) < RANGO_DIA_MIN) && (pvt_ptr->fecha.dia > RANGO_DIA_MAX)) { 
		return PR_ERR_DIA;
	}
	if (((pvt_ptr->horario.hora = payload[8]) < RANGO_HORA_MIN) && (pvt_ptr->horario.hora > RANGO_HORA_MAX)) { 
		return PR_ERR_DIA;
	}
	if (((pvt_ptr->horario.minuto = payload[9]) < RANGO_MES_MIN) && (pvt_ptr->horario.minuto > RANGO_MES_MAX)) { 
		return PR_ERR_MIN;
	}	
	if (((pvt_ptr->horario.segundos = payload[10]) < RANGO_SEGUNDO_MIN) && (pvt_ptr->horario.segundos > RANGO_SEGUNDO_MAX)) { 
		return PR_ERR_SEG;
	}
	// Aux = validity flags;
	aux = payload[11];
	// Se verifica que esten las ultimas 4 en 1,
	if (!(aux & MASCARA_VALID)) { 
		return PR_ERR_VALID_FLAGS;
	}
	aux = payload[21];
 	if (aux & MASCARA_FLAGS) { 
		return PR_ERR_VALID_FIX;
	}
	pvt_ptr->cant_satelites = payload[23];
	
	pvt_ptr->longitud = (float) u1_to_i4(payload + 24);
	pvt_ptr->latitud = (float) u1_to_i4(payload + 28);
	pvt_ptr->sep_geo = (float) u1_to_i4(payload + 32);
	pvt_ptr->elevacion = (float) u1_to_i4(payload + 36);
	
	for (int i = 0; i < LARGO_PAYLOAD_PVT ; i++ ) {
		ck_a += payload[i];
		ck_b += ck_a;
	}
	
	if (fread(payload, U1, 2, *pf_in) != 2) {
		return PR_ERR_ARCHIVO;
	}
	
	//printf("ck_a = %u %x, Checksum A = %u %x\n", ck_a, ck_a, payload[0], payload[0 ]);
	//printf("ck_b = %u %x, Checksum B = %u %x\n", ck_b, ck_b, payload[1], payload[1]);
	
	if ((ck_a != payload[0]) || ck_b != payload[1]) { 
		return PR_ERR_SUM_VER;
	}

	return PR_OK;
}

