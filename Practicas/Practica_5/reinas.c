/*
  BACKTRACKING N-REINAS
  AUTORES: 
    JIMÉNEZ DELGADO LUIS DIEGO
    SÁNCHEZ CASTRO AARÓN GAMALIEL
    SÁNCHEZ TIRADO CITLALI YASMÍN
  VERSIÓN 1.5
  DESCRIPCIÓN: EL PROGRAMA COLOCA N NÚMERO DE REINAS DADAS POR EL USUARIO EN UN TABLERO DE DIMENSIÓN NxN
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
  FUNCIÓN:
  RECIBE:
  DEVUELVE:
  DESCRIPCIÓN: 
  OBSERVACIONES:
*/
// La reina de la fila i está bien colocada si no está
// en la columna ni en la misma diagonal que cualquiera
// de las reinas de las filas anteriores
//
// Parámetros
//   fila   - Fila de la reina cuya posición queremos validar
//   posReinas - Array con las posiciones de las reinas
//   n      - Número de reinas


int validarPosicion(int fila, int posReinas[], int n) {
  for (i=0; i<fila; i++){
    //SI posReinas[i]==posReinas[fila] ENTONCES ESTÁN EN LA MISMA COLUMNA
    //SI posReinas[fila]-posReinas[i]=(fila-columna) ENTONCES ESTÁN EN LA MISMA DIAGONAL
    if ((posReinas[i]==posReinas[fila])||(abs(fila-i) == abs(posReinas[fila]-posReinas[i]))){
      return FALSE;
    }
  }   
  return TRUE;
} //terminamos con la funcion


// Mostrar el tablero con las reinas
// ---------------------------------
// Parámetros:
//   reinas - Vector con las posiciones de las distintas reinas
//   n      - Número de reinas

void mostrarTablero(int posReinas[], int n, int *alto)
{
  x=0;
  y=*alto;
  aux=0;
  for (i=0; i<n; i++) {
      x=0;//SERÁ REUTILIZADA, POR LO TANTO ES NECESARIO REINICIAR EL CONTADOR
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


// Colocación de una reina
// -----------------------
// Parámetros
//   fila   - Fila de la reina que queremos colocar
//   reinas - Vector con las posiciones de las reinas
//   n      - Número de reinas

void Reina (int fila, int posReinas[], int n, int *alto)
{
  int ok = FALSE;
  if (fila<n) {
     // Quedan reinas por colocar
     for (posReinas[fila]=0;posReinas[fila]<n;posReinas[fila]++) {
          //COMPROBAMOS SI LA POSICIÓN ES VÁLIDA
          //¿PUEDO MANDAR A IMPRIMIR?
          mostrarTablero(posReinas,n,alto);
          EsperarMiliSeg(400);
         if (validarPosicion(fila,posReinas,n)) {
            //SI LA POSICIÓN ES VÁLIDA, PROCEDEMOS A COLOCAR LA(S) SIGUIENTE(S) REINA(S)
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
  int numReinas;  // Número de reinas
  int alto=0;
  printf("--------------------\nBIENVENIDO\n--------------------\n");
  printf("Ingresa la cantidad de reinas a colocar (4<=numero<=10):\n>");
  scanf("%i", &numReinas);
  int posReinas[numReinas];
  system("cls");
  //INICIALIZAMOS EL VECTOR CON UN VALOR NEGATIVO (NO ENTRA EN EL RANGO DEL ARREGLO) PARA FACILITAR SU MANIPULACIÓN
  for (i=0; i<numReinas; i++)
    posReinas[i] = -1;
   // Colocar reinas (algoritmo recursivo)
   Reina(0,posReinas,numReinas,&alto);
}