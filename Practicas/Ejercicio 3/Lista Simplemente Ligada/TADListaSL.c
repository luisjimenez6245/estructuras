#include "TADListaSL.h"
#include <stdio.h>
#include <stdlib.h>

//Operaciones de construcción
void Initialize(lista *l)
{
	l->tam=0;
	l->frente=NULL;
	l->final=NULL;
	return;
}
void Destroy(lista *l)
{
	posicion aux;
	while(l->frente!=NULL)
	{
		aux=l->frente->siguiente;
		free(l->frente);
		l->frente=aux;
	}
	l->final=NULL;
	l->tam=0;
	
}

//Operaciones de posicionamiento y busqueda
posicion Final(lista *l)
{
	return l->final;
}
posicion First(lista *l)
{
	return l->frente;
}
posicion Following(lista *l, posicion p)
{
	if(!ValidatePosition(l,p))
	{
		printf("ERROR: Following P INVALIDA");
		exit(1);
	}
	else
	{
		return p->siguiente;
	}
}
posicion Previous(lista *l, posicion p)
{
	posicion aux=l->frente, anterior=NULL;
	if(!ValidatePosition(l,p))
	{
		printf("ERROR: Previous P INVALIDA");
		exit(1);
	}
	else
	{
		while(aux!=NULL)
		{
			if(aux==p)
			{
				return anterior;
			}
			anterior=aux;
			aux=aux->siguiente;
		}
	}	
	
}


posicion Search(lista *l, elemento e)
{
	posicion aux=l->frente;
	while(aux!=NULL)
	{
		if(memcmp(&e,&(aux->e),sizeof(elemento))==0)
		{
			return aux;
		}
		aux=aux->siguiente;
	}
	return aux;
}
//Operación de consulta
elemento Position(lista *l, posicion p)
{
	if(ValidatePosition(l,p))
	{
		return p->e;
	}
	else
	{
		printf("ERROR (Position): P es invalida");
		exit(1);
	}
	
}

boolean ValidatePosition(lista *l, posicion p)
{
	posicion aux;
	aux=l->frente;
	while(aux!=NULL)
	{
		if(p==aux)
			return TRUE;
		else
			aux=aux->siguiente;
	}
	return FALSE;
}


elemento Element(lista *l, int n)
{
	int i;
	posicion aux=l->frente;
	if(n>=1&&n<=Size(l))
	{
		for(i=2;i<=n;i++)
			aux=aux->siguiente;
		return aux->e;
	}		
	else
	{
		printf("ERROR (Element): n fuera del rango");
		exit(1);
	}
}

posicion ElementPosition(lista *l, int n)
{
	int i;
	posicion aux=l->frente;
	if(n>=1&&n<=Size(l))
	{
		for(i=2;i<=n;i++)
			aux=aux->siguiente;
		return aux;
	}		
	else
	{
		printf("ERROR (Element): n fuera del rango");
		exit(1);
	}
}

int Size(lista *l)
{
/*	posicion aux=l->frente;
	int tam=0;
	
	while(aux!=NULL)
	{
		tam++;
		aux=aux->siguiente;
	}
	return tam;*/
	return l->tam;
	
}

boolean Empty(lista *l)
{
	if(Size(l)==0)
		return TRUE;
	return FALSE;
	
}

//Operaciones de modificación
void Insert(lista *l, elemento e, posicion p,boolean b)
{
	posicion aux,ant_p;
	aux=malloc(sizeof(nodo));
	if(aux!=NULL)
	{			
		aux->e=e;
		if(ValidatePosition(l,p))//Si p es valida y b=1 se inserta antes de p.
		{
			if(b==TRUE)	//Insertan antes de p
			{
				ant_p=Previous(l,p);
				if(ant_p!=NULL)
				{
					aux->siguiente=ant_p->siguiente;
					ant_p->siguiente=aux;
				}
				else
				{
					aux->siguiente=l->frente;
					l->frente=aux;
				}
			}
			else//Inserta despues de p
			{
				aux->siguiente=p->siguiente;
				p->siguiente=aux;
				if(p==l->final) //Si p es el final de lista y hay que insertar al final
					l->final=aux;		
			}
		}
		else //Insertar al frente de la listta porque p no es valida
		{
			aux->siguiente=l->frente;
			l->frente=aux;
			if(l->final==NULL)
				l->final=aux;
		}
		l->tam++;
	}
	else
	{
		printf("ERROR (Insert): No se pudo crear un nuevo elemento");
		exit(1);
	}
}

void Add(lista *l,elemento e)
{
	posicion aux,ant_p;
	aux=malloc(sizeof(nodo));
	if(aux!=NULL)
	{			
		aux->e=e;
		aux->siguiente=NULL;
		if(l->tam==0) //Si esta vacia
			l->frente=aux;
		else //Hay que conectar el ultimo de la lista con el nuevo
			l->final->siguiente=aux;	
		//La parte final de lista apunta al nuevo
		l->final=aux;
		l->tam++;
	}
	else
	{
		printf("ERROR (Add): No se pudo crear un nuevo elemento");
		exit(1);
	}	
}

void Remove(lista *l,posicion p)
{
	posicion ant_p;
	if(ValidatePosition(l,p))
	{
		if(p==l->frente)//Si la posicion a eliminar es la primera de la lista
		{
			l->frente=l->frente->siguiente;
			if(l->final==p)
				l->final=NULL;
		}
		else
		{
			ant_p=Previous(l,p);
			ant_p->siguiente=p->siguiente;
			if(p==l->final)//Si el elemnto a remover es el del final
				l->final=ant_p;
		}
		free(p);
		l->tam--;
	}
	else
	{
		printf("ERROR (Remove):p es invalida");
		exit(1);
	}
}

void Replace(lista *l,posicion p, elemento e)
{
	if(ValidatePosition(l,p))
	{
		p->e=e;
	}
	else
	{
		printf("ERROR (Replace):p es invalida");
		exit(1);
	}
}
