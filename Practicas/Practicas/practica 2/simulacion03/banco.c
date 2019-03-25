#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include "TADColaDin.h"
#include "presentacion.h"

#define sup 10
#define inf 40
#define izq 1
#define der 134

typedef struct ruta{
	int x;
	int y;
}ruta;

typedef struct dCaja{
	int xP;
	int yP;
	int xL;
	int yL;
	char estado;
}dCaja;

ruta filaU[42];
ruta filaC[98];
ruta filaP[70];

void serpienteXd(int posiX, int posiY, int col, char fila){
	char sentido = 'S';
	int l=0;
	for(int i=0; i<col; i++){

		if(sentido == 'S'){
			for(int j=inf-2; j>sup+1; j-=2, l++){
				MoverCursor(posiX, j);
				// printf("+");
				if(fila == 'P'){
					filaP[l].x = posiX;
					filaP[l].y = j;
				}
				if(fila == 'C'){
					filaC[l].x = posiX;
					filaC[l].y = j;
				}
				if(fila == 'U'){
					filaU[l].x = posiX;
					filaU[l].y = j;
				}
				if(j==sup+2){
					posiX -= 7;
				}
			}
		}
		if(sentido == 'B'){
			for(int j=sup+2; j<inf-1; j+=2, l++){
				MoverCursor(posiX, j);
				// printf("-");
				if(fila == 'P'){
					filaP[l].x = posiX;
					filaP[l].y = j;
				}
				if(fila == 'C'){
					filaC[l].x = posiX;
					filaC[l].y = j;
				}
				if(fila == 'U'){
					filaU[l].x = posiX;
					filaU[l].y = j;
				}
				if(j==inf-2){
					posiX -= 7;
					// MoverCursor(posiX, j);
					// printf("Si llego we");
				}
			}
		}

		if(i%2 == 0)
			sentido = 'B';
		else
			sentido = 'S';
	}

	return;
}

void invertirSerpiente(){
	ruta filaU2[42];
	ruta filaC2[98];
	ruta filaP2[70];

	for(int i=70, j=0; i>=0; i--, j++){
		filaP2[j].x = filaP[i].x; 
		filaP2[j].y = filaP[i].y; 
	}

	for(int i=98, j=0; i>=0; i--, j++){
		filaC2[j].x = filaC[i].x; 
		filaC2[j].y = filaC[i].y; 
	}

	for(int i=42, j=0; i>=0; i--, j++){
		filaU2[j].x = filaU[i].x; 
		filaU2[j].y = filaU[i].y; 
	}

	for(int i=70; i>=0; i--){
		filaP[i] = filaP2[i];
	}

	for(int i=98; i>=0; i--){
		filaC[i] = filaC2[i];
	}

	for(int i=42; i>=0; i--){
		filaU[i] = filaU2[i];
	}

	filaP[0].x=12;
	filaP[0].y=11;

	filaU[0].x=114;
	filaU[0].y=11;

	filaC[0].x=56;
	filaC[0].y=11;

	return;
}

void pintarFilas(){
	for(int j=izq+9, k=0; j<=der; j+=7, k++){
		for(int i=sup; i<=inf; i++){
			MoverCursor(j,i);

			if(k==5 || k==6 || k==13 || k==14 || k==17 || k==18){
				printf("#");
				if((k==6 || k==14) && i==inf)
					printf("#######");
			}
			else{
				if(k%2==1 && k>0 && i>inf-4 && i!=inf){
					printf(" ");
				}
				else{
					if(k%2==0 && k>0 && i<sup+4 && i!=sup){
						printf(" ");
					}
					else{
						printf("#");
					}
				}
				if(i==inf || i==sup){
					MoverCursor(j+1,i);
					if((izq+9 == j) && i==sup){
						printf("     ");
					}
					else{
						if((k==4 || k==12 || k==16) && (i==inf))
							printf("     ");
						else
							printf("#######");
					}
				}
			}
		}

		if(k==5 || k==13)
			j+=2;
	}

	serpienteXd(40,30, 5, 'P');
	serpienteXd(98,30, 7, 'C');
	serpienteXd(128,30, 3, 'U');

	return;
}

void pintarCajera(int numCajera, int x, dCaja Caja){
	Caja.xP = x;
	Caja.yP = 4;
	Caja.xL = x;
	Caja.yL = 1;
	MoverCursor(x,3);
	printf("|   |");
	MoverCursor(x, 0);
	printf("Caja %d", numCajera);

	return;
}

void pintarVentanillas(int cantVentanillas, dCaja Caja[]){
	for(int i=izq; i<=der; i++){
		MoverCursor(i,2);
		printf("_");
	}

	for(int i=1, x=5; i<=cantVentanillas; i++, x+=13)
		pintarCajera(i, x, Caja[i-1]);

	return;
}

void pintarCliente(elemento aux){
	switch(aux.tipoCliente){
		case 'C':
			MoverCursor(filaC[aux.id-1].x, filaC[aux.id-1].y);
			printf("     ");
			MoverCursor(filaC[aux.id-1].x, filaC[aux.id-1].y);
			printf("%c%d", aux.tipoCliente, aux.id);
		break;

		case 'P':
			MoverCursor(filaP[aux.id-1].x, filaP[aux.id-1].y);
			printf("     ");
			MoverCursor(filaP[aux.id-1].x, filaP[aux.id-1].y);
			printf("%c%d", aux.tipoCliente, aux.id);
		break;

		case 'U':
			MoverCursor(filaU[aux.id-1].x, filaU[aux.id-1].y);
			printf("     ");
			MoverCursor(filaP[aux.id-1].x, filaP[aux.id-1].y);
			printf("%c%d", aux.tipoCliente, aux.id);
		break;
	}

	return;
}

void pintarEstadoCaja(dCaja CajaAtendiendo, int lugar){
	MoverCursor(5+lugar*13, 1);
	printf("      ");
	MoverCursor(5+lugar*13, 1);
	if(CajaAtendiendo.estado == 'A')
		printf("Atendiendo Cliente");
	else
		printf("Sin Atender");

	return;
}

void limpiar(){
	int i;

	for(i=0; i<42; i++){
		MoverCursor(filaC[aux.id-1].x, filaC[aux.id-1].y);
		printf("       ");
	}

	for(i=0; i<42; i++){
		MoverCursor(filaP[aux.id-1].x, filaP[aux.id-1].y);
		printf("       ");
	}

	for(i=0; i<42; i++){
		MoverCursor(filaU[aux.id-1].x, filaU[aux.id-1].y);
		printf("       ");
	}
}

int main(){

	cola filaPreferente;
	cola filaCliente;
	cola filaUsuario;

	Initialize(&filaPreferente);
	Initialize(&filaCliente);
	Initialize(&filaUsuario);

	//Variables a pedir
	unsigned int cantidadDeCajeros, velClientes, velUsuarios, velPreferentes, perLlegadas=0, tiempo=0, idClientes=0, idPreferentes=0, idUsuarios=0, perAtendidos=0, noUserAtendido=1;
	elemento aux;
	int i;

	// Pedir informacion
	printf("Cuantas cajas estaran abiertas en tu banco? ");
	scanf("%d", &cantidadDeCajeros);

	dCaja Caja[cantidadDeCajeros];
	unsigned int tiempoAtencionCajero[cantidadDeCajeros];

	for(i=0; i<cantidadDeCajeros; i++){
		printf("Cual es la velocidad de atencion de la caja %d? ", i+1);
		scanf("%d", &tiempoAtencionCajero[i]);
	}

	printf("Cual sera la velocidad de llegada de los clientes? ");
	scanf("%d", &velClientes);

	printf("Cual sera la velocidad de llegada de los Preferentes? ");
	scanf("%d", &velPreferentes);

	printf("Cual sera la velocidad de llegada de los Usuarios? ");
	scanf("%d", &velUsuarios);

	system("cls");
	pintarFilas();
	pintarVentanillas((int)cantidadDeCajeros, Caja);
	invertirSerpiente();

	while(perLlegadas != 50){
		tiempo++;

		//Llegan clientes
		if(tiempo%velClientes == 0){
			idClientes++;
			perLlegadas++;
			aux.tipoCliente = 'C';
			aux.id = idClientes;
			Queue(&filaCliente, aux);
		}
		if(tiempo%velPreferentes == 0){
			idPreferentes++;
			perLlegadas++;
			aux.tipoCliente = 'P';
			aux.id = idPreferentes;
			Queue(&filaPreferente, aux);
		}
		if(tiempo%velUsuarios == 0){
			idUsuarios++;
			perLlegadas++;
			aux.tipoCliente = 'U';
			aux.id = idUsuarios;
			Queue(&filaUsuario, aux);
		}

		//Se atienden Clientes
		for(i=0; i<cantidadDeCajeros; i++){
			if(cantidadDeCajeros == 1){
				if(tiempo%tiempoAtencionCajero[i] == 0){
					if(!Empty(&filaPreferente) && perAtendidos%5!=0){
						Caja[i].estado='A';
						perAtendidos++;
						Dequeue(&filaPreferente);
					}
					else{
						if(!Empty(&filaCliente) && perAtendidos%5!=0){
							Caja[i].estado='A';
							perAtendidos++;
							Dequeue(&filaCliente);
						}
						else{
							if(!Empty(&filaUsuario)){
								Caja[i].estado='A';
								perAtendidos++;
								Dequeue(&filaUsuario);
							}
							else{
								Caja[i].estado='N';
							}
						}
					}
				}
			}
			else{
				// printf("Valor: %d\n", perAtendidos);
				if(cantidadDeCajeros>1){
					if(i==cantidadDeCajeros){
						if(!Empty(&filaCliente)){
							Caja[i].estado='A';
							perAtendidos++;
							Dequeue(&filaCliente);
						}
						else{
							if(!Empty(&filaPreferente) && perAtendidos%5!=0){
								Caja[i].estado='A';
								perAtendidos++;
								Dequeue(&filaPreferente);
							}
							else{
								if(!Empty(&filaUsuario)){
									Caja[i].estado='A';
									perAtendidos++;
									Dequeue(&filaPreferente);
								}
								else{
									Caja[i].estado='N';
								}
							}
						}
					}
					else{
						if(!Empty(&filaPreferente) && perAtendidos%5!=0){
							Caja[i].estado='A';
							perAtendidos++;
							Dequeue(&filaPreferente);
						}
						else{
							if(!Empty(&filaCliente) && perAtendidos%5!=0){
								Caja[i].estado='A';
								perAtendidos++;
								Dequeue(&filaCliente);
							}
							else{
								if(!Empty(&filaUsuario)){
									Caja[i].estado='A';
									perAtendidos++;
									Dequeue(&filaUsuario);
								}
								else{
									Caja[i].estado='N';
								}
							}
						}
					}
				}
			}
		}

		//Se pintan de colores
		limpiar();

		for(i=0; i<Size(&filaCliente); i++)
		 	pintarCliente(Element(&filaCliente, i+1));

		for(i=0; i<Size(&filaPreferente); i++)
			pintarCliente(Element(&filaPreferente, i+1));

		for(i=0; i<Size(&filaUsuario); i++)
			pintarCliente(Element(&filaUsuario, i+1));

		for(i=0; i<cantidadDeCajeros; i++)
			pintarEstadoCaja(Caja[i], i);


		Sleep(100);
	}

	MoverCursor(izq,inf);
	printf("Llego aqui we2\n");

	return 0;
}