/*
	LIBRERÍA TAD ÁRBOL BINARIO AVL
	AUTORES: 
		JIMÉNEZ DELGADO LUIS DIEGO
		SÁNCHEZ CASTRO AARÓN GAMALIEL
		SÁNCHEZ TIRADO CITLALI YASMÍN
	EN COLABORACIÓN CON: 
		M. EN C. EDGARDO ADRIÁN FRANCO MARTÍNEZ 
	VERSIÓN: 1.0 
	DESCRIPCIÓN:
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADABAVL.h"

/*
FUNCIÓN: Initialize(arbolavl *A)
EFECTO: Recibe un árbol binario avl A y lo inicializa para su trabajo normal.
*/
void Initialize(Arbolavl *A)
{
	*A=NULL;
	return;
}

/*
Destroy (A)
Efecto: Recibe un árbol binario avl A y lo libera completamente.
*/
void Destroy (Arbolavl *A)
{
	if(*A!=NULL)
	{	
		Destroy(&((*A)->HijoI));
		Destroy(&((*A)->HijoD));
		free(*A);
	}
	*A=NULL;
	return;
}

/*
Buscar (Search):recibe<-Ã¡rbol(A), elemento (E); retorna -> posiciÃ³n
Search(A,E)
Efecto: Recibe un Ã¡rbol binario A y un elemento E, devuelve la posiciÃ³n del elemento E en el Ã¡rbol  A.
Requerimientos: El Ã¡rbol binario A es no vacÃ­o y la posiciÃ³n P es una posiciÃ³n valida. Si E no es encontrado devuelve una posiciÃ³n nula.
*/
posicion Search(Arbolavl *A, elemento e)
{
	posicion r=NULL;
	if(*A!=NULL)
	{
		if(memcmp(&e,&((*A)->e),sizeof(elemento))==0)
			r=*A;
		else 
		{
			r=Search(&((*A)->izq),e);
			if(r==NULL)
				r=Search(&((*A)->der),e);
		}
	}
	return r;
}

/*
Leer Nodo(Read Node):recibe<-Ã¡rbol(A), posiciÃ³n (P); retorna -> elemento
ReadNode(A,P)
Efecto: Recibe un Ã¡rbol binario A y una posiciÃ³n P, devuelve el elemento en la posiciÃ³n P del Ã¡rbol A.
Requerimientos: El Ã¡rbol A es no vacÃ­o y la posiciÃ³n P es una posiciÃ³n valida..
*/
elemento ReadNode(Arbolavl *A, posicion p)
{
	if(!NullNode(A,p))
		return p->e;
	else
	{
		printf("\nERROR (ReadNode(A,p)):La posicion P no existe en el Arbol");
		exit(1);
	}
}

/*
Nuevo Hijo Derecho(New Right Son):recibe<-Ã¡rbol(A), posiciÃ³n (P), elemento E; 
NewRightSon(A,P,E)
Efecto: Recibe un Ã¡rbol binario A, una posiciÃ³n P y un elemento E, se aÃ±ade un nodo que contenga E como hijo derecho del nodo con posiciÃ³n P.
Requerimientos: El Ã¡rbol binario A es no vacÃ­o y la posiciÃ³n P es una posiciÃ³n valida. Si el Ã¡rbol A es vacÃ­o se agrega a un nodo raÃ­z con E. si P ya tiene un hijo derecho, se cancela la operaciÃ³n.
*/
void NewRightSon(Arbolavl *A, posicion p, elemento e)
{
	//Si el Ã¡rbol es vacio
	if(*A==NULL)
	{
		*A=malloc(sizeof(nodo));
		if(*A==NULL)
			{
				printf("\nERROR (NewRightSon(A,p,e)):No se pudo crear un nuevo nodo raÃ­z");
				exit(1);				
			}
			(*A)->e=e;
			(*A)->der=NULL;
			(*A)->izq=NULL;
	}		
	else if(!NullNode(A,p))
	{
		if(p->der==NULL)
		{
			p->der=malloc(sizeof(nodo));
			if(p->der==NULL)
			{
				printf("\nERROR (NewRightSon(A,p,e)):No se pudo crear un nuevo nodo");
				exit(1);				
			}
			p->der->e=e;
			p->der->der=NULL;
			p->der->izq=NULL;
		}	
		else
		{
			printf("\nERROR (NewRightSon(A,p,e)):P ya tiene un hijo derecho");
			exit(1);					
		}
	}
	else
	{
		printf("\nERROR (NewRightSon(A,p,e)):la posicion P no existe");
		exit(1);				
	}
	return;
}

/*
Nuevo Hijo Izquierdo(New Left Son):recibe<-Ã¡rbol(A), posiciÃ³n (P), elemento E; 
NewLeftSon(A,P,E)
Efecto: Recibe un Ã¡rbol binario A, una posiciÃ³n P y un elemento E, se aÃ±ade un nodo que contenga E como hijo izquierdo del nodo con posiciÃ³n P.
Requerimientos: El Ã¡rbol binario A es no vacÃ­o y la posiciÃ³n P es una posiciÃ³n valida. Si el Ã¡rbol A es vacÃ­o se agrega a un nodo raÃ­z con E; si P ya tiene un hijo Izquierdo, se cancela la operaciÃ³n.
*/
void NewLeftSon(Arbolavl *A, posicion p, elemento e)
{
	//Si el Ã¡rbol es vacio
	if(*A==NULL)
	{
		*A=malloc(sizeof(nodo));
		if(*A==NULL)
			{
				printf("\nERROR (NewLeftSon(A,p,e)):No se pudo crear un nuevo nodo raÃ­z");
				exit(1);				
			}
			(*A)->e=e;
			(*A)->der=NULL;
			(*A)->izq=NULL;
	}		
	else if(!NullNode(A,p))
	{
		if(p->izq==NULL)
		{
			p->izq=malloc(sizeof(nodo));
			if(p->izq==NULL)
			{
				printf("\nERROR (NewLeftSon(A,p,e)):No se pudo crear un nuevo nodo");
				exit(1);				
			}
			p->izq->e=e;
			p->izq->der=NULL;
			p->izq->izq=NULL;
		}	
		else
		{
			printf("\nERROR (NewLeftSon(A,p,e)):P ya tiene un hijo izquierdo");
			exit(1);					
		}
	}
	else
	{
		printf("\nERROR (NewLeftSon(A,p,e)):la posicion P no existe");
		exit(1);				
	}
	return;	
}

/*
Eliminar Hijo Derecho (Delete Right Son):recibe<-Ã¡rbol(A), posiciÃ³n (P);
DeleteRightSon(A,P)
Efecto: Recibe un Ã¡rbol binario A y una posiciÃ³n se elimina al hijo derecho y todos sus descendientes del nodo con posiciÃ³n P.
Requerimientos: El Ã¡rbol A es no vacÃ­o y la posiciÃ³n P es una posiciÃ³n valida y tiene un hijo derecho.
*/
void DeleteRightSon(Arbolavl *A, posicion p)
{
	if(*A!=NULL)
	{
		Destroy(&(p->der));
	}
	else
	{
		printf("\nERROR (DeleteRightSon(A,p)):la posicion P no existe");
		exit(1);						
	}
	return;
}

/*
Eliminar Hijo Izquierdo(Delete Left Son):recibe<-Ã¡rbol(A), posiciÃ³n (P);
DeleteLeftSon(A,P)
Efecto: Recibe un Ã¡rbol binario A y una posiciÃ³n se elimina al hijo izquierdo y todos sus descendientes del nodo con posiciÃ³n P.
Requerimientos: El Ã¡rbol A es no vacÃ­o y la posiciÃ³n P es una posiciÃ³n valida y tiene un hijo izquierdo.
*/
void DeleteLeftSon(Arbolavl *A, posicion p)
{
	if(*A!=NULL)
	{
		Destroy(&(p->izq));
	}
	else
	{
		printf("\nERROR (DeleteLeftSon(A,p)):la posicion P no existe");
		exit(1);						
	}
	return;
}

/*
Eliminar Nodo(Delete Node):recibe<-Ã¡rbol(A), posiciÃ³n (P);
DeleteNode(A,P)
Efecto: Recibe un Ã¡rbol binario A y una posiciÃ³n P, se elimina al nodo con posiciÃ³n  P  y todos sus descendientes.
Requerimientos: El Ã¡rbol A es no vacÃ­o y la posiciÃ³n P es una posiciÃ³n valida. 
*/
void DeleteNode(Arbolavl *A, posicion p)
{
	if(*A!=NULL)
	{
		Destroy(&p);
	}
	else
	{
		printf("\nERROR (DeleteNode(A,p)):la posicion P no existe");
		exit(1);						
	}
	return;
}

/*
Remplazar Nodo(Replace Node):recibe<-Ã¡rbol(A), posiciÃ³n (P), elemento (E);
ReplaceNode(A,P,E)
Efecto: Recibe un Ã¡rbol binario A, una posiciÃ³n P y un elemento E, se remplaza a E del nodo con posiciÃ³n P en A.
Requerimientos: El Ã¡rbol binario A es no vacÃ­o y la posiciÃ³n P es una posiciÃ³n valida. 
*/
void ReplaceNode(Arbolavl *A,posicion p, elemento e)
{
	if(*A!=NULL)
	{
		p->e=e;
	}
	else
	{
		printf("\nERROR (ReplaceNode((A,p,e)):la posicion P no existe");
		exit(1);						
	}
	return;	
}

int GetHeight(Arbolavl *A, Posicion p, int Altura){
	if(*A!=NULL){
		
	}
}