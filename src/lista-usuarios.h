/*
Autor: Luis Jose Llamas Perez
Fecha (dd/mm/yyyy): 
Descripcion: 
*/

// Cabezera
// Librerias
#include <string.h>

// Constantes

// Tipos
#ifndef NULL
	#define NULL 0
#endif



typedef struct Lista_Usuarios{
	Usuario* inicio;
	Usuario* final;
	int	   tamano;
} Lista_Usuarios;

// Declaracion de procedimientos y funciones

// Operaciones con Lista_Usuarios
Lista_Usuarios* CrearLista_Usuarios();
void DestruirLista_Usuarios(Lista_Usuarios *lista);
void Enlistar(Lista_Usuarios *lista, Usuario *usuario);
void Desenlistar(Lista_Usuarios *lista, Usuario *usuario);
Usuario* Buscar_en_lista_doblelig(Lista_Usuarios *lista, char *usuario);
void VaciarLista_Usuarios(Lista_Usuarios *lista);
int Es_vacia_Lista_Usuarios(Lista_Usuarios *lista);
void Guardar_Lista_Usuarios(Lista_Usuarios *lista);

// FUNCIONES
// Operaciones con Lista-Usuario
Lista_Usuarios* CrearLista_Usuarios(){
	Lista_Usuarios* lista = (Lista_Usuarios *)malloc(sizeof(Lista_Usuarios));
	lista->inicio = NULL; lista->final=NULL;
	lista->tamano = 0;
	return lista;
}

void DestruirLista_Usuarios(Lista_Usuarios *lista){
	if(Es_vacia_Lista_Usuarios(lista)){
		free(lista);
	} else {
		VaciarLista_Usuarios(lista);
		free(lista);
	}	
}

void Enlistar(Lista_Usuarios *lista, Usuario *usuario){
	lista->tamano++;
	if (Es_vacia_Lista_Usuarios(lista)){
		lista->inicio = usuario;
		lista->final = usuario;
	} else {
		usuario->ant = lista->final;
		lista->final->sig = usuario;
		lista->final = usuario;
	}
}

void Desenlistar(Lista_Usuarios *lista, Usuario *usuario){
	if (usuario != NULL){
		if (!(Es_vacia_Lista_Usuarios(lista))){
			// Si el elemento a eliminar es el unico elemento de la lista
			if (usuario->ant == NULL && usuario->sig == NULL){
				lista->inicio = NULL;
				lista->final = NULL;
			// Si el elemento a eliminar es el inicio
			} else if (usuario->ant == NULL){
				lista->inicio = usuario->sig;
				lista->inicio->ant = NULL;
			// Si el elemento a eliminar es el final
			} else if (usuario->sig == NULL){
				lista->final = usuario->ant;
				lista->final->sig = NULL;
			// Caso general
			} else {
				// Elemento anterior apunta a elemento siguiente
				usuario->ant->sig = usuario->sig;
				// Elemento anterior siguiente a elemento anterior
				usuario->sig->ant = usuario->ant;
			}
			lista->tamano--;
			Borrar_Usuario(usuario);
		} 
	}
}

Usuario* Buscar_en_lista_doblelig(Lista_Usuarios *lista, char *usuario){
	if (!(Es_vacia_Lista_Usuarios(lista))){
		Usuario *aux_s, *aux_a;
		aux_s=lista->inicio;
		aux_a=lista->final;
		int i = 0;
		while ((i < ((lista->tamano / 2))) && (strcmp(aux_s->Nombre, usuario) != 0) 
				&& (strcmp(aux_a->Nombre, usuario) != 0)){
			aux_s = aux_s->sig;
			aux_a = aux_a->ant;
			i++;
		}
		if (strcmp(aux_s->Nombre, usuario) == 0){
			return aux_s;
		} else if (strcmp(aux_a->Nombre, usuario) == 0){
			return aux_a;
		}
	}
	return NULL;
}

void VaciarLista_Usuarios(Lista_Usuarios *lista){
	while (!(Es_vacia_Lista_Usuarios(lista))){
		Desenlistar(lista, lista->inicio);
	}
}

int Es_vacia_Lista_Usuarios(Lista_Usuarios *lista){
	if(!lista->inicio){
		return 1;
	}
	return 0;
}

void MostrarLista_Usuarios(Lista_Usuarios *lista){
	if (!(Es_vacia_Lista_Usuarios(lista))){
		Usuario* aux;
		int i=0;
		aux=lista->inicio;
		printf("\nNumero de Usuarios: %d\
		\nUsuario - Faccion Actual - Puntos Disponibles\n",lista->tamano);
		while (aux != NULL){
			printf("%s - %s - %d\n", aux->Nombre, aux->facciones.faccion_actual,
			aux->puntos.disponibles);
			aux = aux->sig;
			i++;
		}
	} else {
		printf("La lista esta vacia\n");
	}
	printf("\n");
}

void Guardar_Lista_Usuarios(Lista_Usuarios *lista){
	
}