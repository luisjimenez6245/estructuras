#include <stdio.h>
#include <math.h>

double fibo(double lugDes, double lugAct, double valAnt, double valAntx2){
	double valAct = valAntx2+valAnt;

	if(lugDes == lugAct)
		return valAct;
	else
		return fibo(lugDes, lugAct+1, valAct, valAnt);
}

double tribo(double lugDes, double lugAct, double valAnt, double valAntx2, double valAntx3){
	double valAct = valAntx3+valAntx2+valAnt;

	if(lugDes == lugAct)
		return valAct;
	else
		return tribo(lugDes, lugAct+1, valAct, valAnt,valAntx2);
}

double main(){
	double n;
	char op;

	printf("K kierez we? T. Tribonacci\tF. Fibonacci\nR: ");
	scanf("%c", &op);

	printf("Introduce un numero limite de la serie deseada: ");
	scanf("%lf", &n);

	if(op == 'F' || op == 'f'){
		if(n == 1){
			printf("El resultado es: 0\n");
		}
		else{
			if(n == 2){
				printf("El resultado es: 1\n");
			}
			else
				printf("El resultado es: %.0lf\n", fibo(n, 3, 1, 0));
		}
	}
	else{
		if(op == 'T' || op == 't'){
			if(n == 1){
				printf("El resultado es: 0\n");
			}
			else{
				if(n == 3 || n == 2 ){
					printf("El resultado es: 1\n");
				}
				else
					printf("El resultado es: %.0lf\n", tribo(n, 4, 1, 1, 0));
			}
		}
		else
			printf("Opcion no reconocida\n");
	}
}

// 0	1	1	2	3	5	8	13	21