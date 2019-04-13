/*
	DICCIONARIO
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include "TADHashTable.h"

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

void cargarDiccionario(tablaHash *diccionario){
	FILE *archivo;
	registro nuevaPalabra; 
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
		printf("%c",charArchivo);
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
				strcpy(&nuevaPalabra.palabra[0],&palabra[0]);
				strcpy(&nuevaPalabra.definicion[0],&definicion[0]);
				AgregarATabla(diccionario,nuevaPalabra);
				printf("\nPalabra %s agregada exitosamente!",nuevaPalabra.palabra);
				if(palabraAlt[0] != '#'){
					strcpy(&nuevaPalabra.palabra[0],&palabra[0]);
					strcpy(&nuevaPalabra.definicion[0],&definicion[0]);
					AgregarATabla(diccionario,nuevaPalabra);
					printf("\nPalabra %s agregada exitosamente!",nuevaPalabra.palabra);
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
	printf("\nPor favor, espere...");
	sleep(2);
	system("cls");
	//system("clear");
	return;
}

void nuevaPalabra(tablaHash *diccionario){
	elemento nueva;
	char palabra[100],definicion[255];
	int aux;
	printf("Ingresa la nueva palabra:\n>");
	scanf("%s[a-zA-Z ]",&palabra);
	fflush(stdin);
	//LIMPIANDO CARACTERES
	for(aux=0;aux<strlen(palabra);aux++){
		palabra[aux]=caracterLatino(palabra[aux]);
	}
	printf("Ingresa su definicion:\n>");
	scanf("%s[a-zA-Z ,.]",&definicion);
	fflush(stdin);
	//LIMPIANDO CARACTERES
	for(aux=0;aux<strlen(definicion);aux++){
		definicion[aux]=caracterLatino(definicion[aux]);
	}
	strcpy(&nueva.palabra[0],&palabra[0]);
	strcpy(&nueva.definicion[0],&definicion[0]);
	AgregarATabla(diccionario,nueva);
	printf("Palabra %s agregada exitosamente!\n",palabra);
	printf("Por favor, espere...\n");
	sleep(2);
	system("cls");
	//system("clear");
	return;
}

void buscaPalabra(tablaHash *diccionario){
	elemento buscame,encontrada;
	char palabra[100],null[4]="NULL";
	int aux,index;
	printf("Ingresa la palabra a buscar:\n>");
	scanf("%s[a-zA-Z ]",palabra);
	for(aux=0;aux<strlen(palabra);aux++){//LIMPIAMOS LA CADENA POR ESO DE LOS CArACTERES RAROS
		palabra[aux]=caracterLatino(palabra[aux]);
	}
	strcpy(&buscame.palabra[0],&palabra[0]);//COPIAMOS LA PALABRA INGRESADA A LA PALABRA DEL NUEVO ELEMENTO
	encontrada=BuscarEnTabla(diccionario,buscame);
	if(strcmp(&encontrada.palabra[0],&null[0])!=0){
		printf("%s: %s\n",encontrada.palabra,encontrada.definicion);
	}
	system("pause");
	system("cls");
	return;
}

int main(){
	int opcion=9,aux;
	tablaHash diccionario;
	printf("TAMANIO %i",TABLE_SIZE);
	diccionario.tamTabla=TABLE_SIZE;
	InicializarTabla(&diccionario);
	while(opcion!=0){
		printf("-------------------------\n\tBIENVENIDO\n--------------------------\n");
		printf("Ingrese la opcion deseada:\n1.- Cargar un archivo de definiciones\n");
		printf("2.- Agregar una palabra\n3.- Buscar una palabra\n4.- Eliminar palabra");
		printf("\n5.- Mostrar estadisticas de la tabla\n>");
		scanf("%i",&opcion);
		switch(opcion){
			case 1:
				cargarDiccionario(&diccionario);
			break;
			case 2:
				nuevaPalabra(&diccionario);
			break;
			case 3:
				buscaPalabra(&diccionario);
			break;
			case 4:
				//eliminarPalabra(diccionario);
			break;
			case 5:
				//mostrarEstats(diccinario);
			break;
			default:
				printf("Ash, me chocas\n");
				exit(1);
			break;
		}
	}
	return 0;
}