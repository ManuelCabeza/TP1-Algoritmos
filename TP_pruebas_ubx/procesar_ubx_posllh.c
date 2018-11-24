#include "procesar_ubx_posllh.h"


procesar_ubx_status _procesar_ubx_posllh (FILE *pf_aux, FILE **pf)  {
	uchar aux_a, aux_b;
	unsigned int i_aux;
	unsigned long l_aux;
	signed long ls_aux;
	
	if (fread(&i_aux, U2, 1, *pf) != 1)
		return PUE_LEC;		
	
	if (i_aux != LARGO_PAYLOAD_POSLLH) 
		return PUE_LARGO;
	
	if (fread(&l_aux, U4, 1, *pf) != 1)
		return PUE_LEC;	
	//l_aux = primer campo del ubx
	
	if (fread(&ls_aux, I4, 1, *pf) != 1)
		return PUE_LEC;	
	//ls_aux = segundo campo del ubx
	
	if (fread(&ls_aux, I4, 1, *pf) != 1)
		return PUE_LEC;	
	//ls_aux = terder campo del ubx
	
	if (fread(&ls_aux, I4, 1, *pf) != 1)
		return PUE_LEC;	
	//ls_aux = cuarto campo del ubx
	
	if (fread(&ls_aux, I4, 1, *pf) != 1)
		return PUE_LEC;	
	//ls_aux = quinto campo del ubx
	
	if (fread(&l_aux, U4, 1, *pf) != 1)
		return PUE_LEC;	
	//l_aux = sexto campo del ubx
	
	if (fread(&l_aux, U4, 1, *pf) != 1)
		return PUE_LEC;	
	//l_aux = 7° campo del ubx
	
	// Lee los caracteres para la suma de verificacion
	if ((fread(&aux_a, U1, 1, *pf) != 1) || (fread(&aux_b, U1, 1, *pf) != 1))
		return PUE_LEC;
	
	if(!check_sum(aux_a, aux_b, pf_aux))
		return PUE_CKSUM;
		
	return PU_OK;
}
