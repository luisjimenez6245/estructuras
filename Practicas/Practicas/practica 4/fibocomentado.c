/*
AUTORES: Paola Raya Tolentino, 
		 Eduardo Gómez Rodriguez, 
		 Vladimir Azpeitia Hernández.
VERSION: 1.0
DESCRIPCIÓN: implementación recursiva del termino n de la serie de Fibonacci y Tribonacci.
COMPILACIÓN: gcc -o fibo fibo.c 
*/		
#include <stdio.h>
#include <math.h>
/*
double fibo(double lugDes, double lugAct, double valAnt, double valAntx2)
Descripción: En esta función lo que se realiza es el calculo de la serie fibonacci
Recibe: double lugDes(lugar que el usuario ingreso), double lugAct(Número donde se empezaran a hacer los calculos), 
double valAnt(El valor del lugar anterior de lugAct), double valAntx2(El valor del lugar anterior a valAnt)
Devuelve: Double valAct o hace la recursividad(que es el valor de la serie fibonacci).
fibo(n, 3, 1, 0)
*/
double fibo(double lugDes, double lugAct, double valAnt, double valAntx2){
	double valAct = valAntx2+valAnt; //Se realiza la suma del lugar anterior y el anterior del anterior
	if(lugDes == lugAct) //Si el lugar deseado es igual al lugar actual
		return valAct; 	//Se va a regresar el valor valAct
	else				//Si no es igual el lugar actual al lugar deseado se realiza la recursividad.
		return fibo(lugDes, lugAct+1, valAct, valAnt); 
}
/*
double tribo(double lugDes, double lugAct, double valAnt, double valAntx2, double valAntx3)
Descripción: En esta función lo que se realiza es el calculo de la serie tribonacci
Recibe: double lugDes(lugar que el usuario ingreso), double lugAct(lugar donde se empezaran a hacer los calculos),
double valAnt(Valor del lugar anterior de lugAct), double valAntx2(El valor del lugar anteior a valtAnt), double valAntx3(El valor del lugar anterior
a valAntx2)
Devuelve: Double valAct o hace la recursividad(que es el valor de la serie tribonacci).
tribo(n, 4, 1, 1, 0)
*/
double tribo(double lugDes, double lugAct, double valAnt, double valAntx2, double valAntx3){
	double valAct = valAntx3+valAntx2+valAnt; // Se realiza la suma del lugar anterior, el anterior del anterior y el anterior del anterior o sea los 
	//3 ultimos numeros
	if(lugDes == lugAct) //si el lugar deseado es igual al lugar actual
		return valAct;	//Se va a retornar el valor valAct
	else				//si no se igual el lugar actual al lugar deseado se realiza la recursividad
		return tribo(lugDes, lugAct+1, valAct, valAnt,valAntx2);
}

int main(){
	double n; //Declaración de variable tipo double
	char op; //Declaración de variabñe tipo caracter

	printf("¿Que serie deseas calcular? T. Tribonacci\tF. Fibonacci\nR: "); //Se pregunta al usuario que serie desea calcular.
	scanf("%c", &op); //La opción elegida se guarda en la variable op ya declarada anteriormente.

	printf("Introduce un numero limite de la serie deseada: "); //Se pregunta al usuario hasta que número desea calcular la serie elegida
	scanf("%lf", &n); //El número ingresado por el usuario se guarda en la varible n, ya declarada anteriormente.

	if(op == 'F' || op == 'f'){ //si el usiario eligio 'f' o 'F' se entra a la serie de Fibonacci
		if(n == 1){				//Primer caso base de la serie Fibonacci
			printf("El resultado es: 0\n");
		}
		else{					//Segundo caso base de la serie Fibonacci
			if(n == 2){
				printf("El resultado es: 1\n");
			}
			else
				printf("El resultado es: %.0lf\n", fibo(n, 3, 1, 0)); //Se manda llamar a la función fibo y se imprime el resultado que regresa la función.
		}
	}
	else{
		if(op == 'T' || op == 't'){ //si el usiario eligio 't' o 'T' se entra a la serie de Tribonacci
			if(n == 1){				//Primer caso base de la serie Tribonacci
				printf("El resultado es: 0\n");
			}
			else{
				if(n == 3 || n == 2 ){ //Segundo y tercer caso de la serie Tribonacci
					printf("El resultado es: 1\n");
				}
				else
					printf("El resultado es: %.0lf\n", tribo(n, 4, 1, 1, 0)); //Se manda llamar a la función fibo y se imprime el resultado que regresa la función.
			}
		}
		else
			printf("Opcion no reconocida\n"); //El usuario ingreso una opción incorrecta
	}
}
