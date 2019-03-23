/*
AUTOR: Edgardo Adrián Franco Martínez (C) Septiembre 2012
VERSIÓN: 1.3

DESCRIPCIÓN: Ejemplo de atención de dos cola de clientes, la simulación
de tiempo se reliza con la función Sleep(Solo funciona en Windows), cada X
tiempo llega un cliente y escoje pseudoaleatoriamente una cola y el tiempo 
de atención es Y.

OBSERVACIONES: Se puede emplear la libreria TADColaEst.h, TADPilaEstCir.h o TADColaDin.h implementadas
en clase. Ambas estructuras elemento, ya sea la de las implementaciónes estáticas o dinámica deberán 
tener un campo int n;

COMPILACIÓN: 	gcc -o Cajeras Cajeras.c TADCola/TADCola(Din|Est|EstCirc).o (Si se tiene el objeto de la implementación)
				gcc -o Cajeras Cajeras.c TADCola/TADCola(Din|Est|EstCirc).c (Si se tiene el fuente de la implementación)

EJECUCIÓN: Cajeras.exe (En Windows)
*/

//LIBRERAS
#include <stdio.h>
#include <windows.h>				//Funciona unicamente en Windows para usar la función Sleep()
//#include "TADCola/TADColaEst.h" 	//Si se usa la implemtentación dinámica (TADColaDin.c)
#include "TADColaDin.h" 	//Si se usa la implemtentación estática (TADColaEst.c|TADColaEstCirc.c)

//DEFINICION DE CONSTANTES
#define TIEMPO_BASE	200			//Tiempo base en ms

//Funcion para ver si un arreglo de TADCola tiene cada uno de sus elementos vacios
boolean arrColaEmpty(cola arrCola[], int numCajeras){
	int i, aux = 0;
	for (i = 0; i < numCajeras; i++){
		if (Empty(&arrCola[i]) == TRUE){
			aux++;
		}
	}
	if (aux == numCajeras){
		return TRUE;
	}
	return FALSE;
}
		


int main(void)
{
	unsigned int tiempo = 0;
	unsigned int cliente = 0;
	unsigned int TIEMPO_CLIENTE = 1;
	unsigned int TIEMPO_ATENCION = 3;
	int i,fila, numCliAten = 0, numCajeras = 2;
	elemento e;
	//Inicializar la función rand
	srand(time(NULL));
	
	//Crear dos colas
	cola cajera[numCajeras];
	
	//Inicializar ambas colas
	for(i = 0; i<numCajeras; i++){
		Initialize(&cajera[i]);
	}

	//Ciclo infinito
	
	do{
		Sleep(TIEMPO_BASE);		//Esperar el tiempo base
		tiempo++;				//Incrementar el contador de tiempo
		
		//Si el tiempo es multiplo del tiempo de atencion
		if (tiempo % TIEMPO_ATENCION == 0)
		{
			//Cajera 0
			if (!Empty(&cajera[0]))
			{
				e = Dequeue(&cajera[0]);
				printf("\n\n\nAtendi a: %d en caja 0", e.n);
			}
			else
			{
				printf("\n\n\nNo hay alguien por atender en caja 0");
			}
			//Cajera 1
			if (!Empty(&cajera[1]))
			{
				e = Dequeue(&cajera[1]);
				printf("\n\n\nAtendi a: %d en caja 1", e.n);
			}
			else
			{
				printf("\n\n\nNo hay alguien por atender en caja 1");
			}
		}
		//Si el tiempo es multiplo del de llegada de los clientes
		if (tiempo % TIEMPO_CLIENTE == 0)
		{
			cliente++;				//Incrementar el numero de clientes
			e.n = cliente;			//Dar el numero que identifica al cliente
			fila=rand()%2;			//Escoger la fila para formarse aleatoriamente					
			Queue(&cajera[fila], e);//Formarse en la fila seleccionada
			printf("\n\n\nLlego el cliente: %d a la cola de la caja %d", e.n,fila);
		}
		
		//Mostrar los clientes en cada cola
		printf("\n\n%d clientes en cola 0: [",Size(&cajera[0]));
		for (i=1;i<=Size(&cajera[0]);i++)
		{
			e=Element(&cajera[0],i);
			printf("%d\t", e.n);
		}
		printf("]");
		
		
		printf("\n\n%d clientes en cola 1: [",Size(&cajera[1]));
		for (i=1;i<=Size(&cajera[1]);i++)
		{
			e=Element(&cajera[1],i);
			printf("%d\t", e.n);
		}
		printf("]");
	}while (numCliAten < 100 && arrColaEmpty(cajera, numCajeras) == FALSE);

	return 0;
}

