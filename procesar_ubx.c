#include "procesar_ubx.h"

#include <stdio.h>

#include "procesar_ubx_posllh.h"
#include "procesar_ubx_timtos.h"
#include "procesar_ubx_pvt.h"

procesar_t procesar_ubx (FILE **pf_in, gps_t *ubx_ptr) {
	uchar aux;
	
	if (!(*pf_in) || !pf_in || !ubx_ptr) {
		return PR_ERR_PTR_NULL;
	}
	while (fread(&aux, U1, 1, *pf_in) == 1) {
		if (aux == B_SYNC1) {
			if (fread(&aux, U1, 1, *pf_in) != 1) { 
				break;
			}
			if (aux == B_SYNC2) {
				return _procesar_ubx(pf_in, ubx_ptr);
			}
		}
	}
	if (ferror(*pf_in)) { 
		return PR_ERR_ARCHIVO;
	}
	return PR_FIN; 
}

procesar_t _procesar_ubx (FILE **pf_in, gps_t *ubx_ptr) {
	uchar aux;
	
	if (!(*pf_in) || !pf_in) { 
		return PR_ERR_PTR_NULL;
	}

	if (fread(&aux, U1, 1, *pf_in) != 1) { 
		return PR_ERR_ARCHIVO;
	}
	
	// Como las clases de pvt y posllh son iguales no se verifican las dos
	if ((aux != CLASE_PVT) && (aux != CLASE_TIMTOS)) { 
		return PR_ERR_CLASE;
	}

	if (fread(&aux, U1, 1, *pf_in) != 1) { 
		return PR_ERR_ARCHIVO;
	}

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
			return PR_ERR_ID;
	}
}

signed long u1_to_i4 (uchar *u1) {

	signed long i4 = 0;
	
	i4 |= *u1;
	i4 |= (*(u1 + 1) << SHIFT_U1);
	i4 |= (*(u1 + 2) << SHIFT_U1 * 2);
	i4 |= (*(u1 + 3) << SHIFT_U1 * 3);
	
	return i4;
}

unsigned short u1_to_u2 (uchar *u1) {

	unsigned short u2 = 0;
	
	u2 |= *u1;
	u2 |= (*(u1 + 1) << SHIFT_U1);
	
	return u2;
}


void inicializar_estructura (gps_t *gps_ptr) {
	gps_ptr->horario.hora = gps_ptr->horario.minuto = gps_ptr->horario.segundos = 0;
	gps_ptr->fecha.anio = gps_ptr->fecha.mes = gps_ptr->fecha.dia = 0;
	gps_ptr->latitud = 0;
	gps_ptr->longitud = 0;
	gps_ptr->sep_geo = 0;
	gps_ptr->hdop = 0;
	gps_ptr->elevacion = 0;
	gps_ptr->calidad_fix = 0;
	gps_ptr->cant_satelites = 0;
}
