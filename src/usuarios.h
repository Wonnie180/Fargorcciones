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
#define DIGITOS_NUM 52

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
	char *Nombre;
	struct Date fecha_sub;
	struct Facciones facciones;
	struct Puntos puntos;
	struct Usuario *sig;
	struct Usuario *ant;
} Usuario;

// Declaracion de procedimientos y funciones
Usuario* Nuevo_Usuario();
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
		\n	Puntos Disponibles: %d\n",
		usuario->Nombre,usuario->fecha_sub.day,
		usuario->fecha_sub.month,usuario->fecha_sub.year,usuario->facciones.faccion_actual,
		usuario->puntos.disponibles);
	} else {
		printf("El usuario no existe");
	}
}

unsigned int Convertir_char_a_unsigned_bit(char *linea, int *i){
	unsigned int aux = 0;
	while (linea[++(*i)] != ',' && linea[(*i)] != '\n')
	{
		aux = ((aux * 10) + (linea[(*i)] - '0'));
	}
	return aux;
}

Usuario* Cargar_Usuario(FILE *fptr){
	char linea[LONG_LINEA];
	if (!fgets(linea, LONG_LINEA, fptr)){
		return NULL;
	}
	int c = 0, i, j;
	char *nombre = (char *)malloc(LONG_NOM * sizeof(char));
	Usuario *usuario = (Usuario *)malloc(sizeof(Usuario));
	// Obtener Nombre
	strncpy(nombre, linea, LONG_NOM + 1);
	strtok(nombre,",");
	usuario->Nombre = nombre;
	while (linea[(c)] != ','){ c++; }
	// Obtener Fecha Año
	usuario->fecha_sub.year = Convertir_char_a_unsigned_bit(linea, &c);
	// Obtener Fecha Mes
	usuario->fecha_sub.month = Convertir_char_a_unsigned_bit(linea, &c);
	// Obtener Fecha Dia
	usuario->fecha_sub.day = Convertir_char_a_unsigned_bit(linea, &c);
	// Obtener Id_Faccion
	usuario->facciones.id_faccion = Convertir_char_a_unsigned_bit(linea, &c);
	usuario->facciones.faccion_actual = Obtener_Nombre_Faccion(usuario->facciones.id_faccion);
	// Obtener Ataques/Defensas
	for (i = 0; i < Numero_Facciones(); i++){
		for (j = 0; j < Numero_Facciones(); j++){
			usuario->facciones.puntos_facciones[i][j] = Convertir_char_a_unsigned_bit(linea, &c);
		}
	}
	// Obtener Puntos Disponibles
	usuario->puntos.disponibles = Convertir_char_a_unsigned_bit(linea, &c);
	// Obtener Puntos Utilizados
	usuario->puntos.utilizados = Convertir_char_a_unsigned_bit(linea, &c);
	// Obtener Puntos Sumador
	usuario->puntos.sumador = Convertir_char_a_unsigned_bit(linea, &c);
	// para la lista
	usuario->sig = NULL;
	usuario->ant = NULL;
	return usuario;
}


void Guardar_Usuario(Usuario *usuario, FILE *fptr){
	int i,j;
	char linea[LONG_LINEA], aux[DIGITOS_NUM];
	// Obtener nombre
	strcpy(linea, usuario->Nombre); 
	strcat(linea, ",");
	// Obtener Año
	sprintf(aux,  "%d,", usuario->fecha_sub.year); 
	strcat(linea, aux);	
	// Obtener Mes
	sprintf(aux,  "%d,", usuario->fecha_sub.month); 
	strcat(linea, aux);	
	// Obtener Dia
	sprintf(aux,  "%d,", usuario->fecha_sub.day); 
	strcat(linea, aux);	
	// Obtener Id Faccion [0] al [3]
	sprintf(aux,  "%d,", usuario->facciones.id_faccion); 
	strcat(linea, aux);	
	// Obtener Puntos de ataque/defensa
	for (i = 0; i < Numero_Facciones(); i++){
		for (j = 0; j < Numero_Facciones(); j++){
			sprintf(aux,  "%d,", usuario->facciones.puntos_facciones[i][j]); 			
			strcat(linea, aux);	
		}
	}
	// Obtener Puntos Disponibles
	sprintf(aux,  "%d,", usuario->puntos.disponibles); 
	strcat(linea, aux);	
	// Obtener Puntos Utilizados
	sprintf(aux,  "%d,", usuario->puntos.utilizados); 
	strcat(linea, aux);	
	// Obtener Puntos Sumador
	sprintf(aux,  "%d\n", usuario->puntos.sumador); 
	strcat(linea, aux);	
	// Escribir en el fichero
	fprintf(fptr, "%s", linea);
}

void Resub(Usuario *usuario){
	if (usuario != NULL){
		usuario->puntos.disponibles += usuario->puntos.sumador++;
	}
}


