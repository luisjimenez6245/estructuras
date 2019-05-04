/*
	PRÁCTICA 05: N-REINAS MIS NIÑOS
	AUTORES: 
		JIMÉNEZ DELGADO LUIS DIEGO
		SÁNCHEZ CASTRO AARÓN GAMALIEL
		SÁNCHEZ TIRADO CITLALI YASMÍN
	VERSIÓN: 1.0
	DESCRIPCIÓN: NPI DE QUÉ HACE EL PROGRAMA

	SE PROPONE LA CREACIÓN DE UN ARREGLO DE TAMAÑO N (NÚMERO DE REINAS)
	DONDE LOS ÍNDICES DEL ARREGLO (0 A N-1) REPRESENTAN LAS COLUMNAS DEL TABLERO
	CONDICIONES:
		-SI DENTRO DEL ARREGLO UN NÚMERO SE REPITE, QUIERE DECIR QUE ESOS ELEMENTOS SE ENCUENTRAN EN LA MISMA FILA
		-SE DEBE COMPROBAR 
*/
//LIBRERÍAS A UTILIZAR
#include <stdio.h>
#include <stdlib.h>
#include "Gotoxy.h"
//CONSTANTES 
#define FALSE 0
#define TRUE 1

int i,j,tamTablero;

int validarPosicion(){
	int valido=FALSE;
	return valido;
}

void agregarReina(){
	return;
}

int main(){
	printf("--------------------\nBIENVENIDO\n--------------------\n");
	printf("Ingresa la cantidad de reinas a colocar (4<=numero<=10):\n>");
	scanf("%i",&tamTablero);
	//SE CREA UN TABLERO DE CARACTERES
	char tablero[tamTablero][tamTablero];
	return 0;
}