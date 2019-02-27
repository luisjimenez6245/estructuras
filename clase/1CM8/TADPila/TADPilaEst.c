#include<stdlib.h>
#include<stdio.h>
#include "TADPilaEst.h"
/*Inicializar pila (Initialize): recibe<- pila (S); 
Initialize(S);
Efecto: Recibe una pila y la inicializa para su trabajo normal.
*/
void Initialize(pila *s)
{
	(*s).tope =-1;
	return;
}

/*
Empilar (Push): recibe<- pila (S); recibe<- elemento (e) 
Push(S,e);
Efecto: Recibe la pila y aumenta su tamaño, poniendo el elemento en la cima de la pila.
*/
void Push(pila *s,elemento e)
{
	(*s).tope++;
	if(s->tope<MAX)
		(*s).A[(*s).tope]=e;
	else 
	{
			printf("\n ERROR:PUSH(S,E) DESBORDAMIENTO DE PILA ");
			exit (1);
	}
			
	return;
}


/*
Desempilar (Pop): recibe<- pila (S); retorna -> elemento
e=Pop(S);
Efecto: Recibe la pila, remueve el elemento tope y lo retorna.
Excepción: Si la pila esta vacía, produce error.
*/
elemento Pop(pila *s)
{
	elemento r;
	if(s->tope>=0)
	{
		r=s->A[s->tope];
		s->tope--;
	}
	else
	{
			printf("\nERROR: POP(S) SUBDESBORDAMIENTO DE PILA");
			exit(1);
	}
	return r;
}
/*
Es vacía (Empty): recibe<- pila (S); retorna -> boolean
b=Empty(S);
Efecto: Recibe una pila y devuelve true si esta vacía y false en caso contrario.
*/
boolean Empty(pila *s)
{
	boolean r = FALSE;
	if(s->tope==-1)
		r=TRUE;
	return r;
}

/*
Tope pila (Top): recibe<- pila (S); retorna -> elemento
e=Top(S);
Efecto: Devuelve el elemento cima de la pila.
Excepción: Si la pila esta vacía produce error
*/
elemento Top(pila *s)
{
	elemento r;
	if(s->tope>-1)
		r=s->A[s->tope];
	else
	{
			printf("\nERROR: TOP(S) SUBDESBORDAMIENTO DE PILA");
			exit(1);
	}
	return r;
}
/*
Tamaño pila (Size): recibe<- pila (S); retorna -> valor del tope
n=Size(S);
Efecto: Devuelve el número de elementos que contiene la pila (Altura de la pila).
*/
int Size(pila *s)
{	
	return s->tope+1;
}/*
Eliminar pila (Destroy): recibe<- pila (S)
Destroy(S);
Efecto: Recibe una pila y la libera completamente
*/
void Destroy(pila *s)
{
	Initialize(s);
	return;
}
