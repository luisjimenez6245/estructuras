/*
IMPLEMENTACIÓN DEL TAD PILA DINÁMICA (TADPilaDin.h)
AUTORES:
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
      return 1;
    aux_node->element=e;
    aux_node->below=s->top;
    s->top=aux_node;
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
