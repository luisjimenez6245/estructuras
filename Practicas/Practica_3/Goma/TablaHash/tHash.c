/*
	ESTRUCTURA DE DATOS TABLA HASH
	AUTOR: AAR? GAMALIEL S?NCHEZ CASTRO (C) ABRIL 2019
	VERSI? 1.0
	DESCRIPCI?: EL PROGRAMA REALIZA ALMACENA UN DICCIONARIO DE PALABRAS, DISTRIBUY?DOLO EN UNA TABLA HASH
		SE UTILIZA LA LISTA DOBLEMENTE LIGADA COMO AUXILIAR EN EL ALMACENAMIENTO DE PALABRAS
*/
//LIBRERÍAS A UTILIZAR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "ListaDoble.h"

//CONSTANTES A OCUPAR EN EL DICCIONARIO
#define TAMANIO_DICCIONARIO 299

int caracterLatino(int c){
	switch(c){
		case 177: 
			return 164; //ñ
		break;

		case 145:
			return 165; //Ñ
		break;

		case 193:
			return 181; //Á
		break;

		case 201:
			return 144; //É
		break;

		case 205:
			return 214; //Í
		break;

		case 211:
			return 224; //Ó
		break;

		case 218:
			return 233; //Ú
		break;

		case 225:
			return 160; //á
		break;

		case 233:
			return 130; //é
		break;

		case 237:
			return 161; //í
		break;

		case 243:
			return 162; //ó
		break;

		case 250:
			return 163; //ú
		break;

		case 241:
			return 164; //ñ
		break;

		case 209:
			return 165; //Ñ
		break;

		case 252:
			return 129; //ü
		break;

		default:
			return c;
		break;
	}
}

int funcionHash(char palabra[]){
	int index=0,m_posicion,valor_letra,aux;//m_posicion = MÚLTIPLO DE LA POSICIÓN
	for(aux=0;aux<strlen(palabra);aux++){
		m_posicion=pow(2,aux+1);
		valor_letra=(int)palabra[aux];
		index=index+valor_letra*m_posicion;
	}
	if(index<0){
		index=index*-1;
	}
	return index%TAMANIO_DICCIONARIO;
}


void agregarPalabra(List diccionario[], char palabra[], char definicion[]){
	Element nuevoRegistro;
	int index;
	strcpy(&nuevoRegistro.palabra[0],&palabra[0]);
	strcpy(&nuevoRegistro.definicion[0],&definicion[0]);
	index=funcionHash(palabra);
	Add(&diccionario[index],nuevoRegistro);
	printf("\n...Palabra %s agregada exitosamente!\n",palabra);
	fflush(stdout);
	fflush(stdin);
	return;
}


void cargarDiccionario(List diccionario[]){
	FILE *archivo;
	char rutaArchivo[100],palabra[100],palabraAlt[100],definicion[251],estado='p';
	/*	ES NECESARIOO CREAR LA VARIABLE palabraAlt PUESTO QUE ALGUNAS PALABRAS TIENEN "ALTERNATIVAS"
		MARCADAS POR EL SIMBOLO /, EL PROGRAMA DEBE RECONOCERLAS COMO PALABRAS DIFERENTES
		LA VARIABLE estado INDICA LA TRANSICIÓN DE PALABRA A DEFINICIÓN
	*/
	int charArchivo,i=0;
	printf("Ingresa la ruta del archivo:\n>");
	scanf("%s", &rutaArchivo);
	archivo = fopen(rutaArchivo,"r");
	palabraAlt[0] = '#';
	while((charArchivo = getc(archivo)) != EOF){
		charArchivo = caracterLatino(charArchivo);
		if(charArchivo != 195){
			if (charArchivo=='/' && estado == 'p'){
				estado='q';
				palabra[i] = '\0';
				i=0;
				continue;
			}
			if (charArchivo==':'){
				if(estado == 'p')
					palabra[i] = '\0';
				if(estado == 'q')
					palabraAlt[i] = '\0';
				estado='s';
				i=0;
				continue;
			}
			if (charArchivo=='\n'){
				definicion[i]=charArchivo;
				definicion[i+1] = '\0';
				agregarPalabra(diccionario, palabra, definicion);
				if(palabraAlt[0] != '#'){
					agregarPalabra(diccionario, palabraAlt, definicion);
					palabraAlt[0] = '#';
				}
				fflush(stdout);
				estado = 'p';
				palabra[0] = '#';
				i=0;
				continue;
			}
			if(estado == 'p'){
				palabra[i]=charArchivo;
				i++;
			}
			if(estado == 'q'){
				palabraAlt[i]=charArchivo;
				i++;
			}
			if(estado == 's'){
				definicion[i]=charArchivo;
				i++;
			}
		}
	}
	printf("Por favor, espere...");
	sleep(2);
	system("cls");
	//system("clear");
	return;
}

void nuevaPalabra(List diccionario[]){
	char palabra[100],definicion[255];
	int aux;
	printf("Ingresa la nueva palabra:\n>");
	scanf("%s[a-zA-Z]",&palabra);
	fflush(stdin);
	//LIMPIANDO CARACTERES
	for(aux=0;aux<strlen(palabra);aux++){
		palabra[aux]=caracterLatino(palabra[aux]);
	}
	printf("Ingresa su definicion:\n>");
	scanf("%s[a-zA-Z /.,;]",&definicion);
	fflush(stdin);
	agregarPalabra(diccionario,palabra,definicion);
	printf("Por favor, espere...");
	sleep(2);
	system("cls");
	//system("clear");
	return;
}

void buscarPalabra(List diccionario[]){
	Element buscame;
	char palabra[100];
	int aux,index;
	printf("Ingresa la palabra a buscar:\n>");
	scanf("%s[a-zA-Z ]",palabra);
	for(aux=0;aux<strlen(palabra);aux++){//LIMPIAMOS LA CADENA POR ESO DE LOS CArACTERES RAROS
		palabra[aux]=caracterLatino(palabra[aux]);
	}
	strcpy(&buscame.palabra[0],&palabra[0]);//COPIAMOS LA PALABRA INGRESADA A LA PALABRA DEL NUEVO ELEMENTO
	index=funcionHash(palabra);//APLICAMOS LA FUNCION HASH PARA SABER EN DÓNDE SE GUARDÓ
	if(Search(&diccionario[index],buscame)!=NULL){//COMPROBAMOS QUE EXISTE LA PALABRA DENTRO DE LA LISTA
		Element encontrada=GetElement(&diccionario[index],Search(&diccionario[index],buscame));
		printf("%s : %s\n",encontrada.palabra,encontrada.definicion);
		printf("Encontrada en %i pasos\n",Search(&diccionario[index],buscame)->pasos);
	}else{
		printf("La palabra solicitada no existe en el diccionario...\n");
	}
	system("pause");
	system("cls");
	return;
}

void eliminarPalabra(List diccionario[]){
	Element buscame;
	char palabra[100];
	int aux,index;
	printf("Ingresa la palabra a eliminar\n>");
	scanf("%s[a-zA-Z ]",&palabra);
	for(aux=0;aux<strlen(palabra);aux++){//LIMPIAMOS LA CADENA POR ESO DE LOS CArACTERES RAROS
		palabra[aux]=caracterLatino(palabra[aux]);
	}
	strcpy(&buscame.palabra[0],&palabra[0]);//COPIAMOS LA PALABRA INGRESADA A LA PALABRA DEL NUEVO ELEMENTO
	index=funcionHash(palabra);//APLICAMOS LA FUNCION HASH PARA SABER EN DÓNDE SE GUARDÓ
	if(Search(&diccionario[index],buscame)!=NULL){//COMPROBAMOS QUE EXISTE LA PALABRA DENTRO DE LA LISTA
		printf("Elemento encontrado...\nEliminando...\n");
		Remove(&diccionario[index],Search(&diccionario[index],buscame));//BORRAMOS EL ELEMENTO
		printf("Eliminado...\n");
	}
	printf("Por favor, espere...");
	sleep(2);
	system("cls");
	//system("clear");
	return;
}

void mostrarEstats(){
	return;
}

int main(){
	int opcion=9,aux;
	List diccionario[TAMANIO_DICCIONARIO];//DECLARANDO UN ARREGLO DE LISTAS, NUESTRO DICCIONARIO
	for(aux=0;aux<TAMANIO_DICCIONARIO;aux++){//INICIALIZANDO LAS LISTAS
		Initialize(&diccionario[aux]);
	}
	while(opcion!=0){
		printf("-------------------------\n\tBIENVENIDO\n--------------------------\n");
		printf("Ingrese la opcion deseada:\n1.- Cargar un archivo de definiciones\n");
		printf("2.- Agregar una palabra\n3.- Buscar una palabra\n4.- Eliminar palabra");
		printf("\n5.- Mostrar estadisticas de la tabla\n>");
		scanf("%i",&opcion);
		switch(opcion){
			case 1:
				cargarDiccionario(diccionario);
			break;
			case 2:
				nuevaPalabra(diccionario);
			break;
			case 3:
				buscarPalabra(diccionario);
			break;
			case 4:
				eliminarPalabra(diccionario);
			break;
			case 5:
				mostrarEstats(diccinario);
			break;
			default:
				printf("Ash, me chocas\n");
				exit(1);
			break;
		}
	}
	return 0;
}
