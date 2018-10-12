#define MAX_LONG_SEN 85
#define CANT_ARGUMENTOS 14
#define MAX_VALOR_FIX 8
#define MIN_VALOR_FIX 0
#define MAX_VALOR_CANT_SATELITES 12
#define MIN_VALOR_CANT_SATELITES 0
#define CARACTER_NORTE 'n'
#define CARACTER_SUR   's'
#define CARACTER_ESTE  'e'
#define CARACTER_OESTE 'w'
#define CARACTER_UNIDAD 'm'
#define CARACTER_INICIO_COMANDO '$' 
#define CARACTER_SEPARACION_COMANDO ','
#define CARACTER_SUMA_VER '*'

typedef struct {
	float horario;
	float latitud;
	float longitud;
	int calidad_fix;
	int cant_satelites;
	float hdop;
	float elevacion;
	float sep_geo;
} gga;

typedef enum {PR_OK, PR_ERR, PR_FIN} procesar_t;

//Funcion que recibe una sentencia y calcula la XOR de todos los bytes hasta llegar a un caracter de corte
unsigned char nmea_verificar_suma(const char * sentencia);

/*La funcion devuelve:
 * PR_FIN si no hay nada mas que leer en el archivo
 * PR_ERR si el formato de una linea de datos no esta bien
 * PR_OK si el dato de una linea fue procesado correctamente. */
procesar_t procesarNMEA(gga * ggaptr);