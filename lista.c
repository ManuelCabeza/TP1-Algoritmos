#include "lista.h"
/*
void imprimir_Lista(Lista * lista, int i ) {
	Nodo * aux;
	if (!lista) {
		puts("La lista está vacía");
	} else {
		puts("La lista es: ");
		aux = lista;
		do {
			printf("%i -> ", i++);
			aux = aux->sig;
		} while (aux != NULL);
		putchar('\n');
	}
}
*/
bool lista_crear (Lista *lista) {
    
    if (!lista) {
        return false;
    }
    *lista = NULL;
    return true;
}

bool lista_esta_vacia(Lista l) {
    return l == NULL;
}

Nodo *crear_nodo (void *dato_clonar, void *(*clonar)(void *)) {
	Nodo *aux;
    if (!dato_clonar || !clonar) {
        return NULL;
    }

    if (!(aux = (Nodo *) malloc(sizeof(Nodo)))) {
        return NULL;
    }

    if (!(aux->dato = (*clonar)(dato_clonar))) {
        free(aux);
        return NULL;
    }
    
    return aux;
}

bool lista_insertar_ultimo (Lista *l, void *dato, void *(*clonar)(void *)) {

    if (!l || !clonar || !dato) {
        return false;
    }

    if (lista_esta_vacia(*l)) {
        return lista_insertar_primero (l, dato, clonar);
    }

    return lista_insertar_ultimo (&(*l)->sig, dato, clonar);
}

bool lista_insertar_primero (Lista *l, void *dato, void *(*clonar)(void *)) {

    struct nodo * aux;

    if (!l || !dato || !clonar) {
        return false;
    }

    aux = crear_nodo (dato, clonar);

    if (!aux) {
        return false;
    }
    aux->sig = *l;
    *l = aux;

    return true;
}

//struct nodo = Nodo -> SI
void destruir_nodo(Nodo **ptr_nodo, void (*destructor)(void *)) {
    
    void *dato;

    if (!ptr_nodo || !destructor || !(*ptr_nodo)) {
        return;
    }

    dato = (*ptr_nodo)->dato;

    (*destructor)(dato);

    (*ptr_nodo)->dato = NULL;
    (*ptr_nodo)->sig = NULL;

    free(*ptr_nodo);
    (*ptr_nodo) = NULL;

}
// Tiene que ser ptr por q sino da error de ISO-C
void * liberar_lista (Lista *lista, void (*destructor)(void *)) {
	Nodo *siguiente;

    if (!lista || !(*lista) || !destructor) {
        return NULL;
    } 

    siguiente = (*lista)->sig;
    destruir_nodo(lista, destructor);

    return liberar_lista(&siguiente, destructor);
}

void * retornar_dato(Lista *lista, size_t i) {
	if (i == 0)
		return (*lista)->dato;
	
	return retornar_dato(&(*lista)->sig, i - 1);
}

size_t cantidad_datos(Lista *lista) {
	size_t contador = 0;
	
	while (*lista != NULL) {
		contador++;
		lista = &((*lista)->sig);
	}	
	return contador;
}
