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


typedef enum {PR_OK, PR_ERR, PR_FIN} procesar_t;

unsigned char nmea_verificar_suma(const char * sentencia);
procesar_t procesarNMEA(gga * ggaptr);
