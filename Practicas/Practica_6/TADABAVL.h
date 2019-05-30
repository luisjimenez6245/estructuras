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

typedef Nodo* Posicion;
typedef Nodo* Arbolavl;

//OPERACIONES DE UN ÁRBOL BINARIO DE BÚSQUEDA AVL
void InsertNode();
void BalanceTree();
int GetHeight(Arbolavl *A, Posicion p);
void ReplaceNode(Arbolavl *A,Posicion p, Elemento e);
void DeleteNode(Arbolavl *A, Posicion p);
void DeleteLeftSon(Arbolavl *A, Posicion p);
void DeleteRightSon(Arbolavl *A, Posicion p);
void NewLeftSon(Arbolavl *A, Posicion p, Elemento e);
void NewRightSon(Arbolavl *A, Posicion p, Elemento e);
Elemento ReadNode(Arbolavl *A, Posicion p);
Posicion Search(Arbolavl *A, Elemento e);
void Destroy (Arbolavl *A);
void Initialize(Arbolavl *A);