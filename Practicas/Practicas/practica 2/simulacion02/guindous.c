#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "presentacion.h"
#include "TADColaDin.h"

#define tiempoEspera 500

void hidecursor(void){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

elemento nuevoProceso(int id){
	elemento procesoAux;
	char *temp, num[4];
	int tam;

	fflush(stdin);
	printf("-----------Proceso %d ---------\n", id);

	temp = procesoAux.processName;
	tam = 45;
	printf("Introduce el nombre del proceso %d: ", id);
	getline(&temp, &tam, stdin);
	fflush(stdin);

	temp = procesoAux.processActivity;
	tam = 200;
	printf("Introduce la descripcion del proceso: ");
	getline(&temp, &tam, stdin);
	fflush(stdin);

	itoa(id, num, 10);
	strcpy(procesoAux.processID, num);
	printf("Introduce el tiempo que necesita el proceso: ");
	scanf("%d", &procesoAux.processTime);

	printf("\n");

	return procesoAux;
}

void enEjecucion(elemento Ejec){
	MoverCursor(0,0);
	printf("Ejecutando el siguiente proceso:\n");
	MoverCursor(0,1);
	for(int i=0; i<90; i++)
		printf("-");
	MoverCursor(0, 2);
	printf("Nombre del Proceso");
	MoverCursor(30,2);
	printf("Actividad");
	MoverCursor(70,2);
	printf("ID");
	MoverCursor(80,2);
	printf("Tiempo");

	MoverCursor(0,3);
	for(int i=0; i<90; i++)
		printf("-");

	MoverCursor(0,4);
	printf("| %s", Ejec.processName);
	MoverCursor(30, 4);
	printf("| %s", Ejec.processActivity);
	MoverCursor(70, 4);
	printf("| %s", Ejec.processID);
	MoverCursor(80, 4);
	printf("| %d  |", Ejec.processTime);
	
	MoverCursor(0,5);
	for(int i=0; i<90; i++)
		printf("-");
}

void imprimirEspera(cola *esperandoEjecucion){
	elemento procesoAux;
	int a,b,c,d,l;
	a = 0;
	b = 30;
	c = 70;
	d = 80;
	l = 9;

	MoverCursor(0,l-2);
	for(int i=0; i<92; i++)
		printf("-");

	MoverCursor(a,l);
	printf("Procesos esperando a la Ejecucion:\n");
	MoverCursor(a, l+2);
	printf("Nombre del Proceso");
	MoverCursor(b,l+2);
	printf("Actividad");
	MoverCursor(c,l+2);
	printf("ID");
	MoverCursor(d,l+2);
	printf("Tiempo");

	for(int i=0, k=0; i<Size(esperandoEjecucion); i++, k++){
		procesoAux = Element(esperandoEjecucion, i+1); 

		if(i==0)
			enEjecucion(procesoAux);
		else{
			MoverCursor(a, k*2+2+l);
			printf("%s", procesoAux.processName);
			MoverCursor(b, k*2+2+l);
			for(int j=0; j<strlen(procesoAux.processActivity); j++){
				if(j%40 != 39){
					printf("%c", procesoAux.processActivity[j]);
				}
				else{
					printf("-\n");
					k++;
					MoverCursor(b, k+2+l);
				}
			}
			MoverCursor(c, k*2+2+l);
			printf("%s", procesoAux.processID);
			MoverCursor(d, k*2+2+l);
			printf("%d", procesoAux.processTime);
		}
	}
}

void imprimirFinalizados(cola *Finalizados){
	elemento procesoAux;
	int a = 100;
	int b = 130;
	int c = 150;

	for(int k=0; k<30; k++){
		MoverCursor(a-8, k);
		printf("|");
	}

	MoverCursor(a,0);
	printf("Procesos Finalizados:");
	MoverCursor(b,0);
	printf("ID");
	MoverCursor(c,0);
	printf("Tiempo total");

	for(int i=0; i<Size(Finalizados); i++){
		procesoAux = Element(Finalizados, i+1); 
		MoverCursor(a, i*2+2);
		printf("%s", procesoAux.processName);
		MoverCursor(b, i*2+2);
		printf("%s", procesoAux.processID);
		MoverCursor(c, i*2+2);
		printf("%d", procesoAux.processTimeReal);
	}
}

int main(){
	elemento procesoAux;
	unsigned int tiempo=0, cantProcesos;

	hidecursor();

	cola esperandoEjecucion;
	// cola Ejecutando; //?? Dudo de que sea correcto poner una cola para ejecutados, puede ser constante
	cola Finalizados;

	Initialize(&esperandoEjecucion);
	Initialize(&Finalizados);

	//Aqui encolamos los procesos (en este caso seran 10 por defecto)
	printf("Ingresa cuantos procesos quieres ejecutar xd: ");
	scanf("%d", &cantProcesos);

	for(int i=0; i<cantProcesos; i++)
		Queue(&esperandoEjecucion, nuevoProceso(i+1));

	system("cls");

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

	MoverCursor(0,30);
	printf("Ia akave we xdd\n");


	return 0;

}