/*
AUTORES: Paola Raya Tolentino, 
		 Eduardo G�mez Rodriguez, 
		 Vladimir Azpeitia Hern�ndez.
VERSION: 1.0
DESCRIPCI�N: Se implementa el problema de las N-Reinas, haciendo uso del backtraking y recursividad
COMPILACI�N: gcc -o reinas2 reinas2.c presentacionWin.o
			 
*/
#include <stdio.h>
#include <stdlib.h>
#include "presentacion.h"

// Constantes simb�licas

#define TRUE  1
#define FALSE 0


// prueba si una reina est� bien colocada
// -----------------------------------------
// La reina de la fila i est� bien colocada si no est�
// en la columna ni en la misma diagonal que cualquiera
// de las reinas de las filas anteriores
//
// Par�metros
//   fila   - Fila de la reina cuya posici�n queremos validar
//   reinas - Vector con las posiciones de las reinas
//   n      - N�mero de reinas


int prueba (int fila, int reinas[], int n) 
{
  int i;

  for (i=0; i<fila; i++)
      if (  ( reinas[i]==reinas[fila] )                      // Misma columna
         || ( abs(fila-i) == abs(reinas[fila]-reinas[i]) ) ) // Misma diagonal
         return FALSE;

  return TRUE;
}


// Mostrar el tablero con las reinas
// ---------------------------------
// Par�metros:
//   reinas - Vector con las posiciones de las distintas reinas
//   n      - N�mero de reinas

void dibuja (int reinas[], int n, int *alto)
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

void nReina (int fila, int reinas[], int n, int *alto)
{
  int ok = FALSE;

  if (fila<n) {

     // Quedan reinas por colocar

     for (reinas[fila]=0; reinas[fila]<n; reinas[fila]++) {

         // Comprobamos si la posici�n 
         // de la reina actual es v�lida

         if (prueba(fila,reinas,n)) {

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

int main ()
{
  int *reinas;  // Vector con las posiciones de las reinas de cada fila
  int nreinas;  // N�mero de reinas
  int i;        // Contador
  int alto=0;

  printf("Ingresa el numero de reinas: ");
  scanf("%d", &nreinas);

  // Colocar las reinas en el tablero

  // Crear vector din�micamente

	reinas = (int*) malloc ( nreinas*sizeof(int) );

  // Inicializar vector:
  // (inicialmente, ninguna reina est� colocada)
	system("cls");
  for (i=0; i<nreinas; i++)
    reinas[i] = -1;
   // Colocar reinas (algoritmo recursivo)
   nReina(0,reinas,nreinas, &alto);
   // Liberar memoria
   free (reinas);
}
