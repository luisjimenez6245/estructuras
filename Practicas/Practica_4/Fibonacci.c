/*
    FIBONACCI
*/
#include <stdio.h>
#include <stdlib.h>

void fibonacci(int n,int m, int limit){
    if(n==0&&m==1){
        printf("0, 1, ");
    }
    if(m>=limit){
        return;
    }
    printf("%i, ",m+n);
    fibonacci(m,m+n,limit);
}

int main(){
    int n;
    printf("Ingresa el numero limite:\n>");
    scanf("%i",&n);
    fibonacci(0,1,n);
    return 0;
}
