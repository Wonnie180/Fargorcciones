/*
Autor: Luis Jose Llamas Perez
Fecha (dd/mm/yyyy): 
Descripcion:
*/

// Cabezera
// Librerias

// Constantes
#ifndef NULL
	#define NULL 0
#endif

#define clear() printf("\033[H\033[J")

// Declaracion de procedimientos y funciones
void generar_menu_principal(Lista_Usuarios *lista);
void generar_menu_usuarios(Lista_Usuarios *lista);
void generar_menu_facciones(Lista_Usuarios *lista);
void generar_menu_lista(Lista_Usuarios *lista);
void pulsa_cont();

// Operaciones con Menus
void generar_menu_principal(Lista_Usuarios *lista)
{
	int i, num_op = 5, seleccion;
	char *opciones[num_op];
	opciones[0] = "Menu Principal:\n";
	opciones[1] = "1 - Menu Usuarios\n";
	opciones[2] = "2 - Menu Facciones\n";
	opciones[3] = "3 - Menu Lista\n";
	opciones[4] = "4 - Cargar Datos\n";
	opciones[5] = "5 - Salir del programa\n";

	do
	{
		clear();
		for (i = 0; i <= num_op; i++)
		{
			printf("%s", opciones[i]);
		}

		printf("Introduce el numero de la opcion: ");
		scanf(" %d", &seleccion);
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
				default:
					break;
			}		
	} while (seleccion != num_op);
}

void generar_menu_usuarios(Lista_Usuarios *lista)
{
	int i, num_op = 4, seleccion, faccion;
	char *opciones[num_op], nombre[LONG_NOM], res;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	Usuario *usuario;
	Date fecha_sub;
	fecha_sub.year = tm.tm_year + 1900;	
	fecha_sub.month = tm.tm_mon + 1;
	fecha_sub.day = tm.tm_mday;
	
	opciones[0] = "Menu de Usuarios:\n";
	opciones[1] = "1 - Insertar un nuevo Usuario\n";
	opciones[2] = "2 - Cambiar faccion\n";
	opciones[3] = "3 - Resub\n";
	opciones[4] = "4 - Volver al menu principal\n";

	do
	{
		clear();
		for (i = 0; i <= num_op; i++)
		{
			printf("%s", opciones[i]);
		}

		printf("Introduce el numero de la opcion: ");
		scanf(" %d", &seleccion);
		clear();
		
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
					printf("Introduce el numero de la opcion: ");
					break;
				case 3:
					printf("Introduce el numero de la opcion: ");
					break;
				case 4:
					printf("Introduce el numero de la opcion: ");
					break;
			}		
	} while (seleccion != num_op);
}

void generar_menu_facciones(Lista_Usuarios *lista)
{
	int i, num_op = 4, seleccion;
	char *opciones[num_op];
	opciones[0] = "Menu de Facciones:\n";
	opciones[1] = "1 - Insertar un nuevo Usuario\n";
	opciones[2] = "2 - Cambiar faccion\n";
	opciones[3] = "3 - Resub\n";
	opciones[4] = "4 - Volver al menu principal\n";

	do
	{
		clear();
		for (i = 0; i <= num_op; i++)
		{
			printf("%s", opciones[i]);
		}

		printf("Introduce el numero de la opcion: ");
		scanf(" %d", &seleccion);
		clear();
		
			switch (seleccion)
			{
				case 1:
					break;
				case 2:
					printf("Introduce el numero de la opcion: ");
					break;
				case 3:
					printf("Introduce el numero de la opcion: ");
					break;
				case 4:
					printf("Introduce el numero de la opcion: ");
					break;
			}		
	} while (seleccion != num_op);
}

void generar_menu_lista(Lista_Usuarios *lista)
{
	int i, num_op = 4, seleccion;
	char *opciones[num_op], c;
	opciones[0] = "Menu de Lista:\n";
	opciones[1] = "1 - Mostrar Lista\n";
	opciones[2] = "2 - Cambiar faccion\n";
	opciones[3] = "3 - Resub\n";
	opciones[4] = "4 - Volver al menu principal\n";

	do
	{
		clear();
		for (i = 0; i <= num_op; i++)
		{
			printf("%s", opciones[i]);
		}

		printf("Introduce el numero de la opcion: ");
		scanf(" %d%c", &seleccion, &c);
		clear();
		
		switch (seleccion)
		{
			case 1:
				MostrarLista_Usuarios(lista);
				pulsa_cont();
				break;
			case 2:
				printf("Introduce el numero de la opcion: ");
				break;
			case 3:
				printf("Introduce el numero de la opcion: ");
				break;
			case 4:
				printf("Introduce el numero de la opcion: ");
				break;
			default:
				break;
		}		
	} while (seleccion != num_op);
}
// Miscelanea
void pulsa_cont(){
	while (getchar() != '\n') { }
	printf("\nPulsa una tecla para continuar\n");
	getchar();
}
