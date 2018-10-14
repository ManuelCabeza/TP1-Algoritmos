#include <time.h>
#include <stdio.h>
#include <stdlib.h>


int main(void) {

    char aux[1900];
    
    time_t tiempo; //askskaksjd tiem_t
    struct tm *fecha; //es una estructura tm
    tiempo = time(NULL); //me devuelve la cantidad de segundo desde la espoca unix en formato time_t
    fecha = localtime(&tiempo); //agarra los segundos jfalsjaisjdoaij, y los traduce a la hs argentina indicada por
    //el sistema operativo de mi compu. me devuelve la estructura tm que tiene los campos  chotos.


    strftime(aux,1900,"Hoy es FUCKING %d DE FUCKING %m %Y seg :%S  min: %M, hs: %H", fecha); //MOdifico NOOO HAGO UN PRINTF CON LOS CAMPOS
    printf("%s\n", aux);
    strftime(aux,1900,"%Y-%m-%dT%H:%M:%SZ", fecha);
    printf("%s", aux);
    
    return EXIT_FAILURE;
}
