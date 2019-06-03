#include <stdio.h>
#include <stdlib.h>
#include "TADListaDL.h"

/*
PRUEBA DEL TADLISTADL
AUTOR: Luis Diego Jiménez Delgado (Abril 2019)
VERSION: 1.0

OBSERVACIONES: Este archivo solo incluye las estructuras, tipos de datos y
declaracion de las operaciones del TAD  Lista.

EL CODIGO QUE IMPLEMENTA LAS FUNCIONES ES EL ARCHIVO: TADListaDL.c
*/
void ImprimeLista(lista *l);
/*
	FUNCIÓN: main
	RECIBE: void
	DEVUELVE:  EXIT_CODE
	DESCRIPCIÓN: Realiza una lista que conteine el abecedario, elimina elementos, los busca y los vuelve a insertar
*/
int main()
{
    lista list;
    posicion pos;
    elemento e, aux;
    int i = 0, auxi = 0;
    char initial = 'z';
    Initialize(&list);
INIT:
    e.letterL = initial;
    --initial;
    e.letterC = 'A' + i;
    Add(&list, e);
    if (i < 25)
    {
        ++i;
        goto INIT;
    }

    printf("\nLista inicial");
    ImprimeLista(&list);
    i = 0;
SEARCH:
    pos = Search(&list, e);
    if (ValidatePosition(&list, pos))
    {
        e = Position(&list, pos);
        aux = e;
        --e.letterC;
        ++e.letterL;
        aux.letterL = 'z' - i;
        Replace(&list, pos, aux);
    }
    if (i < 25)
    {
        ++i;
        goto SEARCH;
    }

    printf("\nLista acomodada");
    ImprimeLista(&list);
    i = 0;
RANDOMDELETE:
    auxi = (rand() % 25);
    printf("%d", i);
    e.letterC = 'Z' - auxi;
    e.letterL = 'z' - auxi;
    pos = Search(&list, e);
    if (ValidatePosition(&list, pos))
    {
        Remove(&list, pos);
    }
    if (i < 5)
    {
        ++i;
        goto RANDOMDELETE;
    }
    printf("\nLista con elementos borrados");
    ImprimeLista(&list);
    i = 0;
RECONSTRUCT:
     e.letterC = 'A' +i;
    e.letterL = 'a' +i;
    pos = Search(&list, e);
    if (ValidatePosition(&list, pos) != TRUE)
    {
            printf("\nS: %c\t%c", e.letterC, e.letterL);
        --e.letterC;
        --e.letterL;
        printf("\nI: %c\t%c", e.letterC, e.letterL);
        pos = Search(&list, e);
        if (ValidatePosition(&list, pos)){
            printf("\nasdsadsadasd");
            Insert(&list, pos, e, TRUE);
        }
        else{
            printf("\nrrrrrrrrrrrrrrrrr");
        }
    }
    if (i < 25)
    {
        ++i;
        goto RECONSTRUCT;
    }
    printf("\nLista con elementos recuperados");
    ImprimeLista(&list);
    pos = First(&list);
    Destroy(&list);
}

/*
	FUNCIÓN: ImprimeLista
	RECIBE: lista *l
	DEVUELVE: void.
	DESCRIPCIÓN: Recibe una lista l e impirme los valores qujes tiene la lista
*/
void ImprimeLista(lista *l)
{
    posicion p;
    elemento e;
    int i;

    p = First(l);

    for (i = 0; ValidatePosition(l, p); ++i)
    {
        e = Position(l, p);
        printf("\nElemento %d\t%c \t%c", i, e.letterC, e.letterL);
        p = Following(l, p);
    }
    return;
}
