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
#include <math.h>

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

char *appendString(char *cadena, char caracter)
{
	size_t tam = strlen(cadena);
	char *res = malloc(tam + 1 + 1);
	strcpy(res, cadena);
	res[tam] = caracter;
	res[tam + 1] = '\0';
	cadena = malloc(strlen(res));
	strcpy(cadena, res);
	free(res);
	return cadena;
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

char *extraerVariables(char exp[])
{
	char *variables = "";
	int count = 0, i, tam = strlen(exp);
	for (i = 0; i < tam; ++i)
	{
		if (tipoValor(exp[i]) == 4)
		{
			boolean contenido = TRUE;
		REVISA:
			if (variables[count] != exp[i] && contenido)
			{
				++count;
				if (count < strlen(variables))
					goto REVISA;
			}
			else
			{
				contenido = FALSE;
			}
			if (contenido == TRUE)
				variables = appendString(variables, exp[i]);
			count = 0;
		}
	}
	return variables;
}

int *obtenerValores(char variables[])
{
	int numeroVariables = strlen(variables), i, aux;
	int res[numeroVariables];
	for (i = 0; i < numeroVariables; i++)
	{
		printf("\nInserta el valor para la variable %c \n", variables[i]);
		scanf("%i", &res[i]);
	}
	return res;
}

int obtenerValorVariable(char variables[], char buscar, int tam)
{
	int i = 0;
VARIABLE:
	if (variables[i] != buscar)
	{
		i++;
		if (i < tam)
			goto VARIABLE;
		else
		{
			printf("\nNo se encontró un valor para la varaible");
			exit(EXIT_FAILURE);
		}
	}
	return i;
}

void evaluacion(char expPost[], char variables[], int valores[])
{
	int tam_cad = strlen(expPost), i, numeroVariables = strlen(variables);
	stack pila;
	Initialize(&pila);
	element e;
	double aux1, aux2;
	printf("valores: %i, %i\n", valores[0], valores[1]);
	for (i = 0; i < tam_cad; ++i)
	{
		if (tipoValor(expPost[i]) != 4)
		{
			if (Top(&pila).c != '?')
			{
				printf("\nval: %i", valores[obtenerValorVariable(variables, Top(&pila).c, numeroVariables)]);
				aux1 = valores[obtenerValorVariable(variables, Pop(&pila).c, numeroVariables)];
				printf("\naux1: %f", aux1);
			}
			else
				aux1 = Pop(&pila).n;
			if (Top(&pila).c != '?')
			{
				printf("\nval: %i", valores[obtenerValorVariable(variables, Top(&pila).c, numeroVariables)]);
				aux2 = valores[obtenerValorVariable(variables, Pop(&pila).c, numeroVariables)];
				printf("\naux2: %f", aux2);
			}
			else
				aux2 = Pop(&pila).n;
			printf("\n aux1:%f,auxx2:%f", aux1, aux2);
			switch (expPost[i])
			{
			case '^':
				e.n = pow(aux1, aux2);
				break;
			case '+':
				e.n = aux2 + aux1;
				break;
			case '-':
				e.n = aux2 - aux1;
				break;
			case '*':
				e.n = aux2 * aux1;
				break;
			case '/':
				e.n = aux2 / aux1;
				break;
			}
			e.c = '?';
		}
		else
		{
			e.c = expPost[i];
		}
		Push(&pila, e);
	}
	printf("\nResultado: %f", Pop(&pila).n);
}

char *cambioPostFijo(char expInf[])
{
	stack pila;
	Initialize(&pila);
	element e;
	char *res = "";
	int i, nivel = 0, aux, tam_cad = strlen(expInf);
	for (i = 0; i < tam_cad; ++i)
	{
		e.c = expInf[i];
		aux = tipoValor(e.c);
		if (aux == 4 || aux < 0)
		{
			if (aux == 4)
			{
				res = appendString(res, e.c);
			}
			else
			{
				nivel = 0;
				if (aux == -2)
				{
				CERRAR:
					if (Top(&pila).c != '(')
					{
						res = appendString(res, Pop(&pila).c);
						goto CERRAR;
					}
					Pop(&pila);
					if (!Empty(&pila))
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
			{
				if (!Empty(&pila))
				{
					res = appendString(res, Pop(&pila).c);
					if (!Empty(&pila))
						nivel = tipoValor(Top(&pila).c);
					goto SIGNO;
				}
			}
			Push(&pila, e);
			nivel = aux;
		}
	}
	while (!Empty(&pila))
		res = appendString(res, Pop(&pila).c);
	Destroy(&pila);
	printf("Expresión Postfija: %s", res);
	return res;
}

int main()
{
	char respuesta1 = 's';
	char *expInf;
	printf("**************\nBIENVENIDO\n**************");
	while (respuesta1 == 's')
	{
		printf("\nIngresa la expresion a convetir:\n");
		scanf("%s", expInf);
		printf("\nComprobando...\n");
		int tam = strlen(expInf);
		if (tam <= 100)
		{
			if (tam <= 100 && comprobarParentesis(expInf, tam))
			{
				printf("\nParentesís validos\n");
				char *post = cambioPostFijo(expInf);
				char *variables = extraerVariables(post);
				evaluacion(post, variables, obtenerValores(variables));
			}
			else
				printf("\nParentesis no validos");
		}
		else
		{
			printf("\nTamaño de expresión no valido.");
		}
		printf("\nQuieres volver a introducir una expresion? [S/N]:\n");
		scanf("%s", &respuesta1);
	}
	printf("Sale bye!\n");
	return EXIT_SUCCESS;
}
