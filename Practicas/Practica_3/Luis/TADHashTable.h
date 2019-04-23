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


//Efecto: Recibe una palabra palabra y un entero con el tamaño de la tabla para aplicar el algoritmo hash.
//Excepcion: Si la la palabra enviado genera un código hash mayor al valor máximo de un entero.
int aplicarHash(char *palabra, int tamTabla);

//Efecto: Recibe una TablaHash tabla y la iniciliza para su trabajo
void InicializarTabla(tablaHash *tabla);

//Efecto: Recibe una TablaHash tabla y la vacía completamente.
void DestruirTabla(tablaHash *tabla);

//Efecto: Recibe una TablaHash tabla y un elemento e para agregarla a la tabla.
void AgregarATabla(tablaHash *tabla, elemento e);

//Efecto: Recibe una TablaHash tabla y un elemento e para eliminarla de la tabla si se encuentra.
void EliminarDeTabla(tablaHash *tabla, elemento e);

//Efecto: Recibe una TablaHash tabla y un elemento e para agregarla a la tabla a elminar.
elemento BuscarEnTabla(tablaHash *tabla, elemento e);

//Efecto: Recibe un TablaHash tabla y un elemento e para ser reemplazado en la lista
void ModificarTabla(tablaHash *tabla, elemento e);

//Efecto: Recibe un TablaHash tabla para generar sus estadisticas.
void Estadisticas(tablaHash *tabla);

//Efecto:  Recibe un TablaHash tabla para exportar su contenido en un archivo.
//Excepcion: si el progrma no logra los permisos de escritura o si le direcotrio a guardar no existe.
void ExportarTabla(tablaHash *tabla)
