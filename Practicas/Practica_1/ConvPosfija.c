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
FUNCIÓN: int tipoValor(char caracter)
DESCRIPCIÓN: Evalula un cracter para ver que tipo de dato es.
RECIBE: char caracter (Caractér a evauluar).
DEVUELVE: int.
OBSERVACIONES: Regresa 4 en caso de que el caracter sea una letra, regresa la 1 si el signo es + o -,regresa la 1 si el signo es + o -, 
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
/*
char *appendString(char *cadena, char caracter)DESCRIPCIÓN: Agrega el elemento indicado a la pila (stack) "s".
RECIBE: int *s (Referencia a la pila <<stack>> "s" a operar), element e (Elemento a introducir en la pila).
DEVUELVE: char * La expresión con el caracter nuevo agregado.
OBSERVACIONES: 
*/
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

/*
boolean comprobarParentesis(char expInf[], int tam_cad)
DESCRIPCIÓN: Verifica si los parentetsis de una expresión estan correctos .
RECIBE: char expInf[](Expresión de ), int tam_cad
DEVUELVE: boolean con el valor de verificación de la operación.
OBSERVACIONES: No se toma encuenta si están correctamente cerrados o no.
*/
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
/*
FUNCIÓN: char *extraerVariables(char exp[])
DESCRIPCIÓN: Extrae las variables de una expresión dada;
RECIBE: char exp[](Expresión de donde se van a extraer).
DEVUELVE: char * Expresión con las varibles de la expresión exp;
OBSERVACIONES: Las varibles son Únicas de la variable;
*/
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

/*
FUNCIÓN: int obtenerValorVariable(char variables[], char buscar)
DESCRIPCIÓN: Obtiene la posición de la la variable a buscar del arreglo variables;
RECIBE: char variables[](Expresión que contiene las variables), char buscar(Caracter a buscar en la cadena).
DEVUELVE: int con la posicion en el arreglo de las variables.
OBSERVACIONES: La expresión variables[] debe de ser obtenida de las funcion char *extraerVariables(char exp[]);
*/

int obtenerValorVariable(char variables[], char buscar)
{
	int i = 0, tam = strlen(variables);
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
/*
FUNCIÓN: void evaluacion(char expPost[], char variables[])
DESCRIPCIÓN: realiza la evaluación de la postfija con valores que se le asignen a las variables de la expresión. 
RECIBE: char expPost[](Expresión postfija), char variables[] (Expresión que contiene las variables).
DEVUELVE: Nada.
OBSERVACIONES: La expresión variables[] debe de ser obtenida de las funcion char *extraerVariables(char exp[]);
*/
void evaluacion(char expPost[], char variables[])
{
	int tam_cad = strlen(expPost), i, numeroVariables = strlen(variables);
	int valores[numeroVariables];
	stack pila;
	Initialize(&pila);
	element e;
	for (i = 0; i < numeroVariables; i++)
	{
		printf("\nInserta el valor para la variable %c \n", variables[i]);
		scanf("%i", &valores[i]);
	}
	double aux1, aux2;
	for (i = 0; i < tam_cad; ++i)
	{
		if (tipoValor(expPost[i]) != 4)
		{
			e = Pop(&pila);
			aux1 = e.n;
			e = Pop(&pila);
			aux2 = e.n;
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
			e.n = valores[obtenerValorVariable(variables, e.c)];
		}
		Push(&pila, e);
	}
	printf("\nResultado: %f", Pop(&pila).n);
}

/*
FUNCIÓN: char *cambioPostFijo(char expInf[])
DESCRIPCIÓN: Realiza el cambio de una expresión dada a una postfija.
RECIBE: char expInf[](Expresión infija a cambiar);
DEVUELVE: char * La cadena de caracteres de la conversion postfija 
OBSERVACIONES: 
*/
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
	while (respuesta1 == 's' || respuesta1 == 'S')
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
				evaluacion(post, variables);
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
