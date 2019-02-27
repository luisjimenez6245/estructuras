#include<stdio.h>
#include<stdlib.h>
#include "TADColaEst.h"
/*Inicializar cola (Initialize): recibe<- cola (C); 
Initialize (C)
Efecto: Recibe una cola, la inicializa para su trabajo normal.
*/
void Initialize(cola * C)
{
	C->final=-1;
	return;	
}
/*
Encolar (Queue): recibe<- cola (C) ; recibe<- elemento(e) 
Queue(C,e);
Efecto: Recibe una cola y un elemento el cuál se introduce al final de la cola.
*/
void Queue(cola *C,elemento e)
{
	if(C->final==MAX-1)
	{
		printf("\nERROR: QUEUE DESBORDAMIENTO DE COLA");
		exit(1);
	}	
	C->final++;
	C->A[C->final]=e;
	return;	
}

/*
Desencolar (Dequeue): recibe<- cola (C); retorna -> elemento
e=Dequeue (C);
Efecto: Recibe una cola y devuelve el elemento que se encuentra al frente de esta, quitándolo de la cola.
Excepción: Si la cola esta vacía produce error.
*/
elemento Dequeue (cola *C)
{
	elemento r;
	int i;
	if (C->final==-1)
	{
		printf("\nERROR: DEQUEUE SUBDESBORDAMIENTO DE COLA");
		exit (1);
	}
	r=C->A[0];
	for (i=0;i<C->final;i++)
		C->A[i]=C->A[i+1];
	C->final--;
	return r;	
}


/*Es vacía (Empty): recibe<- cola (C); retorna -> booleano
Empty (C)
Efecto: Recibe la cola y verifica si esta tiene elementos, devuelve TRUE si esta vacía y FALSE en caso contrario.
*/
booleano Empty (cola *C)
{
	return (C->final==-1)? TRUE:FALSE;
}

/*
Frente (Front): recibe<- cola (C) ; retorna -> elemento
e=Front (C);
Efecto: Recibe una cola y devuelve el elemento que se encuentra al frente de esta.
Excepción: Si la cola esta vacía produce error.
*/
elemento Front (cola *C)
{
	elemento r;
	if (C->final==-1)
	{
		printf("\nERROR: FRONT SUBDESBORDAMIENTO DE COLA");
		exit (1);
	}
	r=C->A[0];
	return r;	
}


/*
Final (Final): recibe<- cola (C); retorna -> elemento
e=Final(C);
Efecto: Recibe una cola y devuelve el elemento que se encuentra al final de esta.
Excepción: Si la cola esta vacía produce error.
*/
elemento Final(cola *C)
{
	elemento r;
	if (C->final==-1)
	{
		printf("\nERROR: FINAL SUBDESBORDAMIENTO DE COLA");
		exit (1);
	}
	r=C->A[C->final];
	return r;	
}



/*
Elemento(Element): recibe<- cola (C); recibe<- índice(n); retorna -> elemento
e=Element (C,n);
Efecto: Recibe una cola y un índice (entre 1 y el tamaño de la cola) y devuelve el elemento que se encuentra en la cola en ese índice partiendo del frente de esta =1.
Excepción: Si la cola esta vacía o el índice se encuentra fuera del tamaño de la cola se produce error.
*/
elemento Element (cola *C,int n)
{
	elemento r;
	if(!(C->final+1>=n)||n<1)
	{
	    printf("\n ERROR:ELEMENT SUBDESBORDAMIENTO INTENTAS ACCEDER A UNA N INEXISTENTE ");	
		exit (1);
	}
	r=	C->A[n-1];
	return r;	
}


/*
Eliminar cola (Destroy): recibe<- cola (C); 
Destroy(C)
Efecto: Recibe una cola y la libera completamente.
*/
void Destroy(cola *C)
{
	C->final=-1;
	return;	
}


/*
Tamaño (Size): recibe<- cola (C);  retorna -> numero
n=Size (C);
Efecto: Recibe una cola y devuelve el tamaño de la cola.
*/
int Size (cola *C)
{
	int r;
	r=C->final+1;
	return r;	
}
