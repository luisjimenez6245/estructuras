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

int esSigno(char caracter)
{
	int res = 0;
	if (caracter == '+' || caracter == '-')
	{
		res = 1;
	}
	else
	{
		if (caracter == '*' || caracter == '/')
		{
			res = 2;
		}
		else
		{
			if (caracter == '^')
				res = 3;
		}
	}

	return res;
}

boolean comprobarParentesis(char expInf[], int tam_cad)
{
	stack parentesis;
	element e;
	Initialize(&parentesis);
	boolean res = TRUE;
	int i = 0;
	for (i = 0; tam_cad > i; i++)
	{
		if (expInf[i] == '(')
		{
			e.c = expInf[i];
			Push(&parentesis, e);
		}
		else if (expInf[i] == ')')
		{
			if (Empty(&parentesis) == FALSE)
			{
				Pop(&parentesis);
			}
			else
			{
				res = FALSE;
				break;
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
	int nivel = 0;

	Destroy(&parentesis);
	Destroy(&caracteres);
	Destroy(&signos);
	return res;
}

char *cambioPostFijo(char expInf[], int tam_cad)
{
	char *res;
	stack pila;
	Initialize(&pila);
	element e;
	int i = 0;
	int nivel = 0;
	for (i = 0; i <= tam_cad; ++i)
	{
		e.c = expInf[i];
		int aux = esSigno(expInf[i]);
		if (aux > 0)
		{
			if (nivel < aux)
			{
				Push(&pila, e);
			}
			else
			{
				res = res + Pop(&pila).c;
			}
		}
		else
		{
			if (aux == '(')
			{
				nivel = 0;
				Push(&pila, e);
			}
			else
			{
				if (aux == ')')
				{
					int j;
					for (j = 0; j < Size(&pila); ++j)
					{
						if (Top(&pila).c != '(' && !Empty(&pila))
							res = res + Pop(&pila).c;
						else
							break;
					}
				}
				else
				{
					res = res + expInf[i];
				}
			}
		}
	}
	if (!Empty(&pila))
		for (i = 0; i < Size(&pila); ++i)
			res += Pop(&pila).c;
	Destroy(&pila);
	return res;
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
		if (comprobarParentesis(expInf, tam))
		{
			printf("\nParentesís validos\n");
			printf("%s", cambioPostFijo(expInf, tam));
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
