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
#include <string.h>

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
	int num_opciones = 8, seleccion = -1, faccion;
	char nombre[LONG_NOM], res;
	
	// Fecha actual
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	// Listas/usuarios
	Lista_Usuarios *lista=CrearLista_Usuarios();;
	Usuario *usuario;
	Date fecha_sub;
	fecha_sub.year = tm.tm_year + 1900;	
	fecha_sub.month = tm.tm_mon + 1;
	fecha_sub.day = tm.tm_mday;
	
	
	// Programa
	do
	{
		generar_menu_usuarios(num_opciones + 1, &seleccion);
		switch (seleccion)
		{
			case 1:
				printf("Introduce el nombre del usuario: ");
				scanf(" %s", &nombre);
				if (Buscar_en_Lista_Usuarios(lista, nombre)){
					printf("El usuario %s ya existe.",nombre);
					pulsa_cont();
					break;
				}
				printf("Se ha suscrito hoy? (s/n): ");
				scanf(" %c", &res);
				if (res != 's'){
					do {
						printf("Introduce la fecha de suscripcion (dd/mm/aaaa): ");
						scanf(" %d/%d/%d", &fecha_sub.day, &fecha_sub.month, &fecha_sub.year);
					} while ((fecha_sub.day < 1 || fecha_sub.day > 31) || (fecha_sub.month < 1 || fecha_sub.month > 12));
				}
				do {
					printf("Introduce la faccion del usuario (1 = Aire, 2 = Agua, 3 = Fuego, 4 = Tierra): ");
					scanf(" %d", &faccion);
				} while (faccion < 1 || faccion > Numero_Facciones());
				usuario = Nuevo_Usuario(nombre, fecha_sub, --faccion); 				
				clear();
				Mostrar_Usuario(usuario);
				Enlistar(lista, usuario);
				pulsa_cont();
				break;
				
			case 2:
				Cargar_Lista_Usuarios(lista);
								pulsa_cont();
				break;
			
			case 3:
				Guardar_Lista_Usuarios(lista);
								pulsa_cont();
				break;
				
			case 4:
				printf("Introduce el nombre del usuario: ");
				scanf(" %s", &nombre);
				usuario=Buscar_en_Lista_Usuarios(lista, nombre);
				Mostrar_Usuario(usuario);
				pulsa_cont();
				break;
				
			case 5:
				MostrarLista_Usuarios(lista);
				pulsa_cont();
				break;
				
			case 6:
				printf("Introduce el nombre del usuario: ");
				scanf(" %s", &nombre);
				usuario=Buscar_en_Lista_Usuarios(lista, nombre);
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
				
			case 7:
				printf("Introduce el nombre del usuario: ");
				scanf(" %s", &nombre);
				usuario=Buscar_en_Lista_Usuarios(lista, nombre);
				Resub(usuario);
				Mostrar_Usuario(usuario);
				pulsa_cont();
				break;
				
			case 8:
				Guardar_Lista_Usuarios(lista);
				VaciarLista_Usuarios(lista);
				free(lista);
				break;
		}
	} while (seleccion != num_opciones);
	return 0;
}


void generar_menu_usuarios(int num_op, int *seleccion)
{
	int i;
	char *opciones[num_op];
	opciones[0] = "Menu de Usuarios:\n";
	opciones[1] = "1 - Insertar un nuevo Usuario\n";
	opciones[2] = "2 - Cargar lista\n";
	opciones[3] = "3 - Guardar lista\n";
	opciones[4] = "4 - Comprobar si un Usuario esta en la lista\n";
	opciones[5] = "5 - Mostrar lista\n";
	opciones[6] = "6 - Cambiar faccion\n";
	opciones[7] = "7 - Resub\n";
	opciones[8] = "8 - Salir del programa\n";

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

