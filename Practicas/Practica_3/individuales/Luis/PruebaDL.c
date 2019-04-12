#include<stdio.h>
#include "TADListaDL.h"

void contactos(){}




int main(){
    lista list;
    posicion pos;
    elemento e;
    int i = 0;

    Initialize(&list);
    for(i = 0; i <10; ++i){
        Add(&list, e);
    }
    pos = First(&list);
    Following(&list,pos);
    VerLigasLista(&list);
    Destroy(&list);
}