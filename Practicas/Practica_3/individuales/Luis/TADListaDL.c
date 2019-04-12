/*
IMPLEMENTACIONES DE LA LIBRERIA DEL TAD LISTA (TADLista.h)
AUTOR: Luis Diego Jiménez DelgadoC) 
VERSION: 1.0 (Abril 2019)

DESCRIPCION: TAD lista o (list)
Estructura de datos en la que se cumple:
Los elementos se consultan, aniaden y se remueven con base en posiciones 
dentro de un arreglo lineal el cual cuenta con un frente o cabeza 
y un final o cola.

OBSERVACIONES: TADLista por definicion es una Estructura de Datos dinamica. 
La implementacion del presente codigo se realiza mediante el principo de "Lista Doblemente Ligada"
i.e. nodos que contienen un elemento y se encuentran ligados hacia siguiente de estos y al anterior de estos.

Frente                                                       Final
      	  ******    ******    ******    ******    ******    ******
NULL  <-  *    * <- *    * <- *    * <- *    * <- *    * <- *    *
    	  * N1 *    * N2 *    * N3 *    * N4 *    * N5 *    * N6 *
      	  *    * -> *    * -> *    * -> *    * -> *    * -> *    * -> NULL
      	  ******    ******    ******    ******    ******    ******    

COMPILACION PARA GENERAR EL CODIGO OBJETO: gcc TADListaDL.c -c 
*/

//LIBRERAS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "TADListaDL.h" 

//DEFINICION DE FUNCIONES

/***************************************************
Operaciones de construccion
***************************************************/
/*
void Initialize(lista *l)
Descripcion: Inicializar lista (Iniciar una lista para su uso)
Recibe: lista *l (Referencia a la lista "l" a operar)
Devuelve:
Observaciones: El usuario a creado una lista y l tiene la referencia a ella, 
si esto no ha pasado se ocasionara un error.
*/
void Initialize (lista *l)
{
	l->frente=NULL;
	l->final=NULL;
	l->tamanio=0;
	return;
}


/*
void Destroy(lista *l)
Descripcion: Destruir una lista (Recibe una lista l y la libera completamente)
Recibe: lista *l (Referencia a la lista "l" a operar)
Devuelve:
Observaciones: El usuario a creado una lista y l tiene la referencia a ella, 
si esto no ha pasado se ocasionara un error.
*/
void Destroy (lista *l)	
{
	//Apuntador auxiliar a nodo
	nodo *aux;
	
	//Mientras el apuntador del frente de la lista no sea "NULL"
	while(l->frente != NULL)
	{
		//Guardar la referencia el frente
		aux = l->frente;
		
		//El nuevo frente es el siguiente
		l->frente = l->frente->siguiente;
		
		//Liberar el antiguo frente de memoria
		free(aux);
	}

	//Colocar el final inicializado en "NULL"
	l->final = NULL;
	l->tamanio = 0;
	
	return;
}

/***************************************************
Operaciones de posicionamiento y busqueda
***************************************************/
/*
posicion Final(lista *l)
Descripcion: Recibe una lista l y regresa la posicion del final (Recibe una 
lista l y retorna la posicion del elemento al final de esta.)
Recibe: lista *l (Referencia a la lista "l" a operar)
Devuelve: posicion del nodo que contiene al elemeto final de la lista
Observaciones: El usuario a creado una lista y l tiene la referencia a ella, 
si esto no ha pasado se ocasionara un error.
*/
posicion Final (lista *l)
{
	return l->final;
}

/*
posicion First(lista *l)
Descripcion: Recibe una lista l y regresa la posicion del frente (Recibe una 
lista l y retorna la posicion del elemento al frente de esta.)
Recibe: lista *l (Referencia a la lista "l" a operar)
Devuelve: posicion del nodo que contiene al elemento del frente de la lista
Observaciones: El usuario a creado una lista y l tiene la referencia a ella, 
si esto no ha pasado se ocasionara un error.
*/
posicion First (lista *l)
{
	return l->frente;
}

/*
posicion Following(lista *l, posicion p)
Descripcion: Recibe una lista l, una posicion p y devuelve la posicion del 
elemento siguiente de p
Recibe: lista *l y posicion p (Referencia a la lista "l" a operar y posicion valida de la lista)
Devuelve: posicion del nodo siguiente a la posicion dada
Observaciones: El usuario a creado una lista y l tiene la referencia a ella, p es una posicion valida de la lista, 
si esto no ha pasado se ocasionara un error.
*/
posicion Following (lista *l,posicion p)
{
	if(ValidatePosition(l,p))
	{
		return p->siguiente;
	}	
	else
	{
		printf("ERROR: Funcion Following (p es invalida)");
		exit(1);
	}
}


/*
posicion Previous(lista *l, posicion p)
Descripcion: Recibe una lista L, una posicion P y devuelve la posicion del 
elemento anterior de P
Recibe: lista *l y posicion p (Referencia a la lista "l" a operar y posicion valida de la lista)
Devuelve: posicion del nodo anterior a la posicion dada
Observaciones: El usuario a creado una lista y l tiene la referencia a ella, p es una posicion valida de la lista, si esto no ha pasado se ocasionara un error.
*/
posicion Previous (lista *l,posicion p)
{
	if(ValidatePosition(l,p))
	{
		return p->anterior;
	}	
	else
	{
		printf("ERROR: Funcion Following (p es invalida)");
		exit(1);
	}	
}


/*
posicion Search(lista *l, elemento e)
Descripcion: Recibe una lista l y un elemento e, regresa la posicion que coincida exactamente con el elemento e.
Recibe: lista *l y un elemento e (Referencia a la lista "l" a operar y elemento a buscar en la lista)
Devuelve: posicion del elemento en caso de ser encontrado, si no se encuentra se devuelve una posicion invalida
Observaciones: El usuario a creado una lista y l tiene la referencia a ella el elemento a buscar se compara directamente 
a nivel de bytes. 
*/
posicion Search (lista *l,elemento e)
{	
	posicion aux=l->frente;
	while(aux!=NULL)
	{
		if(memcmp(&aux->e,&e,sizeof(elemento))==0)
		{
			return aux;			
		}
		aux=aux->siguiente;
	}
	return NULL;
}

/***************************************************
Operaciones de consulta
/***************************************************/
/*
elemento Position(lista *l, posicion p)
Descripcion: Recibe una lista l, una posicion p y devuelve el elemento en dicha posicion. 
Recibe: lista *l y una posicion p(Referencia a la lista "l" a operar posicion valida en la lista)
Devuelve: Elemento en la posicion dada, si la posicion es invalida se genera error.
Observaciones: La lista l es no vacia y la posición p es una posicion valida.
*/
elemento Position (lista *l,posicion p)
{
	elemento e;
	if(ValidatePosition(l,p))
		return p->e;
	else
	{
		printf("\nERROR Position(): La posicion es invalida");
		exit(1);
	}
}

/*
boolean ValidatePosition(lista *l, posicion p)
Descripcion: Recibe una lista l, una posicion p y devuelve TRUE si la posicion es una posicion p valida en la lista l y FALSE en caso contrario.
Recibe: lista *l y una posicion p(Referencia a la lista "l" a operar y una posicion)
Devuelve: Booleano 
Observaciones:
*/
boolean ValidatePosition (lista *l,posicion p)
{
	posicion aux;
	aux=l->frente;
	while(aux!=NULL)
	{		
		if(aux==p) //**************
			return TRUE;	
		aux=aux->siguiente;		
	}	
	return FALSE;	
}

/*
elemento Element(lista *l, int n)
Descripcion: Recibe una lista y un indice (entre 1 y el tamaño de la lista) y devuelve el elemento que se encuentra en la lista en ese indice partiendo del frente de este =1 hacia anterior.
Recibe: lista *l y una entero
Devuelve: elemento 
Observaciones: Si la cola esta vacia o el indice se encuentra fuera del tamaño de la lista se produce error.
*/
elemento Element(lista *l, int n)
{
	elemento r;
	nodo *aux;
	int i;
	//Si el elemento solicitado esta entre 1 y el tamaoo de la lista
	if (n>0&&n<=Size(l))
	{
		//Obtener el elemento en la posicion n
		aux=l->frente;
		for(i=2;i<=n;i++)
			aux=aux->siguiente;
		r=aux->e;
	}
	else
	{
		printf("\nERROR (Element): Se intenta acceder a elemento %d inexistente",n);
		exit(1);		
	}
	return r;	
}

/*
posicion ElementPosition(lista *l, int n)
Descripcion: Recibe una lista y un indice (entre 1 y el tamanio de la lista) y devuelve la posicion del elemento que se encuentra en la lista en ese índice partiendo del frente de este =1 hacia atrás.
Recibe: lista *l y una entero
Devuelve: posicion 
Observaciones: Si la cola esta vaciaa o el indice se encuentra fuera del tamanio de la lista se produce error.
*/
posicion ElementPosition(lista *l, int n)
{
	posicion aux=NULL;
	int i;
	//Si el elemento solicitado esta entre 1 y el tamanio de la lista
	if (n>0&&n<=Size(l))
	{
		//Obtener el elemento en la posicion n
		aux=l->frente;
		for(i=2;i<=n;i++)
			aux=aux->siguiente;
		return aux;
	}
	else
	{
		printf("\nERROR (ElementPosition): Se intenta acceder a posicion %d inexistente",n);
		exit(1);		
	}
	return aux;			
}

/*
int Size(lista * l);
Descripcion: Recibe una lista y devuelve el numero de elemento que se encuentran en esta.
Recibe: lista *l (Referencia a la lista "l")
Devuelve: int (Tamaño de la lista)
Observaciones: El usuario a creado una lista,la lista fue correctamente inicializada.
*/
int Size (lista *l)
{
	return l->tamanio;
}

/*
int Size(lista * l);
Descripción: Recibe una lista l y devuelve TRUE en caso de que la lista este vacia y FALSE en caso contrario.
Recibe: lista *l (Referencia a la lista "l")
Devuelve: boolean (TRUE o FALSE)
Observaciones: El usuario a creado una lista,la lista fue correctamente inicializada.
*/
boolean Empty (lista *l)
{
	return (l->tamanio==0) ? TRUE:FALSE;
}
/***************************************************
Operaciones de modificacion
****************************************************/
/*
void Insert (lista * l, posicion p, elemento e, boolean b);
Descripcion: Inserta un elemento e en la lista este debera agregarse al frente de p 
si b es verdadero y anterior de p en caso contrario. Si p es invalida 
Recibe: lista *l (Referencia a la lista "l"), posicion p (Posicion valida o invalida en la lista), 
elemento e (Elemento a insertar en la lita), boolean b (Indicador de insercion antes de p=TRUE o despues de p =FALSE)
Devuelve: 
Observaciones: El usuario a creado una lista,la lista fue correctamente inicializada, si P es no valida o NULL, 
se insertara a e al frente de la lista.
*/
void Insert (lista * l, posicion p, elemento e, boolean b)
{
	nodo *aux,*aux2; //posicion aux;
	
	//Crear el nodo e insertar e	
	aux=malloc(sizeof(nodo));
	
	//Si no se puede reservar memoria para el nuevo nodo (ERROR de lista) 
	if(aux==NULL)
	{
		printf("\nERROR (Insert): No se puede crear un nuevo nodo");
		exit(1);
		
	}
	
	//Introducir a e en el nuevo nodo
	aux->e=e;	
	
	//Validamos la posicion p
	if(!ValidatePosition(l,p))
	{//Si es invalida insertar al frente de la lista
		if(l->final!=NULL) //Si la lista no esta vacia
		{
			aux->siguiente=l->frente;
			aux->anterior=NULL;
			l->frente=aux;
		}
		else//Si esta vacia
		{
			aux->siguiente=l->frente;
			aux->anterior=l->final;
			l->frente=aux;
			l->final=aux;
			
		}
	}
	else
	{//Si p es valida
		//Si p es FALSE debera agregarse despues de la posicion p
		if(b==FALSE)
		{
			//Si p no es e final
			if(p!=l->final)
			{
				aux->siguiente=p->siguiente;
				aux->anterior=p;
				p->siguiente=aux;
			}
			else //Si p es el final
			{
				aux->siguiente=p->siguiente;
				aux->anterior=p;
				p->siguiente=aux;
				l->final=aux;
			}
		}
		else
		{//Si p es TRUE debera agregarse antes de la posicion p
			
			//Si p->anterior no existe (p es el frente)
			if(p->anterior==NULL)
			{
				aux->siguiente=l->frente;
				aux->anterior=NULL;
				p->anterior=aux;
				l->frente=aux;					
			}
			else
			{
				aux->siguiente=p;
				aux->anterior=p->anterior;
				p->anterior=aux;				
			}
		}
	}
	//Aumentar el tamanio de la lista
	l->tamanio++;
	return;
}

/*
void Add (lista *l,elemento e);
Descripcion: Recibe una lista l y un elemento e, se agrega a e al final de la lista l.
Recibe: lista *l (Referencia a la lista "l"), elemento e (Elemento a insertar en la lita)
Devuelve: 
Observaciones: El usuario a creado una lista,la lista fue correctamente inicializada.
*/
void Add (lista *l,elemento e)
{
	posicion aux;	
	aux=malloc(sizeof(nodo));
	
	//Si no se puede reservar memoria para el nuevo nodo (ERROR de lista) 
	if(aux==NULL)
	{
		printf("\nERROR (Add): No se puede crear un nuevo nodo");
		exit(1);
	}
	
	//Agregar el elemento al nodo
	aux->e=e;
	
	//Si la lista esta vacia
	if(l->final==NULL&&l->frente==NULL&&l->tamanio==0)
	{
		aux->siguiente=NULL;
		l->frente=aux;
		l->final=aux;								
	}
	//Si la lista no esta vacia
	else
	{
		aux->siguiente=NULL;
		aux->anterior=l->final;
		l->final->siguiente=aux;
		l->final=aux;
	}
//Incrementar el tamaniode la lista	
	l->tamanio++;
	return;
}

/*
void Remove (lista *l,posicion p);
Descripcion: Recibe una lista l y una posicion p, el elemento en la posicipn p sera removido.
Recibe: lista *l (Referencia a la lista "l"), posicion p (posicion a eliminar en la lista)
Devuelve: 
Observaciones: El usuario a creado una lista,la lista fue correctamente inicializada, la posicion p es valida.
*/
void Remove (lista *l,posicion p)
{
	
	//Si p es valida
	if(ValidatePosition(l,p))
	{
		//Si la p es frente y final (Solo hay uno en la lista)
		if(p==l->final&&p==l->frente)
		{
			free(p);
			l->final=NULL;
			l->frente=NULL;
			l->tamanio=0;
		}		
		//Si la p es el final
		else if(p==l->final)
		{
			p->anterior->siguiente=NULL;
			l->final=p->anterior;
			l->tamanio--;
			free(p);
		}
		//Si la p es el frente
		else if(p==l->frente)
		{
			l->frente=l->frente->siguiente;
			l->frente->anterior=NULL;
			free(p);
			l->tamanio--;
		}
		else//Si p esta en medio
		{

			p->anterior->siguiente=p->siguiente;
			free(p);
			l->tamanio--;
		}		
	}
	else
	{
		printf("\nERROR: Remove p es invalida");
		exit(1);
	}
	
	return;
}


/*
void Replace (lista *l,posicion p, elemento e);
Descripcion: Recibe una lista l, una posicion p y un elemento e, el elemento en la posicion p sera sustituido por e
Recibe: lista *l (Referencia a la lista "l"), posicion p (posicion a remplazar en la lista), elemento e (elemento que remplazara al existente en p)
Devuelve: 
Observaciones: El usuario a creado una lista,la lista fue correctamente inicializada, la posicion p es valida.
*/
void Replace (lista *l,posicion p, elemento e)
{
	//Si la posicion p existe
	if(ValidatePosition(l,p))
	{
		p->e=e; //Remplazar a e
	}
	else
	{
		printf("\nERROR: Replace : No se puede remplazar una posicion invalida");
		exit(1);
	}
	return;
}

/********************************************************************************
//Funcion para usarse en depuracion, la cual imprime las direcciones de 
//memoria de los nodos y su apuntador a siguiente
********************************************************************************/
void VerLigasLista(lista *l)
{
	posicion aux;	
	aux=l->frente;	
	printf("\n*************************************************************");
	while(aux!=NULL)
	{
		printf("\nPosicion=%p\tSiguiente=%p\tanterior=%p",aux,aux->siguiente,aux->anterior);
		aux=aux->siguiente;
	}
	printf("\n*************************************************************");

	return;
}
