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
//#include "TADPilaDin.h"

/*
	comprobarParentesis()
*/
int comprobarParentesis(char []expInf, int tam_cad)
{
	
}

int main()
{
	char respuesta1='s',respuesta2='s',expInf[100];
	printf("**************\nBIENVENIDO\n**************");
	while(respuesta1=='S'||respuesta1=='s')
	{
		printf("\nIngresa la expresion a convetir:\n");
		scanf("%s",&expInf);
		printf("\nComprobando...");
		/*
			Se asume que la expresión a evaluar tiene una longitud menor o igual a 100, no se comprueba longitud.
			Se comprueba que la expresión abre y cierra paréntesis correctamente.
		*/
		//if(comprobarParentesis(strupr(expInf))==1)
		//{
			//printf("OKAY\n");
		//}
		//else{
			//exit(1);
		//}
		printf("Quieres volver a introducir una expresion? [S/N]");
		scanf("%c",&respuesta1);
	}
	printf("Sale bye!");
	return 0;
}
