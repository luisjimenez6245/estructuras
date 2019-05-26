/*
	CABECERA PARA LA LIBRERÍA TAD ÁRBOL BINARIO AVL
	AUTORES: 
		JIMÉNEZ DELGADO LUIS DIEGO
		SÁNCHEZ CASTRO AARÓN GAMALIEL
		SÁNCHEZ TIRADO CITLALI YASMÍN
	VERSIÓN: 1.0 
	DESCRIPCIÓN:
*/
//LIBRERÍAS A OCUPAR
#include <stdio.h>
#include <stdlib.h>
//CONSTANTES A UTILIZAR
#define TRUE 1
#define FALSE 0

typedef int boolean;

typedef struct Elemento {
	char palabra[100];
	char definicion[255];
} Elemento;

typedef struct Nodo {
	Elemento elemento;
	struct Nodo *HijoI;
	struct Nodo *HijoD;
} Nodo;

//OPERACIONES DE UN ÁRBOL BINARIO DE BÚSQUEDA AVL

void InsertarNodo();
void Balancear();
boolean EliminarNodo();
int CalcularAltura();