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

int main()
{
    char res = 's';
    cola listos, finalizados;
    elemento aux, anterior;
    int tiempo = 1;
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
    printw("%i", Size(&listos));
    printw("\n-------------------------------- INICIO  ---------------------------------\n");
    clear();
    while (!Empty(&listos))
    {
        //Cominenza el proceso de ejecución de procesador  
        aux = Dequeue(&listos);
        --aux.time;
        if (aux.time == 0)
        {
            aux.time = tiempo;
            Queue(&finalizados, aux);
        }
        else
            Queue(&listos, aux);
        move(0, 0);
        printw("Proceso Anterior:\n");
        if (tiempo > 1)
        {
            printw("PROCESO: %s\n", anterior.processName);
            printw("TIEMPO RESTANTE: %i", anterior.time);
        }
        else
        {
            printw("NO HAY PROCESO ANTERIOR");
        }
        move(10, 0);
        printw("Proceso Posterior:\n");
        if (!Empty(&listos))
        {
            printw("PROCESO: %s\n", Final(&listos).processName);
            printw("TIEMPO RESTANTE: %i\n", Final(&listos).time);
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
    printw("\n---------------------------------- RESUMEN -----------------------------------\n");
    while (!Empty(&finalizados))
    {
        aux = Dequeue(&finalizados);
        printw("ID: %s PROCESO: %s TIEMPO: %i \n", aux.id, aux.processName, aux.time);
    }
    printw("\nTiempo total: %i", tiempo);
    getch();
    clear();
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