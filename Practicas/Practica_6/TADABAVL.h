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

typedef struct elemento
{
	char palabra[100];
	char definicion[255];
} elemento;

typedef struct nodo
{
	elemento e;
	struct Nodo *HijoI;
	struct Nodo *HijoD;
} nodo;

typedef nodo *posicion;
typedef nodo *Arbolavl;

//OPERACIONES DE UN ÁRBOL BINARIO DE BÚSQUEDA AVL
void InsertNode();
void BalanceTree();
int GetHeight(Arbolavl *A, posicion p);
void ReplaceNode(Arbolavl *A, posicion p, elemento e);
void DeleteNode(Arbolavl *A, posicion p);
void DeleteLeftSon(Arbolavl *A, posicion p);
void DeleteRightSon(Arbolavl *A, posicion p);
void NewLeftSon(Arbolavl *A, posicion p, elemento e);
void NewRightSon(Arbolavl *A, posicion p, elemento e);
elemento ReadNode(Arbolavl *A, posicion p);
posicion Search(Arbolavl *A, elemento e);
void Destroy(Arbolavl *A);
void Initialize(Arbolavl *A);