#include "procesar_nmea.h"
#include "procesar_nmea_zda.c"
#include "procesar_nmea_gga.c"
#include "procesar_nmea_rmc.c"

procesar_t procesar_nmea (FILE ** pf, gps_t * gps_ptr) { //El archivo abierto en rt
	char cadena[MAX_LONG_SENTENCIA];
	char * ch_ptr;
	
	if (!(fgets(cadena, MAX_LONG_SENTENCIA, *pf))) {
		return PR_FIN; //Ver si esta bien esto
	}
	ch_ptr = cadena;
	
	if (* ch_ptr != CARACTER_INICIO_COMANDO) {
		return PR_ERR_NO_CAR_INI;
	}
	ch_ptr += 3; // Muevo el puntero para que apunte a la primer 'x' de "$GPxxx,"
	
	// Verifico que tipo de sentencia es.
	if (!strncmp(ch_ptr, SENT_GGA, LONG_SENT_GGA)) {
		return procesar_nmea_gga(gps_ptr, ch_ptr, cadena);
	}
	else if (!strncmp(ch_ptr, SENT_ZDA, LONG_SENT_ZDA)) {
		return procesar_nmea_zda(gps_ptr, ch_ptr, cadena);
	}
	else if (!strncmp(ch_ptr, SENT_RMC, LONG_SENT_RMC)) {
		return procesar_nmea_rmc(gps_ptr, ch_ptr, cadena);
	}
	return PR_ERR_SENT;
}


unsigned char nmea_verificar_suma(const char * sentencia) {

	unsigned char suma = 0;

	while ( * sentencia != CARACTER_SUMA_VER) {
		suma ^= *sentencia++;
	}
	return suma;
}

void procesar_horario (horario_t * horario_ptr, float horario) {

	horario_ptr->minuto = (horario - 10000 * (horario_ptr->hora = horario / 10000)) / 100;
	horario_ptr->segundos = horario - 100 * ((int)horario / 100);
}

void procesar_fecha (fecha_t * fecha_ptr, long fecha) {
	
	fecha_ptr->mes = fecha / 100 - 100 * (fecha_ptr->dia = fecha / 10000);
	fecha_ptr->anio = (fecha & 0xFF); //NO SE SI FUNCIONA
}

void imprimir_estructura (gps_t gps_ptr) {
	printf("Hora: %i, Minuto: %i, Segundo: %f\n", gps_ptr.horario.hora, gps_ptr.horario.minuto, gps_ptr.horario.segundos );
	printf("Año: %i, Mes: %i, Día: %i\n", gps_ptr.fecha.anio, gps_ptr.fecha.mes, gps_ptr.fecha.dia);
	printf("Latitud: %f\n", gps_ptr.latitud);
	printf("Longitud: %f\n", gps_ptr.longitud);
	printf("Elevacion: %f\n", gps_ptr.elevacion);
	printf("SepGeo: %f\n", gps_ptr.sep_geo);
	printf("HDop: %f\n", gps_ptr.hdop);
	printf("Calidad Fix: %i\n", gps_ptr.calidad_fix);
	printf("Cantidad satelites: %i\n", gps_ptr.cant_satelites);
}


int main(void) {
	FILE * pf;
	pf = fopen("prueba_zda.txt","rt");
	gps_t estructura;
	procesar_t pr;
	
	while ((pr = procesar_nmea( &pf, &estructura)) != PR_FIN) {
		switch (pr) {
			case PR_OK :
				puts("OK");
				imprimir_estructura(estructura);
				break;
			case PR_ERR_NO_CAR_INI :
				puts("Error no caracter inicial");
				break;
			case PR_ERR :
				puts("Error");
				break;
			case PR_ERR_SENT :
				puts("Error, sentencia no válida");
				break;
			case PR_ERR_SUM_VER :
				puts("Error suma de verificaión");
				break;
			case PR_ERR_CAR_STATUS :
				puts("Error en caracter status");
				break;
			case PR_ERR_HORARIO :
				puts("Error en horario");
				break;
			case PR_ERR_CAR_LATITUD :
				puts("Error en caracter latitud");
				break;
			case PR_ERR_LATITUD :
				puts("Error en latitud");
				break;
			case PR_ERR_CAR_LONGITUD :
				puts("Error en caracter longitud");
				break;
			case PR_ERR_LONGITUD :
				puts("Error en longitud");
				break;
			case PR_ERR_CAL_FIX :
				puts("Error en calidad fix");
				break;
			case PR_ERR_CANT_SAT :
				puts("Error en cantidad satelites");
				break;
			case PR_ERR_ELEVACION :
				puts("Error elevacion");
				break;
			case PR_ERR_CAR_METRO :
				puts("Error en caracter metro");
				break;
			case PR_ERR_HDOP :
				puts("Error en Hdop");
				break;
			case PR_ERR_SEP_GEO :
				puts("Error en SepGeo");
				break;
			case PR_ERR_FECHA :
				puts("Error en fecha");
				break;
			case PR_ERR_DIA :
				puts("Error en dia");
				break;
			case PR_ERR_MES :
				puts("Error en mes");
				break;
			case PR_ERR_ANIO :
				puts("Error en anio");
				break;
			case PR_ERR_ZONA_HORARIA :
				puts("Error en zona horaria");
				break;
			default :
				puts("default?");
				break;
		}
	}
	
	fclose (pf);
	return 0;
}






