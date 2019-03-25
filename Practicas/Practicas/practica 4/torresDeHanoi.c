/*
AUTORES: Paola Raya Tolentino, 
		 Eduardo Gómez Rodriguez, 
		 Vladimir Azpeitia Hernández.
VERSION: 1.0
DESCRIPCIÓN: Con la implimentación del TAD Pila se implemento
un programa que valida y evalua una expresión infija. 
Que toma en consideración la procedencia de los operadores, 
realiza una evaluación de paréntesis escritos correctamente,
convierte la expresión a postfijo, mostrando el resultado
y finalmente realiza la evaluación de la expresión.
COMPILACIÓN: gcc -o torresDehanoi torresDehanoi.c 
*/
//Declaracion de librerias
#include <stdio.h>
#include <stdlib.h>

//Prototipos de funcion hanoi

void hanoi(int ndiscos, char origen, char auxiliar, char destino);

//Funcion main
int main(int argc, char const *argv[]){
	int ndiscos;
	char origen = 'A'; //Palo donde se comienza
	char auxiliar = 'B'; //Palo auxiliar
	char destino = 'C'; // Palo al que se quiere llegar

	//Presentacion
	printf("TORRES DE HANOI\n");
	printf("------------------------------------------------\n");
	printf("Ingresa el numero de discos: "); //Pedimos al usuario que ingrese la cantidad de discos
	scanf("%d", &ndiscos);
	fflush(stdin); //Limpiamos el buffer de entrada de texto

	printf("Los movimientos que se hicieron son: \n");
	hanoi(ndiscos, origen, auxiliar, destino);
	return 0;
}

//Implementacion funcion hanoi
void hanoi(int ndiscos, char origen, char auxiliar, char destino){
	printf("hanoi(%d, %c, %c, %c)\n", ndiscos, origen, auxiliar, destino);
	if(ndiscos == 1){ //Caso base
		printf("%c->%c ", origen, destino);
	}else{ //Caso recursivo
		hanoi(ndiscos-1, origen, destino, auxiliar);
		printf("\n%c->%c\n", origen, destino);
		hanoi(ndiscos-1,auxiliar, origen, destino);
	}
	return;
}
