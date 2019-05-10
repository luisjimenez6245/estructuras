/*
    TRIBONACCI
*/
#include <stdio.h>
#include <stdlib.h>

void tribonacci(int x, int y, int z, int limit){
    if(x==0&&y==0&&z==1){
        printf("0, 0, 1, ");
    }
    if(z>=limit){
        return;
    }
    printf("%i, ",x+y+z);
    tribonacci(y,z,x+y+z,limit);
}

int main(){
    int n;
    printf("Ingresa el número limite:\n>");
    scanf("%i",&n);
    tribonacci(0,0,1,n);
    return 0;
}