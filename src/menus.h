/*
Autor: Luis Jose Llamas Perez
Fecha (dd/mm/yyyy): 
Descripcion:
*/

// Cabezera
// Librerias
#include <stdlib.h>
#ifdef _WIN32 
	inline void clear() {
    	system("cls");
    }
#else
	void clear() {
    	printf("\033[H\033[J");
    }
#endif
// Constantes
#ifndef NULL
#define NULL 0
#endif

//

// Declaracion de procedimientos y funciones
void generar_menu_principal(Lista_Usuarios *lista);
void generar_menu_usuarios(Lista_Usuarios *lista);
void generar_menu_facciones(Lista_Usuarios *lista);
void generar_menu_lista(Lista_Usuarios *lista);
void pulsa_cont();
void clear();
void Leer_Numero(int *seleccion);
void Limpiar_Buffer();

// Operaciones con Menus
void generar_menu_principal(Lista_Usuarios *lista)
{
	int i, num_op = 4, seleccion;
	char *opciones = "Menu Principal:\n\
					\n1 - Menu Usuarios\
					\n2 - Menu Facciones\
					\n3 - Menu Lista\
					\n4 - Salir del programa\n";
	do
	{
		clear();
		printf("%s\nIntroduce el numero de la opcion: ", opciones);
		Leer_Numero(&seleccion);
		clear();
		switch (seleccion)
		{
		case 1:
			generar_menu_usuarios(lista);
			break;
		case 2:
			generar_menu_facciones(lista);
			break;
		case 3:
			generar_menu_lista(lista);
			break;
		case 4:
			Guardar_Lista_Usuarios(lista);
			VaciarLista_Usuarios(lista);
			free(lista);
			break;
		}
	} while (seleccion != num_op);
}

void generar_menu_usuarios(Lista_Usuarios *lista)
{
	int i,j, num_op = 6, seleccion, faccion;
	char nombre[LONG_NOM], res;

	Usuario *usuario = NULL;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	Date fecha_sub;
	fecha_sub.year = tm.tm_year + 1900;
	fecha_sub.month = tm.tm_mon + 1;
	fecha_sub.day = tm.tm_mday;

	char *opciones = "Menu de Usuario:\n\
					\n1 - Insertar un nuevo Usuario\
					\n2 - Seleccionar Usuario\
					\n3 - Utilizar puntos\
					\n4 - Cambiar faccion\
					\n5 - Resub\
					\n6 - Volver al menu principal\n";
	do
	{
		clear();
		if (usuario){
			printf("%s\nUsuario seleccionado: %s\n\nIntroduce el numero de la opcion: ",opciones,usuario->Nombre);
		} else {
			printf("%s\nUsuario seleccionado: \n\nIntroduce el numero de la opcion: ", opciones);
		}
		Leer_Numero(&seleccion);
		clear();
		switch (seleccion)
		{
		case 1:
			printf("Introduce el nombre del usuario: ");
			scanf(" %s", &nombre);
			if (Buscar_en_Lista_Usuarios(lista, nombre))
			{
				printf("El usuario %s ya existe.", nombre);
				pulsa_cont();
				break;
			}
			printf("Se ha suscrito hoy? (s/n): ");
			scanf(" %c", &res);
			Limpiar_Buffer();
			if (res != 's')
			{
				do
				{
					printf("Introduce la fecha de suscripcion (dd/mm/aaaa): ");
					scanf(" %d/%d/%d", &fecha_sub.day, &fecha_sub.month, &fecha_sub.year);
					Limpiar_Buffer();
				} while ((fecha_sub.day < 1 || fecha_sub.day > 31) || (fecha_sub.month < 1 || fecha_sub.month > 12));
			}
			do
			{
				printf("Introduce la faccion del usuario (1 = Aire, 2 = Agua, 3 = Fuego, 4 = Tierra): ");
				Leer_Numero(&faccion);
			} while (faccion < 1 || faccion > Numero_Facciones());
			usuario = Nuevo_Usuario(nombre, fecha_sub, --faccion);
			clear();
			Mostrar_Usuario(usuario);
			Enlistar(lista, usuario);
			pulsa_cont();
			break;
		case 2:
			printf("Introduce el nombre del usuario: ");
			scanf(" %s", &nombre);
			usuario = Buscar_en_Lista_Usuarios(lista, nombre);
			if (usuario){
				printf("Usuario %s seleccionado\n");
			} else {
				printf("No existe %s.", nombre);
			}
			pulsa_cont();
			break;
		case 3:
			if (!usuario){
				printf("Introduce el nombre del usuario: ");
				scanf(" %s", &nombre);
				usuario = Buscar_en_Lista_Usuarios(lista, nombre);
				clear();
			}
			if (usuario){
				printf("%s de %s con %d puntos disponibles:\n",usuario->Nombre, usuario->facciones.faccion_actual, usuario->puntos.disponibles);
				for (i = 0; (i < (Numero_Facciones()-1) && usuario->puntos.disponibles > 0); i++){
					do {
						printf("Ataque/Defensa a %s (Puntos disponibles %d): ",Obtener_Nombre_Faccion(i), usuario->puntos.disponibles);
						Leer_Numero(&j);
					} while (j > usuario->puntos.disponibles);
					if (j > 0){
						usuario->facciones.puntos_facciones[usuario->facciones.id_faccion][i] = j;
						usuario->puntos.disponibles -= j;
					}
				}
			} else {
				printf("No existe %s.", nombre);
			}
			pulsa_cont();
			break;
		case 4:
			if (!usuario){
				printf("Introduce el nombre del usuario: ");
				scanf(" %s", &nombre);
				usuario = Buscar_en_Lista_Usuarios(lista, nombre);
				clear();
			}
			if (usuario){
				printf("Faccion actual de %s: %s\n\n",usuario->Nombre,usuario->facciones.faccion_actual);
				do {
					printf("Nueva faccion? (1 = Aire, 2 = Agua, 3 = Fuego, 4 = Tierra): ");
					Leer_Numero(&faccion);
				} while (faccion < 1 || faccion > Numero_Facciones());
				usuario->facciones.id_faccion = --faccion;
				usuario->facciones.faccion_actual = Obtener_Nombre_Faccion(faccion);
				clear();
				printf("La faccion de %s ahora es: %s",nombre,usuario->facciones.faccion_actual);
			} else {
				printf("No existe %s.", nombre);
			}
			pulsa_cont();
			break;
		case 5:
			if (!usuario){
				printf("Introduce el nombre del usuario: ");
				scanf(" %s", &nombre);
				usuario = Buscar_en_Lista_Usuarios(lista, nombre);
				clear();
			}
			if (usuario){
				printf("Dar %d puntos a %s? (s/n): ",usuario->puntos.sumador, usuario->Nombre);
				scanf(" %c", &res);
				Limpiar_Buffer();
				if (res == 's'){
					usuario->puntos.disponibles += usuario->puntos.sumador++;
					printf("\n\n%s ahora tiene %d puntos\n",usuario->Nombre, usuario->puntos.disponibles);
				}
			} else {
				printf("No existe %s.", nombre);
			}
			pulsa_cont();
			break;
		}
	} while (seleccion != num_op);
}

void generar_menu_facciones(Lista_Usuarios *lista)
{
	int i, num_op = 1, seleccion;
	char *opciones = "Menu de Facciones:\n\
					\n1 - Volver al menu principal\
					\n";
	do
	{
		clear();
		printf("%s\nIntroduce el numero de la opcion: ", opciones);
		Leer_Numero(&seleccion);
		clear();
		
		switch (seleccion)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		}
	} while (seleccion != num_op);
}

void generar_menu_lista(Lista_Usuarios *lista)
{
	int i, num_op = 2, seleccion;
	char *opciones = "Menu de Lista:\n\
					\n1 - Mostrar Lista\
					\n2 - Volver al menu principal\n";
	do
	{
		clear();
		printf("%s\nIntroduce el numero de la opcion: ", opciones);
		Leer_Numero(&seleccion);
		clear();
		switch (seleccion)
		{
		case 1:
			MostrarLista_Usuarios(lista);
			pulsa_cont();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		}
	} while (seleccion != num_op);
}
// Miscelanea
void pulsa_cont()
{
	printf("\nPulsa una tecla para continuar\n");
	getchar();
}

void Leer_Numero(int *entero)
{
	scanf(" %d", entero);
	Limpiar_Buffer();
}

void Limpiar_Buffer()
{
	while ((getchar()) != '\n');
}

