#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "presentacion.h"
#include "TADColaDin.h"

#define tiempoEspera 500

int main(){
	elemento procesoAux;
	unsigned int tiempo=0;

	cola esperandoEjecucion;
	cola Finalizados;

	Initialize(&esperandoEjecucion);
	Initialize(&Finalizados);

	//Aqui encolamos los procesos (en este caso seran 10 por defecto)
	for(int i=0; i<10; i++)
		Queue(&esperandoEjecucion, nuevoProceso(i+1, i*4+1));

	while(!Empty(&esperandoEjecucion)){
		procesoAux = Dequeue(&esperandoEjecucion);
		procesoAux.processTime--;

		if(procesoAux.processTime == 0){
			procesoAux.processTimeReal = tiempo + 1;
			Queue(&Finalizados, procesoAux);
		}
		else{
			Queue(&esperandoEjecucion, procesoAux);
		}

		system("cls");
		
		imprimirEspera(&esperandoEjecucion);
		imprimirFinalizados(&Finalizados);

		Sleep(tiempoEspera);
		tiempo++;
	}
	MoverCursor(0,130);
	printf("Ia akave we xdd\n");

}