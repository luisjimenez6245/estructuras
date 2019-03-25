/*
Autor: Edgardo Adrián Franco Martínez
Versión 1.0 (11 de Septiembre 2012)
Descripción: Programa que dibuja un bloque de "*" cuadrado de ANCHO * ALTO en la consola

El programa imprime ALTO filas de *'s columna por columna hasta la columna ANCHO.

Observaciones: El programa requerira de la libreria "presentacion.h", la cuál tiene las implementaciones 
para mover el cursor de la pantalla, esperar un tiempo y borrar pantalla, la compilación debera incluir
las definiciones de las funciones según la plataforma que se este utilizando (Windows o Linux)

Compilación: 	gcc -o marco marco.c presentacion(Win|Lin).o) (Win si se correra en Windows | Lin si se ejecutará en Linux)  "Si se tiene el código objeto"
				gcc -o marco marco.c presentacion(Win|Lin).c) (Win si se correra en Windows | Lin si se ejecutará en Linux)  "Si se tiene el código fuente"
Ejecución: Windows marco.exe  &  Linux ./marco
*/
//LIBRERIAS
#include <stdio.h>
#include "presentacion.h"
#include <stdlib.h>
#include <windows.h>

//CONSTANTES
//Se piensa en un pantalla de 24 filas x 79 columnas
#define ANCHO 80

#define TIEMPO_BASE	3	//Tiempo base en milisegundos

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void dibujaCaja(int x, int y, int NumCaja){
	MoverCursor(x,y);
	printf("***");
	MoverCursor(x+2,y+1);
	printf("*\t Caja %d", NumCaja+1);
	MoverCursor(x,y+2);
	printf("***");
}

int Cajeras(int cant, int ancho){
	int i;
	printf("Cant: %d\n",cant );
	// system("pause");
	for(i=0; i<cant; i++){
		dibujaCaja(ancho+1, i*4, i);
	}
	return i*4+4;
}

void avanceCliente(int numCliente, int cajaAsignada, int cantCajeras){
	for(int col=1; col<ANCHO; col++){
		Cajeras(cantCajeras, ANCHO);
		MoverCursor(col, 1+cajaAsignada*4);
		printf("#%d", numCliente);
		EsperarMiliSeg(TIEMPO_BASE);
		system("cls");
	}
}

//PROGRAMA PRINCIPAL
int main(void){
	int fila,columna, ALTO, cantCajeras;
	//Borrar la pantalla
	BorrarPantalla();
	printf("Introduce la cantidad de cajeras: ");
	scanf("%d", &cantCajeras);

	printf("Cantidad de cajeras: %d \n", cantCajeras);
	// system("pause");

	hidecursor();

	ALTO = Cajeras(cantCajeras, ANCHO);

	avanceCliente(30, 3, cantCajeras);
	
	// Recorrer cada columna
	// int numCliente=1;
	// for(columna=1;columna<ANCHO;columna++){
	// 	Cajeras(cantCajeras,ANCHO);
	// 	//Recorrer cada fila 
	// 	for(fila=0;fila<cantCajeras;fila++){
	// 		//Mover el cursor, dibujar un * y esperar TIEMPO_BASE milisegundos
	// 		MoverCursor(columna,1+fila*4);
	// 		printf("#%d", fila);
	// 		numCliente++;
	// 	};
	// 	EsperarMiliSeg(TIEMPO_BASE);
	// 	system("cls");

	// };
	return 0;
}
