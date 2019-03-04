/*
	AUTORES (C) Febrero 2019: 
		Jiménez Delgado Luis Diego
		Sánchez Castro Aarón Gamaliel
		Sánchez Tirado Citlali Yasmín
	VERSIÓN: 1.0
	DESCRIPCIÓN: 
	Con la implementación de la librería TAD Pila (Dinámica) se desarrolla un programa que permite convetir 
	una expresión infija a una expresión posfija. Se toma en cuenta la presedencia de los operadores matemáticos
	Además, permite evaluar dicha expresión otorgando valores a las literales dadas y muestra el resultado final.	
*/
//Librerías a ocupar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADPilaDin.h"

/*
	comprobarParentesis()
*/
boolean comprobarParentesis(char expInf[], int tam_cad)
{
	stack parentesis;
	element e;
	Initialize(&parentesis);
	int i = 0;
	for (i = 0; tam_cad > i; i++)
	{
		printf("\n%c",expInf[i]);
		if (expInf[i] == '(')
		{
			e.c = expInf[i];
			Push(&parentesis, e);
		}
		else if (expInf[i] == ')')
		{
			printf("Hola");
			if (Empty(&parentesis) == FALSE)
			{
				Pop(&parentesis);
			}
			else
			{
				printf("ERROR\n");
				exit(1);
			}
		}
	}
	return Empty(&parentesis);
}

int main()
{
	char respuesta1 = 's', respuesta2 = 's';
	char *expInf;
	printf("**************\nBIENVENIDO\n**************");
	while (respuesta1 == 'S' || respuesta1 == 's')
	{
		printf("\nIngresa la expresion a convetir:\n");
		scanf("%[^\n]%*c", expInf);
		printf("\nComprobando...\n");
		int tam = strlen(expInf);
		comprobarParentesis(expInf, tam);
		printf("\nQuieres volver a introducir una expresion? [S/N]\n");
		scanf("%c", &respuesta1);
	}
	printf("Sale bye!\n");
	return 0;
}
