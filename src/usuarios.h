/*
Autor: Luis Jose Llamas Perez
Fecha (dd/mm/yyyy):
Descripcion: 
*/

// Cabezera
// Librerias
#include "./facciones.h"

// Constantes

#ifndef NULL
	#define NULL 0
#endif

#define LONG_NOM 15
#define LONG_LINEA 1024

// Tipos
typedef struct Date
{
	unsigned int year;
	unsigned int month;
	unsigned int day;
} Date;

typedef struct Puntos
{
	unsigned int disponibles;
	unsigned int utilizados;
	unsigned int sumador;
} Puntos;

typedef struct Usuario
{
	char Nombre[LONG_NOM];
	struct Date fecha_sub;
	struct Facciones facciones;
	struct Puntos puntos;
	struct Usuario *sig;
	struct Usuario *ant;
} Usuario;

// Declaracion de procedimientos y funciones
Usuario* Nuevo_Usuario(char *nombre, Date fecha_sub, int id_faccion);
void Modificar_Usuario(Usuario *Usuario);
void Borrar_Usuario(Usuario *Usuario);
void Mostrar_Usuario(Usuario *usuario);
void Cambiar_Faccion_Usuario(Usuario *usuario, int id_faccion);
void Resub(Usuario *usuario);
Usuario* Cargar_Usuario(FILE *fptr);
void Guardar_Usuario(Usuario *usuario, FILE *fptr);

// Operaciones con Usuarios
Usuario* Nuevo_Usuario(char *nombre, Date fecha_sub, int id_faccion)
{
	int i,j;
	Usuario *usuario = (Usuario *)malloc(sizeof(Usuario));
	strcpy(usuario->Nombre, nombre);
	usuario->facciones.faccion_actual = Obtener_Nombre_Faccion(id_faccion);
	usuario->facciones.id_faccion = id_faccion;
	for (i = 0; i < Numero_Facciones(); i++){
		for (j = 0; j < Numero_Facciones(); j++){
			usuario->facciones.puntos_facciones[i][j] = 0;
		}
	}
	usuario->puntos.disponibles = 1;
	usuario->puntos.utilizados = 0;
	usuario->puntos.sumador = 2;
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

void Cambiar_Faccion_Usuario(Usuario *usuario, int id_faccion)
{
	if (usuario != NULL){
		usuario->facciones.id_faccion = id_faccion;
		usuario->facciones.faccion_actual = Obtener_Nombre_Faccion(id_faccion);
	}
}

void Mostrar_Usuario(Usuario *usuario){
	if (usuario != NULL){
		printf("Nombre: %s\
		\n	Fecha de suscripcion: %d/%d/%d\
		\n	Faccion: %s\
		\n	Puntos Disponibles: %d\
		\n	Puntos Sumador: %d\n",
		usuario->Nombre,usuario->fecha_sub.day,
		usuario->fecha_sub.month,usuario->fecha_sub.year,usuario->facciones.faccion_actual,
		usuario->puntos.disponibles,
		usuario->puntos.sumador);
	} else {
		printf("El usuario no existe");
	}
}

unsigned int Convertir_char_a_unsigned_bit(char *linea, int *i){
	unsigned int aux = 0;
	while (linea[(*i)] == ','){
		(*i)++;
	}
	while (linea[(*i)] != ',' && linea[(*i)] != '\n' && linea[(*i)] != '\0')
	{
		aux = ((aux * 10) + (linea[(*i)++] - '0'));
	}
	return aux;
}

Usuario* Cargar_Usuario(FILE *fptr){
	char linea[LONG_LINEA];
	int i,j,c=0;
	Usuario *usuario = (Usuario *)malloc(sizeof(Usuario));
	
	if (fscanf(fptr, "%[^,],%u,%u,%u,%u%[^\n]\n",
		usuario->Nombre,
		&usuario->fecha_sub.year,
		&usuario->fecha_sub.month,
		&usuario->fecha_sub.day,
		&usuario->facciones.id_faccion,
		linea
		) == EOF){
		return NULL;
	}
	
	usuario->facciones.faccion_actual = Obtener_Nombre_Faccion(usuario->facciones.id_faccion);
	for (i = 0; i < Numero_Facciones(); i++){
		for (j = 0; j < Numero_Facciones(); j++){
			usuario->facciones.puntos_facciones[i][j] = Convertir_char_a_unsigned_bit(linea, &c);
		}
	}
	
	usuario->puntos.disponibles = Convertir_char_a_unsigned_bit(linea, &c);
	usuario->puntos.utilizados = Convertir_char_a_unsigned_bit(linea, &c);
	usuario->puntos.sumador = Convertir_char_a_unsigned_bit(linea, &c);
			
	usuario->sig = NULL;
	usuario->ant = NULL;
	
	return usuario;
}


void Guardar_Usuario(Usuario *usuario, FILE *fptr){
	int i,j;
	fprintf(fptr, "%s,%u,%u,%u,%u,",
		usuario->Nombre, 
		usuario->fecha_sub.year,
		usuario->fecha_sub.month,
		usuario->fecha_sub.day,
		usuario->facciones.id_faccion);
	for (i = 0; i < Numero_Facciones(); i++){
		for (j = 0; j < Numero_Facciones(); j++){
			fprintf(fptr, "%u,", usuario->facciones.puntos_facciones[i][j]); 			
		}
	}
	fprintf(fptr, "%u,%u,%u\n",
		usuario->puntos.disponibles, 
		usuario->puntos.utilizados, 
		usuario->puntos.sumador);
}

void Resub(Usuario *usuario){
	if (usuario != NULL){
		usuario->puntos.disponibles += usuario->puntos.sumador++;
	}
}


