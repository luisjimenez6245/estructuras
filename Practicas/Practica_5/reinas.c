/*
  BACKTRACKING N-REINAS
  AUTORES: 
    JIM�NEZ DELGADO LUIS DIEGO
    S�NCHEZ CASTRO AAR�N GAMALIEL
    S�NCHEZ TIRADO CITLALI YASM�N
  VERSI�N 1.5
  DESCRIPCI�N: EL PROGRAMA COLOCA N N�MERO DE REINAS DADAS POR EL USUARIO EN UN TABLERO DE DIMENSI�N NxN
  EL OBJETIVO ES POSICIONAR A LAS REINAS DE MANERA QUE NINGUNA SE AMENACE CON EL RESTO.
*/
#include <stdio.h>
#include <stdlib.h>
#include "Gotoxy.h"
//CONSTANTES A UTILIZAR
#define TRUE  1
#define FALSE 0

//VARIABLES GLOBALES POR COMODIDAD
int i,j,x,y,aux;

/*
  FUNCI�N:
  RECIBE:
  DEVUELVE:
  DESCRIPCI�N: 
  OBSERVACIONES:
*/
// La reina de la fila i est� bien colocada si no est�
// en la columna ni en la misma diagonal que cualquiera
// de las reinas de las filas anteriores
//
// Par�metros
//   fila   - Fila de la reina cuya posici�n queremos validar
//   posReinas - Array con las posiciones de las reinas
//   n      - N�mero de reinas


int validarPosicion(int fila, int posReinas[], int n) {
  for (i=0; i<fila; i++){
    //SI posReinas[i]==posReinas[fila] ENTONCES EST�N EN LA MISMA COLUMNA
    //SI posReinas[fila]-posReinas[i]=(fila-columna) ENTONCES EST�N EN LA MISMA DIAGONAL
    if ((posReinas[i]==posReinas[fila])||(abs(fila-i) == abs(posReinas[fila]-posReinas[i]))){
      return FALSE;
    }
  }   
  return TRUE;
} //terminamos con la funcion


// Mostrar el tablero con las reinas
// ---------------------------------
// Par�metros:
//   reinas - Vector con las posiciones de las distintas reinas
//   n      - N�mero de reinas

void mostrarTablero(int posReinas[], int n, int *alto)
{
  x=0;
  y=*alto;
  aux=0;
  for (i=0; i<n; i++) {
      x=0;//SER� REUTILIZADA, POR LO TANTO ES NECESARIO REINICIAR EL CONTADOR
      for (j=0; j<n; j++) {
          if (posReinas[i]==j){//SE COLOCA UNA REINA
            MoverCursor(x,y);
            printf("%c",219);
          }else{
            if((j+aux)%2 == 0){//SE COLOCA UN ESPACIO
              MoverCursor(x,y);
              printf("%c",176);
            }else{
              MoverCursor(x,y);
              printf("%c",176);
            }
          }
          x+=2;
      }
      y+=1;
      aux=1-aux;
      //printf(" %d %d\n",i,reinas[i]);
      *alto = y+2;
  }
  printf("\n");
}


// Colocaci�n de una reina
// -----------------------
// Par�metros
//   fila   - Fila de la reina que queremos colocar
//   reinas - Vector con las posiciones de las reinas
//   n      - N�mero de reinas

void Reina (int fila, int posReinas[], int n, int *alto)
{
  int ok = FALSE;
  if (fila<n) {
     // Quedan reinas por colocar
     for (posReinas[fila]=0;posReinas[fila]<n;posReinas[fila]++) {
          //COMPROBAMOS SI LA POSICI�N ES V�LIDA
          //�PUEDO MANDAR A IMPRIMIR?
          mostrarTablero(posReinas,n,alto);
          EsperarMiliSeg(400);
         if (validarPosicion(fila,posReinas,n)) {
            //SI LA POSICI�N ES V�LIDA, PROCEDEMOS A COLOCAR LA(S) SIGUIENTE(S) REINA(S)
            Reina(fila+1,posReinas,n,alto);
         }
     } 
  } else {
    printf("SOLUCION");
  }
  return;
}

// Programa principal
// ------------------

int main (){
  int numReinas;  // N�mero de reinas
  int alto=0;
  printf("--------------------\nBIENVENIDO\n--------------------\n");
  printf("Ingresa la cantidad de reinas a colocar (4<=numero<=10):\n>");
  scanf("%i", &numReinas);
  int posReinas[numReinas];
  system("cls");
  //INICIALIZAMOS EL VECTOR CON UN VALOR NEGATIVO (NO ENTRA EN EL RANGO DEL ARREGLO) PARA FACILITAR SU MANIPULACI�N
  for (i=0; i<numReinas; i++)
    posReinas[i] = -1;
   // Colocar reinas (algoritmo recursivo)
   Reina(0,posReinas,numReinas,&alto);
}