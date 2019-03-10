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

char* appendString(char *cadena, char caracter)
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
	int count = 0,i, tam  = strlen(exp);
	for(i = 0; i < tam; ++i)
	{
		if(tipoValor(exp[i]) == 4)
		{
			boolean contenido =  TRUE;
			REVISA:
			if(variables[count] != exp[i] && contenido)
			{
				++count;
				if(count < strlen(variables))
					goto REVISA;
			}
			else
			{
				contenido = FALSE;
			}
			if(contenido ==  TRUE)
				variables = appendString(variables, exp[i]);
			count = 0;
		}
	}
	return variables;
}

int *obtenerValores(char variables[]){
	int * res;
	int numeroVariables = strlen(variables), i = 0;
	for(i = 0; i < numeroVariables; ++i)
	{
		printf("\nInserta el valor para la variable %c: ", variables[i]);
		scanf("%i", &res[i]);
	}
	return res;
}

void evaluacion(char expPost[], char variables[], int valores[])
{
	int tam_cad = strlen(expPost), i;
	stack pila;
	Initialize(&pila);
	for(i = 0; i < tam_cad; ++i)
	{
		if(tipoValor(expPost[i]) == 4)
		{}
		else
		{}
	}
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
	char * expInf;
	printf("**************\nBIENVENIDO\n**************");
	while (respuesta1 == 'S' || respuesta1 == 's')
	{
		printf("\nIngresa la expresion a convetir:\n");
		scanf("%[^\n]%*c", expInf);
		printf("\nComprobando...\n");
		int tam = strlen(expInf);
		if(tam <= 100){
		if (tam <= 100 && comprobarParentesis(expInf, tam))
		{
			printf("\nParentesís validos\n");
			char * post =  cambioPostFijo(expInf);
			char * variables =  extraerVariables(post);
			//printf("\n Var postfijo: %s", extraerVariables(post));
	
			//evaluacion(cambioPostFijo(expInf, tam), );
		}
		else
		{
			printf("\nParentesis no validos");
		}
		}
		printf("\nQuieres volver a introducir una expresion? [S/N]\n");
		scanf("%c", &respuesta1);
	}
	free(expInf);
	printf("Sale bye!\n");
	return EXIT_SUCCESS;
}
