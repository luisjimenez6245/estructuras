/*
AUTORES: Paola Raya Tolentino, 
		 Eduardo G�mez Rodriguez, 
		 Vladimir Azpeitia Hern�ndez.
VERSION: 1.0
DESCRIPCI�N: Se implementa el problema de las N-PrincesaXd, haciendo uso del backtraking y recursividad
COMPILACI�N: gcc -o PrincesaXd2 PrincesaXd2.c presentacionWin.o
			 
*/
#include <stdio.h>
#include <stdlib.h>
#include "presentacion.h"
#include <windows.h>

// Constantes simb�licas

#define TRUE  1
#define FALSE 0


// prueba si una reina est� bien colocada
// -----------------------------------------
// La reina de la f i est� bien colocada si no est�
// en la columna ni en la misma diagonal que cualquiera
// de las Reinas de las fs anteriores
//
// Par�metros
//   f   - f de la reina cuya posici�n queremos validar
//   Reinas - Vector con las posiciones de las Reinas
//   n      - N�mero de Reinas


int validaPosicion(int f, int PrincesaXd[], int n){
  int i;
  for(i=0; i<f; i++){
    if((PrincesaXd[i] == PrincesaXd[f]) || (abs(f-i) == abs(PrincesaXd[f]-PrincesaXd[i]))){  //Comprueba la compatibilidad entre reinas :v 
      return FALSE;
    }
  }
  return TRUE;
}


// Mostrar el tablero con las PrincesaXd
// ---------------------------------
// Par�metros:
//   PrincesaXd - Vector con las posiciones de las distintas PrincesaXd
//   n      - N�mero de PrincesaXd

void pintarxD(int PrincesaXd[], int n){
  int i,j;

  for (i=0; i<n; i++) {
  	  for (j=0; j<n; j++) {
          if (PrincesaXd[i]==j){
            printf("R");
          }else{
			if((j+i)%2 == 0)
			  printf("%c", 176);
			else
			  printf("%c", 178);
          }
      }
      printf("\n");
      //printf(" %d %d\n",i,PrincesaXd[i]);
  }
  printf("\n");
}


// Colocaci�n de una reina
// -----------------------
// Par�metros
//   f   - f de la reina que queremos colocar
//   PrincesaXd - Vector con las posiciones de las PrincesaXd
//   n      - N�mero de PrincesaXd

void princess(int f, int PrincesaXd[], int n){
  int ok = FALSE;

  if (f<n) {

     // Quedan PrincesaXd por colocar

     for (PrincesaXd[f]=0; PrincesaXd[f]<n; PrincesaXd[f]++) {

         // Comprobamos si la posici�n 
         // de la reina actual es v�lida
     			pintarxD(PrincesaXd,n);
     				 Sleep(500);
	 system("cls");
         if (validaPosicion(f,PrincesaXd,n)) {

            // Si es as�, intentamos colocar
            // las PrincesaXd restantes
         	//pintarxD(PrincesaXd,n);
          princess(f+1, PrincesaXd, n);
            
         }
         
     } 
  
  } else {

     // No quedan PrincesaXd por colocar (soluci�n)
		//pintarxD(PrincesaXd,n);
  	printf("solucion\n");
  }

  return;
}

// Programa principal
// ------------------

int main ()
{
  int *PrincesaXd;  // Vector con las posiciones de las PrincesaXd de cada f
  int nPrincesaXd;  // N�mero de PrincesaXd
  int i;        // Contador

  printf("Ingresa el numero de PrincesaXd: ");
  scanf("%d", &nPrincesaXd);

  // Colocar las PrincesaXd en el tablero

  // Crear vector din�micamente

	PrincesaXd = (int*) malloc ( nPrincesaXd*sizeof(int) );

  // Inicializar vector:
  // (inicialmente, ninguna reina est� colocada)
	system("cls");
  printf("Soluciones: \n");
  for (i=0; i<nPrincesaXd; i++)
    PrincesaXd[i] = -1;
   // Colocar PrincesaXd (algoritmo recursivo)
  princess(0,PrincesaXd,nPrincesaXd);
   // Liberar memoria
   free (PrincesaXd);
}
