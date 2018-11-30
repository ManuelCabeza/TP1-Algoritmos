#ifndef MAIN_H
#define MAIN_H

#define MAX_LONG_NOMBRE 100

typedef struct {
	int dia;
	int mes;
	int anio;
} fecha_t;

 
typedef struct {
	int hora;
	int minuto;
	float segundos;
} horario_t;

typedef struct {
	char nombre[MAX_LONG_NOMBRE];
	horario_t horario;
	fecha_t fecha;
} metadata_t;

typedef enum {INVALIDO, GPS, DGPS, PPS, RTK, FRTK, ESTIMADA, MANUAL, SIMULACION} cal_fix;

typedef struct {
	fecha_t fecha;
	horario_t horario;
	float latitud;
	float longitud;
	cal_fix calidad_fix;
	int cant_satelites;
	float hdop;
	float elevacion;
	float sep_geo;
} gps_t;

#endif
