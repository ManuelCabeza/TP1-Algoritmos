#ifndef LISTA_H
#define LISTA_H

#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct nodo {
	void * dato;
	struct nodo * sig;
};

typedef struct nodo * Lista;
typedef struct nodo Nodo;

//void imprimir_Lista(Lista * lista, int i );

bool lista_crear (Lista * lista);
/* Recibe un puntero donde crea la lista. 
 * Devuelve distinto de 0 (True) cuando puede hacerlo y un 0 cuando se le pasa como argumento un NULL
 */

bool lista_esta_vacia (Lista l);
/* Verifica si la lista que se pasa como argumento esta vacia.
 * Devuelve true si lo esta, y un false si no.
 */

Nodo *crear_nodo (void *dato, void *(*clonar)(void *));
/* Recibe como primer argumento un puntero al dato que desea crear en el nodo. 
 * Como segundo recibe un puntero a una funcion con el siguiente prototipo:
 * void *(*clonar)(void *) donde recibe el dato que desea copiar en el nodo cnlaksnakldakl
 * Devuelve NULL en caso que se haya producido un error en algunos de los 
 * pasos de la funcion. Caso contrario, devuelve el nodo creado.
 */

bool lista_insertar_primero (Lista *l, void *dato, void *(*clonar)(void *)); 
/* 0 si ok !0 si mal
 *
 *
 */
/*NO ESTOY TAN SEGURA*/
bool lista_insertar_ultimo (Lista *l, void *dato, void *(*clonar)(void *));
/* Recibe como primer argumento un puntero al ultimo nodo de la lista, como 
 * segundo el tipo de dato que desea insertar y por ultimo un puntero a una 
 * funcion que clona el dato que recibe por parametro y lo devuelve por
 * nombre, para poder cargarlo en el dato.
 * Devuelve un 0 si mal !0 si bien
 */

void destruir_nodo (struct nodo **pnodo, void (*destructor)(void *));
/* 
 *
 *
 */

void * liberar_lista (Lista *lista, void(*destructor)(void *));
/* Recibe como argumento la lista y un puntero a una funcion del siguiente 
 * prototipo: void (*destructor)(void *) donde recibe el dato que se desea 
 * liberar. 
 */
 

void * retornar_dato(Lista *lista, size_t i);

size_t cantidad_datos(Lista *lista); 

#endif
