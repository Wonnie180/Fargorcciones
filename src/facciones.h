/*
Autor: Luis Jose Llamas Perez
Fecha (dd/mm/yyyy): 
Descripcion:
*/

// Cabezera
// Librerias
// Constantes

// Tipos
#ifndef NULL
	#define NULL 0
#endif

typedef struct Facciones
{
	char *faccion_actual;
	unsigned int id_faccion;
	unsigned int puntos_facciones[4][4]; // 0 = Aire, 1 = Agua, 2 = Fuego, 3 = Tierra	
} Facciones;

/*
typedef struct Faccion
{
	int id_faccion;
	int vida;
	int poblacion;
} Faccion;
*/

// Declaracion de procedimientos y funciones

// Operaciones con Facciones
char* Obtener_Nombre_Faccion(int id_faccion);

char* Obtener_Nombre_Faccion(int id_faccion){
	char *facciones[4]={"Aire","Agua","Fuego","Tierra"};
	return facciones[id_faccion];
}

