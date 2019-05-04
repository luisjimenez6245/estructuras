#include <stdio.h>
#include <stdlib.h>
#include "presentacion.h"
//CONSTANTES A UTILIZAR
#define TRUE  1
#define FALSE 0
//VARIABLE GLOBAL POR COMODIDAD
int i;

// validarPosicion si una reina est� bien colocada
// -----------------------------------------
// La reina de la fila i est� bien colocada si no est�
// en la columna ni en la misma diagonal que cualquiera
// de las reinas de las filas anteriores
//
// Par�metros
//   fila   - Fila de la reina cuya posici�n queremos validar
//   posReinas - Array con las posiciones de las reinas
//   n      - N�mero de reinas


int validarPosicion(int fila, int posReinas[], int n) {
  for (i=0; i<fila; i++)
      //SI posReinas[i]==posReinas[fila] ENTONCES EST�N EN LA MISMA COLUMNA
      //SI posReinas[fila]-posReinas[i]=(fila-columna) ENTONCES EST�N EN LA MISMA DIAGONAL
      if ((posReinas[i]==posReinas[fila])||(abs(fila-i) == abs(reinas[fila]-reinas[i])))
         return FALSE;
  return TRUE;
}


// Mostrar el tablero con las reinas
// ---------------------------------
// Par�metros:
//   reinas - Vector con las posiciones de las distintas reinas
//   n      - N�mero de reinas

void mostrarTablero(int posReinas[], int n, int *alto)
{
  int i,j,x=0,y=*alto, aux=0;
  for (i=0; i<n; i++) {
      x=0;
      for (j=0; j<n; j++) {

          if (reinas[i]==j){
            MoverCursor(x,y);
            printf("##");
            MoverCursor(x,y+1);
            printf("##");
          }else{
            if((j+aux)%2 == 0){
              MoverCursor(x,y);
              printf(",,");
              MoverCursor(x,y+1);
              printf(",,");
            }else{
              MoverCursor(x,y);
              printf("..");
              MoverCursor(x,y+1);
              printf("..");
            }
          }
          x+=3;
      }
      y+=2;
      aux=1-aux;
      //printf(" %d %d\n",i,reinas[i]);
      *alto = y+3;
  }
}


// Colocaci�n de una reina
// -----------------------
// Par�metros
//   fila   - Fila de la reina que queremos colocar
//   reinas - Vector con las posiciones de las reinas
//   n      - N�mero de reinas

void Reina (int fila, int reinas[], int n, int *alto)
{
  int ok = FALSE;

  if (fila<n) {

     // Quedan reinas por colocar

     for (reinas[fila]=0; reinas[fila]<n; reinas[fila]++) {

         // Comprobamos si la posici�n 
         // de la reina a |ctual es v�lida

         if (validarPosicion(fila,reinas,n)) {

            // Si es as�, intentamos colocar
            // las reinas restantes
            nReina (fila+1, reinas, n, alto);
         }
     } 
  
  } else {

     // No quedan reinas por colocar (soluci�n)
     dibuja(reinas,n,alto);
  }

  return;
}

// Programa principal
// ------------------

int main (){
  int numReinas;  // N�mero de reinas
  int alto=0;
  printf("Ingresa el numero de reinas: ");
  scanf("%i", &nreinas);
  int posReinas[numReinas];
  system("cls");
  //INICIALIZAMOS EL VECTOR CON UN VALOR NEGATIVO (NO ENTRA EN EL RANGO DEL ARREGLO) PARA FACILITAR SU MANIPULACI�N
  for (i=0; i<nreinas; i++)
    posReinas[i] = -1;
   // Colocar reinas (algoritmo recursivo)
   Reina(0,reinas,nreinas, &alto);
}