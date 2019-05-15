/*
    TRIBONACCI
      AUTORES: 
    JIMÉNEZ DELGADO LUIS DIEGO
    SÁNCHEZ CASTRO AARÓN GAMALIEL
    SÁNCHEZ TIRADO CITLALI YASMÍN
  VERSIÓN 1.5
*/
#include <stdio.h>
#include <stdlib.h>

/*
	FUNCI�N: tribonacci (int x,int y, int z, int limit)
	RECIBE: int x (PRIMER N�MERO A SUMAR), int y (SEGUNDO N�MERO A SUMAR),
		int z (TERCER N�MERO A SUMAR), int limit (POSICI�N L�MITE), int n 
		(POSICI�N ACTUAL).
	DEVUELVE: SE LLAMA A S� MISMA SI ES NECESARIO.
	DESCRIPCI�N: FUNCI�N ENCARGADA DE CALCULAR LOS N�MEROS DE LA SERIE DE TRIBONACCI.
	OBSERVACIONES: CUANDO EL N�MERO ES MUY GRANDE IMPRIME NEGATIVOS.
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