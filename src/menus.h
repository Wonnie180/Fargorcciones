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
	int i, num_op = 5, seleccion;
	char *opciones = "Menu Principal:\n\
					\n1 - Menu Usuarios\
					\n2 - Menu Facciones\
					\n3 - Menu Lista\
					\n4 - Cargar Datos\
					\n5 - Salir del programa\n";
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
			Cargar_Lista_Usuarios(lista);
			break;
		case 5:
			Guardar_Lista_Usuarios(lista);
			VaciarLista_Usuarios(lista);
			free(lista);
			break;
		}
	} while (seleccion != num_op);
}

void generar_menu_usuarios(Lista_Usuarios *lista)
{
	int i, num_op = 4, seleccion, faccion;
	char nombre[LONG_NOM], res;

	Usuario *usuario;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	Date fecha_sub;
	fecha_sub.year = tm.tm_year + 1900;
	fecha_sub.month = tm.tm_mon + 1;
	fecha_sub.day = tm.tm_mday;

	char *opciones = "Menu de Usuario:\n\
					\n1 - Insertar un nuevo Usuario\
					\n2 - Cambiar faccion\
					\n3 - Resub\
					\n4 - Volver al menu principal\n";
	do
	{
		clear();
		printf("%s\nIntroduce el numero de la opcion: ", opciones);
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
			break;
		case 3:
			break;
		case 4:
			break;
		}
	} while (seleccion != num_op);
}

void generar_menu_facciones(Lista_Usuarios *lista)
{
	int i, num_op = 4, seleccion;
	char *opciones = "Menu de Facciones:\n\
					\n1 - Insertar un nuevo Usuario\
					\n2 - Cambiar faccion\
					\n3 - Resub\
					\n4 - Volver al menu principal\n";
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
	int i, num_op = 4, seleccion;
	char *opciones = "Menu de Lista:\n\
					\n1 - Mostrar Lista\
					\n2 - Cambiar faccion\
					\n3 - Resub\
					\n4 - Volver al menu principal\n";
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

