/*
Autor: Luis Jose Llamas Perez
Fecha (dd/mm/yyyy): 
Descripcion: 
*/

// Cabezera

// Librerias
// sistema
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// propias
#include "./usuarios.h"
#include "./lista-usuarios.h"

// Constantes
#define clear() printf("\033[H\033[J")

// Tipos

void generar_menu_usuarios(int num_op, int *seleccion);
void pulsa_cont();

int main()
{
	// Variables
	int num_opciones = 6, seleccion = -1, faccion = 0;
	char nombre[15], res;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	Lista_Usuarios *lista=CrearLista_Usuarios();;
	Usuario *usuario;
	Date fecha_sub;
	fecha_sub.year = tm.tm_year + 1900;	
	fecha_sub.month = tm.tm_mon + 1;
	fecha_sub.day = tm.tm_mday;
	
	// Programa
	while (seleccion != num_opciones)
	{
		generar_menu_usuarios(num_opciones + 1, &seleccion);
		switch (seleccion)
		{
		// Creacion Usuarios
		case 1:
			printf("Introduce el nombre del usuario: ");
			scanf(" %s", &nombre);
			if (!(Buscar_en_lista_doblelig(lista, nombre))){
				printf("Se ha suscrito hoy? (s/n): ");
				scanf(" %c", &res);
				if (res != 's'){
					do {
					printf("Si solo quieres cambiar el dia, introduce solo el dia.\n");
					printf("Introduce la fecha de suscripcion (dd/mm/aaaa): ");
					scanf(" %d/%d/%d", &fecha_sub.day, &fecha_sub.month, &fecha_sub.year);
					} while ((fecha_sub.day < 1 || fecha_sub.day > 31) || (fecha_sub.month < 1 || fecha_sub.month > 12));
				}
				do {
					printf("Introduce la faccion del usuario (1 = Aire, 2 = Agua, 3 = Fuego, 4 = Tierra): ");
					scanf(" %d", &faccion);
				} while (faccion < 1 || faccion > 4);
				clear();
				usuario = Nuevo_Usuario(nombre, fecha_sub, --faccion);
				Mostrar_Usuario(usuario);
				Enlistar(lista, usuario);
			} else {
				printf("El usuario %s ya existe.",nombre);
			}
			pulsa_cont();
			break;
		case 2:
			printf("Introduce el nombre del usuario: ");
			scanf(" %s", &nombre);
			usuario=Buscar_en_lista_doblelig(lista, nombre);
			if (usuario != NULL){
				Desenlistar(lista, usuario);
				printf("Se ha eliminado al usuario %s",nombre);
			} else {
				printf("El usuario %s no existe.",nombre);
			}
			pulsa_cont();
			break;
		case 3:
			printf("Introduce el nombre del usuario: ");
			scanf(" %s", &nombre);
			usuario=Buscar_en_lista_doblelig(lista, nombre);
			Mostrar_Usuario(usuario);
			pulsa_cont();
			break;
		case 4:
			MostrarLista_Usuarios(lista);
			pulsa_cont();
			break;
		case 5:
			printf("Introduce el nombre del usuario: ");
			scanf(" %s", &nombre);
			usuario=Buscar_en_lista_doblelig(lista, nombre);
			if (usuario != NULL){
				do {
					printf("Introduce la faccion del usuario (1 = Aire, 2 = Agua, 3 = Fuego, 4 = Tierra): ");
					scanf(" %d", &faccion);
				} while (faccion < 1 || faccion > 4);
				Cambiar_Faccion_Usuario(usuario, --faccion);
				printf("%s ahora pertenece a %s",nombre, usuario->facciones.faccion_actual);
			} else {
				printf("El usuario %s no existe.",nombre);
			}
			pulsa_cont();
			break;
		case 6:
			VaciarLista_Usuarios(lista);
			break;
		}
	}
	return 0;
}


void generar_menu_usuarios(int num_op, int *seleccion)
{
	int i;
	
	char *opciones[num_op];
	opciones[0] = "Menu de Usuarios:\n";
	opciones[1] = "1 - Insertar un nuevo Usuario\n";
	opciones[2] = "2 - Eliminar un Usuario\n";
	opciones[3] = "3 - Comprobar si un Usuario esta en la lista\n";
	opciones[4] = "4 - Mostrar lista\n";
	opciones[5] = "5 - Cambiar faccion\n";
	opciones[6] = "6 - Salir del programa\n";

	clear();
	for (i = 0; i < num_op; i++)
	{
		printf("%s", opciones[i]);
	}

	printf("Introduce el numero de la opcion: ");
	scanf(" %d", seleccion);
	clear();
}

// Miscelanea
void pulsa_cont(){
	int c;
	while ((c = getchar()) != '\n' && c != EOF) { }
	printf("\nPulsa una tecla para continuar\n");
	getchar();
}

