/*
	SIMULACIÓN DE UN BANCO
	AUTOR: SÁNCHEZ CASTRO AARÓN GAMALIEL (C) MARZO 2019
	VERSIÓN: 1.3
	DESCRIPCIÓN: SIMULACIÓN DE LA ATENCIÓN EN UN BANCO, CUIDANDO QUE LAS POLÍTICAS 
		PLANTEADAS EN LA PRESENTACIÓN SE CUMPLAN.
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
int num_cajas,aux,tClints,tPrefs,tUsus,tiempoAtencion;


/*
	FUNCIÓN: printCajas(int *cordCliCajas).
	RECIBE: int *cordCliCajas (APUNTADOR A UN ARREGLO DE COORDENADAS UBICADO EN simulacion()).
	DEVUELVE: EXPLÍCITAMENTE NO DEVUELVE ALGÚN VALOR. MODIFICA EL ARREGLO DE COORDENADAS PARA LOS ESPACIOS EN BLANCO
		DE CADA CAJA.
	DESCRIPCIÓN: ENCARGADA DE IMPRIMIR LAS CAJAS EN LA CONSOLA, ADEMÁS DE GUARDAR LAS COORDENADAS
		DEL INTERIOR DE CADA CAJA, ESTO CON EL FIN DE SABER DÓNDE COLOCAR A LOS CLIENTES AL MOMENTO
		DE SER ATENDIDOS.
	OBSERVACIONES: NINGUNA.
*/
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

/*
	FUNCIÓN: printCola(cola *cola, int cordX, int cordY).
	RECIBE: cola *cola (APUNTADOR A LA COLA QUE SE IMPRIMIRÁ), int cordX (COMPONENTE X DEL PUNTO DONDE SE IMPRIMIRÁ LA COLA)
		int cordY (COMPONENTE Y DEL PUNTO DONDE SE IMPRIMIRÁ LA COLA).
		(APUNTADOR A UN ARREGLO DE ELEMENTOS GLOBAL, CORRESPONDIENTE A CADA TIPO DE CLIENTE).
	DEVUELVE: EXPLÍCITAMENTE NO DEVUELVE ALGÚN VALOR. IMPRIME LA COLA ESPECIFICADA.
	DESCRIPCIÓN: ENCARGADA DE IMPRIMIR LA COLA DEL TIPO DE CLIENTE SOLICITADA, SE DEBE INDICAR LA POSICIÓN
		EN DONDE SE DESEA IMPRIMIR. LOS CLIENTES A IMPRIMIR NO DEBERÁN SOBREPASAR EL LÍMITE DE CLIENTE POR FILA (ÚNICAMENTE PARA MOSTRAR).
	OBSERVACIONES: SE VALIDA QUE LA COLA ESPECIFICADA NO ESTÉ VACÍA, DE LO CONTRARIO NO ES EJECUTADA LA FUNCIÓN
		POR COMPLETO. ADEMÁS, SI EL NÚMERO DE ELEMENTOS CONTENIDOS EN LA COLA ES MAYOR AL TAMAÑO DEL ARREGLO
		DE ELEMENTOS GLOBAL, SE IMPRIME UN + INDICANDO QUE LA LONGITUD DE LA COLA ES MAYOR. SE UTILIZA LA FUNCIÓN
		MoverCursor() INCLUÍDA EN LA LIBRERÍA Gotoxy.h
*/
void printCola(cola *cola,int cordX, int cordY){
	int tamCola;
	if(!Empty(cola)){
		tamCola=Size(cola);
		for(aux=0;aux<MAX_PER_FILA;aux++){//IMPRIMIMOS EL ARREGLO DE ELEMENTOS, EL NUMERO CON EL TIPO DE PERSONA
			if(Element(cola,aux+1).n!=0){//
				MoverCursor(cordX,cordY++);//MOVEMOS EL CURSOR PARA IMPRIMIR DE MANERA VERTICAL Y CENTRADA
				printf("%c%i",Element(cola,aux+1).tipo,Element(cola,aux+1).n);
			}
		}
		if(tamCola>MAX_PER_FILA)
			printf("+");//SI EL TAMAÑO DE LA FILA SOBREPASA AL MÁXIMO PERMITIDO, ENTONCES IMPRIMIMO UN +
	}
	return;
}

/*
	FUNCIÓN: atenderPersona(int numeroCaja, elemento pAtendida, int *cordCliCajas).
	RECIBE: int numeroCaja (POSICIÓN DE LA CAJA DENTRO DEL ARREGLO cordCliCajas), elemento pAtendida
		(PERSONA QUE ES ATENDIDA POR ESA CAJA), int *cordCliCajas (APUNTADOR A UN ARREGLO CUYA DIMENSIÓN	
		ES IGUAL AL NÚMERO DE CAJAS Y QUE CONTIENE LAS COORDENADAS DE LOS ESPACIOS EN BLANCO DE CADA CAJA).
	DEVUELVE: EXPLÍCITAMENTE NO DEVUELVE ALGÚN VALOR. IMPRIME AL CLIENTE EN LA VENTANA INDICADA.
	DESCRIPCIÓN: ENCARGADA DE COLOCAR AL CLIENTE ESPECIFICADO EN LA CAJA INDICADA, ESTO SE LOGRA A TRAVÉS DEL ARREGLO	
		DE COORDENADAS cordCliCajas, PUES ÉL ALMACENA LA POSICIÓN DE LOS ESPACIOS EN BLANCO DE CADA CAJA.
	OBSERVACIONES: SE UTILIZA LA FUNCIÓN MoverCursor() INCLUÍDA EN LA LIBRERÍA Gotoxy.h
*/
void atenderPersona(int numeroCaja, elemento pAtendida, int *cordCliCajas){
	MoverCursor(cordCliCajas[numeroCaja],Y_CAJAS);
	printf("%c%i",pAtendida.tipo,pAtendida.n);
	return;
}

/*
	FUNCIÓN: simulacionBanco(int tiempoAtencion)
	RECIBE: int tiempoAtencion (TIEMPO QUE TARDARÁN LAS CAJAS EN ATENDER A LOS CLIENTES)
	DEVUELVE: EXPLÍCITAMENTE NO DEVUELVE ALGÚN VALOR.
	DESCRIPCIÓN: ENCARGADA DE CORRER LA SIMULACIÓN, HACIENDO USO DE LAS FUNCIONES PREVIAMENTE DEFINIDAS.
		EN ESTA FUNCIÓN SE AGREGAN LOS CLIENTES A SUS COLAS CORRESPONDIENTES, ADEMÁS; LAS CAJAS VERFICAN 
		LA EXISTENCIA DE CLIENTES EN LAS COLAS Y ATIENDEN A LOS MISMOS, MOSTRANDO TODO ESTE PROCESO A TRAVÉS	
		DE FUNCIONES QUE IMPRIMEN EL ESTADO ACTUAL DE LA COLA Y DE LAS CAJAS.
	OBSERVACIONES: PARA FINES PRÁCTICOS LA SIMULACIÓN SE DETIENE AL ATENDER A 100 PERSONAS (CLIENTES DE CUALQUIER TIPO)<.
*/
void simulacionBanco(int tiempoAtencion){
	int cordCliCajas[num_cajas]; //AREGLO CON LAS COORDENADAS PARA DIBUJAR A LOS CLIENTES AL MOMENTO EN QUE SON ATENDIDOS
	int pAtendidas=0,cLLegados=0,uLLegados=0,pLLegados=0,tTranscurrido=0;
	int prefAten=0,ususAten=0,cliAtend=0; //CONTADORES QUE AYUDAN A CUMPLIR LAS POLITICAS DE LA EMPRESA
	int *arregloCord=cordCliCajas;// APUNTADOR AL ARREGLO DE COORDENADAS, PARA FACILITAR SU MANIPULACIÃ“N
	cola cClientes,cPreferentes,cUsuarios;//DECLARAMOS TRES COLAS PARA TRES TIPOS DE CLIENTES
	elemento persona;
	Initialize(&cClientes);
	Initialize(&cPreferentes);
	Initialize(&cUsuarios);//TERMINAMOS DE INICIALIZAR LAS COLAS Y DECLARAR VARIABLES	
	
	while(pAtendidas!=100){//EL PROCESO DE LLEGADA Y ATENCIÃ“N FUNCIONARÃ CUANDO pAtendidas<100
		system("cls");
		printCajas(arregloCord);//NECESITAMOS IMPRIMIR LAS CAJAS, PASAMOS UN APUNTADOR AL ARREGLO DE COORDENADAS PARA CLIENTES
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

		printCola(&cClientes,X_CLIENTES,Y_FILAS);
		printCola(&cPreferentes,X_PREFERENTES,Y_FILAS);
		printCola(&cUsuarios,X_USUARIOS,Y_FILAS);

		if(num_cajas==1){//UN SOLO CAJERO
			if(tTranscurrido%tiempoAtencion==0){
				if(!Empty(&cPreferentes)){//HAY PERSONAS EN LA FILA PREFERENTE.
					//¿CUÁNTOS PREFERENTES HE ATENDIDO?
					if(prefAten<3){//MENOS DE 3, PUEDO SEGUIR ATENDIENDO
						atenderPersona(0,Dequeue(&cPreferentes),cordCliCajas);
						prefAten++;
						pAtendidas++;//PERSONAS (INDISTINTAS) ATENDIDAS
					}else{//YA ATENDÍ TRES, ¿YA ATENDÍ A 5 PERSONAS CON CUENTA?
						if((prefAten+cliAtend)<=5){//NO, ME TOCA ATENDER UN CLIENTE ENTONCES.
							prefAten=0;//REINICIAMOS EL CONTADOR
							if(!Empty(&cClientes)){//NOS ASEGURAMOS DE QUE SEA POSIBLE, LO ES
								goto ATENDER_CLIENTE;
							}else{//NO HAY NADIE EN CLIENTES
								goto ATENDER_USUARIO;
							}
						}else{//SI, HAY QUE ATENDER A UN USUARIO
							prefAten=0;
							cliAtend=0;
							goto ATENDER_USUARIO;
						}
					}
				}else if(!Empty(&cClientes)){//PREFERENTES VACÍA PERO CLIENTES NO.
					ATENDER_CLIENTE:
					atenderPersona(0,Dequeue(&cClientes),cordCliCajas);
					cliAtend++;
					pAtendidas++;
				}else{//PREFERENTES Y CLIENTES VACÍAS, ¿HAY USUARIOS?.
					ATENDER_USUARIO:
					if(!Empty(&cUsuarios)){
						atenderPersona(0,Dequeue(&cUsuarios),cordCliCajas);
						pAtendidas++;
					}
				}
			}
		}else{//MAS DE UN CAJERO ¿CUÁNTOS TENGO?
			for(aux=0;aux<num_cajas;aux++){//RECORREMOS TODOS
				if(tTranscurrido%tiempoAtencion==0){//LES TOCA ATENDER
					if(!Empty(&cPreferentes)){//HAY PERSONAS EN LA FILA PREFERENTE.
						//¿CUÁNTOS PREFERENTES HE ATENDIDO?
						if(prefAten<3){//MENOS DE 3, PUEDO SEGUIR ATENDIENDO
							atenderPersona(aux,Dequeue(&cPreferentes),cordCliCajas);
							prefAten++;
							pAtendidas++;//PERSONAS (INDISTINTAS) ATENDIDAS
						}else{//YA ATENDÍ TRES, ¿YA ATENDÍ A 5 PERSONAS CON CUENTA?
							if((prefAten+cliAtend)<=5){//NO, ME TOCA ATENDER UN CLIENTE ENTONCES.
								prefAten=0;//REINICIAMOS EL CONTADOR
								if(!Empty(&cClientes)){//NOS ASEGURAMOS DE QUE SEA POSIBLE, LO ES
									goto ATENDER_CLIENTE_N;
								}else{//NO HAY NADIE EN CLIENTES
									goto ATENDER_USUARIO_N;
								}
							}else{//SI, HAY QUE ATENDER A UN USUARIO
								prefAten=0;
								cliAtend=0;
								goto ATENDER_USUARIO;
							}
						}
					}else if(!Empty(&cClientes)){//PREFERENTES VACÍA PERO CLIENTES NO.
						ATENDER_CLIENTE_N:
						atenderPersona(aux,Dequeue(&cClientes),cordCliCajas);
						cliAtend++;
						pAtendidas++;
					}else{//PREFERENTES Y CLIENTES VACÍAS, ¿HAY USUARIOS?.
						ATENDER_USUARIO_N:
						if(!Empty(&cUsuarios)){
							atenderPersona(aux,Dequeue(&cUsuarios),cordCliCajas);
							pAtendidas++;
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
	printf("Ingresa el tiempo de atencion para las cajas: ");
	scanf("%i",&tiempoAtencion);//VARIABLE GLOBAL
	fflush(stdin);
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
	simulacionBanco(tiempoAtencion);
	return 0;
}