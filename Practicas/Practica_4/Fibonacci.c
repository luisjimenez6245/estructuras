#include <stdio.h>
#include <stdlib.h>

/*
	FUNCIÓN: fibonacci (int n,int m, int limit,int a)
	RECIBE: int n (PRIMER NÚMERO A SUMAR), int m (SEGUNDO NÚMERO A SUMAR),
		int limit (POSICIÓN LÍMITE), int a (POSICIÓN ACTUAL).
	DEVUELVE: SE LLAMA A SÍ MISMA SI ES NECESARIO.
	DESCRIPCIÓN: FUNCIÓN ENCARGADA DE CALCULAR LOS NÚMEROS DE LA SERIE DE FIBONACCI.
	OBSERVACIONES: CUANDO EL NÚMERO ES MUY GRANDE IMPRIME NEGATIVOS.
*/
void fibonacci(int n,int m, int limit, int a){
    if(n==0&&m==1){
        printf("0, 1, ");
    }
    if(a==limit){
        return;
    }
    printf("%i, ",m+n);
    fibonacci(m,m+n,limit,a+1);
}

int main(){
    int n;
    printf("Ingresa el numero limite:\n>");
    scanf("%i",&n);
    fibonacci(0,1,n,1);
    return 0;
}
