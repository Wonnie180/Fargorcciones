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
#include "./lista-usuarios.h"
#include "./menus.h"
// Constantes

// Tipos

int main()
{
	Lista_Usuarios *lista = CrearLista_Usuarios();
	Cargar_Lista_Usuarios(lista);
	generar_menu_principal(lista);
	return 0;
}
