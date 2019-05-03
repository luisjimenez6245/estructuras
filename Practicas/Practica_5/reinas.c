/*
	PRÁCTICA 05: N-REINAS MIS NIÑOS
	AUTORES: 
		JIMÉNEZ DELGADO LUIS DIEGO
		SÁNCHEZ CASTRO AARÓN GAMALIEL
		SÁNCHEZ TIRADO CITLALI YASMÍN
	VERSIÓN: 1.0
	DESCRIPCIÓN: NPI DE QUÉ HACE EL PROGRAMA
*/
//LIBRERÍAS A UTILIZAR
#include <stdio.h>
#include <stdlib.h>
#include "Gotoxy.h"
//CONSTANTES 
#define FALSE 0
#define TRUE 1

void reina(){
	int valido = FALSE;
	  if (f<n) {
	     // Quedan reinas por colocar
	     for (reinasTablero[f]=0;reinasTablero[f]<n;PrincesaXd[f]++) {

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

int main(){

	return 0;
}