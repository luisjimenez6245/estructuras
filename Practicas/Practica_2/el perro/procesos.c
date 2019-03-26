#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADColaDin.h"

elemento getProceso();

int main()
{
    char res = 's';
    cola listos, finalizados;
    elemento aux, anterior;
    int tiempo = 0;
    initscr();
    Initialize(&listos);
    Initialize(&finalizados);
PROCESO:
    while (res == 's' || res == 'S')
    {
        Queue(&listos, getProceso());
        printw("\nDeseas ingresar más procesos?:\n");
        scanw("%s", &res);
        clear();
        refresh();
    }
    printw("\n-------------------------------- INICIO  ---------------------------------\n");
    while (!Empty(&listos))
    {
        aux = Dequeue(&listos);
        --aux.time;
        if (aux.time == 0)
            Queue(&finalizados, aux);
        else
            Queue(&listos, aux);
        tiempo = tiempo + aux.time;
        move(0, 0);
        printw("Proceso Anterior:");
        if (&anterior != NULL)
        {
        }
        else
        {
        }
        printw("Proceso Posterior:");
        if (!Empty(&listos))
        {
        }
        else
        {
        }

        move(0, 40);
        printw("Proceso actual:");
        printw("Nombre: %s", aux.processName);
        printw("ID: %s", aux.id);
        printw("Actividad: %s", aux.activity);
        printw("Tiempo: %i", aux.time);
        anterior = aux;
        clear();
        refresh();
    }
    printw("\n--------------------------------   FIN   ---------------------------------\n");
    printw("\n---------------------------------- RESUMEN -----------------------------------\n");
    while (!Empty(&finalizados))
    {
    }
    printw("\nTiempo total: %i", tiempo);
    printw("\nQuieres repetir el programa?:\n");
    scanw("%s", &res);
    if (res == 's' || res == 'S')
        goto PROCESO;
    Destroy(&finalizados);
    Destroy(&listos);
    endwin();
    return EXIT_SUCCESS;
}

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
    printw("Ingresa tiempo del proceso:\n");
    scanw("%i", &e.time);
    fflush(stdin);
    return e;
}