/*
Autor: Luis Jose Llamas Perez
Fecha (dd/mm/yyyy): 
Descripcion: 
*/

// Cabezera
// Librerias
#ifdef _WIN32 
	#include <io.h>
	int Existe_f(const char *pathname){
		return !(_access(pathname, 0));
	}
#else
	#include <unistd.h>
	int Existe_f(const char *pathname){
		return !(access(pathname, F_OK));
	}
#endif

#include "./usuarios.h"

// Constantes
#ifndef NULL
#define NULL 0
#endif

// Tipos
typedef struct Lista_Usuarios
{
	Usuario *inicio;
	Usuario *final;
	int tamano;
} Lista_Usuarios;

// Declaracion de procedimientos y funciones
Lista_Usuarios *CrearLista_Usuarios();
void DestruirLista_Usuarios(Lista_Usuarios *lista);
void Enlistar(Lista_Usuarios *lista, Usuario *usuario);
void Desenlistar(Lista_Usuarios *lista, Usuario *usuario);
Usuario *Buscar_en_Lista_Usuarios(Lista_Usuarios *lista, char *usuario);
void VaciarLista_Usuarios(Lista_Usuarios *lista);
int Es_vacia_Lista_Usuarios(Lista_Usuarios *lista);
void Guardar_Lista_Usuarios(Lista_Usuarios *lista);
void Cargar_Lista_Usuarios(Lista_Usuarios *lista);

// Operaciones con Lista-Usuario
Lista_Usuarios *CrearLista_Usuarios()
{
	Lista_Usuarios *lista = (Lista_Usuarios *)malloc(sizeof(Lista_Usuarios));
	lista->inicio = NULL;
	lista->final = NULL;
	lista->tamano = 0;
	return lista;
}

void DestruirLista_Usuarios(Lista_Usuarios *lista)
{
	if (Es_vacia_Lista_Usuarios(lista))
	{
		free(lista);
	}
	else
	{
		VaciarLista_Usuarios(lista);
		free(lista);
	}
}

void Enlistar(Lista_Usuarios *lista, Usuario *usuario)
{
	if (usuario != NULL)
	{
		lista->tamano++;
		if (Es_vacia_Lista_Usuarios(lista))
		{
			lista->inicio = usuario;
			lista->final = usuario;
		}
		else
		{
			usuario->ant = lista->final;
			lista->final->sig = usuario;
			lista->final = usuario;
		}
	}
}

void Desenlistar(Lista_Usuarios *lista, Usuario *usuario)
{
	if (usuario != NULL)
	{
		if (!(Es_vacia_Lista_Usuarios(lista)))
		{
			// Si el elemento a eliminar es el unico elemento de la lista
			if (usuario->ant == NULL && usuario->sig == NULL)
			{
				lista->inicio = NULL;
				lista->final = NULL;
				// Si el elemento a eliminar es el inicio
			}
			else if (usuario->ant == NULL)
			{
				lista->inicio = usuario->sig;
				lista->inicio->ant = NULL;
				// Si el elemento a eliminar es el final
			}
			else if (usuario->sig == NULL)
			{
				lista->final = usuario->ant;
				lista->final->sig = NULL;
				// Caso general
			}
			else
			{
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

Usuario *Buscar_en_Lista_Usuarios(Lista_Usuarios *lista, char *usuario)
{
	if (!(Es_vacia_Lista_Usuarios(lista)))
	{
		Usuario *aux_s = lista->inicio, *aux_a = lista->final;
		int i = 0;
		while ((i < ((lista->tamano / 2))) && (strcmp(aux_s->Nombre, usuario) != 0) && (strcmp(aux_a->Nombre, usuario) != 0))
		{
			aux_s = aux_s->sig;
			aux_a = aux_a->ant;
			i++;
		}
		if (strcmp(aux_s->Nombre, usuario) == 0)
		{
			return aux_s;
		}
		else if (strcmp(aux_a->Nombre, usuario) == 0)
		{
			return aux_a;
		}
	}
	return NULL;
}

void VaciarLista_Usuarios(Lista_Usuarios *lista)
{
	while (!(Es_vacia_Lista_Usuarios(lista)))
	{
		Desenlistar(lista, lista->inicio);
	}
}

int Es_vacia_Lista_Usuarios(Lista_Usuarios *lista)
{
	if (!lista->inicio)
	{
		return 1;
	}
	return 0;
}

void MostrarLista_Usuarios(Lista_Usuarios *lista)
{
	if (!(Es_vacia_Lista_Usuarios(lista)))
	{
		Usuario *aux = lista->inicio;
		printf("Numero de Usuarios: %d\n\
		\nUsuario - Faccion Actual - Puntos Disponibles\n\n",
			   lista->tamano);
		while (aux != NULL)
		{
			printf("%s - %s - %d\n", aux->Nombre, aux->facciones.faccion_actual,
				   aux->puntos.disponibles);
			aux = aux->sig;
		}
	}
	else
	{
		printf("La lista esta vacia\n");
	}
	printf("\n");
}

void Copiar_Archivo(char *dir_origen, char *dir_destino)
{
	char ch;
	FILE *f_origen = fopen(dir_origen, "r");
	if (f_origen)
	{
		FILE *f_destino = fopen(dir_destino, "w");
		if (f_destino)
		{
			while ((ch = fgetc(f_origen)) != EOF)
			{
				fputc(ch, f_destino);
			}
			fclose(f_destino);
		}
		fclose(f_origen);
	}
}

void Copia_Seguridad()
{
	int i = 0;
	char ch, origen[100], destino[100], *nom_fichero;
	nom_fichero = "./datos/datos";
	sprintf(origen, "%s%d", nom_fichero, 9);
	if (access(origen, F_OK) == 0){ remove(origen); }
	for (i = 9; i > 0; i--)
	{
		sprintf(origen, "%s%i", nom_fichero, i-1);
		sprintf(destino, "%s%i", nom_fichero, i);
		if (access(origen, F_OK) == 0){ rename(origen, destino); }
	}
	Copiar_Archivo("./datos/datos.txt", origen);
}

void Guardar_Lista_Usuarios(Lista_Usuarios *lista)
{
	if (!(Es_vacia_Lista_Usuarios(lista)))
	{
		Copia_Seguridad();
		FILE *fptr = fopen("./datos/datos.txt", "w");
		if (fptr == NULL)
		{
			printf("Error, no se ha podido guardar");
		}
		else
		{
			Usuario *usuario = lista->inicio;
			while (usuario != NULL)
			{
				Guardar_Usuario(usuario, fptr);
				usuario = usuario->sig;
			}
			fclose(fptr);
		}
	}
}

void Cargar_Lista_Usuarios(Lista_Usuarios *lista)
{
	if ((Es_vacia_Lista_Usuarios(lista)))
	{
		FILE *fptr;
		fptr = fopen("./datos/datos.txt", "r");
		if (fptr == NULL)
		{
			printf("Error, no se ha podido cargar");
		}
		else
		{
			while (!feof(fptr))
			{
				Usuario *usuario = Cargar_Usuario(fptr);
				Enlistar(lista, usuario);
			}
			fclose(fptr);
		}
	}
}
