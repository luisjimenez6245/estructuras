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
#define TABLE_SIZE 299

typedef struct tablaHash {
    lista listas [TABLE_SIZE];
    int tamTabla;
} tablaHash;

typedef elemento registro;

int aplicarHash(char *palabra, int tamTabla);
void InicializarTabla(tablaHash *tabla);
void DestruirTabla(tablaHash *tabla);
void AgregarATabla(tablaHash *tabla, elemento e);
void EliminarDeTabla(tablaHash *tabla, elemento e);
elemento BuscarEnTabla(tablaHash *tabla, elemento e);
void ModificarTabla(tablaHash *tabla, elemento e);
void Estadisticas(tablaHash *tabla);
