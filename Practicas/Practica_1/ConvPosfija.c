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

int tipoValor(char caracter)
{
	if ((caracter > 64 && caracter < 91) || (caracter > 96 && caracter < 123))
		return 4;
	else
	{
		if (caracter == '+' || caracter == '-')
			return 1;
		if (caracter == '*' || caracter == '/')
			return 2;
		if (caracter == '^')
			return 3;
		if (caracter == '(')
			return -1;
		if (caracter == ')')
			return -2;
	}
	printf("\n");
	exit(EXIT_FAILURE);
	return 0;
}

boolean comprobarParentesis(char expInf[], int tam_cad)
{
	stack parentesis;
	element e;
	Initialize(&parentesis);
	boolean res = TRUE;
	int i = 0, total = 0, inverso = 0;
	for (i = 0; tam_cad > i; i++)
	{
		if (expInf[i] == '(')
		{
			e.c = expInf[i];
			++total;
			Push(&parentesis, e);
		}
		else if (expInf[i] == ')')
		{
			++inverso;
			if (Empty(&parentesis) == FALSE && inverso <= total)
			{
				Pop(&parentesis);
			}
			else
			{
				res = FALSE;
			}
		}
	}
	if (res != FALSE)
	{
		res = Empty(&parentesis);
	}
	Destroy(&parentesis);
	return res;
}

boolean comprobarSignos(char expInf[], int tam_cad)
{
	boolean res = TRUE;
	stack parentesis, caracteres, signos;
	Initialize(&parentesis);
	Initialize(&caracteres);
	Initialize(&signos);
	int nivel = 0, i = 0;
	for (i = 0; i <= tam_cad; ++i)
	{
		int aux = tipoValor(expInf[i]);
	}

	Destroy(&parentesis);
	Destroy(&caracteres);
	Destroy(&signos);
	return res;
}

void impresora(stack *pila)
{
	while (!Empty(pila))
	{
		printf("%c", Pop(pila).c);
	}
}

void cambioPostFijo(char expInf[], int tam_cad)
{
	stack pila;
	Initialize(&pila);
	element e;
	int i, nivel = 0, aux;
	for (i = 0; i < tam_cad; ++i)
	{
		e.c = expInf[i];
		aux = tipoValor(e.c);
		if (aux <= 4)
		{
			if (aux == 4)
				printf("%c", e.c);
			else
			{
				nivel = 0;
				if (aux == -2)
				{
					CERRAR:
					if(Top(&pila).c != '(')
					{
						printf("%c",Pop(&pila).c);
						goto CERRAR;
					}
					Pop(&pila);
					if(!Empty(&pila))
					{
						nivel = tipoValor(Top(&pila).c);
					}
				}
				else
					Push(&pila, e);
			}
		}
		else
		{
		SIGNO:
			if (aux <= nivel)
				if (!Empty(&pila))
				{
					printf("%c", Pop(&pila).c);
					if (!Empty(&pila))
						nivel = tipoValor(Top(&pila).c);
					goto SIGNO;
				}
			Push(&pila, e);
			nivel = aux;
		}
	}
	while (!Empty(&pila))
		printf("%c", Pop(&pila).c);

	Destroy(&pila);
}

int main()
{
	char respuesta1 = 's';
	char *expInf;
	printf("**************\nBIENVENIDO\n**************");
	while (respuesta1 == 'S' || respuesta1 == 's')
	{
		printf("\nIngresa la expresion a convetir:\n");
		scanf("%[^\n]%*c", expInf);
		printf("\nComprobando...\n");
		int tam = strlen(expInf);
		if (comprobarParentesis(expInf, tam))
		{
			printf("\nParentesís validos\n");
			cambioPostFijo(expInf, tam);
		}
		else
		{
			printf("\nParentesis no validos");
		}
		printf("\nQuieres volver a introducir una expresion? [S/N]\n");
		scanf("%c", &respuesta1);
	}
	printf("Sale bye!\n");
	return EXIT_SUCCESS;
}
