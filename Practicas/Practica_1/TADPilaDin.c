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
#include "TADPilaDin.h"

/*
FUNCIÓN: void Initialize(pila *s);
DESCRIPCIÓN: Inicializar pila (Iniciar una pila para su uso).
RECIBE: int *s (Referencia a la pila "s" a operar).
DEVUELVE: Nada.
OBSERVACIONES: El usuario crea una pila s y deberá inicializarla para su uso haciendo referencia a ella,
en caso contrario se producirá un error.
*/
void initialize
