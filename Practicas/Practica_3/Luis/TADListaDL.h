#ifndef __TADLista_H
#define __TADLista_H
/*
IMPLEMENTACIONES DEL TAD LISTA (TADLista.h)
AUTOR: Luis Diego Jiménez Delgado (Abril 2019)
VERSION: 1.0

OBSERVACIONES: Este archivo solo incluye las estructuras, tipos de datos y
declaracion de las operaciones del TAD  Lista.

EL CODIGO QUE IMPLEMENTA LAS FUNCIONES ES EL ARCHIVO: TADListaDL.c
*/
#define TRUE 1
#define FALSE 0

typedef unsigned char boolean;

typedef struct elemento
{
	char palabra[100];
	char definicion[251];
}elemento;

//Estructura de un NODO DOBLEMENTE LIGADO
typedef struct nodo
{
	elemento e;
	//Realacion con el siguiente y anterior nodo
	struct nodo *siguiente;
	//Numero de pasos en los que se encuentra el nodo
	int pasos;
} nodo;

//Se define una posicion como un apuntador a nodo
typedef nodo* posicion;

//Estructura de una lista
typedef struct lista
{
	int tamanio;
	posicion frente;
	posicion final;
}lista;

//Efecto: Recibe una lista l y la inicializa para su trabajo normal.
void Initialize (lista *l);

//Efecto: Recibe una lista l y la libera completamente
void Destroy (lista *l);
//Efecto: Recibe una lista l y retorna la posicion del elemento al final de esta.
posicion Final (lista *l);

//Efecto: Recibe una lista l y devuelve la posicion del elemento al inicio de esta.
posicion First (lista *l);

//Efecto: Recibe una lista l, una posicion p y devuelve la posición del elemento siguiente de p.
posicion Following (lista *l,posicion p);

//Efecto: Recibe una lista l, una posicion p y devuelve la posicion del elemento anterior a p.
//Requerimientos: La lista l es no vacia y la posicion p es una posicion valida.
posicion Previous (lista *l,posicion p);

//Efecto: Recibe una lista l y un elemento e, devuelve la posicion del elemento que coincida exactamente con e.
posicion Search (lista *l,elemento e);

//Efecto: Recibe una lista l, una posicion p y devuelve el elemento en dicha posicion.
//Requerimientos: La lista l es no vacía y la posicion p es una posicion valida.
elemento Position (lista *l,posicion p);

//Efecto: Recibe una lista l, una posicion p y devuelve TRUE si la posicion es una posicion p valida en la lista l y FALSE en caso contrario.
boolean ValidatePosition (lista *l,posicion p);

//Efecto: Recibe una lista y un indice (entre 1 y el tamaño de la lista) y devuelve la posicion del elemento que se encuentra en la lista en ese índice partiendo del frente de este =1 hacia atrás.
//Excepcion: Si la cola esta vacia o el indice se encuentra fuera del tamanio de la lista se retorna una posicion invalida.
posicion ElementPosition(lista *l, int n);

//Efecto: Recibe una lista y un indice (entre 1 y el tamaño de la lista) y devuelve el elemento que se encuentra en la lista en ese indice partiendo del frente de este =1 hacia atrás.
//Excepcion: Si la cola esta vacia o el indice se encuentra fuera del tamanio de la lista se produce error.
elemento Element(lista *l, int n);

//Efecto: Recibe una lista l y devuelve el tamanio de la lista.
int Size (lista *l);

//Efecto: Recibe una lista l y devuelve TRUE en caso de que la lista este vacia y FALSE en caso contrario
boolean Empty (lista *l);

//Efecto: Recibe una lista l, una posicion p, un elemento e y un valor booleano; el elemento e deberia agregarse al frente de p si b es verdadero y atrás de p en caso contrario.
//Requerimientos: La posicion p es una posicion valida, si p es no valida o NULL, se insertara a e al frente de la lista.
void Insert (lista * l, posicion p, elemento e, boolean b);

//Efecto: Recibe una lista l y un elemento e ; el elemento e debera agregarse al final de la lista
void Add (lista *l,elemento e);

//Efecto: Recibe una lista l y una posicion p, el elemento en la posicion p sera removido.
//Requerimientos: La lista l es no vacia y la posicion p es una posicion valida.
void Remove (lista *l,posicion p);

//Efecto: Recibe una lista l, una posicion p y un elemento e, el elemento en la posicion p sera sustituido por e
//Requerimientos: La lista l es no vacia y la posicion p es una posicion valida.
void Replace (lista *l,posicion p, elemento e);

//Funcion para usarse en depuracion, la cual imprime las direcciones de
//memoria de los nodos y su apuntador a siguiente
void VerLigasLista(lista *l);
#endif    // __TADLista_H
