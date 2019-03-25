/*
	SIMULACIÓN DE UN BANCO
	AUTOR: SÁNCHEZ CASTRO AARÓN GAMALIEL (C) MARZO 2019
	VERSIÓN: 1.0
	DESCRIPCIÓN: NPI DE QUÉ HACE EL PROGRAMA
	COMANDO PARA COMPILAR: gcc 
*/
//LIBRERÍAS A UTILIZAR 
#include <stdio.h>
#include <stdlib.h>
#include "TADColaDin.h"
#include "Gotoxy.h"
//DEFINICIÓN DE CONSTANTES
#define ANCHO_CAJA 6 //CADA CAJA OCUPA 6 ESPACIOS EN LA CONSOLA
//DATO: SI ANCHO_CAJA=6, MAX_ANCHO_DISPLAY=60 (SUPONIENDO QUE SE TIENEN 10 CAJAS ABIERTAS)
#define X_CLIENTES 20
#define X_PREFERENTES 28
#define X_USUARIOS 40
#define Y_FILAS 7
#define Y_CAJAS 4
#define MAX_PER_FILA 10

//VARIABLES GLOBALES, CONVIENE MANEJARLAS ASÍ PORQUE VARIAS FUNCIONES LAS UTILIZAN
int num_cajas,aux,tClints,tPrefs,tUsus;
elemento fClientes[MAX_PER_FILA], fPreferentes[MAX_PER_FILA], fUsuarios[MAX_PER_FILA];

void printCajas(int *cordCliCajas){
	int cordX;//SE ESTABLECEN LAS COORDENADAS (X) PARA COLOCAR A LOS CLIENTES POSTERIORMENTE
	int ANCHO_DISPLAY=num_cajas*ANCHO_CAJA;
	system("cls");
	printf("------------------------------------------------------------");
	printf("\n\t\t\tBANCO DE MEXICO\n");
	printf("------------------------------------------------------------\n");
	for(aux=0;aux<num_cajas;aux++){
		printf("#|CAJ|");//SE IMPRIMEN LAS CAJAS, EL ESPACIO EN BLANCO SE LLENARÁ POSTERIORMENTE CON C#,U#,P#
	}
	printf("\n");
	for(aux=0;aux<num_cajas;aux++){
		printf("#|   |");//SE IMPRIMEN LAS CAJAS, EL ESPACIO EN BLANCO SE LLENARÁ POSTERIORMENTE CON C#,U#,P#
	}
	//EL SIGUIENTE FOR SE UTILIZA PARA LLENAR UN ARREGLO QUE USAREMOS AL REALIZAR LA ANIMACIÓN DE ATENDER CLEINTES
	for(cordX=2,aux=0;cordX<ANCHO_DISPLAY,aux<num_cajas;cordX=cordX+ANCHO_CAJA,aux++){
		cordCliCajas[aux]=cordX;//GUARDAMOS LAS COORDENADAS CALCULADAS EN UN ARREGLO DE DIMENSIÓN num_cajas
	}
	return;
}

void printCola(cola *cola,int cordX, int cordY, elemento *filaPersonas){
	int tamCola;
	if(!Empty(cola)){
		tamCola=Size(cola);
		for(aux=0;aux<MAX_PER_FILA;aux++){//LLENAMOS EL ARREGLO DE ELEMENTOS CORRESPONDIENTE
			filaPersonas[aux]=Element(cola,aux+1);
		}
		for(aux=0;aux<MAX_PER_FILA;aux++){//IMPRIMIMOS EL ARREGLO DE ELEMENTOS, EL NUMERO CON EL TIPO DE PERSONA
			if(filaPersonas[aux].n!=0){//
				MoverCursor(cordX,cordY++);//MOVEMOS EL CURSOR PARA IMPRIMIR DE MANERA VERTICAL Y CENTRADA
				printf("%c%i",filaPersonas[aux].tipo,filaPersonas[aux].n);
			}
		}
		if(tamCola>MAX_PER_FILA)
			printf("+");//SI EL TAMAÑO DE LA FILA SOBREPASA AL MÁXIMO PERMITIDO, ENTONCES IMPRIMIMO UN +
	}
	return;
}

void atenderPersona(int numeroCaja, elemento pAtendida, int *cordCliCajas){
	MoverCursor(cordCliCajas[numeroCaja],Y_CAJAS);
	printf("%c%i",pAtendida.tipo,pAtendida.n);
	return;
}

void simulacionBanco(int *tiemposAtencion){
	int cordCliCajas[num_cajas]; //AREGLO CON LAS COORDENADAS PARA DIBUJAR A LOS CLIENTES AL MOMENTO EN QUE SON ATENDIDOS
	int pAtendidas=0,cLLegados=0,uLLegados=0,pLLegados=0,tTranscurrido=0;
	//LAS VARIABLES cLLegados, uLlegados y pLlegados SIRVEN COMO CONTADORES PARA CUMPLIR LAS POLÍTICAS DEL BANCO
	int *arregloCord=cordCliCajas;// APUNTADOR AL ARREGLO DE COORDENADAS, PARA FACILITAR SU MANIPULACIÓN
	cola cClientes,cPreferentes,cUsuarios;//DECLARAMOS TRES COLAS PARA TRES TIPOS DE CLIENTES
	elemento persona;
	Initialize(&cClientes);
	Initialize(&cPreferentes);
	Initialize(&cUsuarios);//TERMINAMOS DE INICIALIZAR LAS COLAS Y DECLARAR VARIABLES
	
	printCajas(arregloCord);//NECESITAMOS IMPRIMIR LAS CAJAS, PASAMOS UN APUNTADOR AL ARREGLO DE COORDENADAS PARA CLIENTES
	
	while(pAtendidas!=100){//EL PROCESO DE LLEGADA Y ATENCIÓN FUNCIONARÁ CUANDO pAtendidas<100
		tTranscurrido++;
		//CONDICIONES PARA LA LLEGADA DE CLIENTES
		if(tTranscurrido%tClints==0){
			persona.n=++cLLegados;
			persona.tipo='C';
			Queue(&cClientes,persona);
		}
		if(tTranscurrido%tPrefs==0){
			persona.n=++pLLegados;
			persona.tipo='P';
			Queue(&cPreferentes,persona);
		}
		if(tTranscurrido%tUsus==0){
			persona.n=++uLLegados;
			persona.tipo='U';
			Queue(&cUsuarios,persona);
		}
		printCola(&cClientes,X_CLIENTES,Y_FILAS,fClientes);
		printCola(&cPreferentes,X_PREFERENTES,Y_FILAS,fPreferentes);
		printCola(&cUsuarios,X_USUARIOS,Y_FILAS,fUsuarios);

		for(aux=0;aux<num_cajas;aux++){//RECORREMOS LAS CAJAS PARA VERIFICAR CUÁL PUEDE ATENDER CLIENTES
			if(num_cajas==1){
				if(tTranscurrido%tiemposAtencion[aux]==0){
					if(!Empty(&cPreferentes)&&pAtendidas%5!=0){
						atenderPersona(aux,Dequeue(&cPreferentes),cordCliCajas);
						pAtendidas++;
					}
					else{
						if(!Empty(&cClientes) && pAtendidas%5!=0){
							atenderPersona(aux,Dequeue(&cClientes),cordCliCajas);
							pAtendidas++;
						}
						else{
							if(!Empty(&cUsuarios)){
								atenderPersona(aux,Dequeue(&cUsuarios),cordCliCajas);
								pAtendidas++;
							}
						}
					}
				}
				printCola(&cClientes,X_CLIENTES,Y_FILAS,fClientes);
				printCola(&cPreferentes,X_PREFERENTES,Y_FILAS,fPreferentes);
				printCola(&cUsuarios,X_USUARIOS,Y_FILAS,fUsuarios);
			}
			else{
				if(num_cajas>1){
					if(aux==num_cajas){
						if(!Empty(&cClientes)){
							atenderPersona(aux,Dequeue(&cClientes),cordCliCajas);
							pAtendidas++;
						}
						else{
							if(!Empty(&cPreferentes) && pAtendidas%5!=0){
								atenderPersona(aux,Dequeue(&cPreferentes),cordCliCajas);
								pAtendidas++;
							}
							else{
								if(!Empty(&cUsuarios)){
									atenderPersona(aux,Dequeue(&cPreferentes),cordCliCajas);
									pAtendidas++;
								}
							}
						}
						printCola(&cClientes,X_CLIENTES,Y_FILAS,fClientes);
						printCola(&cPreferentes,X_PREFERENTES,Y_FILAS,fPreferentes);
						printCola(&cUsuarios,X_USUARIOS,Y_FILAS,fUsuarios);	
					}
					else{
						if(!Empty(&cPreferentes) && pAtendidas%5!=0){
							atenderPersona(aux,Dequeue(&cPreferentes),cordCliCajas);
							pAtendidas++;
						}
						else{
							if(!Empty(&cClientes) && pAtendidas%5!=0){
								atenderPersona(aux,Dequeue(&cClientes),cordCliCajas);
								pAtendidas++;
							}
							else{
								if(!Empty(&cUsuarios)){
									atenderPersona(aux,Dequeue(&cUsuarios),cordCliCajas);
									pAtendidas++;
								}
							}
							printCola(&cClientes,X_CLIENTES,Y_FILAS,fClientes);
							printCola(&cPreferentes,X_PREFERENTES,Y_FILAS,fPreferentes);
							printCola(&cUsuarios,X_USUARIOS,Y_FILAS,fUsuarios);
						}
					}
				}
			}
		}
		Sleep(100);
	}
	return;
}

int main(){
	printf("--------------------------\n\tBIENVENIDO\n--------------------------\n");
	printf("Ingresa el numero de cajas que tiene el banco 0<cajas<11: ");
	scanf("%i",&num_cajas);//VARIABLE GLOBAL
	fflush(stdin);
	if(num_cajas<0||num_cajas>10){
		printf("Oye no te pases mano, ingresa un numero valido 0<cajas<11\n");
		exit(1);
	}
	int tiemposAtencion[num_cajas];//NECESARIO PARA SIMULACIÓNBANCO()
	for(aux=0;aux<num_cajas;aux++){
		printf("Ingresa el tiempo de atencion de la caja %i: ",aux+1);
		scanf("%i",&tiemposAtencion[aux]);
		fflush(stdin);
	}
	printf("Ingresa el tiempo de llegada para los clientes: ");
	scanf("%i",&tClints);//VARIABLE GLOBAL
	fflush(stdin);
	printf("Ingresa el tiempo de llegada para los preferentes: ");
	scanf("%i",&tPrefs);//VARIABLE GLOBAL
	fflush(stdin);
	printf("Ingresa el tiempo de llegada para los usuarios: ");
	scanf("%i",&tUsus);//VARIABLE GLOBAL
	fflush(stdin);
	//COMENZAMOS EL PROCESO
	simulacionBanco(tiemposAtencion);
	return 0;
}