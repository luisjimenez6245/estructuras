/*
IMPLEMENTACIONES DEL TAD LISTA (TADLista.h)
AUTOR: Edgardo Adrián Franco Martínez (C) Marzo 2017
VERSIÓN: 1.1

DESCRIPCIÓN: TAD lista o (list)
Estructura de datos en la que se cumple:
Los definicions se consultan, añaden y se remueven con base en posiciones 
dentro de un arreglo lineal el cual cuenta con un frente o cabeza 
y un final o cola.

OBSERVACIONES: Este archivo solo incluye las estructuras, tipos de datos y
declaración de las operaciones del TAD  Lista.

EL CODIGO QUE IMPLEMENTA LAS FUNCIONES ES EL ARCHIVO: TADLista.c
*/
#define TRUE	1
#define FALSE	0

//Estructura definicion (Modificable por el usuario)
typedef struct definicion
{
	char palabra[51];
	char significado[251];
}definicion;

//Tipo de dato boolean (Modelado con un char)
typedef unsigned char boolean;

//Estructura de un NODO DOBLEMENTE LIGADO(No modificar)
typedef struct nodo
{
	definicion e;
	int saltos;	
	struct nodo *siguiente;
	struct nodo *anterior;
}nodo;

//Definición de una posición
typedef nodo* posicion;

//Estructura lista
typedef struct lista
{
	posicion frente;
	posicion final;
	int tam;
}lista;

//Operaciones de construcción
//void Initialize(lista *l);
//void Destroy(lista *l);
//Operaciones de posicionamiento y busqueda
//posicion Final(lista *l);
//posicion First(lista *l);
posicion Following(lista *l, posicion p);
posicion Previous(lista *l, posicion p);
posicion Search(lista *l, definicion e);
//Operación de consulta
definicion Position(lista *l, posicion p);
//boolean ValidatePosition(lista *l, posicion p);
definicion Element(lista *l, int n);
//posicion ElementPosition(lista *l, int n);
//int Size(lista *l);
//boolean Empty(lista *l);
//Operaciones de modificación
//void Insert(lista *l, definicion e, posicion p,boolean b);
//void Add(lista *l,definicion e);
//void Remove(lista *l,posicion p);
void Replace(lista *l,posicion p, definicion e);
