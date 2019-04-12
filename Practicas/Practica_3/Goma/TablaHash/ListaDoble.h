/*
	CABECERA PARA EL TADLISTA DOBLEMENTE LIGADA
	AUTOR: AARÓN GAMALIEL SÁNCHEZ CASTRO (C) MARZO 2019
	VERSIÓN 1.0
	DESCRIPCIÓN: EL SIGUIENTE CÓDIGO MUESTRA LA IMPLEMENTACIÓN DE UNA LISTA DOBLEMENTE LIGADA.
	OBSERVACIONES: SE TRATA DE UNA LISTA DINÁMICA, POR LO QUE LA MEMORIA OCUPADA POR EL PROGRAMA CRECERÁ
		DURANTE EL TIEMPO DE EJECUCIÓN.
*/
#define TRUE 1
#define FALSE 0

typedef unsigned int boolean;

typedef struct Element{
	char palabra[100];
	char definicion[251];
} Element;

typedef struct Node
{
	Element content;
	struct Node *previous;
	struct Node *following;
	int pasos;
} Node;

typedef Node* Position;

typedef struct List
{
	struct Node* front;
	struct Node* final;
	int listSize;
} List;

//COMENZMOS CON LAS OPERACIONES DE LA LISTA
void Initialize(List* list);//LISTO
void Destroy(List* list);
void Insert(List* list, Element element, Position position, boolean bool);//LISTO
void Add(List* list, Element element); //LISTO
void Remove(List* list, Position position);
boolean Empty(List* list); //LISTO
Position Final(List* list); //LISTO
Position First(List* list); //LISTO
boolean ValidatePosition(List* list, Position position); //LISTO
int Size(List* list); //LISTO
Position Following(List* list, Position position);//LISTO
Position Search(List* list, Element element);//LISTO
Element GetElement(List *list, Position position);//LISTO
Position ElementPosition(List* list, int position);//LISTO
Position Previous(List* list,Position position);//LISTO