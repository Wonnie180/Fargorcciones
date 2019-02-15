/*
Autor: Luis Jose Llamas Perez
Fecha (dd/mm/yyyy): 05/09/2018
Descripcion: Ejercicio 5
*/

// Cabezera
// Librerias
#include <stdio.h>
#include <stdlib.h>
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
	int total;
} Puntos;

typedef struct Faccion
{
	char *actual;
	char **antiguas;
} Faccion;

typedef struct Usuario
{
	char *Nombre;
	struct Faccion faccion;
	struct Puntos puntos;
	struct Date fecha_sub;
	struct Usuario *sig;
	struct Usuario *ant;
} Usuario;

// Declaracion de procedimientos y funciones

// Operaciones con Usuarios
Usuario *Nuevo_Usuario();
void Modificar_Usuario(Usuario *Usuario);
void Borrar_Usuario(Usuario *Usuario);

// FUNCIONES
// Operaciones con Usuarios
Usuario *Nuevo_Usuario()
{
	char *nombre = "prueba";
	Usuario *usuario = (Usuario *)malloc(sizeof(Usuario));
	usuario->Nombre = nombre;
	usuario->faccion.actual;
	usuario->faccion.antiguas;
	usuario->puntos.disponibles = 0;
	usuario->puntos.total = 0;
	usuario->puntos.utilizados = 0;
	usuario->fecha_sub.year = 0;
	usuario->fecha_sub.month = 0;
	usuario->fecha_sub.day = 0;
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

void Mostrar_Usuario(Usuario *usuario){
	printf("Nombre: %s\nFaccion: %s\nFecha de suscripcion: %d/%d/%d",usuario->Nombre,usuario->faccion.actual,usuario->fecha_sub.day,usuario->fecha_sub.month,usuario->fecha_sub.year);
}