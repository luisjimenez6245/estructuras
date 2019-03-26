/*
	SIMULACIÓN DE UN BANCO
	AUTOR: SÁNCHEZ CASTRO AARÓN GAMALIEL (C) MARZO 2019
	VERSIÓN: 1.3
	DESCRIPCIÓN: NPI DE QUÉ HACE EL PROGRAMA
	COMANDO PARA COMPILAR: gcc SimBan.c Gotoxy.o TADColaDin.o -o NombreEjecutable
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
	int pAtendidas=0,pccAtendidas=0,tTranscurrido=0;//pcc=Personas Con Cuenta
	
	int *arregloCord=cordCliCajas;// APUNTADOR AL ARREGLO DE COORDENADAS, PARA FACILITAR SU MANIPULACIÓN
	cola cClientes,cPreferentes,cUsuarios;//DECLARAMOS TRES COLAS PARA TRES TIPOS DE CLIENTES
	elemento persona;
	Initialize(&cClientes);
	Initialize(&cPreferentes);
	Initialize(&cUsuarios);//TERMINAMOS DE INICIALIZAR LAS COLAS Y DECLARAR VARIABLES
	
	printCajas(arregloCord);//NECESITAMOS IMPRIMIR LAS CAJAS, PASAMOS UN APUNTADOR AL ARREGLO DE COORDENADAS PARA CLIENTES
	
	while(pAtendidas!=100){//EL PROCESO DE LLEGADA Y ATENCIÓN FUNCIONARÁ CUANDO pAtendidas<100
		tTranscurrido++;
		//CONDICIONES PARA LA LLEGADA DE LAS PERSONAS
		if(tTranscurrido%tClints==0){//LLEGA UN CLIENTE.
			persona.tipo='C';
			Queue(&cClientes,persona);
		}
		if(tTranscurrido%tPrefs==0){//LLEGA UN PREFERENTE.
			persona.tipo='P';
			Queue(&cPreferentes,persona);
		}
		if(tTranscurrido%tUsus==0){//LLEGA UN USUARIO.
			persona.tipo='U';
			Queue(&cUsuarios,persona);
		}

		printCola(&cClientes,X_CLIENTES,Y_FILAS,fClientes);
		printCola(&cPreferentes,X_PREFERENTES,Y_FILAS,fPreferentes);
		printCola(&cUsuarios,X_USUARIOS,Y_FILAS,fUsuarios);

		//¿CUÁNTAS CAJAS HAY ABIERTAS?
		if(num_cajas==1){//CASO EN EL QUE HAY UNA SOLA.
			if(tTranscurrido%tiemposAtencion[0]==0){//LE TOCA ATENDER 
				if(!Empty(&cPreferentes)){//HAY PERSONAS EN LA FILA PREFERENTE.
					if(pccAtendidas<=5){//AÚN NO SE HAN ATENDIDO A LAS 5 PERSONAS (LIMITE ESTABLECIDO) PUEDE PASAR
						ATENDER_PREFERENTE:
						atenderPersona(0,Dequeue(&cPreferentes),arregloCord);
						pccAtendidas++;// SE INCREMENTA EL NUMERO DE PERSONAS (CON CUENTA) ATENDIDAS
						pAtendidas++;// SE INCREMENTA EL NÚMERO DE PERSONAS (INDISTINTO) ATENDIDAS
						printCola(&cPreferentes,X_PREFERENTES,Y_FILAS,fPreferentes);//REFRECAR LA VENTANA
					}else{
						pccAtendidas=0;//REINICIAMOS EL CONTADOR
						goto ATENDER_USUARIOS;
					}
				}else if(!Empty(&cClientes)){//PREFERENTES VACÍA PERO CLIENTES NO.
					if(pccAtendidas<=5){
						//NO TIENE CASO PONER ETIQUETA PUES EL PROGRAMA CONTINUARÁ EL WHILE
						atenderPersona(0,Dequeue(&cClientes),arregloCord);
						pccAtendidas++;
						pAtendidas++;
						printCola(&cClientes,X_CLIENTES,Y_FILAS,fClientes);
					}else{
						pccAtendidas=0;
						goto ATENDER_USUARIOS;
					}
				}else{//PREFERENTES Y CLIENTES VACÍAS, ¿HAY USUARIOS?.
					ATENDER_USUARIOS:
					if(!Empty(&cUsuarios)){
						atenderPersona(0,Dequeue(&cUsuarios),arregloCord);
						pAtendidas++;
						printCola(&cUsuarios,X_USUARIOS,Y_FILAS,fUsuarios);	
					}
				}
			}//¿NO LE TOCA ATENDER? NO PASA NAAAH :)
		}else{//LO MÁS COMÚN, DOS O MÁS CAJAS
			exit(1);
		}
		//SI NO SE CUMPLE ALGUNA DE ESAS CONDICIONES, EL PROGRAMA CONTINÚA EL WHILE
		Sleep(50);
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