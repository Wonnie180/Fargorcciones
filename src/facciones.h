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

#define NUM_FACCIONES 4

// Tipos
typedef struct Facciones
{
	char *faccion_actual;
	unsigned char id_faccion; // 0 .. 255
	unsigned int puntos_facciones[NUM_FACCIONES][NUM_FACCIONES];
	// 0 = Aire, 1 = Agua, 2 = Fuego, 3 = Tierra
} Facciones;

// Declaracion de procedimientos y funciones
char *Obtener_Nombre_Faccion(unsigned char id_faccion);
unsigned char Numero_Facciones();

// Operaciones con Facciones
char *Obtener_Nombre_Faccion(unsigned char id_faccion)
{
	char *facciones[NUM_FACCIONES] = {"Aire", "Agua", "Fuego", "Tierra"};
	return facciones[id_faccion];
}

unsigned char Numero_Facciones()
{
	return NUM_FACCIONES;
}
