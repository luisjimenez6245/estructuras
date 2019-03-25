/*AUTORES: Paola Raya Tolentino, 
		 Eduardo Gómez Rodriguez, 
		 Vladimir Azpeitia Hernández.
VERSION: 1.0
DESCRIPCIÓN: Implementacion del algoritmo de huffman, aplicado a documentos de texto. Es solo una 
implementacion didactica.
COMPILACIÓN: gcc -o huffman huffman.c TADArbolBin.o*/

//Librerias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADArbolBin.h"
//Constantes
#define SIZE_ASCII 256 //Numero de arboles por cada caracter ASCII
//Prototipos de funciones
void encode(char nameFile[]); //Funcion para codificar un archivo
void orderTrees(arbol_bin charTrees[], int sizeTree); //Funcion para ordenar arboles de manera ascendente, dependidendo de la frecuencia de cada elemento
void decode(char nameCompressFile[], char nameTableFile[]); //Funcion para descodificar un archivo
void SaveTable(elemento valuesTable[], int sizeTable, char nameTable[]); //Funcion para guardar una tabla de valores
int SearchCharWithCode(elemento valuesTable[], int sizeTable, char huffCode[]); //Funcin para buscar la letra con su codigo

/*FUNCION PRINCIPAL*/
int main(){
	int opc;
	char nameFile[50], nameTableFile[50], nameCompressFile[50]; //Cacdenas que incluiran el nombre del archivo a comprimir, a descomprimir y donde incluye la tabla de valores
 
	printf("--------------------------------------MENU--------------------------------------\n"
		   "Programa que meustra el comportamiento del algoritmo de Huffman\n"
		   "--------------------------------------------------------------------------------\n"
		   "\t1.- Comprimir archivo\n"
		   "\t2.- Descomprimir archivo\n"
		   "\t0.- Salir\n"
		   "--------------------------------------------------------------------------------\n"
		   "Elige una opcion: ");
	scanf("%d", &opc);
	while(opc < 0 || opc >= 3){ 											//Se elige la opción deseada
		printf("Opcion incorrecta. Vuelve a escribir la opcion: ");
		scanf("%d", &opc);
	}

	switch(opc){
		case 1:
			printf("Ingresa el nombre del archivo a comprimir:\n\tejemplo(nameFile.txt)\n");
			scanf("%s", nameFile);//Preguntamos al usuario el nombre del archivo
			encode(nameFile); /*Comprimimos el archivo*/
		break;
		case 2:
			printf("Ingresa el nombre del archivo a descomprimir:\n\tejemplo(nameFile_rar.txt)\n");
			scanf("%s", nameCompressFile); //Preguntamos al usuario el nombre del archivo que desea comprimir
			printf("Ingresa el nombre del archivo que contiene la tabla de valores:\n\tejemplo(nameFile_tabla.txt)\n");
			scanf("%s", nameTableFile);		//Preguntamos al usuario el nombre del archivo que contiene la tabla de valores
			decode(nameCompressFile, nameTableFile);
		break;
		case 0:
			printf("\nBye.");
			exit(0);
		break;
		default:
			printf("Error. Opcion incorrecta\n");
	}

	return 0;
}
/*
void encode(char nameFile[])
Descripción: Funcion oara codificar el archivo.
Recibe: char nameFile[] (nombre del archivo)
Devuelve: void
*/
void encode(char nameFile[]){
	arbol_bin charTreesALL[SIZE_ASCII], newTree, auxTree;//Arreglo de arboles, uno por cada caracter ASCII
	FILE *file, *fp; //Puntero a los archivos
	char c, aux[4], nameCompressFile[50], nameTable[50];
	int character, sizeTree = 0, i, j; //Contadores
	posicion position, backPosition;	//Posiciones auxiliares
	elemento element, backElement, newElement; //Elementos auxiliares

	/*Inicializamos todos los arboles*/
	for(i=0;i<SIZE_ASCII;i++)
		Initialize(&charTreesALL[i]);

	file = fopen(nameFile,"r"); //Abrimos el archivo a codificar

	if (file == NULL){ /*Verificamos que el archivo exista*/
		printf("\nError de apertura del archivo a comprimir. \n\n");
		exit(0);
	}
	else{ /*Si el archvio existe*/
		while((character = fgetc(file)) != EOF){ //Leemos caracter por caracter
			/*Contamos las letras asignado la frecuencia a cada arbol*/
			if(Empty(&charTreesALL[character]) == FALSE){//Si ya habiamos guardado la letra solo aumentamos la frecuencia
				element = ReadNode(&charTreesALL[character], Root(&charTreesALL[character]));
				(element.frequency)++;
				ReplaceNode(&charTreesALL[character], Root(&charTreesALL[character]), element);
			}else{ /*Si es la primera vez que guardamos esa letra*/
				element.character = (char)character;
				element.frequency = 1;
				NewRightSon(&charTreesALL[character], position, element);
				sizeTree++;
			}
		}
	}
	/*Ahora separamos los arboles de los caracteres ASCII que se encuentran en el 
	documento*/
	arbol_bin charTrees[sizeTree]; //arreglo de arboles, uno por cada caracter ASCII que aparece en el documento
	elemento valuesTable[sizeTree];//arreglo de elementos, uno por cada caracter ASCII que aparece en el documento
	for(i = 0; i < sizeTree; i++){
		while(Empty(&charTreesALL[j]) == TRUE)
			j++;
		charTrees[i] = charTreesALL[j]; //Guardamos el arbol en el nuevo arreglo
		valuesTable[i] = ReadNode(&charTrees[i], Root(&charTrees[i]));
 		j++;
 		PrepareTreeForHuffman(&charTrees[i]); //Inicializamos las varaibles de cada elemento 
	}
	/*Union de los arboles*/
	for(i = 0;i < (sizeTree-1);i++){
		Initialize(&newTree); //Inicializamos el arbol auxiliar
		orderTrees(charTrees, sizeTree); //ordenamos el arreglo de arboles
		backPosition = Root(&charTrees[i]); //arbol 1
		position = Root(&charTrees[i+1]); //arbol 2
		element = ReadNode(&charTrees[i+1], position); //elemento del arbol 1
		backElement = ReadNode(&charTrees[i], backPosition); //elemento del arbol 2
		newElement.character = '|';
		newElement.frequency = backElement.frequency + element.frequency; //Asigamos la  frecuencia a la nueva raiz
		NewRightSon(&newTree, NULL, newElement); //Creamos la raiz del nuevo arbol
		PrepareTreeForHuffman(&newTree); //Inicilaizamos las variables de la raiz
		if(element.frequency <= backElement.frequency){
			ReplaceCodeALL(&charTrees[i+1], 0, 0);
			linkTrees(&newTree, charTrees[i+1], 0); //Se unen los arboles 
			ReplaceCodeALL(&charTrees[i], 0, 1); //Cambia el codigo de huffamn de todos los elementos del arbol.
			linkTrees(&newTree, charTrees[i], 1);
		}
		else{
			ReplaceCodeALL(&charTrees[i+1], 0, 1);
			linkTrees(&newTree, charTrees[i+1], 1); //Se unen los arboles
			ReplaceCodeALL(&charTrees[i], 0, 0);
			linkTrees(&newTree, charTrees[i], 0);
		}
		charTrees[i+1] = newTree;//EL nuevo arbol se coloca en la posicion i+1
		Initialize(&newTree); //Reseteamos el arbol auxiliar
	}
	
	for(i = 0;i < sizeTree;++i){
		element = ReadNode(&charTrees[sizeTree-1], Search(&charTrees[sizeTree-1], valuesTable[i].character));
		valuesTable[i].huffmanCode.code = element.huffmanCode.code;//Asignamos el codigo de huffman a cada arbol
		valuesTable[i].huffmanCode.n_bits = element.huffmanCode.n_bits;//Asignamos el codigo de huffman a cada arbol
	} 
 	
	file = fopen(nameFile,"r");
	if (file == NULL){
		printf("\nError de apertura del archivo a comprimir. \n\n");
		exit(0);
	}

	i = 0;
	while(nameFile[i] != '.'){
		nameCompressFile[i] = nameFile[i];
		nameTable[i] = nameFile[i];
		i++;
	}
	nameCompressFile[i] = '\0';
	nameTable[i] = '\0';
	strcat(nameTable, "_tabla.txt");
	SaveTable(valuesTable, sizeTree, nameTable);
	strcat(nameCompressFile, "_rar.txt");
	fp = fopen (nameCompressFile, "w" ); //parametro para escritura al final y para file tipo texto
 	fflush(stdin);
 	printf("\nEl archivo comprimido se a guardado como: \"%s\".", nameCompressFile);
 	
 	while((character = fgetc(file)) != EOF){
 		element = ReadNode(&charTrees[sizeTree-1], Search(&charTrees[sizeTree-1], character));
 		for (i=element.huffmanCode.n_bits-1; i>=0; i--){
 			fprintf(fp, "%d", CONSULTARBIT(element.huffmanCode.code,i));
 		}
 	}
 	fclose(fp); //Cerramos el archivo
 	fclose (file); //Cerramos el archivo
 	for(i=0;i<SIZE_ASCII;i++)//Destruimos todos los arboles para liberar memoria
		Destroy(&charTreesALL[i]);
	for(i=0;i<sizeTree;i++)//Destruimos todos los arboles para liberar memoria
		//Destroy(&charTrees[i]);
	return;
}
/* 
void decode(char nameCompressFile[], elemento table[], int sizeTable)
Descripción: FUNCION PARA DESCODIFICAR UN ARCHIVO
Devuelve: void
*/
void decode(char nameCompressFile[], char  nameTableFile[]){
	FILE *file, *fp; //Puntero a los archivos
 	int character, i = 0, tam = 0, j = 0, b = 0; //Contadores
 	char auxString[30], nameDecodeFile[50];

	file = fopen(nameTableFile,"r"); //Abrimos el archivo de la tabla de valores
	if (file == NULL){ /*Verificamos que el archivo exista*/
		printf("\nError de apertura de la tabla. \n\n");
		exit(0);
	}
	while((character = fgetc(file)) != EOF){ //Leemos caracter por caracter
		if(character == '\n' && b != 0){
			b = 0;
			tam++;
			continue;
		}
		if(character == ';'){
			b=1;
			continue;
		}
	}
	tam++;
	file = fopen(nameTableFile,"r");
	if (file == NULL){ /*Verificamos que el archivo exista*/
		printf("\nError de apertura de la tabla. \n\n");
		exit(0);
	}
	elemento valuesTable[tam]; //Arreglo de elementos
	b=0;
	while((character = fgetc(file)) != EOF){ //Leemos caracter por caracter
		if(character == '\n' && b != 0){
			b = 0;
			valuesTable[i].huffmanCode.newCodeHuffman[j] = '\0';
			j = 0;
			i++;
			continue;
		}
		if(character == ';' && b == 1){
			valuesTable[i].character = character;
			continue;
		}else if(character == ';'){
			b=1;
			continue;
		}
		if(b == 0){
			valuesTable[i].character = character;
		}else if(b == 1){
			valuesTable[i].huffmanCode.newCodeHuffman[j] = character;
			j++;
			if(i == tam-1)
				valuesTable[i].huffmanCode.newCodeHuffman[j] = '\0';
		}	
	}
	fclose(file);

	i = 0;
	while(nameCompressFile[i] != '.'){
		nameDecodeFile[i] = nameCompressFile[i];
		i++;
	}
	nameDecodeFile[i] = '\0';
	strcat(nameDecodeFile, "_descomprimido.txt");
	file = fopen (nameDecodeFile, "w" );

	fp = fopen(nameCompressFile,"r");
	if (fp == NULL){
		printf("\nError de apertura del archivo que esta comprimido. \n\n");
		exit(0);
	}

	i = 0;
	while((character = fgetc(fp)) != EOF){
		//printf("\ni: %d", i);
		auxString[i] = character;
		auxString[i+1] = '\0';
		j = SearchCharWithCode(valuesTable, tam, auxString);
		i++;
		if(j != tam){
			fprintf(file, "%c", valuesTable[j].character);
			i=0;
		}
	}
 	fclose(fp); //Cerraos el archivo
 	fclose(file);
 
 	printf("\nEl archvio descomprimido se creo con el nombre de: \"%s\".", nameDecodeFile);
	return;
}

/*
orderTrees(arbol_bin charTrees[], int sizeTree)
Descripción: Funcion para ordenar arboles
Devuelve: void
*/
void orderTrees(arbol_bin charTrees[], int sizeTree){
	int i, j;
	elemento element, backElement; //Elementos auxiliares
	arbol_bin backTree;		//Arbol auxiliar
	for(j = 1;j<sizeTree;j++){
		for (i = 0;i < sizeTree-1 ;++i){
			backTree = charTrees[i]; 
			element = ReadNode(&charTrees[i+1], Root(&charTrees[i+1]));
			backElement = ReadNode(&backTree, Root(&backTree));
			if(element.frequency < backElement.frequency){ //si el elemento de adelante es mayor el de enfrente se cambian de lugar
				charTrees[i] = charTrees[i+1];
				charTrees[i+1] = backTree;
			}
		}
	}
	return;
}
/*
void SaveTable(elemento valuesTable[], int sizeTable, char nameTable[])
Descripción: Funcion para guardar una tabla de valores
Recibe: elemento valuesTable[], int sizeTable, char nameTable[]
Devuelve: void
*/
void SaveTable(elemento valuesTable[], int sizeTable, char nameTable[]){
	int i, j; //Contadores
	FILE *file; //Puntero a los archivos
	file = fopen(nameTable, "w");		
	for (i = 0;i < sizeTable;++i){
		fprintf(file,"%c;", valuesTable[i].character);
		for(j=valuesTable[i].huffmanCode.n_bits-1; j>=0; j--)
			fprintf(file, "%d",CONSULTARBIT(valuesTable[i].huffmanCode.code,j));
		if(i != sizeTable-1)
			fprintf(file, "\n");
	}
	printf("\nSe a guardado la tabla de valores en: \"%s\".", nameTable);
	fclose(file);
}
/*
int SearchCharWithCode(elemento valuesTable[], int sizeTable, char huffCode[])
Descripción: Funcion para buscar un elemento
Recibe: elemento valuesTable[], int sizeTable, char huffCode[]
Devuelve: int
*/
int SearchCharWithCode(elemento valuesTable[], int sizeTable, char huffCode[]){
	int place = sizeTable, i;
	for(i = 0;i < sizeTable && place == sizeTable;++i){
		if(strcmp(valuesTable[i].huffmanCode.newCodeHuffman, huffCode) == 0)
			place = i;	
	}
	return place;
}

