//gcc -o super super.c TADColaDin.o presentacionWin.o

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "TADColaDin.h"
#include "presentacion.h"

#define ancho 90
#define repaintTime	20
#define tiempoEspaciado 200
#define espacioClientes 5

void hidecursor(void){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void dibujaCaja(int x, int y, int NumCaja, char estado, int velocidad){
	MoverCursor(x,y);
	printf("***\t");
	if(estado == 'A'){
		MoverCursor(x+7, y);
		printf("                               ");
		MoverCursor(x+7, y);
		printf("Atendiendo");
	}
	else
		if(estado == 'F'){
			MoverCursor(x+7, y);
			printf("                               ");
			MoverCursor(x+7, y);
			printf("CAJA CERRADA\n");
		}
		else{
			MoverCursor(x+7, y);
			printf("                               ");
			MoverCursor(x+7, y);
			printf("Vacio");
		}
	MoverCursor(x+2,y+1);
	printf("*\t Caja %d", NumCaja+1);
	MoverCursor(x,y+2);
	printf("***\t");
	printf("Atendiendo 1 cliente/%d seg\n", velocidad);
}

int Cajeras(int cant, int largo, char estadoCajeras[], char marketName[], int llegadaClientes, int tiempoAtencion[], int cantClientesLlegados, int cantClientesAtendidos){
	int i;
	MoverCursor(0,0);
	printf("                                                                                                             ");
	MoverCursor(0,0);
	printf("%s \tRecibiendo 1 cliente/%d seg\tHan llegado %d clientes\t\t%d clientes han sido atendidos\t", marketName, llegadaClientes, cantClientesLlegados, cantClientesAtendidos);
	if(cantClientesAtendidos>100){
		printf("\t\tEL SUPERMERCADO CERRARA\n");
	}
	for(i=0; i<cant; i++){
		dibujaCaja(largo+1, i*4+1, i, estadoCajeras[i], tiempoAtencion[i]);
	}
	return i*4+5;
}

void pintar(int filaPintar, int Posicion, elemento Cliente, char acaboFila){
	char temp[4];
	itoa(Cliente.n,temp,10);
	int x = ancho - espacioClientes*Posicion - 3; 
	int y = filaPintar * 4 + 2; 
	if(acaboFila == 'S'){
		for(int i=0; i<x; i++){
			MoverCursor(i,y);
			printf(" ");
		}
	}
	else{
		MoverCursor(x,y);
		printf("     ");
		MoverCursor(x,y);
		fflush(stdout);
		printf("#%s", temp);
	}
	return;
}

void limpiar(int i){
	int y = i*4+2;
	for(int c=0; c<ancho; c++)
		MoverCursor(0,y);
		printf("#");
	return;
}


int main(void){
	unsigned int tiempo, cliente, atendidos, minClientes, fila,columna, alto, cantCajeras, filaElegida, llegadaClientes;
	elemento aux;
	char marketName[20], fin = 'N';

	printf("Introduce el nombre del supermercado: ");
	scanf("%s", &marketName);
	printf("Introduce la cantidad de cajeras (1-10): ");
	scanf("%d", &cantCajeras);

	if(cantCajeras>10 || cantCajeras < 1){
		printf("Cantidad de cajeras no valida\n");
		exit(0);
	}

	printf("Introduce la minima cantidad de clientes para cerrar el supermercado: ");
	scanf("%d", &minClientes);

	char estadoCajeras[cantCajeras];
	int tiempoAtencion[cantCajeras];
	cola filaCajera[cantCajeras];
	for(int i=0; i<cantCajeras; i++)
		Initialize(&filaCajera[i]);

	for(int i=0; i<cantCajeras; i++){
		printf("Tiempo de atencion de la caja #%d (multiplos de 10): ", i+1);
		scanf("%d", &tiempoAtencion[i]);
	}
	printf("Introduce la velocidad de llegada de Clientes: ");
	scanf("%d", &llegadaClientes);

	alto = Cajeras(cantCajeras, ancho, estadoCajeras, marketName, llegadaClientes, tiempoAtencion, cliente, atendidos);
	tiempo = 0; cliente = 0; atendidos = 0;

	system("cls");
	hidecursor();
	srand(time(NULL));

	while(fin == 'N'){
		tiempo++;
		fin = 'S';

		for(int i=0; i<cantCajeras; i++){
			if((!Empty(&filaCajera[i])) && estadoCajeras[i] != 'F'){
				if(tiempo % tiempoAtencion[i] == 0){
					aux = Dequeue(&filaCajera[i]);
					//Aqui deberia ir el mensaje de a quien antendio
					atendidos++;
				}
				estadoCajeras[i] = 'A';
			}
			else{
				//Aqui da el mensaje de que esta vacia la cola
				estadoCajeras[i] = 'Z';
				if(atendidos>minClientes)
					estadoCajeras[i] = 'F';
			}
			Cajeras(cantCajeras,ancho, estadoCajeras, marketName, llegadaClientes, tiempoAtencion, cliente, atendidos);
		}

		// Cajeras(cantCajeras,ancho, estadoCajeras, marketName, llegadaClientes, tiempoAtencion);
		for(int i=0; i<cantCajeras; i++){
			// printf("llega #%d tam: %d\n", i, Size(&filaCajera[i]));
			// waitRetrace();
			// limpiar(i);
			for(int k=0; k<=Size(&filaCajera[i]); k++){
				// printf(" %d",k);
				if(k == Size(&filaCajera[i])){
					pintar(i,k-1,aux, 'S');
				}
				else{
					aux = Element(&filaCajera[i],k+1);
					pintar(i, k, aux, 'N');
				}
			}
		}

		if((tiempo % llegadaClientes == 0) && atendidos<=minClientes){
			cliente++;
			aux.n = cliente;
			filaElegida = rand()%cantCajeras;
			Queue(&filaCajera[filaElegida], aux);
		}

		Sleep(repaintTime);
		// system("mode con lines=0 cols=0 >nul");
		for(int a=0; a<cantCajeras; a++){
			if(estadoCajeras[a] != 'F')
				fin = 'N';

			MoverCursor(0, alto+5);
			printf("%c\n", fin);
		}
	}

	MoverCursor(0,alto+1);

	return 0;
}
