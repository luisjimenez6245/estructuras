/*
	AUTORES (C) Febrero 2019: 
		Jiménez Delgado Luis Diego
		Sánchez Castro Aarón Gamaliel
		Sánchez Tirado Citlali Yasmín
	VERSIÓN: 1.0
	DESCRIPCIÓN: 
	CON LA IMPLEMENTACIÓN DE LA COLA DINAMICA SE PUEDE SIMULAR EL PROCESO DE UN MONO PROCESADOR SIN PRIORIDADES 
*/
//Librerías a ocupar
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADColaDin.h"

elemento getProceso();
int ejecutaProceso(cola *listos, cola *finalizados);
void creaResumen(cola *finalizados, int tiempo);
void imprimeElemento(elemento e);

int main()
{
    char res = 's';
    cola listos, finalizados;
    int tiempo;
    initscr();
    Initialize(&listos);
    Initialize(&finalizados);
    //incializa las pila
PROCESO:
    while (res == 's' || res == 'S')
    {
        //Ejecuta el proceso de solcitar los procesos al ususario.
        Queue(&listos, getProceso());
        printw("\nDeseas ingresar más procesos?:\n");
        scanw("%s", &res);
        clear();
    }
    tiempo = ejecutaProceso(&listos, &finalizados);
    creaResumen(&finalizados, tiempo);
    printw("\nQuieres repetir el programa?:\n");
    scanw("%s", &res);
    //Verifica si el ususario quiere volver a ejecutar el programa.
    if (res == 's' || res == 'S')
        goto PROCESO;
    Destroy(&finalizados);
    Destroy(&listos);
    endwin();
    return EXIT_SUCCESS;
}

/*
FUNCIÓN: elemento getProceso()
DESCRIPCIÓN: Hace el proceso de solicitar datos al usuario acerca de los procesos
RECIBE: void.
DEVUELVE: elemento e que es el elemento con los datos solicitados al usuario.
OBSERVACIONES: El tiempo es validado para evitar errores con el tiempo
*/
int ejecutaProceso(cola *listos, cola *finalizados)
{
    int tiempo = 1;
    elemento aux, anterior;
    printw("\n-------------------------------- INICIO  ---------------------------------\n");
    clear();
    while (!Empty(listos))
    {
        //Cominenza el proceso de ejecución de procesador
        aux = Dequeue(listos);
        --aux.time;

        move(0, 0);
        printw("Proceso Anterior:\n");
        if (tiempo > 1)
        {
            imprimeElemento(anterior);
        }
        else
        {
            printw("NO HAY PROCESO ANTERIOR");
        }
        move(10, 0);
        printw("Proceso Posterior:\n");
        if (!Empty(listos))
        {
            imprimeElemento(Final(listos));
        }
        else
        {
            printw("FIN DE PROCESOS");
        }

        //Imprime el proceso actual
        move(5, 40);
        printw("Proceso actual:");
        move(6, 40);
        printw("Nombre: %s", aux.processName);
        move(7, 40);
        printw("ID: %s", aux.id);
        move(8, 40);
        printw("Actividad: %s", aux.activity);
        move(9, 40);
        printw("Tiempo: %i", aux.time);
        anterior = aux;
        getch();
        clear();
        ++tiempo;
    }
    printw("\n--------------------------------   FIN   ---------------------------------\n");
    getch();
    clear();
    return tiempo;
}

/*
FUNCIÓN: void creaResumen(cola *finalizados, int tiempo)
DESCRIPCIÓN: Hace el proceso de solicitar datos al usuario acerca de los procesos
RECIBE: cola *finalizados, int tiempo.
DEVUELVE: elemento e que es el elemento con los datos solicitados al usuario.
OBSERVACIONES: El tiempo es validado para evitar errores con el tiempo
*/
void creaResumen(cola *finalizados, int tiempo)
{
    elemento aux;
    printw("\n---------------------------------- RESUMEN -----------------------------------\n");
    while (!Empty(finalizados))
    {
        aux = Dequeue(finalizados);
        printw("ID: %s PROCESO: %s TIEMPO: %i \n", aux.id, aux.processName, aux.time);
    }
    printw("\nTiempo total: %i", tiempo);
    getch();
    clear();
}

/*
FUNCIÓN: void imprimeElemento()
DESCRIPCIÓN: Hace el proceso de solicitar datos al usuario acerca de los procesos
RECIBE: elemento e.
DEVUELVE: void.
OBSERVACIONES: El tiempo es validado para evitar errores con el tiempo
*/
void imprimeElemento(elemento e)
{
    printw("PROCESO: %s\n", e.processName);
    printw("TIEMPO RESTANTE: %i\n", e.time);
    return;
}

/*
FUNCIÓN: elemento getProceso()
DESCRIPCIÓN: Hace el proceso de solicitar datos al usuario acerca de los procesos
RECIBE: void.
DEVUELVE: elemento e que es el elemento con los datos solicitados al usuario.
OBSERVACIONES: El tiempo es validado para evitar errores con el tiempo
*/
elemento getProceso()
{
    elemento e;
    printw("Nuevo Proceso\n");
    printw("Ingresa nombre del proceso:\n");
    scanw("%[^\n]%*c", e.processName);
    printw("Ingresa actividad del proceso:\n");
    scanw("%[^\n]%*c", e.activity);
    printw("Ingresa id del proceso:\n");
    scanw("%s", e.id);
TIEMPO:
    printw("Ingresa tiempo del proceso:\n");
    scanw("%i", &e.time);
    if (e.time < 1)
    {
        printw("No se permiten Tiempos negativos\n");
        goto TIEMPO;
    }
    fflush(stdin);
    return e;
}