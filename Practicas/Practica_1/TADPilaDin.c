/*
IMPLEMENTACIÓN DEL TAD PILA DINÁMICA (TADPilaDin.h)
AUTORES:
    Jiménez Delgado Luis Diego (C) Febrero 2019
    Sánchez Castro Aarón Gamaliel (C) Febrero 2019
    Sánchez Tirado Citlali Yasmín (C) Febrero 2019
VERSIÓN: 1.0
DESCRIPCIÓN:
    Estructura de datos que permite su almacenamiento y recuperación, el modo de acceso a los elementos
    es del tipo LIFO (Last In, First Out). Cuenta con múltiples operaciones que se describen a detalle
    en su respectiva función.
OBSERVACIONES:
    El presente archivo implica la construcción de una pila (stack) dinámica, es decir, la memoria
    que utiliza el programa para almacenar los elementos varía durante el tiempo de ejecución del mismo.
*/

//LIBRERÍAS UTILIZADAS
#include <stdio.h>
#include <stdlib.h>
#include "TADPilaDin.h"

/*
FUNCIÓN: void Initialize(stack *s);
DESCRIPCIÓN: Inicializar pila (Iniciar una pila para su uso).
RECIBE: int *s (Referencia a la pila <<stack>> "s" a operar).
DEVUELVE: Nada.
OBSERVACIONES: El usuario crea una pila s y deberá inicializarla para su uso haciendo referencia a ella,
en caso contrario se producirá un error.
*/
void Initialize(stack *s)
{
    s->top=NULL;
    s->size=0;
    return;
}
/*
FUNCIÓN: void Push(stack *s, element e)
DESCRIPCIÓN: Agrega el elemento indicado a la pila (stack) "s".
RECIBE: int *s (Referencia a la pila <<stack>> "s" a operar), element e (Elemento a introducir en la pila).
DEVUELVE: Nada.
OBSERVACIONES: El usuario debe haber inicializado la pila <<stack>> previamente. Se comprueba que malloc()
aparte memoria correctamente, en caso contrario se imprime el error.
*/
void Push(stack *s, element e)
{
    node *aux_node;
    aux_node=malloc(sizeof(node));
    if(aux_node==NULL)
      printf("\nERROR Push(stack *s, element e): NO SE HA OTORGADO MEMORIA PARA EL SIGUIENTE NODO");
      exit(1);
    aux_node->element=e;
    aux_node->below=s->top;
    s->top=aux_node;
    s->size++;
    return;
}
/*
FUNCIÓN: boolean Empty(stack *s)
DESCRIPCIÓN: Verifica si la pila consultada se encuentra vacía.
RECIBE: int *s (Referencia a la pila <<stack>> "s" a operar).
DEVUELVE: boolean TRUE o FALSE, según sea el caso.
OBSERVACIONES: El usuario ha creado e inicializado previamente la pila.
*/
boolean Empty(stack *s)
{
    boolean value;
    s->top==NULL?value=TRUE;:value=FALSE;
    return value;
}
/*FUNCIÓN: element Pop(stack *s)
DESCRIPCIÓN: Extrae un elemento de la pila dada por el usuario.
RECIBE: int *s (Referencia a la pila <<stack>> "s" a operar).
DEVUELVE: El último elemento que se ingresó a la pila.
OBSERVACIONES: El usuario ha creado e inicializado previamente la pila. Se valida si la pila no está
vacía (causa error en caso de estarlo), no se valida si free pudo liberar la memoria.
*/
element Pop(stack *s)
{
    if(Empty(s)==TRUE)
      printf("\nERROR Pop(stack *s): LA PILA SE ENCUENTRA VACIA");
      exit(1);
    element aux_element; //Se crea un nuevo elemento auxiliar
    node *aux_node;
    aux_element=s->top->e;
    aux_node=s->top; //Se obtiene la dirección del tope actual de la pila para poder eliminarlo después
    s->top=s->top->below; //Se reescribe el tope de la pila
    free(aux_node);
    return aux_element;
}
/*FUNCIÓN: element Top(stack *s)
DESCRIPCIÓN: Muestra el elemento que se encuentra en el tope de la pila.
RECIBE: int *s (Referencia a la pila <<stack>> "s" a operar).
DEVUELVE: El último elemento que se ingresó a la pila.
OBSERVACIONES: El usuario ha creado e inicializado previamente la pila. Se valida si la pila no está
vacía, causa error si está vacía.
*/
element Top(stack *s)
{
    if(Empty(s)==TRUE)
      printf("\nERROR Top(stack *s): LA PILA SE ENCUENTRA VACIA");
      exit(1);
    return s->top->e;
}
/*FUNCIÓN: int Size(stack *s)
DESCRIPCIÓN: Obtiene el tamaño de la pila dada por el usuario.
RECIBE: int *s (Referencia a la pila <<stack>> "s" a operar).
DEVUELVE: Tamaño de la pila.
OBSERVACIONES: El usuario ha creado e inicializado previamente la pila. No es necesario validar
si la pila está vacía.
*/
int Size(stack *s)
{
    return s->size;
}
/*FUNCIÓN: void Destroy(stack *s)
DESCRIPCIÓN: Destruye la pila dada por el usuario
RECIBE: int *s (Referencia a la pila <<stack>> "s" a operar).
DEVUELVE: Nada.
OBSERVACIONES: El usuario ha creado e inicializado previamente la pila.
*/
void Destroy(stack *s)
{
    node *aux_node;
    if(s->top!=NULL)
    {
      //Entonces la pila contiene elementos
      while(s->top!=NULL)
      {
        aux_node=s->top->below;
        free(s->top);
        s->top=aux_node;
      }
    }
    return;
}
