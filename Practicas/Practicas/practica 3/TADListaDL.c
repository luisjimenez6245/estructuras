/*
IMPLEMENTACION DE LA LISTA DOBLEMENTE LIGADA
AUTOR: VLADIMIR AZPEITIA HERNANDEZ 1CM12
VERSIÓN: 1.0

DESCRIPCIÓN: TAD lista
Estructura de datos lineal en la que se cumple:
Los definicions se insertan, eliminan o renplazan en cualquier extremo o posicion de esta.

OBSERVACIONES: Una Lista es una Estructura de datos dinámica (se le asigna memoria a medida que es necesitada, 
durante la ejecución del programa). Una lista doblemente ligada contiene apuntadores a los definicions siguientes
y anteriores, a diferencia de una lista simplemente ligada que solo contiene apuntadores a los siguientes definicions.

COMPILACIÓN PARA GENERAR EL EJECUTABLE: gcc Prueba.c TADListaDL.o | TADListaDL.c
*/

//Librerias
#include "TADListaDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//DEFINICIÓN DE FUNCIONES

//Operaciones de construcción


/*
void Initialize(lista *l);
Descripción: Inicializar lista (Iniciar una lista para su uso)
Recibe: int *l (Referencia a la lista "l" a operar)
Devuelve: 
Observaciones: El usuario a creado una lista y l tiene la referencia a ella, 
si esto no ha pasado se ocasionara un error.
*/
void Initialize(lista *l)
{
	l->tam=0; //Tamanio de la lista
	l->frente=NULL; //Posicion frente(inicio) de la listal->final
	l->final=NULL; //Posicion final de la listal->final
	return;
}

/*
void Destroy(lista *l);
Descripción: Elimina lista (Borra a todos los definicions en a la lista de memoria)
Recibe: int *l (Referencia a la lista "l" a operar)
Devuelve: 
Observaciones: El usuario a creado una lista y l tiene la referencia a ella, l ya ha sido inicializada.
*/
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

/*
void Final(lista *l);
Descripción: Devuelve la posicion del definicion que se encuentre al final de la lista 
Recibe: int *l (Referencia a la lista "l" a operar)
Devuelve: posicion(del ultimo definicion de la lista)
*/
posicion Final(lista *l)
{	
	return l->final;
}

/*
void First(lista *l);
Descripción: Devuelve la posicion del definicion que se encuentre al principio de la lista 
Recibe: int *l (Referencia a la lista "l" a operar)
Devuelve: posicion(del primer definicion de la lista)
*/
posicion First(lista *l)
{
	return l->frente;
}

/*
void Following(lista *l, posicion p);
Descripción: Te devuelve el definicion siguiente, respecto a otro definicion
Recibe: int *l (Referencia a la lista "l" a operar), posicion(Posicion del definicion)
Devuelve: posicion(del definicion siguiente a p)
*/
posicion Following(lista *l, posicion p)
{
	if(!ValidatePosition(l,p))
	{
		printf("ERROR: Following P INVALIDA");
		exit(1);
	}
	else
	{
		return p->siguiente; // Retornamos la posicion siguiente a p
	}
}

/*
void Previous(lista *l, posicion p);
Descripción: Te devuelve el definicion siguiente, respecto a otro definicion
Recibe: int *l (Referencia a la lista "l" a operar), posicion(Posicion del definicion)
Devuelve: posicion(del definicion anterior a p)
*/
posicion Previous(lista *l, posicion p)
{
	if(!ValidatePosition(l,p))
	{
		printf("ERROR: Previous P INVALIDA");
		exit(1);
	}
	else
	{
		return p->anterior; //Retornamos la posicion anterior a p
	}	
	
}

/*
void posicion Search(lista *l, definicion e);
Descripción: Busca al definicion en la lista y si lo encutra lo devuelve
Recibe: int *l (Referencia a la lista "l" a operar), definicion e(definicion a buscar)
Devuelve: posicion(del definicion que se busco)
*/
posicion Search(lista *l, definicion e){
	posicion aux=l->frente;
	int s=0;
	while(aux!=NULL){
		// if(memcmp(&e,&(aux->e),sizeof(definicion))==0)
		// {
		// 	return aux;
		// }
		if(strcmp(&aux->e.palabra[0], &e.palabra[0]) == 0){
			aux->saltos = s;
			return aux;
		}
		aux=aux->siguiente;
		s++;
	}
	return aux;
}
//Operación de consulta
/*
definicion Position(lista *l, posicion p);
Descripción: Devuelve el definicion que esta en la posicion dada
Recibe: int *l (Referencia a la lista "l" a operar), posicion p(posicion a buscar)
Devuelve: definicion(que contiene la posicion p)
*/
definicion Position(lista *l, posicion p)
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
/*
boolean ValidatePosition(lista *l, posicion p);
Descripción: Verifica que la posicion pertenesca a un definicion en la lista
Recibe: int *l (Referencia a la lista "l" a operar), posicion p(posicion a evaluar)
Devuelve: boolean(TRUE si la posicion es valida o FALSE en caso contrario)
*/
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

/*
definicion Element(lista *l, int n);
Descripción: Devuelve el definicion que esta en en indice dado(1 - Size(l))
Recibe: int *l (Referencia a la lista "l" a operar), posicion p(posicion a buscar)
Devuelve: definicion(que esta en la posicion n)
*/
definicion Element(lista *l, int n)
{
	int i;
	posicion aux;
	if(n>=1&&n<=Size(l)) //Validamos que nos den un indice correcto
	{
		if(Size(l)/2>n){ //Si el indice esta entre el primer definicion y la mitad de la lista
			aux=l->frente; //Comezamos desde la posicion del frente
			for(i=2;i<=n;i++)
				aux=aux->siguiente; //Cambiamos a la siguiente posicion
			return aux->e; //Retornamos el definicion de la posicion en la que quedamos
		}else{
			aux=Final(l); //Comenzamos desde el final de la lista
			for(i=Size(l);i>n;i--)	//Vamos recorriendo la lista desde el final hasta la mitad de la lista
				aux=aux->anterior; //Cambiamos a una posicion anterior
			return aux->e; //Retornamos el definicion de la posicion en la que quedamos
		}
	}		
	else
	{
		printf("ERROR (Element): n fuera del rango");
		exit(1);
	}
}
/*
definicion Element(lista *l, int n);
Descripción: Devuelve el definicion que esta en en indice dado(1 - Size(l))
Recibe: int *l (Referencia a la lista "l" a operar), posicion p(posicion a buscar)
Devuelve: definicion(que esta en la posicion n)
*/
posicion ElementPosition(lista *l, int n)
{
	int i;
	posicion aux;
	if(n>=1&&n<=Size(l))
	{
		if(Size(l)/2>n){ //Si el indice esta entre el primer definicion y la mitad de la lista
			aux=l->frente;
			for(i=2;i<=n;i++) //Comezamos a recorrer desde la posicion 2 
			aux=aux->siguiente; //Cambiamos a la siguiente posicion
			return aux; //Retornamos la posicion en la que quedamos 
		}else{ //En caso contrario
			aux=Final(l);
			for(i=Size(l);i>n;i--) //Comenzamos desde el final de la lista
			aux=aux->anterior; //Cambiamos a la posicion anterior
			return aux;//Retornamos la posicion en la que quedamos 
		}
	}		
	else
	{
		printf("ERROR (Element): n fuera del rango");
		exit(1);
	}
}
/*
int Size(lista *l);
Descripción: Tamaño de la lista (Obtener el número de definicions en la lista)
Recibe: int *l (Referencia a la lista "l" a operar)
Devuelve: int (Tamaño de la lista -1->Vacia, 1->1 definicion, 2->2 definicions, ...)
Observaciones: El usuario a creado una lista y l tiene la referencia a ella, l ya ha sido inicializada.
*/
int Size(lista *l)
{
	return l->tam;
}
/*
boolean Empty(lista *s);
Descripción: //Vacia (Preguntar si la lista esta vacia)
Recibe: int *s (Referencia a la lista "s" a operar)
Devuelve: boolean (TRUE o FALSE según sea el caso)
Observaciones: El usuario a creado una lista y s tiene la referencia a ella, s ya ha sido inicializada.
*/
boolean Empty(lista *l)
{
	if(Size(l)==0)
		return TRUE;
	return FALSE;
	
}

//Operaciones de modificación

/*
void Insert(lista *l, definicion e, posicion p,boolean b);
Descripción: Inseta un definicion en la lista en la posicion que tu especifiques 
Recibe: int *l (Referencia a la lista "l" a operar), definicion e(que se deseea insertar), posicion p
a donde se desee insertar, y finalmente un booolean(si es TRUE lo insrta antes de p, de lo contraro lo
inserta despues)
Devuelve: 
*/
void Insert(lista *l, definicion e, posicion p,boolean b)
{
	posicion aux; //Creamos una nueva posicion
	aux=malloc(sizeof(nodo)); //Reservamos espacion en memoria
	if(aux!=NULL) //Si nos dieron memoria
	{			
		aux->e=e; //Guardamos el definicion en la posicion que acabamos de crear
		if(ValidatePosition(l,p))//Si p es valida y b=1 se inserta antes de p.
		{
			if(b==TRUE)	//Insertan antes de p
			{
				if(p->anterior!=NULL) //Si la posicion que nos dieron NO es el frente
				{
					aux->siguiente=p; //La nueva posicion apuntara a la posicion p
					aux->anterior=p->anterior; //La nueva posicion apuntara al definicion anterion a p
					p->anterior=aux; //Conectamos la nueva posicion con p
					p->anterior->siguiente=aux; //Conectamos la nueva posicion con la posicion anterior a p
				}
				else //Si la posicion que nos dieron SI es el frente
				{
					aux->siguiente=l->frente; //Conectamos la nueva posicion con el frente
					aux->anterior=NULL; //Como la nueva posicion sera el frente no tendra posicion antecesora(anterio = NULL)
					l->frente->anterior=aux; //Conectamos el frente anterior con el nuevo frente
					l->frente=aux; //Ahora el nuevo frente sera la nueva posicion
				}
			}
			else//Inserta despues de p
			{
				
				if(p==l->final){//Si p es el final de lista y hay que insertar despues
					Add(l, e); //Llamamos a la funcion Add ya que la posicion se agregara al final de la lista
					l->tam--; //Le quitamos 1 (ya que al llamar la funcion Add)
				}else{ //Si p NO es el final de la lista
					aux->siguiente=p->siguiente; //Conectamos la nueva posicion con la posicion siguiente de p
					aux->anterior=p; //Conectamos la nueva posicion con p
					p->siguiente->anterior=aux; //Enlazamos el definicion siguiente de p con la nueva
					p->siguiente=aux;//Enlazamos a p con la nueva posicion
				} 
							
			}
		}
		else //Insertar al frente de la lista porque p no es valida
		{
			aux->siguiente=l->frente; //Conectamos la nueva posicion con el frente
			l->frente=aux;//la nueva posicion sera el frente
			aux->anterior = NULL;
			if(l->final==NULL){ //Si la lista esta vacia
				l->final=aux; //El final de la lista ahora es la nueva posicion
			}
		}
		l->tam++; //Aunmentamos el tamanio de la lista
	}
	else
	{
		printf("ERROR (Insert): No se pudo crear un nuevo definicion");
		exit(1);
	}
}
/*
void Add(lista *l,definicion e);
Descripción: Inseta un definicion al final de la lista
Recibe: int *l (Referencia a la lista "l" a operar), definicion e(que se deseea agregar a la lista)
Devuelve: 
*/
void Add(lista *l,definicion e)
{
	posicion aux; // Creamos una nueva posicion(*nodo)
	aux=malloc(sizeof(nodo)); //Reservamos espacio en memoria
	if(aux!=NULL) //Si nos dio memoria
	{			
		aux->e=e; //Guardamos el definicion en la posicion que acabamos de creear
		aux->siguiente=NULL; //Apuntamos a NULL, ya que se agregara al final de la lista
		if(l->tam==0){ //Si esta vacia
			aux->anterior=NULL; //Apunta a NULL por ser el primer definicion de la lista
			l->frente=aux; // El nuevo frente sera la nueva posicion
		}
		else{ //Hay que conectar el ultimo de la lista con el nuevo
			l->final->siguiente=aux; // Conectamos el final de la lista con la nueva posicion
			aux->anterior=l->final;  // Conctamos la nueva posicion con el final de la lista
		}
		//La parte final de lista apunta al nuevo
		l->final=aux; //Ahora la nueva posicion sera el final de la lista
		l->tam++; //Aunmentamos el tamanio de la lista
	}
	else //En caso de que no nos hallan dado memoria
	{
		printf("ERROR (Add): No se pudo crear un nuevo definicion");
		exit(1);
	}	
}
/*
void Remove(lista *l,posicion p);
Descripción: Remueve el definicion en la posicion indicada
Recibe: int *l (Referencia a la lista "l" a operar), posicion p(que se deseea remover)
Devuelve: 
*/
void Remove(lista *l,posicion p)
{
	if(ValidatePosition(l,p))
	{
		if(p==l->frente)//Si la posicion a eliminar es la primera de la lista
		{
			l->frente=l->frente->siguiente; //Movemos el frente de la lista a la sig posicion
			if(l->final==p) //Si habia un solo definicion en la lista
				l->final=NULL; //No hay ningun definicion en la lista
			else
				l->frente->anterior = NULL; //Hacemos que el nuevo frente siga apuntando a la posicion anterio del anterior frente
		}
		else
		{
			if(p==l->final){//Si el elemnto a remover es el del final
				l->final=p->anterior; //Ahora el final sera la posicion anterior
				l->final->siguiente=NULL; //Como es el final, ahora apunta a NULL como siguiente
			}
			else{ //En caso de que la posicion no sea el final 
				p->anterior->siguiente=p->siguiente; //El nodo anterior apuntara al siguiente de la posicion
				p->siguiente->anterior=p->anterior; //El nodo siguiente apuntara al anterior de la posicion
			}
		}
		free(p); //Liberamos el espacio de memoria que ocupaba p
		l->tam--; //Le restamos un definicion al total de definicions
	}
	else
	{
		printf("ERROR (Remove):p es invalida");
		exit(1);
	}
}
/*
void Replace(lista *l,posicion p, definicion e);
Descripción: Remplaza el definicion en la posicion indicada
Recibe: int *l (Referencia a la lista "l" a operar), definicion p(que se deseea remplazar)
Devuelve: 
*/
void Replace(lista *l,posicion p, definicion e)
{
	if(ValidatePosition(l,p)) //Validamos que la posicion exista dentro de la lista
	{
		p->e=e; //Remplazamos el definicion en dicha posicion
	}
	else//En caso que la posicion sea invalida
	{
		printf("ERROR (Replace):p es invalida");
		exit(1); //Cerramos la aplicacion
	}
}
