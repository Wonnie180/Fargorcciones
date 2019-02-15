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



typedef struct Date
{
	int year;
	int month;
	int day;
} Date;

typedef struct Puntos
{
	int disponibles;
	int utilizados;
	int sumador;
} Puntos;

typedef struct Facciones
{
	char faccion_actual[10];
	int id_faccion;
	int puntos_facciones[4][4]; // 0 = Aire, 1 = Agua, 2 = Fuego, 3 = Tierra	
} Facciones;

typedef struct Usuario
{
	char Nombre[15];
	struct Date fecha_sub;
	struct Facciones facciones;
	struct Puntos puntos;
	struct Usuario *sig;
	struct Usuario *ant;
} Usuario;

// Declaracion de procedimientos y funciones

// Operaciones con Usuarios
Usuario *Nuevo_Usuario();
void Modificar_Usuario(Usuario *Usuario);
void Borrar_Usuario(Usuario *Usuario);
void Mostrar_Usuario(Usuario *usuario);
char* nombre_faccion(int id_faccion);

// FUNCIONES

// Operaciones con Usuarios
Usuario *Nuevo_Usuario(char *nombre, Date fecha_sub, int id_faccion)
{
	int i,j;

	Usuario *usuario = (Usuario *)malloc(sizeof(Usuario));

	strcpy(usuario->Nombre, nombre);
	strcpy(usuario->facciones.faccion_actual, nombre_faccion(id_faccion));
	usuario->facciones.id_faccion = id_faccion;
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			usuario->facciones.puntos_facciones[i][j] = 0;
		}
	}
	usuario->puntos.disponibles = 1;
	usuario->puntos.utilizados = 0;
	usuario->puntos.sumador = 0;
	usuario->fecha_sub = fecha_sub;
	usuario->sig = NULL;
	usuario->ant = NULL;
	return usuario;
}

void Borrar_Usuario(Usuario *usuario)
{
	usuario->sig = NULL;
	usuario->ant = NULL;
	free(usuario);
}

char* nombre_faccion(int id_faccion){
	char *facciones[4]={"Aire","Agua","Fuego","Tierra"};
	return facciones[id_faccion];
}

void Cambiar_Faccion_Usuario(Usuario *usuario, int id_faccion)
{
	if (usuario != NULL){
		usuario->facciones.id_faccion = id_faccion;
		strcpy(usuario->facciones.faccion_actual, nombre_faccion(id_faccion));
	}
}

void Mostrar_Usuario(Usuario *usuario){
	if (usuario != NULL){
		printf("Nombre: %s\
		\nFecha de suscripcion: %d/%d/%d\
		\nFaccion: %s\
		\nPuntos Disponibles: %d\n",
		usuario->Nombre,usuario->fecha_sub.day,
		usuario->fecha_sub.month,usuario->fecha_sub.year,usuario->facciones.faccion_actual,
		usuario->puntos.disponibles);
	} else {
		printf("El usuario no existe");
	}
}
