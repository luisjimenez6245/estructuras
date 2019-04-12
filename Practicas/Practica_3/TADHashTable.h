#include "TADListaDL.h"
/*
IMPLEMENTACIONES DEL TAD LISTA (TADLista.h)
AUTORES: 
    Luis Diego Jiménez Delgado (Abril 2019)
    Aarón Gamaliel Sanchez Castro (Abril 2019)
VERSION: 1.0

OBSERVACIONES: Este archivo solo incluye las estructuras, tipos de datos y
declaracion de las operaciones del TAD  Lista.

EL CODIGO QUE IMPLEMENTA LAS FUNCIONES ES EL ARCHIVO: TADListaDL.c
*/
#define LIST_SIZE 100

typedef struct tablaHash {
    lista listas [2000];
} tablaHash;

void InicializaTabla(tablaHash *tabla);
void DestruyeTabla(tablaHash *tabla);
void AgregaATabla(tablaHash *tabla, elemento e);
void EliminaDeTabla(tablaHash *tabla, elemento e);
void BuscaEnTabla(tablaHash *tabla, elemento e);
void ModificaTabla(tablaHash *tabla, elemento e);
void Estadisticas(tablaHash *tabla);
void ListarElementos(tablaHash *tabla);