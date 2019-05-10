/*
    TRIBONACCI
*/
#include <stdio.h>
#include <stdlib.h>

/*
	FUNCIÓN: tribonacci (int x,int y, int z, int limit)
	RECIBE: int x (PRIMER NÚMERO A SUMAR), int y (SEGUNDO NÚMERO A SUMAR),
		int z (TERCER NÚMERO A SUMAR), int limit (POSICIÓN LÍMITE), int n 
		(POSICIÓN ACTUAL).
	DEVUELVE: SE LLAMA A SÍ MISMA SI ES NECESARIO.
	DESCRIPCIÓN: FUNCIÓN ENCARGADA DE CALCULAR LOS NÚMEROS DE LA SERIE DE TRIBONACCI.
	OBSERVACIONES: CUANDO EL NÚMERO ES MUY GRANDE IMPRIME NEGATIVOS.
*/
void tribonacci(int x, int y, int z, int limit, int n){
    if(x==0&&y==0&&z==1){
        printf("0, 0, 1, ");
    }
    if(n>=limit){
        return;
    }
    printf("%i, ",x+y+z);
    tribonacci(y,z,x+y+z,limit,n+1);
}

int main(){
    int n;
    printf("Ingresa el numero limite:\n>");
    scanf("%i",&n);
    tribonacci(0,0,1,n,1);
    return 0;
}