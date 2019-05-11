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
  FUNCI�N: validarPosicion(int fila, int posReinas[], int n)
  RECIBE: int fila (FILA DE LA REINA A VALIDAR), int[] posReinas (POSICIONES DE LAS REINAS EN EL TABLERO)
    int n (N�MERO DE REINAS INGRESADO POR EL USUARIO)
  DEVUELVE: TRUE/FALSE SEG�N SEA EL CASO.
  DESCRIPCI�N: LA FUNCI�N VALIDA QUE LA REINA EST� BIEN COLOCADA, SE COMPRUEBA QUE PARA CUALQUIER FILA i
    UNA REINA NO EST� EN LA MISMA COLUMNA (SE COMPRUEBA QUE TODOS LOS N�MEROS EN EL ARREGLO SENA DIFERENTES).
    ADEM�S, EL PROBLEMA DE LAS DIAGONALES ASCENDENTES/DESCENDENTES SE ARREGLA REALIZANDO LA OPERACI�N 
    fila-columna, ESTA OPERACI�N DEBE TENER UN RESULTADO DIFERENTE PARA CADA PAR ORDENADO DEL ARREGLO.
  OBSERVACIONES:
*/
int validarPosicion(int fila, int posReinas[], int n) {
  for (i=0; i<fila; i++){
    //SI posReinas[i]==posReinas[fila] ENTONCES EST�N EN LA MISMA COLUMNA
    //SI posReinas[fila]-posReinas[i]=(fila-columna) ENTONCES EST�N EN LA MISMA DIAGONAL
    if ((posReinas[i]==posReinas[fila])||(abs(fila-i) == abs(posReinas[fila]-posReinas[i]))){
      return FALSE;
    }
  }   
  return TRUE;
}

/*
  FUNCI�N: mostrarTablero( int posReinas[], int n, int *alto)
  RECIBE: int[] posReinas (POSICIONES DE LAS REINAS EN EL TABLERO)
    int n (N�MERO DE REINAS INGRESADO POR EL USUARIO), int* alto (ORDENADA PARA SITUAR EL CURSOR E IMPRIMIR)
  DEVUELVE: NADA.
  DESCRIPCI�N: IMPRIME EL TABLERO CON LAS POSICIONES ALMACENADAS EN EL ARREGLO AL MOMENTO.
  OBSERVACIONES: PARA CASOS DONDE n (N�MERO DE REINAS) ES "GRANDE" (P.E: 10) ES NECESARIO QUE EL TAMA�O DEL B�FER
    DE PANTALLA SEA IGUALMENTE GRANDE PARA EVITAR UN DESBORDAMIENTO Y LA P�RDIDA DE LOS GR�FICOS.
*/
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
            if((j+aux)%2 == 0){//SE COLOCA UN "ESPACIO BLANCO"
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
      *alto = y+2;
  }
  printf("\n");
}


/*
  FUNCI�N: Reina(int fila, int posReinas[], int *alto).
  RECIBE: int fila (FILA DONDE SE COLOCAR� A LA NUEVA REINA), int[] posReinas (TABLERO DE POSICIONES DE LAS REINAS)
    ,int* alto (ORDENADA PARA SITUAR EL CURSOR).
  DEVUELVE: LLAMA A LA FUNCI�N NUEVAMENTE, SEG�N SEA EL CASO.
  DESCRIPCI�N: COLOCA UNA REINA EN EL TABLERO. LLAMA A LA FUNCI�N validarPosicion CADA VEZ QUE LO HACES
  OBSERVACIONES:
*/
void Reina (int fila, int posReinas[], int n, int *alto)
{
  int ok = FALSE;
  if (fila<n) {
     // Quedan reinas por colocar
     for (posReinas[fila]=0;posReinas[fila]<n;posReinas[fila]++) {
          //COMPROBAMOS SI LA POSICI�N ES V�LIDA �PUEDO MANDAR A IMPRIMIR?
          mostrarTablero(posReinas,n,alto);
          EsperarMiliSeg(400);
         if (validarPosicion(fila,posReinas,n)) {
            //SI LA POSICI�N ES V�LIDA, PROCEDEMOS A COLOCAR LA(S) SIGUIENTE(S) REINA(S)
            Reina(fila+1,posReinas,n,alto);
         }
         //AQU� SE HACE EL BACKTRACKING, EN CASO DE NO SER V�LIDA, SIMPLEMENTE NO SE LLAMA A LA FUNCI�N Y SE SIGUE EL for
     } 
  } else {
    printf("SOLUCION");
  }
  return;
}

int main (){
  int numReinas;  // N�mero de reinas
  int alto=0;
  printf("--------------------\nBIENVENIDO\n--------------------\n");
  printf("Ingresa la cantidad de reinas a colocar (4<=numero<=10):\n>");
  scanf("%i", &numReinas);
  int posReinas[numReinas];
  system("cls");
  //INICIALIZAMOS EL ARREGLO CON UN VALOR NEGATIVO (NO ENTRA EN EL RANGO DEL ARREGLO) PARA FACILITAR SU MANIPULACI�N
  for (i=0; i<numReinas; i++)
    posReinas[i] = -1;
   //COMENZAMOS CON LA RECURSIVIDAD PARA COLOCAR LAS REINAS
   Reina(0,posReinas,numReinas,&alto);
}