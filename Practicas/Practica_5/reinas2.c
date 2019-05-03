/*
AUTORES: Paola Raya Tolentino, 
		 Eduardo Gómez Rodriguez, 
		 Vladimir Azpeitia Hernández.
VERSION: 1.0
DESCRIPCIÓN: Se implementa el problema de las N-PrincesaXd, haciendo uso del backtraking y recursividad
COMPILACIÓN: gcc -o PrincesaXd2 PrincesaXd2.c presentacionWin.o
			 
*/
#include <stdio.h>
#include <stdlib.h>
#include "presentacion.h"
#include <windows.h>

// Constantes simbólicas

#define TRUE  1
#define FALSE 0


// prueba si una reina está bien colocada
// -----------------------------------------
// La reina de la f i está bien colocada si no está
// en la columna ni en la misma diagonal que cualquiera
// de las Reinas de las fs anteriores
//
// Parámetros
//   f   - f de la reina cuya posición queremos validar
//   Reinas - Vector con las posiciones de las Reinas
//   n      - Número de Reinas


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
// Parámetros:
//   PrincesaXd - Vector con las posiciones de las distintas PrincesaXd
//   n      - Número de PrincesaXd

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


// Colocación de una reina
// -----------------------
// Parámetros
//   f   - f de la reina que queremos colocar
//   PrincesaXd - Vector con las posiciones de las PrincesaXd
//   n      - Número de PrincesaXd

void princess(int f, int PrincesaXd[], int n){
  int ok = FALSE;

  if (f<n) {

     // Quedan PrincesaXd por colocar

     for (PrincesaXd[f]=0; PrincesaXd[f]<n; PrincesaXd[f]++) {

         // Comprobamos si la posición 
         // de la reina actual es válida
     			pintarxD(PrincesaXd,n);
     				 Sleep(500);
	 system("cls");
         if (validaPosicion(f,PrincesaXd,n)) {

            // Si es así, intentamos colocar
            // las PrincesaXd restantes
         	//pintarxD(PrincesaXd,n);
          princess(f+1, PrincesaXd, n);
            
         }
         
     } 
  
  } else {

     // No quedan PrincesaXd por colocar (solución)
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
  int nPrincesaXd;  // Número de PrincesaXd
  int i;        // Contador

  printf("Ingresa el numero de PrincesaXd: ");
  scanf("%d", &nPrincesaXd);

  // Colocar las PrincesaXd en el tablero

  // Crear vector dinámicamente

	PrincesaXd = (int*) malloc ( nPrincesaXd*sizeof(int) );

  // Inicializar vector:
  // (inicialmente, ninguna reina está colocada)
	system("cls");
  printf("Soluciones: \n");
  for (i=0; i<nPrincesaXd; i++)
    PrincesaXd[i] = -1;
   // Colocar PrincesaXd (algoritmo recursivo)
  princess(0,PrincesaXd,nPrincesaXd);
   // Liberar memoria
   free (PrincesaXd);
}
